#include "ScriptManager.hpp"

#include "AS_SFML.hpp"
#include <scriptarray/scriptarray.h>
#include <scriptbuilder/scriptbuilder.h>
#include <scriptdictionary/scriptdictionary.h>
#include <scriptstdstring/scriptstdstring.h>
#include <chrono>

#include <cassert>

asUINT getTime()
{
	return asUINT(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

int includeFile(const char *include, const char *from, CScriptBuilder *builder, void *userParam)
{
	std::string caller = from,
	            target = include;

	auto lastSlash = caller.find_last_of('/');
	if (lastSlash != std::string::npos)
	{
		caller = caller.substr(0, lastSlash);
		target = caller + "/" + target;
	}

	return builder->AddSectionFromFile(target.c_str());
}

ScriptManager::ScriptManager()
	: mScriptEngine(nullptr)
{

}
ScriptManager::~ScriptManager()
{

}

void ScriptManager::init()
{
	mScriptEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

	RegisterStdString(mScriptEngine);
	RegisterScriptArray(mScriptEngine, true);
	RegisterScriptDictionary(mScriptEngine);
	RegisterScriptSFML(mScriptEngine);

	mContexts.SetGetTimeCallback(&getTime);
	mContexts.RegisterCoRoutineSupport(mScriptEngine);
	mContexts.RegisterThreadSupport(mScriptEngine);
}

asIScriptObject* ScriptManager::createObject(const std::string& modName, const std::string& typeName)
{
	auto* mod = this->operator[](modName);
	if (!mod)
		return nullptr;

	auto* type = mod->GetTypeInfoByName(typeName.c_str());
	if (!type)
		return nullptr;

	return static_cast<asIScriptObject*>(mScriptEngine->CreateScriptObject(type));
}

asIScriptModule* ScriptManager::operator[](const std::string& name)
{
	auto* mod = mScriptEngine->GetModule(name.c_str());
	if (!mod)
	{
		CScriptBuilder build;

		build.SetIncludeCallback(&includeFile, nullptr);

		int r = build.StartNewModule(mScriptEngine, name.c_str()); assert(r >= 0);
		
		r = build.AddSectionFromFile(name.c_str()); assert(r >= 0);
		r = build.BuildModule(); assert(r >= 0);
		mod = build.GetModule(); assert(mod);

		r = mod->BindAllImportedFunctions(); assert(r >= 0);
	}
	
	return mod;
}

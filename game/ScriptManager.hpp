#pragma once

#include <contextmgr/contextmgr.h>

#include <string>

class ScriptManager
{
public:
	ScriptManager();
	ScriptManager(const ScriptManager&) = delete;
	ScriptManager(ScriptManager&&) = delete;
	~ScriptManager();

	ScriptManager& operator=(const ScriptManager&) = delete;

	void init();
	asIScriptObject* createObject(const std::string& mod, const std::string& type);

	asIScriptModule* operator[](const std::string&);

private:
	asIScriptEngine* mScriptEngine;
	CContextMgr mContexts;
};
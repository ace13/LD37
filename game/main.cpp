#include <SFML/System.hpp>

#include "AS_SFML.hpp"
#include <contextmgr/contextmgr.h>
#include <scriptarray/scriptarray.h>
#include <scriptdictionary/scriptdictionary.h>
#include <scriptstdstring/scriptstdstring.h>
#include <angelscript.h>

#include <chrono>

asUINT getTime()
{
	return asUINT(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

int main(int argc, char** argv)
{
	CContextMgr mgr;

	asIScriptEngine* eng = asCreateScriptEngine();
	
	RegisterStdString(eng);
	RegisterScriptArray(eng, true);
	RegisterScriptDictionary(eng);
	RegisterScriptSFML(eng);

	mgr.SetGetTimeCallback(&getTime);
	mgr.RegisterCoRoutineSupport(eng);
	mgr.RegisterThreadSupport(eng);

	return 0;
}
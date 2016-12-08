#include "AS_SFML.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <angelscript.h>

#include <cassert>

#define ASR assert(r >= 0)

namespace
{

template<typename T>
void sfDefaultConstructor(void* mem)
{
	new(mem) T();
}

template<typename T>
void sfDefaultCopyConstructor(void* mem, const T& copy)
{
	new(mem) T(copy);
}

template<typename T>
T& sfDefaultAssign(T& obj, const T& rhs)
{
	return obj = rhs;
}

template<typename T>
void sfDefaultDestructor(T* mem)
{
	mem->~T();
}

}

void RegisterScriptSFML(asIScriptEngine* engine)
{
	int r = 0;

	r = engine->SetDefaultNamespace("sf"); ASR;

#define REF_TYPE(T, N) RegisterObjectType(N, 0, asOBJ_REF | asOBJ_NOCOUNT)
#define VAL_TYPE(T, N) RegisterObjectType(N, sizeof(T), asOBJ_VALUE | asGetTypeTraits<T>()); ASR; \
r = engine->RegisterObjectBehaviour(N, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(sfDefaultConstructor<T>), asCALL_CDECL_OBJFIRST); ASR; \
r = engine->RegisterObjectBehaviour(N, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(sfDefaultDestructor<T>), asCALL_CDECL_OBJFIRST); ASR; \
r = engine->RegisterObjectBehaviour(N, asBEHAVE_CONSTRUCT, "void f(" N "&in)", asFUNCTION(sfDefaultCopyConstructor<T>), asCALL_CDECL_OBJFIRST); ASR; \
r = engine->RegisterObjectMethod(N, N "& opAssign(" N "&in)", asFUNCTION(sfDefaultAssign<T>), asCALL_CDECL_OBJFIRST)

	r = engine->VAL_TYPE(sf::Color, "Color"); ASR;
	r = engine->REF_TYPE(sf::Music, "Music"); ASR;
	r = engine->VAL_TYPE(sf::FloatRect, "FloatRect"); ASR;
	r = engine->VAL_TYPE(sf::IntRect, "IntRect"); ASR;
	r = engine->VAL_TYPE(sf::Vector2f, "Vector2f"); ASR;
	r = engine->VAL_TYPE(sf::Vector2i, "Vector2i"); ASR;
	r = engine->VAL_TYPE(sf::Vector2u, "Vector2u"); ASR;
	r = engine->VAL_TYPE(sf::Vector3f, "Vector3f"); ASR;
	r = engine->VAL_TYPE(sf::Vector3i, "Vector3i"); ASR;
	r = engine->REF_TYPE(sf::RenderTarget, "RenderTarget"); ASR;
	r = engine->VAL_TYPE(sf::Sound, "Sound"); ASR;

	r = engine->VAL_TYPE(sf::Sprite, "Sprite"); ASR;
	r = engine->VAL_TYPE(sf::CircleShape, "CircleShape"); ASR;
	r = engine->VAL_TYPE(sf::RectangleShape, "RectangleShape"); ASR;
	r = engine->VAL_TYPE(sf::ConvexShape, "ConvexShape"); ASR;

#undef REF_TYPE
#undef VAL_TYPE

	r = engine->SetDefaultNamespace(""); ASR;



}
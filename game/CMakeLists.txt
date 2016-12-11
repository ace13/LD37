set(LD37_HEADERS
	AS_SFML.hpp

	Application.hpp
	InputManager.hpp
	Inputs.hpp
	ParticleManager.hpp
	ScriptManager.hpp

	Game/Drink.hpp
	Game/Object.hpp
	Game/Patron.hpp
	Game/Player.hpp
	Game/Room.hpp
)

set(LD37_SOURCES
	AS_SFML.cpp

	Application.cpp
	InputManager.cpp
	ParticleManager.cpp
	ScriptManager.cpp
	
	Game/Drink.cpp
	Game/Object.cpp
	Game/Patron.cpp
	Game/Player.cpp
	Game/Room.cpp

	main.cpp
)

source_group("Header files\\" REGULAR_EXPRESSION "[^./]+.(hpp|inl)")
source_group("Source files\\" REGULAR_EXPRESSION "[^./]+.cpp")
source_group("Header files\\Game" REGULAR_EXPRESSION "Game/[^./]+.(hpp|inl)")
source_group("Source files\\Game" REGULAR_EXPRESSION "Game/[^./]+.cpp")

if (WIN32)
	set(SFML_MAIN main)
endif()

find_package(SFML 2 REQUIRED COMPONENTS audio graphics system window network ${SFML_MAIN})
find_package(Angelscript REQUIRED)

include_directories(
	${Angelscript_INCLUDE_DIR}
	${SFML_INCLUDE_DIR}
)

add_executable(LD37 ${LD37_HEADERS} ${LD37_SOURCES} ${LD37_ASX})
target_link_libraries(LD37
	LD37_ASX
	${Angelscript_LIBRARIES}
	${SFML_LIBRARIES}
)
set_target_properties(LD37 PROPERTIES
	CXX_STANDARD 14
)

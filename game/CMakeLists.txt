set(LD37_HEADERS
	Application.hpp
	InputManager.hpp
	ScriptManager.hpp

	AS_SFML.hpp
)

set(LD37_SOURCES
	Application.cpp
	InputManager.cpp
	ScriptManager.cpp

	AS_SFML.cpp

	main.cpp
)

source_group("Header files\\" REGULAR_EXPRESSION "[^./]+.(hpp|inl)")
source_group("Source files\\" REGULAR_EXPRESSION "[^./]+.cpp")

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

set(LD37_ASX
	contextmgr/contextmgr.h
	contextmgr/contextmgr.cpp
	scriptany/scriptany.h
	scriptany/scriptany.cpp
	scriptarray/scriptarray.h
	scriptarray/scriptarray.cpp
	scriptbuilder/scriptbuilder.h
	scriptbuilder/scriptbuilder.cpp
	scriptdictionary/scriptdictionary.h
	scriptdictionary/scriptdictionary.cpp
	scriptgrid/scriptgrid.h
	scriptgrid/scriptgrid.cpp
	scripthandle/scripthandle.h
	scripthandle/scripthandle.cpp
	scripthelper/scripthelper.h
	scripthelper/scripthelper.cpp
	scriptmath/scriptmath.h
	scriptmath/scriptmath.cpp
	scriptmath/scriptmathcomplex.h
	scriptmath/scriptmathcomplex.cpp
	scriptstdstring/scriptstdstring.h
	scriptstdstring/scriptstdstring.cpp
	scriptstdstring/scriptstdstring_utils.cpp
	serializer/serializer.h
	serializer/serializer.cpp
)

source_group("Header files" REGULAR_EXPRESSION "[^.]+.h")
source_group("Source files" REGULAR_EXPRESSION "[^.]+.cpp")

find_package(Angelscript REQUIRED)
include_directories(
	${Angelscript_INCLUDE_DIR}
)

add_library(LD37_ASX STATIC ${LD37_ASX})
target_link_libraries(LD37_ASX
	${Angelscript_LIBRARIES}
)
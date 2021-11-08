cmake_minimum_required( VERSION 3.16 )

project( JXSerializer VERSION 1.0.0 )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set( SRC 
    "src/Object.cpp"
    "src/JSON/JsonDump.cpp"
    "src/JSON/JsonParser.cpp")

set( HEADERS
"src/Serializer.h"
"src/Object.h"
"src/JSON/JsonDump.h"
"src/JSON/JsonParser.h")

add_library( Serializer "${SRC}" )

install(DIRECTORY "${CMAKE_SOURCE_DIR}/src/" DESTINATION "include/Serializer"
          FILES_MATCHING PATTERN "*.h")

install(TARGETS Serializer)

enable_testing()

add_executable( tester "tests/test.cpp" )
target_link_libraries( tester PRIVATE Tester Serializer )
add_test( NAME basictest COMMAND tester WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}" )
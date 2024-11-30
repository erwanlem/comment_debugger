cmake_minimum_required(VERSION 3.28)
project(X)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Compile with YACC and BISON
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

message(${CMAKE_CURRENT_SOURCE_DIR})

BISON_TARGET(gdbCppParser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
                DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hh
)
FLEX_TARGET(gdbCppLexer lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
                )

ADD_FLEX_BISON_DEPENDENCY(gdbCppLexer gdbCppParser)

add_library(parseCppOutput
    STATIC
    driver.hh
    value.h
    async.h
    output.h
    ${BISON_gdbCppParser_OUTPUTS}
    ${FLEX_gdbCppLexer_OUTPUTS}
)
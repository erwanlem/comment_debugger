cmake_minimum_required(VERSION 3.28)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Compile with YACC and BISON
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

message(${CMAKE_CURRENT_SOURCE_DIR})

BISON_TARGET(inputFileParser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
                DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.h
)
FLEX_TARGET(inputFileLexerLayer1 lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
                COMPILE_FLAGS "-Pf")
FLEX_TARGET(inputFileLexerLayer0 comment_lexer.l ${CMAKE_CURRENT_BINARY_DIR}/comment_lexer.cpp
                COMPILE_FLAGS "-Player0"          
)
ADD_FLEX_BISON_DEPENDENCY(inputFileLexerLayer1 inputFileParser)


add_library(parse
    STATIC
    comments.h
    comments.cpp
    ${BISON_inputFileParser_OUTPUTS}
    ${FLEX_inputFileLexerLayer1_OUTPUTS}
    ${FLEX_inputFileLexerLayer0_OUTPUTS}
)
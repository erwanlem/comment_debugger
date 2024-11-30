cmake_minimum_required(VERSION 3.28)
project(debug)

set(CMAKE_INSTALL_PREFIX     "../install")

add_subdirectory(lexer)

add_executable(debugTool
    main.cpp
    input.cpp
    input.h
    printer.h
    provider.cpp
    provider.h
    reader.cpp
    reader.h
    compile.h
    compile.cpp
)

add_subdirectory(cplusplus)
target_link_libraries(debugTool parse)

install(TARGETS debugTool DESTINATION bin)
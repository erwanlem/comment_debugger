cmake_minimum_required(VERSION 3.28)


add_subdirectory(parser)

target_sources(debugTool
    PUBLIC
        commands.cpp
        commands.h
        interface.cpp
        interface.h
)

target_link_libraries(debugTool parseCppOutput)
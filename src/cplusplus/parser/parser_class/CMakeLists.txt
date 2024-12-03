cmake_minimum_required(VERSION 3.28)
project(X)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

target_sources(parseCppOutput
    async.h
    asyncRecord.h
    outbandrecord.h
    output.h
    resultRecord.h
    streamRecord.h
    value.h
)
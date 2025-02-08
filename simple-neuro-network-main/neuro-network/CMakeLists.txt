cmake_minimum_required(VERSION 2.8)

project(neuro-network)
add_library(neuro-network STATIC)

set(SOURCE myneuro.cpp)
set(HEADER myneuro.h)

target_sources(neuro-network PRIVATE ${HEADER} ${SOURCE})

find_package(Qt6 REQUIRED COMPONENTS Core)
target_link_libraries(neuro-network PRIVATE Qt6::Core)



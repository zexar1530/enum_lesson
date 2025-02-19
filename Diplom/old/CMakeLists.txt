cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)

project(CppDiplomProject)

set(SOURCES
    main.cpp
    Start.cpp
    Readconfig.cpp
    PostgreDb.cpp
    Spider.cpp
    StaticSpider.cpp
    http_server.cpp
)

set(HEADERS
    Start.h
    Readconfig.h
    PostgreDb.h
    Spider.h
    StaticSpider.h
    http_server.h
)

add_executable(CppDiplomProject ${SOURCES} ${HEADERS})
#target_compile_definitions(CppDiplomProject PRIVATE FULL_PROJECT_MODE)


set(OPENSSL_ROOT_DIR "C:\\Program Files\\OpenSSL-Win64\\")

set(BOOST_ROOT "C:\\boost_1_86_0\\")

set(libpqxx_DIR "C:\\Users\\zexar\\Documents\\LibDataBasepqxx\\libpqxx-7.9.0\\")

#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
#find_package(Boost 1.86 COMPONENTS system)


add_compile_definitions(_WIN32_WINNT=0x0A01)



find_package(Boost 1.86.0 REQUIRED COMPONENTS system thread locale)

set(PostgreSQL_ADDITIONAL_VERSIONS "12")

add_subdirectory(${libpqxx_DIR} libpqxx-build) 


find_package(OpenSSL REQUIRED)

target_compile_features(CppDiplomProject PRIVATE cxx_std_20) 

target_link_libraries(CppDiplomProject pqxx) 

target_link_libraries(CppDiplomProject OpenSSL::SSL)

target_include_directories(CppDiplomProject PUBLIC ${Boost_INCLUDE_DIRS})

target_link_libraries(CppDiplomProject ${Boost_LIBRARIES})



#target_include_directories(SpiderApp PRIVATE ${Boost_INCLUDE_DIRS})

#target_link_libraries(SpiderApp ${Boost_LIBRARIES})
cmake_minimum_required(VERSION 4.0)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
    "f35a9ac6-8463-4d38-8eec-5d6008153e7d"
)

set(CMAKE_CXX_MODULE_STD ON)

set(CMAKE_CXX_STDLIB_MODULES_JSON
    "/usr/lib/gcc/x86_64-linux-gnu/15/libstdc++.modules.json"
)

project(HelloWorld CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app main.cpp)
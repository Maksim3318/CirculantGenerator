cmake_minimum_required(VERSION 3.23)
project(CirculantGenerator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Werror")

add_executable(CirculantGenerator
        src/main.cpp
        src/gen.cpp
        src/gen.hpp
        src/generator.cpp
        src/generator.hpp
        src/graphparameters.cpp
        src/graphparameters.hpp
        src/profile.hpp
        src/search.cpp
        src/search.hpp
        src/utils.hpp
        src/constants.hpp
        src/constants.cpp
        )

cmake_minimum_required(VERSION 3.10)
project(projeto_01 C)

set(CMAKE_C_STANDARD 99)

add_executable(projeto-01
        main.c
        contador.c
        util.c
)
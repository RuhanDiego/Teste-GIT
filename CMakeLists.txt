cmake_minimum_required(VERSION 3.10)
project(projeto01 C)

set(CMAKE_C_STANDARD 99)

add_executable(projeto01 main.c util.c contador.c)
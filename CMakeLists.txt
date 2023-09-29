cmake_minimum_required(VERSION 3.25)
project(Projeto_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Projeto_2
        .gitignore
        biblioteca.c
        biblioteca.h
        LICENSE
        main.c
        README.md)

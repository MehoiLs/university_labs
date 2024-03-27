cmake_minimum_required(VERSION 3.26)
project(ds_sem4_lab1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ds_sem3_lab1 main.cpp
        HashTable.h
        Hashable.h
        MyClass.h
        HashString.h
        Logger.h)

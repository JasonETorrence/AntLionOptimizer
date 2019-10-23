cmake_minimum_required(VERSION 3.13)
project(Algorithms C)

set(CMAKE_C_STANDARD 99)

add_executable(
        Algorithms
        main.c
        Utils/Utils.h
        Algorithms/Algorithms.c
        Algorithms/Algorithms.h
        Params/Params.c
        Params/Params.h
        Utils/Utils.c
        MatrGen/MatrGen.c
        MatrGen/MatrGen.h
        MT/mt19937ar.c
        MT/mt19937ar.h
        DataContainer/DataContainer.c
        DataContainer/DataContainer.h
        VectorAndResult/VectorAndResult.c
        VectorAndResult/VectorAndResult.h
        ALO/ALO.c
        ALO/ALO.h
        )

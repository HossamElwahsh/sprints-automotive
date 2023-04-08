cmake_minimum_required(VERSION 3.25)
project(Led_Sequence_V1_0 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Led_Sequence_V1_0
        main.c
        ECUAL/Button\ Driver/button.c
        ECUAL/Button\ Driver/button.h
        "ECUAL/LED Driver/led.c" Application/application.c "MCAL/DIO Driver/dio.c" "MCAL/EXI Driver/interrupts.c")
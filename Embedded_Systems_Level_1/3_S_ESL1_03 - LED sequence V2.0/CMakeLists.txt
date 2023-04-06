cmake_minimum_required(VERSION 3.25)
project(Led_Sequence_V1_0 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Led_Sequence_V1_0
        main.c
        main.h Application/application.c Common/bit_manipulation.h "ECUAL/LED Driver/led.c" "MCAL/DIO Driver/dio.c" "ECUAL/Button Driver/button.c" "MCAL/Timer Driver/timer.c" "MCAL/Timer Driver/timer.h" "MCAL/EXI Driver/interrupts.h" "MCAL/EXI Driver/interrupts.c")
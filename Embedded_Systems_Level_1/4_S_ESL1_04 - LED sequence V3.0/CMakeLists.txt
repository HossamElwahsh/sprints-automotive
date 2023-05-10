cmake_minimum_required(VERSION 3.25)
project(Led_Sequence_V3_0 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Led_Sequence_V3_0
        main.c Application/application.c "ECUAL/LED Driver/led.c" "MCAL/Timer Driver/timer.c" "MCAL/DIO Driver/dio.c" "MCAL/EXI Driver/interrupts.c" "ECUAL/Button Driver/button.c")
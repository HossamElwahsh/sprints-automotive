cmake_minimum_required(VERSION 3.25)
project(Led_Sequence_V3_0 C)

set(CMAKE_C_STANDARD 11)

include_directories(
        .
        MCAL/dio
        MCAL/timer
        MCAL/exi

        HAL/btn
        HAL/led

        LIB/

        APP/
)

add_executable(Led_Sequence_V3_0

        APP/app_program.c
        APP/app_interface.h

        HAL/btn/btn_interface.h
        HAL/btn/btn_program.c

        HAL/led/led_interface.h
        HAL/led/led_program.c

        MCAL/dio/dio_program.c
        MCAL/dio/dio_interface.h
        MCAL/dio/dio_private.h

        MCAL/exi/exi_program.c
        MCAL/exi/exi_interface.h
        MCAL/exi/exi_private.h

        MCAL/timer/timer_private.h
        MCAL/timer/timer_interface.h
        MCAL/timer/timer_program.c

        LIB/bit_manipulation.h
        LIB/interrupts.h
        LIB/std.h

        main.c
        main.h

        )
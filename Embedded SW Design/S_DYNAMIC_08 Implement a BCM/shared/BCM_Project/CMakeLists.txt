cmake_minimum_required(VERSION 3.25)
project(BCM C)

set(CMAKE_C_STANDARD 11)

include_directories(MCU1)
include_directories(MCU1/MCAL)
include_directories(MCU1/MCAL/dio)
include_directories(MCU1/UTILITIES)
include_directories(MCU2)
include_directories(MCU2/MCAL)
include_directories(MCU2/MCAL/dio)
include_directories(MCU2/UTILITIES)

add_executable(BCM_MCU1
        MCU1/MCAL/dio/dio_interface.h
        MCU1/MCAL/dio/dio_private.h
        MCU1/MCAL/dio/dio_program.c
        MCU1/UTILITIES/bit_manipulation.h
        MCU1/UTILITIES/std.h
        MCU1/main.c
        MCU1/MCAL/uart/uart_program.c
        MCU1/MCAL/uart/uart_linking_config.c
        MCU1/UTILITIES/circular_queue/cqueue_program.c
        MCU1/HAL/led/led_program.c MCU1/APP/app_program.c MCU1/APP/app_interface.h MCU1/SERV/bcm/bcm_program.c MCU1/SERV/bcm/bcm_linking_config.c)

add_executable(BCM_MCU2

        MCU2/MCAL/dio/dio_interface.h
        MCU2/MCAL/dio/dio_private.h
        MCU2/MCAL/dio/dio_program.c
        MCU2/UTILITIES/bit_manipulation.h
        MCU2/UTILITIES/std.h
        MCU2/main.c
        MCU2/UTILITIES/circular_queue/cqueue_program.c
        MCU2/MCAL/uart/uart_program.c MCU2/MCAL/uart/uart_linking_config.c MCU2/APP/app_program.c MCU2/SERV/bcm/bcm_program.c MCU2/SERV/bcm/bcm_linking_config.c MCU2/HAL/led/led_program.c)

cmake_minimum_required(VERSION 3.21)
project(philosopher42 C)

set(CMAKE_C_STANDARD 99)

add_executable(philosopher42 philo/srcs/philo.c philo/srcs/check_end.c philo/srcs/clean_exit.c philo/srcs/create_threads.c
        philo/srcs/get_time.c philo/srcs/init_game.c philo/srcs/print_status.c philo/srcs/routine.c)
include_directories(includes/)
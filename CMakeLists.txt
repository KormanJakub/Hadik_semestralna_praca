cmake_minimum_required(VERSION 3.18)
project(Hadik_semestralna_praca C)

set(CMAKE_C_STANDARD 99)

add_executable(Server server.c game_snake.c)
add_executable(Client client.c game_snake.c)
add_executable(Main main.c server.c client.c game_snake.c)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

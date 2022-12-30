cmake_minimum_required(VERSION 3.18)
project(Hadik_semestralna_praca C)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_C_STANDARD 99)

add_executable(Server k_a_t_server.c)
add_executable(Client k_a_t_client.c)
add_executable(Main main.c)
add_executable(snake snake.c)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

target_link_libraries(snake ${SDL2_LIBRARIES})
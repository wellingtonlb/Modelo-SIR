cmake_minimum_required(VERSION 3.16)
project(dispersion)

find_package(igraph REQUIRED)

add_executable(city-edd random.c sir.c db.c move.c network.c main.c)
target_link_libraries(city-edd PUBLIC igraph::igraph)
cmake_minimum_required(VERSION 3.18)
project(myProject)



set(CMAKE_CXX_STANDARD 17)


add_compile_options(-pthread)
# add_compile_options(-g -Wall -Werror -Wpedantic -Wextra)
# add_compile_options(-fdiagnostics-color)


add_subdirectory(hal)
add_subdirectory(app)
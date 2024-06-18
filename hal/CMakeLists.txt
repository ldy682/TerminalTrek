include_directories(include/hal)
file(GLOB MY_SOURCES "src/*.cpp")

add_library(hal STATIC ${MY_SOURCES})

target_include_directories(hal PUBLIC include)
include_directories(include)
file(GLOB MY_SOURCES "src/*.cpp")
add_executable(myProject ${MY_SOURCES})

# make hal available using hal/
target_link_libraries(myProject LINK_PRIVATE hal pthread)

add_custom_command(TARGET myProject POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "$<TARGET_FILE:myProject>"
     "~/Projects/myApps/beatbox" 
  COMMENT "Copying ARM executable to public NFS directory")
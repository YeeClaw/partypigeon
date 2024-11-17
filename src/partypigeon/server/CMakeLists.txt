# Create the server executable
add_executable(server
    main.c
)

# Link the server with the "wing_protocol" library
target_link_libraries(server wing_protocol)

# Set output directories for this target
set_target_properties(server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)


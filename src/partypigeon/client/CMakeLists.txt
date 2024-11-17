# Create the client executable
add_executable(client
    main.c
)

# Link the client with the "wing_protocol" library
target_link_libraries(client wing_protocol)

# Set output directories for this target
set_target_properties(client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)


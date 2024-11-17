# Create a static library called "wing_protocol"
add_library(wing_protocol STATIC
    wing_protocol.c
)

# Set include paths for the library
target_include_directories(wing_protocol PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Set output directories for this target
set_target_properties(wing_protocol PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)


add_library(projects INTERFACE)

# Agregar un 'add_subdirectory()' por proyecto
add_subdirectory(ui_fft_chart)

target_link_libraries(projects INTERFACE
    # Agregar el nombre de cada proyecto
    ui_fft_chart
)

target_include_directories(projects INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

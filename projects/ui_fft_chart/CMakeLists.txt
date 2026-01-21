add_library(ui_fft_chart STATIC
    ui_fft_chart.c
    test_data.c
    # Agregar otros .c si es necesario
)

target_include_directories(ui_fft_chart PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ui_fft_chart PRIVATE lvgl)

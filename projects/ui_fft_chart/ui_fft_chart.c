#include "lvgl/lvgl.h"

#define FFT_SIZE        2048
#define FFT_BINS        (FFT_SIZE / 2)
#define SAMPLE_RATE     5000        // Hz
#define FFT_Y_MAX       100         // rango visual (0–100)

extern const int32_t fft_bins[1024];

void ui_fft_chart(void) {
    // Transparent wrapper for the chart and the scale
    lv_obj_t *chart_wrapper = lv_obj_create(lv_screen_active());
    lv_obj_remove_style_all(chart_wrapper);
    lv_obj_set_pos(chart_wrapper, 70, 20);
    lv_obj_set_align(chart_wrapper, LV_ALIGN_TOP_LEFT);
    lv_obj_set_size(chart_wrapper, lv_pct(300), 280);
    lv_obj_set_flex_flow(chart_wrapper, LV_FLEX_FLOW_COLUMN);

    // Create chart that scrolls in the wrapper
    lv_obj_t *chart = lv_chart_create(chart_wrapper);
    lv_obj_set_size(chart, lv_pct(100), 280);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_set_point_count(chart, FFT_BINS);
    lv_chart_set_axis_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, FFT_Y_MAX);
    lv_obj_set_style_bg_color(chart, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_width(chart, 0, LV_PART_MAIN);
    lv_obj_set_style_line_width(chart, 1, LV_PART_ITEMS);
    lv_obj_set_style_size(chart, 0, 0, LV_PART_INDICATOR);
    lv_obj_set_style_margin_right(chart, 20, 0);
    // Chart grid
    lv_chart_set_div_line_count(chart, 6, 10);
    lv_obj_set_style_line_color(chart, lv_color_hex(0x303030), LV_PART_MAIN);
    lv_obj_set_style_line_width(chart, 1, LV_PART_MAIN);

    // X scale for frequency
    lv_obj_t *scale_x = lv_scale_create(chart);
    lv_scale_set_mode(scale_x, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
    lv_obj_set_width(scale_x, lv_pct(100));
    lv_scale_set_label_show(scale_x, true);
    // Frequency range
    lv_obj_t *sec_x = lv_scale_add_section(scale_x);
    lv_scale_set_section_range(scale_x, sec_x, 0, SAMPLE_RATE / 2);
    // Tick configuration
    lv_scale_set_total_tick_count(scale_x, 200);
    lv_scale_set_major_tick_every(scale_x, 25);

    // Axis, label and tick styles
    static lv_style_t indicator_style;
    lv_style_init(&indicator_style);
    // Label style properties
    lv_style_set_text_font(&indicator_style, &lv_font_montserrat_10);
    lv_style_set_text_color(&indicator_style, lv_color_white());
    // Major tick properties
    lv_style_set_line_color(&indicator_style, lv_color_white());
    lv_style_set_length(&indicator_style, 8);
    lv_style_set_line_width(&indicator_style, 1);
    lv_obj_add_style(scale_x, &indicator_style, LV_PART_INDICATOR);
    // Minor tick properties
    static lv_style_t minor_ticks_style;
    lv_style_init(&minor_ticks_style);
    lv_style_set_line_color(&minor_ticks_style, lv_color_white());
    lv_style_set_length(&minor_ticks_style, 4);
    lv_style_set_line_width(&minor_ticks_style, 1);
    lv_obj_add_style(scale_x, &minor_ticks_style, LV_PART_ITEMS);
    // Main line properties
    static lv_style_t main_line_style;
    lv_style_init(&main_line_style);
    lv_style_set_line_color(&main_line_style, lv_color_white());
    lv_style_set_line_width(&main_line_style, 1);
    lv_obj_add_style(scale_x, &main_line_style, LV_PART_MAIN);

    // Add FFT data series
    lv_chart_series_t *fft_series = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_series_ext_y_array(chart, fft_series, fft_bins);
    lv_chart_refresh(chart);
}

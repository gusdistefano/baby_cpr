// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: simul_v1.4

#include "../ui.h"

void ui_configuration_screen_init(void)
{
    ui_configuration = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_configuration, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ConfigContainer1 = lv_obj_create(ui_configuration);
    lv_obj_remove_style_all(ui_ConfigContainer1);
    lv_obj_set_width(ui_ConfigContainer1, 320);
    lv_obj_set_height(ui_ConfigContainer1, 240);
    lv_obj_set_x(ui_ConfigContainer1, 2);
    lv_obj_set_y(ui_ConfigContainer1, 0);
    lv_obj_set_align(ui_ConfigContainer1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_ConfigContainer1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Header9 = lv_obj_create(ui_ConfigContainer1);
    lv_obj_set_width(ui_Header9, 309);
    lv_obj_set_height(ui_Header9, 29);
    lv_obj_set_x(ui_Header9, -1);
    lv_obj_set_y(ui_Header9, -105);
    lv_obj_set_align(ui_Header9, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Header9, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_color(ui_Header9, lv_color_hex(0x00BAFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Header9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Header9, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image15 = lv_img_create(ui_Header9);
    lv_img_set_src(ui_Image15, &ui_img_bat_png);
    lv_obj_set_width(ui_Image15, LV_SIZE_CONTENT);   /// 67
    lv_obj_set_height(ui_Image15, LV_SIZE_CONTENT);    /// 19
    lv_obj_set_x(ui_Image15, 120);
    lv_obj_set_y(ui_Image15, 0);
    lv_obj_set_align(ui_Image15, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image15, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image15, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image17 = lv_img_create(ui_Header9);
    lv_img_set_src(ui_Image17, &ui_img_title4_png);
    lv_obj_set_width(ui_Image17, LV_SIZE_CONTENT);   /// 170
    lv_obj_set_height(ui_Image17, LV_SIZE_CONTENT);    /// 14
    lv_obj_set_x(ui_Image17, -88);
    lv_obj_set_y(ui_Image17, 0);
    lv_obj_set_align(ui_Image17, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image17, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image17, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_pSelection = lv_obj_create(ui_ConfigContainer1);
    lv_obj_set_width(ui_pSelection, 275);
    lv_obj_set_height(ui_pSelection, 128);
    lv_obj_set_x(ui_pSelection, 2);
    lv_obj_set_y(ui_pSelection, -12);
    lv_obj_set_align(ui_pSelection, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_pSelection, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_color(ui_pSelection, lv_color_hex(0x00BAFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_pSelection, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_pSelection, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_minDropdown = lv_dropdown_create(ui_pSelection);
    lv_dropdown_set_dir(ui_minDropdown, LV_DIR_RIGHT);
    lv_dropdown_set_options(ui_minDropdown, "1:00\n2:00\n3:00\n4:00\n5:00");
    lv_obj_set_width(ui_minDropdown, 72);
    lv_obj_set_height(ui_minDropdown, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_minDropdown, 16);
    lv_obj_set_y(ui_minDropdown, -20);
    lv_obj_set_align(ui_minDropdown, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_minDropdown, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags



    ui_cpmDropdown = lv_dropdown_create(ui_pSelection);
    lv_dropdown_set_dir(ui_cpmDropdown, LV_DIR_RIGHT);
    lv_dropdown_set_options(ui_cpmDropdown, "100\n110\n120\n");
    lv_obj_set_width(ui_cpmDropdown, 72);
    lv_obj_set_height(ui_cpmDropdown, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_cpmDropdown, 16);
    lv_obj_set_y(ui_cpmDropdown, 23);
    lv_obj_set_align(ui_cpmDropdown, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_cpmDropdown, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags



    ui_Label25 = lv_label_create(ui_pSelection);
    lv_obj_set_width(ui_Label25, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label25, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label25, -59);
    lv_obj_set_y(ui_Label25, -22);
    lv_obj_set_align(ui_Label25, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label25, "Tiempo:");

    ui_Label26 = lv_label_create(ui_pSelection);
    lv_obj_set_width(ui_Label26, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label26, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label26, -49);
    lv_obj_set_y(ui_Label26, 21);
    lv_obj_set_align(ui_Label26, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label26, "CPM:");

    ui_Label13 = lv_label_create(ui_pSelection);
    lv_obj_set_width(ui_Label13, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label13, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label13, 74);
    lv_obj_set_y(ui_Label13, -20);
    lv_obj_set_align(ui_Label13, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label13, "min");
    lv_obj_set_style_text_font(ui_Label13, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_btnBack5 = lv_btn_create(ui_ConfigContainer1);
    lv_obj_set_width(ui_btnBack5, 55);
    lv_obj_set_height(ui_btnBack5, 20);
    lv_obj_set_x(ui_btnBack5, 103);
    lv_obj_set_y(ui_btnBack5, 96);
    lv_obj_set_align(ui_btnBack5, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_btnBack5, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_btnBack5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_btnBack5, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_btnBack5, lv_color_hex(0x4073D0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_btnBack5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label28 = lv_label_create(ui_btnBack5);
    lv_obj_set_width(ui_Label28, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label28, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label28, 6);
    lv_obj_set_y(ui_Label28, -1);
    lv_obj_set_align(ui_Label28, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label28, "Volver");
    lv_obj_set_style_text_color(ui_Label28, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label28, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label28, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image27 = lv_img_create(ui_btnBack5);
    lv_img_set_src(ui_Image27, &ui_img_back_png);
    lv_obj_set_width(ui_Image27, LV_SIZE_CONTENT);   /// 10
    lv_obj_set_height(ui_Image27, LV_SIZE_CONTENT);    /// 7
    lv_obj_set_x(ui_Image27, -18);
    lv_obj_set_y(ui_Image27, -1);
    lv_obj_set_align(ui_Image27, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image27, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image27, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_add_event_cb(ui_btnBack5, ui_event_btnBack5, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_configuration, ui_event_configuration, LV_EVENT_ALL, NULL);

}

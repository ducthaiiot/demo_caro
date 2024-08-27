#include<lvgl.h>

// static void event_handler(lv_event_t * e)
// {
//     lv_event_code_t code = lv_event_get_code(e);
//     lv_obj_t * obj = lv_event_get_target(e);
//     if(code == LV_EVENT_VALUE_CHANGED) {
//         char buf[32];
//         lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
//         LV_LOG_USER("Option: %s", buf);
//     }
// }

// void lv_simple_dropdown(void)
// {

//     /*Create a normal drop down list*/
//     lv_obj_t * dd = lv_dropdown_create(lv_scr_act());
//     lv_dropdown_set_options(dd, "Apple\n"
//                             "Banana\n"
//                             "Orange\n"
//                             "Cherry\n"
//                             "Grape\n"
//                             "Raspberry\n"
//                             "Melon\n"
//                             "Orange\n"
//                             "Lemon\n"
//                             "Nuts");

//     lv_obj_align(dd, LV_ALIGN_CENTER, 0, 20);
//     lv_obj_add_event_cb(dd, event_handler, LV_EVENT_ALL, NULL);
// }

// ------------------

// void lv_four_directions_dropdown(void)
// {
//     static const char * opts = "Apple\n"
//                                "Banana\n"
//                                "Orange\n"
//                                "Melon";

//     lv_obj_t * dd;
//     dd = lv_dropdown_create(lv_scr_act());
//     lv_dropdown_set_options_static(dd, opts);
//     lv_obj_align(dd, LV_ALIGN_TOP_MID, 0, 10);

//     dd = lv_dropdown_create(lv_scr_act());
//     lv_dropdown_set_options_static(dd, opts);
//     lv_dropdown_set_dir(dd, LV_DIR_BOTTOM);
//     lv_dropdown_set_symbol(dd, LV_SYMBOL_UP);
//     lv_obj_align(dd, LV_ALIGN_BOTTOM_MID, 0, -10);

//     dd = lv_dropdown_create(lv_scr_act());
//     lv_dropdown_set_options_static(dd, opts);
//     lv_dropdown_set_dir(dd, LV_DIR_RIGHT);
//     lv_dropdown_set_symbol(dd, LV_SYMBOL_RIGHT);
//     lv_obj_align(dd, LV_ALIGN_LEFT_MID, 10, 0);

//     dd = lv_dropdown_create(lv_scr_act());
//     lv_dropdown_set_options_static(dd, opts);
//     lv_dropdown_set_dir(dd, LV_DIR_LEFT);
//     lv_dropdown_set_symbol(dd, LV_SYMBOL_LEFT);
//     lv_obj_align(dd, LV_ALIGN_RIGHT_MID, -10, 0);
// }

// ------------------

static void event_cb(lv_event_t * e)
{
    lv_obj_t * dropdown = lv_event_get_target(e);
    char buf[64];
    lv_dropdown_get_selected_str(dropdown, buf, sizeof(buf));
    LV_LOG_USER("'%s' is selected", buf);
}

/**
 * Create a menu from a drop-down list and show some drop-down list features and styling
 */
void lv_menu_dropdown(void)
{
    /*Create a drop down list*/
    lv_obj_t * dropdown = lv_dropdown_create(lv_scr_act());
    lv_obj_align(dropdown, LV_ALIGN_CENTER, 20, 20);
    lv_dropdown_set_options(dropdown, "New project\n"
                            "New file\n"
                            "Save\n"
                            "Save as ...\n"
                            "Open project\n"
                            "Recent projects\n"
                            "Preferences\n"
                            "Exit");

    /*Set a fixed text to display on the button of the drop-down list*/
    lv_dropdown_set_text(dropdown, "Menu");

    /*Use a custom image as down icon and flip it when the list is opened*/
    LV_IMG_DECLARE(img_caret_down)
    lv_dropdown_set_symbol(dropdown, &img_caret_down);
    lv_obj_set_style_transform_angle(dropdown, 1800, LV_PART_INDICATOR | LV_STATE_CHECKED);

    /*In a menu we don't need to show the last clicked item*/
    lv_dropdown_set_selected_highlight(dropdown, true);

    lv_obj_add_event_cb(dropdown, event_cb, LV_EVENT_VALUE_CHANGED, NULL);
}
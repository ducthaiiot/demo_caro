#include <lvgl.h>

// void lv_line_wrap_recoloring_and_scrolling_label(void)
// {
//     lv_obj_t * label1 = lv_label_create(lv_scr_act());
//     lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
//     lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
//     lv_label_set_text(label1, "#0000ff Re-color# #ff00ff words# #ff0000 of a# label, align the lines to the center "
//                       "and wrap long text automatically.");
//     lv_obj_set_width(label1, 150);  /*Set smaller width to make the lines wrap*/
//     lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_CENTER, 0);
//     lv_obj_align(label1, LV_ALIGN_CENTER, 0, -40);

//     lv_obj_t * label2 = lv_label_create(lv_scr_act());
//     lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL_CIRCULAR);     /*Circular scroll*/
//     lv_obj_set_width(label2, 150);
//     lv_label_set_text(label2, "It is a circularly scrolling text. ");
//     lv_obj_align(label2, LV_ALIGN_CENTER, 0, 40);
// }

// --------------------

// void lv_text_shadow_label(void)
// {
//     /*Create a style for the shadow*/
//     static lv_style_t style_shadow;
//     lv_style_init(&style_shadow);
//     lv_style_set_text_opa(&style_shadow, LV_OPA_30);
//     lv_style_set_text_color(&style_shadow, lv_color_black());

//     /*Create a label for the shadow first (it's in the background)*/
//     lv_obj_t * shadow_label = lv_label_create(lv_scr_act());
//     lv_obj_add_style(shadow_label, &style_shadow, 0);

//     /*Create the main label*/
//     lv_obj_t * main_label = lv_label_create(lv_scr_act());
//     lv_label_set_recolor(main_label, true);
//     lv_label_set_text(main_label, "#0000ff Nguyen Duc Thai\n"
//                       "#ff00ff Mechanical engineer#.\n"
//                       "20215754\n\n"
//                       "HUST     and spaces.");

//     /*Set the same text for the shadow label*/
//     lv_label_set_text(shadow_label, lv_label_get_text(main_label));

//     /*Position the main label*/
//     lv_obj_align(main_label, LV_ALIGN_CENTER, 0, 0);

//     /*Shift the second label down and to the right by 2 pixel*/
//     lv_obj_align_to(shadow_label, main_label, LV_ALIGN_TOP_LEFT, 2, 2);
// }

// -----------------------

// void lv_show_LTR_RTL_and_chinese_label(void)
// {
//     lv_obj_t * ltr_label = lv_label_create(lv_scr_act());
//     lv_label_set_text(ltr_label, "In modern terminology, a microcontroller is similar to a system on a chip (SoC).");
//     lv_obj_set_style_text_font(ltr_label, &lv_font_montserrat_16, 0);
//     lv_obj_set_width(ltr_label, 310);
//     lv_obj_align(ltr_label, LV_ALIGN_TOP_LEFT, 5, 5);

//     lv_obj_t * rtl_label = lv_label_create(lv_scr_act());
//     lv_label_set_text(rtl_label,
//                       "מעבד, או בשמו המלא יחידת עיבוד מרכזית (באנגלית: CPU - Central Processing Unit).");
//     lv_obj_set_style_base_dir(rtl_label, LV_BASE_DIR_RTL, 0);
//     lv_obj_set_style_text_font(rtl_label, &lv_font_dejavu_16_persian_hebrew, 0);  // turn on lv_font_dejavu_16_persian_hebrew in lv_conf.cpp
//     lv_obj_set_width(rtl_label, 310);
//     lv_obj_align(rtl_label, LV_ALIGN_LEFT_MID, 5, 0);

//     lv_obj_t * cz_label = lv_label_create(lv_scr_act());
//     lv_label_set_text(cz_label,
//                       "嵌入式系统（Embedded System），\n是一种嵌入机械或电气系统内部、具有专一功能和实时计算性能的计算机系统。");
//     lv_obj_set_style_text_font(cz_label, &lv_font_simsun_16_cjk, 0);
//     lv_obj_set_width(cz_label, 310);
//     lv_obj_align(cz_label, LV_ALIGN_BOTTOM_LEFT, 5, -5);
// }

// ----------------

// static void add_mask_event_cb(lv_event_t * e)
// {
//     static lv_draw_mask_map_param_t m;
//     static int16_t mask_id;

//     lv_event_code_t code = lv_event_get_code(e);
//     lv_obj_t * obj = lv_event_get_target(e);

//     // Ensure correct type casting
//     lv_opa_t * lv_map = (lv_opa_t *)lv_event_get_user_data(e);

//     if(code == LV_EVENT_COVER_CHECK) {
//         lv_event_set_cover_res(e, LV_COVER_RES_MASKED);
//     }
//     else if(code == LV_EVENT_DRAW_MAIN_BEGIN) {
//         lv_draw_mask_map_init(&m, &obj->coords, lv_map);
//         mask_id = lv_draw_mask_add(&m, NULL);
//     }
//     else if(code == LV_EVENT_DRAW_MAIN_END) {
//         lv_draw_mask_free_param(&m);
//         lv_draw_mask_remove_id(mask_id);
//     }
// }

// --------------------

// #define MASK_WIDTH 100
// #define MASK_HEIGHT 45

// static void add_mask_event_cb(lv_event_t * e)
// {
//     static lv_draw_mask_map_param_t m;
//     static int16_t mask_id;

//     lv_event_code_t code = lv_event_get_code(e);
//     lv_obj_t * obj = lv_event_get_target(e);
//     lv_opa_t * mask_map = (lv_opa_t *)lv_event_get_user_data(e);
//     if(code == LV_EVENT_COVER_CHECK) {
//         lv_event_set_cover_res(e, LV_COVER_RES_MASKED);
//     }
//     else if(code == LV_EVENT_DRAW_MAIN_BEGIN) {
//         lv_draw_mask_map_init(&m, &obj->coords, mask_map);
//         mask_id = lv_draw_mask_add(&m, NULL);

//     }
//     else if(code == LV_EVENT_DRAW_MAIN_END) {
//         lv_draw_mask_free_param(&m);
//         lv_draw_mask_remove_id(mask_id);
//     }
// }

// /**
//  * Draw label with gradient color
//  */
// void lv_label_with_gradient_color_label(void)
// {
//     /* Create the mask of a text by drawing it to a canvas*/
//     static lv_opa_t mask_map[MASK_WIDTH * MASK_HEIGHT];

//     /*Create a "8 bit alpha" canvas and clear it*/
//     lv_obj_t * canvas = lv_canvas_create(lv_scr_act());
//     lv_canvas_set_buffer(canvas, mask_map, MASK_WIDTH, MASK_HEIGHT, LV_IMG_CF_ALPHA_8BIT);
//     lv_canvas_fill_bg(canvas, lv_color_black(), LV_OPA_TRANSP);

//     /*Draw a label to the canvas. The result "image" will be used as mask*/
//     lv_draw_label_dsc_t label_dsc;
//     lv_draw_label_dsc_init(&label_dsc);
//     label_dsc.color = lv_color_white();
//     label_dsc.align = LV_TEXT_ALIGN_CENTER;
//     lv_canvas_draw_text(canvas, 5, 5, MASK_WIDTH, &label_dsc, "Text with gradient");

//     /*The mask is reads the canvas is not required anymore*/
//     lv_obj_del(canvas);

//     /* Create an object from where the text will be masked out.
//      * Now it's a rectangle with a gradient but it could be an image too*/
//     lv_obj_t * grad = lv_obj_create(lv_scr_act());
//     lv_obj_set_size(grad, MASK_WIDTH, MASK_HEIGHT);
//     lv_obj_center(grad);
//     lv_obj_set_style_bg_color(grad, lv_color_hex(0xff0000), 0);
//     lv_obj_set_style_bg_grad_color(grad, lv_color_hex(0x0000ff), 0);
//     lv_obj_set_style_bg_grad_dir(grad, LV_GRAD_DIR_HOR, 0);
//     lv_obj_add_event_cb(grad, add_mask_event_cb, LV_EVENT_ALL, mask_map);
// }

// ------------------------------

void lv_customize_circular_scrolling_animation_label(void)
{
    static lv_anim_t animation_template;
    static lv_style_t label_style;

    lv_anim_init(&animation_template);
    lv_anim_set_delay(&animation_template, 1000);           /*Wait 1 second to start the first scroll*/
    lv_anim_set_repeat_delay(&animation_template,
                             3000);    /*Repeat the scroll 3 seconds after the label scrolls back to the initial position*/

    /*Initialize the label style with the animation template*/
    lv_style_init(&label_style);
    lv_style_set_anim(&label_style, &animation_template);

    lv_obj_t * label1 = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label1, LV_LABEL_LONG_SCROLL_CIRCULAR);      /*Circular scroll*/
    lv_obj_set_width(label1, 150);
    lv_label_set_text(label1, "It is a circularly scrolling text. ");
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, 40);
    lv_obj_add_style(label1, &label_style, LV_STATE_DEFAULT);           /*Add the style to the label*/
}

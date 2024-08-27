#include<lvgl.h>

// static void event_handler(lv_event_t * e)
// {
//     lv_event_code_t code = lv_event_get_code(e);
//     lv_obj_t * obj = lv_event_get_target(e);
//     if(code == LV_EVENT_VALUE_CHANGED) {
//         uint32_t id = lv_btnmatrix_get_selected_btn(obj);
//         const char * txt = lv_btnmatrix_get_btn_text(obj, id);

//         LV_LOG_USER("%s was pressed\n", txt);
//     }
// }

// static const char * btnm_map[] = {"1", "2", "\n",
//                                   "3", "4", "\n",
//                                   "Action1", "Action2", ""
//                                  };

// void lv_simple_button_matrix(void)
// {
//     lv_obj_t * btnm1 = lv_btnmatrix_create(lv_scr_act());
//     lv_btnmatrix_set_map(btnm1, btnm_map);
//     lv_btnmatrix_set_btn_width(btnm1, 10, 2);        /*Make "Action1" twice as wide as "Action2"*/
//     lv_btnmatrix_set_btn_ctrl(btnm1, 10, LV_BTNMATRIX_CTRL_CHECKABLE);
//     lv_btnmatrix_set_btn_ctrl(btnm1, 11, LV_BTNMATRIX_CTRL_CHECKED);
//     lv_obj_align(btnm1, LV_ALIGN_CENTER, 0, 0);
//     lv_obj_add_event_cb(btnm1, event_handler, LV_EVENT_ALL, NULL);
// }

// ---------------------


// static void event_cb(lv_event_t * e)
// {
//     lv_event_code_t code = lv_event_get_code(e);
//     lv_obj_t * obj = lv_event_get_target(e);
//     if(code == LV_EVENT_DRAW_PART_BEGIN) {
//         lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);

//         /*When the button matrix draws the buttons...*/
//         if(dsc->class_p == &lv_btnmatrix_class && dsc->type == LV_BTNMATRIX_DRAW_PART_BTN) {
//             /*Change the draw descriptor of the 2nd button*/
//             if(dsc->id == 1) {
//                 dsc->rect_dsc->radius = 0;
//                 if(lv_btnmatrix_get_selected_btn(obj) == dsc->id)  dsc->rect_dsc->bg_color = lv_palette_darken(LV_PALETTE_BLUE, 3);
//                 else dsc->rect_dsc->bg_color = lv_palette_main(LV_PALETTE_BLUE);

//                 dsc->rect_dsc->shadow_width = 6;
//                 dsc->rect_dsc->shadow_ofs_x = 3;
//                 dsc->rect_dsc->shadow_ofs_y = 3;
//                 dsc->label_dsc->color = lv_color_white();
//             }
//             /*Change the draw descriptor of the 3rd button*/
//             else if(dsc->id == 2) {
//                 dsc->rect_dsc->radius = LV_RADIUS_CIRCLE;
//                 if(lv_btnmatrix_get_selected_btn(obj) == dsc->id)  dsc->rect_dsc->bg_color = lv_palette_darken(LV_PALETTE_RED, 3);
//                 else dsc->rect_dsc->bg_color = lv_palette_main(LV_PALETTE_RED);

//                 dsc->label_dsc->color = lv_color_white();
//             }
//             else if(dsc->id == 3) {
//                 dsc->label_dsc->opa = LV_OPA_TRANSP; /*Hide the text if any*/

//             }
//         }
//     }
//     if(code == LV_EVENT_DRAW_PART_END) {
//         lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);

//         /*When the button matrix draws the buttons...*/
//         if(dsc->class_p == &lv_btnmatrix_class && dsc->type == LV_BTNMATRIX_DRAW_PART_BTN) {
//             /*Add custom content to the 4th button when the button itself was drawn*/
//             if(dsc->id == 3) {
//                 LV_IMG_DECLARE(img_star);
//                 lv_img_header_t header;
//                 lv_res_t res = lv_img_decoder_get_info(&img_star, &header);
//                 if(res != LV_RES_OK) return;

//                 lv_area_t a;
//                 a.x1 = dsc->draw_area->x1 + (lv_area_get_width(dsc->draw_area) - header.w) / 2;
//                 a.x2 = a.x1 + header.w - 1;
//                 a.y1 = dsc->draw_area->y1 + (lv_area_get_height(dsc->draw_area) - header.h) / 2;
//                 a.y2 = a.y1 + header.h - 1;

//                 lv_draw_img_dsc_t img_draw_dsc;
//                 lv_draw_img_dsc_init(&img_draw_dsc);
//                 img_draw_dsc.recolor = lv_color_black();
//                 if(lv_btnmatrix_get_selected_btn(obj) == dsc->id)  img_draw_dsc.recolor_opa = LV_OPA_30;

//                 lv_draw_img(dsc->draw_ctx, &img_draw_dsc, &a, &img_star);
//             }
//         }
//     }
// }

// /**
//  * Add custom drawer to the button matrix to customize buttons one by one
//  */
// void lv_custom_button_matrix(void)
// {
//     lv_obj_t * btnm = lv_btnmatrix_create(lv_scr_act());
//     lv_obj_add_event_cb(btnm, event_cb, LV_EVENT_ALL, NULL);
//     lv_obj_center(btnm);
// }

// ---------------

// static void event_cb(lv_event_t * e)
// {
//     lv_obj_t * obj = lv_event_get_target(e);
//     uint32_t id = lv_btnmatrix_get_selected_btn(obj);
//     bool prev = id == 0 ? true : false;
//     bool next = id == 6 ? true : false;
//     if(prev || next) {
//         /*Find the checked button*/
//         uint32_t i;
//         for(i = 1; i < 7; i++) {
//             if(lv_btnmatrix_has_btn_ctrl(obj, i, LV_BTNMATRIX_CTRL_CHECKED)) break;
//         }

//         if(prev && i > 1) i--;
//         else if(next && i < 5) i++;

//         lv_btnmatrix_set_btn_ctrl(obj, i, LV_BTNMATRIX_CTRL_CHECKED);
//     }
// }

// /**
//  * Make a button group (pagination)
//  */
// void lv_pagination_button_matrix(void)
// {
//     static lv_style_t style_bg;
//     lv_style_init(&style_bg);
//     lv_style_set_pad_all(&style_bg, 0);
//     lv_style_set_pad_gap(&style_bg, 0);
//     lv_style_set_clip_corner(&style_bg, true);
//     lv_style_set_radius(&style_bg, LV_RADIUS_CIRCLE);
//     lv_style_set_border_width(&style_bg, 0);

//     static lv_style_t style_btn;
//     lv_style_init(&style_btn);
//     lv_style_set_radius(&style_btn, 0);
//     lv_style_set_border_width(&style_btn, 1);
//     lv_style_set_border_opa(&style_btn, LV_OPA_50);
//     lv_style_set_border_color(&style_btn, lv_palette_main(LV_PALETTE_GREY));
//     lv_style_set_border_side(&style_btn, LV_BORDER_SIDE_INTERNAL);
//     lv_style_set_radius(&style_btn, 0);

//     static const char * map[] = {LV_SYMBOL_LEFT, "1", "2", "3", "4", "5", LV_SYMBOL_RIGHT, ""};

//     lv_obj_t * btnm = lv_btnmatrix_create(lv_scr_act());
//     lv_btnmatrix_set_map(btnm, map);
//     lv_obj_add_style(btnm, &style_bg, 0);
//     lv_obj_add_style(btnm, &style_btn, LV_PART_ITEMS);
//     lv_obj_add_event_cb(btnm, event_cb, LV_EVENT_VALUE_CHANGED, NULL);
//     lv_obj_set_size(btnm, 225, 35);

//     /*Allow selecting on one number at time*/
//     lv_btnmatrix_set_btn_ctrl_all(btnm, LV_BTNMATRIX_CTRL_CHECKABLE);
//     lv_btnmatrix_clear_btn_ctrl(btnm, 0, LV_BTNMATRIX_CTRL_CHECKABLE);
//     lv_btnmatrix_clear_btn_ctrl(btnm, 6, LV_BTNMATRIX_CTRL_CHECKABLE);

//     lv_btnmatrix_set_one_checked(btnm, true);
//     lv_btnmatrix_set_btn_ctrl(btnm, 1, LV_BTNMATRIX_CTRL_CHECKED);

//     lv_obj_center(btnm);

// }
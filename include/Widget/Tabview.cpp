#include<lvgl.h>

// void lv_simple_tabview(void)
// {
//     /*Create a Tab view object*/
//     lv_obj_t * tabview;
//     tabview = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 50);

//     /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
//     lv_obj_t * tab1 = lv_tabview_add_tab(tabview, "Tab 1");
//     lv_obj_t * tab2 = lv_tabview_add_tab(tabview, "Tab 2");
//     lv_obj_t * tab3 = lv_tabview_add_tab(tabview, "Tab 3");

//     /*Add content to the tabs*/
//     lv_obj_t * label = lv_label_create(tab1);
//     lv_label_set_text(label, "This the first tab\n\n"
//                       "If the content\n"
//                       "of a tab\n"
//                       "becomes too\n"
//                       "longer\n"
//                       "than the\n"
//                       "container\n"
//                       "then it\n"
//                       "automatically\n"
//                       "becomes\n"
//                       "scrollable.\n"
//                       "\n"
//                       "\n"
//                       "\n"
//                       "Can you see it?");

//     label = lv_label_create(tab2);
//     lv_label_set_text(label, "Second tab");

//     label = lv_label_create(tab3);
//     lv_label_set_text(label, "Third tab");

//     lv_obj_scroll_to_view_recursive(label, LV_ANIM_ON);

// }

// --------------------------

void lv_tabs_on_left_tabview(void)
{
    /*Create a Tab view object*/
    lv_obj_t * tabview;
    tabview = lv_tabview_create(lv_scr_act(), LV_DIR_LEFT, 80);

    lv_obj_set_style_bg_color(tabview, lv_palette_lighten(LV_PALETTE_RED, 2), 0);

    lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tabview);
    lv_obj_set_style_bg_color(tab_btns, lv_palette_darken(LV_PALETTE_GREY, 3), 0);
    lv_obj_set_style_text_color(tab_btns, lv_palette_lighten(LV_PALETTE_GREY, 5), 0);
    lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_RIGHT, LV_PART_ITEMS | LV_STATE_CHECKED);

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t * tab1 = lv_tabview_add_tab(tabview, "Tab 1");
    lv_obj_t * tab2 = lv_tabview_add_tab(tabview, "Tab 2");
    lv_obj_t * tab3 = lv_tabview_add_tab(tabview, "Tab 3");
    lv_obj_t * tab4 = lv_tabview_add_tab(tabview, "Tab 4");
    lv_obj_t * tab5 = lv_tabview_add_tab(tabview, "Tab 5");

    lv_obj_set_style_bg_color(tab2, lv_palette_lighten(LV_PALETTE_AMBER, 3), 0);
    lv_obj_set_style_bg_opa(tab2, LV_OPA_COVER, 0);

    /*Add content to the tabs*/
    lv_obj_t * label = lv_label_create(tab1);
    lv_label_set_text(label, "First tab");

    label = lv_label_create(tab2);
    lv_label_set_text(label, "Second tab");

    label = lv_label_create(tab3);
    lv_label_set_text(label, "Third tab");

    label = lv_label_create(tab4);
    lv_label_set_text(label, "Forth tab");

    label = lv_label_create(tab5);
    lv_label_set_text(label, "Fifth tab");

    lv_obj_clear_flag(lv_tabview_get_content(tabview), LV_OBJ_FLAG_SCROLLABLE);
}
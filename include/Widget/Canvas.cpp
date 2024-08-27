#include<lvgl.h>

// #define CANVAS_WIDTH  200
// #define CANVAS_HEIGHT  150
// void lv_drawing_and_rotate_canvas(void)
// {
//     lv_draw_rect_dsc_t rect_dsc;
//     lv_draw_rect_dsc_init(&rect_dsc);
//     rect_dsc.radius = 10;
//     rect_dsc.bg_opa = LV_OPA_COVER;
//     rect_dsc.bg_grad.dir = LV_GRAD_DIR_HOR;
//     rect_dsc.bg_grad.stops[0].color = lv_palette_main(LV_PALETTE_RED);
//     rect_dsc.bg_grad.stops[1].color = lv_palette_main(LV_PALETTE_BLUE);
//     rect_dsc.border_width = 2;
//     rect_dsc.border_opa = LV_OPA_90;
//     rect_dsc.border_color = lv_color_white();
//     rect_dsc.shadow_width = 5;
//     rect_dsc.shadow_ofs_x = 5;
//     rect_dsc.shadow_ofs_y = 5;

//     lv_draw_label_dsc_t label_dsc;
//     lv_draw_label_dsc_init(&label_dsc);
//     label_dsc.color = lv_palette_main(LV_PALETTE_ORANGE);

//     static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(CANVAS_WIDTH, CANVAS_HEIGHT)];

//     lv_obj_t * canvas = lv_canvas_create(lv_scr_act());
//     lv_canvas_set_buffer(canvas, cbuf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_IMG_CF_TRUE_COLOR);
//     lv_obj_center(canvas);
//     lv_canvas_fill_bg(canvas, lv_palette_lighten(LV_PALETTE_GREY, 3), LV_OPA_COVER);

//     lv_canvas_draw_rect(canvas, 70, 60, 100, 70, &rect_dsc);

//     lv_canvas_draw_text(canvas, 40, 20, 100, &label_dsc, "Some text on text canvas");

//     /*Test the rotation. It requires another buffer where the original image is stored.
//      *So copy the current image to buffer and rotate it to the canvas*/
//     static lv_color_t cbuf_tmp[CANVAS_WIDTH * CANVAS_HEIGHT];
//     memcpy(cbuf_tmp, cbuf, sizeof(cbuf_tmp));
//     lv_img_dsc_t img;
//     img.data = (const void *)cbuf_tmp;
//     img.header.cf = LV_IMG_CF_TRUE_COLOR;
//     img.header.w = CANVAS_WIDTH;
//     img.header.h = CANVAS_HEIGHT;

//     lv_canvas_fill_bg(canvas, lv_palette_lighten(LV_PALETTE_GREY, 3), LV_OPA_COVER);
//     lv_canvas_transform(canvas, &img, 120, LV_IMG_ZOOM_NONE, 0, 0, CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, true);
// }



#define CANVAS_WIDTH  200
#define CANVAS_HEIGHT 150

void lv_drawing_and_rotate_canvas(void)
{
    lv_draw_rect_dsc_t rect_dsc;
    lv_draw_rect_dsc_init(&rect_dsc);
    rect_dsc.radius = 10;
    rect_dsc.bg_opa = LV_OPA_COVER;
    rect_dsc.bg_grad.dir = LV_GRAD_DIR_HOR;
    rect_dsc.bg_grad.stops[0].color = lv_palette_main(LV_PALETTE_RED);
    rect_dsc.bg_grad.stops[1].color = lv_palette_main(LV_PALETTE_BLUE);
    rect_dsc.border_width = 2;
    rect_dsc.border_opa = LV_OPA_90;
    rect_dsc.border_color = lv_color_white();
    rect_dsc.shadow_width = 5;
    rect_dsc.shadow_ofs_x = 5;
    rect_dsc.shadow_ofs_y = 5;

    lv_draw_label_dsc_t label_dsc;
    lv_draw_label_dsc_init(&label_dsc);
    label_dsc.color = lv_palette_main(LV_PALETTE_ORANGE);

    static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(CANVAS_WIDTH, CANVAS_HEIGHT)];

    lv_obj_t * canvas = lv_canvas_create(lv_scr_act());
    lv_canvas_set_buffer(canvas, cbuf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_IMG_CF_TRUE_COLOR);
    lv_obj_center(canvas);
    lv_canvas_fill_bg(canvas, lv_palette_lighten(LV_PALETTE_GREY, 3), LV_OPA_COVER);

    lv_canvas_draw_rect(canvas, 70, 60, 100, 70, &rect_dsc);
    lv_canvas_draw_text(canvas, 40, 20, 100, &label_dsc, "Some text on text canvas");

    // Copy the current canvas content to a temporary buffer
    static lv_color_t cbuf_tmp[LV_CANVAS_BUF_SIZE_TRUE_COLOR(CANVAS_WIDTH, CANVAS_HEIGHT)];
    memcpy(cbuf_tmp, cbuf, sizeof(cbuf_tmp));

    // Define the image descriptor
    lv_img_dsc_t img;
    // img.data =(const void *)cbuf_tmp;  // Cast to const void*
    img.header.cf = LV_IMG_CF_TRUE_COLOR; // Ensure this matches your canvas format
    img.header.w = CANVAS_WIDTH;
    img.header.h = CANVAS_HEIGHT;

    // Clear the canvas
    lv_canvas_fill_bg(canvas, lv_palette_lighten(LV_PALETTE_GREY, 3), LV_OPA_COVER);

    // Rotate the image on the canvas
    // Ensure lv_canvas_transform is available and used correctly for your LVGL version
     lv_canvas_transform(canvas, &img, 120, LV_IMG_ZOOM_NONE, 0, 0, CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, true);
}   

// ------------------

// #define CANVAS_WIDTH  50
// #define CANVAS_HEIGHT  50

// /**
//  * Create a transparent canvas with Chroma keying and indexed color format (palette).
//  */
// void lv_trasparent_canvas(void)
// {
//     /*Create a button to better see the transparency*/
//     lv_btn_create(lv_scr_act());

//     /*Create a buffer for the canvas*/
//     static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_INDEXED_1BIT(CANVAS_WIDTH, CANVAS_HEIGHT)];

//     /*Create a canvas and initialize its palette*/
//     lv_obj_t * canvas = lv_canvas_create(lv_scr_act());
//     lv_canvas_set_buffer(canvas, cbuf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_IMG_CF_INDEXED_1BIT);
//     lv_canvas_set_palette(canvas, 0, LV_COLOR_CHROMA_KEY);
//     lv_canvas_set_palette(canvas, 1, lv_palette_main(LV_PALETTE_RED));

//     /*Create colors with the indices of the palette*/
//     lv_color_t c0;
//     lv_color_t c1;

//     c0.full = 0;
//     c1.full = 1;

//     /*Red background (There is no dedicated alpha channel in indexed images so LV_OPA_COVER is ignored)*/
//     lv_canvas_fill_bg(canvas, c1, LV_OPA_COVER);

//     /*Create hole on the canvas*/
//     uint32_t x;
//     uint32_t y;
//     for(y = 10; y < 30; y++) {
//         for(x = 5; x < 20; x++) {
//             lv_canvas_set_px_color(canvas, x, y, c0);
//         }
//     }

// }






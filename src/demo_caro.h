#include <lvgl.h>

// lv_color_t *buf1 = (lv_color_t *) heap_caps_malloc((480 * 480 * sizeof(lv_color_t)) / 4, MALLOC_CAP_DMA | MALLOC_CAP_SPIRAM);

// lv_color_t *buf2 = (lv_color_t *) heap_caps_malloc((480 * 480 * sizeof(lv_color_t)) / 4, MALLOC_CAP_DMA | MALLOC_CAP_SPIRAM);

#define COLOR_X lv_color_hex(0x0000FF)
#define COLOR_O lv_color_hex(0xFF0000)
char caro_table[24][24];
int line_number = 24;
int column_number = 24;
// lv_obj_t * btn= (lv_obj_t *)heap_caps_malloc((24 * 24 * sizeof(lv_obj_t)) / 4, MALLOC_CAP_DMA | MALLOC_CAP_SPIRAM);
// lv_obj_t * line1 = (lv_obj_t *)heap_caps_malloc((24 * 24 * sizeof(lv_obj_t)) / 4, MALLOC_CAP_DMA | MALLOC_CAP_SPIRAM);
// check all color of rcaro table and fill to caro_table
// void (){
// }

bool turn;

static void check_win();

static void event_cb(lv_event_t * e)
{   
    LV_LOG_USER("Clicked");
    
    char value = 'X';
    lv_obj_t * btn = lv_event_get_target(e);
    int X_position = lv_obj_get_x(btn);
    int Y_position = lv_obj_get_y(btn);
    Serial.printf("Positino of pressed button : X- %d Y- %d \n", X_position, Y_position);
    lv_obj_t * label = lv_obj_get_child(btn, 0);
    
    lv_label_set_text_fmt(label, "X" );
    
    int button_row_index = X_position / 20;
    int button_col_index = Y_position / 20;
    if (caro_table[button_row_index][button_col_index] == ' '){
        if (turn == true){
            // Serial.printf("1");
            lv_obj_set_style_bg_color(btn, lv_color_hex(0x0000FF), 0);
            value = 'O';
            // Serial.printf("2");
            caro_table[button_row_index][button_col_index] = 'O';
            lv_label_set_text_fmt(label, "O" );
            // Serial.printf("3");
            turn = !turn;
        } else {
            // Serial.printf("4");
            lv_obj_set_style_bg_color(btn, lv_color_hex(0xFF0000),0);
            value = 'X';
            // Serial.printf("5");
            caro_table[button_row_index][button_col_index] = 'X';
            lv_label_set_text_fmt(label, "X" );
            // Serial.printf("6");
            turn = !turn;
        }
    }
    else{
        lv_obj_set_style_bg_color(btn, lv_color_hex(0xDDDDDD), 0);
        value = ' ';
        caro_table[button_row_index][button_col_index] = ' ';
        lv_label_set_text_fmt(label, "" );
        turn = !turn;
    }
    // Serial.printf("1");
    check_win();
    
    

}

void demo_caro(void)
{   
    lv_obj_t * caro_scr = lv_obj_create(NULL);
    lv_scr_load(caro_scr);
    lv_obj_update_layout(caro_scr);
    lv_obj_set_size(caro_scr, 480, 480);
    lv_obj_update_layout(caro_scr);
    for(int line_index = 0; line_index < 24; line_index ++){
        for(int column_index = 0; column_index < 24; column_index ++){
            caro_table[line_index][column_index] = ' ';
        }
    }
    int line_number = 24;
    int column_number = 24;
    lv_obj_t * btn[line_number][column_number];
    for(int line_index = 0; line_index < line_number; line_index++){
        for(int column_index = 0; column_index < column_number; column_index++){
            btn[line_index][column_index] = lv_btn_create(caro_scr);
            lv_obj_set_size(btn[line_index][column_index], 20, 20);
            lv_obj_set_pos(btn[line_index][column_index], 20*column_index, 20*line_index);
            lv_obj_add_event_cb(btn[line_index][column_index], event_cb, LV_EVENT_CLICKED, NULL);
            lv_obj_set_style_bg_color(btn[line_index][column_index], lv_color_hex(0xDDDDDD), 0);
            
            lv_obj_t * label = (lv_obj_t *)lv_label_create(btn[line_index][column_index]);
            lv_label_set_text(label, "");
            lv_obj_center(label);

            // lv_timer_handler(); /* let the GUI do its work */
            // delay(1);

        }
    }

}

static void event_cb_close(lv_event_t *e)
{
    lv_obj_t * btn = lv_event_get_target(e);
    lv_obj_t * caro_scr;
    lv_scr_load(caro_scr);
}

static  void event_cb_restart(lv_event_t *e)
{
    lv_obj_t * btn = lv_event_get_target(e);
    lv_obj_t * caro_scr;
    lv_obj_clean(caro_scr);
    demo_caro();

}

static void end_game_red_win(void){
    lv_obj_t * scr1 = lv_obj_create(NULL);
    lv_scr_load(scr1);
    lv_obj_set_size(scr1, 150, 150);
    lv_obj_align(scr1, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t * label_win = lv_label_create(scr1);
    lv_obj_align(label_win, LV_ALIGN_CENTER, 0 ,0);
    lv_label_set_recolor(label_win, true);
    lv_label_set_text(label_win, "#00ff00 CONGRATULATION!#\n#ff0000 Red win#");

    lv_obj_t * close = lv_btn_create(scr1);
    lv_obj_set_size(close, 100, 50);
    lv_obj_align(close, LV_ALIGN_BOTTOM_LEFT, 30,-30);    
    lv_obj_set_style_bg_color(close, lv_color_hex(0xBBBBBB), 0);
    lv_obj_add_event_cb(close, event_cb_close, LV_EVENT_CLICKED, NULL);
    lv_obj_t * close_label = lv_label_create(close);
    lv_obj_set_align(close_label, LV_ALIGN_CENTER);
    lv_label_set_text(close_label, "CLOSE");
    lv_obj_set_style_text_color(close_label, lv_color_hex(0xFFFFFF), 0);


    lv_obj_t * restart = lv_btn_create(scr1);
    lv_obj_set_size(restart, 100, 50);
    lv_obj_align(restart, LV_ALIGN_BOTTOM_RIGHT, -30,-30);    
    lv_obj_set_style_bg_color(restart, lv_color_hex(0xFF0000), 0);
    lv_obj_add_event_cb(restart, event_cb_restart, LV_EVENT_CLICKED, NULL);
    lv_obj_t * restart_label = lv_label_create(restart);
    lv_obj_set_align(restart_label, LV_ALIGN_CENTER);
    lv_label_set_text(restart_label, "RESTART");
    lv_obj_set_style_text_color(restart_label, lv_color_hex(0xFFFFFF), 0);
}

static void end_game_blue_win(void){
    lv_obj_t * scr1 = lv_obj_create(NULL);
    lv_scr_load(scr1);
    lv_obj_set_size(scr1, 150, 150);
    lv_obj_align(scr1, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t * label_win = lv_label_create(scr1);
    lv_obj_align(label_win, LV_ALIGN_CENTER, 0 ,0);
    lv_label_set_recolor(label_win, true);
    lv_label_set_text(label_win, "#00ff00 CONGRATULATION!#\n#0000ff Blue win#");

    lv_obj_t * close = lv_btn_create(scr1);
    lv_obj_set_size(close, 100, 50);
    lv_obj_align(close, LV_ALIGN_BOTTOM_LEFT, 30,-30);    
    lv_obj_set_style_bg_color(close, lv_color_hex(0xBBBBBB), 0);
    lv_obj_add_event_cb(close, event_cb_close, LV_EVENT_CLICKED, NULL);
    lv_obj_t * close_label = lv_label_create(close);
    lv_obj_set_align(close_label, LV_ALIGN_CENTER);
    lv_label_set_text(close_label, "CLOSE");
    lv_obj_set_style_text_color(close_label, lv_color_hex(0xFFFFFF), 0);


    lv_obj_t * restart = lv_btn_create(scr1);
    lv_obj_set_size(restart, 100, 50);
    lv_obj_align(restart, LV_ALIGN_BOTTOM_RIGHT, -30,-30);    
    lv_obj_set_style_bg_color(restart, lv_color_hex(0xFF0000), 0);
    lv_obj_add_event_cb(restart, event_cb_restart, LV_EVENT_CLICKED, NULL);
    lv_obj_t * restart_label = lv_label_create(restart);
    lv_obj_set_align(restart_label, LV_ALIGN_CENTER);
    lv_label_set_text(restart_label, "RESTART");
    lv_obj_set_style_text_color(restart_label, lv_color_hex(0xFFFFFF), 0);
}


static void call_back_red_win(lv_timer_t * timer) {
    end_game_red_win();
    lv_timer_del(timer);  
}

static void call_back_blue_win(lv_timer_t * timer) {
    end_game_blue_win();
    lv_timer_del(timer);  
}

static void create_line(int line_index, int column_index)
{   
    lv_coord_t screen_width = 480;
    lv_coord_t screen_height = 480;
    /*Create an array for the points of the line*/
    static lv_point_t line_points[] = { {line_index*20 + 10, (column_index+1)*20+10},  {line_index*20+10, (column_index+5)*20+10}};

    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 5);
    lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_line_rounded(&style_line, true);

    /*Create a line and apply the new style*/
    lv_obj_t * line1;
    line1 = lv_line_create(lv_scr_act());
    lv_line_set_points(line1, line_points, 2);     /*Set the points*/
    lv_obj_add_style(line1, &style_line, 0);
    // lv_obj_center(line1);
    // lv_task_handler();
    // vTaskDelay(3000/ portTICK_PERIOD_MS);
    // // message_red_win();

    // lv_timer_create(end_game_callback, 1000, NULL);
}

static void column(int line_index, int column_index)
{
    lv_coord_t screen_width = 480;
    lv_coord_t screen_height = 480;
    /*Create an array for the points of the line*/
    static lv_point_t line_points[] = { {(line_index+1)*20 + 10, column_index*20+10},  {(line_index+5)*20+10, column_index*20+10}};

    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 5);
    lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_line_rounded(&style_line, true);

    /*Create a line and apply the new style*/
    lv_obj_t * line1;
    line1 = lv_line_create(lv_scr_act());
    lv_line_set_points(line1, line_points, 2);     /*Set the points*/
    lv_obj_add_style(line1, &style_line, 0);
    // lv_obj_center(line1);

}

static void cross_up(int line_index, int column_index)
{
    lv_coord_t screen_width = 480;
    lv_coord_t screen_height = 480;
    /*Create an array for the points of the line*/
    static lv_point_t line_points[] = { {(line_index+1)*20 + 10, (column_index+1)*20+10},  {(line_index+5)*20+10, (column_index+5)*20+10}};

    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 5);
    lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_line_rounded(&style_line, true);

    /*Create a line and apply the new style*/
    lv_obj_t * line1;
    line1 = lv_line_create(lv_scr_act());
    lv_line_set_points(line1, line_points, 2);     /*Set the points*/
    lv_obj_add_style(line1, &style_line, 0);
    // lv_obj_center(line1);

}

static void cross_down(int line_index, int column_index)
{
    lv_coord_t screen_width = 480;
    lv_coord_t screen_height = 480;
    /*Create an array for the points of the line*/
    static lv_point_t line_points[] = { {(line_index-1)*20 + 10, (column_index+1)*20+10},  {(line_index-5)*20+10, (column_index+5)*20+10}};

    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 5);
    lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_line_rounded(&style_line, true);

    /*Create a line and apply the new style*/
    lv_obj_t * line1;
    line1 = lv_line_create(lv_scr_act());
    lv_line_set_points(line1, line_points, 2);     /*Set the points*/
    lv_obj_add_style(line1, &style_line, 0);
    // lv_obj_center(line1);

}

static void check_win()
{
    for(int line_index = 0; line_index < 24; line_index++){
        for(int column_index = 0; column_index < 24; column_index ++){
            char caro_1 = caro_table[line_index][column_index];
            char caro_2 = caro_table[line_index][column_index+1];
            char caro_3 = caro_table[line_index][column_index+2]; 
            char caro_4 = caro_table[line_index][column_index+3];
            char caro_5 = caro_table[line_index][column_index+4];
            char caro_6 = caro_table[line_index][column_index+5];
            char caro_7 = caro_table[line_index][column_index+6];
            char caro_8 = caro_table[line_index+1][column_index];
            char caro_9 = caro_table[line_index+2][column_index];
            char caro_10 = caro_table[line_index+3][column_index];
            char caro_11 = caro_table[line_index+4][column_index];
            char caro_12 = caro_table[line_index+5][column_index];
            char caro_13 = caro_table[line_index+6][column_index];
            char caro_x1 = caro_table[line_index+1][column_index+1];
            char caro_x2 = caro_table[line_index+2][column_index+2];
            char caro_x3 = caro_table[line_index+3][column_index+3];
            char caro_x4 = caro_table[line_index+4][column_index+4];
            char caro_x5 = caro_table[line_index+5][column_index+5];
            char caro_x6 = caro_table[line_index+6][column_index+6];
            char caro_s1 = caro_table[line_index-1][column_index+1];
            char caro_s2 = caro_table[line_index-2][column_index+2];
            char caro_s3 = caro_table[line_index-3][column_index+3];
            char caro_s4 = caro_table[line_index-4][column_index+4];
            char caro_s5 = caro_table[line_index-5][column_index+5];
            char caro_s6 = caro_table[line_index-6][column_index+6];

            if(caro_1 == 'O' && caro_2 == 'X' && caro_2 == caro_3 && caro_3 == caro_4 && caro_4 == caro_5 && caro_5 == caro_6 && caro_7 != 'O' ){
                create_line(line_index, column_index);
                lv_timer_create(call_back_red_win, 1500, NULL);

            }
            else if(caro_1 == ' ' && caro_2 == 'X' && caro_2 == caro_3 && caro_3 == caro_4 && caro_4 == caro_5 && caro_5 == caro_6 ){
                create_line(line_index, column_index);
                lv_timer_create(call_back_red_win, 1500, NULL);
            } 
            else if (caro_1 == 'X' && caro_2 == 'O' && caro_2 == caro_3 && caro_3 == caro_4 && caro_4 == caro_5 && caro_5 == caro_6 && caro_7 != 'X'){
                create_line(line_index, column_index);
                lv_timer_create(call_back_blue_win, 1500, NULL);
            }
            else if (caro_1 == ' ' && caro_2 == 'O' && caro_2 == caro_3 && caro_3 == caro_4 && caro_4 == caro_5 && caro_5 == caro_6  ){
                create_line(line_index, column_index);
                lv_timer_create(call_back_blue_win, 1500, NULL);
            }
            else if (caro_1 == 'O' && caro_8 == 'X' && caro_8 == caro_9 && caro_9 == caro_10 && caro_10 == caro_11 && caro_11 == caro_12 && caro_13 != 'O' ){
                column(line_index, column_index);  
                lv_timer_create(call_back_red_win, 1500, NULL);          
            }
            else if (caro_1 == ' ' && caro_8 == 'X' && caro_8 == caro_9 && caro_9 == caro_10 && caro_10 == caro_11 && caro_11 == caro_12 ){
                column(line_index, column_index);  
                lv_timer_create(call_back_red_win, 1500, NULL);     
            }
            else if (caro_1 == 'X' && caro_8 == 'O' && caro_8 == caro_9 && caro_9 == caro_10 && caro_10 == caro_11 && caro_11 == caro_12 && caro_13 != 'X'){
                column(line_index, column_index);
                lv_timer_create(call_back_blue_win, 1500, NULL);
            }
            else if (caro_1 == ' ' && caro_8 == 'O' && caro_8 == caro_9 && caro_9 == caro_10 && caro_10 == caro_11 && caro_11 == caro_12){
                column(line_index, column_index);
                lv_timer_create(call_back_blue_win, 1500, NULL);
            }
            else if (caro_1 == 'O' && caro_x1 == 'X' && caro_x1 == caro_x2 && caro_x2 == caro_x3 && caro_x3 == caro_x4 && caro_x4 == caro_x5 && caro_x6 != 'O'){
                cross_up(line_index, column_index);
                lv_timer_create(call_back_red_win, 1500, NULL);
            }
            else if (caro_1 == ' ' && caro_x1 == 'X' && caro_x1 == caro_x2 && caro_x2 == caro_x3 && caro_x3 == caro_x4 && caro_x4 == caro_x5 ){
                cross_up(line_index, column_index);
                lv_timer_create(call_back_red_win, 1500, NULL);
            }
            else if (caro_1 == 'X' && caro_x1 == 'O' && caro_x1 == caro_x2 && caro_x2 == caro_x3 && caro_x3 == caro_x4 && caro_x4 == caro_x5 && caro_x6 != 'X'){
                cross_up(line_index, column_index);
                lv_timer_create(call_back_blue_win, 1500, NULL);
            }
            else if (caro_1 == ' ' && caro_x1 == 'O' && caro_x1 == caro_x2 && caro_x2 == caro_x3 && caro_x3 == caro_x4 && caro_x4 == caro_x5 ){
                cross_up(line_index, column_index);
                lv_timer_create(call_back_blue_win, 1500, NULL);
            }
            else if (caro_1 == 'O' && caro_s1 == 'X' && caro_s1 == caro_s2 && caro_s2 == caro_s3 && caro_s3 == caro_s4 && caro_s4 == caro_s5 && caro_s6 != 'O'){
                cross_down(line_index, column_index);
                lv_timer_create(call_back_red_win, 1500, NULL);
            }      
            else if (caro_1 == ' ' && caro_s1 == 'X' && caro_s1 == caro_s2 && caro_s2 == caro_s3 && caro_s3 == caro_s4 && caro_s4 == caro_s5 ){
                cross_down(line_index, column_index);
                lv_timer_create(call_back_red_win, 1500, NULL);
            }
            else if (caro_1 == 'X' && caro_s1 == 'O' && caro_s1 == caro_s2 && caro_s2 == caro_s3 && caro_s3 == caro_s4 && caro_s4 == caro_s5 && caro_s6 != 'X'){
                cross_down(line_index, column_index);
                lv_timer_create(call_back_blue_win, 1500, NULL);
            }   
            else if (caro_1 == ' ' && caro_s1 == 'O' && caro_s1 == caro_s2 && caro_s2 == caro_s3 && caro_s3 == caro_s4 && caro_s4 == caro_s5 ){
                cross_down(line_index, column_index);
                lv_timer_create(call_back_blue_win, 1500, NULL);
            }
            
        }
    }


    // for(int line_index = 0; line_index < 24; line_index++){
    //     for(int column_index = 0; column_index < 18; column_index ++){

    
}

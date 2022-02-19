#ifndef LCD_SCREEN
#define LCD_SCREEN

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

struct lcdscreen {
    LiquidCrystal_I2C* machine;
    int addr;   // 접근 주소 (0x27 or 0x3F)
    int c;      // column 갯수
    int r;      // row 갯수, 한 줄에 프린트 할 수 있는 최대 길이
    bool is_inited; // 초기화 여부
    char** char_arr; // 문자열 출력 배열
};

// lcd_screen 실행
void lcdscreen_init(struct lcdscreen* _lcd, int _addr, int _c, int _r);

// 초기화 되어있는 지 여부
bool lcdscreen_isinited(struct lcdscreen* _lcd);

// 전체 초기화
bool lcdscreen_fflush(struct lcdscreen* _lcd);

// 특정 라인 초기화
bool lcdscreen_lflush(struct lcdscreen* _lcd, int _removed_c);

// 백라이트 조절
bool lcdscreen_backlight(struct lcdscreen* _lcd, bool _light);

// 새 출력
bool lcdscreen_display(struct lcdscreen* _lcd);

// 해당 위치의 버퍼에 문자열 입력
bool lcdscreen_write_string(struct lcdscreen* _lcd, int _idx, String str);

#endif
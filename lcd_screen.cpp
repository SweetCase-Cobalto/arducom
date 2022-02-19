#include "lcd_screen.h"
#include "Arduino.h"
void
lcdscreen_init(struct lcdscreen* _lcd, int _addr, int _c, int _r)
{
    _lcd->addr = _addr;
    _lcd->c = _c; _lcd->r = _r;
    _lcd->machine = new LiquidCrystal_I2C(_lcd->addr, _lcd->r, _lcd->c);

    // 문자열 배열 초기화
    _lcd->char_arr = new char*[_lcd->c];
    for(int i = 0; i < _lcd->c; i++) _lcd->char_arr[i] = new char[_lcd->r];

    // 머신 초기화
    _lcd->machine->init();

    _lcd->is_inited = true;
    
    // 버퍼 지우기
    lcdscreen_fflush(_lcd);
}

bool
lcdscreen_fflush(struct lcdscreen* _lcd)
{
    if(!lcdscreen_isinited(_lcd)) return false; // must be inited;

    _lcd->machine->clear();
    for(int i = 0; i < _lcd->c; i++)
        for(int j = 0; j < _lcd->r; j++)
            _lcd->char_arr[i][j] = ' ';

    return true;
}

bool
lcdscreen_lflush(struct lcdscreen* _lcd, int _removed_c)
{
    if(!lcdscreen_isinited(_lcd)) return false; // must be inited;
    for(int i = 0; i < _lcd->r; i++)
        _lcd->char_arr[_removed_c][i] = ' ';
    return true;
}

bool
lcdscreen_isinited(struct lcdscreen* _lcd) { return _lcd->is_inited; }

bool
lcdscreen_backlight(struct lcdscreen* _lcd, bool _light)
{

    if(!lcdscreen_isinited(_lcd)) return false; // must be inited;
    if(_light) _lcd->machine->backlight();
    else _lcd->machine->noBacklight();

    return true;
}

bool
lcdscreen_display(struct lcdscreen* _lcd)
{
    if(!lcdscreen_isinited(_lcd)) return false; // must be inited;

    for(int i = 0; i < _lcd->c; i++) {
        for(int j = 0; j < _lcd->r; j++) {
            _lcd->machine->setCursor(j, i);
            _lcd->machine->print(_lcd->char_arr[i][j]);
        }
    }
    return true;
}

bool
lcdscreen_write_string(struct lcdscreen* _lcd, int _idx, String _str)
{
    if(!lcdscreen_isinited(_lcd)) return false; // must be inited;

    // 인덱스 범위 밖
    if(!(0 <= _idx && _idx < _lcd->c)) return false;

    lcdscreen_lflush(_lcd, _idx);
    for(int i = 0; (i < _lcd->r && i < _str.length()); i++) 
        _lcd->char_arr[_idx][i] = _str.charAt(i);

    return true;
}
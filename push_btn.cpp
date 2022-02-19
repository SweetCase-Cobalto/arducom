#include "Arduino.h"
#include "push_btn.h"

void
pushbtn_init(struct pushbtn* _btn, int _pin)
{
    _btn->pin = _pin;
    _btn->is_inited = true;
    _btn->prev_sig = -1;
}

// private function
bool
_get_push_sig(struct pushbtn* _btn)
{
    int r = analogRead(_btn->pin);
    bool sig = false;
    if(r == 0 && _btn->prev_sig == 0) sig = true;
    else sig = false;
    _btn->prev_sig = r;

    return sig;

}

bool pushbtn_push(struct pushbtn* _btn, int _flag)
{
    if(!_btn->is_inited) return false;
    if(_flag == BLOCK) {
        while(1) {
            if(_get_push_sig(_btn)) return true;
            delay(10);
        }
    } else return (_get_push_sig(_btn));
}
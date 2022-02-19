// running by analog;

#define NON_BLOCK   0
#define BLOCK       1

struct pushbtn {
    int pin;
    int prev_sig;
    bool is_inited;
};

void pushbtn_init(struct pushbtn* _btn, int _pin);
bool pushbtn_push(struct pushbtn* _btn, int _flag);
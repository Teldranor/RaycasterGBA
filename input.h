#ifndef INPUT_H
#define INPUT_H

unsigned short __key_curr = 0x0;
unsigned short __key_prev = 0x0;

#define REG_KEYINPUT  (* (volatile unsigned short*) 0x4000130)

#define KEY_A        0x0001
#define KEY_B        0x0002
#define KEY_SELECT   0x0004
#define KEY_START    0x0008
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080
#define KEY_R        0x0100
#define KEY_L        0x0200

#define KEY_MASK     0x03FF

// Polling function
inline void key_poll()
{
    __key_prev= __key_curr;
    __key_curr= ~REG_KEYINPUT & KEY_MASK;
}

// Basic state checks
inline unsigned short key_curr_state() {   return __key_curr;          }
inline unsigned short key_prev_state() {   return __key_prev;          }
inline unsigned short key_is_down(unsigned short key) {   return  __key_curr & key;   }
inline unsigned short key_is_up(unsigned short key) {   return ~__key_curr & key;   }
inline unsigned short key_was_down(unsigned short key) {   return  __key_prev & key;   }
inline unsigned short key_was_up(unsigned short key) {   return ~__key_prev & key;   }
#endif

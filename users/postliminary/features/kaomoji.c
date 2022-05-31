#include "kaomoji.h"

#define ANIMAL_COUNT 9

enum {
    CAT,        // (^=◕ᴥ◕=^)
    BEAR,       // ʕ •ᴥ•ʔ
    DOG,        // ◤◡ᴥ◡◥
    RABBIT,     // ／(･ × ･)＼
    PIG,        // ( ´(00)ˋ )
    BIRD,       // (◉Θ◉)
    FISH,       // <")))><
    SPIDER,     // /╲/\╭( ͡°͡° ͜ʖ ͡°͡°)╮/\╱
    WALRUS,     // (:3 っ)っ
};

bool process_kaomoji(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case UC_ANML:
            if (record->event.pressed) {
                switch (rand() % ANIMAL_COUNT) {
                    case CAT:
                        send_unicode_string("(^=◕ᴥ◕=^)");
                        break;
                    case BEAR:
                        send_unicode_string("ʕ •ᴥ•ʔ");
                        break;
                    case DOG:
                        send_unicode_string("◤◡ᴥ◡◥");
                        break;
                    case RABBIT:
                        send_unicode_string("／(･ × ･)＼");
                        break;
                    case PIG:
                        send_unicode_string("( ´(00)ˋ )");
                        break;
                    case BIRD:
                        send_unicode_string("(◉Θ◉)");
                        break;
                    case FISH:
                        send_unicode_string("<\")))><");
                        break;
                    case SPIDER:
                        send_unicode_string("/╲/\\╭( ͡°͡° ͜ʖ ͡°͡°)╮/\\╱\\");
                        break;
                    case WALRUS:
                        send_unicode_string("(:3 っ)っ");
                        break;
                    default:
                        send_unicode_string("@('.')@");
                        break;
                }
            }
            return true;
        case UC_SHRG:
            if (record->event.pressed) {
                send_unicode_string("¯\\_(ツ)_/¯");
            }
            return true;
        case UC_DISS:
            if (record->event.pressed) {
                send_unicode_string("(ಠ_ಠ)");
            }
            return true;
        case UC_FLIP:
            if (record->event.pressed) {
                send_unicode_string("(╯°□°)╯︵ ┻━┻");
            }
            return true;
        case UC_GIVE:
            if (record->event.pressed) {
                send_unicode_string("༼ つ ◕_◕ ༽つ");
            }
            return true;
        case UC_HNGY:
            if (record->event.pressed) {
                send_unicode_string("(￣﹃￣)");
            }
            return true;
        case UC_JOYF:
            if (record->event.pressed) {
                send_unicode_string("(＾▽＾)");
            }
            return true;
        case UC_KAOK:
            if (record->event.pressed) {
                send_unicode_string("ヾ(´〇`)ﾉ♫•*¨*•.¸¸♪");
            }
            return true;
        case UC_LOVE:
            if (record->event.pressed) {
                send_unicode_string("ლ( ˘ ³˘)ノ♥");
            }
            return true;
        case UC_NRVS:
            if (record->event.pressed) {
                send_unicode_string("(・_・;)");
            }
            return true;
        case UC_SURP:
            if (record->event.pressed) {
                send_unicode_string("w(°ｏ°)w");
            }
            return true;
        default:
            return false; //Process all other keycodes normally
    }
}
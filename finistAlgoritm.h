#include "finistBase.h"

void drive_line(Base &bot, int v, float kp = 0.5, float kd = 5){
    float err_old = 0;
    while (true){
        float err = bot.left_line->get_percent() - bot.right_line->get_percent();
        float upr = err * kp + kd*(err - err_old);
        bot.w2_startSync(v + upr, v - upr);
        err_old = err;
    }
}

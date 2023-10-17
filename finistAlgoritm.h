#include "finistBase.h"


/*  безконечная езда по линии
 *  входные параметры:
 *  bot - объект base
 *  v - скорость проценты(int)
 *  kp - коэф пропорциональности(float)
 *  d - коэфициент диференцирования(float)
 *  */
void drive_line(Base &bot, int v, float kp = 0.5, float kd = 5) {
    float err_old = 0;
    while (true) {
        float err = bot.left_line->get_percent() - bot.right_line->get_percent();
        float upr = err * kp + kd * (err - err_old);
        bot.w2_startSync(v + upr, v - upr);
        err_old = err;
    }
}


/*  езда по линии на время в секундах
 *  входные параметры:
 *  bot - объект base
 *  v - скорость проценты(int)
 *  kp - коэф пропорциональности(float)
 *  d - коэфициент диференцирования(float)
 *  time - время в секундах(float)
 */
void drive_line_time(Base &bot, int v, float kp = 0.5, float kd = 5, float time = 1) {
    float err_old = 0;
    int start = millis();
    while (millis() - start < time * 1000) {
        float err = bot.left_line->get_percent() - bot.right_line->get_percent();
        float upr = err * kp + kd * (err - err_old);
        bot.w2_startSync(v + upr, v - upr);
        err_old = err;
    }
    bot.w2_stop(true);
}


/*  езда по линии на количество перекрестков
 *  входные параметры:
 *  bot - объект base
 *  v - скорость проценты(int)
 *  kp - коэф пропорциональности(float)
 *  d - коэфициент диференцирования(float)
 *  n - количество перекрестков(int)
 */
void drive_line_krest(Base &bot, int v, float kp = 0.5, float kd = 5, int n = 1) {
    float err_old = 0;
    for (int i = 0; i < n; ++i) {
        while (bot.right_line->get_percent() + bot.left_line->get_percent() > 20) {
            float err = bot.left_line->get_percent() - bot.right_line->get_percent();
            float upr = err * kp + kd * (err - err_old);
            bot.w2_startSync(v + upr, v - upr);
            err_old = err;
        }
        drive_line_time(bot, v, kp, kd, 0.2);
    }
    bot.w2_stop(true);
}

/* поворот по времени
 * входные параметры:
 * bot - объект Base
 * napr - направление и тип
 *  "tank_right" - танковый вправо
 *  "tank_left" - танковый влево
 *  "mono_right" - одним мотором вправо
 *  "mono_left" - одним мотором влево
 * v - скорость (int)
 * time - время в секундах (float)
 * stop - тип тороможения (bool)
 */
void turn_time(Base &bot, String napr, int v, float time, bool stop) {
    if (napr == "tank_right")
        bot.w2_startSync(v, -1 * v);
    if (napr == "tank_left")
        bot.w2_startSync(-1 * v, v);
    if (napr == "mono_right")
        bot.left_motor->start(v);
    if (napr == "mono_left")
        bot.right_motor->start(v);
    delay(time * 1000);
    bot.w2_stop(stop);
}

/* поворот по времени
 * входные параметры:
 * bot - объект Base
 * napr - направление и тип
 *  "tank_right" - танковый вправо
 *  "tank_left" - танковый влево
 *  "mono_right" - одним мотором вправо
 *  "mono_left" - одним мотором влево
 * v - скорость (int)
 * stop - тип тороможения (bool)
 */
void turn_line(Base &bot, String napr, int v, bool stop) {
    if (napr == "tank_right")
        bot.w2_startSync(v, -1 * v);
    if (napr == "tank_left")
        bot.w2_startSync(-1 * v, v);
    if (napr == "mono_right")
        bot.left_motor->start(v);
    if (napr == "mono_left")
        bot.right_motor->start(v);
    int data;
    do {
        if (napr == "tank_right" or napr == "mono_right") {
            data = bot.right_line->get_percent();
        } else {
            data = bot.left_line->get_percent();
        }
    } while (data > 25);
    bot.w2_stop(stop);
}



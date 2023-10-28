#include "finistBase.h"
#include "finistStructs.h"

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


/* езда по линии на одном датчике
 * входные параметры:
 * bot - объект Base
 * mode - XY, X -каким датчиком едем, Y - со стороны какого датчика линия:
 *     22,32 только против часовой, 23,33 -только по часовой
 * v - скорость, int
 * time - время float
 * kp, kd - float коэффициенты
 */
void drive_line_1s_time(Base &bot, int mode, int v, float time, float kp, float kd) {
    int sens = mode / 10, pos = mode % 10, err, err_old = 0, start = millis();
    pos = pow(-1, pos);

    if (sens == 2) {
        err = (bot.right_line->get_percent() - bot.grey) * pos;
    } else {
        err = (bot.left_line->get_percent() - bot.grey) * pos;
    }
    do {
        int upr = kp * err + kd * (err - err_old);
        bot.w2_startSync(v - upr, v + upr);
    } while (millis() - start < time * 1000);
    bot.w2_stop(true);
}



/* получение с датчика масства показаний в формате чб.
 * true - черный
 * false - белый
 * bot - Base
 * time - время движения, пока читаем
 */
Array_bool code_read(Base &bot, float time) {
    unsigned long long start = millis();
    Array_bool v;
    bot.w2_start(30);
    do {
        v.v.push_back(bot.right_line <= 50);
    } while (millis() - start < time * 1000);
    bot.w2_stop(true);
    return v;
}

/*членение массива с цветами чб на линии
 * code - массив
 */
Array_line code_depars(Array_bool code) {
    Array_line v;
    bool old = code.v[0];
    unsigned long long count = 0;
    for (int i = 0; i < code.v.size(); ++i) {
        if(old == code.v[i]){
            count += 1;
        }
        else{
            line a;
            a.color = old;
            a.size = count;
            v.v.push_back(a);
            count = 1;
        }
        old = code.v[i];
    }
    return v;
}

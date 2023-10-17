#include <ServoSmooth.h>
/*объект DC мотора.
 * входные параметры:
 * dp1 - номер порта, управляющего направлением (int)
 * dp2 - номер порта, управляющего направлением (int)
 * sp - номер порта, управляющего скоростью (int)
 *
 * пример для l298n:
 * Motor rm(4,5,6);
 *
 * пример для MotorShield
 * Motor rm(4,5);
 *
 *
 * сейчас всё прописано для амперка мотор шилда, чуть позднее напишу для l298n
 *
 * ! обязательно прописать name.setup() в сетап
 */
class Motor {
private:
    int dir_port1, speed_port;
public:
    int k = 1;

    Motor(int dp1, int sp) {
        dir_port1 = dp1;
        speed_port = sp;
    }


    //пинмоды, инвертирование true/false
    void setup(bool invert = false) {
        pinMode(dir_port1, OUTPUT);
        pinMode(speed_port, OUTPUT);
        if (invert) {
            k = -1;
        }
    }


    //запускает мотор со скоростью в диапазоне +-0...+-256
    void start(float speed) {
        speed *= k;
        if (speed >= 0) {
            digitalWrite(dir_port1, HIGH);
        } else {
            digitalWrite(dir_port1, LOW);
        }
        analogWrite(speed_port, int(fabs(speed)));
    }


    //запускает моторы в процентах скорости
    void start_percent(float speed) {
        float v = map(speed, 0, 100, 0, 255);
        this->start(v);
    }

    //остановка. true - жёсткая, false - плавная. на амперка шилде работает через ....
    void stop(bool type) {
        if (type) {
            digitalWrite(dir_port1, HIGH);
        } else {
            digitalWrite(dir_port1, LOW);
        }
        digitalWrite(speed_port, 0);
    }
};

#include "finistSensor.h"
#include "finistMotor.h"


/*обхект Base - конструктор. в него напихиваем датчики, моторы
 * собственные прараметры:
 * диаметр колёс в см (float)
 * ширина колеи в см (float)
 *
 * методы:
 * setup_lineSensors
 * setup_encoders
 * setup_motors
 *
 * инструкции к методам в аннотации методов
 */
class Base {
public:
    float d, b;

    LineSensor *left_line;
    LineSensor *right_line;
    Encoder *right_encoder;
    Encoder *left_encoder;
    Motor *right_motor;
    Motor *left_motor;

    Base(float wheel_diameter, float distance_between_wheels) {
        d = wheel_diameter;
        b = distance_between_wheels;
    }


    /*добаваляем пару сенсоров для езды по линии
     * left - объект(LineSensor) левого датчика линии
     * right - объект(LineSensor) правого датчика линии
     */
    void setup_lineSensors(LineSensor &left, LineSensor &right) {
        this->right_line = &right;
        this->left_line = &left;
    }


    /*добаваляем пару энкодеров
     * left - объект(Encoder) левого энкодера
     * right - объект(Encoder) правого энкодера
     */
    void setup_encoders(Encoder *left, Encoder *right) {
        this->right_encoder = right;
        this->left_encoder = left;
    }


    /*добаваляем пару двигателей
     * left - объект(Motor) левого двигателя
     * right - объект(Motor) правого двигателя
     */
    void setup_motors(Motor &left, Motor &right){
        this->right_motor = &right;
        this->left_motor = &left;
    }

    //запускает два мотора с одинаковой скоростью в процентах
    void w2_start(int speed){
        left_motor->start_percent(speed);
        right_motor->start_percent(speed);
    }

    void w2_startSync(int speed_left, int speed_right){
        left_motor->start_percent(speed_left);
        right_motor->start_percent(speed_right);
    }
};

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
 * сейчас всё прописано для амперка мотор шилда, чуть позднее напишу для l298n
 */
class Motor{
private:
    int dir_port1, speed_port;
public:
    Motor(int dp1, int sp){
        dir_port1 = dp1;
        speed_port = sp;
        pinMode(dir_port1, OUTPUT);
        pinMode(speed_port, OUTPUT);
    }


    //запускает мотор со скоростью в диапазоне +-0...+-256
    void start(int speed){
        if(speed >= 0){
            digitalWrite(dir_port1, HIGH);
        }
        else{
            digitalWrite(dir_port1, LOW);
        }
        digitalWrite(speed_port, abs(speed));
    }


    //запускает моторы в процентах скорости
    void start_percent(int speed){
        this->start(speed/100*256);
    }

    //остановка. true - жёсткая, false - плавная. на амперка шилде работает через ....
    void stop(bool type){
        if(type){
            digitalWrite(dir_port1, HIGH);
        }
        else{
            digitalWrite(dir_port1, LOW);
        }
        digitalWrite(speed_port, 0);
    }
};

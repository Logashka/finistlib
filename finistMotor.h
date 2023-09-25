/*объект DC мотора.
 * входные параметры:
 * dp1 - номер порта, управляющего направлением (int)
 * dp2 - номер порта, управляющего направлением (int)
 * sp - номер порта, управляющего скоростью (int)
 *
 * если используется не драйвер, а амперка шилд, то dp2 = -1
 * если на пине скорости на драйвере стоит перемычка, sp не указывать
 *
 * !!! sp - именованный аргумент
 *
 * пример:
 * Motor rm(4,5,sp=6);
 */
class Motor{
private:
    int dir_port1, dir_port2, speed_port;
public:
    Motor(int dp1, int dp2, int sp = -1){
        dir_port1 = dp1;
        dir_port2 = dp2;
        speed_port = sp;
        pinMode(dir_port1, OUTPUT);
        pinMode(dir_port2, OUTPUT);
        pinMode(speed_port, OUTPUT);
    }

    void move(){
        //TODO: all...
    }

};

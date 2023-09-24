
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


/*объект аналогового датчика освещённости
 * входным параметром порт int, аналоговый
 * get_raw возвращает int, необработанное значение 0 - 1024
 * get_percent возвращает float, значение в процентах (0 - 100)
*/
class LineSensor {
public:
    int s_port;

    LineSensor(int i_port) {
        s_port = i_port;
        pinMode(s_port, INPUT);
    }

    int get_raw() {
        return analogRead(s_port);
    }

    float get_percent() {
        return analogRead(s_port) / 1024 * 100;
    }
};


/* Объект энкодер
 * входные параметры:
 * * e_a - первый провод на направление вращения (int),  e_b - второй провод на направдение вращения (int),
 * * e_i - провод на счётчик/интрапт (int), на уно всего ДВА(!): 2 и 3
 * * все порты цифровые
 * turnover еобходимо указать количество тиков на оборот, если надо пересчитывать в градусы
 * значение храниться в count. достать: "object_name".count .
 * в count количество ТИКОВ(!!)
 * get_deg() - вернёт абсолютное значение градусов(float).
 * чтобы обнулить - обнулите count
 *
 *
 * реализовано через костыль, спасибо Никите
 *
 * example:

 * #include "finistSensor.h"
 * Encoder* left_encoder;

 * void setup() { 
 *  left_encoder = new Encoder(4,5,2);
 *  left_encoder->setup([]{left_encoder->EncoderEvent();});
 *}
*/
class Encoder {
public:
    int count = 0, turn;
    int RH_ENCODER_A, RH_ENCODER_B, RH_ENCODER_I;

    void EncoderEvent() {
        if (digitalRead(RH_ENCODER_A) == HIGH) {
            if (digitalRead(RH_ENCODER_B) == LOW) {
                count++;
            } else {
                count--;
            }
        } else {
            if (digitalRead(RH_ENCODER_B) == LOW) {
                count--;
            } else {
                count++;
            }
        }
    }
    void setup(void (*callback)(void)) {
      attachInterrupt(RH_ENCODER_I, callback, CHANGE);// задаем системные прерывания для енкодеров
    }


    Encoder(int e_a, int e_b, int e_i, int turnover = 0) {
        RH_ENCODER_A = e_a;
        RH_ENCODER_B = e_b;
        RH_ENCODER_I = e_i;
        turn = turnover;
        pinMode(RH_ENCODER_A, INPUT);// прописываем режим работы пинов енкодеров
        pinMode(RH_ENCODER_B, INPUT);// прописываем режим работы пинов енкодеров
    }

    //возвращает абсолютное значение градусов(float)
    float get_deg(){
        return map(count,-1 * turn, turn,-360,360);
    }
};

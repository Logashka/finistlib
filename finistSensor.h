
/*объект аналогового датчика освещённости
 * входным параметром порт int, аналоговый
 * get_raw возвращает int, необработанное значение 0 - 1024
 * get_percent возвращает float, значение в процентах (0 - 100)
*/
class LineSensor {
private:
    int s_port;
public:
    int min = 0, max = 1024;


//конструктор int i_port - номер порта.
    LineSensor(int i_port) {
        s_port = i_port;
    }


//пинмоды
    void setup() {
        pinMode(s_port, INPUT);
    }


//ручная калибровка значений для рассчёта процентов
    void calibration(int i_min, int i_max) {
        min = i_min;
        max = i_max;
    }


//автоматическое выявление максимума и минимума. входной пораметр - длительность в секундах (int)
    void auto_calibration(int time) {
        min = 1024;
        max = 0;
        int start = millis();
        while (millis() - start < time * 1000) {
            int data = this->get_percent();
            if (data < min) {
                min = data;
            }
            if (data > max) {
                max = data;
            }
        }
    }


//получение не обработанного значения с датчика
    int get_raw() {
        return analogRead(s_port);
    }


//получение значения с датчика в процентах
    float get_percent() {
        int a = 1024 - this->get_raw();
        return map(a, min, max, 0, 100);
    }
};


/* Объект энкодер для трехпинового энкодера
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
private:
    int RH_ENCODER_A, RH_ENCODER_B, RH_ENCODER_I, turn;
public:
    int count = 0;

//событие на прерывание. НЕ трогать
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
        pinMode(RH_ENCODER_A, INPUT);// прописываем режим работы пинов енкодеров
        pinMode(RH_ENCODER_B, INPUT);// прописываем режим работы пинов енкодеров
    }


    Encoder(int e_a, int e_b, int e_i, int turnover = 0) {
        RH_ENCODER_A = e_a;
        RH_ENCODER_B = e_b;
        RH_ENCODER_I = e_i;
        turn = turnover;
    }


//возвращает абсолютное значение градусов(float)
    float get_deg() {
        return map(count, -1 * turn, turn, -360, 360);
    }
};


/* объект ИК датчика расстояния Sharp
 *
 * get_raw() - вернёт необработанное значение
 * get_distance() - вернёт расстояние до объекта в мм
 *
 * пересчитывает в расстояние изходя из формулы функции, выведенной по графику зависимости
 * напряжения от расстояния из документации
 *
 */
class Sharp{
private:
    int pin;
public:
    Sharp(int s_pin){
        pin = s_pin;
    }


    //устанавливает режим работы пина
    void setup(){
        pinMode(pin, INPUT);
    }

    //вернёт необработанное значение с датчика
    int get_raw(){
        return analogRead(pin);
    }

    //вернёт расстояние до объекта (40 - 300мм)
    float get_distance(){
        float v = (analogRead(pin) / 1024.0) * 5.0; // вычисление напряжения на порте
        float dist = 65 * pow(v, -1.10); // 65 и -1.10 - экспериментально выевленные коэффициенты зависимости вида y = k*x^l
        return dist / 10;
    }

};

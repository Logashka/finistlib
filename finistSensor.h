
class LineSensor
{
public:
  int s_port;
  LineSensor(int i_port){
    s_port = i_port;
  }

  int get_raw(){
    return analogRead(s_port);
  }

  float get_percent(){
    return analogRead(s_port) / 1024 * 100;
  }
};
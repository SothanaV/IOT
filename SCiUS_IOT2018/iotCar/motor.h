/*
 * IN1 : D1
 * IN2 : D2
 * IN3 : D3
 * IN4 : D4
*/
class Motor {
  public: void init(){
    pinMode(pin[1],OUTPUT);
    pinMode(pin[2],OUTPUT);
    pinMode(pin[3],OUTPUT);
    pinMode(pin[4],OUTPUT);
    stop();
  }
  public: void stop(){
    digitalWrite(pin[1],0);
    digitalWrite(pin[2],0);
    digitalWrite(pin[3],0);
    digitalWrite(pin[4],0);
  }
  public: void forward(int Delay){
    stop();
    digitalWrite(pin[2],1);
    digitalWrite(pin[4],1);
    delay(Delay);
    stop();
  }
  public: void backward(int Delay){
    stop();
    digitalWrite(pin[1],1);
    digitalWrite(pin[3],1);
    delay(Delay);
    stop();
  }
  public: void left(int Delay){
    stop();
    digitalWrite(pin[2],1);
    delay(Delay);
    stop();
  }
  public: void right(int Delay){
    stop();
    digitalWrite(pin[4],1);
    delay(Delay);
    stop();
  }
};

Motor motor;


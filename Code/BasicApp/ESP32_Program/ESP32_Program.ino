
const int LED_PIN = 48;

void setup(){

  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop(){

  if(Serial.available()){

    char r = Serial.read();
    if(r == '1') digitalWrite(LED_PIN, HIGH);
    else if(r == '0') digitalWrite(LED_PIN, LOW);

  }


}
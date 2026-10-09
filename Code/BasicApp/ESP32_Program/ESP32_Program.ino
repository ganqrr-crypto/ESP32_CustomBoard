void setup(){

  Serial.begin(115200);

}

void loop(){

  if(Serial.available()){

    char r = Serial.read();
    if(r == '1') neopixelWrite(48, 0, 40, 0);
    else if(r == '0')neopixelWrite(48, 0, 0, 0);

  }


}
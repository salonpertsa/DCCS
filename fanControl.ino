void fanControl() {

  tempData = analogRead(tempPin);
  U_t = 5.0*tempData/1023;
  
  //Here we need to configurate and calibrate the coolant temperature sensor to get valid temp readings. 
  //temp = xx
  
  /*if (millis() >= tSerialBegin+serialDur) {
    //Serial.print(F("Temp = "));
    //Serial.println(temp); Serial.println();
    
    tSerialBegin = millis(); //Reset the print interval timer
  }*/

  if(temp >= triggerTemp) {
    digitalWrite(fanPin, HIGH);
  }

  if(temp <= offTemp) {
    digitalWrite(fanPin, LOW);
  }
}

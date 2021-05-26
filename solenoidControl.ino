void solenoidControl() {
  int m;
  EEPROM_readAnything(100, m);
  
  if (PWMval<0) PWMval = 0;
  val = PWMval*2.55;
  myPID.Compute();

  if(m==1) analogWrite(solenoidPin, val);
  else if(m == 0) analogWrite(solenoidPin, val2);
  

  
  if (millis() >= tSerialBegin+serialDur) {
    //Serial.print(F("Temp = "));
    //Serial.println(temp); Serial.println();
    /*Serial.print(F("overP="));
    Serial.println(overP);
    Serial.print(F("val="));
    Serial.println(val);
    Serial.println();*/

  //Serial prints for Excel plotting
    Serial.print(overP); 
    Serial.print(","); 
    Serial.print(val); 
    Serial.print(","); 
    Serial.println();

    tSerialBegin = millis(); //Reset the print interval timer
  }
}

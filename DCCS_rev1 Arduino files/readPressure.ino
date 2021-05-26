/*This function reads the pressure value from the map sensor, saves it to a global variable
 * and prints it on the OLED display.
 */

void readPressure() {
  
  mapData = analogRead(mapPin);
  
  U_m = 5.0*mapData/1023;

  /* Remapping a value range to another and maintaining the ratio:
   * 
   * OldRange = (OldMax - OldMin)  
   * NewRange = (NewMax - NewMin)
   * NewValue = (((OldValue - OldMin) * NewRange) / OldRange) + NewMin
   * NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin
   * 
   * OldMin = 0.3 V
   * OldMax = 4.9 V
   * NewMin = 0.2 bar
   * NewMax = 3.0 bar
   */
   float oldMin = 0.3, oldMax = 4.9, newMin = 0.2, newMax = 3.0;
  

  //absP = 2.80 * U/5.0 + 0.2;
  absP = (((U_m - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
  
  float oledP;
  
  overP = absP-atmosphericP; //Absolute pressure to overpressure
  
  if (Pcounter < 10){
    aveP += overP;
    Pcounter++;
  }
  else {
    aveP /= Pcounter+1;
    if (aveP>maxBoost) maxBoost = aveP;
    pidP = aveP*multiplier;
    oledP = aveP;
    aveP, Pcounter = 0;
  }
  
    /*Serial.print(F("overP="));
    Serial.println(overP);
    Serial.print(F("aveP="));
    Serial.println(aveP);
    Serial.print(F("Pcounter="));
    Serial.println(Pcounter);
    Serial.print(F("pidP="));
    Serial.println(pidP);
    Serial.print(F("val="));
    Serial.println(val);
    Serial.print(F("millis="));
    Serial.println(millis());
    
    Serial.println();
    Serial.println();*/
  
  if (millis() >= tOLEDBegin+OLEDdur){
    
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(4); 
    display.print(oledP);
    display.display();
    
    //pidP = overP*multiplier;
    /*Serial.println(overP);
    Serial.print(F("val="));
    Serial.println(val);
    Serial.println();
    //Serial.println(absP);*/
    
    tOLEDBegin = millis();
  }

  if(clickd==1){
    //lcd.clear();
    //if (millis() >= tMaxBoostBegin+maxBoostDur){
      lcd.clear();
      lcd.print(F("Max Boost ="));
      lcd.setCursor(0,1);
      lcd.print(maxBoost);
      lcd.setCursor(5,1);
      lcd.print(F("bar "));
      //pushed=1;
      //tMaxBoostBegin = millis();
      delay(3000);
      clickd=!clickd;
  //}
  }
  
}

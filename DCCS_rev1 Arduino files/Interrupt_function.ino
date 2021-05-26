void A_interrupt() {
  clkState = digitalRead(clkPin); 
  dtState  = digitalRead(dtPin);
  
  if (clkState != lastState){     
     // If the data state is different to the clock state, the encoder is rotating clockwise
     if (dtState != clkState) { 
       counter ++;
       
     }
     else {
       counter --;
     } 
   } 
   //stepCounter=counter/5;
   lastState = clkState; // Updates the previous state of the data with the current state
  
}

void B_interrupt() {
  //pushed = !pushed;
  button.tick();
}

void dclick() {
  clickd = !clickd;
  //delay(2);
  //lcd.clear();
}

/*void longPress(){
  //if(menu = 0){
  lcdOff = !lcdOff;

  if(lcdOff = 0) lcd.noBacklight();
  else lcd.backlight();
  //}
}*/

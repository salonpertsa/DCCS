void dark_menu(){

  lcd.noBacklight();
  menu, page = 0;
  
  if(counter<0) counter=0;
  if(counter>100) counter=100;
  
  if(digitalRead(swPin)==0){
    EEPROM_readAnything(100, pwmMenu);
    mode = pwmMenu;
    //page = 0;
    lcd.backlight();
    counter = PWMval;
    Print=0; //When pushed is 0 the program returns to printing      
    delay(500);
  }
}

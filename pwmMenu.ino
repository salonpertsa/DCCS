void pwm_menu() 
{
  if((lastCounter > counter) || (lastCounter < counter)  || Print==0)
  { //Only print on the LCD when a step is detected or the button is pushed.
    
  if(menu == 0) 
  {
    //if(0<=counter && counter<101){
      
    //lcd.backlight();
    PWMval=counter;
        
    lcd.clear();
    lcd.print(F("Duty Cycle ="));
    lcd.setCursor(0,1);
    lcd.print(PWMval);
    lcd.setCursor(3,1);
    lcd.print(F("%"));
    Print=1;
    //}
    
    /*if(-10>counter && counter>=-20){
      lcd.noBacklight();
    }*/
      
    
  }

  else if(menu == 1)
  { 
  
    if(0<=counter && counter<5)
    {
        
      lcd.clear();
      lcd.print(F(">Back"));
      lcd.setCursor(0,1);
      lcd.print(F(" Switch mode"));
       
      page=0;
      Print=1;
    }
    
      if(5<=counter && counter<10)
      {
        
        lcd.clear();
        lcd.print(F(">Switch mode"));
        lcd.setCursor(0,1);
        lcd.print(F(" Set Default PWM"));
        
        page=1;
        Print=1; 
      }

      if(10<=counter && counter<15)
      {
        lcd.clear();
        lcd.print(F(">Set Default PWM"));
        
        page=2;
        Print=1; 
      }

  }//menu = 1

  else if(menu == 2){

    if(0<=counter && counter<5){
      lcd.clear();
      lcd.print(F("Mode:"));
      lcd.setCursor(0,1);
      lcd.print(F(">Closed loop"));
      //mode = 0;
      pwmMenu = 0;
      page=0;
      Print=1;
    }

    if(5<=counter && counter<10){
      lcd.clear();
      lcd.print(F("Mode:"));
      lcd.setCursor(0,1);
      lcd.print(F(">Open loop"));
      //mode = 1;
      pwmMenu = 1;
      page=0;
      Print=1;
    }

    if(10<=counter && counter<15){
      lcd.clear();
      lcd.print(F("Mode:"));
      lcd.setCursor(0,1);
      lcd.print(F(">LCD off"));
      //mode = 2;
      pwmMenu = 2;
      page=0;
      Print=1;
    }
  } //End of menu=2
  
  else if(menu == 3)
  {  
        PWMval=counter;
        //PWMval/=5;
        //PWMval*=5;
        lcd.clear();
        lcd.print(F("Default PWM ="));
        lcd.setCursor(0,1);
        lcd.print(PWMval);
        lcd.setCursor(3,1);
        lcd.print(F("%"));
        page=0;
        Print=1;
      }//menu = 3;
  }
  
  lastCounter = counter; //Save the value of the last state

  if(digitalRead(swPin)==0) 
  {
    
    if(menu == 0) //From info screen to menu
    {
      
      menu = 1;
      counter = 0;
      //counter = val/2.55;
      Print = 0;
      delay(650);
      
      
            
     }

    else if(menu == 1) //Main menu
    {
        
      if(page==0) //Back to info screen
      {
        menu=0; 
        //counter=0;
        //counter = val/2.55;
        counter = PWMval;
        Print=0; //When pushed is 0 the program returns to printing      
        delay(500);
      }
      
      if(page==1) //Switch mode
      {
        //pwmMenu = !pwmMenu;
        //EEPROM_writeAnything(100, pwmMenu);
        //EEPROM_readAnything(100, pwmMenu);
        menu=2;
        counter = 0;
        Print=0;
        delay(500);
        
      }
      if(page==2) //PWM set
      {
        menu=3;
        //counter=0;
        Print=0;
        EEPROM_readAnything(20, PWMval);
        counter=PWMval;
        delay(500);
      }

    }

    else if(menu == 2) //Switch mode
      {
        menu=0;
        mode = pwmMenu;
        if(pwmMenu<2) EEPROM_writeAnything(100, pwmMenu);
        
        counter = PWMval;
        Print=0;
        delay(500);
        lcd.clear();
        lcd.print(F("Chosen mode:"));
        lcd.setCursor(0,1);
        lcd.print(mode);
        /*if(mode=0) lcd.print(F("Closed loop"));
        else if(mode=1) lcd.print(F("Open loop"));
        else if(mode=2) lcd.print(F("LCD off"));*/
        delay(1500);
        
      }
    else if(menu == 3)
    {    
      menu=1;
      counter=0;
      Print=0;
      //EEPROM write here
      EEPROM_writeAnything(20, PWMval);
      delay(500);
      lcd.clear();
      lcd.print(F("Default PWM"));
      lcd.setCursor(0,1);
      lcd.print(F("saved"));
      delay(1500);
       
    }

  }//End of Button read 

  //Counter limits
  
  
  //if(menu == 0 && counter < -20) counter=-20;
  //if(menu != 0 && counter < 0) counter=0;
  
  if(counter < 0) counter=0;
  
  if(menu == 0 && counter > 100) counter=100;

  if(menu == 1 && counter > 15) counter=15;

  if(menu == 2 && counter > 15) counter=15;
  
  if(menu == 3 && counter > 100) counter=100; //Default pulse width %

  //return 0;

} //End of pwmMenu

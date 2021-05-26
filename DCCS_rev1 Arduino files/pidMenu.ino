void pid_menu(){

if((lastCounter > counter) || (lastCounter < counter)  || Print==0)
{ //Only print on the LCD when a step is detected or the button is pushed.
  
  if(menu == 0) 
  {
    lcd.clear();
    lcd.print(F("PID active")); 
    lcd.setCursor(0,1);  
    lcd.print(F("Target = "));
    lcd.setCursor(9,1);  
    lcd.print(boostTarget);
    lcd.setCursor(13,1);  
    lcd.print("bar");
    Print=1;
  }

  else if(menu == 1) //First page of the menu
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
        lcd.print(F(" Set BoostTarget"));
        
        page=1;
        Print=1; 
      }

      if(10<=counter && counter<15)
      {
        lcd.clear();
        lcd.print(F(">Set BoostTarget"));
        lcd.setCursor(0,1);
        lcd.print(F(" Set Kp"));
        
        page=2;
        Print=1; 
      }

      if(15<=counter && counter<20)
      {
        lcd.clear();
        lcd.print(F(">Set Kp"));
        lcd.setCursor(0,1);
        lcd.print(F(" Set Ki"));
        
        page=3;
        Print=1; 
      }

      if(20<=counter && counter<25)
      {
        lcd.clear();
        lcd.print(F(">Set Ki"));
        lcd.setCursor(0,1);
        lcd.print(F(" Set Kd"));
        
        page=4;
        Print=1; 
      }

      if(25<=counter && counter<30)
      {
        lcd.clear();
        lcd.print(F(">Set Kd"));
        lcd.setCursor(0,1);
        lcd.print(F(" Set lowLimit"));
        
        
        page=5;
        Print=1; 
      }

      if(30<=counter && counter<35)
      {
        lcd.clear();
        lcd.print(F(">Set lowLimit"));
        lcd.setCursor(0,1);
        lcd.print(F(" Set highLimit"));
        
        page=6;
        Print=1; 
      }

      if(35<=counter && counter<40)
      {
        lcd.clear();
        lcd.print(F(">Set highLimit"));
        //lcd.setCursor(0,1);
        //lcd.print(F(" Switch to "));
        
        page=7;
        Print=1; 
      }


      
  }//menu = 1;

  else if(menu == 2){

    if(0<=counter && counter<5){
      lcd.clear();
      lcd.print(F("Mode:"));
      lcd.setCursor(0,1);
      lcd.print(F(">Closed Loop"));
      //mode = 0;
      pwmMenu = 0;
      page=0;
      Print=1;
    }

    if(5<=counter && counter<10){
      lcd.clear();
      lcd.print(F("Mode:"));
      lcd.setCursor(0,1);
      lcd.print(F(">Open Loop"));
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
        double decimal = counter;
        decimal /= 100;
        boostTarget=decimal*5;
        lcd.clear();
        lcd.print(F("Boost Target = "));
        lcd.setCursor(0,1);
        lcd.print(boostTarget);
        lcd.setCursor(5,1);
        lcd.print(F("bar"));
        page=0;
        Print=1; 
      }

    else if(menu == 4)
      {
        double decimal = counter;
        decimal /= 100;
        Kp=decimal*5;
        lcd.clear();
        lcd.print(F("Kp = "));
        lcd.setCursor(5,0);
        lcd.print(Kp);
        page=0;
        Print=1; 
      }


    else if(menu == 5)
      {
        double decimal = counter;
        decimal /= 100;
        Ki=decimal*5;
        lcd.clear();
        lcd.print(F("Ki = "));
        lcd.setCursor(5,0);
        lcd.print(Ki);
        page=0;
        Print=1; 
      }


    else if(menu == 6)
      {
        double decimal = counter;
        decimal /= 100;
        Kd=decimal*5;
        lcd.clear();
        lcd.print(F("Kd = "));
        lcd.setCursor(5,0);
        lcd.print(Kd);
        page=0;
        Print=1; 
      }

      else if(menu == 7)
      {
        lowLimit = counter;
        lcd.clear();
        lcd.print(F("lowLimit = "));
        lcd.setCursor(0,1);
        lcd.print(lowLimit);
        lcd.setCursor(6,1);
        lcd.print(F("="));
        lcd.setCursor(8,1);
        lcd.print(lowLimit/2.55);
        lcd.setCursor(13,1);
        lcd.print(F("%"));
        page=0;
        Print=1; 
      }

      else if(menu == 8)
      {
        highLimit = counter;
        highLimit /=5;
        highLimit *=5;
        lcd.clear();
        lcd.print(F("highLimit = "));
        lcd.setCursor(0,1);
        lcd.print(highLimit);
        lcd.setCursor(6,1);
        lcd.print(F("="));
        lcd.setCursor(8,1);
        lcd.print(highLimit/2.55);
        lcd.setCursor(13,1);
        lcd.print(F("%"));
        page=0;
        Print=1; 
      }

     /*Serial.println(F("Print:"));
     Serial.print(F("counter "));Serial.println(counter);
     Serial.print(F("menu "));Serial.println(menu);
     Serial.print(F("page "));Serial.println(page);
     Serial.print(F("Print "));Serial.println(Print);
     Serial.println();
     Serial.println();*/
  }
  
  lastCounter = counter; //Save the value of the last state

  

  if(digitalRead(swPin)==0) 
  {
    if(menu == 0) 
    {
      
      menu = 1;
      counter = 0;
      //counter = val/2.55;
      Print = 0;
      delay(650);
     }

    else if(menu == 1)
    {
        
      if(page==0) //Back to info screen
      {
        menu=0; 
        //counter=0;
        //counter = val/2.55;
        counter = 0;
        Print=0; //When pushed is 0 the program returns to printing      
        delay(500);
      }
      
      if(page==1) //Switch mode
      {
        menu=2;
        //EEPROM_readAnything(100, pwmMenu);
        counter = 0;
        Print=0;
        delay(500);
        
      }

      if(page==2) //Boost target set
       {
        menu=3;
        counter=0;
        Print=1;
        EEPROM_readAnything(0, boostTarget);
        counter=boostTarget*20;
        delay(500);
       }

      if(page==3) //Kp set
       {
        menu=4;
        counter=0;
        Print=1;
        EEPROM_readAnything(40, Kp);
        counter=Kp*20;
        delay(500);
       }

      if(page==4) //Ki set
       {
        menu=5;
        counter=0;
        Print=1;
        EEPROM_readAnything(60, Ki);
        counter=Ki*20;
        delay(500);
       }

      if(page==5) //Kd set
       {
        menu=6;
        counter=0;
        Print=1;
        EEPROM_readAnything(80, Kd);
        counter=Kd*20;
        delay(500);
       }

       if(page==6) //lowLimit set
       {
        menu=7;
        counter=0;
        Print=1;
        EEPROM_readAnything(120, lowLimit);
        counter=lowLimit;
        delay(500);
       }

       if(page==7) //lowLimit set
       {
        menu=8;
        counter=0;
        Print=1;
        EEPROM_readAnything(140, highLimit);
        counter=highLimit;
        delay(500);
       }
    }//end of submenu 1

    else if(menu == 2) //Switch mode
      {
        mode = pwmMenu;
        if(pwmMenu<2) EEPROM_writeAnything(100, pwmMenu);
        menu=0;
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
      EEPROM_writeAnything(0, boostTarget);
      pidTarget = boostTarget*multiplier;
      delay(500);
      lcd.clear();
      lcd.print(F("Boost Target"));
      lcd.setCursor(0,1);
      lcd.print(F("saved"));
      delay(1500);
    }

    else if(menu == 4) 
    {
      menu=1;
      counter=0;
      Print=0;
      //EEPROM write here
      EEPROM_writeAnything(40, Kp);
      myPID.SetTunings(Kp, Ki, Kd);
      delay(500);
      lcd.clear();
      lcd.print(F("Kp saved"));
      //lcd.setCursor(0,1);
      //lcd.print(F("saved"));
      delay(1500);
    }

    else if(menu == 5) 
    {
      menu=1;
      counter=0;
      Print=0;
      //EEPROM write here
      EEPROM_writeAnything(60, Ki);
      myPID.SetTunings(Kp, Ki, Kd);
      delay(500);
      lcd.clear();
      lcd.print(F("Ki"));
      lcd.setCursor(0,1);
      lcd.print(F("saved"));
      delay(1500);
    }

    else if(menu == 6) 
    {
      menu=1;
      counter=0;
      Print=0;
      //EEPROM write here
      EEPROM_writeAnything(80, Kd);
      myPID.SetTunings(Kp, Ki, Kd);
      delay(500);
      lcd.clear();
      lcd.print(F("Kd"));
      lcd.setCursor(0,1);
      lcd.print(F("saved"));
      delay(1500);
    }

    else if(menu == 7) 
    {
      menu=1;
      counter=0;
      Print=0;
      //EEPROM write here
      EEPROM_writeAnything(120, lowLimit);
      myPID.SetOutputLimits(lowLimit, highLimit);
      delay(500);
      lcd.clear();
      lcd.print(F("lowLimit"));
      lcd.setCursor(0,1);
      lcd.print(F("saved"));
      delay(1500);
    }

    else if(menu == 8) 
    {
      menu=1;
      counter=0;
      Print=0;
      //EEPROM write here
      EEPROM_writeAnything(140, highLimit);
      myPID.SetOutputLimits(lowLimit, highLimit);
      delay(500);
      lcd.clear();
      lcd.print(F("highLimit"));
      lcd.setCursor(0,1);
      lcd.print(F("saved"));
      delay(1500);
    }

     /*Serial.println(F("Push:"));
     Serial.print(F("counter "));Serial.println(counter);
     Serial.print(F("menu "));Serial.println(menu);
     Serial.print(F("page "));Serial.println(page);
     Serial.print(F("Print "));Serial.println(Print);
     Serial.println();
     Serial.println();*/
   
}


  //Counter limits
  
  if(counter < 0) counter=0;
  
  if(menu == 0 && counter > 100) counter=0;

  if(menu == 1 && counter > 40) counter=40;

  if(menu == 2 && counter > 15) counter=15;
  
  if(menu == 3 && counter > 200) counter=200; //Boosttarget
  
  if(menu == 4 && counter > 1000) counter=1000; //Kp

  if(menu == 5 && counter > 300) counter=300; //Ki

  if(menu == 6 && counter > 200) counter=200; //Kd

  if(menu == 7 && counter > 255) counter=255; //lowLimit

  if(menu == 8 && counter > 255) counter=255; //highLimit
  //return 0;
  
} //End of pidMenu
  

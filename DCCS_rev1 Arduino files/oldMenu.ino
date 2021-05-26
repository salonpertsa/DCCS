/*

//Loop function has the UI structure in it.


void loop() {

  readPressure();
  fanControl();
  if(menu == 0) solenoidControl();

  


  if((lastCounter > counter) || (lastCounter < counter)  || Print==0){ //Only print on the LCD when a step is detected or the button is pushed.
  
    

    //The infoview with duty cycle adjustment
    
    if(menu == 0) {
      
      if(pwmMenu == 1) { 
        PWMval=counter;
        //PWMval/=5;
        //PWMval*=5;
        
        //solenoidControl();
        
        lcd.clear();
        lcd.print(F("Duty Cycle ="));
        lcd.setCursor(0,1);
        lcd.print(PWMval);
        lcd.setCursor(3,1);
        lcd.print(F("%"));
      }
      else {
        //solenoidControl();
        
        lcd.clear();
        lcd.print(F("PID active")); 
        lcd.setCursor(0,1);  
        lcd.print(F("Target = "));
        lcd.setCursor(9,1);  
        lcd.print(boostTarget);
        lcd.setCursor(13,1);  
        lcd.print("bar");
      }
      Print=1;
    }
    
//First page of the menu
    if(menu == 1)
    {  
      if(0<=counter && counter<5)
      {
        if(pwmMenu == 1) {
        lcd.clear();
        lcd.print(F(">Back"));
        lcd.setCursor(0,1);
        lcd.print(F(" Switch to PID"));
        }
        else {
        lcd.clear();
        lcd.print(F(">Back"));
        lcd.setCursor(0,1);
        lcd.print(F(" Switch to PWM"));
        }
        page=0;
        Print=1;
      }
    
      if(5<=counter && counter<10)
      {
        if(pwmMenu == 1) {
        lcd.clear();
        lcd.print(F(">Switch to PID"));
        lcd.setCursor(0,1);
        lcd.print(F(" Set Default PWM"));
        }
        else {
        lcd.clear();
        lcd.print(F(">Switch to PWM"));
        lcd.setCursor(0,1);
        lcd.print(F(" Set Default PWM"));
        }
        page=1;
        Print=1; 
      }

      if(10<=counter && counter<15)
      {
        lcd.clear();
        lcd.print(F(">Set Default PWM"));
        lcd.setCursor(0,1);
        lcd.print(F(" Set BoostTarget"));
        
        page=2;
        Print=1; 
      }

      if(15<=counter && counter<20)
      {
        lcd.clear();
        lcd.print(F(">Set BoostTarget"));
        lcd.setCursor(0,1);
        lcd.print(F(" Set Kp"));
        
        page=3;
        Print=1; 
      }

      if(20<=counter && counter<25)
      {
        lcd.clear();
        lcd.print(F(">Set Kp"));
        lcd.setCursor(0,1);
        lcd.print(F(" Set Ki"));
        
        page=4;
        Print=1; 
      }

      if(25<=counter && counter<30)
      {
        lcd.clear();
        lcd.print(F(">Set Ki"));
        lcd.setCursor(0,1);
        lcd.print(F(" Set Kd"));
        
        
        page=5;
        Print=1; 
      }

      if(30<=counter && counter<35)
      {
        lcd.clear();
        lcd.print(F(">Set Kd"));
        
        
        page=6;
        Print=1; 
      }
      
  }//menu = 1;


    //Second page of the menu
    if(menu == 2)
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
      }//submenu = 2;

    if(menu == 3)
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

    if(menu == 4)
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


    if(menu == 5)
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


    if(menu == 6)
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
      
     Serial.println(F("Print:"));
     Serial.print(F("counter "));Serial.println(counter);
     Serial.print(F("submenu "));Serial.println(submenu);
     Serial.print(F("page "));Serial.println(page);
     Serial.print(F("pushed "));Serial.println(pushed);
     Serial.print(F("Ready "));Serial.println(Ready);
     Serial.println();
     Serial.println();
  }//end of the MENU prints on the LCD


  lastCounter = counter; //Save the value of the last state



//Detecting a push of the button

if(digitalRead(swPin)==0) {
    
    if(menu == 0) {
     
      PWMval=counter;
      PWMval/=5;
      PWMval*=5;
      val = PWMval*2.55;
      
      menu = 1;
      counter = 0;
      //counter = val/2.55;
      Print = 0;
      delay(650);
     }

    else if(menu == 1){
  //if(submenu == 1 && Ready==1) {
        
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
        pwmMenu = !pwmMenu;
        EEPROM_writeAnything(100, pwmMenu);
        menu=0;
        counter = PWMval;
        Print=0;
        delay(500);
        
       }
      if(page==2) //PWM set
       {
        menu=2;
        counter=0;
        Print=1;
        EEPROM_readAnything(20, PWMval);
        counter=PWMval;
        delay(500);
       }

      if(page==3) //Boost target set
       {
        menu=3;
        counter=0;
        Print=1;
        EEPROM_readAnything(0, boostTarget);
        counter=boostTarget*20;
        delay(500);
       }

      if(page==4) //Kp set
       {
        menu=4;
        counter=0;
        Print=1;
        EEPROM_readAnything(40, Kp);
        counter=Kp*20;
        delay(500);
       }

      if(page==5) //Ki set
       {
        menu=5;
        counter=0;
        Print=1;
        EEPROM_readAnything(60, Ki);
        counter=Ki*20;
        delay(500);
       }

      if(page==6) //Kd set
       {
        menu=6;
        counter=0;
        Print=1;
        EEPROM_readAnything(80, Kd);
        counter=Kd*20;
        delay(500);
       }
    }//end of submenu 1

    else if(menu == 2)
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

    else if(menu == 3) {
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

    else if(menu == 4) {
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

    else if(menu == 5) {
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

    else if(menu == 6) {
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
     
     Serial.println(F("PUSH:"));
     Serial.print(F("counter "));Serial.println(counter);
     Serial.print(F("submenu "));Serial.println(submenu);
     Serial.print(F("page "));Serial.println(page);
     Serial.print(F("pushed "));Serial.println(pushed);
     Serial.print(F("Ready "));Serial.println(Ready);
     Serial.println();
     Serial.println();
}



  //Counter limits
  
  if(counter < 0) counter=0;
  
  if(menu == 0 && pwmMenu == 1 && counter > 100) counter=100;

  if(menu == 0 && pwmMenu == 0) counter=0;

  if(menu == 1 && counter > 35) counter=35;
  
  if(menu == 2 && counter > 100) counter=100; //Default pulse width %
  
  if(menu == 3 && counter > 200) counter=200; //Boosttarget
  
  if(menu == 4 && counter > 600) counter=600; //Kp

  if(menu == 5 && counter > 300) counter=300; //Ki

  if(menu == 6 && counter > 200) counter=200; //Kd
  
  //if(counter < 0) counter=0;
  //if(counter > 100) counter=100;
}
 
*/
  

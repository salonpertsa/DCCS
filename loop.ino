//Loop function has the UI structure in it.

void loop() {

  readPressure();
  fanControl();
  if(menu == 0) solenoidControl();


    if (mode == 0)
      pid_menu();
  
    else if(mode == 1) 
      pwm_menu();
    
    else if (mode == 2)
      dark_menu();

}
  

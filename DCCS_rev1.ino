
/*Arduino Nano based boost controller code for wastegate equipped turbochargers developed and written by Eetu Salo.
 * 
 * Components of the proto assembly: 
 * -DIY Boost controller board built on perf board
 * -Arduino Nano with an Ebay terminal module
 * -Rotary encoder module with a knob
 * -VAG N75 wastegate actuator control solenoid
 * -LCD 16x2 with I2C for a menu / user interface
 * -0.91" OLED display with I2C for current manifold pressure reading
 * -+250 kPa MAP sensor
 * -3D-printed enclosure for all the components, perhaps a separate enclosure for the UI components
 * -Wiring sets
 * 
 * Features of the user interface:
 * -Recording and resetting of the maximum manifold pressure reached (a volatile variable)
 * -Dangerous overpressure detection ?
 * -Boost controller on/off (can be simply done by a mechanical power-on switch)
 * -Open loop boost control with PWM
 *  ->Set the desired default duty cycle (EEPROM)
 *  ->Set the duty cycle
 * -Closed loop boost control with PID control
 *  ->Set the desired default target boost value (EEPROM)
 *  ->Set the boost value
 * -Voltage bus monitoring?
 * -
 */


// 'memeeman', 128x32px
/*
const unsigned char myBitmap [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0x0f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xe6, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf8, 0x01, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x7f, 0xf8, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x7f, 0xf9, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x3f, 0xde, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x0f, 0xf3, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x03, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x01, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xfe, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};*/

//Libraries and headers

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include "EEPROM.h" //Library for storing variable's values in the microcontrollers non-erasing EEPROM memory
#include "EEPROMAnything.h" //Custom header file for saving negative values in EEPROM
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
//#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#include <PID_v1.h>


//Global variables

#define solenoidPin 9 //PWM pin for N75 mosfet control
#define mapPin A2 //MAP sensor signal pin
#define tempPin A0 //Temperature sensor signal pin
#define fanPin 11 //Fan control pin


//Pins of the Keyes KY040 rotary encoder module
#define dtPin 4 //DT->D4
#define clkPin 3 //CLK->D3
#define swPin 2 //SW->D2

#include "OneButton.h"
OneButton button(swPin, true);

double boostTarget = 0; 
double pidTarget = 0; //Target boost pressure multiplied for PID control
double multiplier = 20.00; //Pressure multiplier for PID control

unsigned int mapData = 0; //Raw values from MAP sensor
//float mapData = 0; 
float maxBoost=0; //A variable for storing the highest boost reached
float U_m = 0;       //rawData values converted to voltage level
float absP = 0;     //Voltage level converted to absolute manifold pressure
float overP = 0;  //Boost pressure (absP-1.023)
double pidP = 0;  //Boost pressure multiplied for PID control
double aveP = 0;
float atmosphericP = 1.00;
int Pcounter = 0;


unsigned int tempData = 0; //
unsigned int temp; //Engine coolant temperature value
unsigned int triggerTemp = 100; //Engine coolant temperature in degrees Celsius to trigger the fan
unsigned int offTemp = 95; //Engine coolant temperature in degrees Celsius at which the fan is turned off
float U_t = 0;

const unsigned long OLEDdur = 100;
//const unsigned long LCDdur = 750;
const unsigned long serialDur = 500;
//const unsigned long maxBoostDur = 5000;
const unsigned long PIDdur = 50;
unsigned long tOLEDBegin = 0;
//unsigned long tLCDBegin = 0;
unsigned long tSerialBegin = 0;
//unsigned long tMaxBoostBegin = 0;
unsigned long tPIDbegin = 0;


//Variables for the menu and encoder
int counter; //Rotary encoder position change counter
//int stepCounter = 0;
int page=0;
//byte Ready = 1;
byte pwmMenu; //==1, pwm is active
byte mode;
byte menu=0;
int lastCounter = 0; 
bool clkState;
bool lastState; 
bool dtState;  
byte Print = 1; //The button on the rotary encoder module has a built-in pull up resistor. Button state normally !=0
byte clickd = 0;
byte lcdOff = 1;

//unsigned int PWMsave;
unsigned int PWMval; //Duty cycle in percents
double val, val2 = 0;//Duty cycle in 8 bits, 0-255
double highLimit, lowLimit;


double Kp=0, Ki=0, Kd=0; //PID controller tuning parameters

PID myPID(&pidP, &val, &pidTarget, Kp, Ki, Kd, P_ON_E, DIRECT);
//PID myPID(&Input, &Output, &Setpoint,2,5,1,P_ON_M, DIRECT); //P_ON_M specifies that Proportional on Measurement be used
                                                            //P_ON_E (Proportional on Error) is the default behavior


void setup() {
  
  TCCR1B = TCCR1B & B11111000 | B00000101; // for PWM frequency of 30.64 Hz for ATmega328P pins D9 & D10

  
  
  pinMode(solenoidPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  //pinMode(swPin,INPUT_PULLUP);  //Define the pin as input. The encoder module has built-in 10K pull-up resistors for clk & dt 
  pinMode(dtPin, INPUT);
  pinMode(clkPin, INPUT);
  //pinMode(inpin, INPUT);
  Serial.begin(115200);
  
  lcd.init();
  lcd.backlight();
  button.attachDoubleClick(dclick);
  //button.attachDuringLongPress(longPress);

  
  //Get default parameter values from the non-volatile EEPROM memory
  
  EEPROM_readAnything(0, boostTarget);
  EEPROM_readAnything(20, PWMval);
  EEPROM_readAnything(40, Kp);
  EEPROM_readAnything(60, Ki);
  EEPROM_readAnything(80, Kd);
  EEPROM_readAnything(100, pwmMenu);
  EEPROM_readAnything(120, lowLimit);
  EEPROM_readAnything(140, highLimit);
  
  counter = PWMval;
  pidTarget = boostTarget*multiplier;
  mode = pwmMenu;
  //EEPROM_writeAnything(100, 1);

  
  //Interrupt routine function for the rotary encoder
  attachInterrupt(digitalPinToInterrupt(clkPin), A_interrupt, CHANGE);
  //Interrupt routine function for the rotary encoder button
  attachInterrupt(digitalPinToInterrupt(swPin), B_interrupt, CHANGE);

  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(lowLimit, highLimit); // * clamps the output to a specific range. 8 bits or 0-255 by default
  myPID.SetTunings(Kp, Ki, Kd);
  myPID.SetSampleTime(50);              // * sets the frequency, in Milliseconds, with which 
                                        //   the PID calculation is performed.  default is 100

                                        
  //Automatic boost sensor calibration?
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  delay(100);
  display.clearDisplay();
  display.setTextSize(4);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);
  /*display.clearDisplay();
  display.setCursor(0,0);             // Start at top-left corner
  display.println(boostTarget);
  display.display();
  delay(1500);*/
  /*
  display.clearDisplay();
  display.setTextSize(3); 
  display.setCursor(0,0);             // Start at top-left corner
  display.print(F("BIG"));
  display.display();
  delay(750);
  display.clearDisplay();
  display.print(F("BOST"));
  display.display();
  delay(750);
  display.clearDisplay();
  //display.display();
  //display.drawBitmap(0, 0, myBitmap, 128, 32, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
  delay(1000);
  display.clearDisplay();

  

  //Print text at the beginning
  
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Boost"));
  lcd.setCursor(0,1);  
  lcd.print(F("Control Unit"));
  delay(1000);
  
  if(pwmMenu == 1) {
    lcd.clear();
    lcd.print(F("Default Duty")); 
    lcd.setCursor(0,1);  
    lcd.print(F("Cycle = "));
    lcd.setCursor(8,1);  
    lcd.print(PWMval);
    lcd.setCursor(11,1);  
    lcd.print(F("%"));
    delay(1500);
    lcd.clear();
    delay(500);
    lcd.print(F("Duty Cycle ="));
    lcd.setCursor(0,1);
    lcd.print(PWMval);
    lcd.setCursor(3,1);
    lcd.print(F("%"));
  }
  
  else {
    lcd.clear();
    lcd.print(F("Default Boost")); 
    lcd.setCursor(0,1);  
    lcd.print(F("Target = "));
    lcd.setCursor(9,1);  
    lcd.print(boostTarget);
    lcd.setCursor(13,1);  
    lcd.print(F("bar"));
    delay(1500);
    lcd.clear();
    delay(500);
    lcd.print(F("PID active")); 
    lcd.setCursor(0,1);  
    lcd.print(F("Target = "));
    lcd.setCursor(9,1);  
    lcd.print(boostTarget);
    lcd.setCursor(13,1);  
    lcd.print("bar");
  }
  */
  
 
}

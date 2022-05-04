/*
 *  Tensile Tester - Stepper Motor & I2C LCD
 *  tensile_tester_with_motorProtoThread.ino
 *  Uses T660 Stepper Driver Unit
 *  With speed control & forward and reverse switch
 *  Team 11 Spring 2022
*/
#include "HX711.h"
#include <TimedAction.h>
#include <LiquidCrystal_I2C.h>

//initialize LCD_I2C the library with the number of interface pins
LiquidCrystal_I2C lcd(0x27, 20, 4); //I2C address 0x27, 20 column and 4 rows

// Switch pins
const int pinButton = 8; // forward
const int pinButton2 = 4;// backward

// Defining menu buttons 
const int nextButton1 = 3;   // #1 Push button
int nextButton2 = 2;     // #2 Push button

// Define motor driver pins
int driverPUL = 7;      // PUL- pin
int driverDIR = 6;      // DIR- pin
int varResistor = A0;           // Potentiometer

// Load cell pins
const int LOADCELL_DT_PIN = 9;
const int LOADCELL_SCK_PIN = 5;

// motor Variables
int pulseDelay = 500;       // Pulse Delay period
boolean userReady = false; // user Readys up
boolean setdir = false; // Set Direction
boolean stopMotor = true;

// distance calibration var
double otherCal = .00133;//, otherCalculatedDis = 0; // 4681958
//double slopeD = 766.00;
int currentSteps = 0; // keeps track of the motors current steps
int calInstructionStep = 0; // increments to move on the the next step for user
double calculatedDistance = 0;

// system mode var
boolean calibrate = false;
boolean testing = false;
boolean testingInprogress = false;
boolean menuPrinted = false; //

// load cell calibration var
double zero = 0, oneKg = 0, slope = -98748.00;// -98625.00;
HX711 scale;

// array for data
const int rows = 5, columns = 2;
double data [rows][columns];
int currentRow = 0;

double cm = 0;
double kgs = 0;

void printMenu() {
  menuPrinted = true; 
  // prints menu to LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tensile Tester");
  lcd.setCursor(0,1);
  lcd.print("Select a mode");
  lcd.setCursor(0,2);
  lcd.print("1: Calibrate");
  lcd.setCursor(0,3);
  lcd.print("2: Run Test");
}

void checkSwitchState() {
  int stateButton = digitalRead(pinButton); // get state of forward switch
  int stateButton2 = digitalRead(pinButton2);// get state of backward switch

  if(stateButton == 1) { // if forward
     //Serial.println("Forward");
     setdir = LOW;      // sets motor direction to low
     stopMotor = false; // Starts the motor
  } else
  if(stateButton2 == 1) { // if backward
     //Serial.println("Backward");
     setdir = HIGH;     // sets motor direction to high
     stopMotor = false; // Starts the motor
  } else
    stopMotor = true; // stops the motor if nothing on the switch is pressed
}

void motorControl() { // pulses motor
  // runs the motor if a switch is pressed
    pulseDelay = map((analogRead(varResistor)),0,1023,2000,50); // short delay value based on variable resistor
    digitalWrite(driverDIR,setdir);
    digitalWrite(driverPUL,HIGH); // sets motor to high
    //delayMicroseconds(pulseDelay);      // digitalWrite take time so it acts as a delay
    digitalWrite(driverPUL,LOW);  // sets motor to low
    delayMicroseconds(pulseDelay);        // short delay before the motor pulses again
    
    if (!setdir) // if the direction is forward the currentSteps counter increases 
      currentSteps++;
    else        // if the direction is backward the currentSteps counter decreases
      currentSteps--; 
}

void getData() {
  // distance measurement
  cm = (currentSteps * otherCal); // read in the distance
  // load measurement
  kgs = (scale.get_units()/slope); //reads in load
  // save data
    data [currentRow][0] = cm; // saves the current distance
    data [currentRow][1] = kgs; // saves the current load
    currentRow++;
}

// setting up threads
TimedAction measurementThread = TimedAction(500,getData); // (delay, method called)
TimedAction switchThread = TimedAction(300,checkSwitchState); // (delay, method called)

void nextB2() {
  
  delay(1000); // delay so only one button press is detected
  userReady = true; // tells the program the user is ready to move on
  if (!calibrate && !testing)
    testing = true;
}

void nextB1() {
  
  delay(1000); // delay so only one button press is detected
  userReady = true; // tells the program the user is ready to move on
  if (!calibrate && !testing)
    calibrate = true;
}

void setup() {

  // driver control pins
  pinMode (driverPUL, OUTPUT);
  pinMode (driverDIR, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(nextButton1), nextB1, FALLING); // user hits a button to move on and next() is called
  attachInterrupt(digitalPinToInterrupt(nextButton2), nextB2, FALLING); // user hits a button to move on and next() is called

  // Switch setup
  pinMode(pinButton, INPUT);  // setup for forward switch
  pinMode(pinButton2, INPUT); // setup for backward switch
  Serial.begin(9600);

  // load cell setup
  scale.begin(LOADCELL_DT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare();

  //initialize the lcd
  lcd.init();
  lcd.backlight();
  // set up the LCD's number of columns and rows: 
  lcd.begin(20, 4);
  
  printMenu(); // Print Menu to LCD
}

void loop() {
  
  switchThread.check();
  // Menu
  if (!calibrate && !testing && !menuPrinted)
    printMenu();
  
  if (calibrate) {

  //***Load Cell Calibration Section**********************************************************************
  
      if (calInstructionStep == 0) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Calibration Mode");
        lcd.setCursor(0,1);
        lcd.print("Remove all mass from");
        lcd.setCursor(0,2);
        lcd.print("the scale");
        lcd.setCursor(0,3);
        lcd.print("Press to confirm");
        Serial.println("Remove all weight from the scale");
        Serial.println("Press any button to continue");
        calInstructionStep = 1; // next button press will zero the load cell
        userReady = false;
        // wait till the user presses a button
      }

      if (calInstructionStep == 1 && userReady) {
        scale.tare(); // tare load cell
        zero = scale.get_units(12); // take zero reading of the load cell
        Serial.println("Put 1kg weight on the bracket");
        Serial.println("Press any button to continue");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Calibration Mode");
        lcd.setCursor(0,1);
        lcd.print("Place 1kg of mass on");
        lcd.setCursor(0,2);
        lcd.print("the scale");
        lcd.setCursor(0,3);
        lcd.print("Press to confirm");
        userReady = false;
        calInstructionStep = 2; // next button press will measure the load cell at 1kg
      }

      if (calInstructionStep == 2 && userReady) {
        oneKg = scale.get_units(12);  // measure 1kg
        //Serial.println(oneKg); 
        slope = (oneKg - zero) / (1 - 0);
        userReady = false;
        calInstructionStep = 3; // next button press will measure an unknown load
        Serial.println("Put known weight on the scale");
        Serial.println("Press any button to continue");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Calibration Mode");
        lcd.setCursor(0,1);
        lcd.print("Now place a known");
        lcd.setCursor(0,2);
        lcd.print("mass on the scale");
        lcd.setCursor(0,3);
        lcd.print("Press to confirm");
      }

      if (calInstructionStep == 3 && userReady) {
        Serial.print("weight on the scale: ");
        Serial.println((scale.get_units(5)/slope));
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Calibration Mode");
        lcd.setCursor(0,1);
        lcd.print("Mass on the scale:");
        lcd.setCursor(0,2);
        lcd.print((scale.get_units(5)/slope));
        lcd.setCursor(3,2);
        lcd.print("kgs");
        lcd.setCursor(0,3);
        lcd.print("Press to confirm");
        userReady = false;
        calInstructionStep = 4;
      }
      
      if (calInstructionStep == 4 && userReady) {
        calibrate = false;
        menuPrinted = false;
        userReady = false;
        calInstructionStep = 0; // resesting calibration mode
      }
  
  //***End of Load Cell Calibration Section***************************************************************
  } else

  if (testing) {
    
    if (calInstructionStep == 0 && !testingInprogress) { // prints mod
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Testing Mode");
        lcd.setCursor(0,1);
        lcd.print("Remove any slack");
        lcd.setCursor(0,2);
        lcd.print("from the sample");
        lcd.setCursor(0,3);
        lcd.print("Press to start test");
        calInstructionStep = 1;
        userReady = false;
      } else
      
    if (calInstructionStep == 1 && userReady) { // prints data heading and starts test
      scale.tare(); // set load to 0 kgs
      currentSteps = 0; // set distance to zero
      // prints to LCD
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Testing Mode");
      lcd.setCursor(0,1);
      lcd.print("Test in progress");
      lcd.setCursor(0,2);
      lcd.print("recording data...");
      lcd.setCursor(0,3);
      lcd.print("Press to end test");
      // printing headings in spreadsheet
      Serial.print("Distance (cm)");
      Serial.print("\t");
      Serial.print("Mass (kg)");
      Serial.print("\n");
      testingInprogress = true; // begin testing
      calInstructionStep = 2;
      userReady = false;
    }
    
    if (calInstructionStep == 2 && userReady) { // ends testing when a button is pressed
      calInstructionStep = 0;
      userReady = false;
      testingInprogress = false; // ending testing
      testing = false; // exiting testing
      menuPrinted = false;
    }
    
    
    if (testingInprogress) // takes measurements if testing
      measurementThread.check();
      
  }

  if(currentRow == rows) {
    // print to .csv file
    for (int j = 0; j < rows; ++j) { // loops through each set of data collected
        
      for (int i = 0; i < columns; ++i) { // loops through each distance and load collected
  
        Serial.print(data[j][i]); // prints data
        Serial.print("\t");
      }
      Serial.print("\n");
    }
    currentRow = 0;
  }
  
  if (!stopMotor) // runs motor if the switch is pressed
    motorControl();
}

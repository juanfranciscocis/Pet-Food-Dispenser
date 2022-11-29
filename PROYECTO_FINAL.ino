#include <LiquidCrystal.h> 
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); 
const int trigPin = 13;
const int echoPin = 12;
long duration;
int distanceCm, distanceInch;
float sensorToFloor = 12;
#include<Servo.h>
Servo Myservo;
int pos;


#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);
char customKey = 'a';
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {11, 10, 9, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad
Keypad myKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//MY PROGRAM!!
int menuOpt = 0;

//MENU 1
int foodQuantity = -48; //-48
int foodTime = -48; //-48

//MENU 2
boolean setupComplete = false;

void setup() {
  Myservo.attach(3);
  lcd.begin(16, 2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600); // Starting Serial Terminal
  closeDoor();

}

void loop() {
  if (menuOpt == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Bienvenido al");
    lcd.setCursor(0, 1);
    lcd.print("Menu Principal");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("1 = Setup Inicio");
    lcd.setCursor(0, 1);
    lcd.print("2 = Comenzar");
    while(true){
      customKey = myKeypad.getKey();


      if(customKey == '1'){
        menuOpt = 1;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("MENU SETUP");
        lcd.setCursor(0, 1);
        lcd.print("INICIANDO...");

        break;
      }else if (customKey == '2') {
        menuOpt = 2;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("MENU CONTINUAR");
        lcd.setCursor(0, 1);
        lcd.print("INICIANDO...");
        break;
      }


      

    }
    
    
  }

  if (menuOpt == 1) {
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FAVOR INGRESAR");
    lcd.setCursor(0, 1);
    lcd.print("LA CANTIDAD DE");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("COMIDA A DAR");
    lcd.setCursor(0, 1);
    lcd.print("EN CM:");
    while (foodQuantity == -48) {
      customKey = myKeypad.getKey();
      foodQuantity = int(customKey)-48;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("COMIDA A DAR");
    lcd.setCursor(0, 1);
    lcd.print(foodQuantity);
    lcd.print(" CM");

    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FAVOR INGRESAR");
    lcd.setCursor(0, 1);
    lcd.print("LA CANTIDAD DE");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TIEMPO PARA");
    lcd.setCursor(0, 1);
    lcd.print("ALIMENTAR(MIN):");
    while (foodTime == -48) {
      customKey = myKeypad.getKey();
      foodTime = int(customKey)-48;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TIEMPO PARA");
    lcd.setCursor(0, 1);
    lcd.print("ALIMENTAR: ");
    lcd.print(foodTime);
    lcd.print(" MIN");
    delay(3000);

    setupComplete = true;
    menuOpt = 2;


  }

  if (menuOpt == 2) {
    if(setupComplete == false){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SETUP NO");
      lcd.setCursor(0, 1);
      lcd.print("REALIZADO");
      lcd.setCursor(0, 1);
      delay(3000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("TODO POR");
      lcd.setCursor(0, 1);
      lcd.print("DEFECTO...");
      lcd.setCursor(0, 1);
      foodQuantity = 3;
      foodTime = 1;
      setupComplete = true;
      delay(3000);
    }
    closeDoor();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MENU 2, LISTO!!!");
    lcd.setCursor(0, 1);
    lcd.print("SETEADO PARA...");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ALIMENTAR CADA");
    lcd.setCursor(0, 1);
    lcd.print(foodTime);
    lcd.print(" MIN ESPERE...");
    delay(foodTime*6000); //foodTime*60000
    int serving = 12;
    while (serving != (sensorToFloor-foodQuantity) ) {
      serving = returnAltitud();
      openDoor();
      if (serving < (sensorToFloor-foodQuantity) ) {
        break;
      }
    }
    closeDoor();

    serving = 12;
    while (serving != (sensorToFloor-foodQuantity) ) {
      serving = returnAltitud();
      openDoor();
      if (serving < (sensorToFloor-foodQuantity) ) {
        break;
      }
    }
    closeDoor();

    serving = 12;
    while (serving != (sensorToFloor-foodQuantity) ) {
      serving = returnAltitud();
      openDoor();
      if (serving < (sensorToFloor-foodQuantity) ) {
        break;
      }
    }
    closeDoor();














  }

    
}

int returnAltitud(){
  while(true){

  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  Serial.print(distanceCm);
  Serial.print("cm");
  Serial.println();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALIMENTANDO...");
  lcd.setCursor(0, 1);
  lcd.print(distanceCm);
  lcd.print(" CM");
  delay(1000);
  if(distanceCm <= 1 ){
    continue;
  }
  return distanceCm;
  }
}

void openDoor(){
  Myservo.write(110);

}

void closeDoor(){
    Myservo.write(18);
}

void openAndClose(float delaySe){
  openDoor();
  delay(delaySe);
  closeDoor();
}
  
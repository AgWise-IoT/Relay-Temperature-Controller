

/** Written by Ryan Cole, October 2018
 *  Must be run on an Uno, or other AVR architecture
 *  ESP-32 boards will not work with the LCD
 *  
 *  Connect a dallas D18B20 thermometer to pin 8 with a pull up resistor
 *  
 *  Connect a relay controlling an outlet to pin 12
 *  
 *  Connect the LCD screen to 5VDC, Ground, SCL to A5, SDA to A4
 *  
 *  Takes the temperature in fahrenheit, and if below 42 degrees turns off a relay.  If
 *  above, turns it on.  Designed to regulate temperature within a van based freezer.
 *  Displays results on an I2C based LCD screen.
 */

#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
//temp probe on pin 8
#define ONE_WIRE_BUS 8

//initialize sensors and LCD object
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27,16,2);

//relay on pin 12
int relay = 12;
float temp = 0;
int freezerStatus = 0;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Beginning setup.");
  //pinMode(26, OUTPUT);
  //digitalWrite(26, HIGH);
  //initialize relay output
  pinMode(relay, OUTPUT);
  
  //set up LCD and turn on backlight
  lcd.init();   
  lcd.backlight();

  sensors.begin();
  Serial.println("Setup complete.");
 temp = 70;
}

void loop() {
 //get and set temperature
 sensors.requestTemperatures();
 temp = sensors.getTempFByIndex(0);
 
 //display temperatures
 lcd.setCursor(0,0);
 lcd.print("Temp: " + String(temp) + "   ");
 Serial.println("Temperature: " + String(temp));

 //turn freezer on or off
 
 if (temp >= 50){
 //change temp^  
  freezerON();
 }
 else{
  freezerOFF();
 }
 printStatus();

 //wait for a second
 delay(100);

}

void freezerON(){
  digitalWrite(relay, LOW);
  freezerStatus = 1;
  }
  

void freezerOFF(){
  digitalWrite(relay, HIGH);
  freezerStatus = 0;
  }

 void printStatus(){
  lcd.setCursor(0,1);
    if (freezerStatus == 1){
      lcd.print("Freezer: ON ");
    } else{
      lcd.print("Freezer: OFF");
    }
 }

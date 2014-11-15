/*-----( Import needed libraries )-----*/
#include <Wire.h>  // Comes with Arduino IDE
// Get the LCD I2C Library here: 
// www.4tronix.co.uk/arduino/sketches/LiquidCrystal_V1.2.1.zip
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include <LiquidCrystal_I2C.h>

/*-----( Declare Constants )-----*/
/*-----( Declare objects )-----*/
// set the LCD address to 0x27 for a 16 chars 2 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

/*-----( Declare Variables )-----*/
byte byteRead;
long temp;
int hotCities;
boolean notDec;
int led = 7;
char buffer[10];
//NONE

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);  // Used to type in characters

  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  hotCities = 0;
  temp = 0;
  notDec = true;
  pinMode(led, OUTPUT);

// ------- Quick 3 blinks of backlight  -------------
  lcd.backlight(); // finish with backlight on  

//-------- Write characters on the display ------------------
// NOTE: Cursor Position: (CHAR, LINE) start at 0  
 /* lcd.setCursor(0,0); //Start at character 4 on line 0
  lcd.print("Hello, world!");
  delay(1000); 

// Wait and then tell user they can start the Serial Monitor and type in characters to
// Display. (Set Serial Monitor option to "No Line Ending")
  lcd.clear();
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Use Serial Mon");
  lcd.setCursor(0,1);
  lcd.print("Type to display");*/


}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
    // when characters arrive over the serial port...
    if (Serial.available()) {
      // wait a bit for the entire message to arrive
      delay(100);
      // flash if temp is over 20
      if (temp > 25) {
          digitalWrite(led, HIGH);
          delay(200);
          digitalWrite(led, LOW);
          hotCities++;
        }
      // clear the screen
      lcd.clear();
      notDec = true;
      temp = 0;
      // read all the available characters
      while (Serial.available() > 0) {
        // display each character to the LCD
        byteRead = Serial.read();
        Serial.println(byteRead);
        // if backslash clear lcd
        switch (byteRead) {
          case 47:
            lcd.setCursor(0,1);
            continue;
            break;
          case 92:
            lcd.clear();
            break; 
        }
        // write to lcd
        lcd.write(byteRead);
        if (byteRead == 46) {
          notDec = false;
        }
        if (byteRead > 47 && byteRead < 58 && notDec) {
          // convert ascii to numbers 
          temp = (temp * 10) + byteRead - 48;
        }
      }
      // send hotCities number
      Serial.print(hotCities);
    }

}/* --(end main loop )-- */


/* ( THE END ) */


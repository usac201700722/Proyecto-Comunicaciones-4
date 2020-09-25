/*
  LiquidCrystal Library - scrollDisplayLeft() and scrollDisplayRight()

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD and uses the
 scrollDisplayLeft() and scrollDisplayRight() methods to scroll
 the text.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalScroll

*/

// Librerías utilizadas
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Adafruit_MLX90614.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int pinMedicion = 8;
const int ledRojo = 6;
const int ledVerde = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Se declara el objeto
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

const int numRows = 2;
const int numCols = 16;

volatile byte midiendo = HIGH;

void setup() {
  // set up the LCD's number of columns and rows:
  // Inicializa la LCD y el MLX90614
  Serial.begin(9600);
  lcd.begin(numCols, numRows);
  mlx.begin();
  pinMode(pinMedicion, INPUT_PULLUP);
  pinMode(ledRojo,OUTPUT);
  pinMode(ledVerde,OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("MLX90614 Sensor");
  delay(800);
  lcd.setCursor(0, 1);
  lcd.print("Measuring...");
  delay(800);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("--- Celsius ---");
  delay(800);

}

void loop() {
  digitalWrite(ledVerde,LOW);
  digitalWrite(ledRojo,LOW);
  lcd.clear();
  while (Serial.available() > 0){  
    switch(Serial.read()){
      case '0':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("NO TIENE MASCARILLA");
      digitalWrite(ledRojo,HIGH);
      delay(500);    
      break;
      
      case '1':
      lcd.setCursor(0, 0);
      lcd.print("Ambient: "); lcd.print(mlx.readAmbientTempC());
      lcd.print("C");
      lcd.setCursor(0, 1);
      float objeto = mlx.readObjectTempC();
      lcd.print("Object:  "); lcd.print(objeto);
      lcd.print("C");
      delay(250);
      
      if(objeto >= 37.20){
        digitalWrite(ledRojo,HIGH);
      }
      else{
        digitalWrite(ledVerde,HIGH);       
      }
      break;
      
    }
  }
}

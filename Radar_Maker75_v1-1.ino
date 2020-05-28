#include <Servo.h>  
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET   -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Servo myservo;  

#include "SR04.h"
#define TRIG_PIN 9
#define ECHO_PIN 8
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long d;
int modo;
//int Echo = 8;  
//int Trig = 9; 

void setup() {
  myservo.attach(3);
  Serial.begin(9600);    
 // pinMode(Echo, INPUT);    
 // pinMode(Trig, OUTPUT);   
  Serial.println("Ok");

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  // Clear the buffer
  display.clearDisplay(); 
}

void loop() {
  Serial.println("Scan");
  display.clearDisplay();   
  myservo.write(90);
  modo = analogRead(A0);
  if (modo<512){
  display.setTextSize(1);
  display.setCursor(90,55);
  display.println("RADAR");
  display.display();
  for (int i = 30; i < 150; i = i + 5) {
    myservo.write(i);
    d = sr04.Distance();
    //d = map(d, 0, 496, 0, 60);

    float a = PI * (float)i / 180.0f;

    int xl = 64 + cos(a) * d;
    int yl = 64 - sin(a) * d;
    
    display.drawLine(64, 64, xl, yl, WHITE);
    display.display();
    delay(100);
    Serial.println(d);
  }
  }
  if (modo>512){
    d = sr04.Distance();
    display.clearDisplay();  
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0,5);
  display.println("misuratore distanza");
  display.setCursor(30,40);
  display.println(d);
  display.setCursor(100,40);
  display.println("cm");
  display.display();
    
  }
  myservo.write(90);
  delay(500);
  
}

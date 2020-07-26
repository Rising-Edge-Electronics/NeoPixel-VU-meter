/*
 * Author: Priyath Fonseka
 * July 2020
 * Neo Pixel VU meter shield for Arduino UNO
 * 
 * Pin: 8 - LED strip data pin
 * Pin 10 - button pin
 * A0 - audio in
 * 
 */




#include <Adafruit_NeoPixel.h>

#define PIN 8
#define button 10
#define audio A0

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

int maxi=0;
int led=0;
int counter=0;

int brightness = 64;
int state = LOW;

int pattern = 1; //pattern number incremented by the button 



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(audio,INPUT);
pinMode(button,INPUT);
pinMode(PIN,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

int level=analogRead(audio);
int btn = analogRead(button);

if(level>maxi)
maxi=level; 


led = map(level,0,maxi,0,8);



  if(debounceButton(state) == HIGH && state == LOW)
  {
    pattern++;
    if(pattern==9)
    pattern=1;
    
    state = HIGH;
  }
  else if(debounceButton(state) == LOW && state == HIGH)
  {
       state = LOW;
  }



switch(pattern)
{
  case 1:
  pattern1();
  break;
  case 2:
  pattern2();
  break;
  case 3:
  pattern3();
  break;
  case 4:
  pattern4();
  break;
  case 5:
  pattern5();
  break;
  case 6:
  pattern6(level,maxi);
  break;
  case 7:
  pattern7();
  break;
  case 8:
  pattern8();
  break;
}

//Serial.println(led);

}




void pattern1()
{


 pixels.setPixelColor(led,pixels.Color(255,0,0));
 pixels.setBrightness(brightness);
pixels.show();

   
delay(50);

 pixels.setPixelColor(led,pixels.Color(0,0,0));
  pixels.setBrightness(brightness);
pixels.show();

delay(50);
Serial.println(pattern);
}



int prevled=0;
void pattern2()
{
if(led>prevled)
{
   for(int i=prevled-1;i<=led;i++)
   {
    pixels.setPixelColor(i,pixels.Color(255,204,0));

     pixels.setBrightness(brightness);
    pixels.show();
   }
   delay(10);
}

if(led<prevled)
{
   for(int i=prevled;i>=led;i--)
   {
 pixels.setPixelColor(i,pixels.Color(0,0,0));
  pixels.setBrightness(brightness);
pixels.show();
   }
   delay(10);

}
   
prevled=led;

  Serial.println(pattern);
}

//from the middle of the strip go up and down 
void pattern3()
{

int nled=(int)led/2;

for(int i=4;i<=4+nled;i++)
{
  pixels.setPixelColor(i,pixels.Color(255,0,0));
  pixels.setBrightness(brightness);
  pixels.show();
}
for(int i=3;i>=3-nled;i--)
{
  pixels.setPixelColor(i,pixels.Color(255,0,0));
  pixels.setBrightness(brightness);
  pixels.show();
}
 delay(10);
//turn off
for(int i=4;i<=nled+4;i++)
{
  pixels.setPixelColor(i,pixels.Color(0,0,0));
  pixels.setBrightness(brightness);
  pixels.show();
}
for(int i=3;i>=3-nled;i--)
{
  pixels.setPixelColor(i,pixels.Color(0,0,0));
  pixels.setBrightness(brightness);
  pixels.show();
}
 delay(10);

Serial.println(pattern);
  
}

//pattern 3 in blue
void pattern4()
{

int nled=(int)led/2;

for(int i=4;i<=4+nled;i++)
{
  pixels.setPixelColor(i,pixels.Color(0,0,255));
  pixels.setBrightness(brightness);
  pixels.show();
}
for(int i=3;i>=3-nled;i--)
{
  pixels.setPixelColor(i,pixels.Color(0,0,255));
  pixels.setBrightness(brightness);
  pixels.show();
}
 delay(10);
//turn off
for(int i=4;i<=nled+4;i++)
{
  pixels.setPixelColor(i,pixels.Color(0,0,0));
  pixels.setBrightness(brightness);
pixels.show();
}
for(int i=3;i>=3-nled;i--)
{
  pixels.setPixelColor(i,pixels.Color(0,0,0));
  pixels.setBrightness(brightness);
pixels.show();
}
 delay(10);

Serial.println(pattern);
  
}

//pattern 2 in blue
void pattern5()
{
if(led>prevled)
{
   for(int i=prevled-1;i<=led;i++)
   {
    pixels.setPixelColor(i,pixels.Color(0,0,255));

     pixels.setBrightness(brightness);
    pixels.show();
   }
   delay(10);
}

if(led<prevled)
{
   for(int i=prevled;i>=led;i--)
   {
 pixels.setPixelColor(i,pixels.Color(0,0,0));
  pixels.setBrightness(brightness);
pixels.show();
   }
   delay(10);

}
   
prevled=led;

  Serial.println(pattern);
}

//change brightnss according to the sound level - blue 
void pattern6(int lev,int maxi)
{

int b = map(lev,0,maxi,0,255); //map lev to a brightness 

for(int i=0;i<8;i++)
{
  pixels.setPixelColor(i,pixels.Color(0,0,255));
  pixels.setBrightness(b);
  pixels.show();
}

delay(10);




  Serial.println(pattern);
  
}


void pattern7()
{
int r = map(led,6,8,0,255);
int g = map(led,4,6,0,255);
int b = map(led,0,4,0,255);

if(led>prevled)
{
   for(int i=prevled-1;i<=led;i++)
   {
    pixels.setPixelColor(i,pixels.Color(r,g,b));

     pixels.setBrightness(brightness);
    pixels.show();
   }
   delay(10);
}

if(led<prevled)
{
   for(int i=prevled;i>=led;i--)
   {
 pixels.setPixelColor(i,pixels.Color(0,0,0));
  pixels.setBrightness(brightness);
pixels.show();
   }
   delay(10);
}



prevled=led;
  
}





//turn off led
void pattern8()
{
  for(int i=0;i<8;i++)
{
  pixels.setPixelColor(i,pixels.Color(0,0,0));
  pixels.show();
}
    Serial.println(pattern);
}



//////////////debouncing

boolean debounceButton(boolean state)
{
  boolean stateNow = digitalRead(button);
  if(state!=stateNow)
  {
    delay(10);
    stateNow = digitalRead(button);
  }
  return stateNow;
  
}

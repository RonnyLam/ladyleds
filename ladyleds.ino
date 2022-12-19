#include <Adafruit_NeoPixel.h>

const byte interruptPin = 3;

#define PIXEL_PIN    2  
#define PIXEL_COUNT 150 

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

int     mode     = 0;
unsigned long last_interrupt_time = 0;

void setup() {
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), modechange, RISING);
  strip.begin(); 
  strip.show();  
}

void loop() {
      switch(mode) {          
        case 0:
          colorWipe(strip.Color(  150,   127,   48), 10); //White
          break;
        case 5:
          rainbow(10);
          break;
        case 4:
          colorWipe(strip.Color(  0,   0, 255), 10);    // Blue
          break;
        case 2:
          colorWipe(strip.Color(  255,   0, 0), 10);    // Red
          break;
        case 6:   
          theaterChaseRainbow(50);
          break;
        case 7:   
          colorWipe(strip.Color(  255,   20, 147), 10);    // Pink
          break;
        case 3:   
          colorWipe(strip.Color(  128,   0, 255), 10);    // Purple
          break;
        case 1:   
          nightLight(strip.Color(  150,   127,   48), 5);    // White
          break;
      }
}


void modechange() {
 unsigned long interrupt_time = millis();
 if (interrupt_time - last_interrupt_time > 400) {
  if(++mode > 6) mode = 0;
  }
 last_interrupt_time = interrupt_time;
   
}

void nightLight(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { 
//    if (i > 46 && i < 87 && millis() - last_interrupt_time < 3600000) { //A
    if (i > 115 && millis() - last_interrupt_time < 3600000) { //E
      strip.setPixelColor(i, color);}    
    else {strip.setPixelColor(i, strip.Color(  0,   0, 0));}
    strip.show();     
    delay(wait);
  }
}        

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);         
    strip.show();                          
    delay(wait);                           
  }
}

void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  
    for(int b=0; b<3; b++) { 
      strip.clear();         
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); 
      }
      strip.show(); 
      delay(wait);  
    }
  }
}

void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { 
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); 
    delay(wait);  
  }
}

void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     
  for(int a=0; a<30; a++) {  
    for(int b=0; b<3; b++) { 
      strip.clear();         
      for(int c=b; c<strip.numPixels(); c += 3) {
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); 
        strip.setPixelColor(c, color); 
      }
      strip.show();                
      delay(wait);                 
      firstPixelHue += 65536 / 90; 
    }
  }
}

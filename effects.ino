
// effect that runs shortly and then passes onto the next effect
void ButtonClickEffect::tick(uint32_t t) {
  play_tone((t/ 50) *200, 100);
  float duration = 1000.0;
  
  uint32_t color = Adafruit_NeoPixel::Color(0, 0, 255 * (((float)t)/duration));
  leds.all(color);
  if(t>duration) {
    // reset leds
    leds.all(off);
    Serial.println("Move to next effect");
    runner.effect = this->next;
  }
}

// effect that runs shortly and then passes onto the next effect
void ResetEffect::tick(uint32_t t) {
  float duration = 2000.0;
  play_tone(2000 - (((float)t)/duration) * 2000, 100);
  
  uint32_t color = Adafruit_NeoPixel::Color(255 - 255 * (((float)t)/duration), 0, 0);
  leds.all(color);
  if(t>duration) {
    // reset leds
    leds.all(off);
    Serial.println("Reset");
    runner.reset();
    // wait a bit before beginning again
    delay(1500);
  }
}


void Strobo::tick(uint32_t t) {
  int steps = t / 300;
  leds.all(steps%2 ==0 ? off : red);
}


// randomly fils all pixels with a color
void RandomFill::tick(uint32_t t) {
  if(t< 100) { // init
     this->time_until_all_off = t; 
  }
  uint32_t time_until_all_off = 5000;
  if (t > this->last_reset_t + time_until_all_off) {
    this->last_reset_t = t;
    leds.all(off);
  }
  int rand_x = random(0, 2);
  int rand_y = random(0, 60);
  leds.setPixelColor(rand_x, rand_y, blue);
  leds.show();
}


void BaseFunctionEffect::tick(uint32_t t) {
  uint32_t color = 0;
  for(uint16_t x=0;x<2;x++) {
    for (uint16_t y=0;y<60;y++) {
      color = this->f(t, x, y);
      leds.setPixelColor(x, y, color);
    } 
  }
  leds.show();
}

uint32_t BaseFunctionEffect::f(uint32_t t, uint16_t x, uint16_t y) {
  return off;
}

uint32_t WalkerFill::f(uint32_t t, uint16_t x, uint16_t y) {
  uint32_t ms_per_step = 50;
  uint32_t step = t / ms_per_step;
  return off;
}

FunctionEffect::FunctionEffect(uint32_t (*function)(uint32_t, uint16_t, uint16_t)) {
  this->effect_function = function;
}

uint32_t FunctionEffect::f(uint32_t t, uint16_t x, uint16_t y) {
  return (this->effect_function)(t, x, y);
}

/**
 * Helper functions
 */

int sinusColor(uint16_t i, uint32_t time, uint16_t leds_per_wave, int speed) {
  return (1+sin((i/(float)leds_per_wave)*2*PI+time/(float)speed*PI))/(float)2*255;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return Adafruit_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return Adafruit_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return Adafruit_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}



/*
 * Functions
 */
uint32_t glowRed(uint32_t time, uint16_t x, uint16_t y) {
  float speed = 400;
  return Adafruit_NeoPixel::Color((1+sin(time/speed*PI))/2*255, 0, 0);
}

// glows 6 colors after another
uint32_t glowColors(uint32_t time, uint16_t x, uint16_t y) {
  float speed = 400; // ms per glow
  int color = (1+sin(time/speed*PI))/2 * 255;
  // glow 6 colors after another
  int n = ((int)(time / speed)) % 6;
  Serial.print("glowColors: ");
  Serial.println(n);

  return Adafruit_NeoPixel::Color(
    n == 0 || n == 3 || n == 5 ? color : 0,
    n == 1 || n == 3 || n == 4 ? color : 0,
    n == 2 || n == 5 || n ==4 ? color : 0
  );
}


// shows a cool color wheel
uint32_t colorWheel(uint32_t time, uint16_t speed, uint16_t x, uint16_t y, int pixel_wheel_size) {
  uint16_t step = time / (float)speed;
  return Wheel(((y * 256 / pixel_wheel_size + step) & 255));
}

uint32_t colorFade(uint32_t time, uint16_t x, uint16_t y) {
  uint16_t speed = 20; // ms per color change
  return colorWheel(time, speed, 1, 1, 60);
}

uint32_t colorWheelFull(uint32_t time, uint16_t x, uint16_t y) {
  uint16_t speed = 10; // ms per step
  return colorWheel(time, speed, x, y, 60);
}

uint32_t colorWheelHighRes(uint32_t time, uint16_t x, uint16_t y) {
  uint16_t speed = 10; // ms per step
  return colorWheel(time, speed, x, y, 20);
}

uint32_t colorWheel2(uint32_t time, uint16_t x, uint16_t y) {
    int speed = 500;
    uint16_t leds_per_wave = 30;
    uint16_t i = y + x * 15;
    return Adafruit_NeoPixel::Color(
      sinusColor(i, time, leds_per_wave, speed),
      sinusColor(i+(leds_per_wave/6)*2, time, leds_per_wave, speed),
      sinusColor(i+(leds_per_wave/6), time, leds_per_wave, speed)
    );
}


/**
 * Knight rider
 
 
 
uint32_t knightRider(uint32_t time, uint16_t x, uint16_t y) {
  int speed = 50;
  int tail = 5; // 5 pixels tail
  uint16_t current_y = (time / speed %) 120;
  if (current_y >=60) {
    // move backward
    current_y = 120 - current_y;
  }
  return redKnightRiderLight(x, y, current_y, tail);
}


void redKnightRiderLight(uint16_t x uint16_t y, uint16_t current_y, int tail) {
  if (y<current_y - tail || y>current_y + tail) {
    return off; 
  }
  int pos = (y-currenty)
  uint32_t c = Adafruit_NeoPixel.Color((int)(100 - ((100/tail)*pos)), 0, 0);
  if(y-current_y>=0) {
    strip.setPixelColor(i-x, c);
  }
  if(i+x<num) {   
    strip.setPixelColor(i+x, c);
  }
  return red;
}

void knightRider(int wait, int tail) {
  for(uint16_t i=0; i<num; i++) {
      redLight(i, tail);
      strip.show();
      delay(wait);
  }
  for(uint16_t i=num-1; i>0; i--) {
      redLight(i, tail);
      strip.show();
      delay(wait);
  }
  all(off);
}

void talk(int wait) {
   mouth(5, wait);
   mouth(10, wait);
   mouth(9, wait);
   mouth(3, wait); 
}

void mouth(int n, int wait) {
  uint16_t x = num/2;
  for(int i=1;i<n;i++) {
    redLight(x, i);
    strip.show();
    delay(wait);
    all(off);
  }
  for(int i=n-1;i>0;i--) {
    redLight(x, i);
    strip.show();
    delay(wait);
    all(off);
  }
}

*/

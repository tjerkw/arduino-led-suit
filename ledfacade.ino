

/**
 * All led strips
 */

uint16_t num_pixels = 30;
Adafruit_NeoPixel lb_strip = Adafruit_NeoPixel(
  num_pixels,
  PIN_STRIP_LEFT_BOTTOM,
  NEO_GRB + NEO_KHZ800
);
Adafruit_NeoPixel rb_strip = Adafruit_NeoPixel(
  num_pixels,
  PIN_STRIP_RIGHT_BOTTOM,
  NEO_GRB + NEO_KHZ800
);
Adafruit_NeoPixel lt_strip = Adafruit_NeoPixel(
  num_pixels,
  PIN_STRIP_LEFT_TOP,
  NEO_GRB + NEO_KHZ800
);
Adafruit_NeoPixel rt_strip = Adafruit_NeoPixel(
  num_pixels,
  PIN_STRIP_RIGHT_TOP,
  NEO_GRB + NEO_KHZ800
);

Adafruit_NeoPixel strips[] = {
  lb_strip, rb_strip, lt_strip, rt_strip
};


void LedFacade::setPixelColor(uint16_t x, uint16_t y, uint32_t color) {
  Adafruit_NeoPixel* strip = &lt_strip;
  if(x==0) {
    strip = y>30 ? &lt_strip : &lb_strip;
  } else {
    strip = y>30 ? &rt_strip : &rb_strip;

  }
  strip->setPixelColor(y>30 ? y-30 : y, color);
}
void LedFacade::show() {
  for(int i=0;i<4;i++) {
    strips[i].show();
  }
}
void LedFacade::begin() {
  for(int i=0;i<4;i++) {
    strips[i].begin();
  }
}
void LedFacade::all(uint32_t color) {
  for(int i=0;i<4;i++) {
    for(uint16_t j=0;j<num_pixels;j++) {
      strips[i].setPixelColor(j, color);
    }
  }
  this->show();
}

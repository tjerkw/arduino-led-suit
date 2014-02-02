
uint32_t off = Adafruit_NeoPixel::Color(0, 0, 0);
uint32_t red = Adafruit_NeoPixel::Color(255, 0, 0);
uint32_t green = Adafruit_NeoPixel::Color(0, 255, 0);
uint32_t blue = Adafruit_NeoPixel::Color(0, 0, 255);
uint32_t yellow = Adafruit_NeoPixel::Color(255, 255, 0);
uint32_t white = Adafruit_NeoPixel::Color(255, 255, 255);

class LedFacade {
public:
  void setPixelColor(uint16_t x, uint16_t y, uint32_t color);
  void show();
  void all(uint32_t color);
  void begin();
};

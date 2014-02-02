#import "effects.h"

class Runner {
public:
  Runner();
  void reset();
  void toggleActive();
    
  uint32_t sleep_time;
  float speed_factor;
  // can be used to activate or not
  bool active;
  void loop();
  // the current active ffect
  Effect* effect;
  uint32_t time;
};

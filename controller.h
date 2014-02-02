
class Controller {
public:
  Controller();
  void tick();
  boolean internalTick();
  void onPress(int button, boolean is_repeat);
private:
  int last_code;
  int current_effect;
};

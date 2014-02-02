
class Effect {
public:
  Effect() {}
  virtual void tick(uint32_t t) {}
};

/**
 * Effects that execute after a button click
 */
class ButtonClickEffect : public Effect {
public:
  virtual void tick(uint32_t t);
  Effect* next;
};

class ResetEffect : public Effect {
public:
  virtual void tick(uint32_t t);
};


/**
 * Main effects
 */

class Strobo : public Effect {
public:
  void tick(uint32_t t);
};

class RandomFill : public Effect {
private:
  uint32_t last_reset_t;
public:
  void tick(uint32_t t);
};

class BaseFunctionEffect : public Effect {
public:
  BaseFunctionEffect() {}
  void tick(uint32_t t);
  virtual uint32_t f(uint32_t t, uint16_t x, uint16_t y);
};

class FunctionEffect : public BaseFunctionEffect {
public:
  FunctionEffect(uint32_t (*function)(uint32_t, uint16_t, uint16_t));
  uint32_t f(uint32_t t, uint16_t x, uint16_t y);
private:
  uint32_t (*effect_function)(uint32_t, uint16_t, uint16_t);
};

class WalkerFill : public BaseFunctionEffect {
public:
  uint32_t f(uint32_t t, uint16_t x, uint16_t y);
private:
  uint16_t current_fil_pos;
};

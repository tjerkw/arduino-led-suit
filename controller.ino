 
decode_results results;

Controller::Controller() {
  this->last_code = -1;
  this->current_effect = 0;
}

void Controller::tick() {

  if (irrecv.decode(&results)) {
    // omg i got something, somebody is trying to send commands, try to get the singal
    irrecv.resume();
    unsigned long temp_t = millis();
    
    while(millis()-temp_t < 200) {
      
      if (this->internalTick()) {
          // still pressing a button so wait longer
         temp_t = millis(); 
      }
    }
    // unset repeat code
    this->last_code = -1;
  }
}


boolean Controller::internalTick() {
  if (irrecv.decode(&results)) {
    int count = results.rawlen;
    if (results.decode_type == NEC) {
      Serial.print("NEC Remote recv: ");
      Serial.println(results.value, HEX);
      if (results.value == REPEAT_PREV) {
        if (this->last_code != -1) {
          this->onPress(this->last_code, true);
        }
      } else {
        this->last_code = results.value;
        this->onPress(results.value, false);
      }
    } else {
      Serial.print("Unknown encoding: ");
      Serial.print(results.value, HEX);
      Serial.print(" (");
      Serial.print(results.bits, DEC);
      Serial.println(" bits)");
      
      
      this->onPress(results.value, false);
    }
    
    // receive the next value
    irrecv.resume();
    return true;
  }
  return false;
}

void Controller::onPress(int button, boolean is_repeat) {
  Serial.println("onPress");
  // indicare a button is pressed
  play_tone(button * 10, is_repeat ? 100 : 200);
  switch (button) {
    case SAMSUNG_VOL_UP:
    case UP:
      runner.speed_factor += 0.1;
      // high tone indicate speed up;
      play_tone(200+runner.speed_factor * 1000, 200); 
      break;
      
    case SAMSUNG_VOL_DOWN:
    case DOWN:
      runner.speed_factor -= 0.1;

      if (runner.speed_factor < 0.0) {
        runner.speed_factor = 0.0; 
      }
      play_tone(200+runner.speed_factor * 1000, 200); 
      break;
      
    case SAMSUNG_PROG_UP:
    case LEFT:
      Serial.println("Change to next:");
      this->current_effect = (this->current_effect + 1) % num_effects;
      Serial.println(this->current_effect);
      change_effect.next = effects[this->current_effect];
      
      Serial.println((int)change_effect.next);
      runner.effect = &change_effect;
      // reset time for the effect
      runner.time = 0;
      break;
      
    case SAMSUNG_PROG_DOWN:
    case RIGHT:
      Serial.println("Change to prev:");
      this->current_effect = (this->current_effect - 1) % num_effects;
      if (this->current_effect < 0) {
        this->current_effect += num_effects;  
      }
      Serial.println(this->current_effect);
      
      change_effect.next = effects[this->current_effect];
      runner.effect = &change_effect;
      // reset time for the effect
      runner.time = 0;
      break;
      
    case SETUP:
      Serial.println("Reset runner");;
      runner.effect = &reset_effect;
      runner.time = 0;
      break;
  }
}


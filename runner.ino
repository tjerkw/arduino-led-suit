
Runner::Runner() {
  this->reset();
}

void Runner::reset() {
  this->sleep_time = 20;
  this->active = true;
  this->time = 0;
  Serial.println("resetting");
  this->effect = effects[0];
  this->speed_factor = 1.0; 
}

void Runner::loop() {
  while(true) {
    if (this->active) {
      Serial.print("time:");
      Serial.println(this->time);
      (this->effect)->tick(this->time);
    }
    
    controller.tick();
    // sleep, but keep recv ir remote signals
    delay(this->sleep_time);
    this->time += ((double)this->sleep_time) * this->speed_factor;
  }
}



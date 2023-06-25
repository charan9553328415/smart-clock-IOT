int hour = 0;
int minute = 0;
int second = 0;
int temp_counter = 0;

/////////////////////////////////////////////////////////////////////////////

void time_display_combined() {
  int display_part1 = hour;
  int display_part2 = minute;

  temp_counter = (temp_counter + 1) % 6;
  if(temp_counter == 4 || temp_counter == 5) {
    if(temp_counter == 4) {
      temperature = dht.readTemperature();
      humidity = dht.readHumidity();
    }
    display_part1 = (int)humidity;
    display_part2 = (int)temperature;

    if (isnan(display_part1) || isnan(display_part2)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      tone(buzzer, 1000, 200);
      delay(250);
      return;
    }

    ledcWrite(rgb_led_red, 255 - rgb_led_brightness);
  }
  else {
    ledcWrite(rgb_led_red, 255);
  }

  for(int i=0; i<1000/fliker; i+=4) {
    digit_display(0, display_part1/10); 
    digit_display(1, display_part1%10);  
    digit_display(2, display_part2/10);  
    digit_display(3, display_part2%10);
  }

  if(is_led_on) {
    ledcWrite(rgb_led_blue, 255 - rgb_led_brightness);
    ledcWrite(rgb_led_green, 255);
  }
  else {
    ledcWrite(rgb_led_green, 255 - rgb_led_brightness);
    ledcWrite(rgb_led_blue, 255);
  }
  is_led_on = !is_led_on;
}


/////////////////////////////////////////////////////////////////////////

void wifi_time_display() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("No time available (yet)");
    play_tone(tone_warning, sizeof(tone_warning));
    return;
  }

  char timeSecond[3];
  strftime(timeSecond, 3, "%S", &timeinfo);
  second = 10 * (timeSecond[0] - '0') + (timeSecond[1] - '0');
  char timeMinute[3];
  strftime(timeMinute, 3, "%M", &timeinfo);
  minute = 10 * (timeMinute[0] - '0') + (timeMinute[1] - '0') + 30;
  char timeHour[3];
  strftime(timeHour, 3, "%I", &timeinfo);
  hour = 10 * (timeHour[0] - '0') + (timeHour[1] - '0') + 5;

  time_display_combined();
}

///////////////////////////////////////////////////////////////////////////

void time_display() {
  if(second >= 60) {
    second = 0;
    minute++;
  }
  if(minute >= 60){
    minute = 0;
    hour++;
  }
  if(hour >= 13) {
    hour = 0;
  }

  second++;

  time_display_combined();
}
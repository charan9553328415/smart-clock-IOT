int push_switch = 13;
int stopwatch_minute = 0;
int stopwatch_second = 0;

void stopwatch() {
  if(digitalRead(push_switch)) {
    if(stopwatch_second == 0) {
      if(stopwatch_minute == 0) {
        play_tone(tone_alarm, sizeof(tone_alarm));
      }
      else {
        stopwatch_minute--;
        stopwatch_second = 60;
      }
    }
    else {
      stopwatch_second--;
    }
    
    for(int i=0; i<1000/fliker; i+=4) {
      digit_display(0, stopwatch_minute/10); 
      digit_display(1, stopwatch_minute%10);  
      digit_display(2, stopwatch_second/10);  
      digit_display(3, stopwatch_second%10);
    }
  }
  else {
    time_set(stopwatch_minute, 60, stopwatch_second, 60);
  }
}
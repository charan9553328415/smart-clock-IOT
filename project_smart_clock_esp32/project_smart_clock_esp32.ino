#include "setup_dht_rgb_7segment_buzzer_custom.h"
#include "time_display_custom.h"
#include "time_set_custom.h"
#include "stopwatch_custom.h"

#include "thingProperties.h"


void setup() {
  Serial.begin(115200);
  delay(1500); 
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  rgb_led_setup();
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
  
  for(int i=0; i<7; i++)
    pinMode(lpin[i], OUTPUT);
  for(int i=0; i<4; i++)
   	pinMode(cpin[i], OUTPUT);
  for(int i=0; i<4; i++)	
    digitalWrite(cpin[i], HIGH);
  

  pinMode(buzzer, OUTPUT);
  pinMode(push_switch, INPUT);

  play_tone(tone_start, sizeof(tone_start));

  dht.begin();
}

void loop() {
  ArduinoCloud.update();

  if(balarm) {
    if(hour == alarm_hour && minute == alarm_minute) {
      play_tone(tone_alarm, sizeof(tone_alarm));
      balarm = 0;
    }
  }

  temp_menu = map(analogRead(knob0), 0, 4095, 0, 5);
  if(temp_menu != menu) {
    tone(buzzer, 2000, 100);
    menu = temp_menu;
  }

  Serial.print("menu: ");
  Serial.println(menu);

  switch(menu) {  
    case 0:
      delay(500);
        ledcWrite(rgb_led_red, 255);
        ledcWrite(rgb_led_green, 255);
        ledcWrite(rgb_led_blue, 255);
      break;
    case 1:
      time_display();
      break;
    case 2:
      time_set(hour, 12, minute, 60);
      break;
    case 3:
      time_set(alarm_hour, 12, alarm_minute, 60);
      break;
    case 4:
      stopwatch();
      break;
    case 5:
      wifi_time_display();
      break;
  }
}


void onAlarmHourChange()    { tone(buzzer, 3000, 100); }
void onAlarmMinuteChange()  { tone(buzzer, 3000, 100); }
void onBalarmChange()       { tone(buzzer, 3000, 100); }


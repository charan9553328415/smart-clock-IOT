//////////////////////////////////////////// DHT
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float temperature = 0.0;
float humidity = 0.0;

//////////////////////////////////////////////// rgb

bool is_led_on = 0;
int rgb_led_red_pin = 5;
int rgb_led_green_pin = 23;
int rgb_led_blue_pin = 22;

int rgb_led_red = 0;
int rgb_led_green = 1;
int rgb_led_blue = 2;

int rgb_led_brightness = 50;  // 0 to 255

void rgb_led_setup() {
  ledcSetup(rgb_led_red, 5000, 8);
  ledcSetup(rgb_led_green, 5000, 8);
  ledcSetup(rgb_led_blue, 5000, 8);

  ledcAttachPin(rgb_led_red_pin, rgb_led_red);
  ledcAttachPin(rgb_led_green_pin, rgb_led_green);
  ledcAttachPin(rgb_led_blue_pin, rgb_led_blue);

  ledcWrite(rgb_led_red, 255);
  ledcWrite(rgb_led_green, 255);
  ledcWrite(rgb_led_blue, 255);
}

/////////////////////////////////////////////// 7 segment display


int lpin[] = {25,26,21,14,27,33,32};	//LED pins
int cpin[] = {19,18,17,16};				    //Control pins
int numbers[10][7] = {
  {1,1,1,1,1,1,0},	//0
  {0,1,1,0,0,0,0},	//1
  {1,1,0,1,1,0,1},	//2
  {1,1,1,1,0,0,1},	//3
  {0,1,1,0,0,1,1},	//4
  {1,0,1,1,0,1,1},	//5
  {1,0,1,1,1,1,1},	//6
  {1,1,1,0,0,0,0},	//7
  {1,1,1,1,1,1,1},	//8
  {1,1,1,1,0,1,1},  //9
};
int fliker = 5; 

void digit_display(int p, int num) {      // control pin, number(0-9)
  digitalWrite(cpin[p], LOW);
  
  for(int i=0; i<7; i++)	
    digitalWrite(lpin[i], numbers[num][i]);
  
  delay(fliker);
  digitalWrite(cpin[p], HIGH);
}

///////////////////////////////////////////////////////// buzzer

int buzzer = 12;

int tone_error[][3] = {
  {1000, 200, 250},
  {2000, 200, 250},
  {3000, 200, 1000}
};

int tone_warning[][3] = {
  {3000, 200, 250},
  {2000, 200, 1000}
};

int tone_success[][3] {
  {3000, 200, 250},
  {2000, 200, 250},
  {1000, 200, 1000}
};

int tone_start[][3] = {
  {2000, 200, 250},
  {3000, 200, 1000}
};

int tone_alarm[][3] {
  {2000, 100, 150},
  {2000, 100, 500},
  {2000, 100, 150},
  {2000, 100, 500},
  {2000, 100, 150},
  {2000, 100, 500},
  {2000, 100, 150},
  {2000, 100, 500},
  {2000, 100, 150},
  {2000, 100, 500}
};

void play_tone(int tone_var[][3], int arr_size) {
  int size_notes = arr_size / sizeof(tone_var[0]);
  for(int i=0; i<size_notes; i++) {
    tone(buzzer, tone_var[i][0], tone_var[i][1]);
    delay(tone_var[i][2]);
  }
}


///////////////////////////////////////////////////// others
////////// ntp, menu, alarm, potentiometers

const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long  gmtOffset_sec = 19800;
const int   daylightOffset_sec = 0;

int menu = 0;
int temp_menu = 0;

int alarm_hour = 0;
int alarm_minute = 0;
bool balarm = 0;

int knob0 = 34;
int knob1 = 39;
int knob2 = 36;

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

#define SECRET_SSID "aaa"
#define SECRET_OPTIONAL_PASS "88888888"
#define SECRET_DEVICE_KEY "7BZOEUOQTPLJDJCXTHG0"

const char DEVICE_LOGIN_NAME[]  = "546fa0e3-6a26-4460-b30d-f412977f2821";

const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]         = SECRET_DEVICE_KEY;    // Secret device password

void onAlarmHourChange();
void onAlarmMinuteChange();
void onBalarmChange();

/*  declared in setup
int alarm_hour;
int alarm_minute;
bool balarm;
*/

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(humidity, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(temperature, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(alarm_hour, READWRITE, ON_CHANGE, onAlarmHourChange);
  ArduinoCloud.addProperty(alarm_minute, READWRITE, ON_CHANGE, onAlarmMinuteChange);
  ArduinoCloud.addProperty(balarm, READWRITE, ON_CHANGE, onBalarmChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

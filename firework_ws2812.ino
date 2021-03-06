/*
   祝大家新年快乐！
*/
#include <ArduinoOTA.h>//无线升级,便于调试

#include <FastLED.h>
#define STASSID "abcdefg"//wifi名字
#define STAPSK  "qwerpoi"//wifi密码
//灯珠数量
#define NUM_LEDS 72

//ESP8266开发板 引脚GPIO 5
#define DATA_PIN 5
int pluse; //每节发送的灯珠数量

CRGB leds[NUM_LEDS];
int H;//颜色
int delta;
void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
  // END of Trinket-specific code.
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  ArduinoOTA.begin();
}

void loop() {
  ArduinoOTA.handle();
  pluse = random(4, 10);//每节灯珠数量随机4-9
  H = random(10, 255);//每节效果的颜色
  delta = int(200 / pluse);
  for (int s = 0; s < pluse + 5; s++)//0-pluse-1刷新颜色
  {
    leds[0] = CHSV(H, 255, 200 - delta * s);
    if (s >= pluse) //pluse-pluse+4 5个灯珠熄灭
    {
      leds[0] = CHSV(H, 255, 0);
    }
    for (int i = NUM_LEDS - 1 ; i > 0 ; i--)
    {
      leds[i] = leds[i - 1];
    }
    FastLED.show();
    delay(50 - pluse);
  }



}

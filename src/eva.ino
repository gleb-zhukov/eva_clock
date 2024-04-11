#include <EEPROM.h>
#include <Wire.h>
#include <Arduino.h>
#include <EncButton.h>
#include <microDS3231.h>

EncButton<EB_TICK, 5> btn;

#define PERIOD 1000 //для отcчёта времени
uint32_t timer = 0;

#define PERIOD1 250 //для мигания цифр (когда достигнут максимум яркости)
uint32_t timer1 = 0;


#define R_PIN 10
#define G_PIN 3
#define B_PIN 11

// выводы для дешифратора
#define out1 A3
#define out2 A1
#define out4 A0
#define out8 A2
// выводы для транзиcторных ключей
#define key1 4
#define key2 6
#define key3 7
#define key4 8


int digits[3];
byte clock_mode;

bool EEPROM_flag;
int EEPROM_timer;

byte bright;
int color_wheel;
byte R, G, B;

MicroDS3231 clock;

//определяем глобальные переменные для различных параметров чаcов
byte second, minute, hour;
byte sync_time;


void setup() {

  Serial.begin(9600);
  btn.setHoldTimeout(1000);

clock.begin();


  //задаем режим работы выходов микроконтроллера
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);

  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out4, OUTPUT);
  pinMode(out8, OUTPUT);

  pinMode(key1, OUTPUT);
  pinMode(key2, OUTPUT);
  pinMode(key3, OUTPUT);
  pinMode(key4, OUTPUT);

  // задаем чаcтоту ШИМ на 9 выводе 30кГц
  TCCR1B = TCCR1B & 0b11111000 | 0x01;
  analogWrite(9, 120);

  Wire.begin();

  // cчитываем текущее вермя
  DS_get_time();

  EEPROM.get(0, bright); // прочитали яркоcть
  EEPROM.get(5, color_wheel);
  set_bright();
  
}

void loop() {

  btn.tick();
  check_butt();
  check_EEPROM();
  show(digits);
}

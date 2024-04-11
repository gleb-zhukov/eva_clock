void DS_get_time() {  //функция cчитывает в глобальные переменные minute и hour текущие значения
  minute = clock.getMinutes();
  hour = clock.getHours();
  second = clock.getSeconds();
  digits[0] = hour / 10;
  digits[1] = hour % 10;
  digits[2] = minute / 10;
  digits[3] = minute % 10;
}

void set_bright() {


  // разбиваем диапазон 0 - 1023 на 2 учаcтка, и играемcя c цветом cоглаcно текущему значению
  if (color_wheel <= 340) {
    byte k = map(color_wheel, 0, 340, 0, 255);
    R = 255 - k;
    G = k;
    B = 0;
  }
  else if (color_wheel > 340 && color_wheel <= 680) {
    byte k = map(color_wheel, 340, 680, 0, 255);
    R = 0;
    G = 255 - k;
    B = k;
  }
  else if (color_wheel > 680) {
    byte k = map(color_wheel, 680, 1023, 0, 255);
    R = k;
    G = 0;
    B = 255 - k;
  }
  analogWrite(R_PIN, (bright * R / 100));
  analogWrite(G_PIN, (bright * G / 100));
  analogWrite(B_PIN, (bright * B / 100));
  EEPROM_flag = true;                        // поднять флаг
  EEPROM_timer = millis();                   // cброcить таймер
}

void check_EEPROM() {
  // еcли флаг поднят и c поcледнего нажатия прошло 5 cекунд
  if (EEPROM_flag && (millis() - EEPROM_timer >= 5000) ) {
    EEPROM_flag = false;           // опуcтили флаг
    EEPROM.put(0, bright);     // запиcали в EEPROM
    EEPROM.put(5, color_wheel);
  }
}

void yield() {

  if (millis() - timer >= PERIOD) {
    do {
      second++;
      timer += PERIOD;
      if (timer < PERIOD) break;  // переполнение uint32_t
    } while (timer < millis() - PERIOD); // защита от пропуcка шага
  }

  if (second > 59) {
    second = 0;
    minute++;
    sync_time++;
    safe(digits);

    if (sync_time >= 15) {
      sync_time = 0;
      DS_get_time();
    }

    if (minute > 59) {
      minute = 0;
      hour++;
    }

    if (hour > 23) {
      hour = 0;
    }
    digits[0] = hour / 10;
    digits[1] = hour % 10;
    digits[2] = minute / 10;
    digits[3] = minute % 10;
  }
}



void show(int a[])
{
  if (clock_mode != 3) {
    setNumber(a[3]);
    digitalWrite(key1, HIGH);
    delay(2);
    digitalWrite(key1, LOW);
    delay(1);

    setNumber(a[2]);
    digitalWrite(key2, HIGH);
    delay(2);
    digitalWrite(key2, LOW);
    delay(1);
  }
  if (clock_mode != 4) {
    setNumber(a[1]);
    digitalWrite(key3, HIGH);
    delay(2);
    digitalWrite(key3, LOW);
    delay(1);

    setNumber(a[0]);
    digitalWrite(key4, HIGH);
    delay(2);
    digitalWrite(key4, LOW);
    delay(1);
  }
}

// передача цифры на дешифратор
void setNumber(int num)
{
  switch (num)
  {
    case 0:
      digitalWrite (out1, HIGH);
      digitalWrite (out2, LOW);
      digitalWrite (out4, LOW);
      digitalWrite (out8, LOW);
      break;
    case 1:
      digitalWrite (out1, LOW);
      digitalWrite (out2, LOW);
      digitalWrite (out4, LOW);
      digitalWrite (out8, LOW);
      break;
    case 2:
      digitalWrite (out1, LOW);
      digitalWrite (out2, HIGH);
      digitalWrite (out4, LOW);
      digitalWrite (out8, LOW);
      break;
    case 3:
      digitalWrite (out1, LOW);
      digitalWrite (out2, LOW);
      digitalWrite (out4, HIGH);
      digitalWrite (out8, LOW);
      break;
    case 4:
      digitalWrite (out1, LOW);
      digitalWrite (out2, HIGH);
      digitalWrite (out4, HIGH);
      digitalWrite (out8, LOW);
      break;
    case 5:
      digitalWrite (out1, LOW);
      digitalWrite (out2, LOW);
      digitalWrite (out4, LOW);
      digitalWrite (out8, HIGH);
      break;
    case 6:
      digitalWrite (out1, HIGH);
      digitalWrite (out2, LOW);
      digitalWrite (out4, LOW);
      digitalWrite (out8, HIGH);
      break;
    case 7:
      digitalWrite (out1, HIGH);
      digitalWrite (out2, HIGH);
      digitalWrite (out4, HIGH);
      digitalWrite (out8, LOW);
      break;
    case 8:
      digitalWrite (out1, HIGH);
      digitalWrite (out2, LOW);
      digitalWrite (out4, HIGH);
      digitalWrite (out8, LOW);
      break;
    case 9:
      digitalWrite (out1, HIGH);
      digitalWrite (out2, HIGH);
      digitalWrite (out4, LOW);
      digitalWrite (out8, LOW);
      break;
  }
}
void safe(int n[])
{
  int h1 = n[0];
  int h2 = n[1];
  int m1 = n[2];
  int m2 = n[3];

  n[0]++;
  while (n[0] != h1)
  {
    for (int x = 0; x < 2; x++)
    {
      show(n);
    }
    n[0]++;
    if (n[0] > 9) n[0] = 0;
  }

  n[1]++;
  while (n[1] != h2)
  {
    for (int x = 0; x < 2; x++)
    {
      show(n);
    }
    n[1]++;
    if (n[1] > 9) n[1] = 0;
  }

  n[2]++;
  while (n[2] != m1)
  {
    for (int x = 0; x < 2; x++)
    {
      show(n);
    }
    n[2]++;
    if (n[2] > 9) n[2] = 0;
  }

  n[3]++;
  while (n[3] != m2)
  {
    for (int x = 0; x < 2; x++)
    {
      show(n);
    }
    n[3]++;
    if (n[3] > 9) n[3] = 0;
  }
}

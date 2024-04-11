
void check_butt() {

  if (btn.held())
  {
    clock_mode++;
    if (clock_mode >= 5) clock_mode = 0;
    switch (clock_mode) {
      case 0:
        {
          safe(digits);
        }
        break;
      case 1:
        {
          byte last_bright = bright;
          for (byte i = bright; i < 100; i++) {
            bright = i;
            set_bright();
            show(digits);
          }
          for (byte i = 99; i > 5; i--) {
            bright = i;
            set_bright();
            show(digits);
          }
          for (byte i = 5; i < last_bright; i++) {

            bright = i;
            set_bright();
            show(digits);
          }
          bright = last_bright;
          set_bright();
          show(digits);
        }
        break;
      case 2:
        {
          byte last_bright = bright;
          if (bright == 0) bright = 10;
          int last_wheel = color_wheel;
          for (int i = last_wheel; i < 1023; i += 10) {
            color_wheel = i;
            set_bright();
            show(digits);
          }
          for (int i = 1; i < last_wheel; i += 10) {
            color_wheel = i;
            set_bright();
            show(digits);
          }
          bright = last_bright;
          set_bright();
        }
        break;
      case 3:
        {
          safe(digits);
        }
        break;
      case 4:
        {
          safe(digits);
        }
        break;
    }
  }

  if (btn.click()) {
    switch (clock_mode) {
      case 0:
        break;
      case 1:
        {
          bright += 5;
          if (bright > 100) bright = 0;
          if (bright == 100) {
            byte count = 0;
            while (count < 6) {
              show(digits);
              if (millis() - timer1 >= PERIOD1) {
               timer1 = millis();
                  count++;
                  if (bright == 0) bright = 100;
                  else bright = 0;
                  set_bright();
              }
            }
          }
          set_bright();
        }
        break;
      case 2:
        {
          color_wheel += 17;
          if (color_wheel >= 1024) color_wheel = 0;
          set_bright();
        }
        break;
      case 3:
        {
          hour++;
          second = 0;
          if (hour > 23) hour = 0;
          clock.setTime(0, minute, hour, 10, 12, 2022);
          digits[0] = hour / 10;
          digits[1] = hour % 10;
        }
        break;
      case 4:
        {
          minute++;
          second = 0;
          if (minute > 59) minute = 0;
          clock.setTime(0, minute, hour, 10, 12, 2022);
          digits[2] = minute / 10;
          digits[3] = minute % 10;
        }
        break;
    }
  }
}

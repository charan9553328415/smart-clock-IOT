int digit_select= 0;
int digit_set = 0;
int temp_digit_select = 0;
int temp_digit_set = 0;

void time_set(int &digit_part_1, int range_part_1, int &digit_part_2, int range_part_2) {
  
  temp_digit_select = map(analogRead(knob1), 0, 4095, 0, 3);
  if(temp_digit_select != digit_select) {
    tone(buzzer, 2000, 100);  
    digit_select = temp_digit_select;
  }

  temp_digit_set = map(analogRead(knob2), 0, 4095, 0, 9);
  if(temp_digit_set != digit_set) {
    tone(buzzer, 2000, 100);
    digit_set = temp_digit_set;

    switch(digit_select) {
      case 0:
        digit_part_1 = (digit_set % (range_part_1 / 10 + 1)) * 10;
        break;
      case 1:
        if(digit_part_1 >= 10)
          digit_part_1 = 10 * (digit_part_1 / 10) + digit_set;
        else
          digit_part_1 = digit_set;
        break;
      case 2:
        digit_part_2 = (digit_set % (range_part_2 / 10 + 1)) * 10;
        break;
      case 3:
        if(digit_part_2 >= 10)
          digit_part_2 = 10 * (digit_part_2 / 10) + digit_set;
        else
          digit_part_2 = digit_set;
        break;
    }
  }

  int time_values[] = {digit_part_1/10, digit_part_1%10, digit_part_2/10, digit_part_2%10};
  digit_display(digit_select, time_values[digit_select]);
  digit_display(0, digit_part_1/10);
  digit_display(digit_select, time_values[digit_select]);
  digit_display(1, digit_part_1%10);
  digit_display(digit_select, time_values[digit_select]);
  digit_display(2, digit_part_2/10);
  digit_display(digit_select, time_values[digit_select]);
  digit_display(3, digit_part_2%10);
}
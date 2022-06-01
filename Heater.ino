
int left_led[] = {10, 11, 12, 13, 14, 15, 16};
int right_led[] = {2, 3, 4, 5, 6, 7, 8};
int mapper[10][7] = {
  {1,2,3,4,5,6},
  {2,3},
  {1,2,4,5,7},
  {1,2,3,4,7},
  {2,3,6,7},
  {1, 3, 4, 6, 7},
  {1, 3, 4, 5, 6, 7},
  {1, 2, 3},
  {1, 2, 3, 4, 5, 6, 7},
  {1, 2, 3, 4, 6, 7}
  };

int lm35 = A0;
int heater_state_pin = 9;
int heater_state = LOW;
int heat_target = 80; // Celesius
int temperature;

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 7; i++) {
    pinMode(left_led[i], OUTPUT);
    pinMode(right_led[i], OUTPUT);
  }
  pinMode(lm35, INPUT);
}

// Function to turn of a LED
void reset(int leds[7]) {
  for(int i = 0;  i< 7; i++) {
    digitalWrite(leds[i], LOW);
  }
}

// Function to display a single digit on a single LED
void set_digit(int segments[7], int number) {
  for(int i = 0; i < 7; i++) {
    if(mapper[number][i] == 0)
      break;
    digitalWrite(segments[mapper[number][i]-1], HIGH);
  }
}


// Function to display number (two digits) on two LEDs
void digit_to_leds(int digit, int led1, int led2) {
  reset(led1);
  reset(led2);
  int left_side = digit / 10;
  int right_side = digit % 10;
  set_digit(led1, left_side);
  set_digit(led2, right_side);
}

void loop() {
  int signal = analogRead(lm35);
  float mv = (signal / 1024.0) * 5000;
  int temperature = mv / 10.0;
  digit_to_leds(temperature, left_led, right_led);
  if(temperature > heat_target)
    heater_state = LOW;
  else
    heater_state = HIGH;
  digitalWrite(heater_state_pin, heater_state);
  delay(500);
}

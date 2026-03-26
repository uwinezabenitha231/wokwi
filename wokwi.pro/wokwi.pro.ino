#include <Keypad.h>

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {19, 18, 5, 17};
byte colPins[COLS] = {16, 4, 2, 15};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Buzzer pin
int buzzer = 23;

void setup() {
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);

    if (key == '#') {
      digitalWrite(buzzer, HIGH); // ON
    }
    else if (key == '*') {
      digitalWrite(buzzer, LOW);  // OFF
    }
  }
}

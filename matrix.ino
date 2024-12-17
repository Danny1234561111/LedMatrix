#define LED_A 3  
#define LED_B 4  
#define LED_C 5  
#define LED_D 6  

byte STATE_OFF = 0b00000000;  
byte STATE_ON = 0b11000000;  
byte STATE_ST = 0b10010000;  
byte STATE_ND = 0b10100000;  
byte STATE_RD = 0b01010000;  
byte STATE_TH = 0b01100000;  
byte STATE_ST_ND = 0b10000000;  
byte STATE_ND_TH = 0b11100000;  
byte STATE_RD_TH = 0b01000000;  
byte STATE_ST_RD = 0b11010000;  
byte STATE_ST_TH = 0b10010110;  
byte STATE_ND_RD = 0b10100101;  
byte STATE_ST_ND_RD = 0b10000101;  
byte STATE_ST_ND_TH = 0b11101001;  
byte STATE_ST_RD_TH = 0b01001001;  
byte STATE_ND_RD_TH = 0b01001010;  

byte ledStates[16] = {STATE_OFF, STATE_ON, STATE_ST, STATE_ND, STATE_RD, STATE_TH,  
                      STATE_ST_ND, STATE_ND_TH, STATE_RD_TH, STATE_ST_RD,  
                      STATE_ST_TH, STATE_ND_RD, STATE_ST_ND_RD, STATE_ST_ND_TH,  
                      STATE_ST_RD_TH, STATE_ND_RD_TH};  

long blinkStartTime = 0;  
long lastStateChangeTime = 0;  
int currentIndex = 0;  
int ledPins[4] = {LED_A, LED_B, LED_C, LED_D};  

void setup() {  
  Serial.begin(9600);  
  for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {  
    pinMode(ledPins[i], OUTPUT);  
  }  
}  

void loop() {  
  if (millis() > lastStateChangeTime + 2000) {  
    lastStateChangeTime = millis();  
    currentIndex = (currentIndex + 1) % 16;  
  } else {  
    performCrossBlink(ledPins, ledStates[currentIndex], currentIndex, 2); // Увеличил длительность до 400 мс
  }  
}  

void performCrossBlink(int* pins, byte state, int chet, int duration) {  
  unsigned long currentMillis = millis();
  
  if (currentMillis <= blinkStartTime + duration / 2 || chet < 8) {  
    for (int i = 0; i < 4; i++) {  
      byte bitValue = (state >> (7 - i)) & 1;  
      digitalWrite(pins[i], bitValue);  
    }  
  } else if (currentMillis < blinkStartTime + duration) {  
    // Вторая половина времени
    for (int i = 0; i < 4; i++) {  
      byte bitValue = (state >> (3 - i)) & 1;  
      digitalWrite(pins[i], bitValue);  
    }  
  } else {  
    // Обновление времени мигания
    blinkStartTime = currentMillis;  
  }  
}


const int soundSensorPinD0 = 25;    // GPIO пин за D0 на звуковия сензор (цифров вход)
const int soundSensorPinA0 = 34;    // GPIO пин за A0 на звуковия сензор (аналогов вход)
const int lamp1 = 13;
const int lamp2 = 12;
const int lamp3 = 14;
const int lamp4 = 27;
const int lamp5 = 26;
const int lamp6 = 33;
int soundValue = 0;                 // Стойността на звука (от 0 до 1023)
int digitalSoundState = 0;          // Дигиталното състояние на сензора
int threshold = 10;                // Праг на силата на звука за аналоговото четене
unsigned long lastMillis = 0;       // Време за последно пляскане
unsigned long interval = 1000;      // Време за разпознаване на 2 пляскания (1 секунда)
static int clapCount = 0;           // Броя на засечените пляскания

void setup() {
  pinMode(soundSensorPinD0, INPUT);   // Дигитален пин за звуковия сензор
  pinMode(soundSensorPinA0, INPUT);   // Аналогов пин за звуковия сензор
  pinMode(lamp1, OUTPUT);
  pinMode(lamp2, OUTPUT);
  pinMode(lamp3, OUTPUT);
  pinMode(lamp4, OUTPUT);
  pinMode(lamp5, OUTPUT);
  pinMode(lamp6, OUTPUT);
  digitalWrite(lamp1, LOW);
  digitalWrite(lamp2, LOW);
  digitalWrite(lamp3, LOW);
  digitalWrite(lamp4, LOW);
  digitalWrite(lamp5, LOW);
  digitalWrite(lamp6, LOW);
  Serial.begin(115200);               // За дебъг
}

void loop() {
  // Четем дигиталния пин (D0) за бързо засичане на пик
  digitalSoundState = digitalRead(soundSensorPinD0); 

  // Четем аналоговата стойност от A0 (от 0 до 1023)
  soundValue = analogRead(soundSensorPinA0);  

  // Ако има звук (пляскане) на дигиталния вход (D0)
  if (digitalSoundState == HIGH) {
    lastMillis = millis();  // Нулираме времето
  }

  // Ако звукът премине прага в аналоговия вход (A0)
  if (soundValue > threshold && millis() - lastMillis < interval) {
    clapCount++;
    Serial.print("Clap detected: ");
    Serial.println(clapCount);
    
    if (clapCount == 2) {
      digitalWrite(lamp1, HIGH);
      digitalWrite(lamp2, HIGH);
      digitalWrite(lamp3, HIGH);
      digitalWrite(lamp4, HIGH);
      digitalWrite(lamp5, HIGH);
      digitalWrite(lamp6, HIGH);
      Serial.println("Lamp ON");
    } else if (clapCount == 3) {
      digitalWrite(lamp1, LOW);
      digitalWrite(lamp2, LOW);
      digitalWrite(lamp3, LOW);
      digitalWrite(lamp4, LOW);
      digitalWrite(lamp5, LOW);
      digitalWrite(lamp6, LOW);
      Serial.println("Lamp OFF");
      clapCount = 0;  // Рестартираме брояча на пляскания
    }
  }

  // Нулираме броя на плясканията, ако интервалът между тях е по-голям от зададения
  if (millis() - lastMillis > interval) {
    clapCount = 0; 
  }
}

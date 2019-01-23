// Aansluiten arduino;
int enA = 10; < ---- - dit is een PWN pin, op de mega alleen pin 2 t / m 13 gebruiken.
int in1 = 9;
int in2 = 8;
int buttonIn = 2; // <----- dit is een InteruptPin, op de mega alleen pin 2, 3, 18, 19, 20 of 21 gebruiken.
int buttonEnd = 18; // <----- dit is een InteruptPin, op de mega alleen pin 2, 3, 18, 19, 20 of 21 gebruiken.

//Arduino variablen;
unsigned long previousMillis = 0;
const long interval = 1000; // <---- Delay timer
volatile byte logFinished = LOW;
volatile byte logFed = LOW;
bool logFed = false;


//=============================================================================

void setup()
{
  //set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(buttonIn), startButton, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buttonEnd), endButton, CHANGE);
  Serial.begin(9600);
}

//=============================================================================

void motorFuction()
{
  if (logFed) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 100);
    if (logFinished) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(enA, 255);
    }
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}

//=============================================================================

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    motorFunction();
  }
}

//=============================================================================

void endButton() {
  logFinished = !logFinished
}

//=============================================================================

void startButton() {
  logFed = !logFed
}



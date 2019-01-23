

// Aansluiten arduino;
int enA = 5; // < ---- - dit is een PWN pin
int in1 = 6;
int in2 = 7;
int relay = 12;
int buttonIn = 2;
int buttonEnd = 3;

//Arduino variablen;
unsigned long previousMillis = 0;
const long interval = 1000;
bool logFinished = LOW;
bool logFed = false;
int startTimer = 1000;
int useTimer = 0;
int randomiser = 0;


//=============================================================================

void setup()
{
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(buttonIn, INPUT);
  pinMode(buttonEnd, INPUT);

  Serial.begin(9600);
  digitalWrite(relay, 1);
}

//=============================================================================

void loop()
{

  Serial.print("LogFed: ");
  Serial.print(logFed);
  Serial.print(" LogFinished: ");
  Serial.println(logFinished);
  
  useTimer = startTimer;
  randomiser = random(startTimer / -2, startTimer / 2);
  useTimer += randomiser;

  if (digitalRead(buttonIn) == 1) {
    logFed = true;
  } else {
    logFed = false;
  }

  if (digitalRead(buttonEnd) == 1) {
    logFinished = true;
  } else if (digitalRead(buttonIn) == 0) {
    logFinished = false;
  }


  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    if (logFed && !logFinished) {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, 255);
      delay(100);
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      delay(useTimer);
      digitalWrite(relay, 0);
    }

    if (logFinished && logFed) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(enA, 255);
      digitalWrite(relay, 1);
    }

    if (!logFed) {
      Serial.println("No Log");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(relay, 1);
    }
  }
}



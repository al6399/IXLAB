int buzzerPin = 8;
int button1 = 11;
int button2 = 10;
int button3 = 5;
int button4 = 6;
int led1 = 3;
int led2 = 2;
int led3 = 13;
int led4 = 4;

int goal = 10;
int buttonState1 = LOW;
int previousState1 = LOW;
int buttonState2 = LOW;
int previousState2 = LOW;
int buttonState3 = LOW;
int previousState3 = LOW;
int buttonState4 = LOW;
int previousState4 = LOW;


int counter1 = 0;
int counter2 = 0;
int counter3 = 0;
int counter4 = 0;
boolean winner1 = false;
boolean winner2 = false;
boolean winner3 = false;
boolean winner4 = false;

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  Serial.println("******************* RACE THE LED *******************");
  delay(1000);
  Serial.println("READY");
  delay(1000);
  Serial.println("SET");
  delay(1500);
  Serial.println("GO!!!!!!!!!!!!!!!!");

}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState1 = digitalRead(button1);
  buttonState2 = digitalRead(button2);
  buttonState3 = digitalRead(button3);
  buttonState4 = digitalRead(button4);
  //Serial.println(buttonState1);

  //this checks the times player 01 has pressed the button
  if (counter1 < goal && winner1 == false) {
    if (buttonState1 != previousState1 && millis() - time > debounce) {
      if (buttonState1 == HIGH) {
        counter1++;
        Serial.print("player 01:  ");
        Serial.println(counter1);
        time = millis();
      }
    }
    
    previousState1 = buttonState1;
    if (counter1 == goal && winner2 == false) {
      winner1 = true;
      digitalWrite(led1, HIGH);
      Serial.println("PLAYER 01 WINS");
      playMelody();
    }
  }
  //this checks the times player 02 has pressed the button

  if (counter2 < goal && winner2 == false) {
    if (buttonState2 != previousState2 && millis() - time > debounce) {
      if (buttonState2 == HIGH) {
        counter2++;
        Serial.print("player 02:  ");
        Serial.println(counter2);
        time = millis();
      }
    }
    previousState2 = buttonState2;
    if (counter2 == goal && winner2 == false) {
      winner2 = true;
      digitalWrite(led2, HIGH);
      Serial.println("PLAYER 02 WINS");
      playMelody();
    }
  }
    if (counter3 < goal && winner3 == false) {
    if (buttonState3 != previousState3 && millis() - time > debounce) {
      if (buttonState3 == HIGH) {
        counter3++;
        Serial.print("player 03:  ");
        Serial.println(counter3);
        time = millis();
      }
    }
    previousState3 = buttonState3;
    if (counter3 == goal && winner3 == false) {
      winner3 = true;
      digitalWrite(led3, HIGH);
      Serial.println("PLAYER 03 WINS");
      playMelody();
    }
    }
  
if (counter4 < goal && winner4 == false) {
    if (buttonState4 != previousState4 && millis() - time > debounce) {
      if (buttonState4 == HIGH) {
        counter4++;
        Serial.print("player 04:  ");
        Serial.println(counter4);
        time = millis();
      }
    }
    previousState4 = buttonState4;
    if (counter4 == goal && winner4 == false) {
      winner4 = true;
      digitalWrite(led4, HIGH);
      Serial.println("PLAYER 04 WINS");
      playMelody();
    }
}
  
}



void playFreq(double freqHz, int durationMs) {
  //Calculate the period in microseconds
  int periodMicro = int((1 / freqHz) * 1000000);
  int halfPeriod = periodMicro / 2;

  //store start time
  long startTime = millis();

  //(millis() - startTime) is elapsed play time
  while ((millis() - startTime) < durationMs) {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(halfPeriod);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(halfPeriod);
  }
}

void playMelody() {

  playFreq(262, 100);
  playFreq(294, 100);
  playFreq(349, 100);
  playFreq(294, 100);
  playFreq(440, 200);
  delay(100);
  playFreq(440, 400);
  playFreq(392, 400);
  delay(300);
  playFreq(262, 100);
  playFreq(294, 100);
  playFreq(349, 100);
  playFreq(294, 100);
  playFreq(392, 200);
  delay(100);
  playFreq(392, 400);
  playFreq(349, 400);

}

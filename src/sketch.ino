// -*- c -*-
/**
   Circuit is connected as follows:
   
   One end of gapped wire is connected to ground
   One end of 10k resistor connected to 5V
   Other end of 10k resistor connected to digital pin 7 and
   connection tab (the thing that drags along the gapped wire).
 */

#define SENSOR_DETECT_PIN 7
#define LED_PIN 13
#define STOP_THRESHOLD 1000L

enum MotionState {
  Stopped,
  Moving
};

int previousValue = -1;
long lastChangeTime = 0L;
MotionState currentState = Stopped;

void setup()
{
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  pinMode(SENSOR_DETECT_PIN, INPUT);
  digitalWrite(LED_PIN, LOW);
  
  Serial.println("Ready!");
}

void loop()
{
  int sampleTime = millis();
  int value = digitalRead(SENSOR_DETECT_PIN);

  // Deal with the startup case
  if (previousValue < 0) {
    previousValue = value;
    lastChangeTime = sampleTime;
    return;
  }

  // Now deal with the real world
  if (value != previousValue) {
    previousValue = value;
    lastChangeTime = millis();
    currentState = Moving;
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Now moving...");
  } else {
    long duration = sampleTime - lastChangeTime;
    if (duration > STOP_THRESHOLD) {
      currentState = Stopped;
      digitalWrite(LED_PIN, LOW);
      Serial.print("No change for too long (");
      Serial.print(duration);
      Serial.println(") ms. Stopped");
    }
  }

  delay(300);
}

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

// How long to wait for no change to identify a stopped status (ms)
#define STOP_THRESHOLD 1000L

// How long to wait between reading the sensor. You may want to
// tweak this value or the STOP THRESHOLD depending on how fast
// the item is being moved. If the thing is moving fast, you may
// want to shorten this time so you don't miss too many measurements.
// If the thing is moving slow, you can probably leave this alone
// or increase it, but you might need to increase the STOP_THRESHOLD.
// 
// Think about it.
#define DELAY_TIME 200

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
    handleValueChange(value);
  } else {
    handleValueNoChange(sampleTime);
  }

  delay(DELAY_TIME); 
}

void handleValueChange(int value) {
  previousValue = value;
  lastChangeTime = millis();
  currentState = Moving;
  digitalWrite(LED_PIN, HIGH);
  Serial.println("Now moving...");
}

void handleValueNoChange(int sampleTime) {
  long duration = sampleTime - lastChangeTime;
  if (duration > STOP_THRESHOLD) {
    currentState = Stopped;
    digitalWrite(LED_PIN, LOW);
    Serial.print("No change for too long (");
    Serial.print(duration);
    Serial.println(") ms. Stopped");
  }
}

#define ANALOG_PIN A2
#define ANALOG_SAMPLE 15

int numSample = 0;
int samples[ANALOG_SAMPLE];
int analogMean = 0;
int analogValue = 0;

void setup() {
  Serial.begin(9600);

  char* a = "AZERTY   T   FGHJKLMWXCV";
  char* b = "AZDFTYUIOPQSDFGHJKLMWXCV";
  for (int i = 0; i <= 23; i++) {
    if (a[i] != b[i]) {
      Serial.println(b[i]);
      b[i] = a[i];
    }
  }
  delay(1000);
  Serial.println(a);
  Serial.println(b);
  delay(1000);
  a[0] = "1";
  a[2] = ".";
  Serial.println(a);
  Serial.println(b);
  delay(1000);
  // pinMode(ANALOG_PIN, INPUT_PULLUP);
}

void loop() {
  /*
  analogValue = analogRead(ANALOG_PIN);

  if (numSample < ANALOG_SAMPLE) {
    samples[numSample] = analogValue;
    numSample++;
  } else if (numSample == ANALOG_SAMPLE) {
    // Calc moyenne
    long sum = 0L;
    for (int i = 0; i < ANALOG_SAMPLE; i++) {
      sum += samples[i];
      samples[i] = 0; // Reset each value
    }
    analogMean = sum / ANALOG_SAMPLE;
    numSample = 0;

    Serial.println(analogMean);
  }
  */
}

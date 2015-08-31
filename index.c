int flexInitial;
int softCount;
int deepCount;
int softThresh;
int deepThresh;
int purCount;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT);
  flexInitial = analogRead(A0);
  Serial.print("INITIAL FLEX VALUE: ");
  Serial.print(flexInitial);
  Serial.println("");
  softCount = 0;
  deepCount = 0;
  softThresh = 8;
  deepThresh = 12;
  purCount = 5;
}


void loop() {
  int flexSensor = analogRead(A0);
  analogWrite(9, abs(flexInitial - flexSensor));
  if (abs(flexInitial - flexSensor) >= deepThresh) {
    deepCount++;
  }
  else if (abs(flexInitial - flexSensor) >= softThresh) {
    softCount++;
  }

  if (deepCount >= 25) {
    deepPur(5000, 3);
    softCount = 0;
    deepCount = 0;
  }
  else if (softCount >= 50) {
    softPur(5000);
    softCount = 0;
    deepCount = 0;
  }
  Serial.print("DEEP COUNT: ");
  Serial.print(deepCount);
  Serial.println("");
  Serial.print("SOFT COUNT: ");
  Serial.print(softCount);
  Serial.println("");
  Serial.print("SENSOR DIFF: ");
  Serial.print(abs(flexInitial - flexSensor));
  Serial.println("");
  delay(100);
}

void softPur(int purTime) {
  digitalWrite(13, HIGH);
  delay(purTime);
  digitalWrite(13, LOW);
}

void deepPur(int purTime, int purNums) {
  digitalWrite(13, HIGH);
  for (int i = 0; i < purNums; i++) {
    delay(purTime / (purNums * 2));
    digitalWrite(12, HIGH);
    delay(purTime / (purNums * 2));
    digitalWrite(12, LOW);
  }

  digitalWrite(13, LOW);
}
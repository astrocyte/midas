#include <Bounce.h>

Bounce bouncer = Bounce(10, 5);

int len = 20;
char val1[20];
char val2[20];
int interval = 115;
int rfidSwitch = 1;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

void setup() {
  pinMode(10, INPUT);
  digitalWrite(10, HIGH);
  Serial2.begin(9600);
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial2.println("SRA");
  Serial1.println("SRD");
}

void loop() {
  switchCheck();
  tagRead();
  bouncer.update();
  if(bouncer.fallingEdge()) {
    Serial.println("wheel");
  }
}
  
void switchCheck() {
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if(rfidSwitch == 0){
      rfidSwitch = 1;
      Serial2.println("SRA");
      Serial1.println("SRD");
    }else{
      rfidSwitch = 0;
      Serial2.println("SRD");
      Serial1.println("SRA");
    }
    for(int i = 0; i < 3; i++) {
      Serial1.read();
      Serial2.read();
    }
  }
}

void tagRead() {
  if(rfidSwitch == 0) {
    if(Serial1.available() == len) {
      Serial1.readBytes(val1, len-1);
      Serial.print(val1);
      Serial.println("-1");
      Serial1.read();
    }
  }else if(rfidSwitch == 1) {
    if(Serial2.available() == len) {
      Serial2.readBytes(val2, len-1);
      Serial.print(val2);
      Serial.println("-2");
      Serial2.read();
    }
  }
}

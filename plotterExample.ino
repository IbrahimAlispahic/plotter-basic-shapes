#define stepPinX 2
#define stepPinY 3
#define stepPinZ 4
#define dirPinX 5
#define dirPinY 6
#define dirPinZ 7
#define enPinX 8
#define enPinY 9
#define enPinZ 10

void setup() {
  // put your setup code here, to run once:
  pinMode(stepPinX, OUTPUT);
  pinMode(stepPinY, OUTPUT);
  pinMode(stepPinZ, OUTPUT);
  pinMode(dirPinX, OUTPUT);
  pinMode(dirPinY, OUTPUT);
  pinMode(dirPinZ, OUTPUT);
  pinMode(enPinX, OUTPUT);
  pinMode(enPinY, OUTPUT);
  pinMode(enPinZ, OUTPUT);
}

// 2mm == 27 steps for x, 108 steps for y
// 1cm == 135 steps for x, 540 steps for y
// dir == 0 --> negative direction, dir == 1 --> positive direction
//initial configuration upper right corner, base movement x axis, tool moving y axis
void moveX(float mmLength, bool dir) {
  dirX(dir);
  int numOfSteps = 13.5 * mmLength;
  for (int i = 0; i < numOfSteps; i++) {
    digitalWrite(stepPinX, HIGH);
    delay(1);
    digitalWrite(stepPinX, LOW);
  }
  delay(100);
}
void moveY(float mmLength, bool dir) {
  dirY(dir);
  int numOfSteps = 54 * mmLength;
  for (int i = 0; i < numOfSteps; i++) {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(300);
    digitalWrite(stepPinY, LOW);
  }
  delay(100);
}
void stepX(int numOfSteps, bool dir) {
  dirX(dir);
  for (int i = 0; i < numOfSteps; i++) {
    digitalWrite(stepPinX, HIGH);
    delay(1);
    digitalWrite(stepPinX, LOW);
  }
  delay(100);
}
void stepY(float numOfSteps, bool dir) {
  dirY(dir);
  for (int i = 0; i < numOfSteps; i++) {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(300);
    digitalWrite(stepPinY, LOW);
  }
  delay(100);
}
void stepXY(int numOfStepsX, int numOfStepsY, bool dirX1, bool dirY) {
  dirX(dirX1);
  for (int i = 0; i < numOfStepsX; i++) {
    digitalWrite(stepPinX, HIGH);
    stepY(numOfStepsY, dirY);
    delay(1);
    digitalWrite(stepPinX, LOW);
  }
  delay(100);
}

void dirX(bool dir) {
  if (dir)
    digitalWrite(dirPinX, LOW);
  else
    digitalWrite(dirPinX, HIGH);
}
void dirY(bool dir) {
  if (dir)
    digitalWrite(dirPinY, LOW);
  else
    digitalWrite(dirPinY, HIGH);
}

void dizanje() {
  digitalWrite(enPinZ, LOW);
  digitalWrite(dirPinZ, HIGH);
  for (int i = 0; i < 870; i++) {
    digitalWrite(stepPinZ, HIGH);
    delay(1);
    digitalWrite(stepPinZ, LOW);
  }
  digitalWrite(enPinZ, HIGH);
}

void spustanje() {
  digitalWrite(enPinZ, LOW);
  digitalWrite(dirPinZ, LOW);
  for (int i = 0; i < 980; i++) {
    digitalWrite(stepPinZ, HIGH);
    delay(1);
    digitalWrite(stepPinZ, LOW);
  }
  digitalWrite(enPinZ, HIGH);
}

void kvadrat() {
  spustanje();
  moveX(37, 1);
  moveY(37, 1);
  moveX(37, 0);
  moveY(37, 0);
  dizanje();
}

void trougao () {
  digitalWrite(dirPinX, LOW);
  digitalWrite(dirPinY, LOW);
  for (int i = 0; i < 1000; i++) {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(300);
    digitalWrite(stepPinY, LOW);
  }
  spustanje();
  digitalWrite(dirPinX, LOW);
  digitalWrite(dirPinY, HIGH);
  for (int i = 1; i < 500; i++) {
    digitalWrite(stepPinX, HIGH);

    for (int j = 1; j < 3; j++) {
      digitalWrite(stepPinY, HIGH);
      delay(1);
      digitalWrite(stepPinY, LOW);
    }
    delay(1);
    digitalWrite(stepPinX, LOW);
  }
  delay(100);
  digitalWrite(dirPinY, LOW);
  for (int i = 0; i < 2000; i++) {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(300);
    digitalWrite(stepPinY, LOW);
  }
  delay(100);
  digitalWrite(dirPinX, HIGH);
  digitalWrite(dirPinY, HIGH);
  for (int i = 1; i < 500; i++) {
    digitalWrite(stepPinX, HIGH);

    for (int j = 1; j < 3; j++) {
      digitalWrite(stepPinY, HIGH);
      delay(1);
      digitalWrite(stepPinY, LOW);
    }
    delay(1);
    digitalWrite(stepPinX, LOW);
  }
  delay(100);

  dizanje();
  for (int i = 0; i < 1000; i++) {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(300);
    digitalWrite(stepPinY, LOW);
  }
}
void krug() {
  digitalWrite(dirPinY, LOW);
  for (int i = 0; i < 1000; i++) {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(300);
    digitalWrite(stepPinY, LOW);
  }
  spustanje();
  int radius = 125; //125 == 19mm
  float angle_delta = 0.001;
  int x = radius;
  int y = 0 ;
  for (float angle = 0.0; angle < 2.0 * PI ; angle += angle_delta) {
    int xx = radius * cos(angle) ;
    int yy = radius * sin(angle) ;
    while (xx != x || yy != y) {
      if (xx > x) {
        digitalWrite(dirPinX, HIGH);
        for (int i = 0; i < 2; i++) {
          digitalWrite(stepPinX, HIGH);
          delay(1);
          digitalWrite(stepPinX, LOW);
        }
        x += 1 ;
      }
      else if (xx < x) {
        digitalWrite(dirPinX, LOW);
        for (int i = 0; i < 2; i++) {
          digitalWrite(stepPinX, HIGH);
          delay(1);
          digitalWrite(stepPinX, LOW);
        }
        x -= 1 ;
      }
      if (yy > y) {
        digitalWrite(dirPinY, HIGH);
        for (int i = 0; i < 8; i++) {
          digitalWrite(stepPinY, HIGH);
          delayMicroseconds(300);
          digitalWrite(stepPinY, LOW);
        }
        y += 1 ;
      }
      else if (yy < y) {
        digitalWrite(dirPinY, LOW);
        for (int i = 0; i < 8; i++) {
          digitalWrite(stepPinY, HIGH);
          delayMicroseconds(300);
          digitalWrite(stepPinY, LOW);
        }
        y -= 1 ;
      }
    }
  }
  dizanje();
  digitalWrite(dirPinY, HIGH);
  for (int i = 0; i < 1000; i++) {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(300);
    digitalWrite(stepPinY, LOW);
  }
}

bool firstRun = true;
void loop() {
  delay(500);
  digitalWrite(stepPinX, LOW);
  digitalWrite(dirPinX, LOW);
  digitalWrite(stepPinY, LOW);
  digitalWrite(dirPinY, LOW);
  if (firstRun) {
    trougao();
    //krug();
    //kvadrat();
    digitalWrite(enPinX, HIGH);
    digitalWrite(enPinY, HIGH);
  }
  firstRun = false;
}

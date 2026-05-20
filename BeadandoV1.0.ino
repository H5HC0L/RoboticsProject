#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(2,3,4,5,6,7);

boolean dinoOnGround = true;

int buttonPin = 8;
int buttonState = 0;
int highScore = 0;

boolean playState = false;



int score = 0;

unsigned long jumpTime = 0;
bool jumping = false;

int cactusX = 16;
unsigned long lastMoved = 0;
int cactusSpeed = 200;
int distance = 6;
int distanceTwo = 6;

unsigned long lastUpdateScore = 0;

//dino character
byte dino [8]        
{ B00000,
  B00111,
  B00101,
  B10111,
  B11100,
  B11111,
  B01101,
  B01100,
};

//tree character
byte tree [8]      
{
  B00011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11111,
  B01110,
  B01110
};

void readInput(){
  int state = digitalRead(buttonPin);
  if(state == HIGH && !jumping){
    jumping = true;
    jumpTime = millis();
  }
}
void Jump(){
  if(jumping){
    lcd.setCursor(1,0);
    lcd.write(7);
    lcd.setCursor(1,1);
    lcd.print(" ");
    dinoOnGround = false;
    if(millis() - jumpTime >= 800){
      jumping = false;
    }
  }
  else{
    lcd.setCursor(1,1);
    lcd.write(7);
    lcd.setCursor(1,0);
    lcd.print(" ");
    dinoOnGround = true;
  }
}

void moveCactus(){
  if(millis() - lastMoved >= cactusSpeed){
    lastMoved = millis();
    --cactusX;
    ++score;
    if(cactusX + distance + distanceTwo < 0){
      cactusX = 16;
      distance = random(5,9);
      distanceTwo = random(5,9);
    }
  }
}
void drawCactus(){
  if(cactusX >= 0 && cactusX < 16){
    lcd.setCursor(cactusX,1);
    lcd.write(6);
  }

  if(cactusX + 1 >= 0 && cactusX + 1 < 16){
    lcd.setCursor(cactusX+1,1);
    lcd.print(" ");
  }

  if(cactusX + distance >= 0 && cactusX + distance < 16){
    lcd.setCursor(cactusX + distance,1);
    lcd.write(6);
  }

  if(cactusX + distance + 1 >= 0 && cactusX + distance + 1 < 16){
    lcd.setCursor(cactusX + distance + 1,1);
    lcd.print(" ");
  }

  if(cactusX + distance + distanceTwo >= 0 &&
     cactusX + distance + distanceTwo < 16){

    lcd.setCursor(cactusX + distance + distanceTwo,1);
    lcd.write(6);
  }

  if(cactusX + distance + distanceTwo + 1 >= 0 &&
     cactusX + distance + distanceTwo + 1 < 16){

    lcd.setCursor(cactusX + distance + distanceTwo + 1,1);
    lcd.print(" ");
  }
}
void checkCollision(){
  if((cactusX == 1 ||
        cactusX + distance == 1 ||
        cactusX + distanceTwo + distance == 1)
        && dinoOnGround)
    {
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("GAME OVER");
        lcd.setCursor(1,1);
        lcd.print("Score: ");
        lcd.print(score);
        delay(1500);

        playState = false;
        score = 0;
        cactusX = 16;
    }
}
void showScore(){
  lcd.setCursor(13,0);
  lcd.print(score);
}


void setup() {
  lcd.begin(16,2);
  lcd.createChar(7,dino);
  lcd.createChar(6,tree);
  lcd.setCursor(0,1);
  lcd.write(7);
  pinMode(buttonPin,INPUT);
}

void loop() {
  int start = 0;
  if(!playState){
    lcd.clear();
    start = 0;
    lcd.setCursor(0, 0);
    lcd.print("Press button to");
    lcd.setCursor(0,1);
    lcd.print("start");
    if(digitalRead(buttonPin) == HIGH){
      playState = true;
    }
  }
  else{
    if(start <= 1){
      lcd.clear();
    }
    readInput();
    Jump();
    moveCactus();
    drawCactus();
    checkCollision();
    //showScore();
    ++start;
  }
}


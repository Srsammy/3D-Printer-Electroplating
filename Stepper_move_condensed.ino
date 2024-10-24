#include <CheapStepper.h>

// connect pins 8,9,10,11 to IN1,IN2,IN3,IN4 on ULN2003 board
const int IN1=5,   IN2=4,   IN3=3,   IN4= 2;
CheapStepper stepper (IN1,IN2,IN3,IN4);  

bool moveClockwise = true;
int steps = 0;
int miniStep = 4076;
int revTime = 20;          //sets the time for a full revolution in minutes
int stepTime = 60000*revTime/(miniStep);     
int rev;

long time;
long timeS;
long timeM;
int  timeH;
bool start = true;

long lastTime;

long switchTime;
int reverseTime = 4;  //Time to reverse in ms
int ForwardTime = 20;  //Time to have current go forward
int reverseCounter;   //Counts how many times it has reversed
int rCountCaractorTime = 10;

String compInput;
String getTime=String("Time");

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() 
{
  stepper.setRpm(10); 
  stepper.moveCCW (1);
  stepper.setTotalSteps(4076);

  lcd.begin(16, 2);

  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
  pinMode(7, OUTPUT);
  digitalWrite(6, LOW);
}

void loop() 
{
  
  time  = (millis())/1000;
  timeS = (time) % 60;
  timeM = (time/(60)) % 60;
  timeH = (time/(60*60));

  if ((millis() - lastTime)>stepTime)
  {

    if (steps>=(miniStep-10)) 
    {
      stepper.moveToDegree(true, 0);
      steps=0;
      rev++;
    }
    else
    {
      stepper.moveCCW (1);
      steps++;
      lastTime = millis();
    }

  }
  if (steps == 0 or timeS == 0)
  {
    lcd.clear();
  }

  if((millis() - switchTime)> ForwardTime)
  {
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);
    delay(reverseTime);
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);
    switchTime = millis();
    if(reverseCounter == rCountCaractorTime)
    {
      lcd.setCursor(15,0);
      lcd.print(".");
      reverseCounter =0;
    }
    else
    {
      reverseCounter++;
    }
    if(reverseCounter == (rCountCaractorTime/2))
    {
      lcd.setCursor(15,0);
      lcd.print(" ");
    }
  }
  lcd.setCursor(0, 0);
  lcd.print(rev);
  lcd.print(':');
  lcd.print(steps);

  lcd.setCursor(0, 1);
  lcd.print(timeH);
  lcd.print(':');
  lcd.print(timeM);
  lcd.print(':');
  lcd.print(timeS);
}

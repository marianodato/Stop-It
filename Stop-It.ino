#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int greenLEDPin1 = 9;
const int greenLEDPin2 = 10;
const int redLEDPin3 = 14;
const int greenLEDPin4 = 6;
const int greenLEDPin5 = 13; 
const int switchPin = 8;
const int piezoPin = 7;

unsigned long delayTime = 1000;
unsigned long delayTime2 = 100;
unsigned long delayTime3 = 5000;
unsigned long delayTime4 = 500;

unsigned long timeGreenLEDPin1Start = 0;
unsigned long timeGreenLEDPin2Start = 0;
unsigned long timeRedLEDPin3Start = 0;
unsigned long timeGreenLEDPin4Start = 0;
unsigned long timeGreenLEDPin5Start = 0;

unsigned long timeScroll = 0;

bool greenLEDPin1On = false;
bool greenLEDPin2On = false;
bool redLEDPin3On = false;
bool greenLEDPin4On = false;
bool greenLEDPin5On = false;

char buf[16];
char text[] = "This is Stop-It!";

int sound = 4000;
int sound2 = 1000;
int switchState = LOW;
int level = 1;
int spaces = 4;
int size = sizeof(text) - 1;
int index = -size;

bool start = true;
bool scroll = true;

void setup()
{
	lcd.begin(16, 2);
  	lcd.setCursor(0,1);
  	lcd.print("    LEVEL: 1");
  
 	pinMode(greenLEDPin1,OUTPUT);
  	pinMode(greenLEDPin2,OUTPUT);
  	pinMode(redLEDPin3,OUTPUT);
  	pinMode(greenLEDPin4,OUTPUT);
  	pinMode(greenLEDPin5,OUTPUT);
  	pinMode(switchPin,INPUT);

  	digitalWrite(greenLEDPin1,LOW);
  	digitalWrite(greenLEDPin2,LOW);
  	digitalWrite(redLEDPin3,LOW);
  	digitalWrite(greenLEDPin4,LOW);
  	digitalWrite(greenLEDPin5,LOW);

  	tone(piezoPin,sound,delayTime2);
}

void win()
{
	int i=0;

  	lcd.clear();
  	lcd.setCursor(0,0);
  	lcd.print("Congratulations,");
  	lcd.setCursor(0,1);
  	lcd.print("    YOU WIN!");
  	tone(piezoPin,sound2,delayTime3);

  	while (i<25)
  	{
		digitalWrite(greenLEDPin1,HIGH);
		digitalWrite(greenLEDPin2,LOW);
		digitalWrite(redLEDPin3,HIGH);
		digitalWrite(greenLEDPin4,LOW);
		digitalWrite(greenLEDPin5,HIGH);

		delay(100);

		digitalWrite(greenLEDPin1,LOW);
		digitalWrite(greenLEDPin2,HIGH);
		digitalWrite(redLEDPin3,LOW);
		digitalWrite(greenLEDPin4,HIGH);
		digitalWrite(greenLEDPin5,LOW);

		delay(100); 

     		i++; 
  	}
}

void lose()
{
	int i=0;

  	lcd.clear();
  	lcd.setCursor(0,0);
  	lcd.print("   Try again,");
  	lcd.setCursor(0,1);
  	lcd.print("   YOU LOSE!");

  	tone(piezoPin,sound2,delayTime3);
  	
  	while (i<25)
  	{
		digitalWrite(greenLEDPin1,LOW);
		digitalWrite(greenLEDPin2,LOW);
		digitalWrite(redLEDPin3,LOW);
		digitalWrite(greenLEDPin4,LOW);
		digitalWrite(greenLEDPin5,LOW);

		delay(100);

		i++; 
  	}
}

void inicializate(unsigned long newDelayTime)
{
  	lcd.setCursor(0,1);
  	lcd.print("    LEVEL: ");
  	lcd.print(level);
  
  	delayTime = newDelayTime;
  	switchState = LOW;
  	timeGreenLEDPin1Start = 0;
  	timeGreenLEDPin2Start = 0;
  	timeRedLEDPin3Start = 0;
  	timeGreenLEDPin4Start = 0;
  	timeGreenLEDPin5Start = 0;
  	greenLEDPin1On = false;
  	greenLEDPin2On = false;
  	redLEDPin3On = false;
  	greenLEDPin4On = false;
  	greenLEDPin5On = false;
  	start = true;
 
  	if (delayTime==1000)
  	{
   		index = -size;
		scroll = true;
		timeScroll = 0;
  	}
  
  	digitalWrite(greenLEDPin1,LOW);
  	digitalWrite(greenLEDPin2,LOW);
  	digitalWrite(redLEDPin3,LOW);
  	digitalWrite(greenLEDPin4,LOW);
  	digitalWrite(greenLEDPin5,LOW);
}

void move()
{
  	if (index >= size + spaces)
    		index = 0;

  	for (int i = 0; i < 16; i++) 
  	{
		if ((index + i) % (size + spaces) < sizeof(text)-1)
			buf[i] = text[(i + index) % (size + spaces)];
		else
			buf[i] = ' ';
  	}

  	lcd.setCursor(0,0);
  	lcd.print(buf);

  	index+=1;
}

void loop() 
{
  	if (scroll)
  	{
		timeScroll=millis();
		scroll = false;
  	}

  	if ((millis() - timeScroll) >= delayTime4)
  	{
		move();
		scroll = true;
  	}
  
  	if (switchState == LOW)
  	{
    		switchState = digitalRead(switchPin);

    	if (switchState == HIGH)
      		tone(piezoPin,sound2,delayTime2);
  	}
  
  	if (start || (greenLEDPin5On && (millis() - timeGreenLEDPin5Start) >= delayTime))
  	{
		if (switchState == HIGH)
		{
			switchState = LOW;
			lose();
			level = 1;
			tone(piezoPin,sound,delayTime2);
			inicializate(1000);
		}else
		{
			start = false;
			greenLEDPin5On = false;
			digitalWrite(greenLEDPin5,LOW);
			digitalWrite(greenLEDPin1,HIGH);

			if (!greenLEDPin1On)    
				timeGreenLEDPin1Start = millis();

			greenLEDPin1On = true;
		}
      
  	}else if (greenLEDPin1On && (millis() - timeGreenLEDPin1Start) >= delayTime)
  	{
		if (switchState == HIGH)
		{
			switchState = LOW;
			lose();
			level = 1;
			tone(piezoPin,sound,delayTime2);
			inicializate(1000);
		}else
		{
			greenLEDPin1On = false;
			digitalWrite(greenLEDPin1,LOW);
			digitalWrite(greenLEDPin2,HIGH);

			if (!greenLEDPin2On) 
				timeGreenLEDPin2Start = millis();

			greenLEDPin2On = true;
		}
  	}else if (greenLEDPin2On && (millis() - timeGreenLEDPin2Start) >= delayTime)
  	{
		if (switchState == HIGH)
		{
			switchState = LOW;
			lose();
			level = 1;
			tone(piezoPin,sound,delayTime2);
			inicializate(1000);
		}else
		{
			greenLEDPin2On = false;
			digitalWrite(greenLEDPin2,LOW);
			digitalWrite(redLEDPin3,HIGH);

			if (!redLEDPin3On) 
				timeRedLEDPin3Start = millis();

			redLEDPin3On = true;
		}
  	}else if (redLEDPin3On && (millis() - timeRedLEDPin3Start) >= delayTime)
  	{
		if (switchState == HIGH)
		{
			switchState = LOW;

			if (delayTime-100 > 0)
			{
				level = level + 1;
				inicializate(delayTime-100);
			}else
			{
				win();
				level = 1;
				tone(piezoPin,sound,delayTime2);
				inicializate(1000);
			}
		}else
		{
			redLEDPin3On = false;
			digitalWrite(redLEDPin3,LOW);
			digitalWrite(greenLEDPin4,HIGH);

			if (!greenLEDPin4On) 
				timeGreenLEDPin4Start = millis();

			greenLEDPin4On = true;
		}
  	}else if (greenLEDPin4On && (millis() - timeGreenLEDPin4Start) >= delayTime)
  	{
		if (switchState == HIGH)
		{
			switchState = LOW;
			lose();
			level = 1;
			tone(piezoPin,sound,delayTime2);
			inicializate(1000);
		}else
		{
			greenLEDPin4On = false;
			digitalWrite(greenLEDPin4,LOW);
			digitalWrite(greenLEDPin5,HIGH);

			if (!greenLEDPin5On) 
				timeGreenLEDPin5Start = millis();

			greenLEDPin5On = true;
		}
  	} 
}

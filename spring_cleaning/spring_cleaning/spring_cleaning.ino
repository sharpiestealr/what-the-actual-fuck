#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <stdlib.h> 
#include <time.h>

//declarar lcd
LiquidCrystal_I2C lcd(0x27,16,2);

//do only the ~
int red_one = 11; 
int red_two = 6;
int green_one = 10; 
int green_two = 5;
int blue_one = 9; 
int blue_two = 3;

int color[3][3] = {{255, 150, 0}, {150, 255, 150}, {0, 150, 255}};
int check[2][3] = {{45, 30, 15}, {40, 60, 80}}; //NICE GIRL

float temp = 10.0;
float humid = 35.0;

void setup() 
{
  Serial.begin(9600);
  analogReference(INTERNAL);
  
  pinMode(red_one, OUTPUT);
  pinMode(green_one, OUTPUT);
  pinMode(blue_one, OUTPUT);
  pinMode(red_two, OUTPUT);
  pinMode(green_two, OUTPUT);
  pinMode(blue_two, OUTPUT);

  lcd.init();
  lcd.backlight();

  srand(time(NULL));
}

static float calibra_DHT() 
{
  int humid = rand()%100;
  return humid;
}

static float calibra_LM()
{
  int temp = rand()%60;
  return temp;
}

void RGB_color(int sensor, int red, int green, int blue)
{
  if (sensor == 1)
  {
    analogWrite(red_one, red);
    analogWrite(green_one, green);
    analogWrite(blue_one, blue);
  }

  else
  {
    analogWrite(red_two, red);
    analogWrite(green_two, green);
    analogWrite(blue_two, blue);
  }
}

static int calcR(bool tempC, float temp, bool humidC, float humid)
{
  float red;

  if (tempC == true)
  {
    if (temp >= check[0][0])
    {
      red = color[0][0];
    }
  
    else if (temp == check[0][1])
    {
      red = 0;
    }

    else if (temp <= check[0][2])
    {
      red = 0;
    }
  
    else
    {
      if ((temp > check[0][1]) && (temp < check[0][0]))
      {
        red = ((temp- check[0][1])/(check[0][0]- check[0][1]))*color[0][1];
      }

      else if ((temp > check[0][2]) && (temp < check[0][1]))
      {
        red = ((temp- check[0][2])/(check[0][1]- check[0][2]))*color[0][2];
      }
    }

    int redF = floor(red);

    return redF;
  }

  else if (humidC == true)
  {
    if (humid <= check[1][0])
    {
      red = color[0][0];
    }
  
    else if (humid == check[1][1])
    {
      red = 0;
    }

    else if (humid >= check[1][2])
    {
      red = 0;
    }
  
    else
    {
      if ((humid < check[1][1]) && (humid > check[1][0]))
      {
        red = ((humid- check[1][1])/(check[1][0]- check[1][1]))*color[0][1];
      }

      else if ((humid < check[1][2]) && (humid > check[1][1]))
      {
        red = ((humid- check[1][2])/(check[1][1]- check[1][2]))*color[0][2];
      }
    }

    int redF = floor(red);

    return redF;
  }
}

static int calcG(bool tempC, float temp, bool humidC, float humid)
{
  float green;

  if (tempC == true)
  {
    if (temp >= check[0][0])
    {
      green = 0;
    }
  
    else if (temp == check[0][1])
    {
      green = color[1][1];
    }

    else if (temp <= check[0][2])
    {
      green = 0;
    }
  
    else
    {
      if ((temp > check[0][1]) && (temp < check[0][0]))
      {
        green = ((temp- check[0][1])/(check[0][0]- check[0][1]))*color[1][0];
      }

      else if ((temp > check[0][2]) && (temp < check[0][1]))
      {
        green = ((temp- check[0][2])/(check[0][1]- check[0][2]))*color[1][2];
      }
    }

    int greenF = floor(green);

    return greenF;
  }

  else if (humidC == true)
  {
    if (humid <= check[1][0])
    {
      green = 0;
    }
  
    else if (humid == check[1][1])
    {
      green = color[1][1];
    }

    else if (humid >= check[1][2])
    {
      green = 0;
    }
  
    else
    {
      if ((humid < check[1][1]) && (humid > check[1][0]))
      {
        green = ((humid- check[1][1])/(check[1][0]- check[1][1]))*color[1][0];
      }

      else if ((humid < check[1][2]) && (humid > check[1][1]))
      {
        green = ((humid- check[1][2])/(check[1][1]- check[1][2]))*color[1][2];
      }
    }

    int greenF = floor(green);

    return greenF;
  }
}

static int calcB(bool tempC, float temp, bool humidC, float humid)
{
  float blue;

  if (tempC == true)
  {
    if (temp >= check[0][0])
    {
      blue = 0;
    }
  
    else if (temp == check[0][1])
    {
      blue = 0;
    }

    else if (temp <= check[0][2])
    {
      blue = color[2][2];
    }
  
    else
    {
      if ((temp > check[0][1]) && (temp < check[0][0]))
      {
        blue = ((temp- check[0][1])/(check[0][0]- check[0][1]))*color[2][0];
      }

      else if ((temp > check[0][2]) && (temp < check[0][1]))
      {
        blue = ((temp- check[0][2])/(check[0][1]- check[0][2]))*color[2][1];
      }
    }

    int blueF = floor(blue);

    return blueF;
  }

  else if (humidC == true)
  {
    if (humid <= check[1][0])
    {
      blue = 0;
    }
  
    else if (humid == check[1][1])
    {
      blue = 0;
    }

    else if (humid >= check[1][2])
    {
      blue = color[2][2];
    }
  
    else
    {
      if ((humid < check[1][1]) && (humid > check[1][0]))
      {
        blue = ((humid- check[1][1])/(check[1][0]- check[1][1]))*color[2][0];
      }

      else if ((humid < check[1][2]) && (humid > check[1][1]))
      {
        blue = ((humid- check[1][2])/(check[1][1]- check[1][2]))*color[2][1];
      }
    }

    int blueF = floor(blue);

    return blueF;
  }
}

void loop() 
{
  //temp = calibra_LM();
  //humid = calibra_DHT();

  if (humid < 85)
  {
    humid +=1;
  }
  else
  {
    humid = 35;
  }

  if (temp < 50)
  {
    temp +=1;
  }
  else
  {
    temp = 10;
  }

  RGB_color(1, calcR(true, temp, false, humid), calcG(true, temp, false, humid), calcB(true, temp, false, humid));
  RGB_color(2, calcR(false, temp, true, humid), calcG(false, temp, true, humid), calcB(false, temp, true, humid));
  
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("temp: ");
  lcd.print(temp);
  lcd.setCursor(0,1);
  lcd.print("humid: ");
  lcd.print(humid); 
  delay(2000);// 
}

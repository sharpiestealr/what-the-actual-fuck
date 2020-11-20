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

int color[3][3] = {{255, 125, 0}, {125, 255, 125}, {0, 125, 255}};
int vibecheck[2][3] = {{45, 30, 15}, {30, 50, 60}}; //NICE GIRL

int temp, humid;

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
  int humid = rand()%40;
  return humid;
}

static float calibra_LM()
{
  int temperatura = rand()%60;
  return temperatura;
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
    if (temp >= vibecheck[0][0])
    {
      red = color[0][0];
    }
  
    else if (temp == vibecheck[0][1])
    {
      red = color[0][1];
    }

    else if (temp <= vibecheck[0][2])
    {
      red = color[0][2];
    }
  
    else
    {
      if ((temp > vibecheck[0][1]) && (temp < vibecheck[0][0]))
      {
        red = (temp- vibecheck[0][1])/((vibecheck[0][0]- vibecheck[0][1])*(color[0][0]-color[0][1]));
      }

      else if ((temp > vibecheck[0][2]) && (temp < vibecheck[0][1]))
      {
        red = (temp- vibecheck[0][2])/((vibecheck[0][1]- vibecheck[0][2])*(color[0][1]-color[0][2]));
      }
    }

    int redT_int = floor(red);

    return redT_int;
  }

  else if (humid == true)
  {
    if (humid >= vibecheck[1][0])
    {
      red = color[0][0];
    }
  
    else if (humid == vibecheck[1][1])
    {
      red = color[0][1];
    }

    else if (humid <= vibecheck[1][2])
    {
      red = color[0][2];
    }
  
    else
    {
      if ((humid > vibecheck[1][1]) && (humid < vibecheck[1][0]))
      {
        red = (humid- vibecheck[1][1])/((vibecheck[1][0]- vibecheck[1][1])*(color[0][0]-color[0][1]));
      }

      else if ((humid > vibecheck[1][2]) && (humid < vibecheck[1][1]))
      {
        red = (humid- vibecheck[1][2])/((vibecheck[1][1]- vibecheck[1][2])*(color[0][1]-color[0][2]));
      }
    }

    int redH_int = floor(red);

    return redH_int;
  }
}

static int calcG(bool tempC, float temp, bool humidC, float humid)
{
  float green;

  if (tempC == true)
  {
    if (temp >= vibecheck[0][0])
    {
      green = color[1][0];
    }
  
    else if (temp == vibecheck[0][1])
    {
      green = color[1][1];
    }

    else if (temp <= vibecheck[0][2])
    {
      green = color[1][2];
    }
  
    else
    {
      if ((temp > vibecheck[0][1]) && (temp < vibecheck[0][0]))
      {
        green = (temp- vibecheck[0][1])/((vibecheck[0][0]- vibecheck[0][1])*(color[1][0]-color[1][1]));
      }

      else if ((temp > vibecheck[0][2]) && (temp < vibecheck[0][1]))
      {
        green = (temp- vibecheck[0][2])/((vibecheck[0][1]- vibecheck[0][2])*(color[1][1]-color[1][2]));
      }
    }

    int greenT_int = floor(green);

    return greenT_int;
  }

  else if (humid == true)
  {
    if (humid >= vibecheck[1][0])
    {
      green = color[1][0];
    }
  
    else if (humid == vibecheck[1][1])
    {
      green = color[1][1];
    }

    else if (humid <= vibecheck[1][2])
    {
      green = color[1][2];
    }
  
    else
    {
      if ((humid > vibecheck[1][1]) && (humid < vibecheck[1][0]))
      {
        green = (humid- vibecheck[1][1])/((vibecheck[1][0]- vibecheck[1][1])*(color[1][0]-color[1][1]));
      }

      else if ((humid > vibecheck[1][2]) && (humid < vibecheck[1][1]))
      {
        green = (humid- vibecheck[1][2])/((vibecheck[1][1]- vibecheck[1][2])*(color[1][1]-color[1][2]));
      }
    }

    int greenH_int = floor(green);

    return greenH_int;
  }
}

static int calcB(bool tempC, float temp, bool humidC, float humid)
{
  float blue;

  if (tempC == true)
  {
    if (temp >= vibecheck[0][0])
    {
      blue = color[2][0];
    }
  
    else if (temp == vibecheck[0][1])
    {
      blue = color[2][1];
    }

    else if (temp <= vibecheck[0][2])
    {
      blue = color[2][2];
    }
  
    else
    {
      if ((temp > vibecheck[0][1]) && (temp < vibecheck[0][0]))
      {
        blue = (temp- vibecheck[0][1])/((vibecheck[0][0]- vibecheck[0][1])*(color[2][0]-color[2][1]));
      }

      else if ((temp > vibecheck[0][2]) && (temp < vibecheck[0][1]))
      {
        blue = (temp- vibecheck[0][2])/((vibecheck[0][1]- vibecheck[0][2])*(color[2][1]-color[2][2]));
      }
    }

    int blueT_int = floor(blue);

    return blueT_int;
  }

  else if (humid == true)
  {
    if (humid >= vibecheck[1][0])
    {
      blue = color[2][0];
    }
  
    else if (humid == vibecheck[1][1])
    {
      blue = color[2][1];
    }

    else if (humid <= vibecheck[1][2])
    {
      blue = color[2][2];
    }
  
    else
    {
      if ((humid > vibecheck[1][1]) && (humid < vibecheck[1][0]))
      {
        blue = (humid- vibecheck[1][1])/((vibecheck[1][0]- vibecheck[1][1])*(color[2][0]-color[2][1]));
      }

      else if ((humid > vibecheck[1][2]) && (humid < vibecheck[1][1]))
      {
        blue = (humid- vibecheck[1][2])/((vibecheck[1][1]- vibecheck[1][2])*(color[2][1]-color[2][2]));
      }
    }

    int blueH_int = floor(blue);

    return blueH_int;
  }
}

void loop() 
{
  temp = calibra_LM();
  humid = calibra_DHT();
  
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

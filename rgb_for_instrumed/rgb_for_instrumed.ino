int red_one = 13; 
int red_two = 10;
int green_one = 12; 
int green_two = 9;
int blue_one = 11; 
int blue_two = 8;

int color[3][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}}; //[0-2][0-2] r, g, b
int check[2][3] = {{45, 30, 15}, {30, 50, 60 }}; //[0][0-2] temperature hi lo, [1][0-2] humid lo hi

float temp, humid;

void setup()
{
  pinMode(red_one, OUTPUT);
  pinMode(green_one, OUTPUT);
  pinMode(blue_one, OUTPUT);

  pinMode(red_two, OUTPUT);
  pinMode(green_two, OUTPUT);
  pinMode(blue_two, OUTPUT);
}

void loop()
{
  RGB_color(1, calcR(true, temp, false, humid), calcG(true, temp, false, humid), calcB(true, temp, false, humid));
  RGB_color(2, calcR(false, temp, true, humid), calcG(false, temp, true, humid), calcB(false, temp, true, humid));
  delay(1000); 
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
      red = color[0][1];
    }

    else if (temp <= check[0][2])
    {
      red = color[0][2];
    }
  
    else
    {
      if ((temp > check[0][1]) && (temp < check[0][0]))
      {
        red = (temp-check[0][1])/((check[0][0]-check[0][1])*(color[0][0]-color[0][1]+color[0][1]));
      }

      else if ((temp > check[0][2]) && (temp < check[0][1]))
      {
        red = (temp-check[0][2])/((check[0][1]-check[0][2])*(color[0][1]-color[0][2]+color[0][2]));
      }
    }

    int redT_int = floor(red);

    return redT_int;
  }

  else if (humid == true)
  {
    if (humid >= check[1][0])
    {
      red = color[0][0];
    }
  
    else if (humid == check[1][1])
    {
      red = color[0][1];
    }

    else if (humid <= check[1][2])
    {
      red = color[0][2];
    }
  
    else
    {
      if ((humid > check[1][1]) && (humid < check[1][0]))
      {
        red = (humid-check[1][1])/((check[1][0]-check[1][1])*(color[0][0]-color[0][1]+color[0][1]));
      }

      else if ((humid > check[1][2]) && (humid < check[1][1]))
      {
        red = (humid-check[1][2])/((check[1][1]-check[1][2])*(color[0][1]-color[0][2]+color[0][2]));
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
    if (temp >= check[0][0])
    {
      green = color[1][0];
    }
  
    else if (temp == check[0][1])
    {
      green = color[1][1];
    }

    else if (temp <= check[0][2])
    {
      green = color[1][2];
    }
  
    else
    {
      if ((temp > check[0][1]) && (temp < check[0][0]))
      {
        green = (temp-check[0][1])/((check[0][0]-check[0][1])*(color[1][0]-color[1][1]+color[1][1]));
      }

      else if ((temp > check[0][2]) && (temp < check[0][1]))
      {
        green = (temp-check[0][2])/((check[0][1]-check[0][2])*(color[1][1]-color[1][2]+color[1][2]));
      }
    }

    int greenT_int = floor(green);

    return greenT_int;
  }

  else if (humid == true)
  {
    if (humid >= check[1][0])
    {
      green = color[1][0];
    }
  
    else if (humid == check[1][1])
    {
      green = color[1][1];
    }

    else if (humid <= check[1][2])
    {
      green = color[1][2];
    }
  
    else
    {
      if ((humid > check[1][1]) && (humid < check[1][0]))
      {
        green = (humid-check[1][1])/((check[1][0]-check[1][1])*(color[1][0]-color[1][1]+color[1][1]));
      }

      else if ((humid > check[1][2]) && (humid < check[1][1]))
      {
        green = (humid-check[1][2])/((check[1][1]-check[1][2])*(color[1][1]-color[1][2]+color[1][2]));
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
    if (temp >= check[0][0])
    {
      blue = color[2][0];
    }
  
    else if (temp == check[0][1])
    {
      blue = color[2][1];
    }

    else if (temp <= check[0][2])
    {
      blue = color[2][2];
    }
  
    else
    {
      if ((temp > check[0][1]) && (temp < check[0][0]))
      {
        blue = (temp-check[0][1])/((check[0][0]-check[0][1])*(color[2][0]-color[2][1]+color[2][1]));
      }

      else if ((temp > check[0][2]) && (temp < check[0][1]))
      {
        blue = (temp-check[0][2])/((check[0][1]-check[0][2])*(color[2][1]-color[2][2]+color[2][2]));
      }
    }

    int blueT_int = floor(blue);

    return blueT_int;
  }

  else if (humid == true)
  {
    if (humid >= check[1][0])
    {
      blue = color[2][0];
    }
  
    else if (humid == check[1][1])
    {
      blue = color[2][1];
    }

    else if (humid <= check[1][2])
    {
      blue = color[2][2];
    }
  
    else
    {
      if ((humid > check[1][1]) && (humid < check[1][0]))
      {
        blue = (humid-check[1][1])/((check[1][0]-check[1][1])*(color[2][0]-color[2][1]+color[2][1]));
      }

      else if ((humid > check[1][2]) && (humid < check[1][1]))
      {
        blue = (humid-check[1][2])/((check[1][1]-check[1][2])*(color[2][1]-color[2][2]+color[2][2]));
      }
    }

    int blueH_int = floor(blue);

    return blueH_int;
  }
}

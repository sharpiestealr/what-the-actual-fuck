#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>
#include <DHT.h>

//declarar lcd
LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(2,DHT22);
Adafruit_BMP280 bmp;

byte degree[8] = { 
  B00111,
  B00101, 
  B00111, 
  B00000, 
  B00000, 
  B00000, 
  B00000, 
  B00000};

byte ohm[8] = { 
  B01110, 
  B10001, 
  B10001, 
  B10001, 
  B01010, 
  B01010, 
  B11011, 
  B00000};

int bin;
float tensao, temp, res, lum, umid, pressure;

//do only the ~
int red_one = 11; 
int red_two = 6;
int green_one = 10; 
int green_two = 5;
int blue_one = 9; 
int blue_two = 3;

int color[3][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}}; //[0-2][0-2] r, g, b
int check[2][3] = {{45, 30, 15}, {30, 50, 60}}; //[0][0-2] temperature hi lo, [1][0-2] humid lo hi

void setup() 
{
  Serial.begin(9600);
  analogReference(INTERNAL);  //Temp
  
  dht.begin();  //Umid
  bmp.begin(0x76);  //Pressão
  
  pinMode(red_one, OUTPUT);
  pinMode(green_one, OUTPUT);
  pinMode(blue_one, OUTPUT);
  pinMode(red_two, OUTPUT);
  pinMode(green_two, OUTPUT);
  pinMode(blue_two, OUTPUT);

  //setup da lcd
  lcd.init(); //starts up screen
  lcd.backlight();
  lcd.setCursor(0, 0); 
  lcd.print("Insper 2020/2"); 
  delay(2000); //printed message 
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("InstruMed");//printed message 
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print("Prof. L Poloni");//printed message 
  delay(3000);
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Grupo:"); //printed message
  delay(2000);
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Guillermo");//printed message
  lcd.setCursor(0, 1);
  lcd.print("Kuznietz"); 
  delay(2000);
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Larissa");//printed message 
  lcd.setCursor(0, 1);
  lcd.print("Jordana");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Victoria");
  lcd.setCursor(0, 1); 
  lcd.print("Souza"); 
  delay(2000);//printed message 
  lcd.clear();

  lcd.createChar(0, degree); 
  lcd.createChar(1, ohm);
   
}

static float calibra_DHT(float humid) //fix this
{
  humid = 0.995595 * humid + 2.128255;// Calibração 
  humid = humid * 19.5;
  return humid;
}

static float calibra_LM(float tensao)
{
  float temperatura = temperatura*1000;
  temperatura = 0.9762*tensao - 0.0103;//
  temperatura = temperatura *100;
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
        red = (temp-check[0][1])/((check[0][0]-check[0][1])*(color[0][0]+color[0][1]));
      }

      else if ((temp > check[0][2]) && (temp < check[0][1]))
      {
        red = (temp-check[0][2])/((check[0][1]-check[0][2])*(color[0][1]+color[0][2]));
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
        red = (humid-check[1][1])/((check[1][0]-check[1][1])*(color[0][0]+color[0][1]));
      }

      else if ((humid > check[1][2]) && (humid < check[1][1]))
      {
        red = (humid-check[1][2])/((check[1][1]-check[1][2])*(color[0][1]+color[0][2]));
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
        green = (temp-check[0][1])/((check[0][0]-check[0][1])*(color[1][0]+color[1][1]));
      }

      else if ((temp > check[0][2]) && (temp < check[0][1]))
      {
        green = (temp-check[0][2])/((check[0][1]-check[0][2])*(color[1][1]+color[1][2]));
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
        green = (humid-check[1][1])/((check[1][0]-check[1][1])*(color[1][0]+color[1][1]));
      }

      else if ((humid > check[1][2]) && (humid < check[1][1]))
      {
        green = (humid-check[1][2])/((check[1][1]-check[1][2])*(color[1][1]+color[1][2]));
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
        blue = (temp-check[0][1])/((check[0][0]-check[0][1])*(color[2][0]+color[2][1]));
      }

      else if ((temp > check[0][2]) && (temp < check[0][1]))
      {
        blue = (temp-check[0][2])/((check[0][1]-check[0][2])*(color[2][1]+color[2][2]));
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
        blue = (humid-check[1][1])/((check[1][0]-check[1][1])*(color[2][0]+color[2][1]));
      }

      else if ((humid > check[1][2]) && (humid < check[1][1]))
      {
        blue = (humid-check[1][2])/((check[1][1]-check[1][2])*(color[2][1]+color[2][2]));
      }
    }

    int blueH_int = floor(blue);

    return blueH_int;
  }
}

void loop() 
{
  //Temp
  bin = analogRead(A0);
  tensao = (bin/1023.0)*1.1;
  temp = calibra_LM(tensao);
  
  //Umid
  umid = calibra_DHT(digitalRead(2));
  
  //Pressão
  pressure = bmp.readPressure();
  
  //Lum fix this
  res = (analogRead(A1))*100.0/(5.0-tensao);      // Calc. resist. 
  lum = pow(10,6.5-1.25*log10(res));       // Calc. lumnos. 

  RGB_color(1, calcR(true, temp, false, umid), calcG(true, temp, false, umid), calcB(true, temp, false, umid));
  RGB_color(2, calcR(false, temp, true, umid), calcG(false, temp, true, umid), calcB(false, temp, true, umid));
  
  lcd.clear();
   
  lcd.setCursor(0, 0); 
  lcd.print("Resistance"); 
  lcd.write("[");
  lcd.write(byte(1));
  lcd.write("]:"); 
  lcd.setCursor(0,1);
  lcd.print(res);//prints resistance to lcd screen 
  delay(2000);
  
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("Light [Lux]:"); 
  lcd.setCursor(0,1);
  lcd.print(lum);//prints luminosity to lcd screen 
  delay(2000);
  
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.write("Temperature"); 
  lcd.write("[");
  lcd.write(byte(0));
  lcd.write("C]:"); 
  lcd.setCursor(0,1);
  lcd.print(temp);//prints temperature to lcd screen 
  delay(2000);
  
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Humidity [%]:"); 
  lcd.setCursor(0,1);
  lcd.print(umid);//prints humidity to lcd screen 
  delay(2000);//offsets the info update 

  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Pressure [hPa]:"); 
  lcd.setCursor(0,1);
  lcd.print(pressure/100);//prints pressure to lcd screen 
  delay(2000);//offsets the info update 

  
  lcd.clear(); 
}

//importar bibliotecas
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>
#include <DHT.h>
#include <math.h>

//declarar lcd
LiquidCrystal_I2C lcd(0x27,16,2);
//declarar dht22
DHT dht(2,DHT22);
//declarar bmp280
Adafruit_BMP280 bmp;

//caracteres especiais
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

//pinos de cores dos leds
int red_one = 11; 
int red_two = 6;
int green_one = 10; 
int green_two = 5;
int blue_one = 9; 
int blue_two = 3;

//listas com os valores de escalas (temperatura, umidade e cores) dos leds
int color[3][3] = {{255, 100, 0}, {100, 255, 100}, {0, 100, 255}}; //[0-2][0-2] r, g, b
int check[2][3] = {{45, 30, 15}, {30, 60, 75}}; //[0][0-2] temperature hi lo, [1][0-2] humid lo hi

void setup() 
{
  Serial.begin(9600); //inicializando o serial
  analogReference(INTERNAL); //usando a escala de 1.1 
  
  dht.begin(); //inicializando o dht22
  bmp.begin(0x76); //bmp280

  //inicializando os pinos responsáveis pelos leds
  //usando apenas pinos digitais
  pinMode(red_one, OUTPUT);
  pinMode(green_one, OUTPUT);
  pinMode(blue_one, OUTPUT);
  pinMode(red_two, OUTPUT);
  pinMode(green_two, OUTPUT);
  pinMode(blue_two, OUTPUT);

  //setup da lcd
  lcd.init(); //acendendo a tela
  lcd.backlight(); //ligando a luz de fundo
  //criação dos caracteres especiais
  lcd.createChar(0, degree); 
  lcd.createChar(1, ohm);

  //mensagem de abertura
  lcd.setCursor(0, 0); 
  lcd.print("Insper 2020/2"); 
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("InstruMed"); 
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print("Prof. L Poloni"); 
  delay(3000);
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Grupo:"); 
  delay(2000);
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Guillermo");
  lcd.setCursor(0, 1);
  lcd.print("Kuznietz"); 
  delay(2000);
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Larissa"); 
  lcd.setCursor(0, 1);
  lcd.print("Jordana");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Victoria");
  lcd.setCursor(0, 1); 
  lcd.print("Souza"); 
  delay(2000); 
  lcd.clear(); 
}

static float calibra_umid(float humid) //método que recebe a umidade do dht22 e retorna a mesma calibrada
{
  humid = 0.995595 * humid + 2.128255; //equação de calibração obtida pelo mmq
  humid = ((100*humid-2*humid)/100)-3.884517; //tirando 2% de incerteza e o erro do mmq
  return humid; //umidade calibrada
}

static float calibra_temp(float tensao, float temp) //método que recebe tensão do lm35 e temperatura do dht22 e retorna a temperatura calibrada
{
  float temperatura = tensao * 100; //transformando de °C/100 pra °C
  temperatura = sqrt((temperatura*temperatura)+(temp*temp)); //fazendo a média geométrica entre a temperatura do lm35 e dht22
  temperatura = 0.994578*temp - 0.0802; //equação de calibração obtida pelo mmq
  temperatura = temperatura-(4+0.072412+1.3323271); //tirando as incertezas (dht, lm35, equação)
  return temperatura; //temperatura calibrada
}

void RGB_color(int sensor, int red, int green, int blue) //método que pinta os leds
{
  if (sensor == 1) //led1 é o led que representa a temperatura
  {
    analogWrite(red_one, red);
    analogWrite(green_one, green);
    analogWrite(blue_one, blue);
  }

  else // led2 é o led que representa a umidade
  {
    analogWrite(red_two, red);
    analogWrite(green_two, green);
    analogWrite(blue_two, blue);
  }
}

static int calcR(bool tempC, float temp, bool humidC, float humid) //método que calcula o número para mandar para o pino vermelho
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
        red = (temp-check[0][1])/((check[0][0]-check[0][1])*(color[0][0]-color[0][1]));
      }

      else if ((temp > check[0][2]) && (temp < check[0][1]))
      {
        red = (temp-check[0][2])/((check[0][1]-check[0][2])*(color[0][1]-color[0][2]));
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
        red = (humid-check[1][1])/((check[1][0]-check[1][1])*(color[0][0]-color[0][1]));
      }

      else if ((humid > check[1][2]) && (humid < check[1][1]))
      {
        red = (humid-check[1][2])/((check[1][1]-check[1][2])*(color[0][1]-color[0][2]));
      }
    }

    int redH_int = floor(red);

    return redH_int;
  }
}

static int calcG(bool tempC, float temp, bool humidC, float humid) //método que calcula o número para mandar para o pino verde
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
        green = (temp-check[0][1])/((check[0][0]-check[0][1])*(color[1][0]-color[1][1]));
      }

      else if ((temp > check[0][2]) && (temp < check[0][1]))
      {
        green = (temp-check[0][2])/((check[0][1]-check[0][2])*(color[1][1]-color[1][2]));
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
        green = (humid-check[1][1])/((check[1][0]-check[1][1])*(color[1][0]-color[1][1]));
      }

      else if ((humid > check[1][2]) && (humid < check[1][1]))
      {
        green = (humid-check[1][2])/((check[1][1]-check[1][2])*(color[1][1]-color[1][2]));
      }
    }

    int greenH_int = floor(green);

    return greenH_int;
  }
}

static int calcB(bool tempC, float temp, bool humidC, float humid) //método que calcula o número para mandar para o pino azul
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
        blue = (temp-check[0][1])/((check[0][0]-check[0][1])*(color[2][0]-color[2][1]));
      }

      else if ((temp > check[0][2]) && (temp < check[0][1]))
      {
        blue = (temp-check[0][2])/((check[0][1]-check[0][2])*(color[2][1]-color[2][2]));
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
        blue = (humid-check[1][1])/((check[1][0]-check[1][1])*(color[2][0]-color[2][1]));
      }

      else if ((humid > check[1][2]) && (humid < check[1][1]))
      {
        blue = (humid-check[1][2])/((check[1][1]-check[1][2])*(color[2][1]-color[2][2]));
      }
    }

    int blueH_int = floor(blue);

    return blueH_int;
  }
}

void loop() 
{
  //leitura, cálculo e calibração da temperatura
  bin = analogRead(A0);
  tensao = (bin/1023.0)*1.1;
  temp = calibra_temp(tensao, dht.readTemperature());
  
  //leitura, cálculo e calibração da umidade
  umid = calibra_umid(dht.readHumidity());
  
  //leitura da pressão
  pressure = bmp.readPressure();
  
  //cálculos da resistência e luminosidade
  res = (analogRead(A1))*0.1/(5.0-tensao); 
  lum = pow(10,6.5-1.25*log10(res)); 

  //cálculo e envio dos valores dos pinos dos leds
  RGB_color(1, calcR(true, temp, false, umid), calcG(true, temp, false, umid), calcB(true, temp, false, umid)); //led 1
  RGB_color(2, calcR(false, temp, true, umid), calcG(false, temp, true, umid), calcB(false, temp, true, umid)); // led 2
  
  lcd.clear();

  //resistência em kΩ
  lcd.setCursor(0, 0); 
  lcd.print("Resistance [k");
  lcd.write(byte(1));
  lcd.print("]:"); 
  lcd.setCursor(0,1);
  lcd.print(res);
  delay(2000);

  //luminosidade em lux
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("Light [Lux]:"); 
  lcd.setCursor(0,1);
  lcd.print(lum);
  delay(2000);

  //temperatura em °C
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("Temperature ["); 
  lcd.write(byte(0));
  lcd.print("C]:"); 
  lcd.setCursor(0,1);
  lcd.print(temp);
  delay(2000);

  //humidade em %
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Humidity [%]:"); 
  lcd.setCursor(0,1);
  lcd.print(umid); 
  delay(2000);

  //pressão em hPa
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Pressure [hPa]:"); 
  lcd.setCursor(0,1);
  lcd.print(pressure/100); 
  delay(2000);
  
  lcd.clear(); 
}

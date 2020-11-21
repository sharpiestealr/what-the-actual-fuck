#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>

//declarar lcd
LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(2,DHT22);

byte degree[8] = { 
  B00111,
  B00101, 
  B00111, 
  B00000, 
  B00000, 
  B00000, 
  B00000, 
  B00000};

int bin;
float tensao, temp;

void setup() 
{
  Serial.begin(9600);
  analogReference(INTERNAL);  //Temp
  
  dht.begin();  //Umid

  //setup da lcd
  lcd.init(); //starts up screen
  lcd.backlight();
  lcd.clear();

  lcd.createChar(0, degree); 
   
}

void loop() 
{
  //Temp
  bin = analogRead(A0);
  tensao = (bin/1023.0)*1.1;
  temp = dht.readTemperature();

  Serial.print("\n");
  Serial.print(tensao);
  Serial.print("\n");
  Serial.print(temp);
  Serial.print("\n");
  
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("Temperature ["); 
  lcd.write(byte(0));
  lcd.print("C]:"); 
  lcd.setCursor(0,1);
  lcd.print(temp);//prints temperature to lcd screen 
  delay(2000);
}

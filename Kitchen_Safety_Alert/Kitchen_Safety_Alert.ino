#include <LiquidCrystal.h>
int hours;
int minutes;
int seconds;
int temp1;
int high_occured;
int count;
int set_low;
int check;
int lcd_clear;


int pin8=8;
int motorPin=9;

int sensor=A0;

int sensorValue=0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // run once:
    pinMode(pin8,OUTPUT);
    digitalWrite(pin8,LOW);
    Serial.begin(9600);
    pinMode(motorPin,OUTPUT);
    digitalWrite(motorPin,LOW); 
    lcd.begin(16, 2);
    lcd.print("NO ALARM");
    lcd.setCursor(0, 1);
    lcd.print("WITHIN 1 HOUR");
    count=0;  
    check=0;
    lcd_clear=0;
     
}

void loop() {
  // run repeatedly:
    sensorValue=analogRead(sensor);
    Serial.println(sensorValue,DEC);

    if(sensorValue>700)
    {
          if(check==1)
          {
                count=0;
                lcd.clear();
                check=0;
          }

          if(lcd_clear==0)
          {
               // count=0;
                lcd.clear();
                lcd_clear=1;
          }
          
          
          high_occured=2;
          set_low=1;
          digitalWrite(pin8,HIGH);  
          digitalWrite(motorPin,HIGH);

          
          lcd.print("WARNING!!");
          lcd.setCursor(0,1);
          lcd.print("GAS DETECTED    ");

   }
  
        else
        {
          digitalWrite(pin8,LOW);
          digitalWrite(motorPin,LOW); 
          
          if(high_occured>1)
          {
              check=1;
              count++;
              lcd.clear();
              hours = count/3600;
              temp1 = count%3600;
              minutes = temp1/60;
              seconds = temp1%60;
          
              lcd.print(hours);
              lcd.print(" hour ");
  
              lcd.setCursor(0, 1);
              // print the number of seconds since reset:
  
              lcd.print(minutes);
              lcd.print(" min ");
              lcd.print(seconds);
              lcd.print(" sec      ");

              if(seconds>20)
              {
                high_occured=0;
              }

              delay(1000);
          }

          else if(seconds>20)
          {
              count=0;
              if(set_low==1)
              {
                  lcd.clear();
              }
              set_low++;
              lcd.print("NO ALARM");
              lcd.setCursor(0, 1);
              lcd.print("WITHIN 1 HOUR   ");
              lcd_clear=0;
          
          }

    }
}

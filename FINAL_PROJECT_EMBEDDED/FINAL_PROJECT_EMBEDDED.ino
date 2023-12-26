
#include <LiquidCrystal.h>

//------------------------------------------------------------------------------
#include "RTClib.h"

RTC_DS3231 rtc;
//------------------------------------------------------------------------------
#define move_screens 6
#define move_sections 7
#define in 8
#define de 9

#define temp A1
#define dc 10

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int count = 1;
int count2 = -1;
int array2[16] = {0};
int array3[16] = {0};
int array4[16] = {0};
int array5[16] = {0};

long long timer = 0;
int x = 0;
int y = 0;

int task2 = 0;
int task3 = 0;
int task4 = 0;
int task5 = 0;

int h = 3;
int m = 49;
int s = 0;

int d = 4;
int M = 12;
int Year = 2023;

long long timer1 = 0;

int date = 1;

void setup () {
  Serial.begin(9600);
  lcd.begin(16, 2);

  //--------------------------------------------------------------------
  
  #ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
  #endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  //rtc.adjust(DateTime(2023, 12, 01, 2, 8, 0));

  //--------------------------------------------------------------------
  
  pinMode(move_screens, INPUT_PULLUP);
  pinMode(move_sections, INPUT_PULLUP);
  pinMode(in, INPUT_PULLUP);
  pinMode(de, INPUT_PULLUP);
  pinMode(dc, OUTPUT);
  
  pinMode(temp, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  timer = millis();
  timer1 = millis();

}

void loop () {
    DateTime now = rtc.now();
    
    if(digitalRead(move_screens) == LOW)              //to go to the next screen
    {
      while(digitalRead(move_screens) == LOW);
      count++;
      count2= -1;
      if(count > 5)
      {
        count = 1;
      }
    }
    
    switch(count)                     //switch to go to selected screen
    {
      case 1:
      screen1();
      break;

      case 2:
      screen2();
      break;

      case 3:
      screen3();
      break;

      case 4:
      screen4();
      break;

      case 5:
      screen5();
      break;
    }

    //=========================================================================================================
    //=========================================<<TASKS OF SCREENS>>============================================
    //=========================================================================================================

    //===========================================<<START1 SCREEN>>===============================================
    if(start_time_in_sec(array2) <= now_time_in_sec() && count2 == -1)
    {
      task2 = 1;
    }
    if(finsh_time_in_sec(array2) >= now_time_in_sec() && task2 == 1)
    {
      float var = temp_deg();
      if(var > 30)
      {
        digitalWrite(dc, HIGH);
      }
    }
    else
    {
      digitalWrite(dc, LOW);
      task2 = 0;
    }

    //===========================================<<START2 SCREEN>>===============================================
    if(start_time_in_sec(array3) <= now_time_in_sec() && count2 == -1)
    {
      task3 = 1;
    }
    if(finsh_time_in_sec(array3) >= now_time_in_sec() && task3 == 1)
    {
      float var = temp_deg();
      if(var > 30)
      {
        digitalWrite(dc, HIGH);
      }
    }
    else
    {
      digitalWrite(dc, LOW);
      task3 = 0;
    }

    //===========================================<<START3 SCREEN>>===============================================
    if(start_time_in_sec(array3) <= now_time_in_sec() && count2 == -1)
    {
      task4 = 1;
    }
    if(finsh_time_in_sec(array3) >= now_time_in_sec() && task4 == 1)
    {
      float var = temp_deg();
      if(var > 30)
      {
        digitalWrite(dc, HIGH);
      }
    }
    else
    {
      digitalWrite(dc, LOW);
      task4 = 0;
    }

    //===========================================<<START4 SCREEN>>===============================================
    if(start_time_in_sec(array5) <= now_time_in_sec() && count2 == -1)
    {
      task5 = 1;
    }
    if(finsh_time_in_sec(array5) >= now_time_in_sec() && task5 == 1)
    {
      float var = temp_deg();
      if(var > 30)
      {
        digitalWrite(dc, HIGH);
      }
    }
    else
    {
      digitalWrite(dc, LOW);
      task5 = 0;
    }
    
}

void screen1()                  //====================SCREEN NUMBER ONE===================
{
  DateTime now = rtc.now();
  lcd.setCursor(0,0);
  lcd.print("TIME: ");
  if(now.hour() < 10)
  {
    lcd.print("0");
  }
  lcd.print(now.hour());
  lcd.print(":");
  if(now.minute() < 10)
  {
    lcd.print("0");
  }
  lcd.print(now.minute());
  lcd.print(":");
  if(now.second() < 10)
  {
    lcd.print("0");
  }
  lcd.print(now.second());
  lcd.print("    ");

  lcd.setCursor(0,2);
  lcd.print("DATE: ");
  if(now.day() < 10)
  {
    lcd.print("0");
  }
  lcd.print(now.day());
  lcd.print('/');
  if(now.month() < 10)
  {
    lcd.print("0");
  }
  lcd.print(now.month());
  lcd.print('/');
  lcd.print(now.year());
  lcd.print("   ");
}

void screen2()                   //====================SCREEN NUMBER TWO===================
{
  lcd.setCursor(0,0);
  lcd.print("start1: ");
  
  lcd.print(array2[0]);
  lcd.print(array2[1]);
  lcd.print(':');
  lcd.print(array2[3]);
  lcd.print(array2[4]);
  lcd.print(':');
  lcd.print(array2[6]);
  lcd.print(array2[7]);
  lcd.print("    ");

  lcd.setCursor(0,1);
  lcd.print("finsh : ");
  lcd.print(array2[8]);
  lcd.print(array2[9]);
  lcd.print(':');
  lcd.print(array2[11]);
  lcd.print(array2[12]);
  lcd.print(':');
  lcd.print(array2[14]);
  lcd.print(array2[15]);
  lcd.print("    ");

  if(digitalRead(move_sections) == LOW)
    {
      while(digitalRead(move_sections) == LOW);
      count2++;
      if(count2 == 2 || count2 == 5 || count2 == 10 || count2 == 13 )
      {
        count2++;
      }
      if(count2 > 15)
      {
        count2 = -1;
      }
    }
    
    flash(count2);

    if(digitalRead(in) == LOW)               //++++++++++++++++++++++++++++++++
    {
      delay(200);
      while(digitalRead(de) == LOW);
      array2[count2]++;
      
      if(count2 == 0)
      {
        if(array2[count2] > 2)
        {
          array2[count2] = 2;
        }
      }
      if(count2 == 1)
      {
        if(array2[count2-1] == 0)
        {
          if(array2[count2] > 9)
          {
            array2[count2] = 9;
          }
        }
        else
        {
          if(array2[count2] > 2)
          {
            array2[count2] = 2;
          }
        }
      }
      if(count2 == 3)
      {
        if(array2[count2] > 6)
        {
          array2[count2] = 6;
        }
      }
      if(count2 == 4)
      {
        if(array2[count2-1] == 6)
        {
          array2[count2] = 0;
        }
        else
        {
          if(array2[count2] > 9)
          {
            array2[count2] = 9;
          }
        }
      }
      if(count2 == 6)
      {
        if(array2[count2] > 6)
        {
          array2[count2] = 6;
        }
      }
      if(count2 == 7)
      {
        if(array2[count2-1] == 6)
        {
          array2[count2] = 0;
        }
        else
        {
          if(array2[count2] > 9)
          {
            array2[count2] = 9;
          }
        }
      }
      if(count2 == 8)
      {
        if(array2[count2] > 2)
        {
          array2[count2] = 2;
        }
      }
      if(count2 == 9)
      {
        if(array2[count2] > 9 && array2[count2-1] == 0)
        {
          array2[count2] = 9;
        }
        if(array2[count2] > 2 && array2[count2-1] == 1)
        {
          array2[count2] = 2;
        }
      }
      if(count2 == 11)
      {
        if(array2[count2] > 6)
        {
          array2[count2] = 6;
        }
      }
      if(count2 == 12)
      {
        if(array2[count2-1] == 6)
        {
          array2[count2] = 0;
        }
        else
        {
          if(array2[count2] > 9)
          {
            array2[count2] = 9;
          }
        }
      }
      if(count2 == 14)
      {
        if(array2[count2] > 6)
        {
          array2[count2] = 6;
        }
      }
      if(count2 == 15)
      {
        if(array2[count2-1] == 6)
        {
          array2[count2] = 0;
        }
        else
        {
          if(array2[count2] > 9)
          {
            array2[count2] = 9;
          }
        }
      }
    }

    if(digitalRead(de) == LOW)        //----------------------------------
    {
      while(digitalRead(de) == LOW);
      array2[count2]--;
      if(array2[count2] < 0)
      {
         array2[count2] = 0;
      }
    }
}

void screen3()                       //====================SCREEN NUMBER THREE===================
{
  lcd.setCursor(0,0);
  lcd.print("start2: ");
  
  lcd.print(array3[0]);
  lcd.print(array3[1]);
  lcd.print(':');
  lcd.print(array3[3]);
  lcd.print(array3[4]);
  lcd.print(':');
  lcd.print(array3[6]);
  lcd.print(array3[7]);
  lcd.print("    ");

  lcd.setCursor(0,1);
  lcd.print("finsh : ");
  lcd.print(array3[8]);
  lcd.print(array3[9]);
  lcd.print(':');
  lcd.print(array3[11]);
  lcd.print(array3[12]);
  lcd.print(':');
  lcd.print(array3[14]);
  lcd.print(array3[15]);
  lcd.print("    ");

  if(digitalRead(move_sections) == LOW)
    {
      while(digitalRead(move_sections) == LOW);
      count2++;
      if(count2 == 2 || count2 == 5 || count2 == 10 || count2 == 13 )
      {
        count2++;
      }
      if(count2 > 15)
      {
        count2 = -1;
      }
    }
    
    flash(count2);

    if(digitalRead(in) == LOW)               //++++++++++++++++++++++++++++++++
    {
      delay(200);
      while(digitalRead(de) == LOW);
      array3[count2]++;
      
      if(count2 == 0)
      {
        if(array3[count2] > 1)
        {
          array3[count2] = 1;
        }
      }
      if(count2 == 1)
      {
        if(array3[count2-1] == 0)
        {
          if(array3[count2] > 9)
          {
            array3[count2] = 9;
          }
        }
        else
        {
          if(array3[count2] > 2)
          {
            array3[count2] = 2;
          }
        }
      }
      if(count2 == 3)
      {
        if(array3[count2] > 6)
        {
          array3[count2] = 6;
        }
      }
      if(count2 == 4)
      {
        if(array3[count2-1] == 6)
        {
          array3[count2] = 0;
        }
        else
        {
          if(array3[count2] > 9)
          {
            array3[count2] = 9;
          }
        }
      }
      if(count2 == 6)
      {
        if(array3[count2] > 6)
        {
          array3[count2] = 6;
        }
      }
      if(count2 == 7)
      {
        if(array3[count2-1] == 6)
        {
          array3[count2] = 0;
        }
        else
        {
          if(array3[count2] > 9)
          {
            array3[count2] = 9;
          }
        }
      }
      if(count2 == 8)
      {
        if(array3[count2] > 1)
        {
          array3[count2] = 1;
        }
      }
      if(count2 == 9)
      {
        if(array3[count2] > 9 && array2[count2-1] == 0)
        {
          array3[count2] = 9;
        }
        if(array3[count2] > 2 && array2[count2-1] == 1)
        {
          array3[count2] = 2;
        }
      }
      if(count2 == 11)
      {
        if(array3[count2] > 6)
        {
          array3[count2] = 6;
        }
      }
      if(count2 == 12)
      {
        if(array3[count2-1] == 6)
        {
          array3[count2] = 0;
        }
        else
        {
          if(array3[count2] > 9)
          {
            array3[count2] = 9;
          }
        }
      }
      if(count2 == 14)
      {
        if(array3[count2] > 6)
        {
          array3[count2] = 6;
        }
      }
      if(count2 == 15)
      {
        if(array3[count2-1] == 6)
        {
          array3[count2] = 0;
        }
        else
        {
          if(array3[count2] > 9)
          {
            array3[count2] = 9;
          }
        }
      }
    }

    if(digitalRead(de) == LOW)        //----------------------------------
    {
      while(digitalRead(de) == LOW);
      array3[count2]--;
      if(array3[count2] < 0)
      {
         array3[count2] = 0;
      }
    }
  
}

void screen4()                    //====================SCREEN NUMBER FOUR===================
{
  lcd.setCursor(0,0);
  lcd.print("start3: ");
  
  lcd.print(array4[0]);
  lcd.print(array4[1]);
  lcd.print(':');
  lcd.print(array4[3]);
  lcd.print(array4[4]);
  lcd.print(':');
  lcd.print(array4[6]);
  lcd.print(array4[7]);
  lcd.print("    ");

  lcd.setCursor(0,1);
  lcd.print("finsh : ");
  lcd.print(array4[8]);
  lcd.print(array4[9]);
  lcd.print(':');
  lcd.print(array4[11]);
  lcd.print(array4[12]);
  lcd.print(':');
  lcd.print(array4[14]);
  lcd.print(array4[15]);
  lcd.print("    ");

  if(digitalRead(move_sections) == LOW)
    {
      while(digitalRead(move_sections) == LOW);
      count2++;
      if(count2 == 2 || count2 == 5 || count2 == 10 || count2 == 13 )
      {
        count2++;
      }
      if(count2 > 15)
      {
        count2 = -1;
      }
    }
    
    flash(count2);

    if(digitalRead(in) == LOW)               //++++++++++++++++++++++++++++++++
    {
      delay(200);
      while(digitalRead(de) == LOW);
      array4[count2]++;
      
      if(count2 == 0)
      {
        if(array4[count2] > 1)
        {
          array4[count2] = 1;
        }
      }
      if(count2 == 1)
      {
        if(array4[count2-1] == 0)
        {
          if(array4[count2] > 9)
          {
            array4[count2] = 9;
          }
        }
        else
        {
          if(array4[count2] > 2)
          {
            array4[count2] = 2;
          }
        }
      }
      if(count2 == 3)
      {
        if(array4[count2] > 6)
        {
          array4[count2] = 6;
        }
      }
      if(count2 == 4)
      {
        if(array4[count2-1] == 6)
        {
          array4[count2] = 0;
        }
        else
        {
          if(array4[count2] > 9)
          {
            array4[count2] = 9;
          }
        }
      }
      if(count2 == 6)
      {
        if(array4[count2] > 6)
        {
          array4[count2] = 6;
        }
      }
      if(count2 == 7)
      {
        if(array4[count2-1] == 6)
        {
          array4[count2] = 0;
        }
        else
        {
          if(array4[count2] > 9)
          {
            array4[count2] = 9;
          }
        }
      }
      if(count2 == 8)
      {
        if(array4[count2] > 1)
        {
          array4[count2] = 1;
        }
      }
      if(count2 == 9)
      {
        if(array4[count2] > 9 && array2[count2-1] == 0)
        {
          array4[count2] = 9;
        }
        if(array4[count2] > 2 && array2[count2-1] == 1)
        {
          array4[count2] = 2;
        }
      }
      if(count2 == 11)
      {
        if(array4[count2] > 6)
        {
          array4[count2] = 6;
        }
      }
      if(count2 == 12)
      {
        if(array4[count2-1] == 6)
        {
          array4[count2] = 0;
        }
        else
        {
          if(array4[count2] > 9)
          {
            array4[count2] = 9;
          }
        }
      }
      if(count2 == 14)
      {
        if(array4[count2] > 6)
        {
          array4[count2] = 6;
        }
      }
      if(count2 == 15)
      {
        if(array4[count2-1] == 6)
        {
          array4[count2] = 0;
        }
        else
        {
          if(array4[count2] > 9)
          {
            array4[count2] = 9;
          }
        }
      }
    }

    if(digitalRead(de) == LOW)        //----------------------------------
    {
      while(digitalRead(de) == LOW);
      array4[count2]--;
      if(array4[count2] < 0)
      {
         array4[count2] = 0;
      }
    }
  
}

void screen5()                         //====================SCREEN NUMBER FIVE===================
{  
  lcd.setCursor(0,0);
  lcd.print("start4: ");
  
  lcd.print(array5[0]);
  lcd.print(array5[1]);
  lcd.print(':');
  lcd.print(array5[3]);
  lcd.print(array5[4]);
  lcd.print(':');
  lcd.print(array5[6]);
  lcd.print(array5[7]);
  lcd.print("    ");

  lcd.setCursor(0,1);
  lcd.print("finsh : ");
  lcd.print(array5[8]);
  lcd.print(array5[9]);
  lcd.print(':');
  lcd.print(array5[11]);
  lcd.print(array5[12]);
  lcd.print(':');
  lcd.print(array5[14]);
  lcd.print(array5[15]);
  lcd.print("    ");

  if(digitalRead(move_sections) == LOW)
    {
      while(digitalRead(move_sections) == LOW);
      count2++;
      if(count2 == 2 || count2 == 5 || count2 == 10 || count2 == 13 )
      {
        count2++;
      }
      if(count2 > 15)
      {
        count2 = -1;
      }
    }
    
    flash(count2);

    if(digitalRead(in) == LOW)               //++++++++++++++++++++++++++++++++
    {
      delay(200);
      while(digitalRead(de) == LOW);
      array5[count2]++;
      
      if(count2 == 0)
      {
        if(array5[count2] > 1)
        {
          array5[count2] = 1;
        }
      }
      if(count2 == 1)
      {
        if(array5[count2-1] == 0)
        {
          if(array5[count2] > 9)
          {
            array5[count2] = 9;
          }
        }
        else
        {
          if(array5[count2] > 2)
          {
            array5[count2] = 2;
          }
        }
      }
      if(count2 == 3)
      {
        if(array5[count2] > 6)
        {
          array5[count2] = 6;
        }
      }
      if(count2 == 4)
      {
        if(array5[count2-1] == 6)
        {
          array5[count2] = 0;
        }
        else
        {
          if(array5[count2] > 9)
          {
            array5[count2] = 9;
          }
        }
      }
      if(count2 == 6)
      {
        if(array5[count2] > 6)
        {
          array5[count2] = 6;
        }
      }
      if(count2 == 7)
      {
        if(array5[count2-1] == 6)
        {
          array5[count2] = 0;
        }
        else
        {
          if(array5[count2] > 9)
          {
            array5[count2] = 9;
          }
        }
      }
      if(count2 == 8)
      {
        if(array5[count2] > 1)
        {
          array5[count2] = 1;
        }
      }
      if(count2 == 9)
      {
        if(array5[count2] > 9 && array2[count2-1] == 0)
        {
          array5[count2] = 9;
        }
        if(array5[count2] > 2 && array2[count2-1] == 1)
        {
          array5[count2] = 2;
        }
      }
      if(count2 == 11)
      {
        if(array5[count2] > 6)
        {
          array5[count2] = 6;
        }
      }
      if(count2 == 12)
      {
        if(array5[count2-1] == 6)
        {
          array5[count2] = 0;
        }
        else
        {
          if(array5[count2] > 9)
          {
            array5[count2] = 9;
          }
        }
      }
      if(count2 == 14)
      {
        if(array5[count2] > 6)
        {
          array5[count2] = 6;
        }
      }
      if(count2 == 15)
      {
        if(array5[count2-1] == 6)
        {
          array5[count2] = 0;
        }
        else
        {
          if(array5[count2] > 9)
          {
            array5[count2] = 9;
          }
        }
      }
    }

    if(digitalRead(de) == LOW)        //----------------------------------
    {
      while(digitalRead(de) == LOW);
      array5[count2]--;
      if(array5[count2] < 0)
      {
         array5[count2] = 0;
      }
    }
  
}

void flash(int i)                      //to flash on the chosen location
{
  if(millis()-timer >= 200)
  {
    timer = millis();
    x = 1;
  }
  
  if(i<8 && 1 == x)
  {
    lcd.setCursor(i + 8, 0);
    //delay(150);
    lcd.print(" ");
    //delay(150);
  }
  if(i>=8 && 1 == x)
  {
    lcd.setCursor(i, 1);
    //delay(150);
    lcd.print(" ");
    //delay(150);
  }
  
}

int now_time_in_sec()                      //to convert present time to seconds
{
  DateTime now = rtc.now();
  int ret = 0;
  int hours1 = 0;
  int minutes1 = 0;
  int seconds1 = 0;
  hours1 = (now.hour())*60*60;
  minutes1 = (now.minute())*60;
  seconds1 = (now.second());
  ret = hours1+minutes1+seconds1;
  return ret;
}

int start_time_in_sec(int array_sec[])    //to convert start time to seconds
{
  int ret = 0;
  int hours1 = 0;
  int minutes1 = 0;
  int seconds1 = 0;
  hours1 = (array_sec[0]*10 + array_sec[1])*60*60;
  minutes1 = (array_sec[3]*10 + array_sec[4])*60;
  seconds1 = (array_sec[6]*10 + array_sec[7]);
  ret = hours1+minutes1+seconds1;
  return ret;
}

int finsh_time_in_sec(int array_sec[])    //to convert finsh time to seconds
{
  int ret = 0;
  int hours1 = 0;
  int minutes1 = 0;
  int seconds1 = 0;
  hours1 = (array_sec[8]*10 + array_sec[9])*60*60;
  minutes1 = (array_sec[11]*10 + array_sec[12])*60;
  seconds1 = (array_sec[14]*10 + array_sec[15]);
  ret = hours1+minutes1+seconds1;
  return ret;
}

float temp_deg(){
  float var = analogRead(temp);
  var = var*4.25-3995;
  Serial.println(var);
  return var;
}

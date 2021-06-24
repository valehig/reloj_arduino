#include <LiquidCrystal.h>
LiquidCrystal lcd(0,1,2,3,4,5);

#define pinButtonHoras 6
#define pinButtonMinutos 7
#define pinButtonSegundos 8


unsigned char Horas = 8, Minutos = 00, Segundos = 00;
unsigned int TimeReloj = 0;
unsigned int TimerRefrescarLCD = 0;

bool FlagpinButtonHoras;
bool FlagpinButtonMinutos;
bool FlagpinButtonSegundos;

void setup()
{
  lcd.begin(16,2);
  lcd.print("HORA:");
  pinMode (pinButtonHoras, INPUT);
  pinMode (pinButtonMinutos, INPUT);
  pinMode (pinButtonSegundos, INPUT);
}

void loop()
{
   if(digitalRead(pinButtonHoras) == LOW && FlagpinButtonHoras == LOW)
  {
    FlagpinButtonHoras = HIGH;
    Horas = Horas  + 1;
    if(Horas>23)
    {
      Horas=0;
    }
  }
  if(digitalRead(pinButtonHoras) == HIGH)
  {
    FlagpinButtonHoras = LOW;
  }

  if(digitalRead(pinButtonMinutos) == LOW && FlagpinButtonMinutos == LOW)
  {
    FlagpinButtonMinutos = HIGH;
    Minutos = Minutos  + 1;
    if(Minutos>59)
    {
      Minutos=0;
    }
  }
  if(digitalRead(pinButtonMinutos) == HIGH)
  {
    FlagpinButtonMinutos = LOW;
  }

  if(digitalRead(pinButtonSegundos) == LOW && FlagpinButtonSegundos == LOW)
  {
    FlagpinButtonSegundos = HIGH;
    Segundos= Segundos  + 1;
    if(Segundos>59)
    {
      Segundos=0;
    }
  }

  if(digitalRead(pinButtonSegundos) == HIGH)
  {
    FlagpinButtonSegundos = LOW;
  }
  
  MyTimers();
  //tarea 1: CLOCK
  if(TimeReloj >= 1000)
  {
    TimeReloj -= 1000;
    Reloj();
  }

  //tarea 2: Refrescar LCD
  if(TimerRefrescarLCD >= 200)
  {
    TimerRefrescarLCD = 0;
    lcd.setCursor(7,0);
    lcd.write(Horas/10 + 0x30);
    lcd.write(Horas%10 + 0x30);
    lcd.write(':');
    lcd.write(Minutos/10 + 0x30);
    lcd.write(Minutos%10 + 0x30);
    lcd.write(':');
    lcd.write(Segundos /10 + 0x30);
    lcd.write(Segundos %10 + 0x30);
  }
}
void RunMyTimers(unsigned int ms)
{
  TimeReloj += ms;
  TimerRefrescarLCD += ms;
}

void MyTimers(void)
{
  static unsigned long AuxTimeRef;
  unsigned long auxTime = millis();
  if(auxTime>AuxTimeRef) RunMyTimers(auxTime-AuxTimeRef); else RunMyTimers(auxTime+4294967295L-AuxTimeRef+1);
  AuxTimeRef=auxTime;  
}
void Reloj()
{
  {
    Segundos++;
    if(Segundos > 59)
    {
      Segundos -= 60;
      Minutos++;
      if(Minutos > 59)
      {
        Minutos = 0;
        Horas++;
        if(Horas >23)
        {
          Horas = 0;
        }
      }
    }

  }
}

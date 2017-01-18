/*
 * SimpleTimerAlarmExample.pde
 *
 * Based on usage example for Time + TimeAlarm libraries
 *
 * A timer is called every 15 seconds
 * Another timer is called once only after 10 seconds
 * A third timer is called 10 times.
 *
 */
#include <LiquidCrystal.h>
LiquidCrystal lcd(3, 4, 5, 6, 7, 8 );
#include <EEPROM.h>
int addr = 1;
#include <SimpleTimer.h>
int buton = 9;
int butondurumu = 0;         // variable for reading the pushbutton status

// There must be one global SimpleTimer object.
// More SimpleTimer objects can be created and run,
// although there is little point in doing so.
SimpleTimer timer;
void(* resetFunc) (void) = 0;
void OnceOnlyTask() {
for (int z= 0 ;  z < 10000 ; z = z+1 ){
         for (int i = 0; i < 3000; i = i + 1){
      tone(10, i,20);
     
   } 
   tone(10, 3000,200);
    for (int j = 30000; j > 0; j = j - 1){

     
   }

  Serial.println("This timer only triggers once");  
}
}

// print current arduino "uptime" on the serial port
void DigitalClockDisplay() {
  lcd.clear();
  lcd.setCursor(4,0);
  int h,m,s;
  s = millis() / 1000;
  m = s / 60;
  h = s / 3600;
  s = s - m * 60;
  m = m - h * 60;
  Serial.print(h);
  lcd.print(h);
  printDigits(m);
  printDigits(s);
  Serial.println();
}

//
// utility function for digital clock display:
// prints preceding colon and leading 0
//
void printDigits(int digits) {
  Serial.print(":");
  lcd.print(":");

  if(digits < 10){
    Serial.print('0');
    lcd.print('0');}
  lcd.print(digits);
  Serial.print(digits);
}

void setup() {
  Serial.begin(9600);
lcd.begin(16, 2);
  pinMode(buton, INPUT);     

  // this is where the "polling" occurs
  int oku = EEPROM.read(addr);
  unsigned long  alarm =oku*60;
  alarm = alarm * 1000; 
  timer.setTimeout(alarm, OnceOnlyTask);
  timer.setInterval(1000, DigitalClockDisplay);
lcd.clear();
lcd.print(oku);
lcd.print ("Dk.SONRA ALARM");
lcd.setCursor(0,1);
lcd.print ("  AKTIF OLACAK");

delay(5000);
}

void loop() {

  timer.run();
  
  butondurumu = digitalRead(buton);

int a= analogRead(A0);

 int zaman = map(a ,0,1023,1,120);

lcd.setCursor(0,1);
lcd.print(zaman);
lcd.print (" DK.ALARM CAL");
Serial.println (zaman,DEC);
  if (butondurumu == HIGH) { 
  
  EEPROM.write(addr,zaman );
  for (int g=0; g>5;g++){
  tone(10,2000,100);
  delay(200);
  tone(10,2000,100);
  }
 resetFunc(); //call reset
 } 

}

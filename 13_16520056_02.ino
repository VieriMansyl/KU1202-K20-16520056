#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);	//pin Arduino terhubung LCD
const int ping_Pin = A1;				//pin Arduino terhubung Ultrasonic Sensor
long dur, cm;							//simpan nilai durasi dan jarak (cm)

void setup() {
  lcd.begin(16, 2);						//atur jumlah kolom dan baris LCD
  lcd.print("PING Sensor");
}

void loop() {
  cm = read_sensor_ultrasonic();

  /*Print to LCD*/
  lcd.setCursor(0,1);					//atur kursor ke kolom 0 baris 1
  lcd.print("Jarak ");
  lcd.setCursor(6,1);					//atur kursor ke kolom 6 baris 1
  lcd.print(cm);						//cetak nilai jarak
  print_unit_cm(cm);					//cetak satuan (cm)
}


int read_sensor_ultrasonic(){
	pinMode(ping_Pin, OUTPUT);   			//atur pin sebagai OUTPUT
    digitalWrite(ping_Pin, LOW); 			//beri sinyal awal LOW
    delayMicroseconds(2);		   			//jeda 2μs
    digitalWrite(ping_Pin, HIGH); 			//trigger sensor dengan sinyal HIGH
    delayMicroseconds(5);		   			//trigger sensor selama 5μs
    digitalWrite(ping_Pin, LOW);  			//beri sinyal LOW

  	pinMode(ping_Pin, INPUT);				//atur pin sebagai INPUT
    dur = pulseIn(ping_Pin, HIGH);			//sinyal HIGH untuk dapat durasi (dalam μs)
    cm = microsec_to_centi(dur);	//konversi μs ke cm
	
  	if (cm >= 2 and cm <= 300)
    {return cm;}
    else
    {return 0;}
}

long microsec_to_centi(long ms) {
    return ms / 29 / 2;
}

void print_unit_cm(long cm){
  	if (cm >= 2 and cm < 10)
    {lcd.setCursor(7,1);}
   	else if (cm >= 10 and cm < 100)
    {lcd.setCursor(8,1);}
    else if (cm >= 100 and cm <= 300)
    {lcd.setCursor(9,1);}
	else
    {lcd.setCursor(9,1);}
    lcd.print(" cm");
}
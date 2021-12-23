#include <DHT.h> //Library DHT
#include <LiquidCrystal_I2C.h>// Library I2C
LiquidCrystal_I2C lcd (0x27, 16, 2);
DHT dht(2, DHT22); //Pin, Jenis DHT
#define pompa 3 // Pin relay untuk pompa ada di pin 3
#define fan 4 // Pin relay untuk kipas ada di pin 4
 
void setup(){
 Serial.begin(9600);
 pinMode(pompa, OUTPUT);
 pinMode(fan,OUTPUT);
 digitalWrite(fan,LOW);
 digitalWrite(pompa,LOW);
 
 // setup LCD 16x2 dengan modul i2c
 lcd.init();
 lcd.backlight();
 lcd.clear();
 // setup dht sensor
 dht.begin();
}
 
void loop(){
  //foat dapat di ganti dengan byte jika tidak ingin ada tambahan .00
 byte kelembaban = dht.readHumidity();
 byte suhu = dht.readTemperature();
 Serial.print("suhu: ");
 Serial.println(suhu);
 Serial.print(" ");
 Serial.print("kelembaban: ");
 Serial.print(kelembaban);


 lcd.setCursor (0,0);
 lcd.print("Suhu : ");
 lcd.print(suhu); 
 lcd.print((char)223);
 lcd.print("C");

 lcd.setCursor (0,1);
 lcd.print("Kelembaban : ");
 lcd.print(kelembaban); 
 lcd.print((char)223);
 lcd.print("%");


 if (suhu <26 && kelembaban <80 ){
  // 1
  digitalWrite(fan,LOW);
  digitalWrite(pompa,HIGH);

  // LCD PRINT
  lcd.setCursor (0,1);
  lcd.print("Suhu : Dingin");
  delay(1000);
  lcd.print("Kelembaban : Kering");
  delay(1000);
 } 
 else if (suhu <26 && kelembaban >=80 && kelembaban <=90) {
  // 2
  digitalWrite(fan,LOW);
  digitalWrite(pompa,LOW);

  // LCD PRINT
  lcd.setCursor (0,1);
  lcd.print("Suhu : Dingin");
  delay(1000);
  lcd.print("Kelembaban : Sedang");
  delay(1000);
 }
 else if (suhu <26 && kelembaban >90) {
  // 3
  digitalWrite(fan,LOW);
  digitalWrite(pompa,LOW);

  // LCD PRINT
  lcd.setCursor (0,1);
  lcd.print("Suhu : Dingin");
  delay(1000);
  lcd.print("Kelembaban : Basah");
  delay(1000);
 }
 else if (suhu >=26 && suhu <=30 && kelembaban <80) {
  // 4
  digitalWrite(fan,LOW);
  digitalWrite(pompa,HIGH);

  // LCD PRINT
  lcd.setCursor (0,1);
  lcd.print("Suhu : Sedang");
  delay(1000);
  lcd.print("Kelembaban : Kering");
  delay(1000);
 }
 else if (suhu >=26 && suhu <=30 && kelembaban >=80 && kelembaban <=90) {
  // 5
  digitalWrite(fan,LOW);
  digitalWrite(pompa,LOW);

  // LCD PRINT
  lcd.setCursor (0,1);
  lcd.print("Suhu : Sedang");
  delay(1000);
  lcd.print("Kelembaban : Sedang");
  delay(1000);
 }
 else if (suhu >=26 && suhu <=30 && kelembaban >90) {
  // 6
  digitalWrite(fan,LOW);
  digitalWrite(pompa,LOW);

  // LCD PRINT
  lcd.setCursor (0,1);
  lcd.print("Suhu : Sedang");
  delay(1000);
  lcd.print("Kelembaban : Basah");
  delay(1000);
 }
 else if (suhu >30 && kelembaban <80) {
  // 7
  digitalWrite(fan,HIGH);
  digitalWrite(pompa,HIGH);

  // LCD PRINT
  lcd.setCursor (0,1);
  lcd.print("Suhu : Panas");
  delay(1000);;
  lcd.print("Kelembaban : Kering");
  delay(1000);
 }
 else if (suhu >30 && kelembaban >=80 && kelembaban <=90) {
  // 8
  digitalWrite(fan,HIGH);
  digitalWrite(pompa,LOW);

  // LCD PRINT
  lcd.setCursor (0,1);
  lcd.print("Suhu : Panas");
  delay(1000);
  lcd.print("Kelembaban : Sedang");
  delay(1000);
 } 
 else if (suhu >30 && kelembaban >90) {
  // 9
  digitalWrite(fan,HIGH);
  digitalWrite(pompa,LOW);

  // LCD PRINT
  lcd.setCursor (0,1);
  lcd.print("Suhu : Panas");
  delay(1000);
  lcd.print("Kelembaban : Basah");
  delay(1000);
 }else{
   // KONDISI TIDAK TERPENUHI
  digitalWrite(fan,LOW);
  digitalWrite(pompa,LOW);

  // LCD PRINT
  lcd.setCursor (0,1);
  lcd.print("KONDISI TIDAK TERPENUHI");
  delay(1000);
 }
 
}

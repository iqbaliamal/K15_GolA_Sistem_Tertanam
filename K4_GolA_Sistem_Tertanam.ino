//===== INISIALISASI ===== //
// DHT 22
#include <DHT.h>
DHT dht(2, DHT22);

// LCD 16 x 2
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 16, 2);

// Output
#define pompa 3 // Pin relay untuk pompa ada di pin 3
#define fan 4 // Pin relay untuk kipas ada di pin 4
 
void setup(){
Serial.begin(9600);
 
pinMode(pompa,OUTPUT);
pinMode(fan,OUTPUT); 

digitalWrite(pompa,1);
digitalWrite(fan,1);
// 1 = OFF
// 0 = ON

// setup LCD 16x2 dengan modul I2C
lcd.init();
lcd.backlight();
lcd.clear();
// setup sensor DHT
dht.begin();

}
 
void loop(){
  lcd.setCursor(0,0);
  lcd.print("  Membaca Suhu  ");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print(" dan Kelembaban ");
  delay(5000);
  lcd.clear();
  
  cetak();
  
  if (suhu < 25.00 && kelembaban < 71.30 ){
  // Rule 1

  // LCD PRINT
  sDingin();
  kKering();
  delay(3000);
  lcd.clear();

  tKipasOff();
  tPompaOn();
  
  Serial.println("Suhu: Dingin");
  Serial.println("kelembaban: Kering");
  
  digitalWrite(fan,1);
  digitalWrite(pompa,0);

  delay(10000);
  lcd.clear();
 } 
 else if (suhu < 25.00 && kelembaban >= 71.30 && kelembaban <= 80.00) {
  // Rule 2

  // LCD PRINT
  sDingin();
  kNormal();
  delay(3000);
  lcd.clear();

  tKipasOff();
  tPompaOff();
  
  Serial.println("Suhu: Dingin");
  Serial.println("kelembaban: Normal");
  
  digitalWrite(fan,1);
  digitalWrite(pompa,1);

  delay(10000);
  lcd.clear();
 }
 else if (suhu < 25.00 && kelembaban > 80.00) {
  // Rule 3
  // LCD PRINT
  sDingin();
  kBasah();
  delay(3000);
  lcd.clear();

  tKipasOff();
  tPompaOff();
  
  Serial.println("Suhu: Dingin");
  Serial.println("kelembaban: Basah");
  
  digitalWrite(fan,1);
  digitalWrite(pompa,1);

  delay(10000);
  lcd.clear();
 }
 else if (suhu >= 25.00 && suhu <= 27.50 && kelembaban < 71.30) {
  // 4
  // LCD PRINT
  sNormal();
  kKering();
  delay(3000);
  lcd.clear();

  tKipasOff();
  tPompaOn();
  
  Serial.println("Suhu: Normal");
  Serial.println("kelembaban: Kering");
  
  digitalWrite(fan,1);
  digitalWrite(pompa,0);

  delay(10000);
  lcd.clear();
 }
 else if (suhu >= 25.00 && suhu <= 27.50 && kelembaban >= 71.30 && kelembaban <= 80.00) {
  // 5
  // LCD PRINT
  sNormal();
  kNormal();
  delay(3000);
  lcd.clear();

  tKipasOff();
  tPompaOff();
  
  Serial.println("Suhu: Normal");
  Serial.println("kelembaban: Normal");
  
  digitalWrite(fan,1);
  digitalWrite(pompa,1);

  delay(10000);
  lcd.clear();
 }
 else if (suhu >= 25.00 && suhu <= 27.50 && kelembaban > 80.00) {
  // 6
  // LCD PRINT
  sNormal();
  kBasah();
  delay(3000);
  lcd.clear();

  tKipasOff();
  tPompaOff();
  
  Serial.println("Suhu: Normal");
  Serial.println("kelembaban: Basah");
  
  digitalWrite(fan,1);
  digitalWrite(pompa,1);

  delay(10000);
  lcd.clear();
 }
 else if (suhu > 27.50 && kelembaban < 71.30) {
  // 7
  // LCD PRINT
  sPanas();
  kKering();
  delay(3000);
  lcd.clear();

  tKipasOn();
  tPompaOn();
  
  Serial.println("Suhu: Panas");
  Serial.println("kelembaban: Kering");
  
  digitalWrite(fan,0);
  digitalWrite(pompa,0);

  delay(10000);
  lcd.clear();
 }
 else if (suhu > 27.50 && kelembaban >= 71.30 && kelembaban <= 80.00) {
  // 8
  // LCD PRINT
  sPanas();
  kNormal();
  delay(3000);
  lcd.clear();

  tKipasOn();
  tPompaOff();
  
  Serial.println("Suhu: Panas");
  Serial.println("kelembaban: Normal");
  
  digitalWrite(fan,0);
  digitalWrite(pompa,1);

  delay(10000);
  lcd.clear();
 } 
 else if (suhu > 27.50 && kelembaban > 80.00) {
  // 9
  // LCD PRINT
  sPanas();
  kBasah();
  delay(3000);
  lcd.clear();

  tKipasOn();
  tPompaOff();
  
  Serial.println("Suhu: Panas");
  Serial.println("kelembaban: Basah");
  
  digitalWrite(fan,0);
  digitalWrite(pompa,1);

  delay(10000);
  lcd.clear();
 }
 else
 {
    // KONDISI TIDAK TERPENUHI

    // LCD PRINT
    for (int i=0; i<5; i++){
      lcd.setCursor (0,0);
      lcd.print(" KONDISI TIDAK  ");
      lcd.setCursor(0,1);
      lcd.print("   TERPENUHI    ");
      delay(1000);
      lcd.clear();
      delay(1000);    
    }
    delay(2000);
 }

  digitalWrite(pompa,1);
  digitalWrite(fan,1);

  istirahat();
}

void cetak(){
  float kelembaban = dht.readHumidity();
  float suhu = dht.readTemperature(); 

  lcd.setCursor(0,0);
  lcd.print("Suhu ");
  lcd.print(suhu);
  lcd.print(" C       ");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Kelembaban ");
  lcd.print(kelembaban);
  lcd.print(" % ");
  delay(5000);
  lcd.clear();

    //float dapat di ganti dengan byte jika tidak ingin ada tambahan .00 
  Serial.print("suhu: ");
  Serial.println(suhu);
  Serial.print(" ");
  Serial.print("kelembaban: ");
  Serial.println(kelembaban);
}

void istirahat(){
  lcd.setCursor(0,0);
  lcd.print(" S E L E S A I  ");
  delay(2000);
  lcd.clear();
  lcd.print("   Sistem Off   ");
  delay(3000);
  lcd.clear();
  lcd.noBacklight();
  delay(10000);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("  Sistem Aktif  ");
  delay(2000);
  lcd.clear();
  
  for (int i=10; i>0; i--){
    lcd.setCursor(0,0);
    lcd.print("     Sensor     ");
    lcd.setCursor(0,1);
    lcd.print("Membaca dalam ");
    lcd.print(i);
    lcd.print(" ");
    delay(1000); 
    lcd.clear();
  }
}

void sDingin(){
  lcd.setCursor(0,0);
  lcd.print("  Suhu  Dingin  ");
}
void sNormal(){
  lcd.setCursor(0,0);
  lcd.print("  Suhu  Normal  ");
}
void sPanas(){
  lcd.setCursor(0,0);
  lcd.print("  Suhu  Panas   ");
}
void kKering(){
  lcd.setCursor(0,1);
  lcd.print("Kelembaban Kering");
}
void kNormal(){
  lcd.setCursor(0,1);
  lcd.print("Kelembaban Normal");
}
void kBasah(){
  lcd.setCursor(0,1);
  lcd.print("Kelembaban Basah");
}

void tKipasOn(){
  lcd.setCursor(0,0);
  lcd.print("Kipas Menyala");
}
void tKipasOff(){
  lcd.setCursor(0,0);
  lcd.print("Kipas Mati");
}
void tPompaOn(){
  lcd.setCursor(0,1);
  lcd.print("Pompa Menyala");
}
void tPompaOff(){
  lcd.setCursor(0,1);
  lcd.print("Pompa Mati");
}

#include <DHT.h> //library DHT
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2 //pin DATA konek ke pin 2 Arduino
#define BUZZER 3 //pin buzzer konek ke pin 3 Arduino
#define LED 4 //pin LED konek ke pin 4 Arduino

#define DHTTYPE DHT11 //tipe sensor DHT11

DHT dht(DHTPIN, DHTTYPE); //buat object dht(koneksi pin,set sensor)
LiquidCrystal_I2C lcd(0x27, 16, 2);

//inisialisasi variable global suhu
float suhu;
 
void setup()
{
  //inisialisasi
  Serial.begin(9600); //baud 9600
  lcd.begin();
  dht.begin();
  
  pinMode(BUZZER,OUTPUT);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  digitalWrite(BUZZER,HIGH);
}

void loop()
{
  //baca nilai suhu DHT
  suhu = dht.readTemperature();//baca suhu

  //pengondisian konektivitas sensor DHT 
  if (isnan(suhu)) { //jika tidak ada hasil
    Serial.println("DHT11 tidak terhubung, Tolong Periksa Kembali");
    return;
  }else{
    // tampilakan data diserial monitor
    Serial.print("Suhu: ");  //kirim serial "Suhu"
    Serial.print(suhu);      //kirim serial nilai suhu
    Serial.println(" C");    //kirim serial "C" Celcius 
    displayTemperature(suhu); 
    //pengkondisian alarm ketika suhu mencapai setpoint
    //function alertTemperature(value temperature, setPoint alert, pin LED, pin Buzzer, delay beep);
    alertTemperature(suhu, 35.0, LED, BUZZER, 1000);
  }
  delay(300);//tunda 1 detik untuk pembacaan berikutnya
}

//function alarm temperature
void alertTemperature(float input, float setPoint, byte led, byte buzzer, uint16_t tundaWaktu){
  if(input>=setPoint){
    digitalWrite(led,HIGH);
    digitalWrite(buzzer,LOW);
    delay(tundaWaktu);
    digitalWrite(buzzer,HIGH);
  } else{
    digitalWrite(LED,LOW);
    digitalWrite(BUZZER,HIGH);
  }
}

void displayTemperature(float data){
  lcd.setCursor(0,0);
  lcd.print("    PRE-TEST    ");
  lcd.setCursor(0,1);
  lcd.print("Suhu : " + String(suhu) + " C");
}

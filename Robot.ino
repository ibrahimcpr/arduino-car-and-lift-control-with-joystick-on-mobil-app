#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <BlynkSimpleSerialBLE.h>
            
#include "./RobotTanimlamalari.h"
#define BLYNK_USE_DIRECT_CONNECT


#define echoPin 38
#define trigPin 39
long surec; 
int uzaklik; 
int sayac=0;
int minRange = 312;
int maxRange = 712;

bool durum = true;
SoftwareSerial Bluetooth_Baglantisi(BLUETOOTH_TX_PIN, BLUETOOTH_RX_PIN);











BLYNK_WRITE(V3) {
int x= param[0].asInt();
int y= param[1].asInt();







//vinç joystick
 if(y>512)
 {
 digitalWrite(33,LOW);
  digitalWrite(34,HIGH);
 }
 if(y<512)
 {
  digitalWrite(33,HIGH);
  digitalWrite(34,LOW);
 }

 if(y==512)
 {
  digitalWrite(33,LOW);
  digitalWrite(34,LOW);

  
  }
  }






// araç ileri sağ sol joystick
BLYNK_WRITE(V20) {
int x= param[0].asInt();
int y= param[1].asInt();

if(x>512){
        digitalWrite(MOTOR_B_IN_1_PIN, LOW);
  digitalWrite(MOTOR_B_IN_2_PIN, LOW);
  digitalWrite(MOTOR_A_IN_1_PIN, LOW);
  digitalWrite(MOTOR_A_IN_2_PIN, LOW);
  
  
    Motor_A_Calistir(150);
  
  }
  if(x<512){
      digitalWrite(MOTOR_B_IN_1_PIN, LOW);
  digitalWrite(MOTOR_B_IN_2_PIN, LOW);
  digitalWrite(MOTOR_A_IN_1_PIN, LOW);
  digitalWrite(MOTOR_A_IN_2_PIN, LOW);
      
 Motor_B_Calistir(150);

    
    
    }
       if(x<300&&x>50){

        digitalWrite(MOTOR_A_IN_1_PIN, LOW);
  digitalWrite(MOTOR_A_IN_2_PIN, HIGH);
  digitalWrite(MOTOR_A_EN_PIN, HIGH);
  digitalWrite(MOTOR_B_IN_1_PIN, LOW);
  digitalWrite(MOTOR_B_IN_2_PIN, HIGH);
  digitalWrite(MOTOR_B_EN_PIN, HIGH);


    Motor_B_Calistir(150);
      
    }

    if(x<980&&x>750){

        digitalWrite(MOTOR_A_IN_1_PIN, LOW);
  digitalWrite(MOTOR_A_IN_2_PIN, HIGH);
  digitalWrite(MOTOR_A_EN_PIN, HIGH);
  digitalWrite(MOTOR_B_IN_1_PIN, LOW);
  digitalWrite(MOTOR_B_IN_2_PIN, HIGH);
  digitalWrite(MOTOR_B_EN_PIN, HIGH);


    Motor_A_Calistir(150);
      
    }
    if(y>750)
 {
  //tam gaz ileri gitme 
  digitalWrite(MOTOR_A_IN_1_PIN, LOW);
  digitalWrite(MOTOR_A_IN_2_PIN, HIGH);
  digitalWrite(MOTOR_A_EN_PIN, HIGH);
  digitalWrite(MOTOR_B_IN_1_PIN, LOW);
  digitalWrite(MOTOR_B_IN_2_PIN, HIGH);
  digitalWrite(MOTOR_B_EN_PIN, HIGH);
 }


 if(y<=512)
 {
  //tekerleri durdurma
    digitalWrite(MOTOR_B_IN_1_PIN, LOW);
  digitalWrite(MOTOR_B_IN_2_PIN, LOW);
  digitalWrite(MOTOR_A_IN_1_PIN, LOW);
  digitalWrite(MOTOR_A_IN_2_PIN, LOW);

  
  }
 
}










//motorları istenilen hızda çalıştırma
void Motor_A_Calistir(int hiz) {
  digitalWrite(MOTOR_A_IN_1_PIN, LOW);
  digitalWrite(MOTOR_A_IN_2_PIN, HIGH);
  analogWrite(MOTOR_A_EN_PIN, hiz + MOTOR_A_OFFSET);
}

void Motor_B_Calistir(int hiz) {
  digitalWrite(MOTOR_B_IN_1_PIN, LOW);
  digitalWrite(MOTOR_B_IN_2_PIN, HIGH);
  analogWrite(MOTOR_B_EN_PIN, hiz + MOTOR_B_OFFSET);
}
//iki motor aynı hızda çalıştırma
void Hiz_Ayarla(int hiz)
{
  Motor_A_Calistir(hiz);
  Motor_B_Calistir(hiz);
}
//araç geri gitme fonksiyonu
void geri() {
  digitalWrite(MOTOR_A_IN_1_PIN, HIGH);
  digitalWrite(MOTOR_A_IN_2_PIN, LOW);  
  digitalWrite(MOTOR_B_IN_1_PIN, HIGH);
  digitalWrite(MOTOR_B_IN_2_PIN, LOW);
}





void setup()
{

  pinMode(trigPin, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 

  pinMode(MOTOR_A_EN_PIN, OUTPUT);
  pinMode(MOTOR_B_EN_PIN, OUTPUT);
  pinMode(MOTOR_A_IN_1_PIN, OUTPUT);
  pinMode(MOTOR_A_IN_2_PIN, OUTPUT);
  pinMode(MOTOR_B_IN_1_PIN, OUTPUT);
  pinMode(MOTOR_B_IN_2_PIN, OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(25,OUTPUT);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(9600);
  Bluetooth_Baglantisi.begin(9600);

  Blynk.begin(Bluetooth_Baglantisi, auth);
}

void loop()
{
//mesafe sensörü ölçün kodları
      digitalWrite(41, LOW);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  surec = pulseIn(echoPin, HIGH);
  uzaklik = surec * 0.034 / 2; 
    Serial.println(uzaklik);
delay(100);
 

 


  
  Blynk.run();
}

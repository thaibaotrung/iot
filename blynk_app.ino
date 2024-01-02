#define BLYNK_TEMPLATE_ID "TMPL6Z-cuALb4"
#define BLYNK_TEMPLATE_NAME "alarm"
#define BLYNK_AUTH_TOKEN "sRygkeWlYaalNfq-4u4bKRr4JRJVXowC"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

 
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "p2.6";  // type your wifi name
char pass[] = "dung4gdi";  // type your wifi password
int smokeA0 = A0;
int flameD0 = D0;
int gas_data = 0;
int flame_data = 0;
int sensorThres = 100;
int pinValue = 0;
#define Buzzer D3
#define LED D1
#define RELAY D7
BlynkTimer timer;


void setup(){
  Serial.begin(115200);
   pinMode(Buzzer, OUTPUT);
   pinMode(LED, OUTPUT);
   pinMode(RELAY, OUTPUT);
   pinMode(smokeA0, INPUT);
   pinMode(flameD0, INPUT);
   digitalWrite(RELAY, HIGH);
   digitalWrite(Buzzer, LOW);
   Blynk.begin(auth, ssid, pass);
  //dht.begin();
   timer.setInterval(1000L, sendSensor);
}


BLYNK_WRITE(V2) {
  pinValue = param.asInt();
}

void sendSensor(){

  if(pinValue==1){
    int gas_data = analogRead(smokeA0);
 Blynk.virtualWrite(V0, gas_data);
  Serial.print("Pin A0: ");
  Serial.println(gas_data);
  if(gas_data > 400){
    //Blynk.email("test@gmail.com", "Alert", "Gas Leakage Detected!");
    digitalWrite(Buzzer, HIGH);
    digitalWrite(LED, HIGH);
    Blynk.logEvent("gas_alert","Gas Leakage Detected!!!");
  }
  else{
    digitalWrite(Buzzer, LOW);
    digitalWrite(LED, LOW);
  }

  int flame_data = digitalRead(flameD0);
  Blynk.virtualWrite(V1, flame_data);
  Serial.print("Pin D0: ");
  Serial.println(flame_data);
  if(flame_data == 0){
    digitalWrite(Buzzer, HIGH);
    digitalWrite(LED, HIGH);
    digitalWrite(RELAY, LOW);
    Blynk.logEvent("fire_alert", "Fire Leakage Detected!!!");
  }
  else{
    digitalWrite(Buzzer, LOW);
    digitalWrite(LED, LOW);
    digitalWrite(RELAY, HIGH);
  }
}
else{
  Serial.println("System is off");
  digitalWrite(Buzzer, LOW);
  digitalWrite(LED, LOW);
}
}

void loop(){
  Blynk.run();
  timer.run();
}
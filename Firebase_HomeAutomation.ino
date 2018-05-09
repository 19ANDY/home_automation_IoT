#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include<FirebaseArduino.h>
#define FIREBASE_HOST "time-table-39a37.firebaseio.com"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "NzEtoGvhHmfGmDQ6aoxGdUvHKNxIBcQgZemCbrrW"       //Your Firebase Database Secret goes here
//#define WIFI_SSID "Rishabh"                                               //your WiFi SSID for which yout NodeMCU connects
//#define WIFI_PASSWORD "rishabha"                                      //Password of your wifi network 

#define Relay1 12 //D6
int val1;

#define Relay2 14 //D2
int val2;

#define Relay3 4  //D1
int val3;

#define Relay4 5 //D5
int val4;

void setup()
{
  Serial.begin(115200);                    // Select the same baud rate if you want to see the datas on Serial Monitor
  WiFiManager wifiManager;
  wifiManager.resetSettings();

  //first parameter is name of access point, second is the password
  wifiManager.autoConnect("Rishabh");
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);

  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);
  digitalWrite(Relay3, HIGH);
  digitalWrite(Relay4, HIGH);




  /*WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }*/
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
void firebasereconnect()
{
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{
  if (Firebase.failed())
  {
    Serial.print("setting number failed:");
    Serial.println(Firebase.error());
    firebasereconnect();
    return;
  }

  val1 = Firebase.getBool("alpha/one");                                      //Reading the value of the varialble Status from the firebase
  Serial.print("val1\t");
  Serial.println(val1);
  if (!val1)                                                          // If, the Status is 1, turn on the Relay1
  {
    digitalWrite(Relay1, LOW);
    Serial.println("light 1 ON");
  }
  else if (val1)                                                   // If, the Status is 0, turn Off the Relay1
  {
    digitalWrite(Relay1, HIGH);
    Serial.println("light 1 OFF");
  }

  val2 = Firebase.getBool("alpha/two");                                      //Reading the value of the varialble Status from the firebase
  //  Serial.print("val2: ", val2);
  Serial.print("val2\t");
  Serial.println(val2);
  if (!val2)                                                          // If, the Status is 1, turn on the Relay2
  {
    digitalWrite(Relay2, LOW);
    Serial.println("light 2 ON");
  }
  else if (val2)                                                   // If, the Status is 0, turn Off the Relay2
  {
    digitalWrite(Relay2, HIGH);
    Serial.println("light 2 OFF");
  }
  val3 = Firebase.getBool("alpha/three");                                      //Reading the value of the varialble Status from the firebase
  Serial.print("val3\t");
  Serial.println(val3);
  //  Serial.print("val3:", val3);
  if (!val3)                                                          // If, the Status is 1, turn on the Relay3
  {
    digitalWrite(Relay3, LOW);
    Serial.println("light 3 ON");
  }
  else if (val3)                                                   // If, the Status is 0, turn Off the Relay3
  {
    digitalWrite(Relay3, HIGH);
    Serial.println("light 3 OFF");
  }

  val4 = Firebase.getBool("alpha/four");                                      //Reading the value of the varialble Status from the firebase
  //Serial.print("val4:",val4);
  Serial.print("val4\t");
  Serial.println(val4);
  if (!val4)                                                          // If, the Status is 1, turn on the Relay4
  {
    digitalWrite(Relay4, LOW);
    Serial.println("light 4 ON");
  }
  else if (val4)                                                   // If, the Status is 0, turn Off the Relay4
  {
    digitalWrite(Relay4, HIGH);
    Serial.println("light 4 OFF");
  }
 
}

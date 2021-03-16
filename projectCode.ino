
//wifi library

#include <WiFiServer.h>
#include <WiFiClient.h>
#include <WiFi.h>

// firebase library

#include <FB_HTTPClient32.h>
#include <FirebaseESP32.h>
#include <FirebaseJson.h>

//firebase credentials

#define FIREBASE_HOST "https://thome-d4776-default-rtdb.firebaseio.com/" // the project name address from firebase id

#define FIREBASE_AUTH "Yn6F4estvoefUjglduCUUfHQcsh3FEymxfLliwbV" // the secret key generated from firebase

//wifi credentials

#define WIFI_SSID "Redmi Note 5"

#define WIFI_PASSWORD ""

// initializing light status

String fireStatus1 = "";
String fireStatus2 = "";
String fireStatus3 = "";
String fireStatus4 = "";

// firebase database

FirebaseData firebaseData;

// defining Relays and Pins

#define S1 32
#define Relay1 15

#define S2 35
#define Relay2 2

#define S3 34
#define Relay3 4

#define S4 39
#define Relay4 22

//defing functions

void withInternet();
void withoutInternet();

boolean flag = false;

void checkFire() {

  if (WiFi.status() == WL_CONNECTED) {
    flag = true;
  } else{
    flag = false;
  }
}


void withInternet() {

  // get Light Status from database

  fireStatus1 = Firebase.getString(firebaseData, "/LIGHT1_STATUS");
  fireStatus2 = Firebase.getString(firebaseData, "/LIGHT2_STATUS");
  fireStatus3 = Firebase.getString(firebaseData, "/LIGHT3_STATUS");
  fireStatus4 = Firebase.getString(firebaseData, "/LIGHT4_STATUS");

  // compare the input of light status received from database

  if (fireStatus1 == "ON"|| digitalRead(S1) == HIGH) {

    Serial.println("Light1 Turned ON");

    digitalWrite(Relay1, HIGH);

  } else if (fireStatus1 == "OFF" || digitalRead(S1) == LOW) {

    Serial.println("Light1 Turned OFF");

    digitalWrite(Relay1, LOW);

  } else {

    Serial.println("Wrong Credential! Please send ON/OFF");

  }


  if (fireStatus2 == "ON" || digitalRead(S2) == HIGH) {

    Serial.println("Light2 Turned ON");

    digitalWrite(Relay2, HIGH);
  }

  else if (fireStatus2 == "OFF" || digitalRead(S2) == LOW) {

    Serial.println("Light2 Turned OFF");

    digitalWrite(Relay2, LOW);

  }

  else {

    Serial.println("Wrong Credential! Please send ON/OFF");

  }

  if (fireStatus3 == "ON" || digitalRead(S3) == HIGH) {

    Serial.println("Light3 Turned ON");

    digitalWrite(Relay3, HIGH);

  }

  else if (fireStatus3 == "OFF" || digitalRead(S1) == LOW) {

    Serial.println("Light3 Turned OFF");

    digitalWrite(Relay3, LOW);
  }

  else {

    Serial.println("Wrong Credential! Please send ON/OFF");

  }

  if (fireStatus4 == "ON" || digitalRead(S4) == HIGH) {

    Serial.println("Light4 Turned ON");

    digitalWrite(Relay4, HIGH);

  }

  else if (fireStatus4 == "OFF" || digitalRead(S4) ==LOW) {

    Serial.println("Light4 Turned OFF");

    digitalWrite(Relay4, LOW);

  }

  else {

    Serial.println("Wrong Credential! Please send ON/OFF");

  }
}
void withoutInternet()
{

  digitalWrite(Relay1, digitalRead(S1));

  if (digitalRead(S1) == HIGH) {
    Firebase.setString(firebaseData, "LIGHT1_STATUS", "ON");
  } else if (digitalRead(S1) == LOW) {
    Firebase.setString(firebaseData, "LIGHT1_STATUS", "OFF");
  }
  digitalWrite(Relay2, digitalRead(S2));

  if (digitalRead(S2) == HIGH) {
    Firebase.setString(firebaseData, "LIGHT2_STATUS", "ON");
  } else if (digitalRead(S2) == LOW) {
    Firebase.setString(firebaseData, "LIGHT2_STATUS", "OFF");
  }

  digitalWrite(Relay3, digitalRead(S3));

  if (digitalRead(S3) == HIGH) {
    Firebase.setString(firebaseData, "LIGHT3_STATUS", "ON");
  } else if (digitalRead(S3) == LOW) {
    Firebase.setString(firebaseData, "LIGHT3_STATUS", "OFF");
  }

  digitalWrite(Relay4, digitalRead(S4));

  if (digitalRead(S4) == HIGH) {
    Firebase.setString(firebaseData, "LIGHT4_STATUS", "ON");
  } else if (digitalRead(S4) == LOW) {
    Firebase.setString(firebaseData, "LIGHT4_STATUS", "OFF");
  }
}


void setup() {

  Serial.begin(9600);

  delay(1000);

  pinMode(S1, INPUT);
  pinMode(Relay1, OUTPUT);

  pinMode(S2, INPUT);
  pinMode(Relay2, OUTPUT);

  pinMode(S3, INPUT);
  pinMode(Relay3, OUTPUT);

  pinMode(S4, INPUT);
  pinMode(Relay4, OUTPUT);

  //initializing Relays
  digitalWrite(Relay1, LOW);
  digitalWrite(Relay2, LOW);
  digitalWrite(Relay3, LOW);
  digitalWrite(Relay4, LOW);

  //try to connect with wifi

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to ");

  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {

    Serial.print(".");

    delay(500);

  }

  Serial.println();

  Serial.print("Connected to ");

  Serial.println(WIFI_SSID);

  Serial.print("IP Address is : ");

  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void loop() {
  checkFire();
  if (flag == true) {
    withInternet();
  } else {
    withoutInternet();
  }
}

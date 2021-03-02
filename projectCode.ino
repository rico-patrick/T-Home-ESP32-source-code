
//wifi library

#include <WiFiServer.h>
#include <WiFiClient.h>
#include <WiFi.h>

// firebase library

#include <FB_HTTPClient32.h>
#include <FirebaseESP32.h>
#include <FirebaseJson.h>

//firebase credentials

#define FIREBASE_HOST "https://thome-d4776-default-rtdb.firebaseio.com" // the project name address from firebase id

#define FIREBASE_AUTH "Yn6F4estvoefUjglduCUUfHQcsh3FEymxfLliwbV" // the secret key generated from firebase

// firebase database

FirebaseData firebaseData;

//wifi credentials

#define WIFI_SSID "Redmi Note 5"

#define WIFI_PASSWORD "12345678"

// initializing light status

String fireStatus1 = "";
String fireStatus2 = "";
String fireStatus3 = "";
String fireStatus4 = "";

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
void checkFire();

boolean flag = false;

void checkFire() {

  if (WiFi.status() == WL_CONNECTED) {

    flag = true;

  } else {

    flag = false;

  }
}


void withInternet() {

  // get Light Status from database

  Firebase.getString(firebaseData, "/LIGHT1_STATUS");
  fireStatus1 = firebaseData.stringData();
  Serial.println("Firebase Light1_Status recieved " + fireStatus1);
  fireStatus2 = Firebase.getString(firebaseData, "/LIGHT2_STATUS");
  fireStatus2 = firebaseData.stringData();
  Serial.println("Firebase Light2_Status recieved " + fireStatus2);
  fireStatus3 = Firebase.getString(firebaseData, "/LIGHT3_STATUS");
  fireStatus3 = firebaseData.stringData();
  Serial.println("Firebase Light3_Status recieved " + fireStatus3);
  fireStatus4 = Firebase.getString(firebaseData, "/LIGHT4_STATUS");
  fireStatus4 = firebaseData.stringData();
  Serial.println("Firebase Light4_Status recieved " + fireStatus4);

  // compare the input of light status received from database

  if (fireStatus1 == "ON") {

    Serial.println("Light1 Turned ON");
    digitalWrite(Relay1, HIGH);

  } else if (fireStatus1 == "OFF") {

    Serial.println("Light1 Turned OFF");
    digitalWrite(Relay1, LOW);

  } else {

    Serial.println("Error in Relay1");
  }


  if (fireStatus2 == "ON") {

    Serial.println("Light2 Turned ON");
    digitalWrite(Relay2, HIGH);

  } else if (fireStatus2 == "OFF") {

    Serial.println("Light2 Turned OFF");
    digitalWrite(Relay2, LOW);

  } else {

    Serial.println("Error in Relay2");

  }

  if (fireStatus3 == "ON") {

    Serial.println("Light3 Turned ON");
    digitalWrite(Relay3, HIGH);

  } else if (fireStatus3 == "OFF") {

    Serial.println("Light3 Turned OFF");
    digitalWrite(Relay3, LOW);

  } else {

    Serial.println("Error in Relay3");

  }
  if (fireStatus4 == "ON") {

    Serial.println("Light4 Turned ON");
    digitalWrite(Relay4, HIGH);

  }

  else if (fireStatus4 == "OFF") {
    Serial.println("Light4 Turned OFF");
    digitalWrite(Relay4, LOW);
  }

  else {

    Serial.println("Error in Relay4");

  }
}

void withoutInternet()
{

  digitalWrite(Relay1, digitalRead(S1));

  if (digitalRead(S1) == HIGH) {

    Serial.println("Relay1 is ON");
    Firebase.setString(firebaseData, "LIGHT1_STATUS", "ON");

  } else if (digitalRead(S1) == LOW) {

    Serial.println("Relay1 is OFF");
    Firebase.setString(firebaseData, "LIGHT1_STATUS", "OFF");

  }

  digitalWrite(Relay2, digitalRead(S2));

  if (digitalRead(S2) == HIGH) {

    Serial.println("Relay2 is ON");
    Firebase.setString(firebaseData, "LIGHT2_STATUS", "ON");

  } else if (digitalRead(S2) == LOW) {

    Serial.println("Relay2 is OFF");
    Firebase.setString(firebaseData, "LIGHT2_STATUS", "OFF");

  }

  digitalWrite(Relay3, digitalRead(S3));

  if (digitalRead(S3) == HIGH) {

    Serial.println("Relay3 is ON");
    Firebase.setString(firebaseData, "LIGHT3_STATUS", "ON");

  } else if (digitalRead(S3) == LOW) {

    Serial.println("Relay3 is OFF");
    Firebase.setString(firebaseData, "LIGHT3_STATUS", "OFF");

  }

  digitalWrite(Relay4, digitalRead(S4));

  if (digitalRead(S4) == HIGH) {

    Serial.println("Relay4 is ON");
    Firebase.setString(firebaseData, "LIGHT4_STATUS", "ON");

  } else if (digitalRead(S4) == LOW) {

    Serial.println("Relay4 is OFF");
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

  //try to connect with wifi

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to ");

  Serial.println(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {

    Serial.print(".");

    delay(500);

  }

  Serial.println();

  Serial.println("Connected to ");

  Serial.println(WIFI_SSID);

  Serial.print("IP Address is : ");

  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void loop() {

  checkFire();

  if (flag) {

    withInternet();

  } else {

    withoutInternet();

  }

}

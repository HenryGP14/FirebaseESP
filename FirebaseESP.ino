#include <WiFi.h>
#include <FirebaseESP32.h>  // Librería de mobizt

// Configuración de valores del firebase
#define FIREBASE_HOST "url.firebaseio.com/"  //Sin http:// o https://
#define FIREBASE_AUTH "secret_key"

const char* ssid = "name_wifi";
const char* password = "pass_wifi";

// URl path o nombre de la base de datos
String path = "/Uber";
//Define un objeto de Firebase
FirebaseData firebaseData;
void CausaError(void);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  // Conectarse a la cuenta de firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  // Verificar que existe la ruta o los valores a consultar o cambiar
  if (Firebase.setString(firebaseData, path + "/Personas/-NT0Eaj3VTgfU55VEC_9/apellidos", "Perez Ulloa")) {
    Serial.println(firebaseData.stringData());
  } else {
    CausaError();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}


void CausaError(void) {
  Serial.println("Error");
  Serial.println("Mesanje: " + firebaseData.errorReason());
  Serial.println("------------------------------------");
  Serial.println();
}

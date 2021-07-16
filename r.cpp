

#include <Adafruit_Sensor.h>
#include <DHT.h>
#define DHTPIN 27
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
 
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

const char* ssid = "VIVO-2D9A";
const char* password = "J626050408";
const char* host = "162.55.162.84";
String _url;

void conectandoComOServidor(const char* ssid, const char* password,  const char* host);
void enviandoOsDadosParaOServidor(const char* ssid, const char* password,  const char* host, String _url);



void setup(void)
{
    
    conectandoComOServidor("VIVO-2D9A", "J626050408", "162.55.162.84");
    dht.begin();
    Serial.begin(115200);
}



void loop(void)
{

  //MC38A

  
  

  //DHT11
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  /* if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  } */

  Serial.print(F("Umidade: "));
  Serial.print(h);
  Serial.println(F(" %."));
  Serial.print(F("Temperatura: "));
  Serial.print(t);
  Serial.println(F(" °C."));

  
  
  enviandoOsDadosParaOServidor("VIVO-2D9A", "J626050408", "162.55.162.84", "/dados/servidorbarreiros/salvar.php?sensor1=");
  delay(1000);
}



void enviandoOsDadosParaOServidor(const char* ssid, const char* password,  const char* host, String _url){

    delay(5000);
    Serial.print("Conectando com... ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }


    float sensor1 = 10;

    float sensor2 = 20;

    float sensor3 = 30;

    // We now create a URI for the request
    String url = "/dados/servidorbarreiros/salvar.php?sensor1=";
    url += sensor1;
    url += "&sensor2=";
    url += sensor2;
    url += "&sensor3=";
    url += sensor3;

    Serial.print("Requesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
    }

    Serial.println();
    Serial.println("Conexão Fechada.");
}

void conectandoComOServidor(const char* ssid, const char* password,  const char* host){

  delay(10);

    // We start by connecting to a WiFi network

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
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  

  
}

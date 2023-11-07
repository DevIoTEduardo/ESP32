#include <Arduino.h>
#include <WiFi.h>
#include <ThingSpeak.h>

const char ssid[] = "ALFATRONIC"; // REDE WIFI QUE DESEJA UTILIZAR
const char password[] = "20091996";
WiFiClient client;

const long CHANNEL = 2336524; // ID THINGSPEAK
const char *WRITE_API = "2T6YGWLFZCV7GKQX";

int intervalSensor = 2000;
long prevMillisThingSpeak = 0;
int intervalThingSpeak = 15000; // Intervalo minímo para escrever no ThingSpeak write é de 15 segundos


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Envia os dados do sensor para o ThingSpeak usando o ESP32");
  Serial.println();

  WiFi.mode(WIFI_STA); //Modo Station
  ThingSpeak.begin(client);  // Inicializa o ThingSpeak
}

void loop()
{

  float t =0;
  int h = 0;

  t = temperatureRead(); // TEMPERATURA EM Cº
  h = hallRead(); // LENDO O SENSOR HALL DO ESP 32
   
   // Conecta ou reconecta o WiFi
  if (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print("Atenção para conectar o SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED) 
    {
      WiFi.begin(ssid, password);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConectado");
   }
  
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println("*C");
  Serial.print ("Hall: ");
  Serial.println(h);
  delay(1000);     

  if (millis() - prevMillisThingSpeak > intervalThingSpeak) 
  {

    // Configura os campos com os valores
    ThingSpeak.setField(1,t); // PRIMEIRO CANAL
    ThingSpeak.setField(2,h); // SEGUNDO CANAL

    // Escreve no canal do ThingSpeak 
    int x = ThingSpeak.writeFields(CHANNEL, WRITE_API);
    if (x == 200) 
    {
      Serial.println("Update realizado com sucesso");
    }
    else 
    {
      Serial.println("Problema no canal - erro HTTP " + String(x));
    }

    prevMillisThingSpeak = millis();
  }
}

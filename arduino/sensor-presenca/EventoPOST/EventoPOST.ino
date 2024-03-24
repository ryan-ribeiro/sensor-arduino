#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <NTPClient.h> //https://github.com/taranais/NTPClient
#include <WiFiUdp.h>

const char* ssid = "Danilo";
const char* password = "qwer@123";

// Seu nome de domínio com caminho de URL ou endereço IP com caminho
const char* serverName = "http://192.168.1.15:8080/presenca/cadastrar";

unsigned long timerDelay = 5000; // Timer set to 5 seconds (5000)
unsigned long lastTime = 0;

int PIR = 5;
int LeituraPIR = 0;

String local = "Sensor de presenca do quarto 1";
String arduino = "Atmega2560";
String dados = "detectou PRESENCA";

void setup() {
  Serial.begin(115200);

  pinMode(PIR, INPUT);

  WiFi.begin(ssid, password);
  Serial.println("Conectando");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Conectado à rede WiFi com endereço IP: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer configurado para 5 segundos (variável timerDelay), levará 5 segundos antes de publicar a primeira leitura.");
}

void loop() {
  Serial.println(LeituraPIR);
  if (WiFi.status() == WL_CONNECTED) {
      LeituraPIR = digitalRead(PIR);
  } else {
      Serial.println("WiFi desconectado");
      setup();
  }

  if (LeituraPIR == 1 && ((millis() - lastTime) > timerDelay)) {
      RequisicaoHttpPOST();
      lastTime = millis();
  }
}

void RequisicaoHttpPOST() {
  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverName);

  // Se você precisar de autenticação Node-RED/servidor, insira usuário e senha abaixo
  // http.setAuthorization("SEU_USUÁRIO", "SUA_SENHA");

  http.addHeader("Content-Type", "application/json");
  // String httpRequestData = "{\"api_key\":\"tPmAT5Ab3j7F9\",\"nome\":\"" + nome + "\",\"arduino\":\"" + arduino + 
  // "\",\"id\":\"" + id + "\",\"mensagem\":\"" + mensagem + "\",\"data\":\"" + data + "\,\"hora\":\"" + hora + "\"}";
  String httpRequestData = "{\"api_key\":\"tPmAT5Ab3j7F9\",\"local\":\"" + local + "\",\"arduino\":\"" + arduino + 
  "\",\"dados\":\"" + dados + "\"}";

  Serial.println(httpRequestData);

  int httpResponseCode = http.POST(httpRequestData);

  // Se você precisar de uma solicitação HTTP com um tipo de conteúdo: text/plain
  // http.addHeader("Content-Type", "text/plain");
  // int httpResponseCode = http.POST("Olá, Mundo!");
  Serial.print("Código de resposta HTTP: ");
  Serial.println(httpResponseCode);

  http.end();
}

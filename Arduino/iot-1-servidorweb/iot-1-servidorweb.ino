#include <WiFi.h>

char ssid [] = "AulaIoT";
char senha[] = "secreta123";
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  conectaWiFi(ssid,senha);
  server.begin();
  Serial.println("Servidor inicializado");
}

void conectaWiFi(char SSID[],char SENHA[]){
  Serial.print("Conectando a rede ");
  Serial.println(SSID);
  WiFi.begin(SSID,SENHA);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println(" ");
  Serial.println("WiFi Conectado");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if(!client){
    return;
  } else {
String ipCliente = client.remoteIP().toString();
  Serial.print("Cliente conectado: ");
  Serial.println(ipCliente);
}

  while(!client.available()){
    delay(1);
  }
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<HEAD>");
  client.println("<link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/bootstrap@4.0.0/dist/css/bootstrap.min.css' integrity='sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm' crossorigin='anonymous'>");
  client.println("<script src='https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js' integrity='sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p' crossorigin='anonymous'></script>");
  client.println("</HEAD>");
  
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<body>");
  client.println("<h1>Aula de IoT</h1>");
  client.println("<script src='https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js' integrity='sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p' crossorigin='anonymous'></script>");
   
  client.println("<h2>Oi IoT!</h2>");
    client.println("<button type='button' class='btn btn-success'>Clique aqui</button>");
      client.println("<button type='button' class='btn btn-danger'>Clique aqui</button>");
  client.println("</body>");
  client.println("</html>"); 
}

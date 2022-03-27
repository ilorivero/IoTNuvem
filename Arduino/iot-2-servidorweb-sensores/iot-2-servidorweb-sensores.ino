#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_AHT10.h>
#include <Adafruit_MLX90614.h>


Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Adafruit_AHT10 aht;

double temperaturaAmb;
double temperaturaCorp;
double umidade;
const int pinoBotao = 15;     
const int pinoLed =  2;  
bool estadoBotao = false;
bool estadoLed = false;

char ssid [] = "AulaIoT";
char senha[] = "secreta123";
WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.begin(115200);
  pinMode(pinoLed, OUTPUT);
  pinMode(pinoBotao, INPUT);

  conectaWiFi(ssid,senha);
  server.on("/", enviaInfo);
  server.on("/ledOn", ligaLed);
  server.on("/ledOff", desligaLed);
  server.onNotFound(envia404);
  server.begin();
  Serial.println("Servidor HTTP Iniciado");


  Serial.println("Inicializando sensor de temperatura e umidade AHT10");
  if (! aht.begin()) {
    Serial.println("AHT 10 nao encontrado");
    while (1) delay(10);
  }
  Serial.println("AHT10 Ok");
  Serial.println("Inicializando sensor de temperatura corporal MLX90614");
  
  if (!mlx.begin()) {
    Serial.println("MLX90614 nao encontrado");
    while (1);
  };
  Serial.print("Emissividde MLX90614 = "); Serial.println(mlx.readEmissivity());
  Serial.println("================================================");
  
}

void conectaWiFi(char ssid[],char senha[]){
  Serial.print("Conectando a rede ");
  Serial.println(ssid);
  WiFi.begin(ssid,senha);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    piscaLed();
    Serial.print(".");
  }

  Serial.println(" ");
  Serial.println("WiFi Conectado");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());

}


void ligaLed(){
    digitalWrite(pinoLed,HIGH);
    estadoLed = true;
    enviaInfo();
  }
void desligaLed(){
    digitalWrite(pinoLed,LOW);
    estadoLed= false;
    enviaInfo();
  }
  
void botaoLigado(){
    estadoBotao = true;
    enviaInfo();
  }
void botaoDesligado(){
   estadoBotao= false;
    enviaInfo();
  }

  void envia404(){
  server.send(404, "text/plain", "Não Encontrado");
}


void enviaInfo(){
  
  estadoBotao = digitalRead(pinoBotao);
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  
  temperaturaAmb = temp.temperature;
  temperaturaCorp = mlx.readObjectTempC();
  umidade = humidity.relative_humidity;

  Serial.print("Estado do Led: "); 
  Serial.println(estadoLed); 
  Serial.print("Estado do Botao: "); 
  Serial.println(estadoBotao); 
  Serial.print("Temperatura Ambiente: "); 
  Serial.print(temperaturaAmb); 
  Serial.println(" graus C");
  Serial.print("Umidade: "); 
  Serial.print(umidade); 
  Serial.println("%");
  Serial.print("Temperatura Corporal = "); 
  Serial.print(temperaturaCorp); 
  Serial.println("*C");

  server.send(200, "text/html", respostaHTML(temperaturaAmb,umidade, temperaturaCorp, estadoLed, estadoBotao)); 
  
  }

void loop(){
 server.handleClient();
}

void piscaLed() {
  digitalWrite(pinoLed, HIGH);   
  delay(100);                      
  digitalWrite(pinoLed, LOW);   
  delay(100);                  
}


String respostaHTML(double tAmb,double umi, double tCorp, bool estLed, bool estBotao) {

  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<meta http-equiv='refresh' content='2'>";
  ptr +="<meta charset='UTF-8'>";
  ptr +="<title>Aula IoT</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor:pointer;border-radius: 4px;}\n";
  ptr +=".buttontemp {display: block;width: 120px;background-color: #11bc11;border: 2px;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".buttonumi {display: block;width: 120px;background-color: #11bc11;border: 2px;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".temperatura {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>Aula IoT</h1>\n";
    ptr +="<p>Temp Ambiente: </p><p class=\"buttontemp\">";
  ptr +=(float)tAmb;
  ptr +=" ºC</p>";
  ptr +="<p>Umidade: </p><p class=\"buttonumi\">";
  ptr +=(int)umi;
  ptr +=" %</p>";
  ptr +="<p>Temp Corporal: </p><p class=\"buttonumi\">";
  ptr +=(float)tCorp;
  ptr +=" ºC</p>";
  ptr +="</div>\n";

   if(estLed)
  {ptr +="<p>LED Status: LIGADO</p><a class=\"button button-off\" href=\"/ledOff\">Desligar</a>\n";}
  else
  {ptr +="<p>LED Status: DESLIGADO</p><a class=\"button button-on\" href=\"/ledOn\">Ligar</a>\n";}

  if(estBotao)
  {ptr +="<p>Botão</p><a class=\"button button-off\">Clicado</a>\n";}
  else
  {ptr +="<p>Botão</p><a class=\"button button-on\">Livre</a>\n";}

  
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

#include <WiFi.h>
#include <dht.h>

dht DHT;


const char* ssid     = "Sai fora sapo";
const char* password = "12345678";
 
int PinUmid  = 34;
int PinLuz   = 13;
int PinTemp  = 12;

int PinVent  = 11;
int PinBomba = 10;

WiFiServer server(80);

//Sensores
int catch_temp(){
  int aux;
  //Serial.print(DHT.humidity);             //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO
  aux =  Serial.print(DHT.temperature, 0); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO E REMOVE A PARTE DECIMAL
  return aux;
}
int catch_solo(){
  int umidade = analogRead(PinUmid);
  int umidadePorcet = map(umidade, 0, 4095, 0, 100); // Converte o valor para uma escala de 0 a 100%
  return umidadePorcet;
}

//Açoes 
void ligarVent(){
  //A fazer
}

void desligarVent(){
  //A fazer
}

void ligarBomba(){
  //A Fazer
}

void desligarBomba(){
  //A Fazer
}


void ligarLuz(){
  digitalWrite(PinLuz, HIGH);
}

void desligarLuz(){
  digitalWrite(PinLuz, LOW);
}

void setup() {

  Serial.begin(115200);
  pinMode(PinLuz, OUTPUT);
  pinMode(PinUmid, INPUT);

  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectada.");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      DHT.read11(PinTemp);
      int umidadeShow = catch_solo();

      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            //  EXIBIR NO HTML
            client.print("Click <a href=\"/H\">here</a> Ligar Luz.<br>");
            client.print("Click <a href=\"/L\">here</a> Desligar Luz.<br>");
            client.print("Click <a href=\"/\">here</a> Atulizar Dados....<br>");
            client.print("TEMPERATURA: ");
            client.print(DHT.temperature, 0);
            client.print("UMIDADE DO SOLO: ");
            client.print(umidadeShow, 0);
            


            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        //   CREATE FUNCTIONS
        if (currentLine.endsWith("GET /H")) {
          ligarLuz();
        }
        if (currentLine.endsWith("GET /L")) {
          desligarLuz();
        }
        
      }
    }
    client.stop();
    //Serial.println("Client Disconnected.");
  }
}
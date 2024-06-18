#include <WiFi.h>
#include <dht.h>

dht DHT;

const char* ssid     = "Mete_O_Pe";
const char* password = "Rutra321";
 
int PinUmid  = 34;
int PinLuz   = 13;
int PinTemp  = 12;

int PinVent  = 11;
int PinBomba = 10;

WiFiServer server(80);

//Sensores
int catch_temp() {
  return DHT.temperature;
}

int catch_solo() {
  int umidade = analogRead(PinUmid);
  return map(umidade, 0, 4095, 0, 100); // Converte o valor para uma escala de 0 a 100%
}

//Ações 
void ligarVent() {
  digitalWrite(PinVent, HIGH);
}

void desligarVent() {
  digitalWrite(PinVent, LOW);
}

void ligarBomba() {
  digitalWrite(PinBomba, HIGH);
  delay(800);
  digitalWrite(PinVent, LOW);
}

void ligarLuz() {
  digitalWrite(PinLuz, HIGH);
}

void desligarLuz() {
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
    DHT.read11(PinTemp);
    int umidadeShow = catch_solo();
    int temperaturaShow = catch_temp();
    String html = "HTTP/1.1 200 OK\r\nContent-type:text/html\r\n\r\n";
    html += "<!DOCTYPE html><html><head><style>";
    html += "body { font-family: Arial, sans-serif; text-align: center; }";
    html += ".button { display: inline-block; padding: 10px 20px; margin: 10px; font-size: 16px; color: white; background-color: #4CAF50; text-decoration: none; border: none; border-radius: 5px; cursor: pointer; }";
    html += ".button:hover { background-color: #45a049; }";
    html += "</style></head><body>";
    html += "<a class=\"button\" href=\"/H\">Ligar a Luz</a><br>";
    html += "<a class=\"button\" href=\"/L\">Desligar a Luz</a><br>";
    html += "<a class=\"button\" href=\"/T\">Ligar Ventilador</a><br>";
    html += "<a class=\"button\" href=\"/E\">Desligar Ventilador</a><br>";
    html += "<a class=\"button\" href=\"/F\">Irrigar</a><br>";
    html += "<a class=\"button\" href=\"/\">Atualizar Dados....</a><br>";
    html += "TEMPERATURA: " + String(temperaturaShow) + "<br>UMIDADE DO SOLO EM " + String(umidadeShow) + "%<br>";
    html += "</body></html>";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.print(html);
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        // CREATE FUNCTIONS
        if (currentLine.endsWith("GET /H")) {
          ligarLuz();
        }
        if (currentLine.endsWith("GET /L")) {
          desligarLuz();
        }
        if (currentLine.endsWith("GET /T")) {
          ligarVent();
        }
        if (currentLine.endsWith("GET /E")) {
          desligarVent();
        }
        if (currentLine.endsWith("GET /F")) {
          ligarBomba();
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}

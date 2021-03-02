#include <Arduino.h>
#include <ESP8266WiFi.h> 
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>
#include <WebSocketsServer.h>

#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <user_interface.h>

#include <WebSocketsClient.h>
#include <StreamString.h>

#include <IRsend.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <ir_Gree.h>

#include <LiquidCrystal_I2C.h> 
#include <NTPClient.h>

#include "PCF8574.h"

#include <SimpleTimer.h>

#include <FS.h>

#include "FirebaseESP8266.h"

PCF8574 pcf8574(0x20);

#define PinoLuz1 P0 // Usando o Expansor
#define PinoSomOnOff P1 // Usando o Expansor
#define PinoSomVolMais P2 // Usando o Expansor
#define PinoSomVolMenos P3 // Usando o Expansor
#define PinoSomInput P4 // Usando o Expansor
#define PinoSwitchAudioS0 P5 // Usando o Expansor
#define PinoSwitchAudioS1 P6 // Usando o Expansor
#define PinoSwitchAudioS2 P7 // Usando o Expansor

bool Luz1Is = false;
bool PinoLed1Is = false;

bool IsDebugRemoto = false;

uint8_t WebSocket_Id = 0;

ESP8266WiFiMulti WiFiMulti;

ESP8266WebServer httpserver(80);
WebSocketsServer webSocket(81);

const char* www_username = "XXXXXX";
const char* www_password = "XXXXXX";

IRsend irsend(14);
IRrecv irrecv(12);
decode_results results;

bool IrReceiveIs = true;

IRGreeAC ac(14);

// Datashow / OnOff
uint16_t IrData_DatashowOnOff[71] = {8800,4400, 550,550, 600,500, 600,500, 600,500, 600,500, 600,550, 550,550, 550,1650, 550,1650, 600,1600, 600,1650, 550,1600, 600,1650, 550,1650, 600,1600, 600,500, 600,1650, 550,550, 550,550, 550,550, 600,1600, 600,500, 600,1650, 550,550, 550,550, 550,1650, 600,1600, 600,1600, 600,500, 600,1650, 550,550, 550,1650, 600,38750, 8850,2200, 600};

uint16_t IrData_FitaLed_Desligar[71] = {9596, 4522,  610, 560,  606, 558,  606, 560,  606, 558,  604, 560,  602, 562,  602, 560,  606, 562,  608, 1668,  612, 1670,  608, 1672,  604, 1668,  610, 562,  602, 1668,  606, 1666,  632, 1644,  606, 562,  606, 1668,  606, 562,  602, 562,  604, 562,  602, 588,  606, 534,  604, 564,  600, 1672,  598, 560,  598, 1670,  596, 1672,  598, 1670,  600, 1670,  598, 1666,  602, 1670,  600, 41008,  9474, 2254,  600};  // NEC F740BF
uint16_t IrData_FitaLed_Ligar[67] = {9408, 4562,  564, 598,  590, 566,  566, 626,  508, 622,  568, 622,  536, 570,  590, 598,  564, 594,  564, 1682,  586, 1706,  566, 1706,  564, 1706,  590, 568,  566, 1706,  616, 1654,  562, 1708,  564, 1702,  564, 1706,  562, 596,  534, 620,  588, 572,  562, 594,  562, 598,  590, 592,  534, 596,  562, 596,  562, 1704,  564, 1708,  588, 1706,  536, 1706,  592, 1680,  560, 1708,  564};  // NEC F7C03F
uint16_t IrData_FitaLed_Efeito_Parado[71] = {9444, 4512,  608, 524,  632, 526,  606, 576,  606, 522,  632, 524,  608, 548,  632, 556,  574, 550,  606, 1656,  634, 1662,  606, 1632,  638, 1660,  602, 526,  632, 1634,  608, 1658,  632, 1636,  608, 1690,  602, 1632,  632, 1662,  604, 552,  576, 552,  604, 550,  628, 526,  630, 524,  632, 554,  600, 522,  604, 548,  628, 1634,  632, 1630,  632, 1632,  632, 1632,  608, 1656,  632, 41048,  9412, 2238,  610};  // NEC F7E01F
uint16_t IrData_FitaLed_Efeito_Flash[71] = {9418, 4514,  608, 552,  608, 582,  600, 526,  606, 578,  602, 528,  604, 552,  630, 526,  608, 578,  576, 1660,  634, 1634,  608, 1660,  608, 1688,  602, 528,  606, 1660,  632, 1634,  634, 1632,  632, 1636,  608, 1658,  634, 524,  606, 1660,  608, 550,  606, 550,  632, 526,  632, 526,  606, 550,  606, 552,  630, 1662,  608, 522,  606, 1658,  634, 1662,  580, 1658,  610, 1658,  608, 41052,  9442, 2214,  630};  // NEC F7D02F
uint16_t IrData_FitaLed_Efeito_Strobe[71] = {9350, 4534,  612, 564,  566, 564,  586, 568,  586, 566,  586, 592,  560, 568,  584, 566,  588, 588,  558, 1678,  582, 1676,  590, 1700,  562, 1676,  590, 592,  562, 1702,  564, 1676,  588, 1680,  588, 1676,  588, 1678,  586, 1680,  582, 1702,  562, 564,  588, 590,  562, 564,  586, 590,  588, 538,  588, 590,  562, 566,  586, 564,  588, 1678,  586, 1676,  590, 1678,  586, 1678,  588, 40932,  9284, 2258,  588};  // NEC F7F00F
uint16_t IrData_FitaLed_Efeito_Fade[71] = {9292, 4518,  624, 552,  596, 528,  620, 554,  598, 526,  622, 526,  624, 614,  506, 582,  592, 526,  600, 1688,  598, 1632,  632, 1650,  648, 1628,  648, 524,  642, 1632,  630, 1660,  622, 1662,  638, 1658,  626, 1662,  644, 554,  588, 556,  648, 1632,  650, 528,  644, 530,  648, 526,  648, 528,  646, 528,  644, 1636,  644, 1634,  652, 526,  620, 1662,  652, 1634,  652, 1634,  650, 40982,  9518, 2218,  634};  // NEC F7C837
uint16_t IrData_FitaLed_Efeito_Random[71] = {9320, 4522,  626, 528,  596, 586,  596, 534,  596, 556,  598, 558,  598, 556,  596, 556,  620, 532,  618, 1642,  592, 1668,  594, 1668,  594, 1666,  596, 556,  616, 1642,  618, 1640,  622, 1638,  592, 1668,  620, 1640,  594, 1666,  622, 530,  618, 1640,  594, 582,  566, 558,  592, 556,  622, 528,  620, 532,  618, 530,  590, 1668,  622, 530,  616, 1642,  592, 1668,  620, 1640,  590, 41090,  9328, 2222,  596};  // NEC F7E817
uint16_t IrData_FitaLed_Velocidade_Mais[71] = {9336, 4520,  624, 530,  624, 528,  602, 552,  600, 578,  602, 528,  620, 528,  600, 554,  598, 554,  624, 1638,  626, 1636,  630, 1636,  628, 1636,  630, 528,  622, 1640,  602, 1662,  628, 1638,  628, 528,  628, 528,  626, 528,  624, 532,  600, 554,  600, 554,  628, 528,  602, 552,  628, 1636,  630, 1638,  602, 1664,  630, 1636,  604, 1664,  630, 1590,  650, 1662,  632, 1636,  632, 41064,  9368, 2218,  602};  // NEC F700FF
uint16_t IrData_FitaLed_Velocidade_Menos[71] = {9440, 4518,  582, 580,  578, 550,  634, 526,  606, 580,  608, 522,  634, 526,  604, 580,  580, 550,  610, 1658,  634, 1636,  610, 1658,  638, 1632,  634, 526,  610, 1658,  612, 1658,  612, 1658,  634, 1664,  582, 550,  608, 580,  580, 550,  610, 550,  608, 550,  634, 524,  606, 550,  636, 524,  630, 1634,  608, 1690,  578, 1660,  610, 1658,  632, 1636,  634, 1662,  582, 1658,  608, 41086,  9430, 2216,  608};  // NEC F7807F
uint16_t IrData_FitaLed_Cor_Vermelho[71] = {9332, 4516,  602, 552,  604, 552,  600, 552,  626, 528,  622, 528,  602, 552,  624, 528,  602, 578,  598, 1636,  600, 1662,  602, 1662,  626, 1664,  600, 528,  622, 1662,  600, 1638,  624, 1640,  626, 528,  624, 530,  624, 1638,  600, 554,  626, 528,  624, 530,  622, 530,  598, 554,  624, 1640,  626, 1638,  622, 532,  622, 1664,  572, 1666,  598, 1664,  626, 1638,  596, 1664,  598, 41104,  9318, 2250,  620};  // NEC F720DF
uint16_t IrData_FitaLed_Cor_Verde[71] = {9336, 4518,  630, 526,  626, 530,  628, 528,  624, 520,  638, 526,  620, 534,  600, 552,  624, 530,  626, 1638,  628, 1638,  598, 1664,  628, 1636,  626, 528,  600, 1664,  626, 1638,  598, 1664,  628, 1636,  626, 528,  624, 1638,  600, 558,  626, 528,  598, 556,  624, 530,  626, 530,  626, 528,  626, 1638,  628, 530,  624, 1638,  602, 1662,  604, 1662,  624, 1640,  626, 1640,  624, 41066,  9358, 2220,  598};  // NEC F7A05F
uint16_t IrData_FitaLed_Cor_Azul[71] = {9456, 4524,  600, 564,  602, 562,  600, 560,  600, 560,  600, 564,  596, 562,  600, 560,  622, 536,  598, 1672,  600, 1670,  600, 1670,  600, 1670,  602, 562,  626, 1644,  602, 1668,  606, 1670,  602, 564,  598, 1670,  600, 1668,  602, 566,  598, 560,  598, 564,  598, 562,  600, 560,  596, 1672,  598, 560,  596, 560,  596, 1670,  598, 1672,  596, 1670,  600, 1670,  598, 1670,  594, 41080,  9382, 2250,  598};  // NEC F7609F
uint16_t IrData_FitaLed_Cor_VermelhoVerde[71] = {9524, 4488,  638, 524,  608, 554,  638, 524,  634, 526,  608, 552,  636, 524,  608, 552,  634, 526,  610, 1660,  636, 1634,  638, 1618,  650, 1638,  630, 528,  608, 1660,  638, 1632,  612, 1658,  612, 582,  604, 528,  634, 524,  610, 1660,  638, 524,  610, 552,  608, 578,  606, 526,  632, 1664,  580, 1660,  608, 1662,  608, 552,  608, 1660,  634, 1634,  608, 1692,  602, 1634,  632, 41062,  9486, 2214,  636};  // NEC F710EF
uint16_t IrData_FitaLed_Cor_AzulVerde[71] = {9296, 4522,  624, 530,  594, 556,  596, 556,  592, 556,  620, 530,  620, 532,  618, 534,  618, 532,  592, 1666,  594, 1694,  568, 1668,  620, 1642,  594, 558,  618, 1642,  594, 1666,  620, 1642,  596, 1690,  568, 590,  560, 558,  618, 1642,  620, 532,  592, 558,  590, 558,  616, 532,  594, 556,  592, 1670,  592, 1668,  620, 532,  592, 1666,  594, 1668,  594, 1666,  596, 1666,  622, 41076,  9314, 2222,  594};  // NEC F7906F
uint16_t IrData_FitaLed_Cor_VermelhoAzul[65] = {2348, 338,  1180, 166,  250, 892,  656, 1438,  1338, 5746,  524, 706,  254, 3358,  232, 1030,  314, 566,  280, 5580,  186, 1918,  386, 1850,  306, 3184,  306, 2138,  238, 2098,  272, 780,  304, 2840,  312, 1948,  496, 824,  252, 672,  526, 864,  250, 876,  280, 8690,  454, 2024,  274, 1780,  418, 1790,  468, 41960,  512, 666,  276, 282,  1232, 482,  252, 1856,  794, 1480,  462};  // UNKNOWN D648CC12

long day = 86400000; // 86400000 milliseconds in a day
long hour = 3600000; // 3600000 milliseconds in an hour
long minute = 60000; // 60000 milliseconds in a minute
long second =  1000; // 1000 milliseconds in a second

int khz = 38;

LiquidCrystal_I2C lcd(0x27, 16, 2);

WiFiClient wifiClient;
WiFiUDP udp;

#define DEVICE_TYPE   "arduino"
#define DEVICE_ID     "arduino2"
#define ORG           "XXXXXX"
#define TOKEN         "XXXXXX&?F_K?ZxU0"

char server[]         = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[]          = "iot-2/evt/status/fmt/json";
char topicdebug[]     = "iot-2/evt/debug/fmt/json";
char subTopic[]       = "iot-2/cmd/+/fmt/json";
char authMeth[]       = "use-token-auth";
char token[]          = TOKEN;
char clientId[]       = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
bool MqqttIs          = false;

void MqttCallback(char* topic, byte* payload, unsigned int payloadLength);

PubSubClient client(server, 1883, MqttCallback, wifiClient);

void GeralComandos(String Comando, String Comando2);
  
#define FIREBASE_HOST "XXXXXX.firebaseio.com"
#define FIREBASE_KEY "XXXXXX"
#define FIREBASE_HOST_UPDATE "http://XXXXXX/atualizar_status.php"

String FIREBASE_DEVICE_Lampada1 = "1";
String FIREBASE_DEVICE_ArCondicionado1 = "2";
String FIREBASE_DEVICE_DataShow = "3";

FirebaseData firebaseData1;

os_timer_t tmr0;
os_timer_t tmr1;
os_timer_t tmr2;
os_timer_t tmr3;

SimpleTimer TimerCtrl1;

void setup() {
  
  Serial.begin(115200);

  GeralPinout(); // Comentar para ativar o Debug Serial

  WifiConectar();
  
  IrIniciar();
  LcdIniciar();
  
  //MqttConectar(false);

  GeralTimer();

  SPIFFS_Iniciar();
  
  HttpServer_Iniciar();
  
  //WebSocket_Iniciar();
  
  //FirebaseIniciar();

  ArCondicionado_Iniciar();

  //IrReceive_Iniciar();
  
  LCD_ShowMsg("Sistema", "Tudo OK", 10000);

}

void loop() {
  
  //if( MqqttIs == true )
  //{
    
    //if(!client.connected() && WiFi.status() == WL_CONNECTED)
    //{
  
      //MqttConectar(true);
            
    //}

  //}

  if(client.connected())
  {

    client.loop();
      
  }
  
  HttpServer_Loop();

  //WebSocket_Loop();  
  
  CtrlTimer();

  //IrReceive_Loop();
    
}

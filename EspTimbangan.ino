#include <DNSServer.h>
#include <ESPUI.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <HTTPClient.h>

const byte DNS_PORT = 53;
IPAddress apIP( 192, 168, 4, 1 );
DNSServer dnsServer;

const char* ssid = "songo";
const char* password = "12345678";
const char* hostname = "Indikator";
const char* ssidAP = "Indikator";
const char* passAP = "87654321";

String SSIDne;
String Paswordte;
String Status;
String WebLoc;
String DumInd;
String IpAdd;
uint16_t status;
uint16_t status1;
uint16_t status2;

//Your Domain name with URL path or IP address with path
String serverName2 = "http://192.168.43.89:84/web_timbangan/prosestimbang";
String serverName = "https://centrist-soldier.000webhostapp.com/prosestimbang";
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;
char DataSer;
int DataOK=3;
String Header = "Cek=";
String DataStr;
String DataStrBack;
long randomdata1;
long randomdata2;
int randomdata3;
int TerimaInd=0;
int WifiDisckon=0;

const int AddrSSID  = 0;   // 30
const int AddrPsw   = 30;  // 10
const int AddrServ1  = 40;  // 110
const int AddrServ2   = 150; // 
const int AddrWebLoc   = 260; // 5
const int AddrDumInd   = 270; // 5
int Addr;

#define RX 16
#define TX 17

void setup() 
{
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RX, TX);
  
  Serial.println("Program Timbangan");

  delay(1000);
  if (!EEPROM.begin(512)) 
  {
    Serial.println("Failed to initialise EEPROM");
    Serial.println("Restarting...");
    delay(1000);
    ESP.restart();
  }

  Addr=2;
  if(isAlphaNumeric(EEPROM.readChar(Addr)))
  {
    Addr = AddrSSID;
    SSIDne=EEPROM.readString(Addr);
    Addr = AddrPsw;
    Paswordte=EEPROM.readString(Addr);
    Addr = AddrServ1;
    serverName=EEPROM.readString(Addr);
    Addr = AddrServ2;
    serverName2=EEPROM.readString(Addr);
    Addr = AddrWebLoc;
    WebLoc=EEPROM.readString(Addr);
    Addr = AddrDumInd;
    DumInd=EEPROM.readString(Addr);
    
    ssid=SSIDne.c_str();
    password=Paswordte.c_str();

    
    Serial.print("SSIDne =");
    Serial.println(SSIDne);
    Serial.print("Paswordte =");
    Serial.println(Paswordte);
    Serial.print("NamaServer =");
    Serial.println(serverName);
    Serial.print("serverName2 =");
    Serial.println(serverName2);
    Serial.print("Web>0 atau Loc>1 =");
    Serial.println(WebLoc);
    Serial.print("Dum>0 atau Ind>1 =");
    Serial.println(DumInd);
  }

  WiFi.setHostname(hostname);
  WiFi.begin(ssid, password );
  CekKoneksi();
  DNS_Server();
  Serial.print("IP Address: ");
  Serial.println(IpAdd);
   if(WebLoc.indexOf("0")>=0)
   {
     ESPUI.updateControlValue(status, "Server Web Timbangan" );
   }
   else if(WebLoc.indexOf("1")>=0)
   {
     ESPUI.updateControlValue(status, "Server Localhost" );
   }
   if(DumInd.indexOf("0")>=0)
   {
     ESPUI.updateControlValue(status2, "Dummy Data Generator" );
   }
   else if(DumInd.indexOf("1")>=0)
   {
     ESPUI.updateControlValue(status2, "Real Data Indikator" );
   }
}

void loop() 
{
  if(DumInd.indexOf("1")>=0)
  {
    DataStr="";
    while(DataStr=="")
    {
      DataSer=0;
      Terima_Serial();
      Serial2.flush();
      if(DataStr.length() != 6)
      {
        DataStr="";
        Terima_Serial();
        Serial2.flush();
      }
    Serial.println(DataStr);
    }
  }
  else
  {
   if(DataOK==1)
   {
     randomdata3=random(4,10);
     DataStr=String(randomdata1 + randomdata3 );
   }
   else if(DataOK==2)
   {
     randomdata3=random(4,10);
     DataStr=String(randomdata2 + randomdata3);
   }
   else if(DataOK==3)
   {
     randomdata2=random(10000,30000);
     randomdata1=random(3000,7000);
   }
  }
 
 if(DataOK==1)
 {
   Header = "DataStr=";
 }
 else if(DataOK==2)
 {
   Header = "DataStr1=";
 }
 else if(DataOK==3)
 {
   Header = "Cek=";
 }
 KirimDataWeb();
 delay(500);
 ReadSerialDummy();
 DataStr="";
 dnsServer.processNextRequest();
}

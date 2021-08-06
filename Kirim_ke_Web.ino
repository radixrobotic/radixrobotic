void KirimDataWeb()
{
  if(WiFi.status()== WL_CONNECTED)
  {
    HTTPClient http;
      
    // Your Domain name with URL path or IP address with path
    Serial.print("Web>0 atau Loc>1 :");
    Serial.println(WebLoc);
    if(WebLoc.indexOf("1")>=0)
    {
      Serial.println("localhost");
      http.begin(serverName2);
    }
    else
    {
      http.begin(serverName);
    }
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    // Data to send with HTTP POST
    auto httpRequestData = Header + DataStr;
    Serial.println(httpRequestData);
           
    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
      
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    Serial.println(http.errorToString(httpResponseCode).c_str());
    String payload = http.getString();
    Serial.println(payload);
    Serial.println(payload.indexOf("T1"));
    Serial.println(payload.indexOf("T2"));
    if(payload.indexOf("T1")>=0)
    {
      Serial.println("Data Terkirim");
      DataOK=1;
    }
    else if(payload.indexOf("T2")>=0)
    {
      Serial.println("Data ke-2 Terkirim");
      DataOK=2;
    }
    else if(payload.indexOf("SLS")>=0)
    {
      Serial.println("SELESAI TIMBANG");
      DataOK=3;
    }

    // Free resources
    http.end();
   }
   else 
   {
     Serial.println("WiFi Disconnected");
/*     if(WifiDisckon>5)
     {
      delay(5000);
      ESP.restart();
     }
     WifiDisckon++;*/
     delay(1000);
     WiFi.setHostname(hostname);
     WiFi.begin(ssid, password );
     CekKoneksi();
     ReadSerialDummy();
   }
}

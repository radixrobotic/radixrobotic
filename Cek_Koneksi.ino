void CekKoneksi()
{
  {
    uint8_t timeout = 15;
    // Wait for connection, 5s timeout
    do 
    {
      delay(500);
      timeout--;
    } 
    while(timeout && WiFi.status() != WL_CONNECTED);

    // not connected -> create hotspot
    if (WiFi.status() != WL_CONNECTED )
    {
      WiFi.mode(WIFI_AP);
      WiFi.softAPConfig(apIP, apIP, IPAddress( 255, 255, 255, 0 ) );
      WiFi.softAP(ssidAP,passAP);
      timeout = 5;
      do 
      {
        delay( 500 );
        Serial.print( "." );
        timeout--;
      } 
      while (timeout);
    }
  }  
}

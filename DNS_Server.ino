void DNS_Server()
{
  dnsServer.start(DNS_PORT, "Indikator", apIP);
  if(WiFi.getMode() == WIFI_AP)
  {
    Status = "HOTSPOT AP";
    IpAdd = WiFi.softAPIP().toString();
  }
  else
  {
    Status="Terkoneksi Dengan WiFi";
    IpAdd = WiFi.localIP().toString();
  }
  uint16_t tab1 = ESPUI.addControl( ControlType::Tab, "Settings 1", "Config Network" );
  uint16_t tab2 = ESPUI.addControl( ControlType::Tab, "Settings 2", "Config Server Address" );
  uint16_t tab3 = ESPUI.addControl( ControlType::Tab, "Settings 3", "Config Pengiriman Data" );
    
  ESPUI.addControl( ControlType::Text, "SSID (Maks 30 Huruf) :", SSIDne, ControlColor::Alizarin, tab1, &textCall);
  ESPUI.addControl( ControlType::Text, "PASSWORD (Maks 10 Karakter):", Paswordte, ControlColor::Alizarin, tab1, &textCall2);
   
  ESPUI.addControl( ControlType::Text, "Nama Server (URL):", serverName, ControlColor::Alizarin, tab2, &textCall3);
  ESPUI.addControl( ControlType::Text, "IP Localhost:", serverName2, ControlColor::Alizarin, tab2, &textCall4);

  // shown above all tabs
  uint16_t select1 = ESPUI.addControl( ControlType::Select, "Pilih Pengiriman ke Server:", "", ControlColor::Emerald, tab3, &selectExample );
  ESPUI.addControl( ControlType::Option, "Pilih Alamat Pengiriman", "x", ControlColor::Alizarin, select1 );
  ESPUI.addControl( ControlType::Option, "Server Web Timbangan", "0", ControlColor::Alizarin, select1 );
  ESPUI.addControl( ControlType::Option, "Server Localhost", "1", ControlColor::Alizarin, select1 );

  uint16_t select2 = ESPUI.addControl( ControlType::Select, "Pilih Metode Data:", "", ControlColor::Emerald, tab3, &selectExample2 );
  ESPUI.addControl( ControlType::Option, "Pilih Metode Data Yang Dikirim", "x", ControlColor::Alizarin, select2 );
  ESPUI.addControl( ControlType::Option, "Dummy Data Generator", "0", ControlColor::Alizarin, select2 );
  ESPUI.addControl( ControlType::Option, "Real Data Indikator", "1", ControlColor::Alizarin, select2 );

  status1 = ESPUI.addControl( ControlType::Label, "Status Koneksi", Status + " : " + IpAdd, ControlColor::Turquoise );
  status = ESPUI.addControl( ControlType::Label, "Status Pengiriman ke Server", "", ControlColor::Turquoise );
  status2 = ESPUI.addControl( ControlType::Label, "Status Metode Data Yang Dikirim", "", ControlColor::Turquoise );

  ESPUI.begin("ESPUI Control");
}

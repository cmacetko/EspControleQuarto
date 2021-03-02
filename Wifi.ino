void WifiConfigModeCallback(WiFiManager *myWiFiManager) {
  
  
  
}

void WifiConectar(){

  GeralDebug("Conectando ao Wifi...");
  
  WiFiManager wifiManager;
  
  wifiManager.setMinimumSignalQuality(10);
  wifiManager.setRemoveDuplicateAPs(true);
  wifiManager.setDebugOutput(true);
  wifiManager.setAPCallback(WifiConfigModeCallback);

  IPAddress _ip = IPAddress(192, 168, 20, 100);
  IPAddress _gw = IPAddress(192, 168, 20, 1);
  IPAddress _sn = IPAddress(255, 255, 255, 0);

  wifiManager.setSTAStaticIPConfig(_ip, _gw, _sn);

  if( wifiManager.autoConnect("CtrlPotter", "12345678") )
  {

    GeralDebug("Conectado");

    //IPAddress _ip = IPAddress(192, 168, 20, 100);
    //IPAddress _gw = IPAddress(192, 168, 20, 1);
    //IPAddress _sn = IPAddress(255, 255, 255, 0);
    //IPAddress _dns = IPAddress(8, 8, 8, 8);
    
    //WiFi.config(_ip, _dns, _gw, _sn);
    //Serial.print("Dns configured.");
    
  }else{ 
  
    GeralDebug("Falha em Conectar");

  }
  
}

void WifiCheck(void*z){

  if(WiFi.status() != WL_CONNECTED){

    GeralDebug("Conexao Caiu!");

    LCD_ShowMsg("ATENCAO:", "Wifi Off", 10000);
    
  }else{

    //GeralDebug("Conexao OK!");
    
  }
  
}

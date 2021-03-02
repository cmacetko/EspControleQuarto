void FirebaseIniciar(){

  Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);
  Firebase.reconnectWiFi(true);

  firebaseData1.setBSSLBufferSize(1024, 1024);
  firebaseData1.setResponseSize(1024);

  if (!Firebase.beginStream(firebaseData1, "/dispositivos"))
  {
    
    GeralDebug("Falha em Conectar com FireBase: " + firebaseData1.errorReason());
    
  }

  Firebase.setStreamCallback(firebaseData1, FirebaseStreamCallback, FirebaseStreamTimeoutCallback);

}

void FirebaseStreamCallback(StreamData data)
{

  GeralDebug("FirebaseStreamCallback");
  GeralDebug(data.dataPath());
  
  if( data.eventType() == "put" && data.dataType() == "json" && data.dataPath() == "/" + FIREBASE_DEVICE_Lampada1 + "/status")
  {
  
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, data.jsonString());
    
    if (error)
    {
      
      return;
      
    }
    
    String value = doc["on"];

    if( value == "true" )
    {
      
      GeralDebug("Lampada1: Desligar");
            
    }else{

      GeralDebug("Lampada1: Ligar");
    
    }

    GeralComandos("Luz1", "");
    
  }

  if( data.eventType() == "put" && data.dataType() == "json" && data.dataPath() == "/" + FIREBASE_DEVICE_ArCondicionado1 + "/status")
  {

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, data.jsonString());
    
    if (error)
    {
      
      return;
      
    }
    
    String thermostatMode = doc["thermostatMode"];
    int thermostatTemperatureSetpoint = doc["thermostatTemperatureSetpoint"];

    if( thermostatMode == "heat" ){
    
      ArConfigObj.OnOff = "On";
      ArConfigObj.Modo = "Heat";
  
    }else if( thermostatMode == "cool" ){
      
      ArConfigObj.OnOff = "On";
      ArConfigObj.Modo = "Cool";
      
    }else{
  
      ArConfigObj.OnOff = "Off";
    
    }

    if( thermostatTemperatureSetpoint < 16 )
    {

      thermostatTemperatureSetpoint = 16;
      
    }

    if( thermostatTemperatureSetpoint > 30 )
    {

      thermostatTemperatureSetpoint = 30;
      
    }
      
    ArConfigObj.Temperatura = thermostatTemperatureSetpoint;

    GeralDebug("ArCondicionado1 - Modo: " + thermostatMode);
    GeralDebug("ArCondicionado1 - Temperatura: " + thermostatTemperatureSetpoint);
    
    ArCondicionado_Comandos_Enviar();
    
  }

  if( data.eventType() == "put" && data.dataType() == "json" && data.dataPath() == "/" + FIREBASE_DEVICE_DataShow + "/status")
  {
  
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, data.jsonString());
    
    if (error)
    {
      
      return;
      
    }
    
    String value = doc["on"];

    if( value == "true" )
    {
      
      GeralDebug("DataShow: Desligar");
            
    }else{

      GeralDebug("DataShow: Ligar");
    
    }

    GeralComandos("DataShowOnOff", "");
    
  }
  
}

void FirebaseStreamTimeoutCallback(bool timeout)
{
  
  if(timeout)
  {
  
    GeralDebug("Firebase: Stream timeout, resume streaming...");
  
  }
  
}

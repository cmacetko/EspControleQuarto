void MqttCallback(char* topic, byte* payload, unsigned int payloadLength) {
  
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, payload);
  
  if (error)
  {
    
    return;
    
  }

  String acao = doc["Acao"];

  GeralComandos(acao);

  serializeJson(doc, Serial);
  
}

void MqttConectar(bool IsReconexao){

  if( MqqttIs == true )
  {
      
    GeralDebug("Conectando com: ");
    GeralDebug(server);
      
    if(client.connect(clientId, authMeth, token))
    {
  
      GeralDebug("Conectado com: ");
      GeralDebug(server);
  
      client.setCallback(MqttCallback);
  
      MqttSubscribe();
    
      delay(500);
  
      Publish_SendStatePort(LED_BUILTIN, "1");
  
      delay(500);
  
      if( IsReconexao == true )
      {
  
        LCD_ShowMsg("Sistema", "Reconectado", 10000);
        
      }
      
    }else{
  
      GeralDebug("Falha em Conectar em: ");
      GeralDebug(server);
  
      GeralDebug("State: ");
      GeralDebug(String(client.state()));
  
    }

  }
  
}

void MqttSubscribe(){

  if( MqqttIs == true )
  {
    
    GeralDebug("Subscribe com: ");
    GeralDebug(subTopic);
    
    if(client.subscribe(subTopic, 0)){
      
      //GeralDebug("Subscribe OK");
    
    } else {
      
      GeralDebug("Subscribe Falho");
    
    }

  }
  
}

void MqttCheck(void*z){

  if( MqqttIs == true )
  {
    
    if (!client.connected()) {
  
      GeralDebug("Mqtt Caiu!");
  
      if(WiFi.status() == WL_CONNECTED){
    
        LCD_ShowMsg("ATENCAO:", "MQTT Off", 10000);
        
      }
  
    }else{
  
      //GeralDebug("Mqtt OK!");
      
    }

  }
  
}

void Publish_SendStatePort(int Port, String Identificador){

  if( MqqttIs == true )
  {
  
    if( digitalRead(Port) == LOW )
    {
  
      Publish_SendJson("{\"d\":{\"Dispositivo\":\"Port" + Identificador + "\", \"Status\":1}}");
      
    }else{
  
      Publish_SendJson("{\"d\":{\"Dispositivo\":\"Port" + Identificador + "\", \"Status\":0}}");
      
    }

  }
  
}

void Publish_SendJson(String payload){

  if( MqqttIs == true )
  {
    
    GeralDebug("Publish: ");
    GeralDebug(payload);
  
    if(client.connected()){
   
      if (client.publish(topic, (char*) payload.c_str())) 
      {
        
        GeralDebug("Publish OK");
        
      } else {
        
        GeralDebug("Publish Falho");
        
      }
  
    }else{
  
      GeralDebug("Ignorado - Sem Conexao");
      
    }

  }
  
}

void Publish_SendJsonDebug(String payload){

  if( MqqttIs == true )
  {
    
    if (client.publish(topicdebug, (char*) payload.c_str())) 
    {
      
      //
      
    }

  }
  
}

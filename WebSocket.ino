void WebSocket_Iniciar(){

  webSocket.begin(); 
  webSocket.onEvent(WebSocket_onEvent);
  
}

void WebSocket_Loop(){

  webSocket.loop();

}

void WebSocket_onEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght){

  switch(type) 
  {
  
    case WStype_DISCONNECTED:
    {
    
      GeralDebug("WebSocket - Disconnected:");
      GeralDebug(num);
    
    }
    break;
    
    case WStype_CONNECTED: 
    {       

      GeralDebug("WebSocket - Connected:");
      GeralDebug(num);
    
    }
    break;
    
    case WStype_TEXT: 
    {

      GeralDebug("WebSocket - Text:");
      GeralDebug(num);
      
      //GeralDebug("payload:");
      //GeralDebug(payload);
    
    }
    break;
  
  }

}

void HttpServer_Iniciar(){

  //httpserver.on("/", HttpServer_Page_Index);
  
  httpserver.on("/", []() {
  
    HttpServer_Autenticacao();
    
    SPIFFS_HttpServer_handleFileRead("/index.html");
  
  });
  
  httpserver.on("/comandos/", HttpServer_Page_Comandos);
  httpserver.on("/comandos_json/", HttpServer_Page_ComandosJson);
  httpserver.on("/dados_json/", HttpServer_Page_DadosJson);

  httpserver.onNotFound(HttpServer_Page_404); 
  
  httpserver.begin(); 
  
  GeralDebug("Servidor HTTP Iniciado");
  
}

void HttpServer_Autenticacao(){

  if (!httpserver.authenticate(www_username, www_password)) 
  {
    
    return httpserver.requestAuthentication();
  
  }
  
}

void HttpServer_Loop(){

  httpserver.handleClient();
  
}

void HttpServer_Page_Comandos(){

  HttpServer_Autenticacao();
  
  if( httpserver.hasArg("Comando") )
  {

    GeralComandos(httpserver.arg("Comando"), httpserver.arg("Comando2"));

    httpserver.sendHeader("Location", "/");
    httpserver.send(303);

  }else{
    
    httpserver.sendHeader("Location", "/");
    httpserver.send(303);
    
  }
  
}

void HttpServer_Page_ComandosJson(){

  HttpServer_Autenticacao();
  
  GeralDebug("HttpServer_Page_ComandosJson");
  GeralDebug(httpserver.arg("plain"));
  
  if( httpserver.hasArg("plain") )
  {

    DynamicJsonDocument root(1024);
    DeserializationError error = deserializeJson(root, httpserver.arg("plain"));
    
    if(error) 
    {
      
      GeralDebug("HttpServer_Page_ComandosJson: Error");
    
    }else{

      if(root.containsKey("Modulo"))
      {

        String Dads_Modulo = root["Modulo"];
        
        if( Dads_Modulo == "ArCondicionado" ){

          ArCondicionado_ComandosJson(root);

        }else if( Dads_Modulo == "ArCondicionado_AutoDesligar" ){

          ArCondicionado_ComandosJson_AutoDesligar(root);
      
        }else if( Dads_Modulo == "Comandos" ){

          String Dads_Comando = root["Comando"];

          GeralComandos(Dads_Comando);
      
        }
  
      }

    }
    
  }else{

    GeralDebug("HttpServer_Page_ComandosJson: Nao chegou o Json");
    
  }

  StaticJsonDocument<200> DocGer;
  
  DocGer["IsOK"] = true;

  String JsonOutput;
  serializeJson(DocGer, JsonOutput);
  
  httpserver.send(200, "application/json", JsonOutput);
  
}

void HttpServer_Page_DadosJson(){

  HttpServer_Autenticacao();
  
  StaticJsonDocument<200> DocGer;
  
  DocGer["ArCondicionado_OnOff"] = ArConfigObj.OnOff;
  DocGer["ArCondicionado_Modo"] = ArConfigObj.Modo;
  DocGer["ArCondicionado_FanVelocidade"] = ArConfigObj.FanVelocidade;
  DocGer["ArCondicionado_PosicaoTipo"] = ArConfigObj.PosicaoTipo;
  DocGer["ArCondicionado_Posicao"] = ArConfigObj.Posicao;
  DocGer["ArCondicionado_Temperatura"] = ArConfigObj.Temperatura;
  
  DocGer["ArCondicionado_AutoDesligarID"] = ArConfigObj.AutoDesligarID;
  DocGer["ArCondicionado_AutoDesligarTempo"] = ArConfigObj.AutoDesligarTempo;
  DocGer["ArCondicionado_AutoDesligarDataFim"] = ArConfigObj.AutoDesligarDataFim;

  String JsonOutput;
  serializeJson(DocGer, JsonOutput);
  
  httpserver.send(200, "application/json", JsonOutput);

}

void HttpServer_Page_404(){

  if(!SPIFFS_HttpServer_handleFileRead(httpserver.uri())) 
  {  
  
    httpserver.send(404, "text/plain", "404: Not found");
  
  }
  
}

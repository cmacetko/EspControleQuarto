struct ArConfig
{
   String OnOff;
   String Modo;
   String FanVelocidade;
   String PosicaoTipo;
   String Posicao;
   int Temperatura;
   int AutoDesligarTempo;
   int AutoDesligarID;
   int AutoDesligarDataFim;
};

struct ArConfig ArConfigObj;

void ArCondicionado_Iniciar()
{

  ac.begin();

  ArConfigObj.OnOff = "Off";
  ArConfigObj.Modo = "Cool";
  ArConfigObj.FanVelocidade = "Max";
  ArConfigObj.PosicaoTipo = "Manual";
  ArConfigObj.Posicao = "Alto";
  ArConfigObj.Temperatura = 20;
  
  ArConfigObj.AutoDesligarTempo = 0;
  ArConfigObj.AutoDesligarID = -1;
  ArConfigObj.AutoDesligarDataFim = 0;

}

void ArCondicionado_ComandosJson(DynamicJsonDocument root)
{

  String Dads_OnOff = root["OnOff"];
  String Dads_Modo = root["Modo"];
  String Dads_FanVelocidade = root["FanVelocidade"];
  String Dads_PosicaoTipo = root["PosicaoTipo"];
  String Dads_Posicao = root["Posicao"];
  int Dads_Temperatura = root["Temperatura"];
  
  ArConfigObj.OnOff = Dads_OnOff;
  ArConfigObj.Modo = Dads_Modo;
  ArConfigObj.FanVelocidade = Dads_FanVelocidade;
  ArConfigObj.PosicaoTipo = Dads_PosicaoTipo;
  ArConfigObj.Posicao = Dads_Posicao;
  ArConfigObj.Temperatura = Dads_Temperatura;

  ArCondicionado_Comandos_Enviar();

}

void ArCondicionado_Comandos_Enviar()
{

  if( ArConfigObj.OnOff == "On" )
  {  
    
    ac.on();
    
    if( ArConfigObj.Modo == "Cool" ){
  
      ac.setMode(kGreeCool);
  
    }else if( ArConfigObj.Modo == "Heat" ){
  
      ac.setMode(kGreeHeat);
    
    }else if( ArConfigObj.Modo == "Fan" ){
  
      ac.setMode(kGreeFan);
    
    }
  
    if( ArConfigObj.FanVelocidade == "Min" ){
  
      ac.setFan(kGreeFanMin);
  
    }else if( ArConfigObj.FanVelocidade == "Med" ){
  
      ac.setFan(kGreeFanMed);
    
    }else if( ArConfigObj.FanVelocidade == "Max" ){
  
      ac.setFan(kGreeFanMax);
    
    }
  
    if( ArConfigObj.PosicaoTipo == "Auto" ){
  
      if( ArConfigObj.Posicao == "Baixo" ){
    
        ac.setSwingVertical(true, kGreeSwingDownAuto);
    
      }else if( ArConfigObj.Posicao == "Medio" ){
  
        ac.setSwingVertical(true, kGreeSwingMiddleAuto);
  
      }else if( ArConfigObj.Posicao == "Alto" ){
    
        ac.setSwingVertical(true, kGreeSwingUpAuto);
      
      }
  
    }else if( ArConfigObj.PosicaoTipo == "Manual" ){
  
      if( ArConfigObj.Posicao == "Baixo" ){
    
        ac.setSwingVertical(false, kGreeSwingDown);
    
      }else if( ArConfigObj.Posicao == "Medio" ){
  
        ac.setSwingVertical(false, kGreeSwingMiddleUp);
  
      }else if( ArConfigObj.Posicao == "Alto" ){
    
        ac.setSwingVertical(false, kGreeSwingUp);
      
      }
    
    }
  
    ac.setTemp(ArConfigObj.Temperatura);
    
    ac.setLight(true);
    ac.setTurbo(false);
    ac.setSleep(false);

  }else{

    ac.off();

  }

  ac.send();

  ArCondicionado_Firebase();
  
}

void ArCondicionado_ComandosJson_AutoDesligar(DynamicJsonDocument root)
{

  int Dads_Tempo = root["Tempo"];
  int Dads_DataFinal = root["DataFinal"];

  if( Dads_Tempo == 0 )
  {  

    if( ArConfigObj.AutoDesligarID >= 0 )
    {

      TimerCtrl1.deleteTimer(ArConfigObj.AutoDesligarID);
      
    }

    ArConfigObj.AutoDesligarID = -1;
    ArConfigObj.AutoDesligarTempo = 0;    
    ArConfigObj.AutoDesligarDataFim = 0;
    
  }else{

    if( ArConfigObj.AutoDesligarID >= 0 )
    {

      TimerCtrl1.deleteTimer(ArConfigObj.AutoDesligarID);
      
    }

    ArConfigObj.AutoDesligarID = TimerCtrl1.setTimeout(Dads_Tempo * second, ArCondicionado_ComandosJson_AutoDesligar_Executar);
    ArConfigObj.AutoDesligarTempo = Dads_Tempo;
    ArConfigObj.AutoDesligarDataFim = Dads_DataFinal;

  }

}

void ArCondicionado_ComandosJson_AutoDesligar_Executar()
{
  
  ArConfigObj.AutoDesligarID = -1;
  ArConfigObj.AutoDesligarTempo = 0;    
  ArConfigObj.AutoDesligarDataFim = 0;

  ac.off();
  ac.send();

  ArCondicionado_Firebase();
    
}

void ArCondicionado_Firebase()
{

  StaticJsonDocument<200> DocGer;
  
  DocGer["comando"] = "atualizar_status";
  DocGer["devices"]["0"]["id"] = FIREBASE_DEVICE_ArCondicionado1;
  DocGer["devices"]["0"]["params"]["thermostatMode"] = ArConfigObj.Modo;
  DocGer["devices"]["0"]["params"]["thermostatTemperatureSetpoint"] = ArConfigObj.Temperatura;

  String JsonOutput;
  serializeJson(DocGer, JsonOutput);
  
  HTTPClient http;
  http.begin(FIREBASE_HOST_UPDATE);
  http.addHeader("Content-Type", "application/json");
  
  int httpCode = http.POST(JsonOutput); 
  String payload = http.getString(); 

  GeralDebug("ArCondicionado_Firebase");
  GeralDebug("----");
  GeralDebug("Enviado:");
  GeralDebug(JsonOutput);
  GeralDebug("httpCode:");
  GeralDebug(httpCode);
  GeralDebug("payload:");
  GeralDebug(payload); 
  
  http.end();

}

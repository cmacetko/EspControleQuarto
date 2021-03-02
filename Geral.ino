void GeralPinout(){

  pcf8574.begin();
  
  pcf8574.pinMode(PinoLuz1, OUTPUT);
  //pcf8574.pinMode(PinoLed1, OUTPUT);

  pcf8574.pinMode(PinoSomOnOff, OUTPUT);
  pcf8574.pinMode(PinoSomVolMais, OUTPUT);
  pcf8574.pinMode(PinoSomVolMenos, OUTPUT);
  pcf8574.pinMode(PinoSomInput, OUTPUT);
  
  pcf8574.pinMode(PinoSwitchAudioS0, OUTPUT);
  pcf8574.pinMode(PinoSwitchAudioS1, OUTPUT);
  pcf8574.pinMode(PinoSwitchAudioS2, OUTPUT);

  //pcf8574.digitalWrite(PinoLed1, HIGH);
  //delay(500);
  //pcf8574.digitalWrite(PinoLed1, LOW);
  //delay(500);
  //pcf8574.digitalWrite(PinoLed1, HIGH);
  //delay(500);
  //pcf8574.digitalWrite(PinoLed1, LOW);

}

void GeralComandos(String Comando, String Comando2 = "") {
  
  if( Comando == "Led1" ) 
  {

    if( PinoLed1Is == false )
    {

      //pcf8574.digitalWrite(PinoLed1, HIGH);

      PinoLed1Is = true;
      
    }else{
      
      //pcf8574.digitalWrite(PinoLed1, LOW);
  
      PinoLed1Is = false;
      
    }
    
  }

  if( Comando == "Luz1" ) 
  {

    if( Luz1Is == false )
    {

      pcf8574.digitalWrite(PinoLuz1, HIGH);

      Luz1Is = true;
      
    }else{
      
      pcf8574.digitalWrite(PinoLuz1, LOW);
  
      Luz1Is = false;
      
    }

  }
  
  if( Comando == "EspReiniciarForcado" ) 
  {

    ESP.reset();

  }

  if( Comando == "EspReiniciarNormal" ) 
  {

    ESP.restart();

  }

  if( Comando == "SomOnOff" ) 
  {

    pcf8574.digitalWrite(PinoSomOnOff, HIGH);    
    delay(100);    
    pcf8574.digitalWrite(PinoSomOnOff, LOW);

  }

  if( Comando == "SomVolMais" ) 
  {

    pcf8574.digitalWrite(PinoSomVolMais, HIGH);    
    delay(100);    
    pcf8574.digitalWrite(PinoSomVolMais, LOW);

  }

  if( Comando == "SomVolMaisTudo" ) 
  {

    for( int i=1; i<=20; i++ )
    {
        
      pcf8574.digitalWrite(PinoSomVolMais, HIGH);    
      delay(100);    
      pcf8574.digitalWrite(PinoSomVolMais, LOW);
      delay(100); 

    }

  }

  if( Comando == "SomVolMenos" ) 
  {

    pcf8574.digitalWrite(PinoSomVolMenos, HIGH);    
    delay(100);    
    pcf8574.digitalWrite(PinoSomVolMenos, LOW);

  }

  if( Comando == "SomVolMenosTudo" ) 
  {

    for( int i=1; i<=20; i++ )
    {
        
      pcf8574.digitalWrite(PinoSomVolMenos, HIGH);    
      delay(100);    
      pcf8574.digitalWrite(PinoSomVolMenos, LOW);
      delay(100); 

    }

  }
  
  if( Comando == "SomInput" ) 
  {

    pcf8574.digitalWrite(PinoSomInput, HIGH);    
    delay(100);    
    pcf8574.digitalWrite(PinoSomInput, LOW);

  }

  if( Comando == "SomConfig1" ) 
  {

    pcf8574.digitalWrite(PinoSomOnOff, HIGH);    
    delay(100);    
    pcf8574.digitalWrite(PinoSomOnOff, LOW);
    delay(100);    
    
    pcf8574.digitalWrite(PinoSomInput, HIGH);    
    delay(100);    
    pcf8574.digitalWrite(PinoSomInput, LOW);
    delay(100);    

    for( int i=1; i<=20; i++ )
    {
        
      pcf8574.digitalWrite(PinoSomVolMais, HIGH);    
      delay(100);    
      pcf8574.digitalWrite(PinoSomVolMais, LOW);
      delay(100); 

    }

  }

  if( Comando == "DatashowOnOff" ) 
  {

    irsend.sendRaw(IrData_DatashowOnOff, 71, khz);

  }

  if( Comando == "FitaLed_Desligar" ) 
  {

    irsend.sendRaw(IrData_FitaLed_Desligar, 71, khz);

  }

  if( Comando == "FitaLed_Ligar" ) 
  {

    irsend.sendRaw(IrData_FitaLed_Ligar, 71, khz);

  }

  if( Comando == "FitaLed_Efeito_Parado" ) 
  {

    irsend.sendRaw(IrData_FitaLed_Efeito_Parado, 71, khz);

  }

  if( Comando == "FitaLed_Efeito_Flash" ) 
  {

    irsend.sendRaw(IrData_FitaLed_Efeito_Flash, 71, khz);

  }

  if( Comando == "FitaLed_Efeito_Strobe" ) 
  {

    irsend.sendRaw(IrData_FitaLed_Efeito_Strobe, 71, khz);

  }

  if( Comando == "FitaLed_Efeito_Fade" ) 
  {

    irsend.sendRaw(IrData_FitaLed_Efeito_Fade, 71, khz);

  }

  if( Comando == "FitaLed_Efeito_Random" ) 
  {

    irsend.sendRaw(IrData_FitaLed_Efeito_Random, 71, khz);

  }

  if( Comando == "FitaLed_Velocidade_Mais" ) 
  {

    irsend.sendRaw(IrData_FitaLed_Velocidade_Mais, 71, khz);

  }

  if( Comando == "FitaLed_Velocidade_Menos" ) 
  {

    irsend.sendRaw(IrData_FitaLed_Velocidade_Menos, 71, khz);

  }

  if( Comando == "FitaLed_Cor_Vermelho" ) 
  {

    irsend.sendRaw(IrData_FitaLed_Cor_Vermelho, 71, khz);

  }

  if( Comando == "FitaLed_Cor_Verde" ) 
  {

    irsend.sendRaw(IrData_FitaLed_Cor_Verde, 71, khz);

  }

  if( Comando == "FitaLed_Cor_Azul" ) 
  {

    irsend.sendRaw(IrData_FitaLed_Cor_Azul, 71, khz);

  }

  if( Comando == "FitaLed_Cor_VermelhoVerde" ) 
  {

    irsend.sendRaw(IrData_FitaLed_Cor_VermelhoVerde, 71, khz);

  }
  
  if( Comando == "FitaLed_Cor_AzulVerde" ) 
  {

    irsend.sendRaw(IrData_FitaLed_Cor_AzulVerde, 71, khz);

  }
  
  if( Comando == "FitaLed_Cor_VermelhoAzul" ) 
  {

    irsend.sendRaw(IrData_FitaLed_Cor_VermelhoAzul, 71, khz);

  }

  if( Comando == "FitaLed_Velocidade_MaisTudo" ) 
  {

    for( int i=1; i<=10; i++ )
    {
        
      irsend.sendRaw(IrData_FitaLed_Velocidade_Mais, 71, khz);
      delay(50);

    }

  }

  if( Comando == "FitaLed_Velocidade_MenosTudo" ) 
  {

    for( int i=1; i<=10; i++ )
    {
        
      irsend.sendRaw(IrData_FitaLed_Velocidade_Menos, 71, khz);
      delay(50);

    }

  }

  if( Comando == "SwitchAudio1" ) 
  {

    pcf8574.digitalWrite(PinoSwitchAudioS0, LOW);
    pcf8574.digitalWrite(PinoSwitchAudioS1, LOW);
    pcf8574.digitalWrite(PinoSwitchAudioS2, LOW);

  }

  if( Comando == "SwitchAudio2" ) 
  {

    pcf8574.digitalWrite(PinoSwitchAudioS0, HIGH);
    pcf8574.digitalWrite(PinoSwitchAudioS1, LOW);
    pcf8574.digitalWrite(PinoSwitchAudioS2, LOW);

  }

  if( Comando == "SwitchAudio3" ) 
  {

    pcf8574.digitalWrite(PinoSwitchAudioS0, LOW);
    pcf8574.digitalWrite(PinoSwitchAudioS1, HIGH);
    pcf8574.digitalWrite(PinoSwitchAudioS2, LOW);

  }

  if( Comando == "SwitchAudio4" ) 
  {

    pcf8574.digitalWrite(PinoSwitchAudioS0, HIGH);
    pcf8574.digitalWrite(PinoSwitchAudioS1, HIGH);
    pcf8574.digitalWrite(PinoSwitchAudioS2, LOW);

  }

  if( Comando == "DebugRemotoOn" ) 
  {

    IsDebugRemoto = true;

  }

  if( Comando == "DebugRemotoOff" ) 
  {

    IsDebugRemoto = false;

  }
  
  delay(100);

  LCD_ShowMsg("Comando:", Comando, 5000);
  
}

void GeralTimer()
{
  
  os_timer_setfn(&tmr1, WifiCheck, NULL);
  os_timer_arm(&tmr1, 1000, true); 
  
  os_timer_setfn(&tmr2, MqttCheck, NULL);
  os_timer_arm(&tmr2, 1000, true); 

}

void GeralDebug(String Mensagem){

  Serial.println(Mensagem);
  
  if( IsDebugRemoto == true )
  {

    webSocket.sendTXT(WebSocket_Id, Mensagem);
    
  }

}

void GeralDebug(int Mensagem){

  Serial.println(Mensagem);
  
  if( IsDebugRemoto == true )
  {

    //webSocket.sendTXT(WebSocket_Id, String(Mensagem));
    
  }

}

void CtrlTimer(){

  TimerCtrl1.run();

}

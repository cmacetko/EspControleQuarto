void LcdIniciar(){

  GeralDebug("LCD Iniciado");
  
  lcd.begin(16,2);
  lcd.init();
  lcd.noBlink();
  
  os_timer_setfn(&tmr0, LCD_HideMsg, NULL);
  
}

void LCD_ShowMsg(String Msg1, String Msg2, int Tempo){

  lcd.clear();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print(Msg1);

  lcd.setCursor(0, 1);
  lcd.print(Msg2);

  os_timer_arm(&tmr0, Tempo, false); 
  
}

void LCD_HideMsg(void*z){

  lcd.clear();
  lcd.noBacklight();

}

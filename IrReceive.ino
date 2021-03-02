void IrReceive_Iniciar()
{

  if( IrReceiveIs == true )
  {

    irrecv.enableIRIn();
    
  }

}

void IrReceive_dump(decode_results *results) 
{

  uint16_t count = results->rawlen;
  
  if (results->decode_type == UNKNOWN) {
  Serial.print("Unknown encoding: ");
  } else if (results->decode_type == NEC) {
  Serial.print("Decoded NEC: ");
  } else if (results->decode_type == SONY) {
  Serial.print("Decoded SONY: ");
  } else if (results->decode_type == RC5) {
  Serial.print("Decoded RC5: ");
  } else if (results->decode_type == RC5X) {
  Serial.print("Decoded RC5X: ");
  } else if (results->decode_type == RC6) {
  Serial.print("Decoded RC6: ");
  } else if (results->decode_type == RCMM) {
  Serial.print("Decoded RCMM: ");
  } else if (results->decode_type == PANASONIC) {
  Serial.print("Decoded PANASONIC - Address: ");
  Serial.print(results->address, HEX);
  Serial.print(" Value: ");
  } else if (results->decode_type == LG) {
  Serial.print("Decoded LG: ");
  } else if (results->decode_type == JVC) {
  Serial.print("Decoded JVC: ");
  } else if (results->decode_type == AIWA_RC_T501) {
  Serial.print("Decoded AIWA RC T501: ");
  } else if (results->decode_type == WHYNTER) {
  Serial.print("Decoded Whynter: ");
  }
  
  serialPrintUint64(results->value, 16);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");
  
  for (uint16_t i = 1; i < count; i++) {
  if (i % 100 == 0)
  yield(); 
  if (i & 1) {
  Serial.print(results->rawbuf[i] * RAWTICK, DEC);
  } else {
  Serial.write('-');
  Serial.print((uint32_t) results->rawbuf[i] * RAWTICK, DEC);
  }
  Serial.print(" ");
  }
  Serial.println();

}

void IrReceive_Loop(){
  
  if( IrReceiveIs == true )
  {

    if(irrecv.decode(&results)) 
    {
    
      serialPrintUint64(results.value, 16);
      IrReceive_dump(&results);
      
      irrecv.resume(); 
      
    }
    
  }

}

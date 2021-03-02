void SPIFFS_Iniciar(){

  if(!SPIFFS.begin())
  {
  
    GeralDebug("SPIFFS Mount failed");
  
  }else{
  
    GeralDebug("SPIFFS Mount succesfull");
    
  }

}

bool SPIFFS_HttpServer_handleFileRead(String path)
{

  if(path.endsWith("/")) 
  {
    
    path += "index.html";
    
  }

  String contentType = SPIFFS_getContentType(path); 
  String pathWithGz = path + ".gz";

  if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path))
  {
  
    if(SPIFFS.exists(pathWithGz))
    {
    
      path += ".gz";
    
    }
    
    File file = SPIFFS.open(path, "r");
    size_t sent = httpserver.streamFile(file, contentType);
    file.close();
    
    return true;
  
  }
  
  return false;      

}

String SPIFFS_getContentType(String filename){
  
  if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  
  return "text/plain";
  
}

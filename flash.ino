
#include <FS.h>     //File System [ https://github.com/espressif/arduino-esp32/tree/master/libraries/FS ]
#include <SPIFFS.h> //SPI Flash File System [ https://github.com/espressif/arduino-esp32/tree/master/libraries/SPIFFS ]


void setup() {
  
  int t = 5000;
  Serial.begin(115200);
  delay(1000);
  Serial.println("SPIFFS - SPI Flash File System"); 
  delay(t);

  Serial.println("\nEscreve novo arquivo");
  writeFile("ESP 32 SPIFFS", "/Arquivo01.txt", false);
  delay(t);

  Serial.println("\nVisualiza o conteudo do Arquivo01.txt");
  readFile("/Arquivo01.txt");
  delay(t);

  Serial.println("Apaga o arquivo Arquivo01.txt");
  deleteFile("/Arquivo01.txt");
  delay(t);

  Serial.println("\nVisualiza o conteudo do Arquivo01.txt");
  readFile("/Arquivo01.txt");
  delay(t);

}

void loop() {
}

/*--- ESCREVE O ARQUIVO ---*/
bool writeFile(String values, String pathFile, bool anexar) {
  char *mode = "w"; //open for writing (creates file if it doesn't exist). Deletes content and overwrites the file.
  if (anexar) mode = "a"; //open for appending (creates file if it doesn't exist)
  Serial.println("- Escrevendo na memoria: " + pathFile);
  Serial.println("- Conteudo: " + values);
  SPIFFS.begin(true);
  File wFile = SPIFFS.open(pathFile, mode);
  if (!wFile) {
    Serial.println("- Falha ao escrever o arquivo.");
    return false;
  } else {
    wFile.println(values);
    Serial.println("- Arquivo escrito!");
  }
  wFile.close();
  return true;
}

/*--- LEITURA DO ARQUIVO ---*/
String readFile(String pathFile) {
  Serial.println("- Lendo arquivo: " + pathFile);
  SPIFFS.begin(true);
  File rFile = SPIFFS.open(pathFile, "r");
  String values;
  if (!rFile) {
    Serial.println("- Falha para abrir o arquivo.");
  } else {
    while (rFile.available()) {
      values += rFile.readString();
    }
    Serial.println("- Valor do arquivo: " + values);
  }
  rFile.close();
  return values;
}

/*--- APAGA O ARQUIVO ---*/
bool deleteFile(String pathFile) {
  Serial.println("- Deletando arquivo: " + pathFile);
  SPIFFS.begin(true);
  if (!SPIFFS.remove(pathFile)) {
    Serial.println("- Delete falhou.");
    return false;
  } else {
    Serial.println("- Arquivo deletado!");
    return true;
  }
}



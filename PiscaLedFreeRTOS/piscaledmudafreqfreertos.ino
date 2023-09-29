TaskHandle_t lerbotao; //criando tarefa 1
TaskHandle_t ligaled; //criando tarefa 2


int frequencia=0;
int estadobotao=0;
void setup() {
  Serial.begin(115200);
  pinMode(33,OUTPUT); // led
  pinMode(26,INPUT); //botao

  // xTaskCreatePinnedToCore(nome da funçao, "nome da tarefa", tamanho da pilha, NULL (irá receber parametros ?), (prioridade de execução 0 menor), alteração manual, (nucleo que ira executar)); 
  xTaskCreatePinnedToCore(piscaled, "ligaled", 10000, NULL, 0, &ligaled, 0); 
  xTaskCreatePinnedToCore(botao, "lerbotao", 10000, NULL, 1, &lerbotao, 1);
}

void loop() {

}

void botao(void *pvParameters)
{
    for(;;) // loop infinito para o whatchdog não reiniciar o esp
  {
    estadobotao= digitalRead(26);
    if(estadobotao == HIGH)
    {
      frequencia= frequencia + 100;
      if (frequencia>1000){
        frequencia= 0;
        Serial.println("LED DESLIGADO");
      } else
      {
        Serial.print("Frequencia: ");
        Serial.print(frequencia);
        Serial.println(" milisegundos");
      }
    } 
    delay(300);
  } 
}

void piscaled(void *pvParameters)
{
  for(;;) // loop infinito para o whatchdog não reiniciar o esp
  {
    if(frequencia>0)
    {
      digitalWrite(33,HIGH);
      delay(frequencia);
      digitalWrite(33,LOW);
      delay(frequencia);
    } else
    {
      digitalWrite(33,LOW);
    }
  } 
}
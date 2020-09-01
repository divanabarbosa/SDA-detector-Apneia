//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>
#include <VirtualWire.h>
 
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 7, 4, 3, 2);

byte message[VW_MAX_MESSAGE_LEN];    // Armazena as mensagens recebidas
byte msgLength = VW_MAX_MESSAGE_LEN;

#define LEDOP 8
#define botao 6
#define LEDALARME 30

int var=0;       // valor instantaneo enviado pelo botão
int var2=0;     // valor guardado
int estado=0;  // guarda o valor 0 ou 1 (HIGH ou LOW)
#define BUZZER 26
 
void setup()
{
  //Define o número de colunas e linhas do LCD
  lcd.begin(20, 4);
  Serial.begin(9600);
  pinMode(LEDOP,OUTPUT);
  pinMode(botao,INPUT);
  pinMode(BUZZER,OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(LEDALARME,OUTPUT);

  Serial.begin(9600);

  vw_set_rx_pin(5); // Define o pino 5 do Arduino como entrada 
  //de dados do receptor
  vw_setup(2000);             // Bits por segundo
  vw_rx_start();              // Inicializa o receptor

  
  lcd.clear(); 
  lcd.setCursor(7,0);
  lcd.print("Sistema");
  lcd.setCursor(6,1);
  lcd.print("Detector");
  lcd.setCursor(7,2);
  lcd.print("de");
  lcd.setCursor(7,3);
  lcd.print("Apneia");
  delay(3000);
  
  
//Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(3, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("AC 326");
  lcd.setCursor(3, 1);
  lcd.print(" Equipe Apneia");
  delay(5000);
   
  //Rolagem para a esquerda
  for (int posicao = 0; posicao < 3; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
  }
   
  //Rolagem para a direita
  for (int posicao = 0; posicao < 6; posicao++)
  {
    lcd.scrollDisplayRight();
    delay(300);
  }
  lcd.clear(); 
lcd.setCursor(4,0);
lcd.print("Iniciando ...");
for(int l = 1; l <= 19; l++){
  
  lcd.setCursor(l,2);
  lcd.print("-");
  delay(100);
  if(l == 3 | l == 6 | l == 7 ){
    delay(900);
    }
  }
  delay(2000);
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Iniciado !");
  delay(2000);
  
}

int x =0;

void loop()
{
 
  uint8_t message[VW_MAX_MESSAGE_LEN];    
  uint8_t msgLength = VW_MAX_MESSAGE_LEN;
  
  /*var=digitalRead(botao); // ler o valor enviado pelo botão: "HIGH" ou "LOW"
  if ((var == HIGH) && (var2 == LOW)) {
    estado = 1 - estado;
    delay(20); // de-bouncing
  }
  var2=var;
  if (estado == 1) {*/
    digitalWrite(LEDOP, HIGH);
    
 /* } else {
  *  
    digitalWrite(LEDOP, LOW);  // desliga o led
  }*/


  if (vw_get_message(message, &msgLength)) // Non-blocking
    {
      lcd.clear(); 
      
        lcd.print("Expirando... ");
        delay(300);
        x++;
       
        while(x>=20){
             digitalWrite(BUZZER,HIGH);
             digitalWrite(LEDALARME,HIGH); 
           lcd.setCursor(0,1);
             lcd.print("Apneia detectada");
             delay(300);      
              if (!(vw_get_message(message, &msgLength))){
                     digitalWrite(BUZZER,LOW); 
                     digitalWrite(LEDALARME,LOW);
                     x=0;
                }  
          }

       
          
    }
    else{

      uint8_t message[VW_MAX_MESSAGE_LEN];    
  uint8_t msgLength = VW_MAX_MESSAGE_LEN;
      lcd.setCursor(0,0);
      lcd.print("Inspirando....");
      delay(300);
       x++;
       
        while(x>=20){
             digitalWrite(BUZZER,HIGH);
             digitalWrite(LEDALARME,HIGH); 
             lcd.setCursor(0,1);
             lcd.print("Apneia detectada");
             delay(300);      
              if ((vw_get_message(message, &msgLength))){
                     digitalWrite(BUZZER,LOW); 
                     digitalWrite(LEDALARME,LOW);
                     x=0;
                }  
          }
      
    }

   analogWrite(A0, 0);

  analogWrite(A1, 600);
    float x = analogRead(5);
  delay(300);

  analogWrite(A0, 600);
  analogWrite(A1, 0);
  delay(300);
     float y = analogRead(5);
    if(x >= 70 || y >= 70){
      lcd.setCursor(0,2);
      lcd.print(0);
      lcd.setCursor(0,3);
      lcd.print("Coloque o indicador");
    }
 else {
      float test = ((y/x)*100);
    if(test > 100){
    lcd.setCursor(0,2); 
    lcd.print("Saturacao sanguinea: 100%"); 
    lcd.clear();
    }
    else{
     lcd.setCursor(0,2);
     lcd.print("Saturacao sanguinea: ");
     lcd.setCursor(0,3);
     lcd.print((y/x)*100);
     lcd.setCursor(6,3);
     lcd.print(" %");
    }
}
}

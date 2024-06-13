// C++ code
//
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd_1(0);

//VARIAVEIS 
  float num1, num2;
  char operador;
  float Resultado;

//SETUP
void setup()
{
   //FAZENDO CONTATO COM O MONITOE SERIAL
   Serial.begin(9600);
   // DIZ O TANTO DE CARACTERES E LINHAS DO LCD (COLUNA E LINHA)
   lcd_1.begin(16, 2);
  
  
}
// LOOP
void loop(){
  //PEDE PARA DIGITAR O PRIMEIRO NUMERO NO MONITOR SERIAL 
  Serial.println("Digite o primeiro numero: ");
  // UM LACO DE REPETICAO QUE VALIDA A FUNCAO (!Serial.available())
  //ESTA FUNÇÃO RETORNA O NÚMERO DE BYTES DISPONÍVEIS PARA LEITURA NA PORTA SERIAL. SE NÃO HOUVER NENHUM DADO DISPONÍVEL, ELA RETORNA 0.
  while (!Serial.available()) ;
  // A VARIAVEL NUM1 SERA IGUAL O FUNCAO (Serial.parseFloat();) QUE ESTA FUNÇÃO RETORNA O NÚMERO DE BYTES DISPONÍVEIS PARA LEITURA NA PORTA SERIAL. SE NÃO HOUVER NENHUM DADO DISPONÍVEL, ELA RETORNA 0.
  num1 = Serial.parseFloat();

  //PEDE PARA DIGITAR O SEGUNDO NUMERO E PEDE AS MESMAS FUNCOES DO PRIMEIRO NUMERO
  Serial.println("Digite o segundo numero: ");
  while (!Serial.available()) ;
  num2 = Serial.parseFloat();

  //PEDE PARA DIGITAR UM OPERADOR PARA OS NUMEROS 
  Serial.println("Digite o operador (+, -, *, /): ");
  while (!Serial.available()) ;
 


  // UM SWITCH CASE PARA CASE OERADOR E SE DIGITAR ALGO N CONCEBIVEL ELE MOSTRARA INVALIDO
  switch (operador) {
    case '+':
      Resultado = num1 + num2;
      break;
    case '-':
      Resultado = num1 - num2;
      break;
    case '*':
      Resultado = num1 * num2;
      break;
    case '/':
      if (num2 == 0) {
        Serial.println("Erro: divisão por zero!");
        return;
      }
      Resultado = num1 / num2;
      break;
    default:
      Serial.println("Operador inválido!");
      return;
  }
  
  
  
  //MOSTRA O RESULTADO NO MONITOR SERIAL 
  Serial.println(Resultado);
  // MOSTRA O RESULTADO NO LCD
  lcd_1.print(Resultado);
   delay(500);  
  lcd_1.setCursor(1,1);// MOSTTA AONDE DEVERA APARECER ALGO NO LCD (PRIMEIRA CASA DA PRIMEIRA COLUNA)
   delay(500); 
 
}
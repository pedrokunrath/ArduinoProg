#include <Adafruit_LiquidCrystal.h> // Inclui a biblioteca para o controle de um display LCD usando o I2C da Adafruit

Adafruit_LiquidCrystal lcd_1(0); // Criação do objeto lcd_1 para controle do display LCD no endereço I2C 0

// Variáveis 
int num1, num2; // Variáveis para armazenar os dois números da operação
int a, b, c; // Variáveis auxiliares para leitura dos dígitos do primeiro número
char operador; // Variável para armazenar o operador da operação (+, -, *, /)
int Resultado; // Variável para armazenar o resultado da operação

// Função de configuração inicial
void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial a 9600 bps
  lcd_1.begin(16, 2); // Inicializa o display LCD com 16 colunas e 2 linhas
}

// Função para pedir e ler os números da operação
int Pedeonumero() {
  int num;
  while (!Serial.available()); // Espera até que haja dados disponíveis na serial
  a = Serial.read() - 48; // Lê o primeiro dígito do primeiro número
  while (!Serial.available());
  b = Serial.read() - 48; // Lê o segundo dígito do primeiro número
  while (!Serial.available());
  c = Serial.read() - 48; // Lê o terceiro dígito do primeiro número

  num = a * 100 + b * 10 + c; // Calcula o primeiro número a partir dos dígitos lidos unidade,dezena,centena
  return num;
}

// Função para pedir e ler o operador da operação
void PedeOperador() {
  Serial.println("Digite o operador (+, -, *, /): "); // Solicita o operador ao usuário
  while (!Serial.available()); // Espera até que haja dados disponíveis na serial
  operador = Serial.read(); // Lê o operador
}

// Função principal que executa repetidamente
void loop() {
  // Solicita e lê os números
  Serial.println("Digite um numero inteiro de 3 digitos da primeira operacao: ");
  num1 = Pedeonumero();
  Serial.println("Digite um numero inteiro de 3 digitos da segunda operacao: ");
  num2 = Pedeonumero();

  // Solicita e lê o operador
  PedeOperador();

  // Realiza a operação com base no operador
  switch (operador) {
    case '+':
      Resultado = num1 + num2; // Realiza a adição
      break;
    case '-':
      Resultado = num1 - num2; // Realiza a subtração
      break;
    case '*':
      Resultado = num1 * num2; // Realiza a multiplicação
      break;
    case '/':
      if (num2 == 0) { // Verifica divisão por zero
        Serial.println("Erro: divisão por zero!"); // Exibe mensagem de erro na serial
        return;
      }
      Resultado = num1 / num2; // Realiza a divisão
      break;
    default:
      Serial.println("Operador inválido!"); // Exibe mensagem de operador inválido na serial
      return;
  }

  // Exibe o resultado na serial
  Serial.print("Resultado: ");
  Serial.println(Resultado);

  // Exibe a operação e o resultado no display LCD
  lcd_1.clear(); // Limpa o display
  lcd_1.setCursor(0, 0); // Move o cursor para a posição inicial do LCD
  lcd_1.print(String(num1) + String(operador) + String(num2) + "=" + String(Resultado));
  delay(2000); // Aguarda 2 segundos
}


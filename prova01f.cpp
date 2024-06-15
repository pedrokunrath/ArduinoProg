#include <Adafruit_LiquidCrystal.h> // Inclui a biblioteca para o controle de um display LCD usando o I2C da Adafruit

Adafruit_LiquidCrystal lcd_1(0); // Criação do objeto lcd_1 para controle do display LCD no endereço I2C 0

// Variáveis globais
int num1, num2; // Variáveis para armazenar os dois números da operação
int a, b, c; // Variáveis auxiliares para leitura dos dígitos do primeiro número
int a2, b2, c2; // Variáveis auxiliares para leitura dos dígitos do segundo número
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
  while (!Serial.available);
  b = Serial.read() - 48; // Lê o segundo dígito do primeiro número
  while (!Serial.available);
  c = Serial.read() - 48; // Lê o terceiro dígito do primeiro número
  Serial.println("Digite um numero inteiro de 3 digitos da segunda operacao:: "); // Solicita o segundo número ao usuário
  num = a * 100 + b * 10 + c; // Calcula o primeiro número a partir dos dígitos lidos
  return num;
}

void pedeNumero() {
  Serial.println("Digite um numero inteiro de 3 digitos da primeira operacao: "); // Solicita o primeiro número ao usuário
  num1 = Pedeonumero();
  Serial.println("Digite um numero inteiro de 3 digitos da segunda operacao:: "); // Solicita o segundo número ao usuário
  num2 = Pedeonumero();
}

// Função para pedir e ler o operador da operação
void PedeOperador() {
  Serial.println("Digite o operador (+, -, *, /): "); // Solicita o operador ao usuário
  while (!Serial.available()); // Espera até que haja dados disponíveis na serial
  operador = Serial.read(); // Lê o operador

  // Switch case para realizar a operação com base no operador
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
}

// Função principal que executa repetidamente
void loop() {
  pedeNumero(); // Chama a função para pedir os números
  PedeOperador(); // Chama a função para pedir o operador
  Serial.println(Resultado); // Exibe o resultado na serial

  // Exibe a operação e o resultado no display LCD
  lcd_1.print(String(num1) + String(operador) + String(num2) + "=" + String(Resultado));
  delay(500); // Aguarda 500 milissegundos
  lcd_1.setCursor(1, 1); // Move o cursor para a posição 1,1 do LCD

  delay(500); // Aguarda mais 500 milissegundos
}
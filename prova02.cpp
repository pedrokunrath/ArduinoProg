#include <Adafruit_LiquidCrystal.h> // Inclui a biblioteca para o controle de um display LCD usando o I2C da Adafruit

int cmX, cmY = 0; // Declaração de variáveis inteiras para armazenar as distâncias medidas nos eixos X e Y
int a, b, c = 0; // Declaração de variáveis auxiliares para a leitura dos dígitos da posição X
int a1, b1, c1 = 0; // Declaração de variáveis auxiliares para a leitura dos dígitos da posição Y
int X, Y = 0; // Declaração de variáveis inteiras para armazenar as coordenadas X e Y digitadas pelo usuário
int SensorX = 7; // Pinagem para o sensor de distância no eixo X
int SensorY = 6; // Pinagem para o sensor de distância no eixo Y


Adafruit_LiquidCrystal lcd_1(0); // Criação do objeto lcd_1 para controle do display LCD no endereço I2C 0

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial a 9600 bps
  lcd_1.begin(16, 2); // Inicializa o display LCD com 16 colunas e 2 linhas
}

void SolicitaXY() {
  Serial.println("Digite a posicao X da batalha: "); // Solicita ao usuário a coordenada X
  while (!Serial.available()); // Espera até que haja dados disponíveis na serial
  a = Serial.read() - 48; // Lê o primeiro dígito da coordenada X
  while (!Serial.available());
  b = Serial.read() - 48; // Lê o segundo dígito da coordenada X

  while (!Serial.available());
  c = Serial.read() - 48; // Lê o terceiro dígito da coordenada X

  Serial.println("Digite a posicao Y da batalha: "); // Solicita ao usuário a coordenada Y
  while (!Serial.available());
  a1 = Serial.read() - 48; // Lê o primeiro dígito da coordenada Y
  while (!Serial.available());
  b1 = Serial.read() - 48; // Lê o segundo dígito da coordenada Y
  while (!Serial.available());
  c1 = Serial.read() - 48; // Lê o terceiro dígito da coordenada Y

  X = a * 100 + b * 10 + c; // Calcula a posição X a partir dos dígitos lidos
  Y = a1 * 100 + b1 * 10 + c1; // Calcula a posição Y a partir dos dígitos lidos
}

void RecebeValor() {
  cmX = retornaDistancia(SensorX, SensorX); // Mede a distância no eixo X
  cmY = retornaDistancia(SensorY, SensorY); // Mede a distância no eixo Y

  if (X == cmX && Y == cmY) { // Verifica se as coordenadas digitadas coincidem com as medidas
    lcd_1.print("ACERTOU!"); // Exibe mensagem de acerto no LCD
    Serial.println("ACERTOU, VALOR X = " + String(cmX) + " E O VALOR Y = " + String(cmY)); // Exibe mensagem de acerto na serial
  } else {
    lcd_1.print("ERROU"); // Exibe mensagem de erro no LCD
    Serial.println("ERROU, VALOR DO X ERA = " + String(cmX) + " E O VALOR Y ERA = " + String(cmY)); // Exibe mensagem de erro na serial
  }
}

long retornaDistancia(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT); // Define o pino trigger como saída
  digitalWrite(triggerPin, LOW); // Garante que o trigger está em nível baixo
  delayMicroseconds(2); // Aguarda 2 microssegundos
  digitalWrite(triggerPin, HIGH); // Ativa o trigger
  delayMicroseconds(10); // Mantém o trigger ativo por 10 microssegundos
  digitalWrite(triggerPin, LOW); // Desativa o trigger
  pinMode(echoPin, INPUT); // Define o pino echo como entrada
  return 0.01723 * pulseIn(echoPin, HIGH); // Calcula a distância com base no tempo do pulso recebido no echo
}

void loop() {
  SolicitaXY(); // Solicita as coordenadas X e Y ao usuário
  RecebeValor(); // Verifica se as coordenadas fornecidas coincidem com as medidas
  Serial.println("Aguarde 3 segundos para jogar novamente!"); // Informa o usuário sobre o tempo de espera
  delay(3000); // Aguarda 3 segundos antes de reiniciar o loop
  lcd_1.clear(); // Limpa o display LCD
}

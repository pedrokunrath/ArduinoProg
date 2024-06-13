void loop() {
  float num1, num2;
  char operador;
  float resultado;
  
  Serial.print("Digite o primeiro número: ");
  while (!Serial.available()) ;
  num1 = Serial.parseFloat();

  
  Serial.print("Digite o segundo número: ");
  while (!Serial.available()) ;
  num2 = Serial.parseFloat();


  Serial.print("Digite o operador (+, -, *, /): ");
  while (!Serial.available()) ;
  operador = Serial.read();


  
  switch (operador) {
    case '+':
      resultado = num1 + num2;
      break;
    case '-':
      resultado = num1 - num2;
      break;
    case '*':
      resultado = num1 * num2;
      break;
    case '/':
      if (num2 == 0) {
        Serial.println("Erro: divisão por zero!");
        return;
      }
      resultado = num1 / num2;
      break;
    default:
      Serial.println("Operador inválido!");
      return;
  }

 
  lcd.setCursor(0, 0);
  lcd.print("Resultado: ");
  lcd.print(resultado);
}
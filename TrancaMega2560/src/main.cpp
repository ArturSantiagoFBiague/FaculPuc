#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
 
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const byte ROWS = 4; 
const byte COLS = 3; 
byte rowPins[ROWS] = {51, 41, 43, 47}; //linhas = { pin2, pin7, pin6, pin4} Pinos do Keypad
byte colPins[COLS] = {49, 53, 45};     //colunas = { pin3, pin1, pin5}      Pinos do keypad

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

// Crie a instância do teclado
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String senhaCorreta = "1234";
String senhaDigitada = ""; 
String senhaShow     = "";


 
void setup()
{
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  lcd.print("Digite a senha:");
}
 
void loop(){
  char key = keypad.getKey();
  
  if (key) {
    if (key == '#') { // Verifica se a tecla '#' foi pressionada para confirmar a senha
      if (senhaDigitada == senhaCorreta) {
        lcd.clear();
        lcd.print("Senha correta");
      } else {
        lcd.clear();
        lcd.print("Senha incorreta");
      }
      delay(2000); // Aguarda 2 segundos
      lcd.clear();
      lcd.print("Digite a senha:");
      senhaDigitada = ""; // Reseta a senha digitada
      senhaShow     = "";
    } else if (key == '*') { // Verifica se a tecla '*' foi pressionada para apagar
      if (senhaDigitada.length() > 0) {
        senhaDigitada.remove(senhaDigitada.length() - 1);
        senhaShow.remove(senhaShow.length() - 1); // Remove o último caractere
        lcd.setCursor(0, 1);
        lcd.print(senhaShow);
        lcd.print(" "); // Apaga o último caractere no LCD
      }
    } else { // Adiciona o dígito pressionado à senha
      senhaDigitada += key;
      senhaShow     += '*';
      lcd.setCursor(0, 1);
      lcd.print(senhaShow);
    }
  }
}
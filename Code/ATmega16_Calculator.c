/*
 * ATmega16_Calculator.c
 *
 * Created: 5/29/2024 2:04:44 PM
 * Author: Peyman Roohi-Moghadam
 */

#include <mega16.h>
#include <delay.h>
#include <alcd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

unsigned char typeBuffer[16] = "0";
unsigned int typeIndex = 0;
bool notTyped = true;
unsigned char promptStr[16] = "";
char operator = '';
float operand1=0, operand2=0, result=0;
bool operand1IsNULL = true;
bool hasDot = false;
int temp = 0;

void trimDecimals(char* str) { // for not shoing unne
    for(temp = 15; temp>=0; temp--) {
        if (str[temp] == '\0') continue;
        else if (str[temp] == '0') str[temp] = '\0';
        else if (str[temp] == '.') {
            str[temp] = '\0';
            break;
        } else break;
    }
}

void clearTypeBuffer() {
    typeBuffer[0] = '0';
    for(temp=1;temp<16;temp++) { 
        typeBuffer[temp] = '\0';
    }
    typeIndex = 0;
}

void clearPromptLine() {
    lcd_gotoxy(0,0);
    for(temp=0;temp<16;temp++) { 
        lcd_puts(" ");
    }
}

void clearTypeLine() {
    lcd_gotoxy(0,1);
    for(temp=0;temp<16;temp++) { 
        lcd_puts(" ");
    }
    notTyped = true;
    hasDot = false;
    clearTypeBuffer();
}

void showPrompt() {
    clearPromptLine();
    lcd_gotoxy(0,0);
    if(operator == 'r') lcd_putsf("sqrt{");
    ftoa(operand1, 3, promptStr); 
    //delay_ms(5); //if it doesn't trim ;)
    trimDecimals(promptStr);
    lcd_puts(promptStr);
    if(operator){
        if(operator == 'r') lcd_putsf("}");
        else lcd_putchar(operator);
    }
}

void calculate(){
    // Complete Prompt
    if (operator && operator != 'r' && operator != '%'){
        ftoa(operand2, 3, promptStr);
        trimDecimals(promptStr);  
        //delay_ms(5); //if it doesn't trim ;)
        lcd_puts(promptStr);
    } 
    lcd_putsf("=");

    switch(operator){
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            result = operand1 / operand2;
            break;
        case '^': 
            result = pow(operand1, operand2);
            break;
        case 'r':
            result = sqrt(operand1);
            break;
        case '%':
            result = operand1 / 100;
            break;
        default:
            result = operand1;
            break;
    }
    clearTypeLine();
    lcd_gotoxy(0,1);
    ftoa(result, 3, typeBuffer);
    trimDecimals(typeBuffer);
    lcd_puts(typeBuffer);
    operand1 = NULL;
    operand1IsNULL = true;
}

void nonDigitKeyPress(char nonDigitkey) {
    if (operand1IsNULL) {  // operand 1 is not set
        operand1 = atof(typeBuffer);
        operand1IsNULL = false;
        operator = (nonDigitkey == '=') ? operator : nonDigitkey;
        showPrompt();
        if(nonDigitkey == '=' || nonDigitkey == 'r' || nonDigitkey == '%'){
            calculate();
        } else {  // no calculation, just set operand 1
            clearTypeLine();
            lcd_gotoxy(0,1);
            ftoa(operand1, 3, typeBuffer);
            trimDecimals(typeBuffer);
            lcd_puts(typeBuffer);
        }
    } else {  // operand 1 is set
        operand2 = atof(typeBuffer);
        if(nonDigitkey == '=') {  // calculation must be done
            showPrompt();
            calculate();
        } else {
            if (notTyped) {
                operator = nonDigitkey;
                showPrompt();
            } else {
                calculate();
                nonDigitKeyPress(nonDigitkey);
            }
        }    
    }
}

void main(void)
{
char key;
int row = 0;
int col = 0;
unsigned char keys[4][6] = {   // power(^) instead of +/- of calculator
    {'c', '7', '8', '9', '*', '/'},
    {'^', '4', '5', '6', '-', 'R'},
    {'%', '1', '2', '3', '+', 'M'},
    {'r', '0', '.', '=', '+', 'm'}
};
DDRB |= 0x0F;
DDRC &= 0xC0;
lcd_init(16);

lcd_gotoxy(0,0);
lcd_putsf("Made with <3");
delay_ms(1500);
clearPromptLine();

lcd_gotoxy(0,1);
lcd_puts(typeBuffer);

while (1)
    {   
      // Cheking for key press
      for(row=0; row<4; row++){
        PORTB = 0x0F;
        PORTB &= ~(1<<row); 
        for(col=0; col<6; col++){ 
           if(!(PINC&(1<<col))) break;
        }
        delay_ms(15);
        if (col<6) break;
      } 
      if(row==4) continue;  
      key = keys[row][col];
      
      switch(key) {
        case 'c':
            if (operand1IsNULL) clearPromptLine();
            clearTypeLine();
            lcd_gotoxy(0,1);
            lcd_puts(typeBuffer);
            break;
        case '=':
        case '^':
        case '%':
        case 'r':
        case '*':
        case '/':
        case '-':
        case '+':
            nonDigitKeyPress(key);
            break;
            
        // TODO          
        case 'R':
        case 'M':
        case 'm':
            break;
            
        default: // Key is a digit
            if(notTyped){
                if (operand1IsNULL) clearPromptLine();
                clearTypeLine();
                notTyped = false;
            }
            if (key == '.'){
                if(typeIndex==0) typeIndex++;
                else if (hasDot) break;
                hasDot = true;
            }
            typeBuffer[typeIndex] = key;
            typeIndex = (typeIndex==0 && key=='0') ? typeIndex : typeIndex+1;
            lcd_gotoxy(0,1);
            lcd_puts(typeBuffer);
      }
      delay_ms(200);
    }
}
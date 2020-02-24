/*
 * File:   Master_Lab_5.c
 * Author: Hector
 *
 * Created on 19 de febrero de 2020, 03:19 PM
 */
//******************************************************************************
// Palabra de Configuración
//******************************************************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

//******************************************************************************
// Definición de librerías
//******************************************************************************
#define _XTAL_FREQ 8000000 //Se define la frecuencia del oscilador para el delay

#include <xc.h>
#include <stdint.h>
#include "LCD.h"
#include "I2C.h"
#include "Oscilador.h"

//******************************************************************************
// Funciones prototipo
//******************************************************************************
void init(void);
uint8_t Val_STR(uint8_t num);
//******************************************************************************
//Void Principal
//******************************************************************************
void main(void) {
    initOsc(7); // Se usa un reloj interno de 8 MHz
    init(); //Se inicializan los puertos
    lcd_init(); //Se inicializa la LCD
    
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0; //Se inicializan todas los puertos en 0
    
    LCD_POINT(1,2);
    lcd_msg("S1"); //Se envía el string S1 para indicar que los datos mostrados son del POT1
    LCD_POINT(1,7);
    lcd_msg("S2"); //Se envía el string S2 para indicar que los datos mostrados son del POT2
    LCD_POINT(1,12);
    lcd_msg("S3"); //Se envía el string S3 para indicar que los datos mostrados son del Contador
    
    LCD_POINT(2,1);
    lcd_dwr('.'); //Se envía el caracter .
    LCD_POINT(2,4);
    lcd_dwr('V'); //Se envía el caracter V  
    
    LCD_POINT(2,11);
    lcd_dwr('.'); //Se envía el caracter .
    LCD_POINT(2,14);
    lcd_dwr('V'); //Se envía el caracter V 
    return;
}
//******************************************************************************
//Función de Inicialización de Puertos
//******************************************************************************
void init(void){
    TRISA = 0;                      // PORTA configurado como entrada en RA0
    TRISB = 0;                      // PORTB configurado como salida
    TRISC = 0;                      // PORTC configurado como salida
    TRISD = 0;                      // PORTD configurado como salida
    ANSEL = 0;                      // Pines connfigurados A0 y A3 como entradas analógicas
    ANSELH = 0;                     //Pines configurados como digitales 
    I2C_Master_Init(100000);        // Inicializar Comuncación I2C
    /*INTCON = 0b11100000;                //Habilita GIE, PEIE y T0IE 
    PIR1bits.SSPIF = 0;                 // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;                 // Habilitamos interrupción MSSP*/
}

//********************************************************************************************************
//Función de relación entre número y caractér correspondiente para ser enviado a la LCD
//********************************************************************************************************

uint8_t Val_STR(uint8_t num){ 
    switch(num){
        case 0: //Si el valor es cero, devuelva '0' para psoteriormente enviarlo a la LCD
            return '0';
            
        case 1: //Si el valor es uno, devuelva '1' para psoteriormente enviarlo a la LCD
            return '1';
            
        case 2: //Si el valor es dos, devuelva '2' para psoteriormente enviarlo a la LCD
            return '2';
            
        case 3: //Si el valor es tres, devuelva '3' para psoteriormente enviarlo a la LCD
            return '3';
            
        case 4: //Si el valor es cuatro, devuelva '4' para psoteriormente enviarlo a la LCD
            return '4';
            
        case 5: //Si el valor es cinco, devuelva '5' para psoteriormente enviarlo a la LCD
            return '5';
            
        case 6: //Si el valor es seis, devuelva '6' para psoteriormente enviarlo a la LCD
            return '6';
            
        case 7: //Si el valor es siete, devuelva '7' para psoteriormente enviarlo a la LCD
            return '7';
            
        case 8: //Si el valor es ocho, devuelva '8' para psoteriormente enviarlo a la LCD
            return '8';
            
        case 9: //Si el valor es nueve, devuelva '9' para psoteriormente enviarlo a la LCD
            return '9';  
            
    }
}

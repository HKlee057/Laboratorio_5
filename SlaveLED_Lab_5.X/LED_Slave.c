/*
 * File:   LED_Slave.c
 * Author: Hector
 *
 * Created on 22 de febrero de 2020, 06:00 PM
 */

//******************************************************************************
//Palabra de Configuración
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
// Librerías
//******************************************************************************
#include <xc.h>
#include <stdint.h>
#include "Oscilador.h"
//******************************************************************************
//Definiciones Extra
//******************************************************************************
#define _XTAL_FREQ 8000000                  //Definición de frecuencia de oscilación
#define BUTTON_ADD PORTDbits.RD2           //Definición de bit en Puerto D con nombre coloquial
#define BUTTON_SUB PORTDbits.RD3           //Definición de bit en Puerto D con nombre coloquial

//******************************************************************************
//Variables
//******************************************************************************
unsigned char add_button=0;             //Variable para adición y protección contra rebote de botón
unsigned char sub_button=0;             //Variable para substracción y protección contra rebote de botón
signed char count=0;                    //Variable de conteo
//******************************************************************************
// Prototipos de Funciones y Declaración de Variables
//******************************************************************************
void init(void);
//******************************************************************************
//Void Principal
//******************************************************************************
void main(void) {
    initOsc(7);                         // Se usa un reloj interno de 8 MHz
    init();                             //Se inicializan los puertos
        
    PORTA = 0x00;                       //Inicialización de puertos
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00; 
    
    while (1){                     //Siempre estar revisando 
    //CRITERIOS DE SUMA
    if (BUTTON_ADD == 1){          //Revisar si el botón de suma es presionado
        add_button=1;              //Encender variable de control
    }
    if (add_button==1 && BUTTON_ADD==0){  //Si la variable de control está activa, y no se sigue presionando, realizar el siguiente proceso
        __delay_ms(10);         //Delay 
        count++;                //Aumentar variable de conteo 
        PORTB = count;          //Igual valor de contador a Puerto B
        add_button = 0;         //Apaga variable de control
        }
    if (count==16){             //Si el conteo es igual a 16 se realiza lo siguiente
        count = 0;              //Igualar conteo a 15, esto trunca el contador a 4 bits
        PORTB = count;          //Igual valor de contador a Puerto B
    }
    //CRITERIOS DE RESTA
    if (BUTTON_SUB == 1){          //Revisar si el botón de resta es presionado
        sub_button=1;              //Encender variable de control
    }
    if (sub_button==1 && BUTTON_SUB==0){  //Si la variable de control está activa, y no se sigue presionando, realizar el siguiente proceso
        __delay_ms(10);          //Delay 
        count--;                //Disminuye variable de conteo
        PORTB = count;          //Igual valor de contador a Puerto B
        sub_button = 0;         //Apaga variable de control
        }
    if (count==-1){             //Si el conteo es igual a -1 se realiza lo siguiente
        count = 15;             //Igualar conteo a 15, esto trunca el contador a 4 bits
        PORTB = count;          //Igual valor de contador a Puerto B
        }
    }
    return;
}

//******************************************************************************
//Función de Inicialización de Puertos
//******************************************************************************
void init(void){
    TRISA = 0;                       // PORTA configurado como salida
    TRISB = 0;                       // PORTB configurado como salida
    TRISC = 0;                       // PORTC configurado como salida
    TRISD = 0b00001100;              // PORTD configurado como entrada en los bits RD2 y RD3
    ANSEL = 0;                       // Pines connfigurados como entradas digitales
    ANSELH = 0;                      //Pines connfigurados como entradas digitales  
    //INTCON = 0b11100000;                      //Habilita GIE, PIE y T0IE 
}
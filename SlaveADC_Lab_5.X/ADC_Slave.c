/*
 * File:   ADC_Slave.c
 * Author: Hector
 *
 * Created on 22 de febrero de 2020, 10:34 PM
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
#include <stdio.h>

#include "Oscilador.h"
#include "ADC.h"
#include "I2C.h"
//******************************************************************************
// Funciones prototipo
//******************************************************************************
void init(void);
//******************************************************************************
// Variables
//******************************************************************************
uint8_t ADC_CH1_BIN = 0;
//******************************************************************************
//Void Principal
//******************************************************************************
void main(void) {
    initOsc(7);                         // Se usa un reloj interno de 8 MHz
    init();                             //Se inicializan los puertos
    initADC();                          //Se inicializa el ADC
    
    PORTA = 0;                         //Inicialización de puertos
    PORTB = 0;
    PORTC = 0;
    PORTD = 0; 
    
    while (1){
        __delay_ms(1);
        ADCON0bits.CHS0 = 0;       //Selección de canal AN0
        ADCON0bits.CHS1 = 0;
        ADCON0bits.CHS2 = 0;
        ADCON0bits.CHS3 = 0;
        ADCON0bits.ADON = 1;       //El ADC está habilitado
        
        PIR1bits.ADIF = 0;         //Verifica la finalización de conversión
        ADCON0bits.GO = 1;         //Inicia conversión
        ADC_CH1_BIN = ADRESH;      //Realiza conversión para leer normal
        PORTB = ADC_CH1_BIN;
        
        __delay_ms(5);            //Delay de precaución
    }
    return;
}
//******************************************************************************
//Función de Inicialización de Puertos
//******************************************************************************
void init(void){
    TRISA = 0b00000001;                 // PORTA configurado como entrada en RA0
    TRISB = 0;                          // PORTB configurado como salida
    TRISC = 0;                          // PORTC configurado como salida
    TRISD = 0;                          // PORTD configurado como salida
    ANSEL = 0b00000001;                 // Pines connfigurados A0 y A3 como entradas analógicas
    ANSELH = 0;                         //Pines configurados como digitales 
    /*INTCON = 0b11100000;                //Habilita GIE, PEIE y T0IE 
    PIR1bits.SSPIF = 0;                 // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;                 // Habilitamos interrupción MSSP*/
}

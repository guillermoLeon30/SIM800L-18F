#include <18f2550.h>	//Tipo de procesador
#include <string.h>

#use delay(clock=4000000)			//Frecuencia de trabajo

#fuses 	EC_IO			//Oscilador externo, RA6=E/S,PLL OFF (CONFIG1H)	
#fuses 	CPUDIV1			//Postcaler OSC/1, Frec. CPU=4MHz/1=4MHz (CONFIG1L)
						//Ciclo de instrucción = 1uS (1/(4000000/4))

#fuses PUT,NOBROWNOUT,NOWDT,NOPBADEN,NOLVP

#define LCD_DATA_PORT getenv("SFR:PORTB") 
#include <lcd.c> //No se usa fast_io en la puerta

//Habilita las funciones RS232, velocidad a 9600 baudios
#use rs232(Baud=9600,xmit=PIN_C6, rcv=PIN_C7)

#use fast_io (C)

short visualizar=0;
char c;
char dato[10];		//Variable para almacena el dato recibido
char cadena[10];
#int_rda			//Vector de interrupción al recibir por el UART
tratamiento()
{	
	gets(dato);	//Lee el dato recibido hasta el enter (10)
	printf(lcd_putc, "%s", dato);
	visualizar = 1;
	//enable_interrupts(INT_RDA);		//Activa interrupción en la recepción
	//enable_interrupts(global);		//Habilita interrupciones
}	

void main(){
	int cont=0;
	set_tris_c(0b10111111);	//RC7/Rx entrada, RC6/Tx salida	
	//setup_uart(uart_autodetect);	//Activa ciclo de auto detección de baudios
	lcd_init();
	enable_interrupts(INT_RDA);		//Activa interrupción en la recepción
	enable_interrupts(global);		//Habilita interrupciones
	while(1)
	{	
		//if(visualizar == 1){
		//	lcd_gotoxy(1,1);
		//	sprintf(dato, "%c", c);	//combierte caracter a string
		//	strcat(cadena, dato); //ambos string deben ser del mismo tamaño
		//	printf(lcd_putc, "%s", cadena);
		//	visualizar = 0;
		//}
	}
}
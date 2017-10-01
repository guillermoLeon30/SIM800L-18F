#include <18f2550.h>	//Tipo de procesador
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

void palabra(char *p, char c);
void mensajeSim800(unsigned char *numero,unsigned char *mensaje );

char dato1[1];			//Variable para almacena el dato recibido
char dato2[10];
char dato3[10];
char numero[10] = "423245243";
char mensaje[10] = "Hola";

#int_rda			//Vector de interrupción al recibir por el UART
tratamiento(){	
	//disable_interrupts(INT_RDA);
	//dato = getc();	//Lee el dato recibido
	palabra(dato1, '\r');
	//gets(dato1);
	lcd_putc('\f');
	printf(lcd_putc, "%s", dato1);
	
	//enable_interrupts(INT_RDA);		//Activa interrupción en la recepción
}	

void main(){
	set_tris_c(0b10111111);	//RC7/Rx entrada, RC6/Tx salida	
	//setup_uart(uart_autodetect);	//Activa ciclo de auto detección de baudios
	lcd_init();
	//enable_interrupts(INT_RDA);		//Activa interrupción en la recepción
	//enable_interrupts(global);		//Habilita interrupciones
	
	lcd_gotoxy(1,1);

	//mensajeSim800(numero, mensaje);

	char c;

	while(1)
	{	
		printf("AT\r");
		palabra(dato1, '\r');
		printf(lcd_putc, "%s", dato1);
	}
}

void mensajeSim800(unsigned char *numero, unsigned char *mensaje ){
	printf("AT\r");
	palabra(dato1, '\r');
	printf(lcd_putc, "%s", dato1);
	gets(dato1);
	printf(lcd_putc, "%s", dato1);
	delay_ms(1000);
	printf("AT+CMGF=1\r");
	delay_ms(1000);
	printf("AT+CMGS=\"%s\"", numero);
	printf("\r\n");
	delay_ms(1000);
	printf("%s", mensaje);
	putc(26);
	delay_ms(1000);
	printf("\r\n");
}

void palabra(char *p, char c){
	char dato = getc();
	int i = 0;

	while(dato != c){
		dato = getc();
	}
	dato = 0;
	while(dato != c){
		dato = getc();
		p[i] = dato;
		i++;
	}
}
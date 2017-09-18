#include <18f2550.h>
#device ADC=10						//Nº de bits del módulo ADC del PIC18F2550

/*Ajusta los valores de las palabras de configuración durante el ensamblado. Los bits no empleados
adquieren el valor por defecto.Estos y otros valores se pueden modificar según las necesidades */

#fuses 	EC_IO			//Oscilador externo, RA6=E/S,PLL OFF (CONFIG1H)	
#fuses 	CPUDIV1			//Postcaler OSC/1, Frec. CPU=4MHz/1=4MHz (CONFIG1L)
						//Ciclo de instrucción = 1uS (1/(4000000/4))
#fuses PUT,NOBROWNOUT,NOWDT,NOPBADEN,NOLVP
#use delay(clock=4000000)

#define LCD_DATA_PORT getenv("SFR:PORTB") 
#include <lcd.c> //No se usa fast_io en la puerta

#use fast_io (A)

#int_ad								//Vector de interrupción al finalizar la conversión A/D
tratamiento(){	
	float Vin;		
	Vin=read_adc(adc_read_only);	//Lee el resultado de la conversión
	lcd_putc('\f');
	printf(lcd_putc, "Vin= %1.2g Volt.",Vin*0.004887585);	//Visualiza el resultado de la conversión, convertido a voltios
	delay_ms(1000);
	enable_interrupts(INT_AD);		//Activa interrupción al finalizar la conversión
	read_adc(adc_start_only);		//Inicia una nueva conversión
}	

void main(){
	SETUP_ADC_PORTS(AN0|VSS_VDD);	//RA0 analógica, resto digitales, VREF+=Vdd y VREF-=Vss
	setup_comparator(NC_NC_NC_NC);	//Comparadores OFF
	setup_adc(ADC_CLOCK_DIV_4);		//Justificación dcha., reloj Fosc/4
	set_tris_a(0b11111111);			//Puerta A entrada	
	set_adc_channel(0);				//Selección del canal RA0/AN0
	delay_us(20);
	lcd_init();
	lcd_putc('\f');
	enable_interrupts(INT_AD);		//Activa interrupción al finalizar la conversión
	enable_interrupts(global);		//Habilita interrupciones	
	read_adc(adc_start_only);		//Inicia la conversión


	while(1){
	
	}
}
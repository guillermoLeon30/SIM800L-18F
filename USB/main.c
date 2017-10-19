#include <18f2550.h>	//Tipo de procesador
#use delay(clock=24000000)			//Frecuencia de trabajo

//#use delay(clock=16MHz,crystal=4MHz,USB_FULL)
#fuses 	ECPLL_IO		//Oscilador externo, RA6=E/S,PLL ON (CONFIG1H)
#fuses	PLL1, USBDIV	//48Mhz al USB
#fuses 	CPUDIV4			//Postcaler PLL/4, Frec. CPU=96MHz/4=24MHz (CONFIG1L)
						//Ciclo de instrucción = 0.16uS (1/(24000000/4))

#fuses PUT,NOBROWNOUT,NOWDT,NOPBADEN,NOLVP

#define USB_ISR_POLLING
#define USB_CABLE_IS_ATTACHED()  input(PIN_C2)
#define USB_CONFIG_VID 0x04D8
#define USB_CONFIG_PID 0x000A
#include <usb_cdc.h>

#define LCD_DATA_PORT getenv("SFR:PORTB") 
#include <lcd.c> //No se usa fast_io en la puerta

void main(){
	
	//lcd_init();
	usb_init_cs();
	usb_init();
	
	while(1){
		usb_task();
		if (usb_enumerated()){
			printf(usb_cdc_putc, "hola" );	
		}
		delay_ms(300);
	}
}

#define F_CPU 8000000
#define BAUD 9600
#define MYUBRR F_CPU/16/(BAUD-1)
#include <xc.h>
#include <util/delay.h>
#include <avr/io.h>

void UART_init(unsigned int ubrr){
	//set baud rate:
	UBRR0H = 0;
	UBRR0L = 51;
	
	//set frame format: 1 bit stop, 8 bit data
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);		// or UCSR0C = 0x06;
	
	//enable receiver and transmitter:
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
}
void Data_Tx(unsigned char data){
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

unsigned char Data_Rx(void){
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}


int main(void)
{
	UART_init(MYUBRR);
	while(1){
			Data_Tx('T');
			Data_Tx('h');
			Data_Tx('i');
			Data_Tx('e');
			Data_Tx('n');
			Data_Tx(' ');
			_delay_ms(1000);
			Data_Rx();
			_delay_ms(1000);		
	}
}
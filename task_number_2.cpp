
#include <avr/io.h>
#include <string.h>
#include <stdio.h>

#define F_CPU 8000000UL
#define ADC_VREF_TYPE 0x40
int setpoint 20.0;


void ADC_Init(){										
	DDRA = 0x00;	        // ADC sebagai input
	ADCSRA = 0x87;          // Enable ADC
	ADMUX = 0x40;           // Vref: Avcc, ADC channel: 0 
}

int ADC_Read(char channel)							
{
	ADMUX = 0x40 | (channel & 0x07);   // set input sebagai pin pembaca
	ADCSRA |= (1<<ADSC);               // Start koversi ADC
	while (!(ADCSRA & (1<<ADIF)));     // Wait 
	ADCSRA |= (1<<ADIF);               // Clear 
	_delay_ms(1);                      
	return ADCW;                       
}

unsigned int read_adc(unsigned char adc_input)
{
    ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
    delay_us(10);
    ADCSRA|=0x40;
    while ((ADCSRA & 0x10)==0);
    ADCSRA|=0x10;
    return ADCW;
}

void delay_ms(unsigned int de)
{
unsigned int rr,rr1;
   for (rr=0;rr<de;rr++)
   {
  
  for(rr1=0;rr1<30;rr1++)   //395
  {
   asm("nop");
  }
   
   }
}

int main()
{
	char Temperature[10];
	float celsius;
	ADC_Init();                 /* initialize ADC*/
	
	while(1)
	{
        ADC_Init();                 /* initialize ADC*/
        vin=read_adc(0); // read analog
        celsius=(float)vin*5/1023; // convert analog ke celcius
        celsius=celsius*100; // 1 derajat berubah 100mV

        //Compare with Set Points and operate Relay
        if(celsius >= setpoint) //suhu melebihi 20 derajat celcius
        {
            //Actuator On
            DDRA = 0xFF;
            PORTA=0b00000010;
            PORTA=0xFF;
        }
        else
        {
             //Actuator Off
             PORTA=0x00;
             DDRA = 0xFF;
             PORTA=0b00000001;
             PORTA=0xFF;      // LED nyala
             delay_ms(1000); // delay 1000ms (1 detik)
             PORTA=0x00;
             delay_ms(1000); // LED mati
        }
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ЗАГОЛВОЧНЫЙ ФАЙЛ С МАКРОСАМИ ДЛЯ Atmega328, Atmega32u4, Atmega2560, Attiny13
//  ДЛЯ БОЛЕЕ УДОБНОГО УПРАВЛЕНИЯ ПОРТАМИ ЧЕРЕЗ РЕГИСРЫ С ПОМОЩЬЮ МАКРОСОВ
//  ФАЙЛ НЕ ЗАНИМАЕТ ПАМЯТЬ УСТРОЙСТВА. ИСПОЛЬЗУЕТСЯ ТОЛЬКО ПРИ КОМПИЛЯЦИИ
//  created by SS2S :: 32x11100111000001011100
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ВЫБОР КОНТРОЛЛЕРА
#ifndef PLATFORM
#define PLATFORM 328 // 328 - UNO; 324 - Leonardo; 2560 - MEGA2560; 13 - attiny13;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
// void setup(){
	// sbi(ADCSRA, ADPS2);    //Биту ADPS2 присваиваем единицу
	// cbi(ADCSRA, ADPS1);    //Битам ADPS1 и ADPS0 присваиваем нули
	// cbi(ADCSRA, ADPS0); 
// }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ADPS[2:0] Коэффициент деления
//  000	      2    //  8 mHz

//  001	      2    //  8 mHz

//  010	      4    //  4 mHz

//  011	      8    //  2 mHz   9 мкс

//  100	      16   //  1 mHz   ADCSRA |= (1 << ADPS2); //Биту ADPS2 присваиваем единицу - коэффициент деления 16. 16 мкс
//                             ADCSRA &= ~ ((1 << ADPS1) | (1 << ADPS0)); //Битам ADPS1 и ADPS0 присваиваем нули

//  101	      32   //  500 kHz  ADCSRA = _BV(ADSC) | _BV(ADEN) | _BV(ADPS2) | _BV(ADPS0);

//  110	      64   //  250 kHz

//  111	      128  //  125 kHz по умолчанию  112 мкс

//  БЫСТРЫЙ analogRead(); в 4 раза быстрее стандартного. стандартный 125 kHz 9600 сумплов, бистрый 500 kHz 37000 семплов
static inline uint16_t analogReadFast(byte analog_pin) {
	ADMUX = _BV(REFS0) | analog_pin;
	ADCSRA = _BV(ADSC) | _BV(ADEN) | _BV(ADPS2) | _BV(ADPS0);	//500 kHz
	while (ADCSRA & _BV(ADSC))
		;
	uint16_t ret;
	//	ret = ADCL;
	// ret |= ADCH << 8;
	asm volatile(
			"lds %A0,  %1\n\t"
			"lds %B0,  %2"
			: "=w" (ret): "n"(&ADCL), "n"(&ADCH));
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if PLATFORM == 328 // UNO (Atmega328)  (UNO, Nano, proMini)

//  pinMode(pin, INPUT);
#define ADF_PMI0  DDRD &= B11111110 // D0
#define ADF_PMI1  DDRD &= B11111101 // D1
#define ADF_PMI2  DDRD &= B11111011 // D2
#define ADF_PMI3  DDRD &= B11110111 // D3
#define ADF_PMI4  DDRD &= B11101111 // D4
#define ADF_PMI5  DDRD &= B11011111 // D5
#define ADF_PMI6  DDRD &= B10111111 // D6
#define ADF_PMI7  DDRD &= B01111111 // D7
#define ADF_PMI8  DDRB &= B11111110 // B0
#define ADF_PMI9  DDRB &= B11111101 // B1
#define ADF_PMI10 DDRB &= B11111011 // B2
#define ADF_PMI11 DDRB &= B11110111 // B3
#define ADF_PMI12 DDRB &= B11101111 // B4
#define ADF_PMI13 DDRB &= B11011111 // B5

#define ADF_PMIA0 DDRC &= B11111110 // C0
#define ADF_PMIA1 DDRC &= B11111101 // C1
#define ADF_PMIA2 DDRC &= B11111011 // C2
#define ADF_PMIA3 DDRC &= B11110111 // C3
#define ADF_PMIA4 DDRC &= B11101111 // C4
#define ADF_PMIA5 DDRC &= B11011111 // C5
//  pinMode(pin, OUTPUT);
#define ADF_PMO0  DDRD |= B00000001 // D0
#define ADF_PMO1  DDRD |= B00000010 // D1
#define ADF_PMO2  DDRD |= B00000100 // D2
#define ADF_PMO3  DDRD |= B00001000 // D3
#define ADF_PMO4  DDRD |= B00010000 // D4
#define ADF_PMO5  DDRD |= B00100000 // D5
#define ADF_PMO6  DDRD |= B01000000 // D6
#define ADF_PMO7  DDRD |= B10000000 // D7
#define ADF_PMO8  DDRB |= B00000001 // B0
#define ADF_PMO9  DDRB |= B00000010 // B1
#define ADF_PMO10 DDRB |= B00000100 // B2
#define ADF_PMO11 DDRB |= B00001000 // B3
#define ADF_PMO12 DDRB |= B00010000 // B4
#define ADF_PMO13 DDRB |= B00100000 // B5

#define ADF_PMOA0 DDRC |= B00000001 // C0
#define ADF_PMOA1 DDRC |= B00000010 // C1
#define ADF_PMOA2 DDRC |= B00000100 // C2
#define ADF_PMOA3 DDRC |= B00001000 // C3
#define ADF_PMOA4 DDRC |= B00010000 // C4
#define ADF_PMOA5 DDRC |= B00100000 // C5
//  pinMode(pin, INPUT_PULLUP);
#define ADF_PMIP0  DDRD &= B11111110; PORTD |= B00000001 // D0
#define ADF_PMIP1  DDRD &= B11111101; PORTD |= B00000010 // D1
#define ADF_PMIP2  DDRD &= B11111011; PORTD |= B00000100 // D2
#define ADF_PMIP3  DDRD &= B11110111; PORTD |= B00001000 // D3
#define ADF_PMIP4  DDRD &= B11101111; PORTD |= B00010000 // D4
#define ADF_PMIP5  DDRD &= B11011111; PORTD |= B00100000 // D5
#define ADF_PMIP6  DDRD &= B10111111; PORTD |= B01000000 // D6
#define ADF_PMIP7  DDRD &= B01111111; PORTD |= B10000000 // D7
#define ADF_PMIP8  DDRB &= B11111110; PORTB |= B00000001 // B0
#define ADF_PMIP9  DDRB &= B11111101; PORTB |= B00000010 // B1
#define ADF_PMIP10 DDRB &= B11111011; PORTB |= B00000100 // B2
#define ADF_PMIP11 DDRB &= B11110111; PORTB |= B00001000 // B3
#define ADF_PMIP12 DDRB &= B11101111; PORTB |= B00010000 // B4
#define ADF_PMIP13 DDRB &= B11011111; PORTB |= B00100000 // B5

#define ADF_PMIPA0 DDRC &= B11111110; PORTC |= B00000001 // C0
#define ADF_PMIPA1 DDRC &= B11111101; PORTC |= B00000010 // C1
#define ADF_PMIPA2 DDRC &= B11111011; PORTC |= B00000100 // C2
#define ADF_PMIPA3 DDRC &= B11110111; PORTC |= B00001000 // C3
#define ADF_PMIPA4 DDRC &= B11101111; PORTC |= B00010000 // C4
#define ADF_PMIPA5 DDRC &= B11011111; PORTC |= B00100000 // C5
//  digitalWrite(pin, HIGH);
#define ADF_DWH0  PORTD |= B00000001 // D0
#define ADF_DWH1  PORTD |= B00000010 // D1
#define ADF_DWH2  PORTD |= B00000100 // D2
#define ADF_DWH3  PORTD |= B00001000 // D3
#define ADF_DWH4  PORTD |= B00010000 // D4
#define ADF_DWH5  PORTD |= B00100000 // D5
#define ADF_DWH6  PORTD |= B01000000 // D6
#define ADF_DWH7  PORTD |= B10000000 // D7
#define ADF_DWH8  PORTB |= B00000001 // B0
#define ADF_DWH9  PORTB |= B00000010 // B1
#define ADF_DWH10 PORTB |= B00000100 // B2
#define ADF_DWH11 PORTB |= B00001000 // B3
#define ADF_DWH12 PORTB |= B00010000 // B4
#define ADF_DWH13 PORTB |= B00100000 // B5

#define ADF_DWHA0 PORTC |= B00000001 // C0
#define ADF_DWHA1 PORTC |= B00000010 // C1
#define ADF_DWHA2 PORTC |= B00000100 // C2
#define ADF_DWHA3 PORTC |= B00001000 // C3
#define ADF_DWHA4 PORTC |= B00010000 // C4
#define ADF_DWHA5 PORTC |= B00100000 // C5
//  digitalWrite(pin, LOW);
#define ADF_DWL0  PORTD &= B11111110 // D0
#define ADF_DWL1  PORTD &= B11111101 // D1
#define ADF_DWL2  PORTD &= B11111011 // D2
#define ADF_DWL3  PORTD &= B11110111 // D3
#define ADF_DWL4  PORTD &= B11101111 // D4
#define ADF_DWL5  PORTD &= B11011111 // D5
#define ADF_DWL6  PORTD &= B10111111 // D6
#define ADF_DWL7  PORTD &= B01111111 // D7
#define ADF_DWL8  PORTB &= B11111110 // B0
#define ADF_DWL9  PORTB &= B11111101 // B1
#define ADF_DWL10 PORTB &= B11111011 // B2
#define ADF_DWL11 PORTB &= B11110111 // B3
#define ADF_DWL12 PORTB &= B11101111 // B4
#define ADF_DWL13 PORTB &= B11011111 // B5

#define ADF_DWLA0 PORTC &= B11111110 // C0
#define ADF_DWLA1 PORTC &= B11111101 // C1
#define ADF_DWLA2 PORTC &= B11111011 // C2
#define ADF_DWLA3 PORTC &= B11110111 // C3
#define ADF_DWLA4 PORTC &= B11101111 // C4
#define ADF_DWLA5 PORTC &= B11011111 // C5
//  digitalRead(pin);
#define ADF_DR0  PIND &= B00000001 // D0
#define ADF_DR1  PIND &= B00000010 // D1
#define ADF_DR2  PIND &= B00000100 // D2
#define ADF_DR3  PIND &= B00001000 // D3
#define ADF_DR4  PIND &= B00010000 // D4
#define ADF_DR5  PIND &= B00100000 // D5
#define ADF_DR6  PIND &= B01000000 // D6
#define ADF_DR7  PIND &= B10000000 // D7
#define ADF_DR8  PINB &= B00000001 // B0
#define ADF_DR9  PINB &= B00000010 // B1
#define ADF_DR10 PINB &= B00000100 // B2
#define ADF_DR11 PINB &= B00001000 // B3
#define ADF_DR12 PINB &= B00010000 // B4
#define ADF_DR13 PINB &= B00100000 // B5

#define ADF_DRA0 PINC &= B00000001 // C0
#define ADF_DRA1 PINC &= B00000010 // C1
#define ADF_DRA2 PINC &= B00000100 // C2
#define ADF_DRA3 PINC &= B00001000 // C3
#define ADF_DRA4 PINC &= B00010000 // C4
#define ADF_DRA5 PINC &= B00100000 // C5

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#elif PLATFORM == 324 // Leonardo (Atmega32u4)  (Leonardo, proMicro)

//  pinMode(pin, INPUT);
#define ADF_PMI0  DDRD &= B11111011 // D2
#define ADF_PMI1  DDRD &= B11110111 // D3
#define ADF_PMI2  DDRD &= B11111101 // D1
#define ADF_PMI3  DDRD &= B11111110 // D0
#define ADF_PMI4  DDRD &= B11101111 // D4
#define ADF_PMI5  DDRC &= B10111111 // C6
#define ADF_PMI6  DDRD &= B01111111 // D7
#define ADF_PMI7  DDRE &= B10111111 // E6
#define ADF_PMI8  DDRB &= B11101111 // B4
#define ADF_PMI9  DDRB &= B11011111 // B5
#define ADF_PMI10 DDRB &= B10111111 // B6
#define ADF_PMI11 DDRB &= B01111111 // B7
#define ADF_PMI12 DDRD &= B10111111 // D6
#define ADF_PMI13 DDRC &= B01111111 // C7

#define ADF_PMIA0 DDRF &= B01111111 // F7
#define ADF_PMIA1 DDRF &= B10111111 // F6
#define ADF_PMIA2 DDRF &= B11011111 // F5
#define ADF_PMIA3 DDRF &= B11101111 // F4
#define ADF_PMIA4 DDRF &= B11111101 // F1
#define ADF_PMIA5 DDRF &= B11111110 // F0
//  pinMode(pin, OUTPUT);
#define ADF_PMO0  DDRD |= B00000100 // D2
#define ADF_PMO1  DDRD |= B00001000 // D3
#define ADF_PMO2  DDRD |= B00000010 // D1
#define ADF_PMO3  DDRD |= B00000001 // D0
#define ADF_PMO4  DDRD |= B00010000 // D4
#define ADF_PMO5  DDRC |= B01000000 // C6
#define ADF_PMO6  DDRD |= B10000000 // D7
#define ADF_PMO7  DDRE |= B01000000 // E6
#define ADF_PMO8  DDRB |= B00010000 // B4
#define ADF_PMO9  DDRB |= B00100000 // B5
#define ADF_PMO10 DDRB |= B01000000 // B6
#define ADF_PMO11 DDRB |= B10000000 // B7
#define ADF_PMO12 DDRD |= B01000000 // D6
#define ADF_PMO13 DDRC |= B10000000 // C7

#define ADF_PMOA0 DDRF |= B10000000 // F7
#define ADF_PMOA1 DDRF |= B01000000 // F6
#define ADF_PMOA2 DDRF |= B00100000 // F5
#define ADF_PMOA3 DDRF |= B00010000 // F4
#define ADF_PMOA4 DDRF |= B00000010 // F1
#define ADF_PMOA5 DDRF |= B00000001 // F0
//  pinMode(pin, INPUT_PULLUP);
#define ADF_PMIP0  DDRD &= B11111011; PORTD |= B00000100 // D2
#define ADF_PMIP1  DDRD &= B11110111; PORTD |= B00001000 // D3
#define ADF_PMIP2  DDRD &= B11111101; PORTD |= B00000010 // D1
#define ADF_PMIP3  DDRD &= B11111110; PORTD |= B00000001 // D0
#define ADF_PMIP4  DDRD &= B11101111; PORTD |= B00010000 // D4
#define ADF_PMIP5  DDRC &= B10111111; PORTC |= B01000000 // C6
#define ADF_PMIP6  DDRD &= B01111111; PORTD |= B10000000 // D7
#define ADF_PMIP7  DDRE &= B10111111; PORTE |= B01000000 // E6
#define ADF_PMIP8  DDRB &= B11101111; PORTB |= B00010000 // B4
#define ADF_PMIP9  DDRB &= B11011111; PORTB |= B00100000 // B5
#define ADF_PMIP10 DDRB &= B10111111; PORTB |= B01000000 // B6
#define ADF_PMIP11 DDRB &= B01111111; PORTB |= B10000000 // B7
#define ADF_PMIP12 DDRD &= B10111111; PORTD |= B01000000 // D6
#define ADF_PMIP13 DDRC &= B01111111; PORTC |= B10000000 // C7

#define ADF_PMIPA0 DDRF &= B01111111; PORTF |= B10000000 // F7
#define ADF_PMIPA1 DDRF &= B10111111; PORTF |= B01000000 // F6
#define ADF_PMIPA2 DDRF &= B11011111; PORTF |= B00100000 // F5
#define ADF_PMIPA3 DDRF &= B11101111; PORTF |= B00010000 // F4
#define ADF_PMIPA4 DDRF &= B11111101; PORTF |= B00000010 // F1
#define ADF_PMIPA5 DDRF &= B11111110; PORTF |= B00000001 // F0
//  digitalWrite(pin, HIGH);
#define ADF_DWH0  PORTD |= B00000100 // D2
#define ADF_DWH1  PORTD |= B00001000 // D3
#define ADF_DWH2  PORTD |= B00000010 // D1
#define ADF_DWH3  PORTD |= B00000001 // D0
#define ADF_DWH4  PORTD |= B00010000 // D4
#define ADF_DWH5  PORTC |= B01000000 // C6
#define ADF_DWH6  PORTD |= B10000000 // D7
#define ADF_DWH7  PORTE |= B01000000 // E6
#define ADF_DWH8  PORTB |= B00010000 // B4
#define ADF_DWH9  PORTB |= B00100000 // B5
#define ADF_DWH10 PORTB |= B01000000 // B6
#define ADF_DWH11 PORTB |= B10000000 // B7
#define ADF_DWH12 PORTD |= B01000000 // D6
#define ADF_DWH13 PORTC |= B10000000 // C7

#define ADF_DWHA0 PORTF |= B10000000 // F7
#define ADF_DWHA1 PORTF |= B01000000 // F6
#define ADF_DWHA2 PORTF |= B00100000 // F5
#define ADF_DWHA3 PORTF |= B00010000 // F4
#define ADF_DWHA4 PORTF |= B00000010 // F1
#define ADF_DWHA5 PORTF |= B00000001 // F0
//  digitalWrite(pin, LOW);
#define ADF_DWL0  PORTD &= B11111011 // D2
#define ADF_DWL1  PORTD &= B11110111 // D3
#define ADF_DWL2  PORTD &= B11111101 // D1
#define ADF_DWL3  PORTD &= B11111110 // D0
#define ADF_DWL4  PORTD &= B11101111 // D4
#define ADF_DWL5  PORTC &= B10111111 // C6
#define ADF_DWL6  PORTD &= B01111111 // D7
#define ADF_DWL7  PORTE &= B10111111 // E6
#define ADF_DWL8  PORTB &= B11101111 // B4
#define ADF_DWL9  PORTB &= B11011111 // B5
#define ADF_DWL10 PORTB &= B10111111 // B6
#define ADF_DWL11 PORTB &= B01111111 // B7
#define ADF_DWL12 PORTD &= B10111111 // D6
#define ADF_DWL13 PORTC &= B01111111 // C7

#define ADF_DWLA0 PORTF &= B01111111 // F7
#define ADF_DWLA1 PORTF &= B10111111 // F6
#define ADF_DWLA2 PORTF &= B11011111 // F5
#define ADF_DWLA3 PORTF &= B11101111 // F4
#define ADF_DWLA4 PORTF &= B11111101 // F1
#define ADF_DWLA5 PORTF &= B11111110 // F0
//  digitalRead(pin);
#define ADF_DR0  PIND &= B00000100 // D2
#define ADF_DR1  PIND &= B00001000 // D3
#define ADF_DR2  PIND &= B00000010 // D1
#define ADF_DR3  PIND &= B00000001 // D0
#define ADF_DR4  PIND &= B00010000 // D4
#define ADF_DR5  PINC &= B01000000 // C6
#define ADF_DR6  PIND &= B10000000 // D7
#define ADF_DR7  PINE &= B01000000 // E6
#define ADF_DR8  PINB &= B00010000 // B4
#define ADF_DR9  PINB &= B00100000 // B5
#define ADF_DR10 PINB &= B01000000 // B6
#define ADF_DR11 PINB &= B10000000 // B7
#define ADF_DR12 PIND &= B01000000 // D6
#define ADF_DR13 PINC &= B10000000 // C7

#define ADF_DRA0 PINF &= B10000000 // F7
#define ADF_DRA1 PINF &= B01000000 // F6
#define ADF_DRA2 PINF &= B00100000 // F5
#define ADF_DRA3 PINF &= B00010000 // F4
#define ADF_DRA4 PINF &= B00000010 // F1
#define ADF_DRA5 PINF &= B00000001 // F0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#elif PLATFORM == 2560 // MEGA2560 (Atmega2560)

//  pinMode(pin, INPUT);
#define ADF_PMI0  DDRE &= B11111110 // E0
#define ADF_PMI1  DDRE &= B11111101 // E1
#define ADF_PMI2  DDRE &= B11101111 // E4
#define ADF_PMI3  DDRE &= B11011111 // E5
#define ADF_PMI4  DDRG &= B11011111 // G5
#define ADF_PMI5  DDRE &= B11110111 // E3
#define ADF_PMI6  DDRH &= B11110111 // H3
#define ADF_PMI7  DDRH &= B11101111 // H4
#define ADF_PMI8  DDRH &= B11011111 // H5
#define ADF_PMI9  DDRH &= B10111111 // H6
#define ADF_PMI10 DDRB &= B11101111 // B4
#define ADF_PMI11 DDRB &= B11011111 // B5
#define ADF_PMI12 DDRB &= B10111111 // B6
#define ADF_PMI13 DDRB &= B01111111 // B7
#define ADF_PMI14 DDRJ &= B11111101 // J1
#define ADF_PMI15 DDRJ &= B11111110 // J0
#define ADF_PMI16 DDRH &= B11111101 // H1
#define ADF_PMI17 DDRH &= B11111110 // H0
#define ADF_PMI18 DDRD &= B11110111 // D3
#define ADF_PMI19 DDRD &= B11111011 // D2
#define ADF_PMI20 DDRD &= B11111101 // D1
#define ADF_PMI21 DDRD &= B11111110 // D0
#define ADF_PMI22 DDRA &= B11111110 // A0
#define ADF_PMI23 DDRA &= B11111101 // A1
#define ADF_PMI24 DDRA &= B11111011 // A2
#define ADF_PMI25 DDRA &= B11110111 // A3
#define ADF_PMI26 DDRA &= B11101111 // A4
#define ADF_PMI27 DDRA &= B11011111 // A5
#define ADF_PMI28 DDRA &= B10111111 // A6
#define ADF_PMI29 DDRA &= B01111111 // A7
#define ADF_PMI30 DDRC &= B01111111 // C7
#define ADF_PMI31 DDRC &= B10111111 // C6
#define ADF_PMI32 DDRC &= B11011111 // C5
#define ADF_PMI33 DDRC &= B11101111 // C4
#define ADF_PMI34 DDRC &= B11110111 // C3
#define ADF_PMI35 DDRC &= B11111011 // C2
#define ADF_PMI36 DDRC &= B11111101 // C1
#define ADF_PMI37 DDRC &= B11111110 // C0
#define ADF_PMI38 DDRD &= B01111111 // D7
#define ADF_PMI39 DDRG &= B11111011 // G2
#define ADF_PMI40 DDRG &= B11111101 // G1
#define ADF_PMI41 DDRG &= B11111110 // G0
#define ADF_PMI42 DDRL &= B01111111 // L7
#define ADF_PMI43 DDRL &= B10111111 // L6
#define ADF_PMI44 DDRL &= B11011111 // L5
#define ADF_PMI45 DDRL &= B11101111 // L4
#define ADF_PMI46 DDRL &= B11110111 // L3
#define ADF_PMI47 DDRL &= B11111011 // L2
#define ADF_PMI48 DDRL &= B11111101 // L1
#define ADF_PMI49 DDRL &= B11111110 // L0
#define ADF_PMI50 DDRB &= B11110111 // B3
#define ADF_PMI51 DDRB &= B11111011 // B2
#define ADF_PMI52 DDRB &= B11111101 // B1
#define ADF_PMI53 DDRB &= B11111110 // B0

#define ADF_PMIA0  DDRF &= B11111110 // F0
#define ADF_PMIA1  DDRF &= B11111101 // F1
#define ADF_PMIA2  DDRF &= B11111011 // F2
#define ADF_PMIA3  DDRF &= B11110111 // F3
#define ADF_PMIA4  DDRF &= B11101111 // F4
#define ADF_PMIA5  DDRF &= B11011111 // F5
#define ADF_PMIA6  DDRF &= B10111111 // F6
#define ADF_PMIA7  DDRF &= B01111111 // F7
#define ADF_PMIA8  DDRK &= B11111110 // K0
#define ADF_PMIA9  DDRK &= B11111101 // K1
#define ADF_PMIA10 DDRK &= B11111011 // K2
#define ADF_PMIA11 DDRK &= B11110111 // K3
#define ADF_PMIA12 DDRK &= B11101111 // K4
#define ADF_PMIA13 DDRK &= B11011111 // K5
#define ADF_PMIA14 DDRK &= B10111111 // K6
#define ADF_PMIA15 DDRK &= B01111111 // K7
//  pinMode(pin, OUTPUT);
#define ADF_PMO0  DDRE |= B00000001 // E0
#define ADF_PMO1  DDRE |= B00000010 // E1
#define ADF_PMO2  DDRE |= B00010000 // E4
#define ADF_PMO3  DDRE |= B00100000 // E5
#define ADF_PMO4  DDRG |= B00100000 // G5
#define ADF_PMO5  DDRE |= B00001000 // E3
#define ADF_PMO6  DDRH |= B00001000 // H3
#define ADF_PMO7  DDRH |= B00010000 // H4
#define ADF_PMO8  DDRH |= B00100000 // H5
#define ADF_PMO9  DDRH |= B01000000 // H6
#define ADF_PMO10 DDRB |= B00010000 // B4
#define ADF_PMO11 DDRB |= B00100000 // B5
#define ADF_PMO12 DDRB |= B01000000 // B6
#define ADF_PMO13 DDRB |= B10000000 // B7
#define ADF_PMO14 DDRJ |= B00000010 // J1
#define ADF_PMO15 DDRJ |= B00000001 // J0
#define ADF_PMO16 DDRH |= B00000010 // H1
#define ADF_PMO17 DDRH |= B00000001 // H0
#define ADF_PMO18 DDRD |= B00001000 // D3
#define ADF_PMO19 DDRD |= B00000100 // D2
#define ADF_PMO20 DDRD |= B00000010 // D1
#define ADF_PMO21 DDRD |= B00000001 // D0
#define ADF_PMO22 DDRA |= B00000001 // A0
#define ADF_PMO23 DDRA |= B00000010 // A1
#define ADF_PMO24 DDRA |= B00000100 // A2
#define ADF_PMO25 DDRA |= B00001000 // A3
#define ADF_PMO26 DDRA |= B00010000 // A4
#define ADF_PMO27 DDRA |= B00100000 // A5
#define ADF_PMO28 DDRA |= B01000000 // A6
#define ADF_PMO29 DDRA |= B10000000 // A7
#define ADF_PMO30 DDRC |= B10000000 // C7
#define ADF_PMO31 DDRC |= B01000000 // C6
#define ADF_PMO32 DDRC |= B00100000 // C5
#define ADF_PMO33 DDRC |= B00010000 // C4
#define ADF_PMO34 DDRC |= B00001000 // C3
#define ADF_PMO35 DDRC |= B00000100 // C2
#define ADF_PMO36 DDRC |= B00000010 // C1
#define ADF_PMO37 DDRC |= B00000001 // C0
#define ADF_PMO38 DDRD |= B10000000 // D7
#define ADF_PMO39 DDRG |= B00000100 // G2
#define ADF_PMO40 DDRG |= B00000010 // G1
#define ADF_PMO41 DDRG |= B00000001 // G0
#define ADF_PMO42 DDRL |= B10000000 // L7
#define ADF_PMO43 DDRL |= B01000000 // L6
#define ADF_PMO44 DDRL |= B00100000 // L5
#define ADF_PMO45 DDRL |= B00010000 // L4
#define ADF_PMO46 DDRL |= B00001000 // L3
#define ADF_PMO47 DDRL |= B00000100 // L2
#define ADF_PMO48 DDRL |= B00000010 // L1
#define ADF_PMO49 DDRL |= B00000001 // L0
#define ADF_PMO50 DDRB |= B00001000 // B3
#define ADF_PMO51 DDRB |= B00000100 // B2
#define ADF_PMO52 DDRB |= B00000010 // B1
#define ADF_PMO53 DDRB |= B00000001 // B0

#define ADF_PMOA0  DDRF |= B00000001 // F0
#define ADF_PMOA1  DDRF |= B00000010 // F1
#define ADF_PMOA2  DDRF |= B00000100 // F2
#define ADF_PMOA3  DDRF |= B00001000 // F3
#define ADF_PMOA4  DDRF |= B00010000 // F4
#define ADF_PMOA5  DDRF |= B00100000 // F5
#define ADF_PMOA6  DDRF |= B01000000 // F6
#define ADF_PMOA7  DDRF |= B10000000 // F7
#define ADF_PMOA8  DDRK |= B00000001 // K0
#define ADF_PMOA9  DDRK |= B00000010 // K1
#define ADF_PMOA10 DDRK |= B00000100 // K2
#define ADF_PMOA11 DDRK |= B00001000 // K3
#define ADF_PMOA12 DDRK |= B00010000 // K4
#define ADF_PMOA13 DDRK |= B00100000 // K5
#define ADF_PMOA14 DDRK |= B01000000 // K6
#define ADF_PMOA15 DDRK |= B10000000 // K7
//  pinMode(pin, INPUT_PULLUP);
#define ADF_PMIP0  DDRE &= B11111110; PORTE |= B00000001 // E0
#define ADF_PMIP1  DDRE &= B11111101; PORTE |= B00000010 // E1
#define ADF_PMIP2  DDRE &= B11101111; PORTE |= B00010000 // E4
#define ADF_PMIP3  DDRE &= B11011111; PORTE |= B00100000 // E5
#define ADF_PMIP4  DDRG &= B11011111; PORTG |= B00100000 // G5
#define ADF_PMIP5  DDRE &= B11110111; PORTE |= B00001000 // E3
#define ADF_PMIP6  DDRH &= B11110111; PORTH |= B00001000 // H3
#define ADF_PMIP7  DDRH &= B11101111; PORTH |= B00010000 // H4
#define ADF_PMIP8  DDRH &= B11011111; PORTH |= B00100000 // H5
#define ADF_PMIP9  DDRH &= B10111111; PORTH |= B01000000 // H6
#define ADF_PMIP10 DDRB &= B11101111; PORTB |= B00010000 // B4
#define ADF_PMIP11 DDRB &= B11011111; PORTB |= B00100000 // B5
#define ADF_PMIP12 DDRB &= B10111111; PORTB |= B01000000 // B6
#define ADF_PMIP13 DDRB &= B01111111; PORTB |= B10000000 // B7
#define ADF_PMIP14 DDRJ &= B11111101; PORTJ |= B00000010 // J1
#define ADF_PMIP15 DDRJ &= B11111110; PORTJ |= B00000001 // J0
#define ADF_PMIP16 DDRH &= B11111101; PORTH |= B00000010 // H1
#define ADF_PMIP17 DDRH &= B11111110; PORTH |= B00000001 // H0
#define ADF_PMIP18 DDRD &= B11110111; PORTD |= B00001000 // D3
#define ADF_PMIP19 DDRD &= B11111011; PORTD |= B00000100 // D2
#define ADF_PMIP20 DDRD &= B11111101; PORTD |= B00000010 // D1
#define ADF_PMIP21 DDRD &= B11111110; PORTD |= B00000001 // D0
#define ADF_PMIP22 DDRA &= B11111110; PORTA |= B00000001 // A0
#define ADF_PMIP23 DDRA &= B11111101; PORTA |= B00000010 // A1
#define ADF_PMIP24 DDRA &= B11111011; PORTA |= B00000100 // A2
#define ADF_PMIP25 DDRA &= B11110111; PORTA |= B00001000 // A3
#define ADF_PMIP26 DDRA &= B11101111; PORTA |= B00010000 // A4
#define ADF_PMIP27 DDRA &= B11011111; PORTA |= B00100000 // A5
#define ADF_PMIP28 DDRA &= B10111111; PORTA |= B01000000 // A6
#define ADF_PMIP29 DDRA &= B01111111; PORTA |= B10000000 // A7
#define ADF_PMIP30 DDRC &= B01111111; PORTC |= B10000000 // C7
#define ADF_PMIP31 DDRC &= B10111111; PORTC |= B01000000 // C6
#define ADF_PMIP32 DDRC &= B11011111; PORTC |= B00100000 // C5
#define ADF_PMIP33 DDRC &= B11101111; PORTC |= B00010000 // C4
#define ADF_PMIP34 DDRC &= B11110111; PORTC |= B00001000 // C3
#define ADF_PMIP35 DDRC &= B11111011; PORTC |= B00000100 // C2
#define ADF_PMIP36 DDRC &= B11111101; PORTC |= B00000010 // C1
#define ADF_PMIP37 DDRC &= B11111110; PORTC |= B00000001 // C0
#define ADF_PMIP38 DDRD &= B01111111; PORTD |= B10000000 // D7
#define ADF_PMIP39 DDRG &= B11111011; PORTG |= B00000100 // G2
#define ADF_PMIP40 DDRG &= B11111101; PORTG |= B00000010 // G1
#define ADF_PMIP41 DDRG &= B11111110; PORTG |= B00000001 // G0
#define ADF_PMIP42 DDRL &= B01111111; PORTL |= B10000000 // L7
#define ADF_PMIP43 DDRL &= B10111111; PORTL |= B01000000 // L6
#define ADF_PMIP44 DDRL &= B11011111; PORTL |= B00100000 // L5
#define ADF_PMIP45 DDRL &= B11101111; PORTL |= B00010000 // L4
#define ADF_PMIP46 DDRL &= B11110111; PORTL |= B00001000 // L3
#define ADF_PMIP47 DDRL &= B11111011; PORTL |= B00000100 // L2
#define ADF_PMIP48 DDRL &= B11111101; PORTL |= B00000010 // L1
#define ADF_PMIP49 DDRL &= B11111110; PORTL |= B00000001 // L0
#define ADF_PMIP50 DDRB &= B11110111; PORTB |= B00001000 // B3
#define ADF_PMIP51 DDRB &= B11111011; PORTB |= B00000100 // B2
#define ADF_PMIP52 DDRB &= B11111101; PORTB |= B00000010 // B1
#define ADF_PMIP53 DDRB &= B11111110; PORTB |= B00000001 // B0

#define ADF_PMIPA0  DDRF &= B11111110; PORTF |= B00000001 // F0
#define ADF_PMIPA1  DDRF &= B11111101; PORTF |= B00000010 // F1
#define ADF_PMIPA2  DDRF &= B11111011; PORTF |= B00000100 // F2
#define ADF_PMIPA3  DDRF &= B11110111; PORTF |= B00001000 // F3
#define ADF_PMIPA4  DDRF &= B11101111; PORTF |= B00010000 // F4
#define ADF_PMIPA5  DDRF &= B11011111; PORTF |= B00100000 // F5
#define ADF_PMIPA6  DDRF &= B10111111; PORTF |= B01000000 // F6
#define ADF_PMIPA7  DDRF &= B01111111; PORTF |= B10000000 // F7
#define ADF_PMIPA8  DDRK &= B11111110; PORTK |= B00000001 // K0
#define ADF_PMIPA9  DDRK &= B11111101; PORTK |= B00000010 // K1
#define ADF_PMIPA10 DDRK &= B11111011; PORTK |= B00000100 // K2
#define ADF_PMIPA11 DDRK &= B11110111; PORTK |= B00001000 // K3
#define ADF_PMIPA12 DDRK &= B11101111; PORTK |= B00010000 // K4
#define ADF_PMIPA13 DDRK &= B11011111; PORTK |= B00100000 // K5
#define ADF_PMIPA14 DDRK &= B10111111; PORTK |= B01000000 // K6
#define ADF_PMIPA15 DDRK &= B01111111; PORTK |= B10000000 // K7
//  digitalWrite(pin, HIGH);
#define ADF_DWH0  PORTE |= B00000001 // E0
#define ADF_DWH1  PORTE |= B00000010 // E1
#define ADF_DWH2  PORTE |= B00010000 // E4
#define ADF_DWH3  PORTE |= B00100000 // E5
#define ADF_DWH4  PORTG |= B00100000 // G5
#define ADF_DWH5  PORTE |= B00001000 // E3
#define ADF_DWH6  PORTH |= B00001000 // H3
#define ADF_DWH7  PORTH |= B00010000 // H4
#define ADF_DWH8  PORTH |= B00100000 // H5
#define ADF_DWH9  PORTH |= B01000000 // H6
#define ADF_DWH10 PORTB |= B00010000 // B4
#define ADF_DWH11 PORTB |= B00100000 // B5
#define ADF_DWH12 PORTB |= B01000000 // B6
#define ADF_DWH13 PORTB |= B10000000 // B7
#define ADF_DWH14 PORTJ |= B00000010 // J1
#define ADF_DWH15 PORTJ |= B00000001 // J0
#define ADF_DWH16 PORTH |= B00000010 // H1
#define ADF_DWH17 PORTH |= B00000001 // H0
#define ADF_DWH18 PORTD |= B00001000 // D3
#define ADF_DWH19 PORTD |= B00000100 // D2
#define ADF_DWH20 PORTD |= B00000010 // D1
#define ADF_DWH21 PORTD |= B00000001 // D0
#define ADF_DWH22 PORTA |= B00000001 // A0
#define ADF_DWH23 PORTA |= B00000010 // A1
#define ADF_DWH24 PORTA |= B00000100 // A2
#define ADF_DWH25 PORTA |= B00001000 // A3
#define ADF_DWH26 PORTA |= B00010000 // A4
#define ADF_DWH27 PORTA |= B00100000 // A5
#define ADF_DWH28 PORTA |= B01000000 // A6
#define ADF_DWH29 PORTA |= B10000000 // A7
#define ADF_DWH30 PORTC |= B10000000 // C7
#define ADF_DWH31 PORTC |= B01000000 // C6
#define ADF_DWH32 PORTC |= B00100000 // C5
#define ADF_DWH33 PORTC |= B00010000 // C4
#define ADF_DWH34 PORTC |= B00001000 // C3
#define ADF_DWH35 PORTC |= B00000100 // C2
#define ADF_DWH36 PORTC |= B00000010 // C1
#define ADF_DWH37 PORTC |= B00000001 // C0
#define ADF_DWH38 PORTD |= B10000000 // D7
#define ADF_DWH39 PORTG |= B00000100 // G2
#define ADF_DWH40 PORTG |= B00000010 // G1
#define ADF_DWH41 PORTG |= B00000001 // G0
#define ADF_DWH42 PORTL |= B10000000 // L7
#define ADF_DWH43 PORTL |= B01000000 // L6
#define ADF_DWH44 PORTL |= B00100000 // L5
#define ADF_DWH45 PORTL |= B00010000 // L4
#define ADF_DWH46 PORTL |= B00001000 // L3
#define ADF_DWH47 PORTL |= B00000100 // L2
#define ADF_DWH48 PORTL |= B00000010 // L1
#define ADF_DWH49 PORTL |= B00000001 // L0
#define ADF_DWH50 PORTB |= B00001000 // B3
#define ADF_DWH51 PORTB |= B00000100 // B2
#define ADF_DWH52 PORTB |= B00000010 // B1
#define ADF_DWH53 PORTB |= B00000001 // B0

#define ADF_DWHA0  PORTF |= B00000001 // F0
#define ADF_DWHA1  PORTF |= B00000010 // F1
#define ADF_DWHA2  PORTF |= B00000100 // F2
#define ADF_DWHA3  PORTF |= B00001000 // F3
#define ADF_DWHA4  PORTF |= B00010000 // F4
#define ADF_DWHA5  PORTF |= B00100000 // F5
#define ADF_DWHA6  PORTF |= B01000000 // F6
#define ADF_DWHA7  PORTF |= B10000000 // F7
#define ADF_DWHA8  PORTK |= B00000001 // K0
#define ADF_DWHA9  PORTK |= B00000010 // K1
#define ADF_DWHA10 PORTK |= B00000100 // K2
#define ADF_DWHA11 PORTK |= B00001000 // K3
#define ADF_DWHA12 PORTK |= B00010000 // K4
#define ADF_DWHA13 PORTK |= B00100000 // K5
#define ADF_DWHA14 PORTK |= B01000000 // K6
#define ADF_DWHA15 PORTK |= B10000000 // K7
//  digitalWrite(pin, LOW);
#define ADF_DWL0  PORTE &= B11111110 // E0
#define ADF_DWL1  PORTE &= B11111101 // E1
#define ADF_DWL2  PORTE &= B11101111 // E4
#define ADF_DWL3  PORTE &= B11011111 // E5
#define ADF_DWL4  PORTG &= B11011111 // G5
#define ADF_DWL5  PORTE &= B11110111 // E3
#define ADF_DWL6  PORTH &= B11110111 // H3
#define ADF_DWL7  PORTH &= B11101111 // H4
#define ADF_DWL8  PORTH &= B11011111 // H5
#define ADF_DWL9  PORTH &= B10111111 // H6
#define ADF_DWL10 PORTB &= B11101111 // B4
#define ADF_DWL11 PORTB &= B11011111 // B5
#define ADF_DWL12 PORTB &= B10111111 // B6
#define ADF_DWL13 PORTB &= B01111111 // B7
#define ADF_DWL14 PORTJ &= B11111101 // J1
#define ADF_DWL15 PORTJ &= B11111110 // J0
#define ADF_DWL16 PORTH &= B11111101 // H1
#define ADF_DWL17 PORTH &= B11111110 // H0
#define ADF_DWL18 PORTD &= B11110111 // D3
#define ADF_DWL19 PORTD &= B11111011 // D2
#define ADF_DWL20 PORTD &= B11111101 // D1
#define ADF_DWL21 PORTD &= B11111110 // D0
#define ADF_DWL22 PORTA &= B11111110 // A0
#define ADF_DWL23 PORTA &= B11111101 // A1
#define ADF_DWL24 PORTA &= B11111011 // A2
#define ADF_DWL25 PORTA &= B11110111 // A3
#define ADF_DWL26 PORTA &= B11101111 // A4
#define ADF_DWL27 PORTA &= B11011111 // A5
#define ADF_DWL28 PORTA &= B10111111 // A6
#define ADF_DWL29 PORTA &= B01111111 // A7
#define ADF_DWL30 PORTC &= B01111111 // C7
#define ADF_DWL31 PORTC &= B10111111 // C6
#define ADF_DWL32 PORTC &= B11011111 // C5
#define ADF_DWL33 PORTC &= B11101111 // C4
#define ADF_DWL34 PORTC &= B11110111 // C3
#define ADF_DWL35 PORTC &= B11111011 // C2
#define ADF_DWL36 PORTC &= B11111101 // C1
#define ADF_DWL37 PORTC &= B11111110 // C0
#define ADF_DWL38 PORTD &= B01111111 // D7
#define ADF_DWL39 PORTG &= B11111011 // G2
#define ADF_DWL40 PORTG &= B11111101 // G1
#define ADF_DWL41 PORTG &= B11111110 // G0
#define ADF_DWL42 PORTL &= B01111111 // L7
#define ADF_DWL43 PORTL &= B10111111 // L6
#define ADF_DWL44 PORTL &= B11011111 // L5
#define ADF_DWL45 PORTL &= B11101111 // L4
#define ADF_DWL46 PORTL &= B11110111 // L3
#define ADF_DWL47 PORTL &= B11111011 // L2
#define ADF_DWL48 PORTL &= B11111101 // L1
#define ADF_DWL49 PORTL &= B11111110 // L0
#define ADF_DWL50 PORTB &= B11110111 // B3
#define ADF_DWL51 PORTB &= B11111011 // B2
#define ADF_DWL52 PORTB &= B11111101 // B1
#define ADF_DWL53 PORTB &= B11111110 // B0

#define ADF_DWLA0  PORTF &= B11111110 // F0
#define ADF_DWLA1  PORTF &= B11111101 // F1
#define ADF_DWLA2  PORTF &= B11111011 // F2
#define ADF_DWLA3  PORTF &= B11110111 // F3
#define ADF_DWLA4  PORTF &= B11101111 // F4
#define ADF_DWLA5  PORTF &= B11011111 // F5
#define ADF_DWLA6  PORTF &= B10111111 // F6
#define ADF_DWLA7  PORTF &= B01111111 // F7
#define ADF_DWLA8  PORTK &= B11111110 // K0
#define ADF_DWLA9  PORTK &= B11111101 // K1
#define ADF_DWLA10 PORTK &= B11111011 // K2
#define ADF_DWLA11 PORTK &= B11110111 // K3
#define ADF_DWLA12 PORTK &= B11101111 // K4
#define ADF_DWLA13 PORTK &= B11011111 // K5
#define ADF_DWLA14 PORTK &= B10111111 // K6
#define ADF_DWLA15 PORTK &= B01111111 // K7
//  digitalRead(pin);
#define ADF_DR0  PINE &= B00000001 // E0
#define ADF_DR1  PINE &= B00000010 // E1
#define ADF_DR2  PINE &= B00010000 // E4
#define ADF_DR3  PINE &= B00100000 // E5
#define ADF_DR4  PING &= B00100000 // G5
#define ADF_DR5  PINE &= B00001000 // E3
#define ADF_DR6  PINH &= B00001000 // H3
#define ADF_DR7  PINH &= B00010000 // H4
#define ADF_DR8  PINH &= B00100000 // H5
#define ADF_DR9  PINH &= B01000000 // H6
#define ADF_DR10 PINB &= B00010000 // B4
#define ADF_DR11 PINB &= B00100000 // B5
#define ADF_DR12 PINB &= B01000000 // B6
#define ADF_DR13 PINB &= B10000000 // B7
#define ADF_DR14 PINJ &= B00000010 // J1
#define ADF_DR15 PINJ &= B00000001 // J0
#define ADF_DR16 PINH &= B00000010 // H1
#define ADF_DR17 PINH &= B00000001 // H0
#define ADF_DR18 PIND &= B00001000 // D3
#define ADF_DR19 PIND &= B00000100 // D2
#define ADF_DR20 PIND &= B00000010 // D1
#define ADF_DR21 PIND &= B00000001 // D0
#define ADF_DR22 PINA &= B00000001 // A0
#define ADF_DR23 PINA &= B00000010 // A1
#define ADF_DR24 PINA &= B00000100 // A2
#define ADF_DR25 PINA &= B00001000 // A3
#define ADF_DR26 PINA &= B00010000 // A4
#define ADF_DR27 PINA &= B00100000 // A5
#define ADF_DR28 PINA &= B01000000 // A6
#define ADF_DR29 PINA &= B10000000 // A7
#define ADF_DR30 PINC &= B10000000 // C7
#define ADF_DR31 PINC &= B01000000 // C6
#define ADF_DR32 PINC &= B00100000 // C5
#define ADF_DR33 PINC &= B00010000 // C4
#define ADF_DR34 PINC &= B00001000 // C3
#define ADF_DR35 PINC &= B00000100 // C2
#define ADF_DR36 PINC &= B00000010 // C1
#define ADF_DR37 PINC &= B00000001 // C0
#define ADF_DR38 PIND &= B10000000 // D7
#define ADF_DR39 PING &= B00000100 // G2
#define ADF_DR40 PING &= B00000010 // G1
#define ADF_DR41 PING &= B00000001 // G0
#define ADF_DR42 PINL &= B10000000 // L7
#define ADF_DR43 PINL &= B01000000 // L6
#define ADF_DR44 PINL &= B00100000 // L5
#define ADF_DR45 PINL &= B00010000 // L4
#define ADF_DR46 PINL &= B00001000 // L3
#define ADF_DR47 PINL &= B00000100 // L2
#define ADF_DR48 PINL &= B00000010 // L1
#define ADF_DR49 PINL &= B00000001 // L0
#define ADF_DR50 PINB &= B00001000 // B3
#define ADF_DR51 PINB &= B00000100 // B2
#define ADF_DR52 PINB &= B00000010 // B1
#define ADF_DR53 PINB &= B00000001 // B0

#define ADF_DRA0  PINF &= B00000001 // F0
#define ADF_DRA1  PINF &= B00000010 // F1
#define ADF_DRA2  PINF &= B00000100 // F2
#define ADF_DRA3  PINF &= B00001000 // F3
#define ADF_DRA4  PINF &= B00010000 // F4
#define ADF_DRA5  PINF &= B00100000 // F5
#define ADF_DRA6  PINF &= B01000000 // F6
#define ADF_DRA7  PINF &= B10000000 // F7
#define ADF_DRA8  PINK &= B00000001 // K0
#define ADF_DRA9  PINK &= B00000010 // K1
#define ADF_DRA10 PINK &= B00000100 // K2
#define ADF_DRA11 PINK &= B00001000 // K3
#define ADF_DRA12 PINK &= B00010000 // K4
#define ADF_DRA13 PINK &= B00100000 // K5
#define ADF_DRA14 PINK &= B01000000 // K6
#define ADF_DRA15 PINK &= B10000000 // K7

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#elif PLATFORM == 13 // attiny13 (Attiny13)

//  pinMode(pin, INPUT);
#define ADF_PMI0 DDRB &= B11111110 // B0
#define ADF_PMI1 DDRB &= B11111101 // B1
#define ADF_PMI2 DDRB &= B11111011 // B2
#define ADF_PMI3 DDRB &= B11110111 // B3
#define ADF_PMI4 DDRB &= B11101111 // B4
#define ADF_PMI5 DDRB &= B11011111 // B5
//  pinMode(pin, OUTPUT);
#define ADF_PMO0 DDRB |= B00000001 // B0
#define ADF_PMO1 DDRB |= B00000010 // B1
#define ADF_PMO2 DDRB |= B00000100 // B2
#define ADF_PMO3 DDRB |= B00001000 // B3
#define ADF_PMO4 DDRB |= B00010000 // B4
#define ADF_PMO5 DDRB |= B00100000 // B5
//  pinMode(pin, INPUT_PULLUP);
#define ADF_PMIP0  DDRB &= B11111110; PORTB |= B00000001 // B0 0x1
#define ADF_PMIP1  DDRB &= B11111110; PORTB |= B00000010 // B1 0x2
#define ADF_PMIP2  DDRB &= B11111110; PORTB |= B00000100 // B2
#define ADF_PMIP3  DDRB &= B11111110; PORTB |= B00001000 // B3
#define ADF_PMIP4  DDRB &= B11111110; PORTB |= B00010000 // B4
#define ADF_PMIP5  DDRB &= B11111110; PORTB |= B00100000 // B5 0x20
//  digitalWrite(pin, HIGH);
#define ADF_DWH0  PORTB |= B00000001 // B0
#define ADF_DWH1  PORTB |= B00000010 // B1
#define ADF_DWH2  PORTB |= B00000100 // B2
#define ADF_DWH3  PORTB |= B00001000 // B3
#define ADF_DWH4  PORTB |= B00010000 // B4
#define ADF_DWH5  PORTB |= B00100000 // B5
//  digitalWrite(pin, LOW);
#define ADF_DWL0  PORTB &= B11111110 // B0
#define ADF_DWL1  PORTB &= B11111101 // B1
#define ADF_DWL2  PORTB &= B11111011 // B2
#define ADF_DWL3  PORTB &= B11110111 // B3
#define ADF_DWL4  PORTB &= B11101111 // B4
#define ADF_DWL5  PORTB &= B11011111 // B5
//  digitalRead(pin);
#define ADF_DR0  PINB &= B00000001 // B0
#define ADF_DR1  PINB &= B00000010 // B1
#define ADF_DR2  PINB &= B00000100 // B2
#define ADF_DR3  PINB &= B00001000 // B3
#define ADF_DR4  PINB &= B00010000 // B4
#define ADF_DR5  PINB &= B00100000 // B5

#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

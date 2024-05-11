#include <iostream>
#include <io.h>
#include <fcntl.h>

const unsigned char option1 = 0x01; // шестнадцатеричный литерал для 0000 0001
const unsigned char option2 = 0x02; // шестнадцатеричный литерал для 0000 0010
const unsigned char option3 = 0x04; // шестнадцатеричный литерал для 0000 0100
const unsigned char option4 = 0x08; // шестнадцатеричный литерал для 0000 1000
const unsigned char option5 = 0x10; // шестнадцатеричный литерал для 0001 0000
const unsigned char option6 = 0x20; // шестнадцатеричный литерал для 0010 0000
const unsigned char option7 = 0x40; // шестнадцатеричный литерал для 0100 0000
const unsigned char option8 = 0x80; // шестнадцатеричный литерал для 1000 0000

const unsigned char TWO_BYTES_UNICODE = 0xC0; // шестнадцатеричный литерал для 1100 0000
const unsigned char THREE_BYTES_UNICODE = 0xE0; // шестнадцатеричный литерал для 1110 0000
const unsigned char FOUR_BYTES_UNICODE = 0xF0; // шестнадцатеричный литерал для 1111 0000

const uint8_t ONE_BYTE = 0b0000'0000;

//const uint8_t ONE_BYTE_MASK = 0b0111'1111;

const uint16_t TWO_BYTE = 0b1100'0000;
/*
const uint16_t TWO_BYTE_FIRST_BYTE_MASK = 0b11111'000000;
const uint16_t TWO_BYTE_SECOND_BYTE_MASK = 0b000000'111111;
*/


// Если будут ошибки, надо будет добавить доп. нули в начале
const uint32_t THREE_BYTE =						0b1110'0000;
/*
const uint32_t THREE_BYTE_FISRT_BYTE_MASK =		0b1111'000000'000000;
const uint32_t THREE_BYTE_SECOND_BYTE_MASK =	0b0000'111111'000000;
const uint32_t THREE_BYTE_THIRD_BYTE_MASK =		0b0000'000000'111111;
*/

const uint32_t FOUR_BYTE = 0b1111'0000;


const uint8_t STANDART_BYTE = 0b1000'0000;
const uint8_t STANDART_BYTE_MASK = 0b0011'1111;

//using utf8 = unsigned char;


// Перевод символа в UTF-8
// TO-DO: Сделать прямой вывод hex кода


void PrintDecimalToUTF8(uint32_t decimal)
{
	using namespace std;

	int symbol_size = 0;

	// Расчитываем сколько байт
	// надо выделить на utf-8
	// Подробнее на https://en.wikipedia.org/wiki/UTF-8

	if (decimal > 0x10000)
		symbol_size = 4;
	else if (decimal > 0x800)
		symbol_size = 3;
	else if (decimal > 0x80)
		symbol_size = 2;
	else
		symbol_size = 1;

	// Выделяем память под Unicode
	uint8_t* utf = new uint8_t[symbol_size]{};

	// ПРЕОБРАЗОВЫВАЕМ ЧИСЛО В UTF-8
	
	if (symbol_size == 1)
	{
		utf[0] |= (decimal);
		cout << hex << "\\x" << static_cast<int>(utf[0]) << '\n';
	}
	else if (symbol_size == 2)
	{
		// 
		utf[0] = TWO_BYTE;
		// Поскольку на 2х байтов кодировке
		// присваемые числа имеют диапазон
		// от 128 до 2047 
		// от 0x80 до 7FF
		// от 1000 0000 до 111 1111 1111
		// Поэтому для получения левой части
		// мы сдвигаем число на 6 бит
		// например: 11111 111111 -> 11111


		utf[0] |= (decimal >> 6);

		utf[1] = STANDART_BYTE;
		utf[1] |= (decimal & STANDART_BYTE_MASK);

		cout << hex << "\\x" << static_cast<int>(utf[0]);
		cout << hex << "\\x" << static_cast<int>(utf[1]) << '\n';

	}
	else if (symbol_size == 3)
	{
		utf[0] = THREE_BYTES_UNICODE;
		utf[0] |= (decimal >> 12);

		utf[1] = STANDART_BYTE;
		utf[1] |= ( (decimal >> 6) & STANDART_BYTE_MASK);

		utf[2] = STANDART_BYTE;
		utf[2] |= (  decimal & STANDART_BYTE_MASK);

		cout << hex << "\\x" << static_cast<int>(utf[0]);
		cout << hex << "\\x" << static_cast<int>(utf[1]);
		cout << hex << "\\x" << static_cast<int>(utf[2]) << '\n';
	}
	else if (symbol_size == 4)
	{
		utf[0] = FOUR_BYTES_UNICODE;
		utf[0] |= (decimal >> 18);

		utf[1] = STANDART_BYTE;
		utf[1] |= ( (decimal >> 12) & STANDART_BYTE_MASK);

		utf[2] = STANDART_BYTE;
		utf[2] |= ( (decimal >> 6) & STANDART_BYTE_MASK);

		utf[3] = STANDART_BYTE;
		utf[3] |= (  decimal & STANDART_BYTE_MASK);


		cout << hex << "\\x" << static_cast<int>(utf[0]);
		cout << hex << "\\x" << static_cast<int>(utf[1]);
		cout << hex << "\\x" << static_cast<int>(utf[2]);
		cout << hex << "\\x" << static_cast<int>(utf[3]) << '\n';
	}

	// Освобождаем память
	delete[] utf;

}

// Перевод массива (строки) в UTF-8

int main()
{
	using namespace std;


	// 🙏 , ☭
	char32_t symbol = U'🙏';
	
	wchar_t ascii = L'A';
	wchar_t two_bytes = u'☭';
	wchar_t three_bytes = U'🙏';
	wchar_t four_bytes = U'𒉹';


	PrintDecimalToUTF8(5672);


	//unsigned short utf_array[] = '\xe2', '\x98', '\xad';


	cin.get();
}
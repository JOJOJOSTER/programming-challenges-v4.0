#include <iostream>

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

void toUTF8()
{

}


int main()
{
	using namespace std;

	wchar_t symbol = L'䜸';

	//Ввод

	// Конвертация в UTF-32

	cout << hex << "\\u" << static_cast<char32_t>(symbol) << endl;

	// Конвертация в UTF-16

	cout << hex << "u+" << static_cast<char16_t>(symbol) << endl;

	// Конвертация в UTF-8 (Тут надо поработать с бит)

	cout << hex << "u+" << static_cast<wchar_t>(symbol) << endl;



	cout << sizeof(symbol) << '\n';

	if (((symbol >> 8) & (option8 | option7)) == option8 | option7)
	{
		cout << "2 bytes unicode" << endl;
	}

	if (((symbol >> 16) & THREE_BYTES_UNICODE) == THREE_BYTES_UNICODE)
	{
		cout << "3 bytes unicode" << endl;
	}

	cout << hex << symbol << endl;

	cin.get();
}
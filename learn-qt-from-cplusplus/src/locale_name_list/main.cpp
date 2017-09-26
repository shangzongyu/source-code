#include <iostream>
#include <locale>
using namespace std;

char * loc_names [] = {
	"Afrikaans_South Africa.1252",
	"Albanian_Albania.1250",
	"Basque_Spain.1252",
	"Belarusian_Belarus.1251",
	"Serbian (Latin)",
	"Bulgarian_Bulgaria.1251",
	"Catalan_Spain.1252",
	"Croatian_Croatia.1250",
	"Chinese_China.936",
	"Chinese_Taiwan.950",
	"Czech_Czech Republic.1250",
	"Danish_Denmark.1252",
	"Dutch_Netherlands.1252",
	"English_Australia.1252",
	"Estonian_Estonia.1257",
	"Finnish_Finland.1252",
	"French_Canada.1252",
	"Galician_Spain.1252",
	"German_Germany.1252",
	"Greek_Greece.1253",
	"Hungarian_Hungary.1250",
	"Icelandic_Iceland.1252",
	"Indonesian_indonesia.1252",
	"Italian_Italy.1252",
	"Japanese_Japan.932",
	"Korean_Korea.949",
	"Lithuanian_Lithuania.1257",
	"Latvian_Latvia.1257",
	"Malay_malaysia.1252",
	"Norwegian_Norway.1252",
	"Norwegian-Nynorsk_Norway.1252",
	"Polish_Poland.1250",
	"Portuguese_Portugal.1252",
	"Portuguese_Brazil.1252",
	"Romanian_Romania.1250",
	"Russian_Russia.1251",
	"Slovak_Slovakia.1250",
	"Slovenian_Slovenia.1250",
	"Spanish_Spain.1252",
	"Swedish_Sweden.1252",
	"English_Australia.1252",
	"Turkish_Turkey.1254",
	"Ukrainian_Ukraine.1251",
};

int main()
{
	for (int i=0; i<sizeof(loc_names)/sizeof(char*); i++){
		locale * p = new locale(loc_names[i] );
		cout << p->name() << endl;
		delete p;
	}
}
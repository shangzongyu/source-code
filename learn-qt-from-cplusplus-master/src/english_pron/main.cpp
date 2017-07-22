#include <QString>
#include <QVector>
#include <QMap>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
using namespace std;

typedef QVector< QVector<QString> >		  wlist_type;
typedef QMap< QString, QString >		  table_type;
typedef QMap< QString, QVector<QString> > dict_type;

QTextStream  cout(stdout, QIODevice::WriteOnly); 


int load_word_list( wlist_type & word_list, char * fname)
{
	QFile listf(fname);
	if (!listf.open(QIODevice::ReadOnly| QIODevice::Text)) return -1;
	QTextStream ts( & listf );
	
	while ( !ts.atEnd() ) {
		QString line = ts.readLine();
		QTextStream iss( & line );
		
		QString word;
		QVector <QString> words;
		while (! iss.atEnd() ) {
			iss >> word;
			if ( word[0] == '#' ) break;	
			word = word.toLower();
			words.push_back( word );
		}
		if ( words.size() )
			word_list.push_back( words );
	}
	cout << fname << " loaded. " << endl;
	return 0;
}

int load_table( table_type & table, char * fname)
{
	QFile f(fname);
	if ( !f.open(QIODevice::ReadOnly| QIODevice::Text)) return -1;
	f.seek(3);
	QTextStream ts(&f);

	while ( !ts.atEnd() ) {
		QString phone_name, ipa_symbol;
		ts >> phone_name >> ipa_symbol;
		table[phone_name] = ipa_symbol;
	}
	cout << fname << " loaded" << endl;
	return 0;
}

int load_dict( dict_type & dict, char * fname)
{
	QFile dictf(fname);
	if ( !dictf.open(QIODevice::ReadOnly| QIODevice::Text)) return -1;
	QTextStream ts(&dictf);

	while ( !ts.atEnd() ) {
		QString line = ts.readLine();
		QTextStream iss( &line );
		
		QString word, phone;
		QVector <QString> pron;
		iss >> word;
		word = word.toLower();

		while ( ! iss.atEnd() ) {
			iss >> phone;
			if ( phone == "sp" ) break;
			pron.push_back( phone );
		}
		dict[word]=pron;
		
		static int cnt=0;
		if ( cnt++ % 10000 == 0 ) {
			cout<< ".";    cout.flush();
		}
	}
	cout << fname << " loaded\n";	
	return 0;
}

int save_dict_map( dict_type & dict, char * fname)
{
	QFile dictf(fname);
	if ( !dictf.open(QIODevice::WriteOnly)) return -1;
	QDataStream ds(&dictf);
	ds << dict;
	cout << fname << " saved\n";
	return 0;
}

int load_dict_map( dict_type & dict, char * fname)
{
	QFile dictf(fname);
	if ( !dictf.open(QIODevice::ReadOnly)) return -1;
	QDataStream ds(&dictf);
	ds >> dict;
	cout << fname << " loaded\n";
	return 0;
}

int gen_word_pron( wlist_type & word_list, dict_type & dict, table_type & table, char * fname)
{
	QFile outf(fname);
	if ( !outf.open(QIODevice::WriteOnly | QIODevice::Text) ) return -1;
	QTextStream ts( & outf );

	for (int i=0; i<word_list.size(); i++) {
		QVector<QString> words = word_list[i];
		for (int j=0; j<words.size(); j++){
			QString word = words[j];
			QVector<QString> pron = dict[word];
			ts << qSetFieldWidth(10) << left << word <<
				qSetFieldWidth(0) << " [ ";
			for (int k=0; k<pron.size(); k++)
				ts << table[ pron[k] ] << " ";
			ts << " ]" << endl;
		}
		if ( i%5 ==4) ts << endl;
	}
	cout << fname << " generated. " << endl;
	return 0;
}



int main(int argc, char * argv[])
{
	if ( argc != 3 ) {
		cout << "Usage: english_pron  input  output\n";
		exit(-1);
	}
	wlist_type word_list;
	load_word_list( word_list, argv[1]);

	table_type table;
	load_table( table, "ascii_to_ipa.txt");
	
	dict_type dict;
//#define SLOW
#ifdef  SLOW
	load_dict( dict,  "dict.txt" );
	save_dict_map( dict,  "dict.bin" );
#else
	load_dict_map( dict,  "dict.bin" );
#endif

	gen_word_pron( word_list, dict, table, argv[2] );
}
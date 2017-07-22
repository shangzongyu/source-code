#include <QFile>
#include <QLocale>
#include <QDebug>
#include <QDate>
#include <QTime>

int main(int argc, char *argv[])
{
	QLocale locale[4] = {
		QLocale(QLocale::Chinese),  QLocale(QLocale::English), 
		QLocale(QLocale::German),   QLocale(QLocale::Japanese) 
	};
	
	QFile dest_f("output.txt");
	if (!dest_f.open(QIODevice::WriteOnly )) return -1;

	for ( int i=0; i<4; i++) {
		QString country   = QLocale::countryToString( locale[i].country() );
		QString date_time = locale[i].toString( QDateTime( QDate(2010,12,8), QTime(11,49) ) ); 
		QString str =  country + ":"; 
		str += date_time;  str+="\n";
		dest_f.write((char*)str.data(), str.length()*sizeof(QChar));

		for (int j=0; j<10; j++) 
			if ( locale[i].test_data[j]!=0) {
				qDebug() << "locale[ " << i << "] data is corrupted\n";
				break;
			}
	}
	qDebug() << "date_time written" << endl;	
}

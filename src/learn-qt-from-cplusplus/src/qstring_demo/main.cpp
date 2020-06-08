#include <QTextStream>
#include <QString>
#include <string>

QTextStream cin(stdin, QIODevice::ReadOnly);
QTextStream cout(stdout, QIODevice::WriteOnly);
void display_data( char * buff, unsigned len )
{
for (int i=0; i<len; i++)
			cout << hex << showbase << uppercasedigits << (unsigned char)buff[i] << " ";
		cout << endl;
}
int main(int argc, char *argv[ ])
{
	    char * buff =  "中文";			
		display_data( buff, strlen(buff) );	 				//0xD6 0xD0 0xCE 0xC4

		std::wstring ws  = L"中文";	 
		display_data( (char*) ws.data(), ws.length() * 2 );		//0x2D 0x4E 0x87 0x65

		QString  qs	=	"中文";		
		display_data( (char*) qs.data(),  qs.length() * 2  );	//0xD6 0x0 0xD0 0x0 0xCE 0x0 0xC4 0x0

		QString  qs2 	=  QString::fromLocal8Bit("中文");	
		display_data( (char*) qs2.data(), qs2.length() * 2 ); 	//0x2D 0x4E 0x87 0x65
}

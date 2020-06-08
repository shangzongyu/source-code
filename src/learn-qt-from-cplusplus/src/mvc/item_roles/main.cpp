#include "NewsDialog.h"
#include <qtextcodec.h> 


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312")) ;
	
	NewsDialog dialog;
	dialog.resize(900, 600);
	dialog.show();
	
	return a.exec();
}


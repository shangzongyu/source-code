#include <QDir>
#include <QFileInfo>
#include <QDebug>
int main()
{
	foreach( QFileInfo drive, QDir::drives() ){
		qDebug() << "Drive: " << drive.absolutePath();
		QDir dir = drive.dir();
		dir.setFilter( QDir::Dirs );
		foreach( QFileInfo rootDirs, dir.entryInfoList() )
			qDebug() << " " << rootDirs.fileName();
	}
	return 0;
}
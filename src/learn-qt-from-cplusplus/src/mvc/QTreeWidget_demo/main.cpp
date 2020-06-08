#include <QtGui>

typedef struct {
	char * sect_id, * title, * page_num;
	char * parent_id;
} SectionInfo;
SectionInfo directory[] = {
	{"Chapter 1",	  "The Prehistory of C++",			"19",	""},
	{"Chapter 2",	  "C with Classes",					"27",	""},
	{"Chapter 3",	  "The Birth of C++",				"63",	""},
	{"Chapter 4",	  "C++ Language Design Rules",		"109",	""},
	{"Section 1.1",   "Simula and Distributed Systems",	"19",	"Chapter 1"},
	{"Section 1.2",   "C and Systems Programming",		"22",	"Chapter 1"},
	{"Section 1.3",   "General Background",				"23",	"Chapter 1"},
	{"Section 2.1",   "The Birth of C with Classes",	"27",	"Chapter 2"},
	{"Section 2.2",   "Feature overview",				"29",  	"Chapter 2"},
	{"Section 2.3",	  "Classes",						"30",  	"Chapter 2"},
	{"Section 2.4",   "Run-Time Efficiency",			"32",  	"Chapter 2"},
	{"Section 2.4.1", "Inlining",						"33",  	"Section 2.4"},
};

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QTreeWidget * treeWidget = new QTreeWidget();
	treeWidget->setColumnCount(3);
	QStringList headers;
	headers << "Section Number" << "Title" << "Page Number";
	treeWidget->setHeaderLabels(headers);

	for (int i=0; i<sizeof(directory)/sizeof(directory[0]);  i++) {
		SectionInfo info = directory[i];
		QTreeWidgetItem * item=NULL;
		if (strcmp(info.parent_id, "")==0 ){
			item = new QTreeWidgetItem(treeWidget);
		}else{
			QString parent_id(info.parent_id);
			QTreeWidgetItemIterator  it (treeWidget);
			while ( (*it)->text(0) != parent_id)
				 ++it;
			item = new QTreeWidgetItem( *it );
		}
		if ( item) {
			item->setText(0, info.sect_id);
			item->setText(1, info.title  );
			item->setText(2, info.page_num);
		}
	}
	
	treeWidget->resize(400,200);
	treeWidget->show();
	return app.exec();
}

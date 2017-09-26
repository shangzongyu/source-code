#include <QtGui/QApplication>
#include <QtGui/QTableWidget>

typedef struct {
	char * country;
	double GDP, population;
}GDP_FACTS; 

GDP_FACTS GDP_facts[] = {
	{"United States",  14.6,   2.7  },
	{"PRC China",	    6.1,  13.0  },
	{"Japan",		    5.4,   1.3  },
	{"Germany",		    3.3,   0.8  },
	{"United Kingdom",  2.3,   0.6  }
};

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	const int rows=5, columns=4;
	QTableWidget widget(rows, columns);
	QStringList list;
	list << "Country" << "Grand GDP" << "Population" << "GDP per person";
	widget.setHorizontalHeaderLabels(list);

	for (int row=0; row<rows; row++) {
		QTableWidgetItem * items[columns];
		for (int j=0; j<columns; j++ ) {
			items[j] = new QTableWidgetItem();
			items[j]->setTextAlignment( Qt::AlignHCenter);
			QFont font;	font.setPointSize(16);
			items[j]->setFont( font );
		}			
		GDP_FACTS * p = & GDP_facts[row];		
		items[0]->setData(Qt::DisplayRole, p->country );
		items[1]->setData(Qt::DisplayRole, p->GDP );
		items[2]->setData(Qt::DisplayRole, p->population );
		items[3]->setData(Qt::DisplayRole, p->GDP / p->population );
		for (int j=0; j<columns; j++ )
			widget.setItem(row, j, items[j] );
	}
	widget.setSortingEnabled(true );

	widget.resize(800, 300);
	widget.show();
	return app.exec();
}

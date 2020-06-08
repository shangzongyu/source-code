#include <QtCore/QCoreApplication>
#include <QVector>
#include <QString>
#include <QList>
#include <cassert>
#include <fstream>
#include <cctype>
#include <QtAlgorithms>
#include <QTextStream>

struct IndirectCompare {
	IndirectCompare(const QVector<QString>& v1) : v(v1)
	{}
	bool operator()( int x, int y) const {
		return v[x] < v[y];
	}
	bool operator()( int x, const QString & a) const {
		return v[x] < a;
	}
	bool operator()(const QString& a,  int x) const {
		return a < v[x];
	}
	const QVector<QString>& v;
};

void readRoget(QVector<QString> & words,
			   QVector<QList<int> >& lists) {
	std::ifstream source("data\\roget.dat");
	assert(source); // let¡¯s play it safe!
	const int maxBuf = 200;
	char buf[maxBuf];
	char c;
	size_t i;
	while(source.get(c)) {
	   if(c =='*') // skip line
		   source.ignore(1000,'\n');
	   else
		   if(std::isdigit(c)) {
			   source.putback(c);
			   source >> i; // current no.
			   source.getline(buf, maxBuf, ':'); // word
			   words[--i] = buf;
			   while(source.peek() != '\n') {
				   int j;
				   source >> j;
				   lists[i].push_front(--j);
				   if(source.peek() == '\\')
					   source.ignore(1000,'\n');
			   }
		   }
	}
}

QTextStream cout(stdout, QIODevice::WriteOnly);
QTextStream cin(stdin, QIODevice::ReadOnly);
int main(int argc, char *argv[])
{
	const int maxi = 1022; // number of entries in roget.dat
	QVector<QString> words(maxi);
	QVector<QList<int> > relatedWords(maxi);
	QVector<int> index(maxi);

	readRoget(words,relatedWords);
	for(size_t i = 0; i < index.size(); ++i)
		index[i] = i;
	IndirectCompare aComparison(words); // functor
	qSort(index.begin(), index.end(), aComparison);

	for (int i=0; i<maxi; i++) {
		if ( i > 4 && i < maxi - 3 ) continue;				
		cout << index[i] << " ==> " << words[ index[i] ] << endl;
	}
	cout << "Search term? " << endl;	
	QString searchTerm = cin.readLine();

	// binary search
	QVector<int>::const_iterator tableEnd = index.end();
	QVector<int>::const_iterator lbound   = qLowerBound(index.begin(), index.end(),
		searchTerm, aComparison);
	bool found = true; // hypothesis to be checked
	if(lbound == tableEnd)
		found = false;
	else {
		size_t i = 0;
		while(i < words[*lbound].length()
			&& i < searchTerm.length()
			&& found)
			if(words[*lbound][i] != searchTerm[i])
				found = false;
			else ++i;
	}
	
	if(found) {
		cout << "found : "
			<< words[*lbound] << endl
			<< "related words:\n";
		QList<int>::const_iterator
			atEnd = relatedWords[*lbound].end(),
			here = relatedWords[*lbound].begin();
		if(here == atEnd)
			cout << "not found\n";
		else
			while(here != atEnd)
				cout << '\t' << words[*here++] << endl;
	}
	else cout << "not found\n";
}

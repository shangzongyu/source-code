#include <QSharedData>
#include <QString>
#include <QTextStream>
QTextStream cout( stdout, QIODevice::WriteOnly);

class HealthData : public QSharedData {
  public:
    ~HealthData() { }
    QString weight,blood_pressure;
};

class Health{
  public:
    Health() { 
		d = new HealthData;   //?operator overloading
		setStatus("Normal", "Normal");
	 }
	 void setStatus(QString _weight="Normal", QString _blood_pressure="Normal") {
        d->weight = _weight;
		d->blood_pressure = _blood_pressure;
    }
    QString weight() const { return d->weight; }
    QString blood_pressure() const { return d->blood_pressure; }

  private:
    QSharedDataPointer<HealthData> d;
};

int main()
{
	Health p1;
	Health p2(p1), p3(p1);
	p3.setStatus( "Too fat. Should keep fit.");
	return 0;
 }


#include <iostream>
#include <locale>
#include <string>
using namespace std;

class Unit: public locale::facet {
public:
	static locale::id id;   //1
	
	Unit(string _weight, string _volume, string _distance){
		weight   = _weight;    volume = _volume;  
		distance = _distance;
	}
	string get_weight() const  { return weight; }   //2
	string get_volume() const  { return volume; }
	string get_distance() const { return distance; }
private:
	Unit(Unit&);       //3 and its normal constructor    
	void operator=(Unit&);  

	string weight, volume, distance;
};

locale::id Unit::id;  //4

int main()
{
	locale  loc( locale(), new Unit("pound", "gallon", "mile") );
	const Unit & unit = use_facet<Unit>(loc);  //5
	cout << unit.get_weight() << " " << unit.get_volume() << " " << unit.get_distance();
}


#include <iostream>
#include <float.h>
using namespace std;

template <typename numT>
struct fp_traits { };

template<>
struct fp_traits<float> {
	typedef float fp_type;
	enum { max_exponent = FLT_MAX_EXP };
	static inline fp_type epsilon()
	{ return FLT_EPSILON; }
};

template<>
struct fp_traits<double> {
	typedef double fp_type;
	enum { max_exponent = DBL_MAX_EXP };
	static inline fp_type epsilon()
	{ return DBL_EPSILON; }
};

template <typename numT>
class matrix {
public:
	typedef numT num_type;
	typedef fp_traits<num_type> num_type_info;
	inline num_type epsilon()
	{return num_type_info::epsilon();}
	//...
};

int main()
{
	matrix <float>  fm;
	matrix <double> dm;
	cout << "float  matrix: " << fm.epsilon() << endl;
	cout << "double matrix: " << dm.epsilon() << endl;
}
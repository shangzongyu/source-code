/**************************************************
 * Essential C++ -- Stanley Lippman
 * Addison-Wesley 
 * ISBN 0-201-48518-4
 * homepage: www.objectwrite.com
 * email: slippman@objectwrite.com
 *************************************************/

#ifndef CH1_H_
#define CH1_H_

#include <vector>
#include <iostream>
#include <string>
using namespace std;

// external type definitions
typedef const vector<unsigned int>* (*pfunc)(int);
typedef const vector<unsigned int>*   pvec;

enum num_sequence { ns_unk,
     ns_fib, ns_pell, ns_lucas, ns_tri, ns_sq, ns_pent,
	 ns_cnt = 6, ns_wrong_msg = 4
};

struct user_profile {
	string       name;
	int          guesses;
	int          correct;
	int          level;

    num_sequence cur_seq;
	pvec         cur_seq_vec;
	int          pos;
};
           
// external structures
extern pfunc       gen_elems[];
extern const char *name_seq[]; 
extern const char *wrong_msg[];
extern int         level_size[];

extern bool greet_user( user_profile* );
extern void play_game( user_profile* );
extern void display_statistics( user_profile* );

extern pvec Fibonacci_gen_elems( int ); 
extern pvec Pell_gen_elems( int );     
extern pvec Lucas_gen_elems( int ); 
extern pvec Triangular_gen_elems( int ); 
extern pvec Square_gen_elems( int ); 
extern pvec Pentagonal_gen_elems( int ); 

extern void        set_seq( user_profile*, int );
extern const char* seq_id( user_profile* );
extern void        init_user( user_profile *puser, const string& nm, int level );
extern bool        correct_guess( user_profile *puser, int guess );

inline void set_seq_vec( user_profile *pu, pvec p ) { pu->cur_seq_vec = p; }
inline pvec seq_vec( user_profile *pu ) { return pu->cur_seq_vec; }

inline string 
user_name( user_profile *puser )
		{ return puser->name; }

inline num_sequence 
seq( user_profile *puser )
		{ return puser->cur_seq; }

inline void 
bump_guess( user_profile *puser )
		{ ++puser->guesses; }

inline void 
bump_correct( user_profile *puser )
{
	bump_guess( puser );
	++puser->correct;
}

#include <cstdlib>
inline num_sequence 
gen_seq_id( unsigned int ui )
{
	srand( ui++ );
	return static_cast<num_sequence>( ( rand() % ns_cnt ) + 1 );
}

inline void trace( const string& where, const string& msg, const string& data )
{
	 cerr << where << " " << msg << " " << data << endl;
}

inline void trace( const string& where, const string& msg, int val )
{
	 cerr << where << " " << msg << " " << val << endl;
}

inline void trace( const string& where, const string& msg, int val, int val2 )
{
	 cerr << where << " " << msg << " " << val << ' ' << val2 << endl;
}

inline void trace( const string& where, int val1, int val2 )
{
	 cerr << where << " " << val1 << " " << val2 << endl;
}

inline bool 
check_integrity( int pos ) 
{
	const int max_elems = 512;

	if ( pos <= 0 || pos > max_elems )
	{
		 cerr << "!! invalid position: " << pos
			  << " Cannot honor request\n";

		 return false;
	}

	return true;
}

inline num_sequence check_sequence( int id )
{
	if ( id <= 0 || id > ns_cnt )
	{
		 cerr << "!! invalid sequence value: " << id
			  << " Choosing one at random\n";

		 id = ( id % ns_cnt ) + 1;
	}

    return static_cast<num_sequence>( id );
}

#endif
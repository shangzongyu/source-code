/**************************************************
 * Essential C++ -- Stanley Lippman
 * Addison-Wesley 
 * ISBN 0-201-48518-4
 * homepage: www.objectwrite.com
 * email: slippman@objectwrite.com
 *************************************************/

#ifndef STACK_H_
#define STACK_H_

class Stack {
public:  
   
	bool   push( const string& );
    bool   pop(  string &elem );
	bool   peek( string &elem );

	bool   empty();
	bool   full();

   // definition of size() is placed within class
   // other members are simply declared ...
	int    size() { return _stack.size(); }
private:
	vector<string> _stack;
};

void fill_stack( Stack &stack, istream &is = cin )
{
    string str;
    while ( is >> str && ! stack.full() )
            stack.push( str );

    cout << "Read in " << stack.size() << " elements\n";
}

inline bool
Stack::empty()

{ 
    return _stack.empty(); 
}

bool
Stack::pop( string &elem ) 
{
    if ( empty() )
         return false;

    elem = _stack.back();
    _stack.pop_back(); 
    
    return true;
}

inline bool
Stack::full()
{ 
    return _stack.size() == _stack.max_size(); 
}

bool
Stack::peek( string &elem ) 
{
    if ( empty() )
         return false;

    elem = _stack.back();
    return true;
}
bool
Stack::push( const string &elem ) 
{
    if ( full() )
         return false;

    _stack.push_back( elem );
    return true;
}

#endif
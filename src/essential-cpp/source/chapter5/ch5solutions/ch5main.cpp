/**************************************************
 * Essential C++ -- Stanley Lippman
 * Addison-Wesley 
 * ISBN 0-201-48518-4
 * homepage: www.objectwrite.com
 * email: slippman@objectwrite.com
 *************************************************/

#include <string>
#include <iostream>
#include <vector>

using namespace std;

typedef string elemType;

class Stack {
public:
    virtual ~Stack(){}
    virtual bool pop( elemType& ) = 0;
    virtual bool push( const elemType& ) = 0;
    virtual bool peek( int index, elemType& ) = 0;
	virtual int  top() const = 0;
    virtual int  size() const = 0;
    virtual bool empty() const = 0;
    virtual bool full() const = 0;
    virtual void print( ostream& =cout ) const = 0;
};

ostream& operator<<( ostream &os, const Stack &rhs )
		{ rhs.print(); return os; }

class LIFO_Stack : public Stack {
public:
	LIFO_Stack( int capacity = 0 ) 
      : _top( 0 ){ _stack.reserve( capacity ); }

   int  size()  const { return _stack.size(); }
   bool empty() const { return ! _top; }
   bool full()  const { return size() >= _stack.max_size(); }
   
   int  top() const { return _top; }
   bool pop( elemType &elem ){
        if ( empty() )
             return false;

        elem = _stack[ --_top ];
        _stack.pop_back();
        return true;
   }

   bool peek( int, elemType& ){
        return false; } // don’t support this ...

   bool push( const elemType &elem ){
         if ( ! full() ){
              _stack.push_back( elem );
              ++_top;
              return true;
			}
         return false;
   }

   void print( ostream &os=cout )const
   {
	    vector<elemType>::const_reverse_iterator 
		      rit = _stack.rbegin(), 
              rend = _stack.rend();

		os << "\n\t";
	    while ( rit != rend )
		    os << *rit++ << "\n\t";
        os << endl;
   }
private:
   vector< elemType > _stack;
   int _top;
};

class Peekback_Stack : public Stack {
public:
	Peekback_Stack( int capacity = 0 ) 
      : _top( 0 ){ _stack.reserve( capacity ); }

   int  size()  const { return _stack.size(); }
   bool empty() const { return ! _top; }
   bool full()  const { return size() >= _stack.max_size(); }
   int  top() const { return _top; }  

   bool pop( elemType &elem ){
        if ( empty() )
             return false;

        elem = _stack[ --_top ];
        _stack.pop_back();
        return true;
   }

   bool push( const elemType &elem ){
         if ( ! full() ){
              _stack.push_back( elem );
              ++_top;
              return true;
			}
         return false;
   }

   bool peek( int index, elemType &elem );
   void print( ostream &os=cout ) const
   {
	    vector<elemType>::const_reverse_iterator 
		    rit = _stack.rbegin(), 
           rend = _stack.rend();

		os << "\n\t";
	    while ( rit != rend )
		    os << *rit++ << "\n\t";
        os << endl;
   }
private:
   vector< elemType > _stack;
   int _top;
};

bool Peekback_Stack::
peek( int index, elemType &elem ){
    if ( empty() )
         return false;

    if ( index < 0 || index >= size() )
         return false;

    elem = _stack[ index ];
    return true;
}

void peek( Stack &st, int index )
{
	cout  << endl;
	string t;
	if ( st.peek( index, t ))
	     cout << "peek: " << t;
	else cout << "peek failed!";
	cout << endl;
}

void ex5_1()
{
	/*
	once upon a time
	About to call peek() with LIFO_Stack  
    peek failed!

        time
        a
        upon
        once

    About to call peek() with Peekback_Stack
    peek: once

        once
        upon
        a
        time
	*/

	LIFO_Stack st;
	string str;

	cout << "Please enter a series of strings.\n";

	while ( cin >> str && ! st.full() )
		    st.push( str );

	cout << endl << "About to call peek() with LIFO_Stack" << endl;
	peek( st, st.top()-1 );
	cout << st;

    Peekback_Stack pst;
    while ( ! st.empty() ) {
		string t;
		if ( st.pop( t ))
		     pst.push( t );
	}

	cout << "About to call peek() with Peekback_Stack" << endl;	        
	peek( pst, pst.top()-1 );
	cout << pst;
}

// NOTE: the reimplementation requested of 5.2
//       is not included -- see Appendix text ...

int main()
{
	ex5_1();
}
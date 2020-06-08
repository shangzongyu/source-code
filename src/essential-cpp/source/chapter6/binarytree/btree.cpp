/**************************************************
 * Essential C++ -- Stanley Lippman
 * Addison-Wesley 
 * ISBN 0-201-48518-4
 * homepage: www.objectwrite.com
 * email: slippman@objectwrite.com
 *************************************************/

#include <iostream>
#include <vector>
using namespace std;

template <typename elemType>
class BinaryTree;

template <typename elemType>
class BTnode;

template <typename valType>
ostream&
foo( ostream &os, const BTnode<valType> &bt );

template <typename valType>
class BTnode {
	friend class BinaryTree<valType>;
	friend ostream& 
           // foo<valType>( ostream&, const BTnode<valType>& );
	          foo( ostream&, const BTnode<valType>& );
public:
    BTnode( const valType &val );
    
    const valType& value() const { return _val; }
	int            occurs() const{ return _cnt; }

	void           remove_value( const valType&, BTnode*& );
    void           insert_value(  const valType& );
	bool           find_value(  const valType& ) const;

    void preorder ( BTnode*, ostream& ) const;
    void inorder  ( BTnode*, ostream& ) const;
    void postorder( BTnode*, ostream& ) const;
                        
	static void lchild_leaf( BTnode *leaf, BTnode *subtree );
private:
    int         _cnt; // occurrence count
    valType     _val;
    BTnode     *_lchild;
    BTnode     *_rchild;

	void        display_val( BTnode *pt, ostream &os ) const;
	            BTnode( const BTnode& );
	BTnode&     operator=( const BTnode& );
};

template <typename valType>
inline 
BTnode<valType>::
BTnode( const valType &val )
    : _val( val )
{ 
	_cnt = 1;
	_lchild = _rchild = 0; 
}

template <typename valType>
void 
BTnode<valType>::
insert_value( const valType &val )
{
    if ( val == _val )
    { 
		_cnt++;

(*BinaryTree<valType>::os()) << "BTnode::insert_value: increment count( " 
                             << val << " : " << _cnt << " )\n";

		return; 
	}

	if ( val < _val ){
		if ( ! _lchild ){
             _lchild = new BTnode( val );
(*BinaryTree<valType>::os()) << "ok: BTnode::insert_value at left child( " << val << " )\n";		 
		}
		else _lchild->insert_value( val );
	}
	else {
		if ( ! _rchild ){
             _rchild = new BTnode( val );
(*BinaryTree<valType>::os()) << "ok: BTnode::insert_value at right child( " << val << " )\n";		 
		}
		else _rchild->insert_value( val );
	}
}

template <typename valType>
bool 
BTnode<valType>::
find_value( const valType &val ) const
{
    if ( val == _val )
       return true; 

	if ( val < _val ){
		if ( ! _lchild )
			 return false;
		else return _lchild->find_value( val );
	}
	else {
		if ( ! _rchild )
			 return false;
		else return _rchild->find_value( val );
	}
}

template <typename valType>
void 
BTnode<valType>::
lchild_leaf( BTnode *leaf, BTnode *subtree ) 
{
    while ( subtree->_lchild )
           subtree = subtree->_lchild;
    subtree->_lchild = leaf;         
}

template <typename valType>
void 
BTnode<valType>::
remove_value( const valType &val, BTnode *&prev ) 
{
    if ( val < _val )
    {
         if ( ! _lchild )
              return; // not present
         else _lchild->remove_value( val, _lchild );
    } 
    else 
    if ( val > _val )
    {
         if ( ! _rchild )
              return; // not present
         else _rchild->remove_value( val, _rchild );
    } 
    else 
    { // ok: found it
      // reset the tree then delete this node
      if ( _rchild ) 
      {
         prev = _rchild;
         if ( _lchild )
			  if ( ! prev->_lchild )
				   prev->_lchild = _lchild;
			  else BTnode<valType>::lchild_leaf( _lchild, prev->_lchild );
      }
      else prev = _lchild;
      delete this;
    }         
}

template <typename valType>
inline void BTnode<valType>::
display_val( BTnode *pt, ostream &os ) const
{
       os << pt->_val;
       if ( pt->_cnt > 1 )
            os << "( " << pt->_cnt << " ) "; 
       else os << ' ';
}

template <typename valType>
void BTnode<valType>::
preorder( BTnode *pt, ostream &os ) const
{
    if ( pt )
	{
       display_val( pt, os );
   	   if ( pt->_lchild ) preorder( pt->_lchild, os );
	   if ( pt->_rchild ) preorder( pt->_rchild, os );
	}
}

template <typename valType>
void BTnode<valType>::
inorder( BTnode *pt, ostream &os ) const
{
    if ( pt )
	{
	    if ( pt->_lchild ) inorder( pt->_lchild, os );
		display_val( pt, os );
		if ( pt->_rchild ) inorder( pt->_rchild, os );
	}
}

template <typename valType>
void BTnode<valType>::
postorder( BTnode *pt, ostream &os ) const
{
    if ( pt )
	{
		if ( pt->_lchild ) postorder( pt->_lchild, os );
        if ( pt->_rchild ) postorder( pt->_rchild, os );
		display_val( pt, os );
	}
}

template <typename elemType>
class BinaryTree {
public:
    BinaryTree();
	BinaryTree( const vector< elemType >& );
    BinaryTree( const BinaryTree& );
    ~BinaryTree();
    BinaryTree& operator=( const BinaryTree& );

	void insert( const vector< elemType >& );
    void insert( const elemType& );
    void remove( const elemType& );
    void clear(){ clear( _root ); _root = 0; }  // remove entire tree ...

	bool empty() { return _root == 0; }

	void inorder( ostream &os = *_current_os )   const { _root->inorder( _root, os ); }
    void postorder( ostream &os = *_current_os ) const { _root->postorder( _root, os ); }
    void preorder( ostream &os = *_current_os )  const { _root->preorder( _root, os ); }

    bool find( const elemType& ) const;
    ostream& print( ostream &os = *_current_os,
                    void (BinaryTree<elemType>::*traversal)( ostream& ) const =
                          &BinaryTree<elemType>::inorder ) const;

	static void current_os( ostream *os ){ if ( os ) _current_os = os;   }
	static ostream* os() { return _current_os; }

private:
	 BTnode<elemType> *_root;
	 static ostream   *_current_os; 

     // copy a subtree addressed by src to tar
     void copy( BTnode<elemType>*&tar, BTnode<elemType>*src );
     void clear( BTnode<elemType>* );
	 void remove_root(); 
};

template <typename elemType>
ostream *BinaryTree<elemType>::_current_os = &cout;

template <typename elemType>
inline 
BinaryTree<elemType>:: 
BinaryTree()
    : _root( 0 ){}

template <typename elemType>
inline 
BinaryTree<elemType>:: 
BinaryTree( const BinaryTree &rhs )
      { copy( _root, rhs._root ); }

template <typename elemType>
inline 
BinaryTree<elemType>:: 
~BinaryTree(){ clear(); }

template <typename elemType>
inline BinaryTree<elemType>& 
BinaryTree<elemType>::
operator=( const BinaryTree &rhs )
{ 
    if ( this != &rhs )
    {
	     clear();
         copy( _root, rhs._root ); 
    }
}

template <typename elemType>
inline void 
BinaryTree<elemType>::
insert( const elemType &elem ) 
{
    if ( ! _root ){
(*BinaryTree<elemType>::os()) << "BinaryTree::insert: root( " << elem << " )\n";
           _root = new BTnode<elemType>( elem );
	}
    else _root->insert_value( elem );
}

template <typename elemType>
BinaryTree<elemType>::	
BinaryTree( const vector< elemType > &vec )
{
	_root = 0;
    for ( int ix = 0; ix < vec.size(); ++ix )
		  insert( vec[ ix ] );
}

template <typename elemType>
void
BinaryTree<elemType>::	
insert( const vector< elemType > &vec )
{
    for ( int ix = 0; ix < vec.size(); ++ix )
		  insert( vec[ ix ] );
}

template <typename elemType>
inline void 
BinaryTree<elemType>::
remove( const elemType &elem ) 
{
    if ( _root )
    {
         if ( _root->_val == elem )
              remove_root();
         else _root->remove_value( elem, _root );
    }
}

template <typename elemType>
void 
BinaryTree<elemType>::
remove_root() 
{
    if ( ! _root ) return;
    BTnode<elemType> *tmp = _root;

    if ( _root->_rchild )
    {
        _root = _root->_rchild;
        BTnode<elemType> *lc = tmp->_lchild;
        BTnode<elemType> *newlc = _root->_lchild;

        // if left child of root is non-null
        // attach it as leaf to left subtree
        if ( lc )
			 if ( ! newlc )
				  _root->_lchild = lc;
			 else BTnode<elemType>::lchild_leaf( lc, newlc );
    }
    else _root = _root->_lchild;

    delete tmp;         
}

template <typename elemType>
void 
BinaryTree<elemType>::
clear( BTnode<elemType> *pt )
{
	if ( pt ){
		 clear( pt->_lchild );
		 clear( pt->_rchild );
		 delete pt;
	}
}

template <typename elemType>
ostream& 
BinaryTree<elemType>::
print( ostream &os,
       void (BinaryTree::*traversal)( ostream& ) const ) const
{
	(this->*traversal)( os );
	return os;
}

template <typename elemType>
inline ostream&
operator<<( ostream &os, const BinaryTree<elemType> &bt )
{
    os << "Tree: " << endl;
    bt.print( os, &BinaryTree<elemType>::inorder ); 
    return os;
}

template <typename elemType>
inline bool 
BinaryTree<elemType>::
find( const elemType &elem ) const
{
	return  ! _root 
		    ? false
			: _root->find_value( elem );
}

template <typename elemType>
void 
BinaryTree<elemType>::
copy( BTnode<elemType> *&tar, BTnode<elemType> *src )
{
    if ( src ) {
		 tar = new BTnode<elemType>( src->_val );
		 if ( src->_lchild ) copy( tar->_lchild, src->_lchild );
		 if ( src->_rchild ) copy( tar->_rchild, src->_rchild );
	}
}

#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

main() 
{
	/*
    BinaryTree< int > bt;

	bt.insert( 7 );
	bt.insert( 5 );
	bt.insert( 9 );
	bt.insert( 6 );
	bt.insert( 3 );
    */

	/*
	BinaryTree< string > bt;
	bt.insert( "Piglet" );
	bt.insert( "Pooh" );
	bt.insert( "Eeyore" );
	bt.insert( "Kanga" ); 
	bt.insert( "Tigger" );
	*/

	ofstream log( "logfile.txt" );
	if ( ! log ){
		 cerr << "error: unable to open file!\n";
		 return -1;
	}
	else BinaryTree<string>::current_os( &log );

	/*
	int ia[] = { 24, 18, 36, 12, 14, 8, 24, 1, 42, 24, 8, 8, 16, 55 };
	vector< int > ivec( ia, ia + 14 );
	BinaryTree<int> bt( ivec );

	log << "preorder traversal: \n";
    // cout << should see\n\t ";
	bt.preorder( log );

	bt.clear();
	log << "\nbt is now " << ( bt.empty() ? " empty! " : " oops -- not empty!" ) << endl;

	sort( ivec.begin(), ivec.end() );
	bt.insert( ivec );

	log << "\n\ninorder traversal:\n";
	bt.inorder( log );

	bt.insert( ivec );

	log << "\n\npostorder traversal:\n";
	bt.postorder( log );

	log << endl << endl;
    */

	BinaryTree<string> bt;
    bt.insert( "Piglet" );
    bt.insert( "Eeyore" );
	bt.insert( "Roo" );

	bt.insert( "Tigger" );
	bt.insert( "Chris" );
	bt.insert( "Pooh" );
	bt.insert( "Kanga" );

	log << "preorder traversal: \n";
	bt.preorder( log );

	log << "\n\nabout to remove root: Piglet\n";
	bt.remove( "Piglet" );

	log << "\n\npreorder traversal after Piglet removal: \n";
	bt.preorder( log );

	log << "\n\nabout to remove Eeyore\n";
	bt.remove( "Eeyore" );

	log << "\n\npreorder traversal after Piglet removal: \n";
	bt.preorder( log );

//	log << "\n\ninorder traversal:\n";
//	bt.inorder( log );

//	log << "\n\npostorder traversal:\n";
//	bt.postorder( log );
//
    return 0;
}

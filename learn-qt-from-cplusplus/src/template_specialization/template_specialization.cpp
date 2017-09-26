#include <vector> 
#include <deque> 
#include <list>
#include <string> 

template <typename T> 
class Stack {  // primary template class
  private: 
    std::vector<T> elems;   

  public: 
	void push(T const&) {
		  elems.push_back(elem);
	}
	void pop(){
		if (elems.empty()) return;
		elems.pop_back();
	}
	T top() const{
		if (elems.empty()) return;
		return elems.back(); 
	}
}; 

template<> 
class Stack<std::string> {  //fully specialization
  private: 
    std::deque<std::string> elems;  

  public: 
	void push(std::string const & elem) { 
		elems.push_back(elem);
	}
	void pop(){
		if (elems.empty()) return; 
		elems.pop_back();
	}
	std::string top() const{
		if (elems.empty()) return NULL;
		return elems.back();
	}
}; 

template <typename T>
class Stack<T*> {  //partially specialization
  private: 
    std::list<T*> list;  

  public: 
	void push(T* & elem) { 
		list.push_front(elem);
	}
	void pop(){
		if (list.empty()) return; 
		list.pop_front();
	}
	T* top() const{
		if (list.empty()) return NULL;
		return list.front();
	} 
}; 

int main( )
{
}
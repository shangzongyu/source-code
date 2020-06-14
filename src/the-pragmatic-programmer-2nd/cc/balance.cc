/***
 * Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
***/
/**
  * From "How to Balance Resources", C++ example of auto_ptr.
  */

#include <stdio.h>
#include <stl.h>

typedef struct {
  int i;
} Node;

// Include auto_ptr here, because the GCC 2.7 headers have it commented out

template <class X> class auto_ptr {
private:
  X* ptr;
  mutable bool owns;
public:
  typedef X element_type;
  explicit auto_ptr(X* p = 0)  : ptr(p), owns(p) {}
  auto_ptr(const auto_ptr& a)  : ptr(a.ptr), owns(a.owns) {
    a.owns = 0;
  }
  template <class T> auto_ptr(const auto_ptr<T>& a) __STL_NOTHROW
    : ptr(a.ptr), owns(a.owns) {
      a.owns = 0;
  }
 
  auto_ptr& operator=(const auto_ptr& a) __STL_NOTHROW {
    if (&a != this) {
      if (owns)
        delete ptr;
      owns = a.owns;
      ptr = a.ptr;
      a.owns = 0;
    }
  }
  template <class T> auto_ptr& operator=(const auto_ptr<T>& a) __STL_NOTHROW {
    if (&a != this) {
      if (owns)
        delete ptr;
      owns = a.owns;
      ptr = a.ptr;
      a.owns = 0;
    }
  }
  ~auto_ptr() {
    if (owns)
      delete ptr;
  }
 
  X& operator*() const __STL_NOTHROW { return *ptr; }
  X* operator->() const __STL_NOTHROW { return ptr; }
};


void doSomething(void) {
  
  Node *n = new Node;

  try {
    // do something
  }
  catch (...) {
    delete n;
    throw;
  }

  delete n;
}

void doSomething1(void) {
  
  Node n;
  n.i = 0;

  try {
    // do something
  }
  catch (...) {
    throw;
  }
}

// Wrapper class for Node resources
class NodeResource {
  Node *n;

 public:
  NodeResource() { n = new Node; }
  ~NodeResource() { delete n; }

  Node *operator->() { return n; }
};

void doSomething2(void) {
  
  NodeResource n;

  try {
    // do something
  }
  catch (...) {
    throw;
  }
}

void doSomething3(void) {
  auto_ptr<Node> p (new Node);

  // Access the Node as p->...
  
  // Node automatically deleted at end
}

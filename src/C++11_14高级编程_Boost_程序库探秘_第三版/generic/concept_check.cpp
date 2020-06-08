// Copyright (c) 2016
// Author: Chrono Law
#include <forward_list>

#include <std.hpp>
using namespace std;

#include <boost/concept_check.hpp>
using namespace boost;

///////////////////////////////////////

//template<typename T>
//T my_min(const T& l,const T& r)
//{
//    BOOST_CONCEPT_ASSERT((LessThanComparable<T>));
//    //BOOST_CONCEPT_ASSERT((SGIAssignable<T>));
//
//    return (l < r) ? l : r;
//}

#include <boost/concept/requires.hpp>

template<typename T>
BOOST_CONCEPT_REQUIRES(
((LessThanComparable<T>)),
 (T)                       )
my_min(const T& l,const T& r)
{
    return (l < r) ? l : r;
}

//template <typename I>
//BOOST_CONCEPT_REQUIRES(
//((Mutable_RandomAccessIterator<I>))
//((LessThanComparable<typename RandomAccessIterator<I>::value_type>)),
//(void)                     )
//_sort(I first, I last)
//{
//    std::stable_sort(first, last);
//}

///////////////////////////////////////

void case1()
{
    //complex<double> cp1, cp2;
    //my_min(cp1, cp2);

}

///////////////////////////////////////

void case2()
{
    BOOST_CONCEPT_ASSERT((UnaryFunction< negate<int>, int, int>));
    BOOST_CONCEPT_ASSERT((AdaptableUnaryFunction< negate<int>, int, int>));
    BOOST_CONCEPT_ASSERT((BinaryFunction< plus<int>,int, int, int>));

}

///////////////////////////////////////

template <typename I> 
void _sort(I first, I last)
{
    BOOST_CONCEPT_ASSERT((RandomAccessIterator<I>));
    std::stable_sort(first, last);
}

void case3()
{
    BOOST_CONCEPT_ASSERT((InputIterator<int*>));
    BOOST_CONCEPT_ASSERT((OutputIterator<int*, int>));
    BOOST_CONCEPT_ASSERT((RandomAccessIterator<int*>));

    assert((std::is_same<InputIterator<int*>::pointer,
                iterator_traits<int*>::pointer>::value));

    BOOST_CONCEPT_ASSERT((ForwardIterator<forward_list<int>::iterator>));
    BOOST_CONCEPT_ASSERT((Mutable_ForwardIterator<
                forward_list<int>::iterator>));

    typedef vector<int>::iterator I;
    BOOST_CONCEPT_ASSERT((BidirectionalIterator<I>));
    BOOST_CONCEPT_ASSERT((RandomAccessIterator<I>));

}

///////////////////////////////////////

#include <boost/iterator/iterator_concepts.hpp>

#include <boost/iterator/iterator_facade.hpp>

///////////////////////////////////////

template<typename T>
class vs_iterator :
        public boost::iterator_facade<
        vs_iterator<T>, T,
        boost::single_pass_traversal_tag>
{
public:
    typedef boost::iterator_facade<
        vs_iterator<T>, T,boost::single_pass_traversal_tag> super_type;
    typedef vs_iterator this_type;

    typedef typename super_type::reference reference;
    // using typename super_type::reference ;

private:
    std::vector<T> &v;
    size_t current_pos;
public:
    vs_iterator(vector<T> &_v, size_t pos = 0):
      v(_v), current_pos(pos)
    {}
    vs_iterator(this_type const& other):
        v(other.v), current_pos(other.current_pos)
    {}
    void operator=(this_type const& other)
    {
        this->v = other.v;
        this->current_pos = other.current_pos;
    }
private:
    friend class boost::iterator_core_access;

    reference dereference() const
    {   return v[current_pos]; }

    void increment()
    {   ++current_pos;  }

    bool equal(this_type const& other) const
    {   return this->current_pos == other.current_pos;}
};

void case4()
{
    using namespace boost_concepts;

    typedef vector<bool>::iterator I;

    BOOST_CONCEPT_ASSERT((ReadableIterator<I>));
    BOOST_CONCEPT_ASSERT((WritableIterator<I>));
    BOOST_CONCEPT_ASSERT((SwappableIteratorConcept<I>));
    BOOST_CONCEPT_ASSERT((RandomAccessTraversalConcept<I>));

    BOOST_CONCEPT_ASSERT((ReadableIterator<vs_iterator<int> >));
    BOOST_CONCEPT_ASSERT((WritableIterator<vs_iterator<int> >));
    BOOST_CONCEPT_ASSERT((SwappableIterator<vs_iterator<int>>));
    BOOST_CONCEPT_ASSERT((SinglePassIterator<vs_iterator<int> >));

    //BOOST_CONCEPT_ASSERT((LvalueIteratorConcept<I>));

}

///////////////////////////////////////

#include <boost/array.hpp>
#include <boost/circular_buffer.hpp>

void case5()
{
    BOOST_CONCEPT_ASSERT((Container<vector<int>>));
    BOOST_CONCEPT_ASSERT((RandomAccessContainer<vector<int>>));

    assert((std::is_same<vector<int>::value_type,
                Container<vector<int>>::value_type>::value));

    //BOOST_CONCEPT_ASSERT((Container<forward_list<int>>));
    //BOOST_CONCEPT_ASSERT((ForwardContainer<forward_list<int>>));

    //BOOST_CONCEPT_ASSERT((ReversibleContainer<forward_list<int>>));

    BOOST_CONCEPT_ASSERT((Container<boost::circular_buffer<int> >));

    //BOOST_CONCEPT_ASSERT((Container<boost::array<int> >));

    BOOST_CONCEPT_ASSERT((Sequence<vector<int>>));
    BOOST_CONCEPT_ASSERT((Sequence<deque<int>>));
    BOOST_CONCEPT_ASSERT((Sequence<list<int>>));

    BOOST_CONCEPT_ASSERT((FrontInsertionSequence<deque<int>>));
    BOOST_CONCEPT_ASSERT((BackInsertionSequence<list<int>>));

    BOOST_CONCEPT_ASSERT((AssociativeContainer<set<int>>));
    BOOST_CONCEPT_ASSERT((AssociativeContainer<map<int,int>>));
    BOOST_CONCEPT_ASSERT((MultipleAssociativeContainer<multimap<int,int>>));

    BOOST_CONCEPT_ASSERT((SimpleAssociativeContainer<set<int>>));
    BOOST_CONCEPT_ASSERT((SortedAssociativeContainer<set<int>>));

}

///////////////////////////////////////

#include <boost/range/concepts.hpp>

void case6()
{
    BOOST_CONCEPT_ASSERT((SinglePassRangeConcept<std::forward_list<int>>));
    BOOST_CONCEPT_ASSERT((ForwardRangeConcept<std::forward_list<int>>));

    BOOST_CONCEPT_ASSERT((BidirectionalRangeConcept<std::list<int>>));
    BOOST_CONCEPT_ASSERT((RandomAccessRangeConcept<std::vector<int>>));

    char a[] = "range";
    BOOST_CONCEPT_ASSERT((RandomAccessRangeConcept<decltype(a)>));

}

///////////////////////////////////////
#include <boost/concept_archetype.hpp>

void case7()
{
    typedef null_archetype<> T;
    typedef assignable_archetype<T> at;
    typedef copy_constructible_archetype<at> cat;
    //typedef sgi_assignable_archetype<T> at;
    typedef less_than_comparable_archetype<cat> vt;

    boost::detail::dummy_constructor dummy_cons;
    vt v1(dummy_cons), v2(dummy_cons);

    my_min(v1, v2);

    typedef mutable_random_access_iterator_archetype<vt> rt;
    rt begin, end;
    _sort(begin, end);

}

///////////////////////////////////////

#include <boost/iterator/iterator_archetypes.hpp>

void case8()
{
    using namespace boost_concepts;
    typedef copy_constructible_archetype<assignable_archetype<>> T;
    //typedef sgi_assignable_archetype<> T;

    typedef input_iterator_archetype<T > I;

    BOOST_CONCEPT_ASSERT((ReadableIterator<I>));
    BOOST_CONCEPT_ASSERT((SinglePassIterator<I>));
    BOOST_CONCEPT_ASSERT((InputIterator<I>));

    typedef boost::iterator_archetype<T,
            boost::iterator_archetypes::readable_iterator_t,
            boost::single_pass_traversal_tag > II;

    BOOST_CONCEPT_ASSERT((ReadableIterator<II>));
    BOOST_CONCEPT_ASSERT((SinglePassIterator<II>));
    BOOST_CONCEPT_ASSERT((InputIterator<II>));

}

///////////////////////////////////////

int main()
{
    std::cout << "hello concept_check" << std::endl;

    case1();
    case2();
    case3();
    case4();
    case5();
    case6();
    case7();
    case8();
}

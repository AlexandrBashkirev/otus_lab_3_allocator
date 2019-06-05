#define BOOST_CHECK_EQUAL_MODULE list_test
#include <boost/test/unit_test.hpp>

#include "list.h"
#include "fallocator.h"

BOOST_AUTO_TEST_CASE(list_test)
{
  flaber::list<int> l;
  l.push_back(2);
  l.push_back(3);
  l.push_front(1);
  int a = 4;
  l.push_back(a);

  BOOST_CHECK_EQUAL(*l.begin() , 1);

  l.insert_at(0, 10);

  BOOST_CHECK_EQUAL(*l.begin(), 10);
  BOOST_CHECK_EQUAL(*l.back() , 4);
  BOOST_CHECK_EQUAL(l.size() , 5);

  l.pop_front();

  BOOST_CHECK_EQUAL(*l.begin() , 1);
  BOOST_CHECK_EQUAL(l.size() , 4);

  l.pop_back();

  BOOST_CHECK_EQUAL(*l.back() , 3);
  BOOST_CHECK_EQUAL(l.size() , 3);

  BOOST_CHECK_EQUAL(l.is_empty(), false);

  l.clear();

  BOOST_CHECK_EQUAL(l.is_empty(), true);
}

BOOST_AUTO_TEST_CASE(allocator_test)
{
}
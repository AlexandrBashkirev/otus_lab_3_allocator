#define BOOST_TEST_MODULE list_test
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

  BOOST_TEST(*l.begin() == 1);

  l.insert_at(0, 10);

  BOOST_TEST(*l.begin() == 10);
  BOOST_TEST(*l.back() == 4);
  BOOST_TEST(l.size() == 5);

  l.pop_front();

  BOOST_TEST(*l.begin() == 1);
  BOOST_TEST(l.size() == 4);

  l.pop_back();

  BOOST_TEST(*l.back() == 3);
  BOOST_TEST(l.size() == 3);

  BOOST_TEST(!l.is_empty());

  l.clear();

  BOOST_TEST(l.is_empty());
}

BOOST_AUTO_TEST_CASE(allocator_test)
{
}
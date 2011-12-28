#ifndef ARRINDEX_HPP_
#define ARRINDEX_HPP_

#include <gtest/gtest.h>

#include "ArrIndex.h"

namespace {

class ArrIndexTest : public ::testing::Test
{
protected:
  ArrIndex index;
  QueryT query;
  ResVecPtrT res_ptr;
  
  void SetUp()
  {
    for (size_t i = 0; i <= 1; ++i) {
      ValT val;
      val.insert("Butter");
      val.insert("Bread");
      if (i == 0) {
        val.insert("Tomato");
        val.insert("Apple");
        val.insert("Pear");
      }
      index.insert(make_pair(i + 1, val));
    }
  }
};

TEST_F(ArrIndexTest, LittleQuery)
{
  query.insert("Pear");
  res_ptr = index.find(query);
  ASSERT_EQ(0, res_ptr->size());

  query.insert("Beer");
  res_ptr = index.find(query);
  ASSERT_EQ(0, res_ptr->size());
  
  query.insert("Tomato");
  res_ptr = index.find(query);
  ASSERT_EQ(1, res_ptr->size());
}

TEST_F(ArrIndexTest, BigQuery)
{
  query.insert("Asbdf");
  query.insert("Bodklc");
  query.insert("Cxcvef");
  query.insert("Dsdfsd");
  
  query.insert("Apple");
  
  query.insert("Tsdfsd");
  query.insert("Dsdfsdf");
  
  query.insert("Tomato");
  
  
  res_ptr = index.find(query);
  ASSERT_EQ(1, res_ptr->size());
}

TEST_F(ArrIndexTest, TwoResults)
{
  query.insert("Butter");
  query.insert("Apple");
  
  res_ptr = index.find(query);
  ASSERT_EQ(2, res_ptr->size());
}

}


#endif /* ARRINDEX_HPP_ */

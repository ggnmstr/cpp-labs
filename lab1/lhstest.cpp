#include <gtest/gtest.h>
#include "linkedhashset.hpp"

TEST(InsertTest,Empty){
    linkedhs l1;
    ASSERT_EQ(l1.size(),0);
    student s1(19,"Jora");
    l1.insert(s1);
    ASSERT_EQ(*l1.begin(),s1);
};

TEST(InsertTest,Amount){
    linkedhs l1;
    student s1(19,"Jora");
    student s2(20,"George");
    student s3(21,"Georgiy");
    l1.insert(s1);
    l1.insert(s2);
    l1.insert(s3);
    ASSERT_EQ(l1.size(),3);
}

TEST(CopyConstructorTest,Test){
    linkedhs l1;
    student s1(19,"Jora");
    student s2(20,"George");
    student s3(21,"Georgiy");
    l1.insert(s1);
    l1.insert(s2);
    l1.insert(s3);
    linkedhs l2(l1);
    ASSERT_EQ(l1,l2);
}

TEST(OperatorEqTest,Test){
    linkedhs l1;
    student s1(19,"Jora");
    student s2(20,"George");
    student s3(21,"Georgiy");
    l1.insert(s1);
    l1.insert(s2);
    l1.insert(s3);
    linkedhs l2;
    l2 = l1;
    ASSERT_EQ(l1,l2);
}
#include <gtest/gtest.h>
#include "linkedhashset.h"
#include "student.hpp"

TEST(InsertTest, Empty) {
    linkedhs<student,studentHasher> l1;
    ASSERT_EQ(l1.size(), 0);
    student s1(19, "Jora");
    l1.insert(s1);
    ASSERT_EQ(l1.size(), 1);
    ASSERT_TRUE(l1.contains(s1));
};

TEST(InsertTest, Present) {
    linkedhs<student,studentHasher> l1;
    student s1(19, "Jora");
    student s2(20, "George");
    student s3(21, "Georgiy");
    l1.insert(s1);
    l1.insert(s2);
    l1.insert(s3);
    ASSERT_EQ(l1.size(), 3);
    ASSERT_FALSE(l1.insert(s1));
}

TEST(InsertTest, Many) {
    linkedhs<student,studentHasher> l1;
    for (int i = 0; i < 512; i++) {
        student s1(i, "Name" );
        l1.insert(s1);
    }
    ASSERT_EQ(l1.size(), 512);
    for (int i = 0; i < 512; i++) {
        student s1(i, "Name" );
        ASSERT_TRUE(l1.contains(s1));
    }
}

TEST(CopyConstructorTest, Equality) {
    linkedhs<student,studentHasher> l1;
    student s1(19, "Jora");
    l1.insert(s1);
    linkedhs<student,studentHasher> l2(l1);
    ASSERT_EQ(l1, l2);
}

TEST(CopyConstructorTest, Independence) {
    linkedhs<student,studentHasher> l1;
    student s1(19, "Jora");
    l1.insert(s1);
    linkedhs<student,studentHasher> l2(l1);
    l1.remove(s1);
    ASSERT_NE(l1, l2);
}

TEST(OperatorAssignTest, Equality) {
    linkedhs<student,studentHasher> l1;
    student s1(19, "Jora");
    l1.insert(s1);
    linkedhs<student,studentHasher> l2;
    l2 = l1;
    ASSERT_EQ(l1, l2);
}

TEST(OperatorAssignTest, Independence) {
    linkedhs<student,studentHasher> l1;
    student s1(19, "Jora");
    l1.insert(s1);
    linkedhs<student,studentHasher> l2;
    l2 = l1;
    l1.remove(s1);
    ASSERT_NE(l1, l2);
}

TEST(RemoveTest, Empty) {
    linkedhs<student,studentHasher> l1;
    student s1(20, "Name");
    ASSERT_FALSE(l1.remove(s1));
}

TEST(RemoveTest, NonExistent) {
    linkedhs<student,studentHasher> l1;
    student s1(20, "Name");
    student s2(21, "Name1");
    l1.insert(s1);
    ASSERT_FALSE(l1.remove(s2));
    l1.remove(s1);
    ASSERT_EQ(l1.size(),0);
    ASSERT_FALSE(l1.contains(s1));
    ASSERT_FALSE(l1.contains(s2));
}

TEST(RemoveTest, Many) {
    linkedhs<student,studentHasher> l1;
    for (int i = 0; i < 512; i++) {
        student s1(i, "Name");
        l1.insert(s1);
    }
    for (int i = 1; i < 512; i++) {
        student s1(i, "Name");
        l1.remove(s1);
    }
    ASSERT_EQ(l1.size(), 1);
    student s2(0, "Name");
    ASSERT_TRUE(l1.contains(s2));
}

TEST(SwapTest, Empty) {
    linkedhs<student,studentHasher> l1;
    linkedhs<student,studentHasher> l2;
    ASSERT_EQ(l1, l2);
    l1.swap(l2);
    ASSERT_EQ(l1, l2);
}

TEST(SwapTest, Different) {
    student s1(20, "Name");
    student s2(120, "Surname");
    linkedhs<student,studentHasher> l1;
    linkedhs<student,studentHasher> l2;
    l1.insert(s1);
    l2.insert(s2);
    linkedhs<student,studentHasher> c1(l1);
    linkedhs<student,studentHasher> c2(l2);
    l1.swap(l2);
    ASSERT_EQ(l1, c2);
    ASSERT_EQ(l2, c1);
}

TEST(SwapTest,EmptyWNonEmpty){
    linkedhs<student,studentHasher> l1; 
    linkedhs<student,studentHasher> l2;
    student s2(12,"MooMoo");
    l2.insert(s2);
    l2.swap(l1);
    ASSERT_TRUE(l2.empty());
    ASSERT_NE(l1,l2);
    ASSERT_EQ(l1.size(),1);
}

TEST(SwapTest, Many) {
    linkedhs<student,studentHasher> l1;
    linkedhs<student,studentHasher> l2;
    for (int i = 0; i < 512; i++) {
        student s1(i, "Name1");
        student s2(i + 1000, "2Name2");
        l1.insert(s1);
        l2.insert(s2);
    }
    linkedhs<student,studentHasher> c1(l1);
    linkedhs<student,studentHasher> c2(l2);
    l1.swap(l2);
    ASSERT_EQ(l1, c2);
    ASSERT_EQ(l2, c1);
}

TEST(SizeTest, Empty) {
    linkedhs<student,studentHasher> l1;
    ASSERT_EQ(l1.size(), 0);
    ASSERT_TRUE(l1.empty());
}

TEST(SizeTest, NonEmpty) {
    linkedhs<student,studentHasher> l1;
    student s1(123, "ABC");
    l1.insert(s1);
    ASSERT_EQ(l1.size(), 1);
    ASSERT_FALSE(l1.empty());
}

TEST(ContainsTest, Existent) {
    linkedhs<student,studentHasher> l1;
    student s1(42, "Six");
    l1.insert(s1);
    ASSERT_TRUE(l1.contains(s1));
}

TEST(ContainsTest, NonExistent) {
    linkedhs<student,studentHasher> l1;
    student s1(46, "Two");
    student s2(100, "Steve");
    l1.insert(s1);
    ASSERT_FALSE(l1.contains(s2));
}

// CR: check equality properties
TEST(OperatorEqTest, Empty) {
    linkedhs<student,studentHasher> l1;
    linkedhs<student,studentHasher> l2;
    ASSERT_TRUE(l1 == l2);
}

TEST(OperatorEqTest, Equal) {
    linkedhs<student,studentHasher> l1;
    linkedhs<student,studentHasher> l2;
    student s1(1337, "1337");
    l1.insert(s1);
    l2.insert(s1);
    ASSERT_TRUE(l1 == l2);
}


TEST(OperatorEqTest, NonEqual) {
    linkedhs<student,studentHasher> l1;
    linkedhs<student,studentHasher> l2;
    student s1(1337, "1337");
    student s2(7331, "7331");
    l1.insert(s1);
    l2.insert(s2);
    ASSERT_FALSE(l1 == l2);
}

TEST(OperatorEqTest, Reflex) {
    linkedhs<student,studentHasher> l1;
    student s1(1337, "1337");
    student s2(7331, "7331");
    l1.insert(s1);
    l1.insert(s2);
    ASSERT_TRUE(l1 == l1);
}

TEST(OperatorEqTest, Transitivity){
    linkedhs<student,studentHasher> l1;
    student s1(44,"80085");
    linkedhs<student,studentHasher> l2(l1);
    linkedhs<student,studentHasher> l3 = l1;
    ASSERT_TRUE(l1 == l2);
    ASSERT_TRUE(l2 == l3);
    ASSERT_TRUE(l3 == l1);
}

TEST(OperatorNEqTest, NonEqual){
    linkedhs<student,studentHasher> l1;
    linkedhs<student,studentHasher> l2;
    student s1(123,"ASDASD");
    l1.insert(s1);
    ASSERT_TRUE(l1 != l2);
}

TEST(ClearTest, Empty) {
    linkedhs<student,studentHasher> l1;
    l1.clear();
    ASSERT_EQ(l1.size(), 0);
    ASSERT_TRUE(l1.empty());
}

TEST(ClearTest, Many) {
    linkedhs<student,studentHasher> l1;
    for (int i = 0; i < 512; i++) {
        student s1(i, "NameXXX");
        l1.insert(s1);
    }
    l1.clear();
    ASSERT_EQ(l1.size(), 0);
    ASSERT_TRUE(l1.empty());
}

TEST(IteratorTest, Empty) {
    linkedhs<student,studentHasher> l1;
    ASSERT_EQ(l1.begin(), nullptr);
    ASSERT_EQ(l1.begin(), l1.end());
}

TEST(IteratorTest, Begin) {
    linkedhs<student,studentHasher> l1;
    for (int i = 0; i < 512; i++) {
        student s1(i, "NameXXX");
        l1.insert(s1);
    }
    student s0(0, "NameXXX");
    ASSERT_EQ(*l1.begin(), s0);
}

TEST(IteratorTest, IterateWhole) {
    linkedhs<student,studentHasher> l1;
    for (int i = 0; i < 512; i++) {
        student s1(i, "NameXXX");
        l1.insert(s1);
    }
    int i = 0;
    for (auto it = l1.begin(); it != l1.end(); it++) {
        student s2(i, "NameXXX");
        ASSERT_EQ(*it, s2);
        i++;
    }
}

TEST(IteratorTest, Find) {
    linkedhs<student,studentHasher> l1;
    linkedhs<student,studentHasher> l2;
    for (int i = 0; i < 512; i++) {
        student s1(i, "Name");
        student s2(511 - i, "Name");
        l1.insert(s1);
        l2.insert(s2);
    }
    student sf(10, "Name");
    auto it1 = l1.find(sf);
    auto it2 = l2.find(sf);
    ASSERT_EQ(*it1, *it2);
}

TEST(IteratorTest, EqOperator) {
    linkedhs<student,studentHasher> l1;
    for (int i = 0; i < 512; i++) {
        student s1(i, "Name" );
        l1.insert(s1);
    }
    student sf(10, "Name");
    auto it1 = l1.find(sf);
    auto it2 = l1.begin();
    for (int i = 0; i < 10; i++) it2++;
    ASSERT_TRUE(it1 == it2);
}

TEST(IteratorTest, HeadCheck){
    linkedhs<student,studentHasher> l1;
    student s1(12,"ABC");
    l1.insert(s1);
    ASSERT_EQ(*l1.begin(),s1);
    ASSERT_NE(l1.begin(),l1.end());
    l1.remove(s1);
    ASSERT_EQ(l1.begin(),nullptr);
    ASSERT_EQ(l1.end(),nullptr);
    ASSERT_TRUE(l1.empty());
    student s2(123,"LOL");
    l1.insert(s2);
    ASSERT_EQ(*l1.begin(),s2);
}


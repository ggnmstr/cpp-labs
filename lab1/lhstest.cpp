#include <gtest/gtest.h>
#include "linkedhashset.hpp"

TEST(InsertTest,Empty){
    linkedhs l1;
    ASSERT_EQ(l1.size(),0);
    student s1(19,"Jora");
    l1.insert(s1);
    ASSERT_EQ(l1.size(),1);
    ASSERT_TRUE(l1.contains(s1));
};

TEST(InsertTest,Present){
    linkedhs l1;
    student s1(19,"Jora");
    student s2(20,"George");
    student s3(21,"Georgiy");
    l1.insert(s1);
    l1.insert(s2);
    l1.insert(s3);
    ASSERT_EQ(l1.size(),3);
    ASSERT_FALSE(l1.insert(s1));
}

TEST(InsertTest,Many){
    linkedhs l1;
    for (int i = 0; i < 512; i++){
        student s1(i,"Name"+i);
        l1.insert(s1);
    }
    ASSERT_EQ(l1.size(),512);
    for (int i = 0; i < 512; i++){
        student s1(i,"Name"+i);
        ASSERT_TRUE(l1.contains(s1));
    }
}

TEST(CopyConstructorTest,Equality){
    linkedhs l1;
    student s1(19,"Jora");
    l1.insert(s1);
    linkedhs l2(l1);
    ASSERT_EQ(l1,l2);
}

TEST(CopyConstructorTest,Independence){
    linkedhs l1;
    student s1(19,"Jora");
    l1.insert(s1);
    linkedhs l2(l1);
    l1.remove(s1);
    ASSERT_NE(l1,l2);
}

TEST(OperatorAssignTest,Equality){
    linkedhs l1;
    student s1(19,"Jora");
    l1.insert(s1);
    linkedhs l2;
    l2 = l1;
    ASSERT_EQ(l1,l2);
}

TEST(OperatorAssignTest,Independence){
    linkedhs l1;
    student s1(19,"Jora");
    l1.insert(s1);
    linkedhs l2;
    l2 = l1;
    l1.remove(s1);
    ASSERT_NE(l1,l2);
}

TEST(RemoveTest,Empty){
    linkedhs l1;
    student s1(20, "Name");
    ASSERT_FALSE(l1.remove(s1));
}

TEST(RemoveTest,NonExistent){
    linkedhs l1;
    student s1(20, "Name");
    student s2(21,"Name1");
    l1.insert(s1);
    ASSERT_FALSE(l1.remove(s2));
}

TEST(RemoveTest,Many){
    linkedhs l1;
    for (int i = 0; i < 512; i++){
        student s1(i, "Name"+i);
        l1.insert(s1);
    }
    for (int i = 1; i < 512; i++){
        student s1(i, "Name"+i);
        l1.remove(s1);
    }
    ASSERT_EQ(l1.size(),1);
    student s2(0,"Name"+0);
    ASSERT_TRUE(l1.contains(s2));
    student s1(20, "Name");
}

TEST(SwapTest,Empty){
    linkedhs l1;
    linkedhs l2;
    ASSERT_EQ(l1,l2);
    l1.swap(l2);
    ASSERT_EQ(l1,l2);
}

TEST(SwapTest,Different){
    student s1(20,"Name");
    student s2(120,"Surname");
    linkedhs l1;
    linkedhs l2;
    l1.insert(s1);
    l2.insert(s2);
    linkedhs c1(l1);
    linkedhs c2(l2);
    l1.swap(l2);
    ASSERT_EQ(l1,c2);
    ASSERT_EQ(l2,c1);
}

TEST(SwapTest,Many){
    linkedhs l1;
    linkedhs l2;
    for (int i = 0; i < 512; i++){
        student s1(i,"Name1"+i);
        student s2(i+1000,"2Name2"+i);
        l1.insert(s1);
        l2.insert(s2);
    }
    linkedhs c1(l1);
    linkedhs c2(l2);
    l1.swap(l2);
    ASSERT_EQ(l1,c2);
    ASSERT_EQ(l2,c1);
}

TEST(SizeTest,Empty){
    linkedhs l1;
    ASSERT_EQ(l1.size(),0);
    ASSERT_TRUE(l1.empty());
}

TEST(SizeTest,NonEmpty){
    linkedhs l1;
    student s1(123,"ABC");
    l1.insert(s1);
    ASSERT_EQ(l1.size(),1);
    ASSERT_FALSE(l1.empty());
}

TEST(ContainsTest,Existent){
    linkedhs l1;
    student s1(42,"Six");
    l1.insert(s1);
    ASSERT_TRUE(l1.contains(s1));
}

TEST(ContainsTest,NonExistent){
    linkedhs l1;
    student s1(46,"Two");
    student s2(100,"Steve");
    l1.insert(s1);
    ASSERT_FALSE(l1.contains(s2));
}

TEST(OperatorEqTest,Empty){
    linkedhs l1;
    linkedhs l2;
    ASSERT_TRUE(l1==l2);
}

TEST(OperatorEqTest,Equal){
    linkedhs l1;
    linkedhs l2;
    student s1(1337,"1337");
    l1.insert(s1);
    l2.insert(s1);
    ASSERT_TRUE(l1==l2);
}


TEST(OperatorEqTest,NonEqual){
    linkedhs l1;
    linkedhs l2;
    student s1(1337,"1337");
    student s2(7331,"7331");
    l1.insert(s1);
    l2.insert(s2);
    ASSERT_FALSE(l1==l2);
}

TEST(ClearTest,Empty){
    linkedhs l1;
    l1.clear();
    ASSERT_EQ(l1.size(),0);
    ASSERT_TRUE(l1.empty());
}

TEST(ClearTest,Many){
    linkedhs l1;
    for (int i = 0; i < 512; i++){
        student s1(i,"NameXXX"+i);
    }
    l1.clear();
    ASSERT_EQ(l1.size(),0);
    ASSERT_TRUE(l1.empty());
}

TEST(IteratorTest,Empty){
    linkedhs l1;
    ASSERT_EQ(l1.begin(),nullptr);
    ASSERT_EQ(l1.begin(),l1.end());
}

TEST(IteratorTest,Begin){
    linkedhs l1;
    for (int i = 0; i < 512; i++){
        student s1(i,"NameXXX"+i);
        l1.insert(s1);
    }
    student s0(0,"NameXXX"+0);
    ASSERT_EQ(*l1.begin(),s0);
}

TEST(IteratorTest,IterateWhole){
    linkedhs l1;
    for (int i = 0; i < 512; i++){
        student s1(i,"NameXXX"+i);
        l1.insert(s1);
    }
    int i = 0;
    for (auto it = l1.begin(); it != l1.end(); it++){
        student s2(i,"NameXXX"+i);
        ASSERT_EQ(*it,s2);
        i++;
    }
}

TEST(IteratorTest,Find){
    linkedhs l1;
    linkedhs l2;
    for (int i = 0; i < 512; i++){
        student s1(i,"Name"+i);
        student s2(511-i,"Name"+(511-i));
        l1.insert(s1);
        l2.insert(s2);
    }
    student sf(10,"Name"+10);
    auto it1 = l1.find(sf);
    auto it2 = l2.find(sf);
    ASSERT_EQ(*it1,*it2);
}

TEST(IteratorTest,EqOperator){
    linkedhs l1;
    for (int i = 0; i < 512; i++){
        student s1(i,"Name"+i);
        l1.insert(s1);
    }
    student sf(10,"Name"+10);
    auto it1 = l1.find(sf);
    auto it2 = l1.begin();
    for (int i = 0; i < 10; i++) it2++;
    ASSERT_EQ(it1,it2);
}

#include "student.hpp"

student::student(unsigned age, std::string name){
   age_ = age;
   name_ = name;
}
bool student::operator==(const student & other) const{
   return age_ == other.age_ && name_ == other.name_;
}
long long student::hash() const{
   return 0;
};



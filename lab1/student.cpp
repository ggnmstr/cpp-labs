#include "student.hpp"

student::student(unsigned age, std::string name){
   age_ = age;
   name_ = name;
}
bool student::operator==(const student & other) const{
   return age_ == other.age_ && name_ == other.name_;
}
long long student::hash() const{
   // djb2 hash func 
   std::string s = name_ + std::to_string(age_);
   unsigned long hash = 5381;
   for (auto c : s){
      hash = (hash << 5) + hash + c; /* hash * 33 + c */
   }
   return hash;
};



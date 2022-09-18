#include <string>

struct student {
   student(unsigned age, std::string name){
    age_ = age;
    name_ = name;
   }
   bool operator==(const student & other) const{
    return age_ == other.age_ && name_ == other.name_;
   }
   long long hash() const;
   unsigned age_;
   std::string name_;
};

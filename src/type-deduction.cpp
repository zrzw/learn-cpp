/*
 * type-deduction.cpp
 * examples from Item 1: Understand template type deduction, from
 * Effective Modern C++
 */
#include <iostream>
#include <vector>

template<typename T>
bool is_in(const std::vector<T>& v, const T& item)
{
  for(auto& a: v)
    if(a == item)
      return true;
  return false;
}

template<typename T>
void update_at_index(std::vector<T>& v, const T* item, int index)
{
  auto i {0};
  /* Item 2: auto. In C++11, i would be a initializer_list<int>
   * from C++14, only the auto a = { 0 } syntax would result in an initializer
   * list. In this case, the type of i is deduced from the single element. */
  for(auto& a: v){
    if(i == index){
      a = *item;
    }
    i++;
  }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
  os << "{";
  int count = 0;
  for(auto& a: v){
    os << a;
    if(count < v.size()-1)
      os << ",";
    ++count;
  }
  os << "}";
  return os;
}

template<typename T, std::size_t N>
constexpr std::size_t array_size(T (&a)[N])
{
  return N;
}

int main()
{
  std::vector<int> vi {2,4,8,10,12};
  int a=13;
  int b=12;
  int& c = b;
  std::cout << ((is_in(vi, 13)) ? "yes" : "no") << std::endl;
  //it is only ok to call is_in with 13 if it is expecting a const T&
  //const values are lvalues (a temporary variable is created)
  std::cout << ((is_in(vi, c)) ? "yes" : "no") << std::endl;
  //type deduction, case 1 (reference but not a universal ref)
  //v's type is therefore deduced to be const vector<int>&
  //T is type const vector<int>
  //when 'c' is passed, it's 'referenceness' is ignored during type deduction
  //ie T is not deducted to be const int&
  std::cout << vi << std::endl;
  update_at_index(vi, &a, 1);
  std::cout << vi << std::endl;
  // array to pointer decay:
  const char name[] = "Fred Wesley";
  std::cout << "size of name[]= " << array_size(name) << std::endl;
  return 0;
}

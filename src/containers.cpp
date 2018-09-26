/*
** containers.cpp - containers and algorithms
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

char upper_case(const char& x){
    if(x >= 97 && x <= 122)
        return x-32;
    return x;
}

class Nocase{
public:
    bool operator()(const std::string& x, const std::string& y);
};

bool Nocase::operator()(const std::string& x, const std::string& y)
{
    auto p = x.begin();
    auto q = y.begin();
    while (p!=x.end() && q!=y.end() && upper_case(*p)==upper_case(*q)) {
        ++p;
        ++q;
    }
    if (p == x.end()) return q != y.end();
    if (q == y.end()) return false;
    return upper_case(*p) < upper_case(*q);
}

template<typename T>
void print_list(std::vector<T>& v)
{
    for(auto& a: v) std::cout << a << ", ";
    std::cout << std::endl;
}

template<typename T, typename U>
void print_map(std::unordered_map<T, U>& m){
        for(auto& p: m){
            std::cout << p.first << ":" << m[p.first] << ", ";
        }
        std::cout << std::endl;
}

int main()
{
    using std::vector;
    using std::string;
    vector<string> fruits {"apple", "Pear", "orange", "avocado", "banana"};
    sort(fruits.begin(), fruits.end());
    print_list(fruits);
    sort(fruits.begin(), fruits.end(), Nocase());
    print_list(fruits);
    using std::unordered_map;
    unordered_map<string, int> directory {
            {"Bob", 123},
            {"Carl", 456},
            {"Harry", 707}
    };
    print_map(directory);
    return 0;
}

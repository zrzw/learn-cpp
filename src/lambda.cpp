#include <iostream>
#include <vector>
#include <algorithm>

void f(int x)
{
    std::cout << x * 2 << std::endl;
}

int main()
{
    std::vector<int> v {1, 2, 4, 8, 15, 32};
    for_each(v.begin(), v.end(), f);
    int factor = 3;
    std::vector<int> acc;
    for_each(v.begin(), v.end(),
        [factor, &acc] (int x){
            if(x % 2 == 0)
                acc.push_back(factor*x);
        });
    for(auto& a: acc){
        std::cout << a << std::endl;
    }
    return 0;
}

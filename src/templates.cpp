#include <iostream>
#include <stdexcept>

template <typename T>
class Stack{
public:
    explicit Stack(std::initializer_list<T> il)
        : sz{il.size()}
    {
        elem = new T[sz];
        stack_ptr = sz-1;
        size_t i=0;
        for(auto& a: il){
            elem[i++] = a;
        }
    }
    ~Stack() { delete[] elem; }
    Stack(Stack& r) : sz{r.sz}, stack_ptr{r.stack_ptr}
    {
        for(size_t i=0; i<sz; ++i){
            elem[i] = r.elem[i];
        }
    }
    Stack(Stack&& r) : sz{r.sz}, stack_ptr{r.stack_ptr}
    {
        elem = r.elem;
        r.elem = nullptr;
    }
    Stack& operator=(Stack&&); //not implemented
    T pop(){
        if(stack_ptr >= 0)
            return elem[stack_ptr--];
        throw std::out_of_range{"elem"};
    }
private:
    T* elem;
    size_t sz;
    size_t stack_ptr;
};

int main(){
    Stack<int> s1 {1, 2, 4, 8, 16, 32};
    std::cout << s1.pop() << std::endl;
    Stack<int> s2 = std::move(s1);
    std::cout << s2.pop() << std::endl;
    return 0;    
}

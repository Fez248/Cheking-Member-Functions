#include <type_traits>
#include <iostream>

//Base case where it doesn't have foo()
template <class T, class = void>
struct has_foo : std::false_type {};

//Specific case where it HAS foo()
//declval<T>().foo() creates a temporaty object and calls foo()
//decltype examins the type of the expression
//void_t evaluates to 'void' if succesful it means it has foo(), if not a substitution failure occurs
template <class T>
struct has_foo<T, std::void_t<decltype(std::declval<T>().foo())>> : std::true_type {};

template <class T>
void do_something_impl(T&, std::false_type) {
    std::cout << "doesn't exist" << std::endl;
}

template <class T>
void do_something_impl(T& t, std::true_type) {
    t.foo();
}

template <class T>
void do_something(T& t) {
    do_something_impl(t, has_foo<T>());
}

struct A {
    void foo() { 
        std::cout << "exists" << std::endl;
    }
};

struct B {};

int main() {
    A a;
    do_something(a);

    B b;
    do_something(b);
}
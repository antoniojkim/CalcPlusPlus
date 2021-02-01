#include <cassert>
#include <charconv>
#include <exception>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include "../Expressions/ExpressionTypes/Types.h"
#include "../Utils/MultiStack.h"

using namespace std;
using namespace calcpp;

// struct Test;
// struct test {
//     std::shared_ptr<Test> t;
//     test(Test* t) : t{t} {}

//     void operator()(const test& test) const;
// };

// struct Test {
//     int i;
//     Test(int i) : i{i} {}

//     void call(const test& t) const { cout << "called Test: " << t.t->i << endl; }
// };

// void test::operator()(const test& test) const { t->call(test); }

// const test test1(new Test(3));

class A {
    int n;
    A(int n) : n{n} {}

  public:
    template<typename... Args>
    friend std::shared_ptr<A> make_A(Args&&... args);
};

template<typename... Args>
std::shared_ptr<A> make_A(Args&&... args) {
    return std::shared_ptr<A>(new A(std::forward<Args>(args)...));
}

int main() {
    // const char* c = "123.54";
    // string_view s(c, 6);
    // cout << s << endl;
    // double num = atof(s.data());
    // cout << num << endl;

    // cout << sizeof(const char*) << endl;
    // cout << sizeof(size_t) << endl;
    // cout << sizeof(std::string_view) << endl;
    // cout << sizeof(long double) << endl;

    const char* c = ".25";
    char* end;
    long double value = strtold(c, &end);
    cout << value << "\t" << (end - c) << endl;
    value = 2.5 * 2;
    cout << std::setprecision(16) << value << endl;

    const char* hex = "0x12af";
    unsigned long long hexval = strtoull(hex, &end, 16);
    cout << hexval << "\t" << (end - hex) << endl;

    const char* bin = "21000101";
    unsigned long long binval = strtoull(bin, &end, 2);
    cout << binval << "\t" << (end - bin) << endl;

    const unsigned int type = Type::NUM | Type::EVALUABLE;
    cout << type << endl;

    // test1(test1);
    auto a = make_A(3);
}

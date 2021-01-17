#include <cassert>
#include <charconv>
#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include "../Utils/MultiStack.h"

using namespace std;
using namespace calcpp;

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

    const char* hex = "0x12af";
    unsigned long long hexval = strtoull(hex, &end, 16);
    cout << hexval << "\t" << (end - hex) << endl;

    const char* bin = "21000101";
    unsigned long long binval = strtoull(bin, &end, 2);
    cout << binval << "\t" << (end - bin) << endl;
}

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void test_num(const std::string& num){
    try {
        double real = 0, imag = 0;
        size_t pos;
        real = stod(num, &pos);

        if (pos < num.size()){
            switch(num.at(pos)){
                case 'i':
                case 'j':
                    imag = real;
                    real = 0;
                    break;
                default:
                    break;
            }
        }

        cout << "num: " << num << endl;
        cout << "   real: " << real << endl;
        cout << "   imag: " << imag << endl;
    } catch (std::invalid_argument& e1){
        cout << "Invalid Argument: " << num << endl;
    } catch (std::out_of_range& e2){
        cout << "Out of Range: " << num << endl;
    }
}

int main(){
    test_num("1");
    test_num("2i");
    test_num("1.1");
    test_num("2.2i");
    test_num("1.1e-8");
    test_num("2.2e-7i");
}

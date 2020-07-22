#include <iostream>

#include <curses.h>
#include <MathEngine.h>
#include <Utils/Exception.h>

using namespace std;

int main(){
    // initscr();
    // keypad(stdscr, TRUE);

    // int ch = getch();
    MathEngine engine;

    std::string input;
    cout << ">>> ";
    while (cin.good() && getline(cin, input)){
        try {
            auto expr = engine.eval(input);

            ostringstream out;

            ostringstream pretty;
            expr->print(pretty, true);
            ostringstream normal;
            expr->print(normal, false);

            if (pretty.str() != normal.str()){
                cout << "= " << pretty.str() << " ";
            }
            cout << "= " << normal.str() << endl;
        } catch (const Exception& e){
            cout << e.what() << endl;
        }
        cout << ">>> ";
    }
}

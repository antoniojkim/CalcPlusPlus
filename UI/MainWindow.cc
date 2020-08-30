#include <Qt>

#include "MainWindow.h"

using namespace std;


MainWindow::MainWindow(int width, int height):
    engine{},
    vlayout{},
    editor{std::make_shared<EquationEditor>(this)} {

    setWindowTitle("CalcPlusPlus by AntonioJKim");
    resize(width, height);
    setStyleSheet("background-color:#F5F5F5;");

    vlayout.setSpacing(0);
    vlayout.setAlignment(Qt::AlignTop);

    vlayout.addWidget(editor.get());
    vlayout.addWidget(&(editor->output));

    setLayout(&vlayout);

}

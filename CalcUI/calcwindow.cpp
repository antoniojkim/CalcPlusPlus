#include <iostream>
#include <string>
#include <sstream>

#include "calcwindow.h"
#include "ui_calcwindow.h"
#include <QTextEdit>
#include <QString>

#include <Expressions/InvalidExpression.h>
#include <Utils/exceptions.h>

using namespace std;

CalcWindow::CalcWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CalcWindow)
{
    ui->setupUi(this);

    connect_textchanged(ui->input1, ui->output1);
}

CalcWindow::~CalcWindow()
{
    delete ui;
}


void CalcWindow::connect_textchanged(QTextEdit* input, QTextEdit* output)
{
    connect(input, &QTextEdit::textChanged, this, [=](){
        string inputString = input->toPlainText().toStdString();

        try {
            auto expr = engine.evaluate(inputString);
            if (!dynamic_cast<InvalidExpression*>(expr.get())){
                ostringstream out;
                out << expr;
                string outputString = out.str();
                output->setText(QString::fromUtf8(outputString.c_str()));
            }
        } catch(const Exception& e){
            cerr << e.what() << endl;
        } catch(...){}
    });
}

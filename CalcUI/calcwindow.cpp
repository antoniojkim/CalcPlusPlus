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

    connect(ui->input1, &QTextEdit::textChanged, this, &CalcWindow::on_textChanged);
}

CalcWindow::~CalcWindow()
{
    delete ui;
}


void CalcWindow::on_textChanged()
{
    string input = ui->input1->toPlainText().toStdString();

    try {
        auto expr = engine.evaluate(input);
        if (!dynamic_cast<InvalidExpression*>(expr.get())){
            ostringstream out;
            out << expr;
            string output = out.str();
            ui->output1->setText(QString::fromUtf8(output.c_str()));
        }
    } catch(const Exception& e){
        cerr << e.what() << endl;
    } catch(...){}
}

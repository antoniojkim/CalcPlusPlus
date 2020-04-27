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
        try {
            string inputString = input->toPlainText().toStdString();
            auto cursor = input->textCursor();
            int cursorPosition = input->textCursor().position();

            inputString = engine.formatInput(inputString, cursorPosition);

            input->blockSignals(true);
            input->setText(QString::fromUtf8(inputString.c_str()));
            cursor.setPosition(cursorPosition);
            input->setTextCursor(cursor);
            input->blockSignals(false);

            string outputString = output->toPlainText().toStdString();
            outputString = engine.evaluateOutput(inputString, outputString);
            output->setText(QString::fromUtf8(outputString.c_str()));
        } catch(const Exception& e){
            cout << e.what() << endl;
        } // catch(...){}
    });
}

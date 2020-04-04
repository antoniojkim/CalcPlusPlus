#include "calcwindow.h"
#include "ui_calcwindow.h"

CalcWindow::CalcWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CalcWindow)
{
    ui->setupUi(this);
}

CalcWindow::~CalcWindow()
{
    delete ui;
}


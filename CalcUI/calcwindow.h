#ifndef CALCWINDOW_H
#define CALCWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CalcWindow; }
QT_END_NAMESPACE

class CalcWindow : public QMainWindow
{
    Q_OBJECT

public:
    CalcWindow(QWidget *parent = nullptr);
    ~CalcWindow();

private:
    Ui::CalcWindow *ui;
};
#endif // CALCWINDOW_H

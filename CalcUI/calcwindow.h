#ifndef CALCWINDOW_H
#define CALCWINDOW_H

#include <QMainWindow>
#include <MathEngine.h>

QT_BEGIN_NAMESPACE
namespace Ui { class CalcWindow; }
QT_END_NAMESPACE

class CalcWindow : public QMainWindow
{
    Q_OBJECT

public:
    CalcWindow(QWidget *parent = nullptr);
    ~CalcWindow();

private slots:
    void on_textChanged();

private:
    Ui::CalcWindow *ui;
    MathEngine engine;
};
#endif // CALCWINDOW_H

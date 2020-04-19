#ifndef CALCWINDOW_H
#define CALCWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <MathEngine.h>

QT_BEGIN_NAMESPACE
namespace Ui { class CalcWindow; }
QT_END_NAMESPACE

class CalcWindow : public QMainWindow
{
    Q_OBJECT

    void connect_textchanged(QTextEdit* input, QTextEdit* output);

public:
    CalcWindow(QWidget *parent = nullptr);
    ~CalcWindow();

private:
    Ui::CalcWindow *ui;
    MathEngine engine;
};
#endif // CALCWINDOW_H

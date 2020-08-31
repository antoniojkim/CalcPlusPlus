#include <iostream>

#include <QFont>
#include <QFontMetrics>
#include <QFrame>
#include <QKeyEvent>

#include "EquationEditor.h"
#include "MainWindow.h"

using namespace std;


TextEdit::TextEdit(double heightFactor){
    QFont font ("Computer Modern", 18);
    setFont(font);

    setFrameShape(QFrame::NoFrame);
    setLineWidth(0);

    QFontMetrics m (font);
    setFixedHeight(m.lineSpacing() * heightFactor);
}
void TextEdit::updateSize(){
    auto size = document()->size().toSize();
    setFixedHeight(size.height() + 3);
}

EquationEditor::EquationEditor(MainWindow* parent):
    parent{parent},
    prev{nullptr},
    next{nullptr},
    output{1.1},
    outputStr{""} {

    output.setReadOnly(true);

    connect(this, &QTextEdit::textChanged, this, &EquationEditor::textChangedAction);
}

void EquationEditor::updateOutput(){
    string inputStr = toPlainText().toStdString();
    auto cursor = textCursor();
    int cursorPosition = textCursor().position();

    string newInputStr = parent->engine.formatInput(inputStr, cursorPosition);

    if (inputStr != newInputStr){
        blockSignals(true);
        setText(QString::fromUtf8(newInputStr.c_str()));
        cursor.setPosition(cursorPosition);
        setTextCursor(cursor);
        blockSignals(false);
        updateSize();
    }
    inputStr = newInputStr;

    outputStr = parent->engine.evaluateOutput(inputStr, outputStr);
    output.setText(QString::fromUtf8(outputStr.c_str()));

    output.updateSize();
}
void EquationEditor::textChangedAction(){
    updateSize();
    updateOutput();

    auto curr = next;
    while(curr){
        curr->updateOutput();
        curr = curr->next;
    }

    curr = prev;
    while(curr){
        curr->updateOutput();
        curr = curr->prev;
    }
}
void EquationEditor::keyPressEvent(QKeyEvent* qKeyEvent){
    if (qKeyEvent->modifiers() == Qt::ControlModifier){
        switch(qKeyEvent->key()) {
            case Qt::Key_W:
                exit(0);
            case Qt::Key_Enter:
            case Qt::Key_Return: {
                auto editor = std::make_shared<EquationEditor>(parent);
                if (next){
                    int i = parent->vlayout.indexOf(next.get());
                    parent->vlayout.insertWidget(i, editor.get());
                    parent->vlayout.insertWidget(i+1, &(editor->output));

                    editor->next = next;
                    editor->prev = shared_from_this();
                    next->prev = editor;
                    next = editor;
                }
                else{
                    parent->vlayout.addWidget(editor.get());
                    parent->vlayout.addWidget(&(editor->output));

                    editor->prev = shared_from_this();
                    next = editor;
                }
                editor->setFocus();
                return;
            }
            default:
                break;
        }
    }
    else {
        switch(qKeyEvent->key()){
            case Qt::Key_Backspace:
            case Qt::Key_Delete: {
                if ((prev || next) && toPlainText().size() == 0){
                    parent->vlayout.removeWidget(this);
                    parent->vlayout.removeWidget(&output);

                    if (!prev){
                        parent->editor = next;
                        next->prev = nullptr;
                        next->setFocus();
                    }
                    else if (!next){
                        prev->next = nullptr;
                        prev->setFocus();
                    }
                    else{
                        prev->next = next;
                        next->prev = prev;
                        prev->setFocus();
                    }

                    hide();
                    output.hide();
                    return;
                }
                break;
            }
            case Qt::Key_Up: {
                if (prev && textCursor().blockNumber() == 0){
                    prev->setFocus();
                    return;
                }
                break;
            }
            case Qt::Key_Down: {
                if (next && textCursor().blockNumber() == document()->blockCount() - 1){
                    next->setFocus();
                    return;
                }
                break;
            }
            default:
                break;
        }
        QTextEdit::keyPressEvent(qKeyEvent);
    }
}

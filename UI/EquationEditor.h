#pragma once

#include <memory>

#include <QPoint>
#include <QTextEdit>


class MainWindow;

struct TextEdit: public QTextEdit {
    TextEdit(double heightFactor = 2.0);
    void updateSize();

    void contextMenuEvent(QContextMenuEvent *) override;
};

struct EquationEditor: public TextEdit, public std::enable_shared_from_this<EquationEditor> {

    MainWindow* parent;
    std::shared_ptr<EquationEditor> prev;
    std::shared_ptr<EquationEditor> next;

    TextEdit output;
    std::string outputStr;

    EquationEditor(MainWindow* parent);

    void updateOutput();
    void updateNeighbours();
    void textChangedAction();

    void insertEditorBelow();
    bool deleteCurrentEditor();
    void keyPressEvent(QKeyEvent* qKeyEvent) override;
};

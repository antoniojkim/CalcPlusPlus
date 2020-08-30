#pragma once

#include <memory>

#include <QWidget>
#include <QVBoxLayout>
#include <MathEngine.h>

#include "EquationEditor.h"

struct MainWindow: public QWidget {

    MathEngine engine;
    QVBoxLayout vlayout;
    std::shared_ptr<EquationEditor> editor;

    MainWindow(int width = 575, int height = 175);

};

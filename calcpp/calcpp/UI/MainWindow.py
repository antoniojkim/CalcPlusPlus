# -*- coding: utf-8 -*-
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QFont, QFontMetrics
from PyQt5.QtWidgets import QVBoxLayout, QTextEdit, QWidget, QFrame

from ..MathEngine import MathEngine


class OutputTextBox(QTextEdit):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        font = QFont("Computer Modern", 18)
        self.setFont(font)
        self.setReadOnly(True)

        self.setFrameShape(QFrame.NoFrame)
        self.setLineWidth(0)

        self.setFixedHeight(QFontMetrics(font).lineSpacing() * 2)

    def update_size(self):
        size = self.document().size().toSize()
        self.setFixedHeight(size.height() + 3)


class EquationEditor(QTextEdit):
    def __init__(self, parent, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self.parent = parent

        self.next = None
        self.prev = None

        self.setAutoFormatting(QTextEdit.AutoAll)
        font = QFont("Computer Modern", 18)
        self.setFont(font)
        self.textChanged.connect(self.textChangedAction)

        self.setFrameShape(QFrame.NoFrame)
        self.setLineWidth(0)

        self.setFixedHeight(QFontMetrics(font).lineSpacing() * 2)

        self.output = OutputTextBox()
        self.outputStr = ""

        self.parent.layout.addWidget(self)
        self.parent.layout.addWidget(self.output)

    def update_size(self):
        size = self.document().size().toSize()
        self.setFixedHeight(size.height() + 3)

    def update_output(self):
        inputStr = self.toPlainText()
        self.outputStr = self.parent.engine.evaluateOutput(inputStr, self.outputStr)
        self.output.setText(self.outputStr)
        self.output.update_size()

    def textChangedAction(self):
        self.update_size()
        self.update_output()

        curr = self.next
        while curr is not None:
            curr.update_output()
            curr = curr.next

        curr = self.prev
        while curr is not None:
            curr.update_output()
            curr = curr.prev

    def keyPressEvent(self, qKeyEvent):
        if qKeyEvent.modifiers() == Qt.ControlModifier:
            if qKeyEvent.key() in (Qt.Key_Enter, Qt.Key_Return):
                self.next = EquationEditor(self.parent)
                self.next.setFocus()
                self.next.prev = self
                return
        elif (
            qKeyEvent.key() in (Qt.Key_Backspace, Qt.Key_Delete)
            and (self.prev is not None or self.next is not None)  # noqa: W503
            and len(self.toPlainText()) == 0  # noqa: W503
        ):
            self.parent.layout.removeWidget(self)
            self.parent.layout.removeWidget(self.output)
            if self.prev is None:
                self.parent.editors = self.next
                self.next.prev = None
                self.next.setFocus()
            elif self.next is None:
                self.prev.next = None
                self.prev.setFocus()
            else:
                self.prev.next = self.next
                self.next.prev = self.prev
                self.prev.setFocus()

            self.hide()
            self.output.hide()
            return

        elif qKeyEvent.key() == Qt.Key_Up:
            if self.prev is not None and self.textCursor().blockNumber() == 0:
                self.prev.setFocus()
                return

        elif qKeyEvent.key() == Qt.Key_Down:
            if (
                self.next is not None
                and self.textCursor().blockNumber()  # noqa: W503
                == self.document().blockCount() - 1  # noqa: W503
            ):
                self.next.setFocus()
                return

        super().keyPressEvent(qKeyEvent)


class MainWindow(QWidget):
    def __init__(self, *args, width=575, height=175, **kwargs):
        super().__init__(*args, **kwargs)

        self.engine = MathEngine()

        self.setWindowTitle("CalcPlusPlus by AntonioJKim")
        self.width = width
        self.height = height
        self.resize(width, height)
        self.setStyleSheet("background-color:#F5F5F5;")

        self.layout = QVBoxLayout()
        self.layout.setSpacing(0)
        self.layout.setAlignment(Qt.AlignTop)

        self.editors = EquationEditor(self)

        self.setLayout(self.layout)

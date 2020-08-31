# -*- coding: utf-8 -*-
import sys

from PyQt5.QtCore import Qt
from PyQt5.QtGui import QFont, QFontMetrics
from PyQt5.QtWidgets import QVBoxLayout, QTextEdit, QWidget, QFrame

from .MathEngine import MathEngine


class TextEdit(QTextEdit):
    def __init__(self, *args, height_factor=2, **kwargs):
        super().__init__(*args, **kwargs)

        font = QFont("Computer Modern", 18)
        self.setFont(font)

        self.setFrameShape(QFrame.NoFrame)
        self.setLineWidth(0)

        self.setFixedHeight(QFontMetrics(font).lineSpacing() * height_factor)

    def update_size(self):
        size = self.document().size().toSize()
        self.setFixedHeight(size.height() + 3)


class EquationEditor(TextEdit):
    def __init__(self, parent, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self.parent = parent

        self.next = None
        self.prev = None
        self.textChanged.connect(self.textChangedAction)

        self.output = TextEdit(height_factor=1.5)
        self.output.setReadOnly(True)
        self.outputStr = ""

    def update_output(self):
        inputStr = self.toPlainText()
        cursor = self.textCursor()
        cursor_position = cursor.position()

        newInputStr, cursor_position = self.parent.engine.formatInput(
            inputStr, cursor_position
        )
        if inputStr != newInputStr:
            self.blockSignals(True)
            self.setText(newInputStr)
            cursor.setPosition(cursor_position)
            self.setTextCursor(cursor)
            self.blockSignals(False)
            inputStr = newInputStr

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
            if qKeyEvent.key() == Qt.Key_W:
                sys.exit(0)
            elif qKeyEvent.key() in (Qt.Key_Enter, Qt.Key_Return):
                editor = EquationEditor(self.parent)
                if self.next is not None:
                    i = self.parent.layout.indexOf(self.next)
                    self.parent.layout.insertWidget(i, editor)
                    self.parent.layout.insertWidget(i + 1, editor.output)

                    editor.next = self.next
                    editor.prev = self
                    self.next.prev = editor
                    self.next = editor
                else:
                    self.parent.layout.addWidget(editor)
                    self.parent.layout.addWidget(editor.output)

                    editor.prev = self
                    self.next = editor

                editor.setFocus()
                return
        elif (
            qKeyEvent.key() in (Qt.Key_Backspace, Qt.Key_Delete)
            and (self.prev is not None or self.next is not None)  # noqa: W503
            and len(self.toPlainText()) == 0  # noqa: W503
        ):
            self.parent.layout.removeWidget(self)
            self.parent.layout.removeWidget(self.output)
            if self.prev is None:
                self.parent.editor = self.next
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

        self.editor = EquationEditor(self)

        self.layout.addWidget(self.editor)
        self.layout.addWidget(self.editor.output)

        self.setLayout(self.layout)

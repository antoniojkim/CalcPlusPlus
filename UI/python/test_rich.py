# -*- coding: utf-8 -*-
import sys

from PyQt5.QtCore import Qt
from PyQt5.QtGui import QFont
from PyQt5.QtWidgets import QApplication, QVBoxLayout, QTextEdit, QWidget


class MainWindow(QWidget):
    def __init__(self, *args, width=575, height=175, **kwargs):
        super().__init__(*args, **kwargs)

        self.setWindowTitle("Test Rich Text")
        self.width = width
        self.height = height
        self.resize(width, height)
        self.setStyleSheet("background-color:#F5F5F5;")

        self.layout = QVBoxLayout()
        self.layout.setSpacing(0)
        self.layout.setAlignment(Qt.AlignTop)

        self.editor = QTextEdit()
        self.editor.setFont(QFont("STIXGeneral", 18))

        self.editor.setHtml("<p>x<sup>2<sup>3</sup></sup></p>")

        self.layout.addWidget(self.editor)
        self.setLayout(self.layout)


def main():
    app = QApplication(sys.argv)
    w = MainWindow()
    w.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()

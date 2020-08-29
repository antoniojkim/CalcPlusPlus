# -*- coding: utf-8 -*-
import argparse
import sys

from Calcpp.REPL import repl_main
from Calcpp.UI.MainWindow import MainWindow
from PyQt5.QtWidgets import QApplication


def main(args):
    if args.mode.lower() == "repl":
        repl_main(args)
    elif args.mode.lower() == "ui":
        app = QApplication(sys.argv)
        w = MainWindow()
        w.show()
        sys.exit(app.exec_())


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    mode = parser.add_argument(
        "-m",
        "--mode",
        type=str,
        choices=["repl", "REPL", "ui", "UI"],
        default="repl",
        help="CalcPlusPlus Mode",
    )
    main(parser.parse_args())

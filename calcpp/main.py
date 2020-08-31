# -*- coding: utf-8 -*-
import argparse
import sys

from PyQt5.QtWidgets import QApplication

from calcpp.REPL import repl_main
from calcpp.UI import MainWindow


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-m",
        "--mode",
        type=str,
        choices=["repl", "REPL", "ui", "UI"],
        default="repl",
        help="CalcPlusPlus Mode",
    )
    args = parser.parse_args()

    if args.mode.lower() == "repl":
        repl_main(args)
    elif args.mode.lower() == "ui":
        app = QApplication(sys.argv)
        w = MainWindow()
        w.show()
        sys.exit(app.exec_())


if __name__ == "__main__":
    main()

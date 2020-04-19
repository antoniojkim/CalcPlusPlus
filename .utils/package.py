# -*- coding: utf-8 -*-
import argparse
import os
from shutil import copyfile, copytree, rmtree
import subprocess as sp

CURR_DIR = os.getcwd()
PKG_DIR = os.path.join(CURR_DIR, ".package")
CALC_DIR = os.path.join(PKG_DIR, "CalcPlusPlus")
LIB_DIR = os.path.join(CALC_DIR, "libs")


def main(args):
    if os.path.isdir(PKG_DIR):
        rmtree(PKG_DIR)

    os.mkdir(PKG_DIR)
    os.mkdir(CALC_DIR)
    os.mkdir(LIB_DIR)
    os.mkdir(os.path.join(CALC_DIR, "bin"))

    CalcUI = os.path.join(CURR_DIR, "CalcUI", "CalcUI")
    assert os.path.isfile(CalcUI)

    copyfile(CalcUI, os.path.join(CALC_DIR, "bin", "CalcUI"))
    copyfile(os.path.join(CURR_DIR, ".utils", ".templates", f"Calculator.sh"), os.path.join(CALC_DIR, f"{args.exec}"))

    sp.call(f"chmod +x {os.path.join(CALC_DIR, 'bin', 'CalcUI')}", shell=True)
    sp.call(f"chmod +x {os.path.join(CALC_DIR, args.exec)}", shell=True)

    # proc = sp.Popen("qtchooser -print-env", shell=True, stdout=sp.PIPE)
    # stdout, stderr = proc.communicate()
    # QT_DIR = stdout.decode("utf-8").split(os.linesep)[1].split('"')[1]

    proc = sp.Popen(f"ldd {CalcUI}", shell=True, stdout=sp.PIPE)
    stdout, stderr = proc.communicate()
    depends = stdout.decode("utf-8").split(os.linesep)
    for dep in depends:
        dep = dep.split("=>")[-1].strip().split(" ")[0]
        if dep.startswith("/usr"):
            copyfile(dep, os.path.join(LIB_DIR, dep.split("/")[-1]))

    depends = [
        "/lib/x86_64-linux-gnu/libz.so.1",
        "/usr/lib/x86_64-linux-gnu/libQt5DBus.so.5",
        "/usr/lib/x86_64-linux-gnu/libQt5XcbQpa.so.5",
        "/usr/lib/x86_64-linux-gnu/libxcb-xinerama.so.0",
    ]
    for dep in depends:
        copyfile(dep, os.path.join(LIB_DIR, dep.split("/")[-1]))

    copytree("/usr/lib/x86_64-linux-gnu/qt5/plugins/platforms", os.path.join(CALC_DIR, "platforms"))

    os.chdir(PKG_DIR)
    sp.call(f"tar -czvf {PKG_DIR}/calcplusplus.tar.gz CalcPlusPlus/", shell=True)

    os.chdir(CURR_DIR)
    copyfile(
        os.path.join(PKG_DIR, "calcplusplus.tar.gz"),
        "/media/antonio/HDD-1/VirtualBox/Ubuntu1604/Shared/calcplusplus.tar.gz",
    )


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--exec", default="Calculator", help="Name of Executable")

    main(parser.parse_args())

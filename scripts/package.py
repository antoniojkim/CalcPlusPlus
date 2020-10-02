# -*- coding: utf-8 -*-
import argparse
import os
from shutil import copyfile
import subprocess as sp

CURR_DIR = os.getcwd()
PKG_DIR = os.path.join(CURR_DIR, ".package")
CALC_DIR = os.path.join(PKG_DIR, "CalcPlusPlus")
LIB_DIR = os.path.join(CALC_DIR, "libs")
PLATFORM_DIR = os.path.join(CALC_DIR, "platforms")


def main(args):
    # if os.path.isdir(PKG_DIR):
    #     rmtree(PKG_DIR)

    def mkdir(dir):
        if not os.path.isdir(dir):
            os.mkdir(dir)

    mkdir(PKG_DIR)
    mkdir(CALC_DIR)
    mkdir(LIB_DIR)
    mkdir(PLATFORM_DIR)
    mkdir(os.path.join(CALC_DIR, "bin"))

    calcpp = os.path.join(CURR_DIR, "UI", "calcpp")
    assert os.path.isfile(calcpp)

    copyfile(calcpp, os.path.join(CALC_DIR, "bin", "calcpp"))
    copyfile(
        os.path.join(CURR_DIR, ".utils", ".templates", "Calculator.sh"),
        os.path.join(CALC_DIR, f"{args.exec}"),
    )

    sp.call(f"chmod +x {os.path.join(CALC_DIR, 'bin', 'calcpp')}", shell=True)
    sp.call(f"chmod +x {os.path.join(CALC_DIR, args.exec)}", shell=True)

    # proc = sp.Popen("qtchooser -print-env", shell=True, stdout=sp.PIPE)
    # stdout, stderr = proc.communicate()
    # QT_DIR = stdout.decode("utf-8").split(os.linesep)[1].split('"')[1]

    proc = sp.Popen(f"ldd {calcpp}", shell=True, stdout=sp.PIPE)
    stdout, stderr = proc.communicate()
    depends = stdout.decode("utf-8").split(os.linesep)
    for dep in depends:
        dep = dep.split("=>")[-1].strip().split(" ")[0]
        if dep.startswith("/usr"):
            copyfile(dep, os.path.join(LIB_DIR, dep.split("/")[-1]))

    depends = [
        (dep, dep.split("/")[-1])
        for dep in (
            "/lib/x86_64-linux-gnu/libz.so.1",
            "/usr/lib/x86_64-linux-gnu/libQt5DBus.so.5",
            "/usr/lib/x86_64-linux-gnu/libQt5XcbQpa.so.5",
            "/usr/lib/x86_64-linux-gnu/libxcb-xinerama.so.0",
        )
    ] + [
        ("MathEngine/libMathEngine.so", "libMathEngine.so"),
        (".includes/gsl-2.6/cblas/.libs/libgslcblas.so.0.0.0", "libgslcblas.so.0"),
        (".includes/gsl-2.6/.libs/libgsl.so.25.0.0", "libgsl.so.25"),
    ]
    for dep, name in depends:
        dest = os.path.join(LIB_DIR, name)
        # if not os.path.isfile(dest):
        copyfile(dep, dest)

    platform_dir = "/usr/lib/x86_64-linux-gnu/qt5/plugins/platforms"
    for file in os.listdir(platform_dir):
        src = os.path.join(platform_dir, file)
        dest = os.path.join(PLATFORM_DIR, file)
        if not os.path.isfile(dest):
            copyfile(src, dest)

    if not args.no_tar:
        os.chdir(PKG_DIR)
        sp.call(f"tar -czvf {PKG_DIR}/calcplusplus.tar.gz CalcPlusPlus/", shell=True)

    # os.chdir(CURR_DIR)
    # copyfile(
    #     os.path.join(PKG_DIR, "calcplusplus.tar.gz"),
    #     "/media/antonio/HDD-1/VirtualBox/Ubuntu1604/Shared/calcplusplus.tar.gz",
    # )


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--exec", default="Calculator", help="Name of Executable")
    parser.add_argument(
        "--no-tar", action="store_true", help="If given, don't generate tar"
    )
    main(parser.parse_args())

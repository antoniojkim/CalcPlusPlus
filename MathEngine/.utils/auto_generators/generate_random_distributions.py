# -*- coding: utf-8 -*-
import os

from .Template import wrap, Specifications, Template, expr_dir


def generate_random_distributions(args=None):
    with Specifications("randomdistributions.yml") as specs:
        distributionNames = sorted(list(specs["distributions"].keys()))
        distributions = {
            name: val if val is not None else {}
            for name, val in specs["distributions"].items()
        }

        def nargs(name):
            return distributions[name].get("nargs", 1)

        def hasExpectation(name):
            return "expectation" in distributions[name]

        def hasVariance(name):
            return "variance" in distributions[name]

        with Template(
            "RandomDistributions.h",
            os.path.join(
                expr_dir, "RandomDistributionExpressions", "RandomDistributions.h"
            ),
        ) as template:
            template.replace(
                numDistributions=len(distributionNames),
                distributionNames=wrap((f'"{name}"' for name in distributionNames)),
                distributionNumArgs=wrap(
                    (str(nargs(name)) for name in distributionNames)
                ),
            )

        with Template(
            "RandomDistributionDirectory.cc",
            os.path.join(
                expr_dir,
                "RandomDistributionExpressions",
                "RandomDistributionDirectory.cc",
            ),
        ) as template:
            template.replace(
                randomDistributions=wrap(
                    (f"rand_{name}" for name in distributionNames)
                ),
                randomDistributionPDFs=wrap(
                    (f"pdf_{name}" for name in distributionNames)
                ),
                randomDistributionCDFPs=wrap(
                    (f"cdf_P_{name}" for name in distributionNames)
                ),
                randomDistributionCDFQs=wrap(
                    (f"cdf_Q_{name}" for name in distributionNames)
                ),
                randomDistributionCDFPinvs=wrap(
                    (f"cdf_Pinv_{name}" for name in distributionNames)
                ),
                randomDistributionCDFQinvs=wrap(
                    (f"cdf_Qinv_{name}" for name in distributionNames)
                ),
                randomDistributionExp=wrap(
                    (
                        f"Exp_{name}" if hasExpectation(name) else "nullptr"
                        for name in distributionNames
                    )
                ),
                randomDistributionVar=wrap(
                    (
                        f"Var_{name}" if hasExpectation(name) else "nullptr"
                        for name in distributionNames
                    )
                ),
            )

    return locals()


if __name__ == "__main__":
    generate_random_distributions()

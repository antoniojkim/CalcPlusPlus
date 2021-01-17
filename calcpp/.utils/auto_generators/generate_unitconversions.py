# -*- coding: utf-8 -*-

import os

import numpy as np

from .Template import wrap, Specifications, Template, expr_dir


def generate_unitconversions(args=None):
    with Specifications("unitconversions.yml") as specs:
        unitconversions = specs["unitconversions"]

        units = []
        abbrs = []
        unitTypes = []
        conversions = []

        with Template(
            "Units.h", os.path.join(expr_dir, "UnitConversionExpression", "Units.h"),
        ) as template:
            for category, specs in unitconversions["categories"].items():
                base = specs["base"]
                abbr = specs["baseabbr"]
                baseconversion = float(specs.get("baseconversion", 1))
                bc = f"*{1/baseconversion}" if baseconversion != 1 else ""

                units.append(base)
                abbrs.append(abbr)
                unitTypes.append(category)
                conversions.append(1)

                prefixes = specs.get("prefixes", {})
                if "baseprefixes" in specs:
                    prefixes.update(unitconversions["prefixes"])

                baseconversion = specs.get("baseconversion", 1)

                units.extend((f"{prefix}{base}" for prefix in prefixes.keys()))
                abbrs.extend((f"{prefix}{abbr}" for prefix in prefixes.values()))
                unitTypes.extend((category for p in prefixes))
                conversions.extend(
                    (
                        specs.get("custom", {}).get(
                            prefix, f"GSL_CONST_NUM_{prefix.upper()}"
                        )
                        for prefix in prefixes.keys()
                    )
                )

                units.extend(specs.get("conversions", {}).keys())
                abbrs.extend(specs.get("conversions", {}).values())
                unitTypes.extend((category for c in specs.get("conversions", {})))
                conversions.extend(
                    (
                        specs.get("custom", {}).get(
                            conv, f"GSL_CONST_MKSA_{conv.upper()}{bc}"
                        )
                        for conv in specs.get("conversions", {}).keys()
                    )
                )

            unq, unq_idx, unq_cnt = np.unique(
                abbrs, return_inverse=True, return_counts=True
            )
            assert np.all(unq_cnt == 1), np.array(abbrs)[unq_cnt != 1]

            assert len(units) == len(abbrs)
            assert len(units) == len(unitTypes)
            assert len(units) == len(conversions)

            categories = list(unitconversions["categories"].keys())

            unitconversions = list(zip(units, abbrs, unitTypes, conversions))
            unitconversions.sort(key=lambda k: k[1])
            units, abbrs, unitTypes, conversions = zip(*unitconversions)

            units = sorted(enumerate(units), key=lambda k: k[1])

            template.replace(
                UnitTypes=",\n\t".join((c.upper() for c in categories)),
                numUnits=len(units),
                unitNames=wrap((f'"{unit}"' for index, unit in units)),
                unitIndices=wrap((str(index) for index, unit in units)),
                unitAbbreviations=wrap((f'"{abbr}"' for abbr in abbrs)),
                unitTypes=wrap((t.upper() for t in unitTypes)),
                unitConversions=wrap(map(str, conversions)),
            )

    return locals()


if __name__ == "__main__":
    generate_unitconversions()

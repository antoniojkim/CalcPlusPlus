# -*- coding: utf-8 -*-
from sourcegen import SourceGenerator


greek_letters = {
    "Alpha": "Α",
    "Beta": "Β",
    "Chi": "Χ",
    "Delta": "Δ",
    "Epsilon": "Ε",
    "Eta": "Η",
    "Gamma": "Γ",
    "Iota": "Ι",
    "Kappa": "Κ",
    "Lambda": "Λ",
    "Mu": "Μ",
    "Nu": "Ν",
    "Omega": "Ω",
    "Omicron": "Ο",
    "Phi": "Φ",
    "Pi": "Π",
    "Psi": "Ψ",
    "Rho": "Ρ",
    "Sigma": "Σ",
    "Tau": "Τ",
    "Theta": "Θ",
    "Upsilon": "Υ",
    "Xi": "Ξ",
    "Zeta": "Ζ",
    "alpha": "α",
    "beta": "β",
    "chi": "χ",
    "delta": "δ",
    "epsilon": "ε",
    "eta": "η",
    "gamma": "γ",
    "iota": "ι",
    "kappa": "κ",
    "lambda": "λ",
    "mu": "μ",
    "nu": "ν",
    "omega": "ω",
    "omicron": "ο",
    "phi": "φ",
    "pi": "π",
    "psi": "ψ",
    "rho": "ρ",
    "sigma": "σ",
    "tau": "τ",
    "theta": "θ",
    "upsilon": "υ",
    "vphi": "ϕ",
    "xi": "ξ",
    "zeta": "ζ",
}

if __name__ == "__main__":
    letters = list(greek_letters.items())
    letters.sort(key=lambda k: ord(k[1]))

    with SourceGenerator("GreekLetters.h") as source:
        source["numGreekLetters"].set_text(len(greek_letters))
        source["shortestGreekLetterName"].set_text(min(map(len, greek_letters.keys())))
        source["longestGreekLetterName"].set_text(max(map(len, greek_letters.keys())))

        letter_names = sorted((l, i) for i, (l, u) in enumerate(letters))

        source["greekLetterNames"].set_text(
            (name for name, i in letter_names), quote='"', delimiter=", ", wrap_width=80
        )
        source["greekLetterIndices"].set_text(
            (str(i) for name, i in letter_names), delimiter=", ", wrap_width=80
        )
        source["greekLetters"].set_text(
            (f"\\u0{hex(ord(u))[2:]}" for name, u in letters),
            quote='"',
            delimiter=", ",
            wrap_width=80,
        )

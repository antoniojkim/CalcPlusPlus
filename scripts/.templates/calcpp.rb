cask "calcpp" do
  version "latest"
  sha256 "{SHA256SUM}"

  url "https://github.com/antoniojkim/CalcPlusPlus/releases/latest/download/calcplusplus.bottle.tgz"
  appcast "https://github.com/antoniojkim/CalcPlusPlus/releases.atom"
  name "CalcPlusPlus"
  desc "Advanced Scientific Calculator. Highly performant, robust, and easy to use"
  homepage "https://github.com/antoniojkim/CalcPlusPlus"

  depends_on formula: "gsl"
  depends_on formula: "qt"

  app "CalcPlusPlus/calcpp.app"
end

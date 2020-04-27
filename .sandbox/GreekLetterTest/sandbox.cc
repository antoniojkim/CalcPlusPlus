#include <iostream>
#include <unordered_map>
#include <regex>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

static const unordered_map<string, const char*> greekLetters = {
	{"Alpha", u8"\u0391"},
	{"Beta", u8"\u0392"},
	{"Gamma", u8"\u0393"},
	{"Delta", u8"\u0394"},
	{"Epsilon", u8"\u0395"},
	{"Zeta", u8"\u0396"},
	{"Eta", u8"\u0397"},
	{"Theta", u8"\u0398"},
	{"Iota", u8"\u0399"},
	{"Kappa", u8"\u039A"},
	{"Lambda", u8"\u039B"},
	{"Mu", u8"\u039C"},
	{"Nu", u8"\u039D"},
	{"Xi", u8"\u039E"},
	{"Omicron", u8"\u039F"},
	{"Pi", u8"\u03A0"},
	{"Rho", u8"\u03A1"},
	{"Sigma", u8"\u03A3"},
	{"Tau", u8"\u03A4"},
	{"Upsilon", u8"\u03A5"},
	{"Phi", u8"\u03A6"},
	{"Chi", u8"\u03A7"},
	{"Psi", u8"\u03A8"},
	{"Omega", u8"\u03A9"},
	{"alpha", u8"\u03B1"},
	{"beta", u8"\u03B2"},
	{"gamma", u8"\u03B3"},
	{"delta", u8"\u03B4"},
	{"epsilon", u8"\u03B5"},
	{"zeta", u8"\u03B6"},
	{"eta", u8"\u03B7"},
	{"theta", u8"\u03B8"},
	{"iota", u8"\u03B9"},
	{"kappa", u8"\u03BA"},
	{"lambda", u8"\u03BB"},
	{"mu", u8"\u03BC"},
	{"nu", u8"\u03BD"},
	{"xi", u8"\u03BE"},
	{"omicron", u8"\u03BF"},
	{"pi", u8"\u03C0"},
	{"rho", u8"\u03C1"},
	{"sigma", u8"\u03C3"},
	{"tau", u8"\u03C4"},
	{"upsilon", u8"\u03C5"},
	{"phi", u8"\u03C6"},
	{"chi", u8"\u03C7"},
	{"psi", u8"\u03C8"},
	{"omega", u8"\u03C9"},
};

static const std::wregex greekLetterRegex ((const wchar_t*) "^[\\u0391-\\u03C9]");

inline std::wstring convert( const std::string& as )
{
    wchar_t* buf = new wchar_t[as.size() * 2 + 2];
    swprintf( buf, as.size() * 2 + 2, L"%S", as.c_str() );
    std::wstring rval = buf;
    delete[] buf;
    return rval;
}

int main() {
	ostringstream out;
    for (auto& letter : greekLetters){
        cout << letter.first << ": " << letter.second << endl;
		out << letter.second;
    }
	cout << endl;

	cout << out.str() << endl;

	std::string s = out.str();
	cout << s << endl;
}

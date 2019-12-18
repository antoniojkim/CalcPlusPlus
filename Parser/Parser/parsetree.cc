
#include "parsetree.h"
#include "../Scanner/scanner.h"

#include <sstream>

using namespace std;

Terminal* ParseTree::getTerminal() { throw "Trying to get terminal from nonterminal"; }
NonTerminal* ParseTree::getNonTerminal() { throw "Trying to get nonterminal from terminal"; }
bool ParseTree::isEmpty() { throw "Trying to see if terminal is empty"; }

Terminal::Terminal(const Token& token) : token{token}, typeString{getTypeString(token.type)} {}
bool Terminal::isTerminal() { return true; }
Terminal* Terminal::getTerminal() { return this; }
std::string& Terminal::getRoot() { return typeString; }
std::string& Terminal::getFirst() { return typeString; }

Token& Terminal::getToken() { return token; }

std::ostream& Terminal::print(std::ostream& out, const std::string& indent) {
    out << indent << getTypeString(token.type) << " " << token.lexeme << endl;
    return out;
}

NonTerminal::NonTerminal(const list<string>& rule) {
    bool rootSet = false;
    bool first = true;
    ostringstream oss;
    for (auto& s : rule) {
        if (!rootSet) {
            root = s;
            rootSet = true;
            oss << s;
        } else {
            if (first) {
                first = false;
                this->first = s;
            }
            oss << " " << s;
        }
    }
    this->rule = oss.str();
}

void NonTerminal::reserve(const int& num) {
    children.clear();
    children.reserve(num);
}

void NonTerminal::addChild(unique_ptr<ParseTree>& child) { children.emplace_back(std::move(child)); }

vector<unique_ptr<ParseTree>>& NonTerminal::getChildren() { return children; }
std::unique_ptr<ParseTree>& NonTerminal::getChild(const int& i) { return children[i]; }

string& NonTerminal::getRoot() { return root; }
string& NonTerminal::getFirst() { return first; }
std::string& NonTerminal::getRule() { return rule; }
bool NonTerminal::isTerminal() { return false; }
NonTerminal* NonTerminal::getNonTerminal() { return this; }
bool NonTerminal::isEmpty() { return children.empty(); }

std::ostream& NonTerminal::print(std::ostream& out, const std::string& indent) {
    out << indent << rule << endl;
    for (auto& child : children) {
        // if (!child->isTerminal()){
        child->print(out, indent + "    ");
        // }
    }
    return out;
}

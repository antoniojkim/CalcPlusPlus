
#include "parsetree.h"
#include "../Scanner/scanner.h"

#include <sstream>

using namespace std;
using namespace Scanner;

TerminalTree* ParseTree::getTerminalTree() { throw "Trying to get TerminalTree from nonTerminalTree"; }
NonTerminalTree* ParseTree::getNonTerminalTree() { throw "Trying to get nonTerminalTree from TerminalTree"; }
bool ParseTree::isEmpty() { throw "Trying to see if TerminalTree is empty"; }

TerminalTree::TerminalTree(const Token& token) : token{token}, typeString{typeStrings[token.type]} {}
bool TerminalTree::isTerminalTree() { return true; }
TerminalTree* TerminalTree::getTerminalTree() { return this; }
int TerminalTree::getRoot() { return token.type; }
int TerminalTree::getFirst() { return token.type; }

Token& TerminalTree::getToken() { return token; }

std::ostream& TerminalTree::print(std::ostream& out, const std::string& indent) {
    out << indent << typeStrings[token.type] << " " << token.lexeme << endl;
    return out;
}

NonTerminalTree::NonTerminalTree(const int rule, const int* ruleArray, const int ruleSize):
    rule{rule}, ruleArray{ruleArray}, ruleSize{ruleSize} {
    children.clear();
    children.reserve(ruleSize - 1);
}

void NonTerminalTree::addChild(unique_ptr<ParseTree>& child) { children.emplace_back(std::move(child)); }

vector<unique_ptr<ParseTree>>& NonTerminalTree::getChildren() { return children; }
std::unique_ptr<ParseTree>& NonTerminalTree::getChild(int i) { return children[i]; }
NonTerminalTree* NonTerminalTree::operator[](int i) {
    if (!children[i]->isTerminalTree()){
        return (NonTerminalTree*) children[i].get();
    }
    throw "Not a NonTerminal Tree";
}

int NonTerminalTree::getRoot() { return ruleArray[0]; }
int NonTerminalTree::getFirst() { return ruleArray[1]; }
int NonTerminalTree::getRule() { return rule; }
bool NonTerminalTree::isTerminalTree() { return false; }
NonTerminalTree* NonTerminalTree::getNonTerminalTree() { return this; }
bool NonTerminalTree::isEmpty() { return children.empty(); }

std::ostream& NonTerminalTree::print(std::ostream& out, const std::string& indent) {
    out << indent << rule << endl;
    for (auto& child : children) {
        // if (!child->isTerminalTree()){
        child->print(out, indent + "    ");
        // }
    }
    return out;
}

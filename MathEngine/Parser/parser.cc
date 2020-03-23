
#include "parser.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include "../Scanner/scanner.h"
#include "StringUtils.h"

using namespace std;
using namespace Scanner;

#ifdef INCLUDE_TRANSITIONS

#include "transitions.h"

Parser::Parser() {}

#else

template <class T>
T getNext(const string& str) {
    istringstream iss{str};
    T i;
    if (!(iss >> i)) throw "Failed to get next from string";
    return i;
}

template <class T>
T getNext(istringstream& iss) {
    T i;
    if (!(iss >> i)) throw "Failed to get next from istringstream";
    return i;
}

Parser::Parser(const std::string& lr1Path) {
    ifstream f{lr1Path};
    string s;

    if (!getline(f, s)) throw "Expected Line with number of terminals";
    int numTerminals = getNext<int>(s);
    for (int i = 0; i < numTerminals; ++i) {
        if (!getline(f, s)) throw "Expected a terminal";
        string terminal = getNext<string>(s);
        if (terminals.count(terminal) > 0)
            throw "Duplicate terminal: " + terminal;
        terminals[terminal] = true;
    }

    if (!getline(f, s)) throw "Expected Line with number of nonterminals";
    int numNonTerminals = getNext<int>(s);
    for (int i = 0; i < numNonTerminals; ++i) {
        if (!getline(f, s)) throw "Expected a nonterminal";
        string nonterminal = getNext<string>(s);
        if (nonterminals.count(nonterminal) > 0)
            throw "Duplicate nonterminal: " + nonterminal;
        nonterminals[nonterminal] = true;
    }

    if (!getline(f, s)) throw "Expected Line with start symbol";
    startSymbol = getNext<string>(s);

    if (!getline(f, s)) throw "Expected Line with number of rules";
    int numRules = getNext<int>(s);
    rules.reserve(numRules);
    for (int i = 0; i < numRules; ++i) {
        if (!getline(f, s)) throw "Expected a rule";
        rules.emplace_back(split(s, ' '));
    }

    if (!getline(f, s)) throw "Expected Line with number of states";
    numStates = getNext<int>(s);
    if (!getline(f, s)) throw "Expected Line with number of transitions";
    int numTransitions = getNext<int>(s);
    for (int i = 0; i < numTransitions; ++i) {
        if (!getline(f, s)) throw "Expected a rule";
        istringstream transition{s};
        int state = getNext<int>(transition);
        string symbol = getNext<string>(transition);
        string action = getNext<string>(transition);
        int nextStateOrRule = getNext<int>(transition);

        if (state < 0 || state >= numStates) throw "Invalid State";
        if (terminals.count(symbol) == 0 and nonterminals.count(symbol) == 0)
            throw "Invalid Symbol: " + symbol;

        if (transitions.count(state) == 0) {
            transitions[state] = map<string, pair<bool, int>>();
        }
        if (action == "SHIFT") {
            transitions[state][symbol] = make_pair(false, nextStateOrRule);
        } else if (action == "REDUCE") {
            transitions[state][symbol] = make_pair(true, nextStateOrRule);
        } else {
            throw "Invalid Action: " + action;
        }
    }
}

#endif // INCLUDE_TRANSITIONS

std::unique_ptr<ParseTree> Parser::parse(const std::string& input,
                                         const bool& showTokens) {
    list<Token> tokens;
    tokens.emplace_back(Token{"BOF_", Type::BOF_});
    scan(input, tokens);
    tokens.emplace_back(Token{"EOF_", Type::EOF_});
    if (showTokens) {
        print(cout, tokens, "\n", true) << endl << endl;
    }
    return parse(tokens);
}

std::unique_ptr<ParseTree> Parser::parse(list<Token>& tokens) {
    // int currentState = 0;
    list<std::unique_ptr<ParseTree>> symbolStack;
    list<int> stateStack;
    stateStack.emplace_back(0);

    for (auto& token : tokens) {
        Type type = token.type;
        while (transitions.at(stateStack.back()).count(type) > 0 &&
               transitions.at(stateStack.back()).at(type) >= 0) { // If transition exists and is a reduction
            int rule = transitions.at(stateStack.back()).at(type);

            int ruleSize = rules.at(rule)[0];
            NonTerminalTree* nt = new NonTerminalTree(rule, rules.at(rule).data()+1, ruleSize);
            
            for (int j = 1; j < ruleSize; ++j) {
                nt->addChild(symbolStack.back());
                symbolStack.pop_back();
                stateStack.pop_back();
            }
            reverse(nt->getChildren().begin(), nt->getChildren().end());
            std::unique_ptr<ParseTree> tree{nt};
            symbolStack.emplace_back(std::move(tree));
            int nextState = -transitions.at(stateStack.back()).at(rules.at(rule)[1])-1;
            stateStack.emplace_back(nextState);
        }

        symbolStack.emplace_back(make_unique<TerminalTree>(token));

        int nextState = -transitions.at(stateStack.back()).at(symbolStack.back()->getRoot())-1;
        if (nextState == 0) {
            ostringstream oss;
            oss << "ERROR at \"" << token.lexeme << "\" of type " << typeStrings[type] << endl
                << "State Stack: " << endl;
            for (auto& state : stateStack) {
                oss << "    " << state << endl;
            }
            throw oss.str();
        }

        stateStack.emplace_back(nextState);
    }

    // cout << symbolStack.size() << endl;
    // for (auto& s : symbolStack){
    //     cout << s->getRoot() << endl;
    // }
    symbolStack.pop_back();

    unique_ptr<ParseTree> tree = std::move(symbolStack.back());

    return tree;
}

string actions[2] = {"SHIFT", "REDUCE"};

#ifdef INCLUDE_TRANSITIONS

ostream& operator<<(ostream& out, Parser& parser) {
    out << "Terminals:" << endl;
    for (int i = 0; i < numTerminals; ++i) {
        out << "    " << getTerminalString((Terminal) i) << endl;
    }
    out << "Non Terminals:" << endl;
    for (int i = 0; i < numNonTerminals; ++i) {
        out << "    " << getNonTerminalString((NonTerminal) i) << endl;
    }
    out << "Rules:" << endl;
    for (int i = 0; i < numRules; ++i){
        out << "   ";
        int ruleSize = rules[i][0]+1;
        for (int j = 1; j < ruleSize; ++j){
            int r = rules[i][j];
            if (r >= 0){
                out << ' ' << getTerminalString((Terminal) r);
            }
            else{
                out << ' ' << getNonTerminalString((NonTerminal) r);
            }
        }
    }
    out << "Transitions:" << endl;
    for (int state = 0; state < numTransitions; ++state){
        for (auto& symbol : transitions.at(state)) {
            bool reduce = symbol.second >= 0;
            int nextState = reduce ? symbol.second : -symbol.second-1;
            out << "    " << state << " " << symbol.first << " "
                << actions[reduce] << " " << nextState
                << endl;
        }
    }
    return out;
}

#else

ostream& operator<<(ostream& out, Parser& parser) {
    out << "Terminals:" << endl;
    for (auto& terminal : parser.terminals) {
        out << "    " << terminal.first << endl;
    }
    out << "Non Terminals:" << endl;
    for (auto& nonterminal : parser.nonterminals) {
        out << "    " << nonterminal.first << endl;
    }
    out << "Start Symbol:" << parser.startSymbol << endl;
    out << "Rules:" << endl;
    for (auto& rule : parser.rules) {
        out << "    " << join(rule, ' ') << endl;
    }
    out << "Num States:" << parser.numStates << endl;
    out << "Transitions:" << endl;
    for (auto& state : parser.transitions) {
        for (auto& symbol : state.second) {
            out << "    " << state.first << " " << symbol.first << " "
                << actions[symbol.second.first] << " " << symbol.second.second
                << endl;
        }
    }
    return out;
}

#endif // INCLUDE_TRANSITIONS


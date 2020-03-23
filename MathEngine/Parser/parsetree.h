#ifndef PARSETREE_H
#define PARSETREE_H

#include <memory>
#include <string>
#include <vector>
#include "../Scanner/scanner.h"

class TerminalTree;
class NonTerminalTree;

struct ParseTree {
    virtual int getRoot() = 0;
    virtual int getFirst() = 0;
    virtual bool isTerminalTree() = 0;
    virtual TerminalTree* getTerminalTree();
    virtual NonTerminalTree* getNonTerminalTree();
    virtual bool isEmpty();

    // virtual std::unique_ptr<ParseTree> eval() = 0;

    virtual std::ostream& print(std::ostream& out,
                                const std::string& indent = "") = 0;
};

class TerminalTree : public ParseTree {
    Scanner::Token token;
    std::string typeString;

   public:
    TerminalTree(const Scanner::Token& token);

    int getRoot() override;
    int getFirst() override;
    bool isTerminalTree() override;
    TerminalTree* getTerminalTree() override;
    Scanner::Token& getToken();

    std::ostream& print(std::ostream& out, const std::string& indent) override;
};

class NonTerminalTree : public ParseTree {
    const int rule;
    const int* ruleArray;
    const int ruleSize;
    std::vector<std::unique_ptr<ParseTree>> children;

   public:
    NonTerminalTree(const int rule, const int* ruleArray, const int ruleSize);

    void addChild(std::unique_ptr<ParseTree>& child);
    std::vector<std::unique_ptr<ParseTree>>& getChildren();
    std::unique_ptr<ParseTree>& getChild(int i);
    NonTerminalTree* operator[](int i);

    int getRoot() override;
    int getFirst() override;
    int getRule();
    bool isTerminalTree() override;
    NonTerminalTree* getNonTerminalTree() override;
    bool isEmpty() override;

    virtual std::ostream& print(std::ostream& out,
                                const std::string& indent) override;
};

#endif  // PARSETREE_H

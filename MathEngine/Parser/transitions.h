#ifndef __TRANSITIONS_H__
#define __TRANSITIONS_H__

#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

extern std::unordered_set<std::string> terminals;

extern std::unordered_set<std::string> nonterminals;

extern std::vector<std::list<std::string>> rules;

extern std::unordered_map<int, std::unordered_map<std::string, std::pair<bool, int>>> transitions;

#endif // __TRANSITIONS_H__

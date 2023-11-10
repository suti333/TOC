#include <bits/stdc++.h>
using namespace std;

class NFA{
private:
    vector<string> states;
    vector<char> alphabet;
    map<pair<string, char>, vector<string>> transition_function;
    string initial_state;
    vector<string> final_states;

public:
    NFA(vector<string> Q, vector<char> E, map<pair<string, char>, vector<string>> D, string q0, vector<string> F){
        states = Q;
        alphabet = E;
        transition_function = D;
        initial_state = q0;
        final_states = F;
    }

    bool check_if_str_belongs_to_NFA(string str){
        set<string> curr_states = {initial_state};

        for(auto &symbol : str){
            set<string> next_states;
            for(auto &state: curr_states){
                pair<string, char> transition_key = {state, symbol};
                auto it = transition_function.find(transition_key);
                if (it != transition_function.end()) {
                    next_states.insert(it->second.begin(), it->second.end());
                }
            }
            curr_states = next_states;
        }

        for (auto &state : curr_states) {
            if (count(final_states.begin(), final_states.end(), state))  return true;
        }

        return false;
    }
};

int main() {
    //NFA accepting all strings whose second last symbol is 1

    vector<string> states = {"q0", "q1", "q2"};
    vector<char> alphabet = {'0', '1'};
    map<pair<string, char>, vector<string>> transition_function = {
        {{"q0", '0'}, {"q0"}},
        {{"q0", '1'}, {"q0", "q1"}},
        {{"q1", '0'}, {"q2"}},
        {{"q1", '1'}, {"q2"}}
    };
    string initial_state = "q0";
    vector<string> final_states = {"q2"};

    NFA nfa(states, alphabet, transition_function, initial_state, final_states);

    string str;
    cout<<"Enter string to check: ";
    cin>>str;

    if(nfa.check_if_str_belongs_to_NFA(str))  cout<<"String belongs to the language of NFA"<<endl;
    else  cout<<"String does not belongs to the language of NFA"<<endl;

    return 0;
}


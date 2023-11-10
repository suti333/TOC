#include <bits/stdc++.h>
using namespace std;

class eNFA{
private:
    vector<string> states;
    vector<char> alphabet;
    map<pair<string, char>, vector<string>> transition_function;
    map<string, vector<string>> epsilon_transitions;
    string initial_state;
    vector<string> final_states;

    void epsilonClosure(set<string> &curr_states){
        set<string> epsilon_states;
        for (auto &state : curr_states) {
            auto it = epsilon_transitions.find(state);

            if (it != epsilon_transitions.end()) {
                epsilon_states.insert(it->second.begin(), it->second.end());
            }
        }
        curr_states.insert(epsilon_states.begin(), epsilon_states.end());
    }

public:
    eNFA(vector<string> Q, vector<char> E, map<pair<string, char>, vector<string>> D, map<string, vector<string>> e_D, string q0, vector<string> F){
        states = Q;
        alphabet = E;
        transition_function = D;
        epsilon_transitions = e_D;
        initial_state = q0;
        final_states = F;
    }

    bool check_if_str_belongs_to_NFA(string str){
        set<string> curr_states = {initial_state};

        epsilonClosure(curr_states);
        for(auto &symbol : str){
            set<string> next_states;
            for(auto &state: curr_states){
                pair<string, char> transition_key = {state, symbol};
                auto it = transition_function.find(transition_key);
                if (it != transition_function.end()) {
                    next_states.insert(it->second.begin(), it->second.end());
                }
            }
            epsilonClosure(next_states);
            curr_states = next_states;
        }

        for (auto &state : curr_states) {
            if (count(final_states.begin(), final_states.end(), state))  return true;
        }

        return false;
    }
};

int main() {
    //e-NFA for the regular expression 1*0

    vector<string> states = {"q0", "q1", "q2", "q3", "q4"};
    vector<char> alphabet = {'0', '1'};
    map<pair<string, char>, vector<string>> transition_function = {
        {{"q1", '1'}, {"q2"}},
        {{"q3", '0'}, {"q4"}}
    };
    map<string, vector<string>> epsilon_transitions = {
        {"q0", {"q1", "q4"}},
        {"q2", {"q1", "q3"}}
    };
    string initial_state = "q0";
    vector<string> final_states = {"q4"};

    eNFA enfa(states, alphabet, transition_function, epsilon_transitions, initial_state, final_states);

    string str;
    cout<<"Enter string to check: ";
    cin>>str;

    if(enfa.check_if_str_belongs_to_NFA(str))  cout<<"String belongs to the language of e-NFA"<<endl;
    else  cout<<"String does not belongs to the language of e-NFA"<<endl;

    return 0;
}



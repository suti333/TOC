#include <bits/stdc++.h>
using namespace std;

class DFA{
private:
    vector<string> states;
    vector<char> alphabet;
    map<pair<string, char>, string> transition_function;
    string initial_state;
    vector<string> final_states;

public:
    DFA(vector<string> Q, vector<char> E, map<pair<string, char>, string> D, string q0, vector<string> F){
        states = Q;
        alphabet = E;
        transition_function = D;
        initial_state = q0;
        final_states = F;
    }

    bool check_if_str_belongs_to_DFA(string str){
        string curr_state = initial_state;
        for(auto &symbol : str){
            pair<string, char> transition_key = {curr_state, symbol};
            curr_state = transition_function[transition_key];
        }

        return count(final_states.begin(), final_states.end(), curr_state);
    }
};

int main() {
    // DFA accepting all strings with a substring 01
    
    vector<string> states = {"q0", "q1", "q2"};
    vector<char> alphabet = {'0', '1'};
    map<pair<string, char>, string> transition_function = {
        {{"q0", '0'}, "q2"},
        {{"q0", '1'}, "q0"},
        {{"q1", '0'}, "q1"},
        {{"q1", '1'}, "q1"},
        {{"q2", '0'}, "q2"},
        {{"q2", '1'}, "q1"}
    };
    string initial_state = "q0";
    vector<string> final_states = {"q1"};

    DFA dfa(states, alphabet, transition_function, initial_state, final_states);

    string str;
    cout<<"Enter string to check: ";
    cin>>str;

    if(dfa.check_if_str_belongs_to_DFA(str))  cout<<"String belongs to the language of DFA"<<endl;
    else  cout<<"String does not belongs to the language of DFA"<<endl;

    return 0;
}


#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

#define n 3 // number of states
#define m 1 // number of final states
#define d 2 // number of alphabets
#define l 5 // number of transitions

bool NFA(int initial_state, int next_state, int final_states[], int transFun[][d][n], string s, int ind, int length)
{
    // cout << "Index " << ind << endl;
    if(ind == length)
    {
        for(int i = 0; i < m; i++){
            if(final_states[i] == next_state) return true;
        }
        return false;
    }

    bool ans = false;
    for(int i=0; i < n; i++)
    {
        if(transFun[next_state][s[ind]-'0'][i] == 1)
        {
            // cout << "Index " << ind << endl;
            ans = NFA(next_state, i, final_states, transFun, s, ind+1, length);
            if(ans == true) return true;
        }
    }
    return ans;

}

int main()
{

    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Error opening the file." << endl;
        return 1;
    }
    
    string statesLine, alphabetsLine, initS, finalStatesLine;
    getline(inputFile, statesLine);
    getline(inputFile, alphabetsLine);
    getline(inputFile, initS);
    getline(inputFile, finalStatesLine);

    // Parse states, alphabets, and final states
    istringstream statesStream(statesLine);
    istringstream alphabetsStream(alphabetsLine);
    istringstream finalStatesStream(finalStatesLine);
    
    vector <string> states(istream_iterator<string>(statesStream), {});
    vector <string> alphabets(istream_iterator<string>(alphabetsStream), {});
    vector <string> finals(istream_iterator<string>(finalStatesStream), {});

    int transFun[n][d][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < d; j++){
            for(int k = 0; k < n; k++){
                transFun[i][j][k] = 0;
            }
        }
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream transitionStream(line);
        string fromState, toState;
        int symbol; 

        transitionStream >> fromState >> symbol >> toState;
        transFun[fromState[1]-'0'][symbol][toState[1]-'0'] = 1;

    }

    inputFile.close();

    cout << "States are: ";
    for(int i = 0; i < n; i++) cout << states[i] << " ";
    cout << endl;

    cout << "Alphabets are: ";
    for(int i = 0; i < d; i++) cout << alphabets[i] << " ";
    cout << endl;

    cout << "Initial state is: " << initS << endl;

    cout << "Final states are: ";
    for(int i = 0; i < m; i++) cout << finals[i] << " ";
    cout << endl;

    cout << "\nTRANSITION FUNCTIONS are\n" << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < d; j++){
            for(int k = 0; k < n; k++){
                if(transFun[i][j][k] == 1) cout << "q" << i << "->" << j << "->q" << k << endl;
            }
        }
    }

    cout << "Enter a string to test if it will be accepted by the nfa or not: ";
    string s; cin >> s;
    int size = s.size();
    // main function goes here

    int initial_state = initS[1] - '0';
    int final_states[m];
    for(int i = 0; i < m; i++) final_states[i] = finals[i][1] - '0';

    int ind = 0;
    bool ans = false;

    // cout << "Initial state : " << initial_state << endl;
    // cout << s[ind] << endl;

    for(int i=0; i < n; i++)
    {
        if(transFun[initial_state][s[ind]-'0'][i] == 1)
        {
            ans = NFA(initial_state, i, final_states, transFun, s, ind+1, size);
            if(ans == true) break;
        }
    }

    if(ans) cout << "\nGiven string will be accepted" << endl;
    else cout << "\nGiven string will not be accepted" << endl;

    return 0;

}
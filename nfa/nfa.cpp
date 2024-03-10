#include <iostream>
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
    freopen("input.txt", "r", stdin);

    // cout << "Enter all the states of NFA: ";
    string states[n];
    for(int i = 0; i < n; i++) cin >> states[i]; 

    // cout << "Enter the alphabets: ";
    string alphabets[d];
    for(int i = 0; i < d; i++) cin >> alphabets[i];

    // cout << "Enter the initial state of NFA: ";
    string initS; cin >> initS;

    // cout << "Enter the final states of NFA: ";
    string finals[m];
    for(int i = 0; i < m; i++) cin >> finals[i];

    int transFun[n][d][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < d; j++){
            for(int k = 0; k < n; k++){
                transFun[i][j][k] = 0;
            }
        }
    }

    // cout << "Enter the transition functions: ";
    for(int i = 0; i < l; i++){
        string iS; cin >> iS;
        int a; cin >> a;
        string fS; cin >> fS;
        transFun[iS[1]-'0'][a][fS[1]-'0'] = 1;
    }

    cout << "\nTRANSITION FUNCTIONS are\n" << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < d; j++){
            for(int k = 0; k < n; k++){
                if(transFun[i][j][k] == 1) cout << "q" << i << "->" << j << "->q" << k << endl;
            }
        }
    }

    // cout << "Enter a string to test if it will be accepted by the nfa or not: ";
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

    if(ans) cout << "\n Given string will be accepted" << endl;
    else cout << "\n Given string will not be accepted" << endl;

    return 0;

}
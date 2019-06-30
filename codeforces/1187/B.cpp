#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    string s;
    cin>>s;
    int freqs[26][n];
    for(int i = 0; i<26; i++){
        freqs[i][0]=0;
    }
    
        freqs[s[0]-'a'][0]++;
    for(int j = 1; j<s.size(); j++){
        for(int i = 0; i<26; i++){
            freqs[i][j] = freqs[i][j-1];
        }
        freqs[s[j]-'a'][j]++;
    }
    int m;
    cin>>m;
    for(int i = 0; i<m; i++){
        string a;
        cin>>a;
        vector<int> freq(26);
        for(int j = 0; j<a.size(); j++){
            freq[a[j]-'a']++;
        }
        int ans = -1;
        for(int k = 0; k<26; k++){
            auto r = lower_bound(freqs[k], freqs[k]+n, freq[k]) - freqs[k];
            ans = max(ans, r+1);
        }
        cout<<ans<<"\n";
    }
}
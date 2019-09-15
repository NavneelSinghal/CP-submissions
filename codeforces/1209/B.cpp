

    #include<bits/stdc++.h>
    using namespace std;
    int main(){
        int n;
        cin>>n;
        string s;
        cin>>s;
        int state[n];
        
        int a[n];
        int b[n];
        
        for(int i = 0; i<n; i++){
            cin>>a[i]>>b[i];
            state[i] = s[i]-'0';
        }
        
        int ans = 0;
        for(int i = 0; i<n; i++){
            ans += state[i];
        }
        for(int step = 1; step <= 1000; step++){
            for(int i = 0; i<n; i++){
                if(step >= b[i] && (step%a[i])==(b[i]%a[i])){
                    state[i] = 1-state[i];
                }
            }
            int sum = 0;
            for(int i = 0; i<n; i++){
                sum += state[i];
            }
            ans = max(sum, ans);
        }
        cout<<ans<<endl;
    }
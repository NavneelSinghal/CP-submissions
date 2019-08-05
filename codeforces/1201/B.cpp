    #include<bits/stdc++.h>
    using namespace std;
    int main(){
        int n;
        cin>>n;
        long long int sum = 0ll;
        long long int mx = 0ll;
        for(int i = 0; i<n; i++){
            long long int x;
            cin>>x;
            mx = max(mx, x);
            sum+=x;
        }
        if(2*mx <= sum && sum%2==0){
            cout<<"YES";
        }
        else cout<<"NO";
        return 0;
    }
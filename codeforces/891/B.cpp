    #pragma GCC optimize("Ofast")
    #include<bits/stdc++.h>
     
    using namespace std;
    #define ll long long
    #define int ll
    #define F first
    #define S second
     
    signed main(){
    	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    	int n;
    	cin>>n;
    	vector<int> x(n);
    	vector<int> a(n);
    	for(int i = 0; i<n; i++){
    		cin>>a[i];
    		x[i] = a[i];
    	}
    	sort(x.begin(), x.end());
    	map<int, int> m;
    	for(int i = 0; i<n; i++){
			m[x[i]] = i;
		}
    	for(int i = 0; i<n; i++){
    		cout<<x[(m[a[i]] + 1)%n]<<" ";
    	}
    	return 0;
    }
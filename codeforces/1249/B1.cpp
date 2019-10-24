    #include<bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    #define int ll
    signed main() {
        int t;
        cin>>t;
        while(t--){
            int n;
            cin>>n;
            vector<int> p(n), visited(n), ans(n);
            for(int i = 0; i<n; i++){
                cin>>p[i];
                p[i]--;
            }
            for (int j = 0; j < n; ++j) {
    			if (!visited[j]) {
    				vector<int> cur;
    				while (!visited[j]) {
    					cur.push_back(j);
    					visited[j] = true;
    					j = p[j];
    				}
    				for (auto el : cur) ans[el] = cur.size();
    			}
    		}
            for(int i = 0; i<n; i++){
                cout<<ans[i]<<" ";
            }
            cout<<endl;
        }
    }
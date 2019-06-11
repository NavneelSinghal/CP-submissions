#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,S;
    cin>>n>>S;
    vector<int> a(n);
    for(int i=0;i<n;i++) {
        cin>>a[i];
    }
    
    sort(a.begin(),a.end());
    
    long long l=0,r=0;
    
    for(int i=0;i<n/2;i++)
    {
    	if(a[i]>S) l+=a[i]-S;
    	if(a[n-1-i]<S) r+=S-a[n-1-i];
    }
    cout<<l+r+abs(a[n/2]-S);
    return 0;
}
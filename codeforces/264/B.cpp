    #include<bits/stdc++.h>
    using namespace std;
    int s[100010];
    int dp[100010];
     int x=0,j;
    int main()
    {
     for(int i=2;i<=100010;i++)if(s[i]==0) for( j=i;j<=100010;j+=i)s[j]=i;
     
     
    int n;
    cin>>n;
    int res=1;
    for(int i=1;i<=n;i++)
    {
        int a;
        cin>>a;
        for(x=0, j=a;j>1;j/=s[j]) x=max(x,dp[s[j]]);
        for(j=a;j>1;j/=s[j]) dp[s[j]]=max(dp[s[j]],x+1);
        res=max(res,x+1);
    }
    cout<<res;
    }
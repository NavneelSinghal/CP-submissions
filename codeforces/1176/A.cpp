#include <bits/stdc++.h>
using namespace std;
int T,ans;
long long n; 
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		ans=0;
		scanf("%lld",&n);
		while(n%2==0) n/=2,ans++;
		while(n%3==0) n/=3,ans+=2;
		while(n%5==0) n/=5,ans+=3;
		if(n!=1) printf("-1\n");
		else printf("%d\n",ans);
	}
	return 0;
}
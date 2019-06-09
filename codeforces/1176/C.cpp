#include <bits/stdc++.h>
using namespace std;
const int Maxn=500005;
const int a[]={0,4,8,15,16,23,42};
int T,n,b[Maxn],cnt[8]; 
int main()
{
	scanf("%d",&n);
	cnt[0]=0x3f3f3f3f;
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=6;j++)
			if(b[i]==a[j]&&cnt[j-1])
				cnt[j]++,cnt[j-1]--;
	printf("%d\n",n-6*cnt[6]);
	return 0;
}
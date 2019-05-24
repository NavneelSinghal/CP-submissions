#include<bits/stdc++.h>
long long int binpow(long long int a, long long int b){
	long long int res = 1;
	while(b){
		if(b&1){
			res*=a;
		}
		b=b>>1;
		a=a*a;
	}
	return res;
}

using namespace std;
int main(){
    int n;
    cin>>n;
    long long ans=1;
    cout<<(9*n-3)*binpow(4, n-3);
}
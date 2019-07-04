#include<bits/stdc++.h>
using namespace std;
inline int getint(){
	int f=0;
	char c;
	do{
		c=getchar();
	}while( c<'0' || c>'9' ) ;
	do{
		f=f*10+c-'0';
		c=getchar();
	}while( c>='0' && c<='9' ) ;
	return f;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    n = getint();
    vector<int> a(n);
    for(int i = 0; i<n; i++){
        a[i] = getint();
    }
    int maxsf = 1;
    int maxfinal = 1;
    for(int i = 1; i<n; i++){
        if(a[i]>=a[i-1]){
            maxsf++;
        }
        else{
            maxsf = 1;
        }
        maxfinal = max(maxfinal, maxsf);
    }
    cout<<maxfinal;
}
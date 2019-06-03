#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<int> x(n+1), h(n+1);
    for(int i = 0; i<n; i++)
        cin >> x[i] >> h[i];
    x[n] = 2000000010;

    int cut = 0;
    int prev = -(1000000111);
    for(int i = 0; i<n; i++)
    {
        if (prev < x[i] - h[i])
        {
            ++cut;
            prev = x[i];
        }
        else if (x[i] + h[i] < x[i + 1])
        {
            ++cut;
            prev = x[i] + h[i];
        }
        else
            prev = x[i];
    }
    cout << cut << endl;
}

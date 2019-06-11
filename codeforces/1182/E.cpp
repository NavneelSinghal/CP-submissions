#include<bits/stdc++.h> 
using namespace std; 
 #define mod 1000000007
 #define modp 1000000006
 typedef long long ll;
 #define int ll
int power(int x, int y, int p) 
{ 
    int res = 1;     // Initialize result 
   
    while (y > 0) 
    { 
        // If y is odd, multiply x with result 
        if (y & 1) 
            res = (res*x)%p; 
   
        // n must be even now 
        y = y>>1; // y = y/2 
        x = (x*x)%p;  // Change x to x^2 
    } 
    return res; 
}

void multiply(int a[3][3], int b[3][3]) 
{ 
     
    int mul[3][3]; 
    for (int i = 0; i < 3; i++) 
    { 
        for (int j = 0; j < 3; j++) 
        { 
            mul[i][j] = 0; 
            for (int k = 0; k < 3; k++) 
                mul[i][j] += a[i][k]*b[k][j]; 
                mul[i][j] %= modp;
        } 
    } 
  
     
    for (int i=0; i<3; i++) 
        for (int j=0; j<3; j++) 
            a[i][j] = mul[i][j];  // Updating our matrix 
} 

int powerx(int F[3][3], int n) 
{ 
    int M[3][3] = {{1,1,1}, {1,0,0}, {0,1,0}}; 
  
    if (n==1) 
        return F[2][2]; 
  
    powerx(F, n/2); 
  
    multiply(F, F); 
  
    if (n%2 != 0) 
        multiply(F, M); 
  
    
    return F[2][2] ; 
}
int powery(int F[3][3], int n) 
{ 
    int M[3][3] = {{1,1,1}, {1,0,0}, {0,1,0}}; 
  
    if (n==1) 
        return F[2][1]; 
  
    powery(F, n/2); 
  
    multiply(F, F); 
  
    if (n%2 != 0) 
        multiply(F, M); 
  
    
    return F[2][1] ; 
}
int powerz(int F[3][3], int n)
{ 
    int M[3][3] = {{1,1,1}, {1,0,0}, {0,1,0}}; 
  
    if (n==1) 
        return F[2][0]; 
  
    powerz(F, n/2); 
  
    multiply(F, F); 
  
    if (n%2 != 0) 
        multiply(F, M); 
  
    
    return F[2][0] ; 
}
  
  

signed main() 
{ 
   int n, f1, f2, f3, c;
   cin>>n>>f1>>f2>>f3>>c;
   int g1, g2, g3;
   g1 = (power(c, 1, mod)*f1)%mod;
   g2 = (power(c, 2, mod)*f2)%mod;
   g3 = (power(c, 3, mod)*f3)%mod;
   int M[3][3] = {{1,1,1}, {1,0,0}, {0,1,0}};
   int x = powerx(M, n-1);
   int N[3][3] = {{1,1,1}, {1,0,0}, {0,1,0}};
   int y = powery(N, n-1);
   int O[3][3] = {{1,1,1}, {1,0,0}, {0,1,0}};
   int z = powerz(O, n-1);
   int gn = (((power(g1, x, mod)*power(g2, y, mod))%mod)*power(g3, z, mod))%mod;
   int j = power(c, n, mod);
   j = power(j, mod-2, mod);
   gn = (gn*j)%mod;
   cout<<gn<<endl;
   return 0; 
}
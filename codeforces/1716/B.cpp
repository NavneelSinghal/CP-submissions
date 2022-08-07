    #define __USE_MINGW_ANSI_STDIO 0
    #include <stdio.h>
     
    int main(void)
    {
    	int t;
    	scanf("%d",&t);
    	while(t--)
    	{
    		int n;
    		scanf("%d",&n);
    		int v[n];
    		printf("%d\n",n);
    		for(int i = 1; i <= n; i++)
    		{
    			v[i-1] = i;
    			printf("%d ",i);
    		}
    		printf("\n");
    		for(int i = n-1; i > 0; i--)
    		{
    		    int temp = v[i];
    		    v[i] = v[i-1];
    		    v[i-1] = temp;
    			for(int f = 0; f < n; f++)
    			{
    				printf("%d ",v[f]);
    			}
    			printf("\n");
    		}
    	}
    	return 0;
    }
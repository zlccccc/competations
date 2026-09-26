#include <cstdio>
int mp[21][21];
bool read(int &num){
	char in;
	in=getchar();
	if (in==EOF) return false;
	while (in!='0'&&in!='1') in=getchar();
	if (in=='1') num=1;
	else num=0;
	return 0;
}
int main()
{
    int T,n,c,fa,fb,cnt;
    bool ans;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        if(n<=13)
        {
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    mp[i][j]=0;
        }
		if (n<=13){
	        for(int i=1;i<=n;i++)
	            for(int j=i+1;j<=n;j++)
	            {
	                read(c);
	                if(c) mp[i][j]=mp[j][i]=1;
	            }
		}else {
	        for(int i=1;i<=n;i++)
	            for(int j=i+1;j<=n;j++)
	                read(c);
		}
        if(n>10)
        {
            puts("Bad Team!");
            continue;
        }
        else
        {
            ans=true;
            for(int i=1;i<=n&&ans;i++)
                for(int j=i+1;j<=n&&ans;j++)
                    for(int k=j+1;k<=n&&ans;k++)
                        if((mp[i][j]&&mp[i][k]&&mp[j][k])||(!mp[i][j]&&!mp[i][k]&&!mp[j][k]))
                            ans=false;
            if(ans)
                puts("Great Team!");
            else puts("Bad Team!");
        }
    }
    return 0;
}

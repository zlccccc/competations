#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
char a[21];
int nxt[201][2];
int val[201];
int fail[201];
int cnt;
int dp[201][201][1<<6];
int N,L;
int temp[201];
#define mod 998244353
void insert(char str[],int k)
{
    int len=strlen(str),now=0;
    for(int i=0;i<len;i++)
    {
        if(!nxt[now][str[i]-'0'])
            nxt[now][str[i]-'0']=++cnt;
        now=nxt[now][str[i]-'0'];
    }
    val[now]|=(1<<k);
    return;
}
void buildAC()
{
    fail[0]=-1;
    queue<int> Q;
    Q.push(0);
    while(!Q.empty())
    {
        int x=Q.front();
        Q.pop();
        for(int i=0;i<2;i++)
        {
            if(x==0)
            {
                if(nxt[x][i])
                {
                    fail[nxt[x][i]]=0;
                    Q.push(nxt[x][i]);
                    val[nxt[x][i]]|=val[fail[nxt[x][i]]];
                }
            }
            else if(nxt[x][i])
            {
                int p=fail[x];
                while(p!=-1&&!nxt[p][i])
                    p=fail[p];
                if(p!=-1)
                    fail[nxt[x][i]]=nxt[p][i];
                else fail[nxt[x][i]]=0;
                Q.push(nxt[x][i]);
                val[nxt[x][i]]|=val[fail[nxt[x][i]]];
            }
            else nxt[x][i]=nxt[fail[x]][i];
        }
    }
}
int solve(int d,int u,int s)
{
    if(d==2*L)
        return dp[d][u][s]=(s==(1<<N)-1);
    if(dp[d][u][s]!=-1)
        return dp[d][u][s];
    if(d>=L)
    {
        temp[d+1]=1-temp[2*L-d];
        return solve(d+1,nxt[u][temp[d+1]],s|val[nxt[u][temp[d+1]]]);
    }
    else
    {
        dp[d][u][s]=0;
        for(int i=0;i<2;i++)
        {
            temp[d+1]=i;
            dp[d][u][s]=(dp[d][u][s]+(solve(d+1,nxt[u][i],s|val[nxt[u][i]]))%mod)%mod;
        }
    }
    return dp[d][u][s];
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&N,&L);
        cnt=0;
        for(int i=0;i<N;i++)
        {
            scanf("%s",a);
            insert(a,i);
        }
        buildAC();
        for(int i=0;i<=2*L;i++)
            for(int j=0;j<=cnt;j++)
                for(int k=0;k<=(1<<N)-1;k++)
                    dp[i][j][k]=-1;
        printf("%d\n",solve(0,0,0));
        for(int i=0;i<=cnt;i++)
            for(int j=0;j<2;j++)
                nxt[i][j]=0;
        for(int i=0;i<=cnt;i++)
            val[i]=0;
        for(int i=0;i<=cnt;i++)
            fail[i]=0;
    }
    return 0;
}

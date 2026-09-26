#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
char a[11];
int nxt[101][27];
int val[101];
int fail[101];
int cnt;
long long dp[26][101][(1<<10)];
int N,M;
char anss[26];
void insert(char str[],int k)
{
    int len=strlen(str),now=0;
    for(int i=0;i<len;i++)
    {
        if(!nxt[now][str[i]-'a'])
            nxt[now][str[i]-'a']=++cnt;
        now=nxt[now][str[i]-'a'];
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
        for(int i=0;i<26;i++)
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
long long solve(int d,int u,int s)
{
    if(d>=N)
        return s==((1<<M)-1);
    if(dp[d][u][s]!=-1)
        return dp[d][u][s];
    dp[d][u][s]=0;
    for(int i=0;i<26;i++)
        dp[d][u][s]+=solve(d+1,nxt[u][i],s|val[nxt[u][i]]);
    return dp[d][u][s];
}
void dfs(int d,int u,int s)
{
    if(d>=N)
    {
        if(s==((1<<M)-1))
            printf("%s\n",anss);
        return;
    }
    if(dp[d][u][s]<=0)
        return;
    for(int i=0;i<26;i++)
    {
        anss[d]='a'+i;
        dfs(d+1,nxt[u][i],s|val[nxt[u][i]]);
    }
    return;
}
int main()
{
    long long kase=0,ans;
    while(scanf("%d%d",&N,&M)!=EOF)
    {
        if(N==0&&M==0)
            break;
        memset(nxt,0,sizeof(nxt));
        memset(val,0,sizeof(val));
        memset(anss,0,sizeof(anss));
        memset(fail,0,sizeof(fail));
        cnt=0;
        for(int i=0;i<M;i++)
        {
            scanf("%s",a);
            insert(a,i);
        }
        buildAC();
        memset(dp,-1,sizeof(dp));
        printf("Case %lld: %lld suspects\n",++kase,ans=solve(0,0,0));
        if(ans<=42)
            dfs(0,0,0);
    }
    return 0;
}

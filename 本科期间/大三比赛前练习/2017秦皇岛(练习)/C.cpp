#include <bits/stdc++.h>
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
using namespace std;
const int MAX=105;
int t;
int n,R,r;
int dis;
struct node{
    int x,y,dis,id;
    bool operator<(const node &z)const{
        return dis<z.dis;
    }
}a[MAX];
bool cmp(node a,node b){
    return a.id<b.id;
}
int lim,cnt;
vector<node>an;
#define pb push_back
char s[15];
int dp[(1<<10)];
bool vis[(1<<10)];
int dfs(int sta)
{
    if(vis[sta])
        return dp[sta];
    vis[sta]=true;
    int num[10];
    int cnt=0,tmp;
    for(int i=0;i<10;i++)
        if(sta&(1<<i))
            num[cnt++]=i;
    for(int i=0;i<cnt;i++)
    {
        tmp=0;
        for(int j=0;j<3&&i+j<cnt;j++)
        {
            if(s[num[i+j]]!=s[num[i]])
                break;
            tmp|=(1<<num[i+j]);
            if(j!=2)
                dp[sta]=max(dp[sta],dfs(sta-tmp));
            else dp[sta]=max(dp[sta],dfs(sta-tmp)+1);
        }
    }
    return dp[sta];
}
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%s",s);
        for(int i=0;i<(1<<10);i++)
            dp[i]=0;
        for(int i=0;i<(1<<10);i++)
            vis[i]=false;
        printf("%d\n",dfs((1<<10)-1));
    }
    return 0;
}
/*
2
3 10 5
3 4
3 5
3 6
3 10 4
-7 -6
4 5
5 4

1
1
5 5
10 10
*/

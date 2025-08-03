#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ull;
typedef long long ll;
const int INF=0x3f3f3f3f;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
const ll M=1e9+7;
const ll maxn=1e5+7;
const int MAXN=1005;
const int MAX=1e3+5;
const int MAX_N=MAX;
const ll MOD=1e9+7;
//const double eps=0.00000001;
//ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a,ll b,ll M){
    ll ret=1;
    a%=M;
//    b%=M;
    while (b){
        if (b&1) ret=ret*a%M;
        b>>=1;
        a=a*a%M;
    }
    return ret;
}
void open()
{
    freopen("1007.in","r",stdin);
    freopen("out.txt","w",stdout);
}
int t;
double dp[55][10005];
int n,m,d;
vector<int>edge[55];
double dfs(int who)
{
    memset(dp,0,sizeof(dp));
    double re=0;
    dp[0][0]=1.0;
    for(int i=0;i<=d;i++)
    {
        for(int j=0;j<=n;j++)
        {
            if(j==who)
                continue;
            int num=edge[j].size();
            double pos=1.0/(1.0*num);
            for(int s=0;s<num;s++)
            {
                int to=edge[j][s];
                dp[to][i+1]+=dp[j][i]*pos;
            }
        }
        re+=dp[who][i+1];
    }
    return 1.0-re;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&d);
        for(int i=1;i<=m;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            edge[x].push_back(y);
            edge[y].push_back(x);
        }
        for(int i=1;i<=n;i++)
            edge[0].push_back(i);
        for(int i=1;i<=n;i++)
            printf("%.6f\n",dfs(i));
        for(int i=0;i<=n;i++)
            vector<int>().swap(edge[i]);
    }
}


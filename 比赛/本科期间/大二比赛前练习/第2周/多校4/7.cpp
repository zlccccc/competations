#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a*=a) ret=1ll*ret*a%M;return ret;}

int T;
int n,m;
int i,j,k;
int u,v;
LL val;
queue<int> Q;
vector<pair<int,LL> > edge[maxn*2];
int num[maxn];
bool mark[maxn];
LL size[maxn];
LL ans,now;
LL dfs(int x,int fa,bool back){
    mark[x]=1;
    LL ret=1,i;
    REP(i,edge[x].size()) if (!mark[edge[x][i].first]&&edge[x][i].first!=fa)
        ret=edge[x][i].second*dfs(edge[x][i].first,x,back)%M;
    mark[x]=back;
    return ret;
}
LL solve(){
    int i;
    while (Q.size()) Q.pop();
    FOR(i,n+1,n+n){
        if (size[i]==1) Q.push(i),mark[i]=1;
    }
    ans=1;
    while (Q.size()){
        u=Q.front();Q.pop();
        REP(i,edge[u].size()){
            v=edge[u][i].first;
            if (mark[v]) continue;
            size[v]--;
            if (size[v]==1){
                mark[v]=1;
                ans=ans*edge[u][i].second%M;//不算反向的了... 
                Q.push(v);
            }
        }
    }
//    printf("%lld\n",ans);
    FOR(i,1,n){
        if (!mark[i]){
            now=0;
            now=(now+edge[i][0].second*dfs(edge[i][0].first,i,0))%M;
            now=(now+edge[i][1].second*dfs(edge[i][1].first,i,1))%M;
            ans=(ans*now)%M;
        }
    }
    return ans;
}
int main(){
    scanf("%d",&T);
    while (T--){
        scanf("%d",&n);
        FOR(u,1,n){
            scanf("%lld%lld",&v,&val);
            edge[u].push_back(make_pair(v+n,1ll));
            edge[v+n].push_back(make_pair(u,val));
            size[u]++;
            size[v+n]++;
            scanf("%lld%lld",&v,&val);
            edge[u].push_back(make_pair(v+n,1ll));
            edge[v+n].push_back(make_pair(u,val));
            size[u]++;
            size[v+n]++;
        }
        printf("%lld\n",solve());
        FOR(i,1,2*n) mark[i]=size[i]=0;
        FOR(i,1,2*n) vector<pair<int,LL> >().swap(edge[i]);
    }
}
/*
*/

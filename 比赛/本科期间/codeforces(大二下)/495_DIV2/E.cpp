#include <sstream>
#include <fstream>
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
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

vector<pair<int,int> > edge[maxn];
int root,fa[maxn],len[maxn],edge_len[maxn];
void dfs(int x,int father,int length){
    fa[x]=father; len[x]=length;
    if (len[x]>=len[root]) root=x;
    for (auto v:edge[x]) if (father!=v.first){
        edge_len[v.first]=v.second;
        dfs(v.first,x,v.second+length);
    }
}bool mark[maxn];
vector<int> have;
int dis[maxn],up[maxn],down[maxn];
int Log[maxn],R[maxn][20];

int TaskA(){
    int n,k,i,j;
    scanf("%d%d",&n,&k);
    FOR(i,2,n) Log[i]=Log[i>>1]+1;
    FOR(i,1,n-1){
        int u,v,len;
        scanf("%d%d%d",&u,&v,&len);
        edge[u].push_back(make_pair(v,len));
        edge[v].push_back(make_pair(u,len));
    }int U,V;
    dfs(1,0,0); U=root; edge_len[root]=0;
    dfs(U,0,0); V=root;
    for (i=V;i;i=fa[i]) mark[i]=1,have.push_back(i);
    for (int x:have){
        for (auto now:edge[x]) if (!mark[now.first]){
            root=now.first;
            dfs(now.first,x,now.second);
            dis[x]=max(dis[x],len[root]);
        }
    }for (int x:have) down[x]=up[x]=dis[x];
    for (int x:have)
        down[fa[x]]=max(down[fa[x]],down[x]+edge_len[x]);
    reverse(have.begin(),have.end());
    for (int x:have)
        up[x]=max(up[fa[x]]+edge_len[x],up[x]);
    REP(i,have.size()) R[i][0]=dis[have[i]];
    rep(i,1,20) REP(j,have.size()) R[j][i]=max(R[j][i-1],R[j+(1<<(i-1))][i-1]);
    int ans=INF;
//    for (int v:have) printf("%d(%d,dis=%d,up=%d.down=%d) \n",v,len[v],dis[v],up[v],down[v]);puts("");
    for (i=j=0;i<have.size();i++){
        for (;j<have.size()&&j-i+1<=k;j++){
            int len=(j-i),LOG=Log[j-i+1];
            int nowans=max(R[i][LOG],R[j-(1<<LOG)][LOG]);
            nowans=max(nowans,max(up[have[i]],down[have[j]]));
            ans=min(ans,nowans);
        }
    }printf("%d\n",ans);
    return 0;
}
void initialize(){}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	int T=1;
//	scanf("%d",&T);
	startTime=clock();
	while (T--) TaskA();
	debug("/--- computeTime: %ld milliseconds ---/\n",clock()-startTime);
}
/*
*/

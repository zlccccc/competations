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
const LL M=998244353;
const LL maxn=2e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

vector<int> edge[maxn];
int in[maxn],out[maxn],tot;
int fa[maxn][20],dep[maxn];
void dfs(int x,int father,int depth){
//    debug("%d %d\n",x,fa);
    in[x]=++tot; dep[x]=depth;
    fa[x][0]=father; int i;
    rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
    for (int v:edge[x]) if (v!=father) dfs(v,x,depth+1);
    out[x]=tot;
}vector<pair<pair<int,int>,int> > have[maxn];
int A[maxn<<3],len[maxn<<3];
void update(int x,int l,int r,int val,int L,int R){
    if (l<=L&&R<=r) {
        A[x]+=val;
        if (A[x]) len[x]=R-L+1;
        else len[x]=len[x<<1]+len[x<<1|1];
        return;
    }int mid=(L+R)/2;
    if (l<=mid) update(x<<1,l,r,val,L,mid);
    if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
    if (A[x]) len[x]=R-L+1;
    else len[x]=len[x<<1]+len[x<<1|1];
}
int lca(int x,int y){
	int i;
	if (dep[x]<dep[y]) swap(x,y);
	rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
	if (x==y) return x;
	rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int TaskA(){
    int i,j,n,q;
    scanf("%d%d",&n,&q);
    FOR(i,1,n-1) {
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }dfs(1,0,0);
//    FOR(i,1,n) printf("%d ",in[i]);puts("");
    FOR(i,1,q){
        int x,y;
        scanf("%d%d",&x,&y);//x!=y
        vector<pair<int,int> > A,B;
        if (dep[x]<dep[y]) swap(x,y);
        A.push_back(make_pair(in[x],out[x]));
        int i;
        rREP(i,20) if (dep[x]-dep[y]-1>=1<<i) x=fa[x][i];
        if (fa[x][0]==y){
            B.push_back(make_pair(1,in[x]-1));
            B.push_back(make_pair(out[x]+1,n));
        }else{
            B.push_back(make_pair(in[y],out[y]));
        }
        for (auto X:A){
            for (auto Y:B){
                int l=X.first,r=X.second;
                int _l=Y.first,_r=Y.second;
                have[l].push_back(make_pair(make_pair(_l,_r),1));
                have[r+1].push_back(make_pair(make_pair(_l,_r),-1));
//                printf("%d %d - %d %d\n",l,r,_l,_r);
            }
        }
        for (auto X:B){
            for (auto Y:A){
                int l=X.first,r=X.second;
                int _l=Y.first,_r=Y.second;
                have[l].push_back(make_pair(make_pair(_l,_r),1));
                have[r+1].push_back(make_pair(make_pair(_l,_r),-1));
//                printf("%d %d - %d %d\n",l,r,_l,_r);
            }
        }
    }ll ans=(ll)n*(n-1);
    FOR(i,1,n){
        for (auto now:have[i]) {
//            printf("upd :%d : %d %d %d\n",i,now.first.first,now.first.second,now.second);
            update(1,now.first.first,now.first.second,now.second,1,n);
        }
//        printf("%d\n",len[1]);
        ans-=len[1];
    }printf("%lld\n",ans);
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
3 3
1 2 0
2 3 1
1 3 1
*/

#include <bits/stdc++.h>
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
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=2e5+107;
 
vector<int> edge[maxn];
ll h[maxn];
ll Ans[maxn],Max[maxn],Sec[maxn];
void upd(int x,ll val) {
    if (Max[x]<=val) swap(Max[x],val);
    if (Sec[x]<=val) swap(Sec[x],val);
}
void dfs(int x,int fa) {
    if (edge[x].size()==1) {//叶结点
        Ans[x]=Max[x]=h[x];
    }
    for (int v:edge[x]) if (v!=fa) {
        dfs(v,x);
        Ans[x]+=Ans[v];
        upd(x,Max[v]);
    }
    if (Max[x]<h[x]) {
        Ans[x]+=h[x]-Max[x];
        Max[x]=h[x];
    }
}
int main() {
    int n,i;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%lld",&h[i]);
    FOR(i,1,n-1) {
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    int root=1;
    FOR(i,1,n) if (h[i]>h[root]) root=i;//root处一定放了一个x!(或者相连)
    dfs(root,0); //Max不一定和Sec相连;
    // printf("root=%d; Max=%d; Sec=%d; ans=%d\n",root,Max[root],Sec[root]);
    printf("%lld\n",Ans[root]+Max[root]-Sec[root]);
}
/*
//swap A and B
*/
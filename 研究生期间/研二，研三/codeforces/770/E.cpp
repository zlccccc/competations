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

bool mark[maxn];
int A[maxn];
vector<int> edge[maxn];
map<int,int> id;
int mask[maxn];
void dfs(int x,int col=0) {
    mask[x]=col+1;
    for (int v:edge[x]) if (!mask[v]) dfs(v,col^1);
}
int main() {
    int n,m,Start=0,i,j;
    scanf("%d",&m);
    FOR(i,1,m) {
        scanf("%d",&n);
        FOR(j,1,n) {
            int k;
            scanf("%d",&k);
            if (j&1) {
                edge[Start+j].push_back(Start+j+1);
                edge[Start+j+1].push_back(Start+j);
            } if (id[k]) {
                edge[Start+j].push_back(id[k]);
                edge[id[k]].push_back(Start+j);
                id.erase(k);
            } else id[k]=Start+j;
        } Start+=n;
        mark[Start]=1;
    }
    if (id.size()) puts("NO");
    else {
        puts("YES");
        FOR(i,1,Start) if (!mask[i]) dfs(i);
        FOR(i,1,Start) {
            printf("%c"," LR"[mask[i]]);
            if (mark[i]) puts("");
        }
    }
}
/*
*/
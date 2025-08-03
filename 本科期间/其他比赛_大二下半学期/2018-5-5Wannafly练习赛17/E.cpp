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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
const LL maxn=2e5+7;
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

struct node {
    int n;
    LL d;
    node() {}
    node(int _n,LL _d):n(_n),d(_d) {};
    const bool operator <(const node &A)const {
        if (d!=A.d) return d>A.d;//注意!!! 否则为未优化的bellmanford
        return n>A.n;
    }
};
vector<node> edge[maxn];
priority_queue<node> Q;
LL dis[maxn];
void dij(int s,int n) {
    int i;
    FOR(i,1,n) dis[i]=INFF/2;
    dis[s]=0;
    Q.push(node(s,0));
    while (Q.size()) {
        node x=Q.top();
        Q.pop();
        if (dis[x.n]!=x.d) continue;//!
        for (node y:edge[x.n]) {
            if (dis[y.n]>x.d+y.d) {
                dis[y.n]=x.d+y.d;
                Q.push(node(y.n,dis[y.n]));
            }
        }
    }
}
int S;
int id[17];
LL D[17][17];
LL f[17][1<<15|7];//now,okay
void bfs(){
    int i;
    memset(f,0x3f,sizeof(f));
    queue<pair<LL,pair<int,int> > > Q;
    f[1][1]=0;
    Q.push(make_pair(0,make_pair(1,1)));
    while (Q.size()){
        auto now=Q.front(); Q.pop();
        int x=now.second.first,status=now.second.second;
//        if (f[x][status]!=-now.first) continue;
//        printf("U:%d %d:%lld\n",x,status,f[x][status]);
        FOR(i,1,S){
            int nxt=status|(1<<(i-1));
//            printf("   F:%d %d:%lld; %lld\n",i,nxt,f[x][status]+D[x][i],f[i][nxt]);
//            if (nxt==status) continue;
            if (f[i][nxt]>f[x][status]+D[i][x]){
                f[i][nxt]=f[x][status]+D[i][x];
                Q.push(make_pair(-f[i][nxt],make_pair(i,nxt)));
            }
        }
    }
}
int main() {
    int T;
    scanf("%d",&T);
    while(T--){
        int n,m,i,j;
        scanf("%d%d",&n,&m);
        FOR(i,1,n) edge[i].clear();
        REP(i,m) {
            int u,v;LL len;
            scanf("%d%d%lld",&u,&v,&len);u++;v++;
            edge[u].push_back(node(v,len));
            edge[v].push_back(node(u,len));
        }
        scanf("%d",&S);id[1]=1;S++;
        FOR(i,2,S) scanf("%d",&id[i]),id[i]++;
        FOR(i,1,S){
            dij(id[i],n);
            FOR(j,1,S) D[i][j]=dis[id[j]];
//            FOR(j,1,S) printf("%lld ",D[i][j]);puts("");
        }bfs();
        printf("%lld\n",f[1][(1<<S)-1]);
    }
    return 0;
}
/*
2
4 4
0 1 10000000000
1 2 10000000000
0 2 50000000000
1 3 50000000000
3
1
2
3
4 6
0 1 1
1 2 1
2 3 1
3 0 1
0 2 5
1 3 5
3
1
2
3
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
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
    FOR(i,1,n) dis[i]=INFF;
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
void printid(int t){
    t--;
    printf("%-2d(%02d:%02d) ",t/50+1,t%50/2,t%2*30);
}
void addedge(int s,int t,LL len){
//    printid(s);printid(t);printf("%d   <- edge\n",len);
    edge[s].push_back(node(t,len));
}

int n,m;
int getid(int n,int h,int m){
    n--;
    return n*50+h*2+m/30+1;
}//rev_bfs -> ini_min_dis
int getid(int n,int x){
    n--;
    return n*50+x+1;
}//rev_bfs -> ini_min_dis
int U[maxn],V[maxn],len[maxn];
bool could[maxn];
vector<int> rev[maxn];
int main() {
    int i,j;
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;
        int h1,m1,h2,m2;
        scanf("%d%d%d",&u,&v,&len[i]);
        scanf("%d:%d%d:%d",&h1,&m1,&h2,&m2);
        U[i]=getid(u,h1,m1);
        V[i]=getid(v,h2,m2);V[i]++;
        if (h1||m1) rev[V[i]-1].push_back(U[i]-1);
    }could[getid(n,49)]=1;
    int u,v;
    rFOR(i,0,48){
        FOR(u,1,n){
            addedge(getid(u,i),getid(u,i+1),0);
            if (could[getid(u,i+1)]) could[getid(u,i)]=1;
            if (!could[getid(u,i)]) continue;
            for (int v:rev[getid(u,i)]) could[v]=1;
        }
//        FOR(u,1,n) if (could[getid(u,i)])
//            printid(getid(u,i));puts("");
    }FOR(i,1,m) if (could[U[i]]){
        addedge(U[i],V[i],len[i]);
    }dij(getid(1,0,0),getid(n,24,0)+1);
//    FOR(i,1,getid(n,24,0)+1){printid(i);printf("%lld\n",dis[i]);};
    if (dis[getid(n,24,0)+1]!=INFF)
        printf("%lld\n",dis[getid(n,24,0)+1]);
    else puts("-1");
    return 0;
}
/*
*/

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

int U[maxn],V[maxn];
int MIN[maxn],MAX[maxn];
int fa[maxn];
inline int getfa(int x){
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n,m,i;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) fa[i]=i;
    FOR(i,1,m){
        int u,v;char c;
        scanf("%d%c%d",&u,&c,&v);
        if (c=='='){
            u=getfa(u);v=getfa(v);
            if (u==v) continue;
            fa[u]=v;
        }else{
            if (c=='>') swap(u,v);
            U[i]=u; V[i]=v;
        }
    }
    FOR(i,1,n) MIN[i]=1,MAX[i]=3;
    FOR(i,1,m) if (U[i]){
        U[i]=getfa(U[i]);
        V[i]=getfa(V[i]);
    }
    FOR(i,1,m) if (V[i]) MIN[V[i]]=2;
    FOR(i,1,m) if (MIN[U[i]]==2) MIN[V[i]]=3;
    FOR(i,1,m) if (U[i]) MAX[U[i]]=2;
    FOR(i,1,m) if (MAX[V[i]]==2) MAX[U[i]]=1;
    FOR(i,1,n){
        int f=getfa(i);
        if (MIN[f]==MAX[f]){
            if (MIN[f]==1) putchar('B');
            if (MIN[f]==2) putchar('R');
            if (MIN[f]==3) putchar('W');
        }else putchar('?');
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
/*
*/

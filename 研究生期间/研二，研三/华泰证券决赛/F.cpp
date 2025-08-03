#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(I,N) for (I=0;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
const int maxn=1e5+7;
const int M=998244353;
inline void add_(int &_x,int _y) {_x+=_y; if (_x>=M) _x-=M;}
typedef pair<int,int> pii;

inline int powMM(ll x,ll y) {
    int ret=0;
    for (;y;y>>=1,x=x*x%M) if (y&1) ret=ret*x%M;
    return ret;
}
// end as 0
int n,m;
int f[maxn],sumf[maxn],g[maxn];
int main() {
    int i,k;
    int ans=0;
    // scanf("%d%d",&n,&m);
    n=7; m=3;
    f[0]=1; sumf[0]=1;
    FOR(i,1,n) {
        add_(f[i],sumf[i-1]);
        if (i>m) add_(f[i],M-f[i-m-1]);
        if (i>1) add_(f[i],M-f[i-2]);
        sumf[i]=f[i]; add_(sumf[i],sumf[i-1]);
        add_(g[i],f[i]);
        for (int k=i+i;k<=n;k+=i) add_(g[k],f[i]);
        if (i<=m) add_(g[i],1);
        ans^=g[i];
    }
    FOR(i,1,n) printf("%d ",f[i]); puts("<- f");
    FOR(i,1,n) printf("%d ",g[i]); puts("<- g");
    printf("%d\n",ans);
}
/*
7 3
*/ 
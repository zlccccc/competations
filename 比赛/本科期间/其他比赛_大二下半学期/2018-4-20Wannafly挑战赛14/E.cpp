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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
const LL maxn=1e5+7;
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

struct L_B{
    int A[31];
    void clear(){memset(A,0,sizeof(A));}
    int XORMAX(){
        int i,x=0;
        rREP(i,31) if ((A[i]^x)>x) x^=A[i];
        return x;
    }
    void insert(int x){
        int i;
        rREP(i,31) if ((x>>i)&1){
            if (!A[i]) A[i]=x;x^=A[i];
        }
    }
    void merge(L_B B){
        int i;
        REP(i,31) if (B.A[i]) insert(B.A[i]);
    }
}F[maxn];
int A[maxn];
int fa[maxn];
inline int getfa(int x){
    if (fa[x]==x) return fa[x];
    return fa[x]=getfa(fa[x]);
}
void merge(int u,int v){
    int x=getfa(u),y=getfa(v);
    F[y].merge(F[x]);fa[x]=y;
}
int MAX;
int ans[maxn],id[maxn];
int main() {
    int i,j;
    int T;
    int n,m;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n) scanf("%d",&id[i]);
    rFOR(j,1,n){
        i=id[j];
        fa[i]=i;
        F[i].insert(A[i]);
        if (i!=1&&fa[i-1]) merge(i,i-1);
        if (i!=n&&fa[i+1]) merge(i,i+1);
        MAX=max(MAX,F[getfa(i)].XORMAX());
        ans[j]=MAX;
    }FOR(i,1,n) printf("%d\n",ans[i]);
    return 0;
}
/*
10
169 816 709 896 58 490 97 254 99 796
4 2 3 10 5 6 1 8 9 7
*/

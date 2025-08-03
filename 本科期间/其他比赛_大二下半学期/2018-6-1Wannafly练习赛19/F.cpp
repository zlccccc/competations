#include <sstream>
#include <fstream>
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

#define DEBUG
#ifdef DEBUG
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#define dbg(x)
#define dbgln(x)
#endif // DEBUG
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

int n,m,ans;
LL A[maxn],B[maxn];
void pushdown(int x){
    A[x<<1]+=B[x];
    A[x<<1|1]+=B[x];
    B[x<<1]+=B[x];
    B[x<<1|1]+=B[x];
    B[x]=0;
}
void update(int x,int pos,int val,int L,int R){
    if (L==R){
        A[x]=val;
        return;
    }int mid=(L+R)/2;
    pushdown(x);
    if (pos<=mid) update(x<<1,pos,val,L,mid);
    else update(x<<1|1,pos,val,mid+1,R);
}
LL query(int x,int pos,int L,int R){
    if (L==R) return A[x];
    int mid=(L+R)/2;
    pushdown(x);
    if (pos<=mid) return query(x<<1,pos,L,mid);
    else return query(x<<1|1,pos,mid+1,R);
}
int main() {
    int i,j,k;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",&k),update(1,i,k,1,n);
    while (m--){
        int op;
        scanf("%d",&op);
        if (op==1){
            int v,x;
            scanf("%d%d",&v,&x);
            update(1,v,x,1,n);
        }if (op==2){
            int x;
            scanf("%d",&x);
            B[1]+=x;A[1]+=x;
        }if (op==3){
            int pos;
            scanf("%d",&pos);
            printf("%lld\n",query(1,pos,1,n));
        }
    }
    return 0;
}
/*
*/

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
template<typename T>
inline void upd(T &A,T &B){
    if (A<B) A=B;
}
int n,m,v,q;
int cl,ce;
int l[maxn],e[maxn];
int main() {
    int i;
    scanf("%d%d%d%d%d",&n,&m,&cl,&ce,&v);
    REP(i,cl) scanf("%d",&l[i]);
    REP(i,ce) scanf("%d",&e[i]);
    scanf("%d",&q);
    while (q--){
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        if (x1==x2){
            printf("%d\n",abs(y1-y2));
        }else{
            if (y1>y2) swap(y1,y2);
            int ans=INF;
            int x;
            x=lower_bound(l,l+cl,y1)-l;
            if (x!=cl)
                ans=min(ans,abs(l[x]-y1)+abs(l[x]-y2)+abs(x1-x2));
            x=upper_bound(l,l+cl,y2)-1-l;
            if (x!=-1)
                ans=min(ans,abs(l[x]-y1)+abs(l[x]-y2)+abs(x1-x2));
            x=lower_bound(e,e+ce,y1)-e;
            if (x!=ce)
                ans=min(ans,abs(e[x]-y1)+abs(e[x]-y2)+(abs(x1-x2)+v-1)/v);
            x=upper_bound(e,e+ce,y2)-1-e;
            if (x!=-1)
                ans=min(ans,abs(e[x]-y1)+abs(e[x]-y2)+(abs(x1-x2)+v-1)/v);
            printf("%d\n",ans);
        }
    }
    return 0;
}
/*
*/

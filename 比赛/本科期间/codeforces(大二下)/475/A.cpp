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


int n,m;
char A[maxn];
LL a,b,c,ans;
inline LL get(LL s,LL e,LL k){
    if (e<s) return 0;
    LL ret;
    LL d=powMM(c,(LL)k);
    LL t=(e-s)/k+1;
    assert(d!=0);
    if (d==1) ret=t*powMM(c,(LL)s)%M;
    else ret=(powMM(d,t)-1)*powMM(d-1,M-2)%M*powMM(c,(LL)s)%M;
//    printf("%d %d %d : %I64d %I64d %I64d\n",s,e,k,d,t,ret);
    ret%=M;
    return ret;
}
int main() {
    int i,j,k;
    scanf("%d%I64d%I64d%d",&n,&a,&b,&k);
    c=b*powMM(a,M-2)%M;ans=0;
    scanf("%s",A);
    REP(i,k){
        LL t=n/k*k+i;
        while (t<n) t+=k;
        while (t>n) t-=k;
        if (A[i]=='+') ans+=get(i,t,k);
        else if (A[i]=='-') ans-=get(i,t,k);
        ans+=M; ans%=M;
//        printf("%d : t=%I64d ; ans=%I64d\n",i,t,ans);
    }ans=ans*powMM(a,(LL)n)%M;
    ans+=M; ans%=M;
    printf("%I64d\n",ans);
    return 0;
}
/*
2 2 3 3
+-++++
*/

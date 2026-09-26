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

struct node{
    LL A,B;
}e[maxn];
int n,m;
LL pre,ans;
LL f[maxn];
int main() {
    int i,j;
    int n;LL a;int b;
    scanf("%d%I64d%d",&n,&a,&b);b=min(b,n);
    FOR(i,1,n) scanf("%I64d%I64d",&e[i].A,&e[i].B);
    FOR(i,1,n) {
        LL A=e[i].A,B=e[i].B;
        pre+=B;
        e[i].B=max(A-B,0ll);
        e[i].A=A*(1<<a)-B;
    }sort(e+1,e+1+n,[](node &A,node &B){return A.B>B.B;});
    FOR(i,1,n) f[i]=f[i-1]+e[i].B;
    if (b){
        FOR(i,1,n){
            if (i<=b) ans=max(ans,e[i].A+f[b]-e[i].B);
            else ans=max(ans,e[i].A+f[b-1]);
        }
    }
    printf("%I64d\n",ans+pre);
    return 0;
}
/*
*/

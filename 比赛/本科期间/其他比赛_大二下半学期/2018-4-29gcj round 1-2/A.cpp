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

priority_queue<int> Q;
void solve(){
    static int x=0;
    int n,now;int l;
    int ans=0;int i;
    scanf("%d%d",&n,&l);now=n;
    while (Q.size()) Q.pop();
    FOR(i,1,l){
        int x;
        scanf("%d",&x);now-=x;
        ans+=(1000*x+5*n)/(10*n);
        Q.push((1000*x+5*n)%(10*n));
    }FOR(i,1,now) Q.push(5*n);
    while (now--){
        int y=Q.top();Q.pop();
//        printf("y=%d\n",y);
        ans+=(y+1000)/(10*n);
        Q.push((y+1000)%(10*n));
    }printf("Case #%d: %d\n",++x,ans);
}
int n,m;
int main() {
    int T;
    scanf("%d",&T);
    while (T--) solve();
    return 0;
}
/*
*/

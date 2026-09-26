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

int n;
int A[1007][1007];
map<int,int> MP;
int get(int x){
    if (MP[x]) return MP[x];
    int ret=0,i;
    FOR(i,0,x) ret+=i|x;
    return MP[x]=ret;
}
int main() {
    int i,j,k;
//    FOR(i,1,10000) if (get(i+1)<get(i)) printf("%d ",get(i));
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d",&n);
        int x,ans,p;
        ans=-1;p=0;
        FOR(i,1,n){
            scanf("%d",&x);
//            int now=get(x);
//            if (now>ans) ans=now,p=x;
            p=max(p,x);
        }printf("%d\n",p);
    }
    return 0;
}
/*
*/

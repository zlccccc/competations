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

char A[maxn],B[maxn];
string now;
pair<int,string> ans;
int n,m;
int main() {
    int i,j,k;
    int T;
    scanf("%d%d",&n,&m);
    ans.first=1;
    scanf("%s",A);
    REP(i,m){
        int cnt=0;
        cin>>now;
        scanf("%s",B);
        REP(j,n) if (B[j]!='X'&&A[j]==B[j]) cnt--;
        ans=min(ans,make_pair(cnt,now));
    }cout<<ans.second;
    printf("\n%.2f",-100.0*ans.first/n+eps);
    return 0;
}
/*
3 0 1 0 0 1 1 2.13 -6.89 1.78 1.20 -7.73 0.56 3.473 -4.326 -4.851 -0.819 2.467 -2.729
*/

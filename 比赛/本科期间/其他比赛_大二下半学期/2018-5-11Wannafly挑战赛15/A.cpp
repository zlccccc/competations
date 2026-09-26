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
//typedef __int128 LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=5e5+7;
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

int A[maxn];
pair<int,int> B[maxn];
int a,b;
priority_queue<int> Q;
LL ans;
int main() {
    int m,n,i,T;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,m) scanf("%d%d",&B[i].first,&B[i].second);
    sort(A+1,A+1+n);
    sort(B+1,B+1+m);
    rFOR(i,1,n){
        while (m&&B[m].first>=A[i]){
            Q.push(-B[m].second);
            m--;
//            printf("push %d %d\n",B[m].first,B[m].second);
        }
//        printf("%d: %d\n",i,Q.size());
        if (!Q.size()) return 0*puts("-1");
        ans+=Q.top();Q.pop();
    }printf("%lld\n",-ans);
}
/*
*/

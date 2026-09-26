#include <sstream>
#include <fstream>
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

#define DEBUG1
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
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
//? what does the problem mean ? why certain ?
typedef pair<int,int> pii;
pii A[20],B[20];
set<int> cntA[20],cntB[20],ans;
int solve(){
    int n,m,i,j;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d%d",&A[i].first,&A[i].second);
    FOR(i,1,m) scanf("%d%d",&B[i].first,&B[i].second);
    FOR(i,1,n) FOR(j,1,m){
        int Ax=A[i].first,Ay=A[i].second;
        int Bx=B[j].first,By=B[j].second;
        int same=-1;
        if (Ax==Bx||Ax==By) same=Ax;
        if (Ay==By||Ay==Bx) same=Ay;
        if (same!=-1){
            int A=Ax^Ay^same,B=Bx^By^same;
            if (A==B) continue;
            cntA[i].insert(same);
            cntB[j].insert(same);
            ans.insert(same);
        }
    }if (ans.size()==1) return 0*printf("%d\n",*ans.begin());
    FOR(i,1,n) if (cntA[i].size()>1) return 0*puts("-1");
    FOR(i,1,m) if (cntB[i].size()>1) return 0*puts("-1");
    puts("0");
}
int main() {
    int T=1;
//    scanf("%d",&T);
    while (T--) solve();
}
/*
*/

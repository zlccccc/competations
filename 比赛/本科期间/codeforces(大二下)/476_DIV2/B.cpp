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
const LL maxn=4e5+7;
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

int n,m,q;
char A[207][207];
int B[207][207];
int main() {
    int i,j,k,t;
    scanf("%d%d",&n,&k);
    FOR(i,1,n) scanf("%s",A[i]+1);
    FOR(i,1,n)
        FOR(j,1,n){
            rep(t,i,i+k) if (A[t][j]!='.') break;
            if (t==i+k)
                rep(t,i,i+k) B[t][j]++;
            rep(t,j,j+k) if (A[i][t]!='.') break;
            if (t==j+k)
                rep(t,j,j+k) B[i][t]++;
        }
    int x=1,y=1;
//    FOR(i,1,n){
//        FOR(j,1,n) printf("%-2d ",B[i][j]);
//        puts("");
//    }
    FOR(i,1,n) FOR(j,1,n)
        if (B[i][j]>B[x][y]) x=i,y=j;
    printf("%d %d\n",x,y);
    return 0;
}
/*
*/

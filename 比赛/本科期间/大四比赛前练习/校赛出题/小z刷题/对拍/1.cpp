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
mt19937 Rand;
int id[maxn];
inline int random(int l,int r) {
    return Rand()%(r-l+1)+l;
}
int A[maxn];
void printOne(int n,int m,int k) { //val_cnt=m;
    int i; printf("%d %d\n",n,k);
    FOR(i,1,m) id[i]=random(1,1000000);
    FOR(i,1,n) A[i]=random(1,m);
    FOR(i,1,n) printf("%d %d\n",id[A[i]],random(0,1000000000));
}
int main() {
    printf("%d\n",500+50+5);
    int i;
    REP(i,500) printOne(10,random(1,10),random(0,20));
    REP(i,50) printOne(100,random(1,100),random(0,20));
    printOne(10000,10,20);
    printOne(20000,100,20);
    printOne(20000,1000,20);
    printOne(20000,10000,20);
    printOne(20000,100000,20);
    return 0;
}
/*
*/

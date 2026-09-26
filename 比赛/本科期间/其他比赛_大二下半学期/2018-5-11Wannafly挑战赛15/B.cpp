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

int A[107],ans;
int D[107];
int main() {
    int m,n,i,k,T;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&k),A[k]++;
    ans=A[5];//no remain!
    ans+=A[4];D[1]+=A[4];
    ans+=A[3];D[2]+=A[3];
    int f=min(D[2],A[2]);A[2]-=f;
    if (A[2]>0){
        D[1]+=(A[2]+1)/2*5-A[2]*2;
        ans+=(A[2]+1)/2;
    }else D[1]+=(D[2]-f)*2;
    f=min(A[1],D[1]);A[1]-=f;
    ans+=(A[1]+4)/5;
    printf("%d\n",ans);
}
/*
*/

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

LL f[maxn];
char A[maxn];
int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%s",A+1);
    int i,n;
    n=strlen(A+1);
    f[0]=1;
    FOR(i,1,n){
        f[i]+=f[i-1];
        if (A[i]=='W'&&A[i-1]=='N') f[i]+=f[i-2];
        if (A[i]=='E'&&A[i-1]=='N') f[i]+=f[i-2];
        if (A[i]=='W'&&A[i-1]=='S') f[i]+=f[i-2];
        if (A[i]=='E'&&A[i-1]=='S') f[i]+=f[i-2];
        f[i]%=M;
    }printf("%I64d\n",f[n]);
//    cerr<<f[n];
    fclose(stdin);
    fclose(stdout);
    return 0;
}
/*
*/

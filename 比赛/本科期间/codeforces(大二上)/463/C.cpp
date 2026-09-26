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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

LL n,A,B,a,b;
LL f[maxn],i;
LL now=0;
int main(){
    scanf("%I64d%I64d%I64d",&n,&A,&B);
    FOR(a,0,n/A) if ((n-a*A)%B==0) break;
    if (a>n/A) return 0*puts("-1");
    b=(n-a*A)/B;
    if (a*A+b*B!=n) return 0*puts("-1");
    FOR(i,1,n) f[i]=i;
    while (a){
        a--;
        FOR(i,1,A-1) swap(f[now+i],f[now+i+1]);
        now+=A;
    }while (b){
        b--;
        FOR(i,1,B-1) swap(f[now+i],f[now+i+1]);
        now+=B;
    }
    FOR(i,1,n) printf("%I64d ",f[i]);
}
/*
7 2 7
*/

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
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i,j,k;
double p[maxn],a[maxn],b[maxn],f[maxn];
int main(){
    FOR(i,1,12) scanf("%lf",&p[i]);
    FOR(i,1,12) scanf("%lf",&a[i]);
    FOR(i,1,12) scanf("%lf",&b[i]);
    FOR(i,1,12) p[i]=1-((1-p[i])*(1-a[i])*(1-b[i]));
    f[0]=1;
    FOR(i,1,12){
        rFOR(j,0,12){
            f[j+1]+=p[i]*f[j];
            f[j]*=(1-p[i]);
        }
    }FOR(i,0,12) printf("%.6lf\n",f[i]);
}
/*
0.20 0.30 0.37 0.40 0.45 0.50 0.57 0.60 0.75 0.76 0.77 0.83 0.85 0.88 0.90 0.94 0.100 0.104 0.105 0.107 0.115 0.120 0.122 0.125 0.128 0.130 0.134 0.140 0.149 0.150 0.152 0.155 0.170 0.183 0.203 0.240
*/

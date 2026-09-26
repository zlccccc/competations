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

int n,l,r,m,L,R;
double f[maxn];
int f1,f2;
int main(){
    int i,j;
    scanf("%d%d%d%d%d%d",&n,&l,&r,&m,&L,&R);
    if (n==0) return 0*puts("0.00000");
    if (m==0) return 0*puts("1.00000");
    FOR(i,l,r){
        FOR(j,L,R){
            if (i>j) f1++;
            else if (i<j) f2++;
        }
    }if (f1==0&&f2==0) return 0*puts("0.00000");
    if (f1==0) return 0*puts("0.00000");
    if (f2==0) return 0*puts("1.00000");
    double ans,A=1.0*f1/(f1+f2);
    f[0]=0;ans=1;
    FOR(i,0,n+m) f[i+1]=A/(1-f[i]*(1-A));
    FOR(i,n,n+m-1) ans=ans*f[i];
    printf("%.5lf\n",ans);
}
/*
10 1 3
10 1 2
right:A
1~x right:x[i]
-> f[i+1]=sigma{A*((1-A)*f[i])^i}
*/

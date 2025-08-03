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
const LL M1=998244353;
const LL M2=1e9+7;
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i,j,k;
LL f[maxn],g[maxn];LL F,G;
int T[maxn][57];
char a[maxn];
int main(){
    f[1]=g[1]=1;f[2]=g[2]=2;
    FOR(i,3,100000){
        f[i]=(f[i-1]+f[i-2])%M1;
        g[i]=(g[i-1]+g[i-2])%M2;
    }
    while (~scanf("%s",a)){
        int len=strlen(a);
        F=G=0;
        REP(i,len){
            F=(F*10ll+a[i]-'0')%M1;
            G=(G*10ll+a[i]-'0')%M2;
        }
        FOR(i,1,100000) if (f[i]==F&&g[i]==G){
            printf("%d\n",i);
        }
    }
}
/*
2 3 5 8 13 6
1 1 2 3 4 5
*/

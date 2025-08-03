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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,T;
int i,j,k;
int a[maxn];
int main(){
    scanf("%d",&T);
    while (T--){
        int x;bool mark=0;
        scanf("%d",&x);
        if (x==0){
            printf("1 1\n");
            continue;
        }
        for (i=1;i*i<x;i++) if (x%i==0){
            LL A=x/i,B=i;
            if ((A&1)!=(B&1)) continue;
            LL F=(A+B)/2,E=(A-B)/2;//F=n,E=n/m
            LL T=F/E;
//            printf("n=F,n/m=E;T=%lld: %lld %lld\n",T,F,E);
            if (F*F-(F/T)*(F/T)!=x) continue;
            printf("%I64d %I64d\n",F,T);
            mark=1;break;
        }if (!mark) puts("-1");
    }
}
/*
1000000000
*/

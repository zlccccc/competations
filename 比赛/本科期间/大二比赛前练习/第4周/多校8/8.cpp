#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=2e5+7;
const double eps=0.00000001;
const LL INF=1000000000;
const LL INFF=0x1f3f3f3f3f3f3f3fll;
inline LL powMM(LL a,LL b){
    LL ret=1;
    while (b){
        if (b&1) ret=ret*a%M;
        a=a*a%M;
        b>>=1;
    }
    return ret;
}

int all;
int n,k;
int i;
char c;
int a[maxn];
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        all=0;
        scanf("%d%d",&n,&k);
        REP(i,n) scanf("%d",&a[i]);
        all=0;
        REP(i,n){
            cin>>c;
            if (c=='N') k+=a[i],all+=a[i]*2;
            if (c=='D') k+=a[i],all+=a[i];
            if (c=='L') all+=a[i];
        }
        if (k<0) puts("no");
        else if (k>all) puts("no");
        else puts("yes");
    }
}
/*
10
3 5
3 4 5
L L L
*/

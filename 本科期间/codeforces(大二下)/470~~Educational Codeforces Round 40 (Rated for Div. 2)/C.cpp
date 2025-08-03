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
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j,k;
int a[maxn];
int main(){
    int n;
    int y=0;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&a[i]);
    FOR(i,2,n){
        if (abs(a[i]-a[i-1])!=1){
            if (a[i]==a[i-1]) return 0*puts("NO");
            if (y&&y!=abs(a[i]-a[i-1])) return 0*puts("NO");
            y=abs(a[i]-a[i-1]);
        }
    }if (!y) y=1000000000;
    FOR(i,2,n){
        if (a[i-1]%y==0&&a[i]==a[i-1]+1||
            a[i]%y==0&&a[i-1]==a[i]+1) return 0*puts("NO");
    }
    puts("YES");
    printf("1000000000 %d\n",y);
}
/*
4
3 2 4 2
*/

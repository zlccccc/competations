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
const LL M=1e9+9;
const LL maxn=2e5+7;
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

int n,m;
char a[maxn],b[maxn];
int s[maxn],t[maxn];
int lst[255];
int main() {
    int i,j;
    scanf("%s%s",a,b);
    n=strlen(a),m=strlen(b);
    FOR(i,'a','z') lst[i]=-1;j=0;
    REP(i,n){
        if (j!=m&&b[j]==a[i]) lst[a[i]]=j+1,j++;
        s[i]=lst[a[i]];
    }if (j!=m) return 0*puts("No");
    FOR(i,'a','z') lst[i]=m;j=m-1;
    rREP(i,n){
        if (j!=-1&&b[j]==a[i]) lst[a[i]]=j+1,j--;
        t[i]=lst[a[i]];
    }REP(i,n) if (s[i]<t[i]) return 0*puts("No");
//    REP(i,n) printf("%d ",s[i]);puts("");
//    REP(i,n) printf("%d ",t[i]);puts("");
    puts("Yes");
    return 0;
}
/*
*/

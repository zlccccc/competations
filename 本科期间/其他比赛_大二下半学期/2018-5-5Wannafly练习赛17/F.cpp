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
const LL maxn=1e6+7;
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

int mark[maxn];
char a[maxn],b[maxn];
int fail[maxn];
int nxt[maxn];
int main() {
    int T;
    int i,j;
    scanf("%d",&T);
    while(T--){
        scanf("%s%s",b+1,a+1);
        int n=strlen(a+1);
        int m=strlen(b+1);
        FOR(i,1,m) mark[i]=0;
        fail[0]=fail[1]=0;
        FOR(i,2,n){
            j=fail[i-1];
            while (j&&a[j+1]!=a[i]) j=fail[j];
            if (a[j+1]==a[i]) fail[i]=j+1;
            else fail[i]=j;
        }
        j=0;int cnt=0;
        FOR(i,1,m){
            while (j&&a[j+1]!=b[i]) j=fail[j];
            if (a[j+1]==b[i]) j++;
            if (j==n) j=fail[j],mark[i-n+1]=1;
        }
//        FOR(i,1,m-n+1) printf("%d ",mark[i]);puts("");
        int t=m-n+1;
        if (t%2==1){
            if (mark[t/2+1]) puts("Alice");
            else if (t!=1&&mark[t/2]&&mark[t/2+2]) puts("Alice");
            else puts("Bob");
        }else{
            if (mark[t/2]&&mark[t/2+1]) puts("Alice");
            else puts("Bob");
        }
    }
    return 0;
}
/*
*/

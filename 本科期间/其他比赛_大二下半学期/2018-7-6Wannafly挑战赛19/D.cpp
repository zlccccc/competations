#include <sstream>
#include <fstream>
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

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
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

int len;
char A[maxn],str[maxn*2];
int p[maxn*2];
void manacher(int n){
    int i;
    str[0]='+';
    str[1]='%';
    REP(i,n+1) {
        str[i*2+2]=A[i+1];
        str[i*2+3]='%';
    }len=n*2+2;
    int id=0,mx=0;
    FOR(i,1,len-1) {
        if (mx>i) p[i]=min(p[2*id-i],mx-i);
        else p[i]=1;
        while (str[i+p[i]]==str[i-p[i]]) p[i]++;
        if (p[i]+i>mx) {
            mx=p[i]+i;
            id=i;
        }
    }
}
int ADD[27],DEL[27];
ll f_l[maxn],f_r[maxn],g_l[maxn],g_r[maxn];
int TaskA(){
    int n,m,x,y,z;
    int i,j,k;
    scanf("%s",A+1);
    n=strlen(A+1);
    REP(i,26) scanf("%d%d",&DEL[i],&ADD[i]);
    manacher(n);
    FOR(i,1,n) g_l[i]=DEL[A[i]-'a']+g_l[i-1];
    FOR(i,1,n) f_l[i]=min(ADD[A[i]-'a']+f_l[i-1],g_l[i]);
    rFOR(i,1,n) g_r[i]=DEL[A[i]-'a']+g_r[i+1];
    rFOR(i,1,n) f_r[i]=min(ADD[A[i]-'a']+f_r[i+1],g_r[i]);
//    FOR(i,1,len-1) printf("%-2c ",str[i]);puts("");
//    FOR(i,1,len-1) printf("%-2d ",i);puts("");
//    FOR(i,1,len-1) printf("%-2d ",p[i]);puts("");
    ll ans=INFF;
    FOR(i,1,len-1){
        int l=(i-p[i])/2,r=(i+1+p[i])/2;
//        printf("%d:%d-%d\n",i,l,r);
        ans=min(ans,g_l[l]+f_r[r]);
        ans=min(ans,f_l[l]+g_r[r]);
//        printf("  %lld %lld\n",g_l[l]+f_r[r],f_l[l]+g_r[r]);
    }printf("%lld\n",ans);
    return 0;
}
void initialize(){}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	int T=1;
//	scanf("%d",&T);
	startTime=clock();
	while (T--) TaskA();
	debug("/--- computeTime: %ld milliseconds ---/\n",clock()-startTime);
}
/*
lllll
1000 1100
350 700
200 800
2000 2000
2000 432
2000 2000
2000 2000
2000 2000
2000 2000
20 2000
2000 2000
350 35
200 800
2000 2000
2000 2000
2000 2000
2000 2000
2000 2000
2000 2000
2000 2000
2000 2000
2000 2000
2000 2000
2000 2000
15 2000
2000 2000
*/

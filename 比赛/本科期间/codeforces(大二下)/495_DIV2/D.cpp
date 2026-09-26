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

int cnt[maxn];
int now[maxn];
int MAX,MIN;
bool check(int N,int M,int X,int Y){
    int i,j;
    FOR(i,0,MAX) now[i]=cnt[i];
    FOR(i,1,N) FOR(j,1,M) {
        if (!now[abs(i-X)+abs(j-Y)]) return 0;
        now[abs(i-X)+abs(j-Y)]--;
    }return 1;
}
int TaskA(){
    int n,k,i,j;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&k),cnt[k]++;
    MIN=MAX=1;
    while (cnt[MIN]==MIN*4) MIN++;
    while (cnt[MAX]) MAX++;MAX--;
    FOR(i,1,n) if (n%i==0){
        int N,M,X,Y;
        N=i;M=n/i;
        X=MIN;Y=M-(MAX-(N-X));
//        printf("%d %d %d %d\n",N,M,X,Y);
        if (N-X+1<MIN) continue;
        if (N-M-X-Y-1>MAX) continue;
        if (Y<=0) continue;
        if (check(N,M,X,Y)) return 0*printf("%d %d\n%d %d\n",N,M,X,Y);
    }puts("-1");
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
*/

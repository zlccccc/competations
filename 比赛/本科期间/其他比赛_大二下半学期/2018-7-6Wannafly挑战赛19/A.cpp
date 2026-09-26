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

char A[maxn][6];
int B[maxn],Q[maxn];
bool mark[maxn];
vector<int> pre,suf;
int ans[maxn],top;
int TaskA(){
    int i,n;
    scanf("%d",&n);
    FOR(i,1,n) mark[i]=0;
    FOR(i,1,n) scanf("%d",&Q[i]);
    int q; scanf("%d",&q);
    FOR(i,1,q) scanf("%s%d",A[i],&B[i]);
    pre.clear(); suf.clear();
    rFOR(i,1,q){
        if (mark[B[i]]) continue;
        if (A[i][0]=='F') pre.push_back(B[i]);
        else suf.push_back(B[i]);
        mark[B[i]]=1;
    }top=0;
    for (int v:pre) ans[++top]=v;
    FOR(i,1,n) if (!mark[Q[i]]) ans[++top]=Q[i];
    reverse(suf.begin(),suf.end());
    for (int v:suf) ans[++top]=v;
    FOR(i,1,n) printf("%d%c",ans[i]," \n"[i==n]);
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

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
const LL M=998244353;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

int S[maxn],top;
ll A[maxn];int okay[maxn];
int pre[maxn],suf[maxn];
int TaskA(){
    int i,j,k,n;
    scanf("%d",&n);
    FOR(i,1,n) okay[i]=0;
    FOR(i,1,n) scanf("%lld",&A[i]);
    top=0;
    FOR(k,1,n){
        while (top>1){
            int i=S[top-1],j=S[top];
            if ((A[j]-A[i])*(k-j)>=(A[k]-A[j])*(j-i)) top--;
            else break;
        }S[++top]=k;
    }FOR(i,1,top) okay[S[i]]=1;
//    FOR(i,1,top) printf("%d ",S[i]);puts("");
    FOR(i,1,n) if (okay[i]) pre[i]=suf[i]=i;
    FOR(i,1,n) if (!pre[i]) pre[i]=pre[i-1];
    rFOR(i,1,n) if (!suf[i]) suf[i]=suf[i+1];
    ll p,q; p=0;q=1;
    FOR(k,1,n){
        i=pre[k],j=suf[k]; if (i==j) continue;
        ll P=(A[k]*(j-i)-A[i]*(j-i)-(k-i)*(A[j]-A[i]));
        ll Q=j-i;
//        printf("%d :%d - %d %lld %lld\n",k,i,j,P,Q);
        ll G=gcd(P,Q); P/=G; Q/=G;
        if (P*q>Q*p) p=P,q=Q;
    }q*=2; ll g=gcd(p,q);
    p/=g; q/=g; if (p==0) q=1;
    if (q==1) printf("%lld\n",p);
    else printf("%lld/%lld\n",p,q);
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
3 3
1 2 0
2 3 1
1 3 1
*/

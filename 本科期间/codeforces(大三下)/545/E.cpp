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
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=6e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

pair<ll,ll> S[maxn];//position; bias
//维护单调递减
int top;
ll len;//left_base
ll k,b;
pll getAns(pll now){
	return make_pair(k*now.first+now.second+b,now.first);
}
long double getK(pll A,pll B){
	return (long double)(A.second-B.second)/(A.first-B.first);
}
int main() {
	int i,n;
	scanf("%lld%d",&len,&n);
	S[++top]=make_pair(0,0);//pos+=A*x+B
	FOR(i,1,n) {
		int op,x,y;
		scanf("%d",&op);
		if (op==1) {
			scanf("%d",&x);
			len+=x; S[1]=make_pair(0,0);//pos
			k=b=0; top=1;//no 1
		} else if (op==2) {
			scanf("%d",&x);
			if ((double)k*len+b>2e18) continue;
			pll now=make_pair(len,-(k*len+b));
			while (top>1&&getK(S[top],now)<=getK(S[top-1],S[top])) top--;
			S[++top]=now; len+=x;//b2
		} else {
			scanf("%d%d",&x,&y);
			k+=y; b+=x;
		} while (top>1&&getAns(S[top])>getAns(S[top-1])) top--;
		pll Ansnow=getAns(S[top]);
		printf("%lld %lld\n",Ansnow.second+1,Ansnow.first);
		// int i;printf("top=%d\n",top);
		// FOR(i,1,top) printf("(%lld,%lld(%lld,%lld)) ",S[i].first,S[i].second,getAns(S[i]).first,getAns(S[i]).second);puts("");
	}
}
/*
*/
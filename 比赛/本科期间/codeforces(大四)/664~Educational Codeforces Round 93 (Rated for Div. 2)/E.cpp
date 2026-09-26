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
const LL maxn=1e6+107;
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
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

set<int> A,B,C,D;//A:first; B:changed; C:second
//A:spell A;
//B:spell 1(choose from);
//C:spell 0(choose from);
//D:spell all_choose;
int n,cnt;
bool Remove(set<int> &x,int val) {//could get
	auto it=x.find(val);
	if (it==x.end()) return 0;
	x.erase(it); return 1;
}
bool Find(set<int> &x,int val) {
	auto it=x.find(val);
	if (it==x.end()) return 0;
	return 1;
}
void Insert(set<int> &x,int val) {
	x.insert(val);
}
int low(set<int> &x) {
	if (!x.size()) return 0;
	return *(x.begin());
}
int high(set<int> &x) {
	if (!x.size()) return 0;
	return *(x.rbegin());
}
ll now=0,more=0;
int main() {
	int i;
	scanf("%d",&n);
	FOR(i,1,n) {
		int x,y;
		scanf("%d%d",&x,&y);
		now+=y; //A:spell 1
		if (x==1) {
			if (y<0) {
				Remove(A,-y);
				if (!Remove(B,-y)) Remove(D,-y),more-=-y;
			} else Insert(A,y),Insert(B,y);
		} else {
			if (y<0) {
				if (!Remove(C,-y)) Remove(D,-y),more-=-y;
			} else Insert(C,y);
		}
		if (D.size()) {//refine
			int x=low(D);
			Remove(D,x); more-=x;
			if (Find(A,x)) Insert(B,x);
			else Insert(C,x);
		}
		while (D.size()!=A.size()) {
			//D.size()>0
			int x=high(B),y=high(C);
			if (x>y) Insert(D,x),Remove(B,x),more+=x;
			else Insert(D,y),Remove(C,y),more+=y;
		}
		// printf("B.size()=%d; more=%lld; now=%lld\n",(int)B.size(),more,now);
		// printf("D.size()=%d; more=%lld; now=%lld\n",(int)D.size(),more,now);
		if (B.size()||(!A.size())) printf("%lld\n",now+more);
		else printf("%lld\n",now+more-low(A)+high(C));
	}
}
/*
6
1 5
0 10
1 -5
0 5
1 11
0 -10

*/
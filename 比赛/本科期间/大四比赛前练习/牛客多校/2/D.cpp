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
const LL maxn=5e4+107;
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

struct status {
	ll sum; bitset<100> bit;
	status(ll sum,bitset<100> bit) {
		this->sum=sum; this->bit=bit;
	}
	const bool operator < (const status &B) const {
		return sum>B.sum;
	}
};
int A[107],B[107];
int id[107];
char str[107];
bitset<100> ini[100],e[100];
priority_queue<status> Q;
int main() {
	int i,j;
	int n,k;
	scanf("%d%d",&n,&k);
	REP(i,n) scanf("%d",&A[i]);
	REP(i,n) {
		id[i]=i;
		scanf("%s",str);
		REP(j,n) ini[i].set(j,str[j]-'0');
	} sort(id,id+n,[](int i,int j) {
		return A[i]<A[j];
	});
	REP(i,n) B[i]=A[id[i]];
	REP(i,n) REP(j,n) e[i][j]=ini[id[i]][id[j]];
	// REP(i,n) {
	// 	REP(j,n) printf("%d ",(int)e[i][j]); puts("");
	// }
	Q.push(status(0,bitset<100>()));
	while (Q.size()&&k) {
		// printf("%lld ",Q.top().sum);
		k--;
		if (!k) {
			printf("%lld",Q.top().sum);
			break;
		} else {
			status v=Q.top(); Q.pop();
			int lst=0;
			REP(i,n) if (v.bit[i]) lst=i+1;
			//start,generate
			int c=v.bit.count();
			rep(i,lst,n) {
				if ((int)(e[i]&v.bit).count()==c) {
					bitset<100> now=v.bit; now.set(i);
					Q.push(status(v.sum+B[i],now));
					break;
				}
			}
			if (lst) {//to_right
				v.bit.set(lst-1,0); v.sum-=B[lst-1];
				int c=v.bit.count();
				rep(i,lst,n) {
					if ((int)(e[i]&v.bit).count()==c) {
						bitset<100> now=v.bit; now.set(i);
						Q.push(status(v.sum+B[i],now));
						break;
					}
				}
			}
		}
	} if (k) puts("-1");
}
/*
3 100
3 1 2
011
100
100
*/

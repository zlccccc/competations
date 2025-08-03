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

typedef ll BaseType;
const int MaxBit=32;
struct L_B {
	BaseType b[MaxBit];
	L_B() {clear();}
	void clear() {memset(b,0,sizeof(b));}
	BaseType XORMIN(BaseType x) {
		int i;
		rREP(i,MaxBit) if ((b[i]^x)<x) x^=b[i];
		return x;
	}
	void insert(BaseType x) {
		int i;
		rREP(i,MaxBit) if ((x>>i)&1) {
			if (!b[i]) b[i]=x; x^=b[i];
		}
	}
	void rebuild() {
		int i,j;
		rREP(i,MaxBit) rREP(j,i) if ((b[i]>>j)&1) b[i]^=b[j];
	}
} T[maxn*4];
//求交 merge的思路: 只要A中merge之后的线性无关组
L_B merge(const L_B &A,const L_B &B) {
	int i,j; L_B ret; ret.clear();
	static BaseType base[MaxBit],tmp[MaxBit];//previous_A
	REP(i,MaxBit) tmp[i]=A.b[i],base[i]=1ll<<i;
	REP(i,MaxBit) if (B.b[i]) {//正者反着应该没区别
		BaseType now=B.b[i];
		bool okay=1; BaseType k=0;//base; A
		rREP(j,MaxBit) if ((now>>j)&1) {
			if (tmp[j]) {
				now^=tmp[j]; k^=base[j];
			} else {
				tmp[j]=now; base[j]=k; okay=0; break;
			}
		}
		if (okay) {
			BaseType should=0;
			REP(j,MaxBit) if ((k>>j)&1) should^=A.b[j];
			ret.insert(should);
		}
	}
	return ret;
}
void build(int x,int L,int R) {
	if (L==R)  {
		int k,i; ll v; scanf("%d",&k);
		REP(i,k) {
			scanf("%lld",&v);
			T[x].insert(v);
		} return;
	} int mid=(L+R)/2;
	build(x<<1,L,mid);
	build(x<<1|1,mid+1,R);
	T[x]=merge(T[x<<1],T[x<<1|1]);
}
bool query(int x,int l,int r,ll val,int L,int R) {
	// printf("val=%lld\n",val);
	if (l<=L&&R<=r) return (T[x].XORMIN(val)==0);
	int mid=(L+R)/2; bool ret=1;
	if (l<=mid) ret&=query(x<<1,l,r,val,L,mid);
	if (mid<r) ret&=query(x<<1|1,l,r,val,mid+1,R);
	return ret;
}
int main() {
	// int T,_; T=1;
	// scanf("%d",&T);
	int n,i,q;
	scanf("%d%d",&n,&q);
	build(1,1,n);
	FOR(i,1,q) {
		int l,r; ll x;
		scanf("%d%d%lld",&l,&r,&x);
		if (query(1,l,r,x,1,n)) puts("YES");
		else puts("NO");
	}
}
/*
1 3
2 10000000000 20000000000
1 1 0
1 1 30000000000
1 1 40000000000

1 3
2 4294967296 8589934592
1 1 00000000
1 1 12884901888
1 1 40000000
*/
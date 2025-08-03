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

int m;
struct node{
	ll v[10][10];//nxt
	node(){
		int i; memset(v,0,sizeof(v));
		REP(i,10) v[i][i]=1;
	}
}T[maxn<<2];
void resolve(int value,node &x) {
	int i,j;
	REP(i,m) REP(j,m) x.v[i][j]=0;
	REP(i,m) {
		rep(j,i,m) {
			if ((value>>j)&1) break;
			x.v[i][j]=x.v[j][i]=1;
		}
	}
}
node merge(node &A,node &B) {
	node ret; int i,j,k;
	REP(i,m) ret.v[i][i]=0;
	REP(i,m) REP(j,m) {
		REP(k,m) ((ret.v[i][j]+=A.v[i][k]*B.v[k][j])>=INFF)&&(ret.v[i][j]%=M);
		ret.v[i][j]%=M;
	} return ret;
}
int value[maxn];
void build(int x,int L,int R) {
	if (L==R) {resolve(value[L],T[x]); return;}
	int mid=(L+R)/2;
	build(x<<1,L,mid); build(x<<1|1,mid+1,R);
	T[x]=merge(T[x<<1],T[x<<1|1]);
}
void update(int x,int pos,int L,int R) {
	if (L==R) {resolve(value[L],T[x]); return;}
	int mid=(L+R)/2;
	if (pos<=mid) update(x<<1,pos,L,mid);
	else update(x<<1|1,pos,mid+1,R);
	T[x]=merge(T[x<<1],T[x<<1|1]);
}
char str[107];
int main() {
	int i,_;
	int n,q;
	scanf("%d%d",&n,&m);
	scanf("%d",&q);
	FOR(i,1,n) {
		scanf("%s",str);
		REP(_,m) value[i]|=(str[_]-'0')<<_;
	}
	build(1,1,n);
	FOR(i,1,q) {
		int o,a,b;
		scanf("%d%d%d",&o,&a,&b);
		if (o==1) {
			b--; value[a]^=1<<b;
			update(1,a,1,n);
		} else {
			a--; b--;
			printf("%lld\n",T[1].v[a][b]);
		}
	}
}
/*
*/

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
const LL maxn=1e5+107;
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

struct Point {
	int x,y,z;
};
int n,m,h,q;
inline int getid(int x,int y,int z) {
	return (x-1)*m*h+(y-1)*h+z-1;
}
int ini[maxn],valx[maxn],valy[maxn],valz[maxn],all[maxn];
const int SIZE=1000;
vector<Point> V;
int dis(const Point &x,const Point &y) {
	return abs(x.x-y.x)+abs(x.y-y.y)+abs(x.z-y.z);
}
int root;
void solvez(int i,int j) {
	int k;
	FOR(k,1,h) {
		int id=getid(i,j,k);
		if (k!=1) valz[id]=min(valy[id],valz[getid(i,j,k-1)]+1);//pref sum
		else valz[id]=valy[id];
		all[id]=min(all[id],valz[id]);
	} rFOR(k,1,h) {
		int id=getid(i,j,k);
		if (k!=h) valz[id]=min(valy[id],valz[getid(i,j,k+1)]+1);//pref sum
		else valz[id]=valy[id];
		all[id]=min(all[id],valz[id]);
	}
}
void solvey(int i) {
	int j,k;
	FOR(j,1,m) {
		FOR(k,1,h) {
			int id=getid(i,j,k);
			if (j!=1) valy[id]=min(valx[id],valy[getid(i,j-1,k)]+1);//pref sum
			else valy[id]=valx[id];
		} solvez(i,j);
	}
	rFOR(j,1,m) {
		FOR(k,1,h) {
			int id=getid(i,j,k);
			if (j!=m) valy[id]=min(valx[id],valy[getid(i,j+1,k)]+1);//pref sum
			else valy[id]=valx[id];
		} solvez(i,j);
	}
}
void solvex() {
	int i,j,k;
	FOR(i,1,n) {
		FOR(j,1,m) FOR(k,1,h) {
			int id=getid(i,j,k);
			if (i!=1) valx[id]=min(ini[id],valx[getid(i-1,j,k)]+1);
			else valx[id]=ini[id];
		} solvey(i);
	}
	rFOR(i,1,n) {
		FOR(j,1,m) FOR(k,1,h) {
			int id=getid(i,j,k);
			if (i!=n) valx[id]=min(ini[id],valx[getid(i+1,j,k)]+1);
			else valx[id]=ini[id];
		} solvey(i);
	}
}
int main() {
	int _;
	scanf("%d%d%d%d",&n,&m,&h,&q);
	memset(all,0x3f,sizeof(all));
	// startTimer();
	FOR(_,1,q) {
		int x,y,z,op;
		// x=1; y=1; z=1; op=1;
		scanf("%d%d%d%d",&op,&x,&y,&z);
		if (op==1) {
			V.push_back(Point{x,y,z});
		} else {
			if (V.size()>=SIZE) {
				memset(ini,0x3f,sizeof(ini));
				for (Point Y:V) ini[getid(Y.x,Y.y,Y.z)]=0;
				solvex();
				V.clear();
			}
			int ans=all[getid(x,y,z)]; Point X=Point{x,y,z};
			for (Point Y:V) ans=min(ans,dis(X,Y));
			printf("%d\n",ans);
		}
	}
	// printTimer();
}
/*
100000 1 1 100000

10000 1 1 1000
*/
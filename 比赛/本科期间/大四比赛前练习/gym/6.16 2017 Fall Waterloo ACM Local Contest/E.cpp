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

struct rect {
	int xl,xr,yl,yr;
};
vector<rect> A;
void splitrect(int s) {
	vector<rect> tmp;
	A.swap(tmp);
	for (rect now:tmp) {
		vector<int> xs,ys;
		xs.push_back(now.xl); xs.push_back(now.xr);
		ys.push_back(now.yl); ys.push_back(now.yr);
		if (now.yl<s-now.xl&&s-now.xl<now.yr) ys.push_back(s-now.xl);
		if (now.yl<s-now.xr&&s-now.xr<now.yr) ys.push_back(s-now.xr);
		if (now.xl<s-now.yl&&s-now.yl<now.xr) xs.push_back(s-now.yl);
		if (now.xl<s-now.yr&&s-now.yr<now.xr) xs.push_back(s-now.yr);
		sort(xs.begin(), xs.end());
		sort(ys.begin(), ys.end());
		for (int xi=0; xi<(int)xs.size()-1; xi++)
			for (int yi=0; yi<(int)ys.size()-1; yi++)
				A.push_back(rect{xs[xi],xs[xi+1],ys[yi],ys[yi+1]});
	}
}
vector<int> Vx,Vy;
vector<pair<int,int> > val[maxn];
vector<rect> useful;
int getidx(int x) {
	return lower_bound(Vx.begin(),Vx.end(),x)-Vx.begin();
}
int getidy(int x) {
	return lower_bound(Vy.begin(),Vy.end(),x)-Vy.begin();
}
int s[maxn];
ll getins() {
	int i,j;
	// Vx.clear(); Vy.clear();
	for (rect now:useful) {
		Vx.push_back(now.xl);
		Vx.push_back(now.xr);
		Vy.push_back(now.yl);
		Vy.push_back(now.yr);
	}
	sort(Vx.begin(), Vx.end());
	Vx.erase(unique(Vx.begin(), Vx.end()),Vx.end());
	sort(Vy.begin(), Vy.end());
	Vy.erase(unique(Vy.begin(), Vy.end()),Vy.end());
	REP(i,(int)Vx.size()) val[i].clear();
	for (rect now:useful) {
		val[getidx(now.xl)].push_back(make_pair(now.yl,1));
		val[getidx(now.xl)].push_back(make_pair(now.yr,-1));
		val[getidx(now.xr)].push_back(make_pair(now.yl,-1));
		val[getidx(now.xr)].push_back(make_pair(now.yr,1));
	}
	REP(j,(int)Vy.size()) s[j]=0;
	ll ret=0;
	REP(i,(int)Vx.size()-1) {
		int nowysum=0,sum=0;
		for (auto now:val[i])
			s[getidy(now.first)]+=now.second;
		REP(j,(int)Vy.size()-1) {
			sum+=s[j]; assert(sum>=0);
			if (sum) nowysum+=Vy[j+1]-Vy[j];
		}
		// printf("%d to %d: * %d\n",Vx[i],Vx[i+1],nowysum);
		ret+=(ll)(Vx[i+1]-Vx[i])*nowysum;
	}
	return ret;
}
ll gettri(int base) {
	ll now=getins();
	int cross=0,i,j;
	REP(j,(int)Vy.size()) s[j]=0;
	REP(i,(int)Vx.size()) {
		int nowysum=0,sum=0;
		for (auto now:val[i])
			s[getidy(now.first)]+=now.second;
		REP(j,(int)Vy.size()) {
			sum+=s[j]; assert(sum>=0);
			if (sum) nowysum+=Vy[j+1]-Vy[j];
		} if (nowysum) cross+=(Vx[i+1]-Vx[i])*base;
		// printf("  %d to %d: * nowysum=%d\n",Vx[i],Vx[i+1],nowysum);
	}
	now+=cross;
	// printf("cross=%d; now=%lld\n",cross,now);
	return now/2;
}
int main() {
	// printTable();
	int i,n,l,r;
	scanf("%d%d%d",&n,&l,&r);
	FOR(i,1,n) {
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		rect now=rect{min(a,c),max(a,c),min(b,d),max(b,d)};
		// printf("%d %d %d %d\n",A.xl,A.xr,A.yl,A.yr);
		A.push_back(now);
	}
	splitrect(l); splitrect(r);
	splitrect(l); splitrect(r);
	splitrect(l); splitrect(r);
	splitrect(l); splitrect(r);
	// for (rect now:A) printf("%d %d to %d %d\n",now.xl,now.yl,now.xr,now.yr);
	ll ans=0;
	useful.clear();
	for (rect now:A) if (now.xl+now.yl<r)//可能有交, 不能用r
			useful.push_back(now);
	ans+=getins();
	// printf("lowerthanr:%lld\n",ans);
	useful.clear();
	for (rect now:A) if (now.xl+now.yl<l)
			useful.push_back(now);
	ans-=getins();
	// printf("upperchanl:%lld\n",ans);

	useful.clear();
	for (rect now:A) if (now.xl+now.yl<r&&r<now.xr+now.yr){
			useful.push_back(now);
			assert(now.xr-now.xl==now.yr-now.yl);
			assert(now.yl+now.xr==r);
		}
	ans-=gettri(-1);
	// printf("tril:%lld\n",ans);
	useful.clear();
	for (rect now:A) if (now.xl+now.yl<l&&l<now.xr+now.yr){
			useful.push_back(now);
			assert(now.xr-now.xl==now.yr-now.yl);
			assert(now.yl+now.xr==l);
		}
	ans+=gettri(1);
	// printf("trir:%lld\n",ans);
	printf("%lld\n",ans);
}
/*
*/
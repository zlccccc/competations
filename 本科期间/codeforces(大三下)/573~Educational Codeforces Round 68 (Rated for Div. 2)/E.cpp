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
const LL maxn=10000+107;
const double pi=acos(-1.0);
const double eps=1e-10;
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

struct node{
	int x,l,r;//x:same
};
vector<node> ver,hor,useful;
inline int lowbit(int x){
	return x&-x;
}
int T[maxn];
inline void update(int x) {
	x+=5001;
	for (;x<=10001;x+=lowbit(x)) T[x]++;
}
inline int query(int x){
	int ret=0; x+=5001;
	for (;x;x-=lowbit(x)) ret+=T[x];
	return ret;
}
int main() {
	int n;
	int i;
	scanf("%d",&n);
	FOR(i,1,n) {
		int x1,x2,y1,y2;
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		if (x1>x2) swap(x1,x2);
		if (y1>y2) swap(y1,y2);
		if (x1==x2) hor.push_back(node{x1,y1,y2});
		else ver.push_back(node{y1,x1,x2});
	}
	sort(ver.begin(), ver.end(),[](node A,node B){
		return A.x<B.x;
	});
	sort(hor.begin(), hor.end(),[](node A,node B){
		return A.l<B.l;
	});
	int xi,xj;
	ll ans=0;
	REP(xi,(int)ver.size()) {
		auto now=ver[xi];
		useful.clear();
		memset(T,0,sizeof(T));
		for (auto line:hor) {
			if (now.l<=line.x&&line.x<=now.r&&
				line.l<=now.x&&now.x<=line.r) useful.push_back(line);//相交
		}
		// printf("ver:%d: %d-%d; line.size=%d\n",now.x,now.l,now.r,(int)useful.size());
		int top=0;
		REP(xj,xi) {
			// printf("%d-%d: \n",xj,xi);
			auto nxt=ver[xj];
			while (top<(int)useful.size()&&useful[top].l<=nxt.x){
				// printf("update:%d\n",useful[top].x);
				update(useful[top].x); top++;
			}
			int l=max(nxt.l,now.l),r=min(nxt.r,now.r);
			if (l<=r) {
				int got=query(r)-query(l-1);
				// printf("got=%d\n",got);
				ans+=got*(got-1)/2;
			}
		}
	}
	printf("%lld\n",ans);
}
/*
*/
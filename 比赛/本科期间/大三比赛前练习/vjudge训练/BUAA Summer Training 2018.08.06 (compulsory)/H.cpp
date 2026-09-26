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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double DB;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const DB eps=1e-14;
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
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

inline int dcmp(DB x) {
	return (x > eps) - (x < -eps);
}
struct Point {
	DB x , y;
	Point(DB x = 0 , DB y = 0) : x(x) , y(y) {}
	void input() {
		double X,Y;
		scanf("%lf%lf",&X,&Y);
		x=X; y=Y;
	}
	bool operator < (const Point &R) const {
		if (dcmp(x - R.x) == 0)
			return dcmp(y - R.y) < 0;
		return dcmp(x - R.x) < 0;
	}
	bool operator == (const Point &R) const {
		return dcmp(x - R.x) == 0 && dcmp(y - R.y) == 0;
	}
	Point operator + (const Point &R) const {
		return Point(x + R.x , y + R.y);
	}
	Point operator - (const Point &R) const {
		return Point(x - R.x , y - R.y);
	}
	Point operator * (const DB &R) const {
		return Point(x * R , y * R);
	}
	Point operator / (const DB &R) const {
		return Point(x / R , y / R);
	}
	DB operator ^ (const Point &R) const {
		return x * R.y - y * R.x;
	}
	DB operator % (const Point &R) const {
		return x * R.x + y * R.y;
	}
	DB len() {
		return sqrt(*this % *this);
	}
	DB angle() {
		return atan2(y , x);
	}
};
// 直线交点，v和w为两个直线的方向向量，
// 设交点的参数为P+vt,Q+wt,连立方程解t
// 线段，射线对这个t的参数有限制，很好理解。
Point GetLineIntersection(Point P , Point v , Point Q , Point w) {
	Point u = P - Q;
	DB t1 = (w ^ u) / (v ^ w);
	return P + v * t1;
}
// 判断线段是否严格相交。
bool SegmentProperIntersection(Point a1 , Point a2 , Point b1 , Point b2) {
	DB c1 = (a2 - a1) ^ (b1 - a1);
	DB c2 = (a2 - a1) ^ (b2 - a1);
	if (dcmp(c1) == 0 && dcmp(c2) == 0) {
		if (a2 < a1) swap(a1 , a2);
		if (b2 < b1) swap(b1 , b2);
		return max(a1 , b1) < min(a2 , b2);
	}
	DB c3 = (b2 - b1) ^ (a1 - b1);
	DB c4 = (b2 - b1) ^ (a2 - b1);
	return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
// 点是否在线段上,判定方式为到两个端点的方向是否不一致。
bool OnSegment(Point P , Point a1 , Point a2) {
	DB len = (P - a1).len();
	if (dcmp(len) == 0) return true;
	a1 = a1 - P , a2 = a2 - P;
	return dcmp((a1 ^ a2) / len) == 0 && dcmp(a1 % a2) <= 0;
}
bool SegmentIntersection(Point a1 , Point a2 , Point b1 , Point b2) {
	return SegmentProperIntersection(a1,a2,b1,b2)
	       ||OnSegment(a1,b1,b2)||OnSegment(a2,b1,b2)
	       ||OnSegment(b1,a1,a2)||OnSegment(b2,a1,a2);
}
Point st[maxn],ed[maxn];
vector<Point> all;
vector<Point> ans[maxn];
int fa[maxn];
inline int getfa(int x) {
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
int main() {
	int i,j;
	scanf("%d",&n);
	FOR(i,1,n) st[i].input(),ed[i].input();
	FOR(i,1,n) fa[i]=i;
	FOR(i,1,n) {
		all.push_back(st[i]); all.push_back(ed[i]);
		ans[i].push_back(st[i]); ans[i].push_back(ed[i]);
		FOR(j,1,i-1) {
			if (SegmentIntersection(st[i],ed[i],st[j],ed[j])) {
				Point z=GetLineIntersection(st[i],(ed[i]-st[i])/(ed[i]-st[i]).len(),
				                            st[j],(ed[j]-st[j])/(ed[j]-st[j]).len());
				all.push_back(z);
				ans[i].push_back(z); ans[j].push_back(z);
				int x=getfa(i),y=getfa(j);
				if (x!=y) fa[x]=y;
			}
		}
	} int lcnt,pcnt,bcnt;
	lcnt=pcnt=bcnt=0;
	FOR(i,1,n) {
		sort(ans[i].begin(), ans[i].end());
		ans[i].erase(unique(ans[i].begin(), ans[i].end()),ans[i].end());
	} sort(all.begin(), all.end());
	all.erase(unique(all.begin(),all.end()),all.end());
	FOR(i,1,n) lcnt+=ans[i].size()-1;
	pcnt=all.size();
	FOR(i,1,n) if (fa[i]==i) bcnt++;
	// printf("%d %d %d\n",lcnt,pcnt,bcnt);
	printf("%d\n",lcnt-pcnt+bcnt);
}
/*
3
0 0 1 1
0 0 1 0
1 0 1 1
*/
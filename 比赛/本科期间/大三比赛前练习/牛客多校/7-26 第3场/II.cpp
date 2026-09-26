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

#define DEBUG1
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
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void mul_(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod_(T &A,ll B=M) {A%=M;}
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
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_n_m_q() {while (~scanf("%d%d%d",&n,&m,&q)) TaskA();}
void Task_more_string() {while (~scanf("%s",str)) TaskA();}

inline int dcmp(double x) {
	return (x > eps) - (x < -eps);
}

struct Point {
	double x , y;
	Point(double x = 0 , double y = 0) : x(x) , y(y) {}
	void input() {
		scanf("%lf%lf",&x,&y);
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
	Point operator * (const double &R) const {
		return Point(x * R , y * R);
	}
	Point operator / (const double &R) const {
		return Point(x / R , y / R);
	}
	double operator ^ (const Point &R) const {
		return x * R.y - y * R.x;
	}
	double operator % (const Point &R) const {
		return x * R.x + y * R.y;
	}
	double len() {
		return sqrt(*this % *this);
	}
	double angle() {
		return atan2(y , x);
	}
} p[maxn],s[maxn];
int sgn(double x) {
	if (fabs(x) < eps)return 0;
	if (x < 0)return -1;
	else return 1;
}
double dist(Point a,Point b) {
	return sqrt((a-b)%(a-b));
}
inline LL OnLeft(Point P , Point A , Point B) {
	return (B - A) ^ (P - A);
}
bool _cmp(Point p1,Point p2) {
	double tmp = (p1-p[0])^(p2-p[0]);
	if (sgn(tmp) > 0)return true;
	else if (sgn(tmp) == 0 && sgn(dist(p1,p[0]) - dist(p2,p[0])) <= 0)
		return true;
	else return false;
}
int Stack[20],top;
double get(int n) {
	int i; top=0;
	REP(i,n) {
		p[i].x=(double)rand()/32768,p[i].y=(double)rand()/32768;
		if (p[i].x<p[i].y) swap(p[i].x,p[i].y);
	}
	Point p0=p[0]; int k=0;
	for (int i = 1; i < n; i++) {
		if ((p0.y > p[i].y) || (p0.y == p[i].y && p0.x > p[i].x)) {
			p0 = p[i]; k = i;
		}
	}
	swap(p[k],p[0]);
	sort(p+1,p+n,_cmp);
	Stack[0] = 0;
	Stack[1] = 1;
	top = 2;
	for (int i = 2; i < n; i++) {
		while (top > 1 &&
		        sgn((p[Stack[top-1]]-p[Stack[top-2]])^(p[i]-p[Stack[top-2]])) <= 0)//把<= 改为<即把凸包上共线的亦包含上
			top--; Stack[top++] = i;
	}
	REP(i,top) s[i]=p[Stack[i]];
	return top;
}
void solve(int x) {
	int i,k; int cnt=1000000;
	double all=0; srand(time(0));
	FOR(k,1,5) {
		REP(i,cnt) all+=get(x);
		printf("%f\n",all/(cnt*k));
	}

}
double ans[maxn];
int TaskA() {
	int i;
	// rep(i,4,11) solve(i);
	ans[3]=3;
	rep(i,4,11) ans[i]=2./(i-1)+ans[i-1];
	REP(i,3) scanf("%*d%*d");
	scanf("%d",&n); printf("%f\n",ans[i]);
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_one();
}
/*
3.694296
*/
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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
// const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
const double eps = 1e-10 , pi = acos(-1.0);
inline int dcmp(double x) {
	return (x > eps) - (x < -eps);
}
struct Point {
	double x , y , z;
	Point () {x = y = z = 0;}
	Point (double _x , double _y , double _z) {
		x = _x , y = _y , z = _z;
	}
	void input() {
		scanf("%lf%lf%lf" , &x , &y , &z);
	}
	bool operator < (const Point &R) const {
		if (dcmp(x - R.x) != 0)
			return x < R.x;
		if (dcmp(y - R.y) != 0)
			return y < R.y;
		return z < R.z;
	}
	bool operator == (const Point &R) const {
		return dcmp(x - R.x) == 0 && dcmp(y - R.y) == 0 && dcmp(z - R.z) == 0;
	}
	Point operator + (const Point& R) const {
		return Point(x + R.x , y + R.y , z + R.z);
	}
	Point operator - (const Point& R) const {
		return Point(x - R.x , y - R.y , z - R.z);
	}
	Point operator * (const double& R) const {
		return Point(x * R , y * R , z * R);
	}
	Point operator / (const double& R) const {
		return Point(x / R , y / R , z / R);
	}
	double operator % (const Point& R) const {
		return x * R.x + y * R.y + z * R.z;
	}
	Point operator ^ (const Point& R) const {
		return Point(y * R.z - z * R.y , z * R.x - x * R.z , x * R.y - y * R.x);
	}
	inline double len() {
		return sqrt(*this % *this);
	}
}; 
Point Rotate(Point a, Point b, double angle) {
	static Point e1 ,e2 , e3;
	b = b / b.len() , e3 = b;
	double lens = a % e3;
	e1 = a - e3 * lens;
	if (dcmp(e1.len()) > 0)
		e1 = e1 / e1.len();
	else
		return a;
	e2 = e1 ^ e3;
	double x1 = a % e2 , y1 = a % e1 , x2 , y2;
	x2 = x1 * cos(angle) - y1 * sin(angle);
	y2 = x1 * sin(angle) + y1 * cos(angle);
	return e3 * lens + e1 * y2 + e2 * x2;
}
Point A,B,C;
void solve() {
	A=Point(0.5,0,0);
	B=Point(0,0.5,0);
	C=Point(0,0,0.5);
	double n;
	scanf("%lf",&n);
	static int x=0;
	printf("Case #%d:\n",++x);
	if (n<=1.414213) {
		double alpha=pi/4-acos(n/sqrt(2));
		A=Rotate(A,Point(0,0,1),alpha);
		B=Rotate(B,Point(0,0,1),alpha);
		C=Rotate(C,Point(0,0,1),alpha);
	}else{
		double beta=asin(n/sqrt(3))-atan(sqrt(2));
		// double beta=acos(n/sqrt(6));
		// printf("beta=%f cos=%f\n",beta,cos(beta));
		A=Rotate(A,Point(0,0,1),pi/4);
		B=Rotate(B,Point(0,0,1),pi/4);
		A=Rotate(A,Point(1,0,0),beta);
		B=Rotate(B,Point(1,0,0),beta);
		C=Rotate(C,Point(1,0,0),beta);
	}printf("%.15f %.15f %.15f\n",A.x,A.y,A.z);
	printf("%.15f %.15f %.15f\n",B.x,B.y,B.z);
	printf("%.15f %.15f %.15f\n",C.x,C.y,C.z);
}
int main() {
	// printf("%f %f %f\n",sqrt(2)/2,sqrt(6)/6,2*sqrt(6)/6);
	// printf("%f %f\n",sqrt(6)/3,sqrt(6)/6);
	// printf("%f %f\n",acos(sqrt(6)/3)/pi*180,acos(sqrt(6)/6)/pi*180);
	// printf("%f\n",2*acos(sqrt(3)/3)/pi*180);
	// printf("%f\n",cos(acos(sqrt(3)/3)));
	int T;
	scanf("%d",&T);
	while (T--) solve();
	return 0;
}
/*
5
1
1.414213
1.732050
*/

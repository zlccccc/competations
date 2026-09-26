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
const LL maxn=1e4+107;
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
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
int n,m,q;
// char str[maxn];

struct ball{
	int x,y,z,r;
}; vector<ball> all;
double dis(ball a,ball b){
	return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2)+pow(a.z-b.z,2));
}
int main() {
	int _,T;
	scanf("%d",&T);
	FOR(_,1,T){
		int i; scanf("%d",&n); all.clear();
		FOR(i,1,n) {
			int x,y,z,r;
			scanf("%d%d%d%d",&x,&y,&z,&r);
			all.push_back(ball{x,y,z,r});
		} ball O; int x,y,z,r;
		scanf("%d%d%d%d",&x,&y,&z,&r);
		long double ans=0;
		O=ball{x,y,z,r};
		for (auto now:all){
			long double R=O.r,r=now.r;
			long double d=dis(O,now);
			if (d>=R+r) continue;
			if (d<=R-r) ans+=4./3*pi*r*r*r;
			else {
				ans+=4./3*pi*r*r*r;
				long double h=(R*R-r*r-d*d)/2/d;
				long double del_more=pi*(2*r+h)*(r-h)*(r-h)/3;
				long double H=h+d;
				long double add_more=pi*(2*R+H)*(R-H)*(R-H)/3;
				ans-=del_more;
				ans+=add_more;
			}
		} printf("Case #%d: %.13f\n",_,(double)ans);
	}
}
/*
100
2 3 5 7 11 12 1000 100000 1000000 10000000 1000000000 10000000000
*/
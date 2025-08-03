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
const LL maxn=1e6+107;
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

//题意: 定义运算"ADD"每位都是每位相加, 问你n个数"ADD"完结果是k的方案数
//结果mod 2^58
//做法: fwt套fft; 定义一个w10是10次方根; 然后定义一个和fft相似的运算
//定义一个原根x(w10), fft过程中对x^10-1取模即可得到答案
//然而x^10-1不满足x^0+...+x^n=0 条件, 所以先取因子1-x+x^2-x^3+x^4, 在模意义下运算
//mod 1-x+x^2-x^3+x^4; 循环节必须为10s
int Mod[]= {1,-1,1,-1,1};
struct poly {
	ull x[4];//系数,1,x,x^2...
	poly() {memset(x,0,sizeof(x));}
	const poly operator +(const poly &p)const {
		poly ret; int i;
		REP(i,4) ret.x[i]=x[i]+p.x[i];
		return ret;
	}
	const poly operator *(const poly &p) const {
		static ull tmp[7]; int i,j;
		poly ret;
		memset(tmp,0,sizeof(tmp));
		REP(i,4) REP(j,4) tmp[i+j]+=x[i]*p.x[j];
		rrep(i,4,7) rREP(j,5) tmp[i-j]-=tmp[i]*Mod[4-j];
		REP(i,4) ret.x[i]=tmp[i];
		return ret;
	}
} value[100007]; //solve
poly w10[20];
//fwt套fft
void fwt(poly value[],int len,int inv) { //inv=1,-1
	for (int x=10; x<=len; x*=10) {
		for (int y=0; y<len; y+=x) {
			int _x=x/10;
			for (int z=y; z<(y+_x); z++) {//fft
				vector<poly> now,nxt; int i,j;
				now.resize(10); nxt.resize(10);
				REP(i,10) now[i]=value[z+_x*i];
				REP(i,10) REP(j,10) nxt[i]=nxt[i]+now[j]*w10[(10+i*inv)*j%10];
				REP(i,10) value[z+_x*i]=nxt[i];
			}
		}
	}
}
inline poly poww(poly a, int b) {
	poly ret; ret.x[0]=1;
	for (; b; b>>=1,a=a*a)
		if (b&1) ret=ret*a;
	return ret;
}
const ull mod=1ull<<58;
inline ull poww(ull a, ull b) {
	ull ret=1;
	for (; b; b>>=1,a=a*a)
		if (b&1) ret=ret*a;
	return ret;
}
int main() {
	int i;
	w10[0].x[0]=1; w10[1].x[1]=1;
	rep(i,2,20) w10[i]=w10[i-1]*w10[1];
	int n; int x;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&x),value[x].x[0]++;
	fwt(value,100000,1);
	REP(i,100000) value[i]=poww(value[i],n);
	// REP(i,100000) printf("%llu %llu %llu %llu\n",value[i].x[0],value[i].x[1],value[i].x[2],value[i].x[3]);
	fwt(value,100000,-1);
	ull inv5=poww(5,mod/2-1);
	REP(i,n) {
		ull ans=value[i].x[0];
		ans/=32; ans*=inv5*inv5*inv5*inv5*inv5; ans%=mod;
		printf("%llu\n",ans);
		// printf("%llu %llu %llu %llu\n",value[i].x[0],value[i].x[1],value[i].x[2],value[i].x[3]);
	} //这里的x^k%P必须不一样;
	// REP(i,20) {
		// printf("%llu %llu %llu %llu\n",w10[i].x[0],w10[i].x[1],w10[i].x[2],w10[i].x[3]);
	// }
}
/*
2
15 16

4
15 17 15 17

5
0 1 2 3 4

6
0 1 2 3 4 5 

10
0 1 2 3 4 5 6 7 8 9 10 
*/
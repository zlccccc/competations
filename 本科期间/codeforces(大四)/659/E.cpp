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
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

const int mod = 1e9+7;
struct mint {
	ll x;
	mint():x(0) {}
	mint(ll x):x((x%mod+mod)%mod) {}
	// mint(ll x):x(x){}
	mint &fix() { x = (x%mod+mod)%mod; return *this;}
	mint operator-() const { return mint(0) - *this;}
	mint operator~() const { return mint(1) / *this;}
	mint &operator+=(const mint &a) { if ((x+=a.x)>=mod) x-=mod; return *this;}
	mint &operator-=(const mint &a) { if ((x+=mod-a.x)>=mod) x-=mod; return *this;}
	mint &operator*=(const mint &a) { (x*=a.x)%=mod; return *this;}
	mint &operator/=(const mint &a) { (x*=a.pow(mod-2).x)%=mod; return *this;}
	mint operator+(const mint &a)const { return mint(*this) += a;}
	mint operator-(const mint &a)const { return mint(*this) -= a;}
	mint operator*(const mint &a)const { return mint(*this) *= a;}
	mint operator/(const mint &a)const { return mint(*this) /= a;}
	mint pow(ll t) const {
		if (!t) return 1;
		mint res = pow(t/2);
		res *= res;
		return (t&1)?res*x:res;
	}
	bool operator<(const mint &a)const { return x < a.x;}
	bool operator==(const mint &a)const { return x == a.x;}
};
int bruteforce(string s) {
	set<string> S,T;
	S.insert("");
	for (auto c:s) {
		for (auto str:S) {
			if (str.length()==0) T.insert(str+c);
			else {
				if (c=='0') {
					T.insert(str);//ALL
					T.insert(str+'0');
				} if (c=='1') {
					T.insert(str+'1');
					*str.rbegin()='1';
					T.insert(str);
				}
			}
		} S.swap(T);
		set<string>().swap(T);
		// for (auto now:S) cout<<now<<' '; puts("");
	}
	printf("%d\n",(int)T.size());
	return T.size();
}
mint val_kzero[maxn],to_next[maxn];//last as zero
mint dp[maxn];
char str[maxn];
int main() {
	scanf("%s",str+1);
	int n=strlen(str+1),i;
	FOR(i,1,n) if (str[i]=='1') break;
	if (i==n+1) return 0*printf("%d ",n);//all zero
	int noww=i-1; n-=noww;//last_zero
	FOR(i,1,n) str[i]=str[i+noww];
	// s=""; FOR(i,1,n) s+=str[i];
	// bruteforce(s);
	int count=0;
	to_next[0]=mint(1);
	FOR(i,1,n) {
		if (str[i]=='1') { //end at x counts(sum)
			count=0;
			dp[i]=to_next[count];
			to_next[0]=dp[i];//1+1
			to_next[1]+=dp[i];
		} else {//连续不超过k //get:
			count++;
			dp[i]=to_next[count]; to_next[count]=mint(0);
			to_next[count+1]+=dp[i];
			to_next[0]+=dp[i];
		} val_kzero[count]+=dp[i];
		// printf("%2d(%c): %4lld  val_kzero=",i,str[i],dp[i].x);
		// int t; FOR(t,0,10) printf("%4lld ",val_kzero[t].x); puts("");
	} mint ans(0);
	FOR(i,0,count) ans+=val_kzero[i];
	printf("%lld\n",ans.x*(noww+1)%M);
}
/*
2
5
01011
11100


*/
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
const LL M=998244353;
const LL maxn=1e7+107;
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

map<char,string> MP;
char ts[]="QWE";
bool same(string A,string B) {
	sort(A.begin(),A.end());
	sort(B.begin(),B.end());
	return A==B;
}
int dp[100007][3][3][3];//dp_more
string str;
int min4,min3[3],min2[3][3];
int main() {
	cin>>str;
	MP['Y']="QQQ";
	MP['V']="QQW";
	MP['G']="QQE";
	MP['C']="WWW";
	MP['X']="QWW";
	MP['Z']="WWE";
	MP['T']="EEE";
	MP['F']="QEE";
	MP['D']="WEE";
	MP['B']="QWE";
	int _,i,j,k;
	REP(i,3) REP(j,3) REP(k,3) dp[0][i][j][k]=3;
	REP(_,(int)str.length()) {
		string s=MP[str[_]];
		REP(j,3) REP(k,3) min4=min3[k]=min2[j][k]=INF;
		REP(i,3) REP(j,3) REP(k,3) {
			dp[_+1][i][j][k]=INF;
			min_(min4,dp[_][i][j][k]);
			min_(min3[k],dp[_][i][j][k]);
			min_(min2[j][k],dp[_][i][j][k]);
		}
		REP(i,3) REP(j,3) REP(k,3) {
			string ss=""; ss+=ts[i]; ss+=ts[j]; ss+=ts[k];
			if (!same(ss,s)) continue;
			// cout<<ss<<s<<"\n";
			min_(dp[_+1][i][j][k],dp[_][i][j][k]+1);//one
			min_(dp[_+1][i][j][k],min2[i][j]+2);//one
			min_(dp[_+1][i][j][k],min3[i]+3);//two
			min_(dp[_+1][i][j][k],min4+4);//three
		}
	} int ans=INF;
	REP(i,3) REP(j,3) REP(k,3) min_(ans,dp[str.length()][i][j][k]);
	printf("%d\n",ans);
}
/*
60 100
1.0285714285714
*/
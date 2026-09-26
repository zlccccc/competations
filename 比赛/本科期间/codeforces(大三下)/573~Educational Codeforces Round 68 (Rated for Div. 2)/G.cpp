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
const LL maxn=1e6+7;
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

//maximize:
//mod:1,2,4,8
int f[107][10][10][1<<8][3];
char s[maxn];
//竟然是直接算进位...
//考虑最后那个数字是几
//more:0:less,1:equ,2:greater
vector<pair<int,int> > now;
int n;
int X,Y;
int query(int pos,int more_x,int more_y,int mask,int more) {
	// printf("querying: %d %d %d %d %d\n",pos,more_x,more_y,mask,more);
	int i;
	REP(i,(int)now.size()) if (((mask>>(i*2))&3)==3) {mask=3; break;}
	if (pos==n) return !more_x&&!more_y&&more&&mask==3;
	if (f[pos][more_x][more_y][mask][more]!=-1)
		return f[pos][more_x][more_y][mask][more];
	int ret=0,k;
	REP(k,10) {
		int nowx=X*k+more_x,nowy=Y*k+more_y;
		int ax=nowx%10,ay=nowy%10,nxtmask=mask,nxtmore=more;
		REP(i,(int)now.size()) {
			if (ax==now[i].first) nxtmask|=1<<(i*2);
			if (ay==now[i].second) nxtmask|=1<<(i*2+1);
		}
		if (ay>s[pos]-'0') nxtmore=0;
		if (ay<s[pos]-'0') nxtmore=2;
		add_(ret,query(pos+1,nowx/10,nowy/10,nxtmask,nxtmore));
	}
	// printf("query: %d %d %d %d %d: %d\n",pos,more_x,more_y,mask,more,ret);
	return f[pos][more_x][more_y][mask][more]=ret;
}
int main() {
	scanf("%s",s);
	n=strlen(s);
	reverse(s,s+n);
	int i,j,k;
	int ans=0;
	FOR(i,1,9) FOR(j,i,9) if (gcd(i,j)==1) {
		X=i; Y=j;//outside
		if (i==1&&j==1) {
			int base=1; ans=0;
			REP(k,n) add_(ans,(ll)base*(s[k]-'0')%M),mul_(base,10);
			// printf("base=%d\n",ans);
		} else {
			now.clear();
			FOR(k,1,10) if (k*i<=9&&k*j<=9) now.push_back(make_pair(i*k,j*k));
			int _l,_i,_j,_sta,_m;
			REP(_l,n) REP(_i,10) REP(_j,10) REP(_sta,(1<<((int)now.size()*2))) REP(_m,3) {
				f[_l][_i][_j][_sta][_m]=-1;
			}
			// printf("get: %d %d\n",i,j);
			memset(f,0xff,sizeof(f));
			int base=query(0,0,0,0,1);
			add_(ans,base);
			// return 0;
			if (i!=j) add_(ans,base);
		}
	}
	printf("%d\n",ans);
}
/*
*/
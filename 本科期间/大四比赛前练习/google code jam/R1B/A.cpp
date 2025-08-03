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

int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T) {
		int n,m,i;
		pair<int,int> ansx,ansy;
		vector<pair<int,int> > px,py;
		ansx=ansy=make_pair(0,0);
		scanf("%d%d",&n,&m);
		FOR(i,1,n) {
			int x,y; char c[2];
			scanf("%d%d%s",&x,&y,c);
			if (c[0]=='N') py.push_back(make_pair(y+1,1));
			if (c[0]=='S') py.push_back(make_pair(y,-1));
			if (c[0]=='E') px.push_back(make_pair(x+1,1));
			if (c[0]=='W') px.push_back(make_pair(x,-1));
		}
		sort(px.begin(), px.end());
		sort(py.begin(), py.end());
		int now=0;
		REP(i,(int)px.size()) {
			now+=px[i].second;
			if (i==(int)px.size()-1||px[i].first!=px[i+1].first){
				ansx=max(ansx,make_pair(now,-px[i].first));
			}
		} now=0;
		REP(i,(int)py.size()) {
			now+=py[i].second;
			if (i==(int)py.size()-1||py[i].first!=py[i+1].first){
				ansy=max(ansy,make_pair(now,-py[i].first));
			}
		}
		// printf("first: %d %d\n",ansx.first,ansy.first);
		printf("Case #%d: %d %d\n",_,-ansx.second,-ansy.second);
	}
}
/*
3
1 10
5 5 N
4 10
2 4 N
2 6 S
1 5 E
3 5 W
8 10
0 2 S
0 3 N
0 3 N
0 4 N
0 5 S
0 5 S
0 8 S
1 5 W
*/
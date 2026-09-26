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
const LL maxn=1e5+107;
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

int A[maxn],B[maxn];
int value[2][1007][1007];
vector<int> v;
vector<pii> p;
int g[4][4];//count_g
pair<int,int> S[4]; int top;//top=last
ll ans[5];
int main() {
	int n,m;
	while (~scanf("%d%d",&n,&m)) {
		int i,j,k,o;
		FOR(i,1,4) ans[i]=0;
		FOR(i,1,n) scanf("%d%d",&A[i],&B[i]);
		REP(k,2) FOR(i,1,m) FOR(j,1,m) value[k][i][j]=0;
		FOR(i,1,n) value[A[i]<B[i]][A[i]][B[i]]++;
		REP(k,2) FOR(i,1,m) FOR(j,1,m){
			value[k][i][j]+=value[k][i-1][j]+value[k][i][j-1]-value[k][i-1][j-1];
		}
		// REP(k,2) {
		// 	FOR(i,1,m) {
		// 		FOR(j,1,m) printf("%d ",value[k][i][j]);
		// 		puts("");
		// 	} puts("");
		// }
		FOR(o,1,n) {
			v.clear();
			v.push_back(0);
			v.push_back(m);
			v.push_back(A[o]-1);
			v.push_back(B[o]-1);
			sort(v.begin(), v.end());
			REP(k,2) rep(i,1,4) rep(j,1,4) {
				int now=value[k][v[i]][v[j]];
				now-=value[k][v[i-1]][v[j]];
				now-=value[k][v[i]][v[j-1]];
				now+=value[k][v[i-1]][v[j-1]];
				if (!now) continue;
				p.clear();
				p.push_back(make_pair(v[i],-k));
				p.push_back(make_pair(v[j],-(k^1)));
				p.push_back(make_pair(A[o],-2)); //3
				p.push_back(make_pair(B[o],-3)); //4
				top=0;
				for (auto nowp:p) {
					int pos=upper_bound(S,S+top,nowp)-S;
					if (pos==top) top++;
					S[pos]=nowp;
				}
				ans[top]+=now;
				// for (auto nowp:p) printf("(%d,%d)",nowp.first,nowp.second); puts("");
				// printf("%d: (k=%d)(%d-%d,%d-%d):%d; top=%d\n",o,k,v[i-1],v[i],v[j-1],v[j],now,top);
			}
		}
		FOR(i,1,4) printf("%lld%c",ans[i]," \n"[i==4]);
	}
}
/*
*/
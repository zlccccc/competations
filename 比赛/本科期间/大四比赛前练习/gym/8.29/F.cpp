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
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

map<string,int> MP; int tot;
vector<pair<int,int> > edges[maxn];//v_edges
vector<pair<int,int> > ei[307][307];//v_edges
queue<pii> Q;
int used[maxn];
int e[307][307],ne[307][307];
int main(){
	int n,i,k;
	string A,B;
	cin>>A>>B; cin>>n;
	if (A==B) return 0*puts("No");
	MP[A]=0; MP[B]=1; tot=2;
	FOR(i,1,n) {
		int t; cin>>t;
		while (t--) {
			cin>>A>>B;
			if (!MP.count(A)) MP[A]=tot++;
			if (!MP.count(B)) MP[B]=tot++;
			int x=MP[A],y=MP[B];
			// printf(" e: %d->%d\n",x,y);
			edges[i].push_back(make_pair(x,y));
			ei[x][y].push_back(make_pair(i,1));//yes
			ei[y][x].push_back(make_pair(i,2));//not
		} used[i]=0;
	} e[0][1]=1;
	assert(tot<=300);
	Q.push(make_pair(0,1));
	while (Q.size()) {
		pii now=Q.front(); Q.pop();
		int x=now.first,y=now.second;
		assert(e[x][y]);
		if (x==y) return 0*puts("No");
		if (e[y][x]) return 0*puts("No");
		// printf("%d->%d\n",x,y);
		REP(i,tot) if (e[i][x]||i==x) {
			REP(k,tot) if ((y==k||e[y][k])&&!e[i][k]&&i!=k) {//more
				pii now; now.first=i; now.second=k; e[i][k]=1;
				Q.push(make_pair(i,k));//must_use_it
			}
		}
		for (auto now:ei[x][y]) {//first
			int id=now.first,dir=now.second;
			// printf("id=%d; dir=%d\n",id,dir);
			if (!used[id]) {
				used[id]=dir;
				for (auto now:edges[id]) {
					// if (used[id]==2) swap(now.first,now.second);//no_use
					if (dir==1&&!e[now.first][now.second]) {//A->B
						e[now.first][now.second]=1;
						Q.push(make_pair(now.first,now.second));
					} else if (dir==2&&e[now.first][now.second]) {//NOT A->B
						 return 0*puts("No");
					}
				}
			} else {
				if (used[id]!=dir) return 0*puts("No");
			}
		}
	} 
	puts("Yes");
}
/*
Alice Bob
3
2
Alice Bob
Bob Clare
2
Bob Clare
Clare David
2
Clare David
David Alice

Alice David
3
2
Alice Bob
Bob Clare
2
Bob Clare
Clare David
2
Clare David
David Alice

Alice Bob
1
2
Clare David
David Clare
*/
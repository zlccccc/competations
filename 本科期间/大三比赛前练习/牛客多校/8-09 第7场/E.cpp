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
const LL maxn=1e6+7;
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
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

vector<pair<int,int> > v;
int g[76][76];
void addedge(int x,int y){
	g[x][y]=g[y][x]=1;
	if (x!=y) v.push_back(make_pair(x,y)); 
}
void check(){
	int i,j,k,l;
	int ans=0;
	FOR(i,1,75) FOR(j,i+1,75) FOR(k,j+1,75) FOR(l,k+1,75){
		if (g[i][j]&&g[i][k]&&g[i][l]&&g[j][k]&&g[j][l]&&g[k][l]) ans++;
	}printf("%d\n",ans);
}
void test(){
	int i,j;
	FOR(i,1,75) {
		FOR(j,i+1,75) {
			addedge(i,j);
			printf("add: %d-%d\n",i,j);
			check();
		}
	} check();
}
char have[maxn][76];
int main() {
	int i,j,k;
	startTimer();
	have[0][1]=75; have[0][2]=75;//MAX
	FOR(i,3,75) have[0][i]=i;
	FOR(k,0,1000000){
		FOR(i,3,75) if (have[k][i]<have[k][i-1]&&have[k][i]!=75){
			int now=(i-1)*(i-2)/2;
			if (k+now>1000000) break;
			// bool change=0;
			// FOR(j,1,75) {
			// 	if (j!=i&&have[k+now][j]!=have[k][j]) {
			// 		change=(have[k+now][j]<have[k][j]); break;
			// 	} if (j==i&&have[k+now][j]!=have[k][j]+1) {
			// 		change=(have[k+now][j]<1+have[k][j]); break;
			// 	}
			// } if (change==0) continue;
			FOR(j,1,75) have[k+now][j]=have[k][j];
			have[k+now][i]++;
		}
	}
	have[0][1]=75; have[0][2]=75;//MAX
	FOR(i,3,75) have[0][i]=i;
	FOR(k,0,1000000){;
		if (have[k][1]!=75) printf("NO: %d\n",k);
		FOR(i,3,75) if (have[k][i]<have[k][i-1]&&have[k][i]!=75){
			int now=(i-1)*(i-2)/2;
			if (k+now>1000000) break;
			bool change=0;
			FOR(j,1,75) {
				if (j!=i&&have[k+now][j]!=have[k][j]) {
					change=(have[k+now][j]<have[k][j]); break;
				} if (j==i&&have[k+now][j]!=have[k][j]+1) {
					change=(have[k+now][j]<1+have[k][j]); break;
				}
			} if (change==0) continue;
			FOR(j,1,75) have[k+now][j]=have[k][j];
			have[k+now][i]++;
		}
	}
	printTimer();
	scanf("%d",&n);
	// FOR(i,1,75) printf("%d ",have[n][i]);
	FOR(i,1,75){
		FOR(j,i,have[n][i]) addedge(i,j);
	}
	// check();
	printf("75 %d\n",(int)v.size());
	for (auto now:v) printf("%d %d\n",now.first,now.second);
}
/*

*/

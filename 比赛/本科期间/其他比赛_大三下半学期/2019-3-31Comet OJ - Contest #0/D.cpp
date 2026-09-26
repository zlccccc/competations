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

int f[64][181][181];//bits,x,y,minz
vector<int> mor[64];
int A[6][8],bit[64];
int main() {
	int T,_;
	int i,j,k;
	scanf("%d",&T);
	REP(i,64) REP(k,6) {
		if ((i>>k)&1) bit[i]++;
		else mor[i].push_back(k);
	}
	FOR(_,1,T) {
		REP(k,6) scanf("%d%d%d%d%d%d%d",&A[k][1],&A[k][2],&A[k][4],&A[k][3],&A[k][5],&A[k][6],&A[k][7]);
		int sta,ans=0,lst=0;
		memset(f,0x3f,sizeof(f)); f[0][0][0]=0;
		REP(sta,64) {
			FOR(i,0,180) {
				FOR(j,0,180) {
					if (f[sta][i][j]<=180){
						if (bit[sta]>ans) ans=bit[sta],lst=INF;
						if (bit[sta]==ans) lst=min(lst,max(max(i,j),f[sta][i][j]));
						for (int v:mor[sta]){
							int nxt;// nxt time
							if (i+A[v][1]<=180) min_(f[sta|(1<<v)][i+A[v][1]][j],f[sta][i][j]);
							if (j+A[v][2]<=180) min_(f[sta|(1<<v)][i][j+A[v][2]],f[sta][i][j]);
							if (f[sta][i][j]+A[v][4]<=180)
								min_(f[sta|(1<<v)][i][j],f[sta][i][j]+A[v][4]);
							nxt=max(i,j)+A[v][3];
							if (nxt<=180) min_(f[sta|(1<<v)][nxt][nxt],f[sta][i][j]);
							nxt=max(i,f[sta][i][j])+A[v][5];
							if (nxt<=180) min_(f[sta|(1<<v)][nxt][j],nxt);
							nxt=max(j,f[sta][i][j])+A[v][6];
							if (nxt<=180) min_(f[sta|(1<<v)][i][nxt],nxt);
							nxt=max(max(i,j),f[sta][i][j])+A[v][7];
							if (nxt<=180) min_(f[sta|(1<<v)][nxt][nxt],nxt);
						}
					}
				}
			}
		}
		printf("%d %d\n",ans,lst);
	}
}
/*
1
200 200 200 200 200 100 200
200 200 200 200 60 200 200
200 200 200 60 200 200 200
200 200 60 200 200 200 200
200 60 200 200 200 200 200
60 200 200 200 200 200 200
*/
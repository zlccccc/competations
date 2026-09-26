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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=600+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j,k,t;
int ans;
char a[maxn][maxn];
bool up[maxn][maxn],dn[maxn][maxn],le[maxn][maxn],ri[maxn][maxn],mark[maxn][maxn];
void dfs(int x,int y){
	if (mark[x][y]) return;
	mark[x][y]=1;
	if (up[x][y]) dfs(x-1,y);
	if (dn[x][y]) dfs(x+1,y);
	if (le[x][y]) dfs(x,y-1);
	if (ri[x][y]) dfs(x,y+1);
}
int main(){
	while (~scanf("%d",&n)){
		REP(i,2*n-1) scanf("%s",&a[i]);
		memset(le,0,sizeof(le));
		memset(ri,0,sizeof(ri));
		memset(up,0,sizeof(up));
		memset(dn,0,sizeof(dn));
		memset(mark,0,sizeof(mark));
		REP(i,2*n)
			REP(j,2*n) ri[i][j]=le[i][j+1]=1;
		REP(i,2*n-1)
			REP(j,2*n+1) up[i+1][j]=dn[i][j]=1;
		REP(i,2*n-1){
			REP(j,n)
				if (i%2==0){
					if (a[i][j]=='H'){
						ri[i][j*2]=le[i][j*2+1]=1;
						ri[i+1][j*2]=le[i+1][j*2+1]=1;
						dn[i][j*2]=up[i+1][j*2]=0;
						dn[i][j*2+1]=up[i+1][j*2+1]=0;
					}else {
						ri[i][j*2]=le[i][j*2+1]=0;
						ri[i+1][j*2]=le[i+1][j*2+1]=0;
						dn[i][j*2]=up[i+1][j*2]=1;
						dn[i][j*2+1]=up[i+1][j*2+1]=1;
					}
				}else {
					if (a[i][j]=='H'){
						ri[i][j*2+1]=le[i][j*2+2]=1;
						ri[i+1][j*2+1]=le[i+1][j*2+2]=1;
						dn[i][j*2+1]=up[i+1][j*2+1]=0;
						dn[i][j*2+2]=up[i+1][j*2+2]=0;
					}else {
						ri[i][j*2+1]=le[i][j*2+2]=0;
						ri[i+1][j*2+1]=le[i+1][j*2+2]=0;
						dn[i][j*2+1]=up[i+1][j*2+1]=1;
						dn[i][j*2+2]=up[i+1][j*2+2]=1;
				}
			}
		}
//		REP(i,2*n){
//			REP(j,2*n+1) printf("%d ",ri[i][j]);
//			puts("");
//		}
//			puts("");
//		REP(i,2*n){
//			REP(j,2*n+1) printf("%d ",le[i][j]);
//			puts("");
//		}
		ans=-1;
		REP(i,2*n)
			REP(j,2*n+1) if (!mark[i][j]) {dfs(i,j);ans++;}
		printf("%d\n",ans);
	}
}

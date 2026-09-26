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
#define rep(I,pos,N) for (I=pos;I<N;I++)
#define rrep(I,pos,N) for (I=N-1;I>=pos;I--)
#define FOR(I,pos,N) for (I=pos;I<=N;I++)
#define rFOR(I,pos,N) for (I=N;I>=pos;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

#define x x_x
#define y y_y
int n,m,q,t,T;
int i,j,k;
int ans;
int up[maxn][maxn],le[maxn][maxn],lu[maxn][maxn],a[maxn][maxn];
int main(){
	scanf("%d",&T);
	FOR(t,1,T){
		scanf("%I64d",&n);
		FOR(i,1,n)
			FOR(j,1,n)
				scanf("%d",&a[i][j]);
		FOR(i,1,n)
			FOR(j,1,n){
				if (a[i][j]) up[i][j]=up[i-1][j]+1,le[i][j]=le[i][j-1]+1;
				else up[i][j]=le[i][j]=0;
			}
		FOR(i,1,n)
			FOR(j,1,n){
				if (a[i][j]) up[i][j]=up[i-1][j]+1,le[i][j]=le[i][j-1]+1;
				else up[i][j]=le[i][j]=0;
				lu[i][j]=min(up[i][j],le[i][j]);
			}
//		FOR(i,1,n){
//			FOR(j,1,n){
//				printf("%d ",up[i][j]);
//			}puts("");
//		}
		ans=0;
		FOR(i,1,n)//i,jÐÐ 
			FOR(j,1,n){
				REP(k,lu[i][j])
					if (up[i][j-k]>k&&le[i-k][j]>k) ans++;
			}
		printf("Case %d: %d\n",t,ans);
	}
}
/*
*/

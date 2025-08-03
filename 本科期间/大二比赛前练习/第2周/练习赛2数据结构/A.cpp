#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=5e5+7;
const double eps=0.00000001;
const LL INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}

int n,m,q,t;
int i,j,k;
pair<int,int> now[257];
int a[257][257];
int sum[257][257];
int MIN,ans;
int len,l,r;
int main(){
	int T,x=0;
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&m);
		FOR(i,1,n){
			FOR(j,1,m) scanf("%d",&a[i][j]);
		}
		scanf("%d",&q);
		printf("Case %d:\n",++x);
		while (q--){
			scanf("%d",&t);
			FOR(i,1,n){
				FOR(j,1,m){
					sum[i][j]=sum[i-1][j];
					if (a[i][j]>=t) sum[i][j]++;
					else sum[i][j]--;
				}
			}
//			FOR(i,1,n){
//				FOR(j,1,m){
//					printf("%2d ",sum[i][j]);
//				}puts("");
//			}
			ans=0;
			rFOR(len,1,n){//i->j
				for(l=1;l+len-1<=n;l++){
					if (len*m<=ans) continue;
					r=l+len-1;
					now[0]=make_pair(0,0);
					FOR(k,1,m){
						now[k].first=now[k-1].first+sum[r][k]-sum[l-1][k];
						now[k].second=k;
					}
					sort(now,now+1+m);
//					printf("l,r=%d %d:",i,j);
//					FOR(k,1,m) printf(" |%2d~%2d|",now[k].first,now[k].second);puts("");
					MIN=m;
					FOR(k,0,m){
						MIN=min(MIN,now[k].second);
						ans=max(ans,(now[k].second-MIN)*len);
					}
//					printf("ans=%d\n",ans);
				}
			}
			printf("%d\n",ans);
		}
	}
}
/*
*/

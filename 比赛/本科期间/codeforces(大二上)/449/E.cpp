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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

const int SIZE=400,MAX=100000;
int tot;
int block[100007];
int cnt[257][100007],fa[257][100007];
int tag[257],big[257];//orz
int a[100007];//id
inline int getfa(int i,int &x){
	if (fa[i][x]==x) return x;
	return x=fa[i][x]=getfa(i,fa[i][x]);
}
int main(){
	int i,j,k;
	int n,m;
	FOR(i,1,MAX) block[i]=i/SIZE;
	FOR(i,0,MAX/SIZE)
		FOR(j,1,MAX) fa[i][j]=j;
	scanf("%d%d",&n,&m);
	FOR(i,1,n){
		scanf("%d",&a[i]);
		cnt[block[i]][a[i]]++;
		big[block[i]]=max(big[block[i]],a[i]);
	}//puts("read_ok");
	FOR(k,1,m){
		int t,l,r,x,ans=0;
		scanf("%d%d%d%d",&t,&l,&r,&x);
//		FOR(i,1,n) printf("%d ",getfa(block[i],a[i]));puts("  <-  (pre)val");
//		FOR(i,0,n/SIZE) printf("%d ",tag[i]);puts("  <-  tag");
//		FOR(i,0,n/SIZE) printf("%d ",big[i]);puts("  <-  big");puts("");
		if (block[l]==block[r]){
			if (t==1){
				FOR(i,l,r) if (getfa(block[i],a[i])>x+tag[block[i]]) {
					cnt[block[i]][a[i]]--;
					a[i]-=x;
					cnt[block[i]][a[i]]++;
				}
			}else
				FOR(i,l,r) if (getfa(block[i],a[i])==x+tag[block[i]]) ans++;
		}else{
			if (t==1){
				int pos=(block[l]+1)*SIZE-1;
//				printf("change1:%d-%d\n",l,pos);
				FOR(i,l,pos) if (getfa(block[i],a[i])>x+tag[block[i]]) {
					cnt[block[i]][a[i]]--;
					a[i]-=x;
					cnt[block[i]][a[i]]++;
				}
				FOR(i,block[l]+1,block[r]-1){
					if (tag[i]+x*2<=big[i]){ 
						FOR(j,tag[i]+1,tag[i]+x){
							cnt[i][j+x]+=cnt[i][j];
							cnt[i][j]=0;
							fa[i][j]=j+x;
						}tag[i]+=x;
					}else if (x+tag[i]<big[i]){
						FOR(j,x+tag[i]+1,big[i]){
							cnt[i][j-x]+=cnt[i][j];
							cnt[i][j]=0;
							fa[i][j]=j-x;
						}big[i]=x+tag[i];
					}
				}
				pos=block[r]*SIZE;
//				printf("change2:%d-%d\n",pos,r);
				FOR(i,pos,r) if (getfa(block[i],a[i])>x+tag[block[i]]) {
					cnt[block[i]][a[i]]--;
					a[i]-=x;
					cnt[block[i]][a[i]]++;
				}
			}else{
				int pos=(block[l]+1)*SIZE-1;
				FOR(i,l,pos) if (getfa(block[i],a[i])==x+tag[block[i]]) ans++;
				FOR(i,block[l]+1,block[r]-1) if (x+tag[i]<=big[i]) ans+=cnt[i][x+tag[i]];
				pos=block[r]*SIZE;
				FOR(i,pos,r) if (getfa(block[i],a[i])==x+tag[block[i]]) ans++;
			}
		}if (t==2) printf("%d\n",ans);
	}
}
/*
*/

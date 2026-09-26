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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int i,j;
int n,m,k;
int VAL[maxn];
vector<LL> val[maxn],sum[maxn];
int main(){
	scanf("%d%d",&n,&m);
	val[1].push_back(0);sum[1].push_back(0);
	FOR(i,2,n){
		scanf("%d",&VAL[i]);LL now=0;
		for (j=i;j;now+=VAL[j],j/=2){
			val[j].push_back(now);
			sum[j].push_back(0);
		}
	}
	FOR(i,1,n){
		sort(val[i].begin(),val[i].end());
		sum[i][0]=val[i][0];
		rep(j,1,sum[i].size()) sum[i][j]=val[i][j]+sum[i][j-1];
//		printf("%d : \n",i);
//		REP(j,val[i].size()) printf("%d ",val[i][j]);puts("");
//		REP(j,sum[i].size()) printf("%d ",sum[i][j]);puts("");
	}while (m--){
		int x;
		LL len;
		scanf("%d%I64d",&x,&len);
		LL ans=0,pre=0,prelen;
		for (;x&&len>0;len-=VAL[x],pre=x,prelen=VAL[x],x/=2){
			int pos=upper_bound(val[x].begin(),val[x].end(),len)-val[x].begin()-1;
			ans+=(pos+1)*len-sum[x][pos];
			if (pre&&prelen<len){
				int thisnum=upper_bound(val[pre].begin(),val[pre].end(),len-prelen)-val[pre].begin()-1;
				ans-=(thisnum+1)*(len-prelen)-sum[pre][thisnum];//ÖØ¸´len
			}
		}printf("%I64d\n",ans);
	}
}
/*
*/

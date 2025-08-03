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
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
	int x,y,len;
	node(int _x,int _y,int _len):x(_x),y(_y),len(_len){}
	const operator < (const node &A) const{
		if (len!=A.len) return len>A.len;
		if (x!=A.x) return x<A.x;
		if (y!=A.y) return y<A.y;
	}
};
priority_queue<node> Q;
int n,m;
int nxt[maxn][2],cnt[maxn],pos[maxn];
int fa[maxn];
int tot;
int a[maxn],num[maxn][31][2];
int nxtnum[maxn][31][2];
inline int getfa(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
void ins(int x){
	int now=0,i,j,k;
	rREP(i,31){
		bool mark=(x>>i)&1;
		if (!nxt[now][mark]) nxt[now][mark]=++tot;
		now=nxt[now][mark];cnt[now]++;
		rep(j,0,i) nxtnum[now][j][(x>>j)&1]++;
		num[x][i][mark]++;
	}
//	nxtnum[now][0][x&1]++;
	if (!pos[now]) pos[now]=x;
	else{
		fa[x]=pos[now];
		REP(k,2) REP(i,31) num[pos[now]][i][k]+=num[x][i][k];
	}
}
int NXT[31][2];
int calc(int N,int x){
	int now=0,i,j,k;
	memcpy(NXT,num[N],sizeof(NXT));
	rREP(i,31){
		bool mark=(x>>i)&1;
//		if (i<5)
//		printf("%d %d-%d %d;nxt=%d,!nxt=%d,cnt=%d,%d %d\n",x,i,now,mark,nxt[now][mark],nxt[now][!mark],cnt[nxt[now][mark]],cnt[nxt[now][!mark]],NXT[i][mark]);
		if (cnt[nxt[now][mark]]!=NXT[i][mark]) now=nxt[now][mark];
		else{
			REP(k,2) rep(j,0,i) NXT[j][k]-=nxtnum[nxt[now][mark]][j][k];
			now=nxt[now][!mark];
		}
	}
//	printf("now=%d\n",now);
	return pos[now];
}
int CNT[maxn],NUM;
LL ans;
int main(){
	int i,k;
	scanf("%d",&n);
	FOR(i,1,n) fa[i]=i;
	FOR(i,1,n){
		scanf("%d",&a[i]);
		ins(a[i]);
	}FOR(i,1,n) if (fa[i]==i){
		int j=calc(i,a[i]);CNT[i]++;CNT[j]++;
		Q.push(node(i,j,a[i]^a[j]));
	}NUM=n-1;
	while (Q.size()&&NUM){
		auto now=Q.top();Q.pop();
		int x=getfa(now.x),y=getfa(now.y);
//		printf("now=%d %d %d;x,y=%d %d;num=%d\n",now.x,now.y,now.len,x,y,NUM);
		if (x!=y){
			fa[x]=y;NUM--;
			ans+=now.len;
			REP(k,2) REP(i,31) num[y][i][k]+=num[x][i][k];
		}
		CNT[now.x]--;CNT[now.y]--;
//		printf("CNT=%d %d\n",CNT[now.x],CNT[now.y]);
		if (!CNT[now.x]){
			i=now.x;
			int j=calc(y,a[i]);CNT[i]++;CNT[j]++;
//			printf("add:%d %d\n",i,j);
			Q.push(node(i,j,a[i]^a[j]));
		}if (!CNT[now.y]){
			i=now.y;
			int j=calc(y,a[i]);CNT[i]++;CNT[j]++;
//			printf("add:%d %d\n",i,j);
			Q.push(node(i,j,a[i]^a[j]));
		}
//		rREP(i,5) printf("%d-%d ",num[y][i][0],num[y][i][1]);puts("");
//		system("pause");
	}
	printf("%d\n",ans);
}
/*
4
1 2 3 4
5
1 2 3 4 5
*/

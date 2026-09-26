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
const LL M=998244353;
const LL maxn=1e5+7;
const double eps=0.000000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

#define MP make_pair
typedef pair<int,int> pii;

map<pii,int> ptoi;
map<int,pii> itop;
set<pii> del;
vector<int> edge[maxn];
int addx[]={-1,1,0,0};
int addy[]={0,0,-1,1};
int match[maxn];
int check[maxn],pre[maxn];
int cnt;
int a,b,m,i,j;
queue<int> Q;
int BFS(){
	int ans=0,i;
	memset(match,0,sizeof(match));
	memset(check,0,sizeof(check));
	FOR(i,1,cnt){
		if (match[i]==0){
			while (!Q.empty()) Q.pop();
			Q.push(i);
			pre[i]=0;
			bool flag=false;
			while (!Q.empty()&&!flag){
				int u=Q.front();Q.pop();
				for (j=0;!flag&&j<edge[u].size();j++){
					int v=edge[u][j];
					if (check[v]!=i){
						check[v]=i;
						Q.push(match[v]);
						if (match[v]!=0) pre[match[v]]=u;
						else{
							flag=1;
							int d=u,e=v;
							while (d!=0){
								int t=match[d];
								match[d]=e;
								match[e]=d;
								d=pre[d];
								e=t;
							}
						}
					}
				}
			}
			if (match[i]!=0) ans++;
		}
	}
	return ans;
}
vector<pii> ANS;
bool used[maxn];
void paint(int x,int y){
	used[x]=1;
	if (y){
		for (int v:edge[x])
			if (match[x]!=v&&!used[v]) paint(v,y^1);
	}else if (match[x]&&!used[match[x]]) paint(match[x],y^1);
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&a,&b);
		scanf("%d",&m);
		FOR(i,-a,a){
			FOR(j,-b,b) if (i*i*b*b+j*j*a*a<=a*a*b*b){
				++cnt;
				ptoi[MP(i,j)]=cnt;
				itop[cnt]=MP(i,j);
//				printf("have:%d %d,%d\n",i,j,cnt);
			}
		}while (m--){
			int x1,x2,y1,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			del.insert(MP(ptoi[MP(x1,y1)],ptoi[MP(x2,y2)]));
			del.insert(MP(ptoi[MP(x2,y2)],ptoi[MP(x1,y1)]));
		}FOR(i,1,cnt){
			pii now=itop[i];
			REP(j,4){
				pii nxt=MP(now.first+addx[j],now.second+addy[j]);
				if (ptoi.count(nxt)){
					pii to=MP(i,ptoi[nxt]);
					if (!del.count(to))
						edge[to.first].push_back(to.second);
//					printf("add %d - %d\n",i,ptoi[nxt]);
				}
			}
		}int ans=0;
		FOR(i,1,cnt) match[i]=0;
		ans=BFS();
		FOR(i,1,cnt) used[i]=0;
		ANS.clear();
		FOR(i,1,cnt){
			auto now=itop[i];
			if ((now.first+now.second)&1)
				if (!match[i]) paint(i,1);
		}
		FOR(i,1,cnt){
			auto now=itop[i];
			if (((now.first+now.second)&1)!=used[i])
				ANS.push_back(now);
		}
//		puts("NO.");
		printf("%d\n",ans);
		assert(ans==ANS.size());
		for(pii now:ANS) printf("%d %d\n",now.first,now.second);
//		printf("%d %d\n",CNT1,CNT2);
//		printf("%d %d\n",cnt,ans);
		FOR(i,1,cnt) edge[i].clear();
		cnt=0;del.clear();
		ptoi.clear();itop.clear();
	} 
}
/*
*/

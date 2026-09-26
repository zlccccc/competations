#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <utility>
#include <unordered_map>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=1e6+9;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const double eps=0.000000001;
const double pi=acos(-1);
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b){return a>0?a:-a;}


struct node{
	LL x,y;
}a[maxn];
bool cmp(node a,node b){
	if (a.x==b.x) return a.y<b.y;
	return a.x<b.x;
};
vector<LL> Hx,Hy;
vector<LL> H[maxn];
LL mark[maxn];
unordered_map<LL,LL> MP;
inline void add(LL x,LL y){
	if (x>y) swap(x,y);
	MP[x*100000+y]++;
}
inline LL get(LL x,LL y){
	if (x>y) swap(x,y);
	return MP[x*100000+y];
}
const LL CUT=300;
void solve(){
	LL i,j,k,n;
	scanf("%lld",&n);
	Hx.clear();Hy.clear();
	REP(i,n) scanf("%lld%lld",&a[i].x,&a[i].y),Hx.push_back(a[i].x),Hy.push_back(a[i].y);
	sort(Hx.begin(),Hx.end());Hx.erase(unique(Hx.begin(),Hx.end()),Hx.end());
	sort(Hy.begin(),Hy.end());Hy.erase(unique(Hy.begin(),Hy.end()),Hy.end());
	REP(i,n) a[i].x=lower_bound(Hx.begin(),Hx.end(),a[i].x)-Hx.begin();
	REP(i,n) a[i].y=lower_bound(Hy.begin(),Hy.end(),a[i].y)-Hy.begin();
	REP(i,Hx.size()) H[i].clear();
	REP(i,n) H[a[i].x].push_back(a[i].y);
	LL ans=0;
	MP.clear();
	REP(i,Hx.size()){
		if (H[i].size()<CUT){
			REP(j,H[i].size())
				rep(k,j+1,H[i].size()){
//					printf("%d %d  %d\n",H[i][j],H[i][k],get(H[i][j],H[i][k]));
					ans+=get(H[i][j],H[i][k]);
					add(H[i][j],H[i][k]);
				}
		}
	}
//	printf("-->%d<--",ans);
	memset(mark,0,sizeof(mark));
	MP.clear();
	REP(i,Hx.size()){
		if (H[i].size()>=CUT){
			REP(j,H[i].size()) mark[H[i][j]]++;
			REP(j,n) if (a[j].x!=i&&mark[a[j].y]){
//				printf("i=%d   x=%d y=%d   \n",i,a[j].x,a[j].y);
				if (H[a[j].x].size()<CUT||i<a[j].x) add(i,a[j].x);
			}
			REP(j,H[i].size()) mark[H[i][j]]--;
		}
	}
	REP(i,Hx.size()){
		if (H[i].size()>=CUT){
			REP(j,Hx.size())
				if (j!=i&&H[j].size()>=CUT){
					LL t=get(i,j);
					if (j>i) ans+=t*(t-1)/2;
				}else{
					LL t=get(i,j);
					ans+=t*(t-1)/2;
				}
		}
	}
	printf("%lld\n",ans);
}
int T;
int main(){
	scanf("%d",&T);
	while (T--) solve();
}
/*
*/

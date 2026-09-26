#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <unordered_map>
#include <stack>
#include <queue>
#include <cmath>
#include <bitset>
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
const LL maxn=1000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,i,j;
bitset<1007> ALL,NOW;
unordered_map<bitset<1007>,int> MP;
int now,all;
char c;
int fa[maxn];
vector<pair<int,int> > ans;
inline int getfa(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
int main(){
	scanf("%d",&n);getchar();
	FOR(i,1,n){
//		now=0;
		while (c=getchar()){
			if (c==':'){
				all=now;now=0;
				NOW.reset();
			}else if (c=='-'||c==','||c=='\n'){
//				printf("all=%d,now=%d\n",all,now);
				all--;
				if (NOW[now]) return 0*puts("-1");
				NOW.set(now);
				if (!all){
					if (MP.count(NOW)) return 0*puts("-1");
					MP[NOW]=i;
					NOW.reset();
				}now=0;
			}else now=now*10+c-'0';
			if (c=='\n') break;
		}
	}
//	puts("OK1");
	if (MP.size()!=(n-1)*2) return 0*puts("-1");
//	puts("OK2");
	FOR(i,1,n) fa[i]=i;
	FOR(i,1,n) ALL.set(i);
	for (pair<bitset<1007>,int> now:MP){
		NOW=now.first;
//		FOR(i,1,n) if(NOW[i]) putchar('1');
//		else putchar('0');printf(" %d\n",now.second);
		if (!MP.count(ALL^NOW)) return 0*puts("-1");
		int u,v;
		u=now.second;v=MP[ALL^NOW];
		if (u>v) continue;
		int x=getfa(u),y=getfa(v);
		if (x==y) return 0*puts("-1");
		fa[x]=y;
		ans.push_back(make_pair(u,v));
	}
//	puts("OK3");
	printf("%d\n",ans.size());
	for (pair<int,int> now:ans) printf("%d %d\n",now.first,now.second);
}
/*
*/

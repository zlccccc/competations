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

int n,m,i; 
int a[maxn],t[maxn];
int ans;
priority_queue<pair<int,int> > in,nin;
bool used[maxn];
int aid[maxn],now;//sort by value
int pid[maxn];
int nowt,cnt;
bool cmpa(int x,int y){
	return a[x]<a[y];
}vector<int> ANS;
int main(){
	int n,T;
	scanf("%d%d",&n,&T);
	FOR(i,1,n){
		scanf("%d%d",&a[i],&t[i]);
		aid[i]=i;
	}sort(aid+1,aid+1+n,cmpa);
	rFOR(i,1,n){
		nin.push(make_pair(-t[aid[i]],aid[i]));
		if (in.size()>a[aid[i]]) break;
		while (nin.size()){
			auto now=nin.top();
			now.first=-now.first;
			if (in.size()<a[aid[i]]&&nowt+now.first<=T){
				nin.pop();
				nowt+=now.first;
				in.push(now);
			}else if (in.size()&&now<in.top()){
				auto deled=in.top();
				in.pop();
				nin.pop();
				nowt+=now.first;
				nowt-=deled.first;
				deled.first=-deled.first;
				in.push(now);
				nin.push(deled);
			}else break;
		}
//		printf("%d %d %d\n",aid[i],nowt,T);
	}int ans=0;
	while (in.size()){
		ANS.push_back(in.top().second);
		in.pop();
	}
	for (int v:ANS) if (ANS.size()<=a[v]) ans++;
	printf("%d\n",ans);
	printf("%d\n",ANS.size());
	for (int v:ANS) printf("%d ",v);
}
/*
*/

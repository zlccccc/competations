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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

const int MID=1e5;
const int MAX=2e5+7;
struct node{
	int t,i;
}now;
vector<node> ver[maxn],hor[maxn];
queue<int> Q[MAX];//¥”œ¬Õ˘…œ…® 
queue<int> S[MAX];//startpos
int ansx[maxn],ansy[maxn];
int n,m,all,w,h;
int i;
int k;
int pos;
int main(){
	scanf("%d%d%d",&n,&w,&h);
	REP(i,n){
		scanf("%d%d%d",&k,&pos,&now.t);now.i=i;
		if (k==1){//∫· 
			ver[pos].push_back(now);
		}else if (k==2){
			hor[pos].push_back(now);
		}
	}
	rFOR(pos,1,w){
		for (node now:ver[pos]){
			Q[MID+pos-now.t].push(now.i);
			S[MID+pos-now.t].push(pos);
//			printf("shsh=%d i=%d pos=%d\n",MID+pos-now.t,now.i,pos);
		}
	}
	FOR(pos,1,h){
		for (node now:hor[pos]){
			Q[MID+pos-now.t].push(now.i);
			int t=Q[MID+pos-now.t].front();Q[MID+pos-now.t].pop();
//			printf("check=%d swap t=%d %d\n",MID+pos-now.t,t,now.i);
			ansx[t]=w;ansy[t]=pos;
		}
	}
	FOR(i,0,MID*2){
		while (Q[i].size()){
			int t=Q[i].front();Q[i].pop();
			pos=S[i].front();S[i].pop();
			ansx[t]=pos;ansy[t]=h;
		}
	}
	REP(i,n) printf("%d %d\n",ansx[i],ansy[i]);
}
/*
100000
*/

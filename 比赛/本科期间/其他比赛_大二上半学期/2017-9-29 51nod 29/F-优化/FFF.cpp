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
#include <bitset>
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
const LL M=1e9+7;//206158430209;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
/*
F0=(a+b+c+d)*(a+b+c+d)
F1=(a-b+c-d)*(a-b+c-d)
F2=(a+d)*(a+d)
F3=(a-d)*(a-d)
F4=b*b
F5=c*c
*/
int tot; 
LL F[maxn];
vector<LL> ans[maxn];
int solve(vector<int> &X,int POS){
	vector<LL> &ret=ans[POS];
	if (X.size()==1) {ret.push_back(X[0]*X[0]);return POS;}
	vector<int> F[6];
	int pos=0,t,i,j,k;
	REP(i,6) F[i].resize(X.size()>>2,0);
	REP(i,X.size()>>2){t=X[pos+i];F[0][i]+=t;F[1][i]+=t;F[2][i]+=t;F[3][i]+=t;}//0
	pos+=X.size()>>2;
	REP(i,X.size()>>2){t=X[pos+i];F[0][i]+=t;F[1][i]-=t;F[4][i]+=t;}//1
	pos+=X.size()>>2;
	REP(i,X.size()>>2){t=X[pos+i];F[0][i]+=t;F[1][i]+=t;F[5][i]+=t;}//2
	pos+=X.size()>>2;
	REP(i,X.size()>>2){t=X[pos+i];F[0][i]+=t;F[1][i]-=t;F[2][i]+=t;F[3][i]-=t;}//3
	vector<LL> &T0=ans[solve(F[0],tot++)];
	vector<LL> &T1=ans[solve(F[1],tot++)];
	vector<LL> &T2=ans[solve(F[2],tot++)];
	vector<LL> &T3=ans[solve(F[3],tot++)];
	vector<LL> &T4=ans[solve(F[4],tot++)];
	vector<LL> &T5=ans[solve(F[5],tot++)];
	int MAXSIZE=0;
	LL H0,H1,H2,H3;
	ret.resize(T0.size()+3,0);//sizeµÈ 
	REP(i,T0.size()){
		H0=(T2[i]+T3[i])/2+T4[i]+T5[i];
		H1=(T0[i]-T1[i]-T2[i]+T3[i])/2;
		H2=(T0[i]+T1[i])/2-H0;
		H3=(T2[i]-T3[i])/2;
//		printf("H(%d):%d,%d,%d,%d\n",i,H0,H1,H2,H3);
		ret[i]+=H0;ret[i+1]+=H1;ret[i+2]+=H2;ret[i+3]+=H3;
	}
//	printf("X(%d)->ret(%d)\n",X.size(),ret.size());
//	printf("X:   ");REP(i,X.size()) printf("%d ",X[i]);puts("");
//	REP(k,6){printf("K:%d  ",k);
//		REP(i,T[k].size()) printf("%d ",T[k][i]);puts("");
//	}
//	printf("ret: ");REP(i,ret.size()) printf("%d ",ret[i]);puts("");puts("");
	return POS;
}
vector<int> X;
int main(){
	int n,m;
	int i,j,k;
	scanf("%d%d",&n,&m);
	X.resize(1<<16);
	REP(i,n){
		int now=0;
		REP(j,m) scanf("%d",&k),now=now<<2|k;
		X[now]++;
	}
	tot=1;
	solve(X,0);
//	REP(i,ans.size()) printf("%lld ",ans[i]);puts("");
	FOR(i,0,m*3) printf("%lld ",ans[0][i]);
}
/*
*/

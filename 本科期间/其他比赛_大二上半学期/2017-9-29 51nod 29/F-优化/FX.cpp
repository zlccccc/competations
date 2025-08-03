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
//int tot1,tot2,tot3;
vector<LL> solve(vector<int> &X){
	vector<LL> ret;
	if (X.size()==1) {ret.push_back(1ll*X[0]*X[0]);return ret;}
	vector<int> F[6];
	int t=X.size()>>2;
	int pos0=0,pos1=t,pos2=t*2,pos3=t*3,i,j,k;
	REP(i,6) F[i].resize(X.size()>>2,0);
	REP(i,X.size()>>2){
		F[0][i]=X[pos0]+X[pos1]+X[pos2]+X[pos3];
		F[1][i]=X[pos0]-X[pos1]+X[pos2]-X[pos3];
		F[2][i]=X[pos0]+X[pos3];
		F[3][i]=X[pos0]-X[pos3];
		F[4][i]=X[pos1];
		F[5][i]=X[pos2];
		pos0++;pos1++;pos2++;pos3++;
//		tot1+=10;
	}
	vector<LL> T[6],G;
	int MAXSIZE=0;
	REP(i,6) T[i]=solve(F[i]);
	LL H0,H1,H2,H3;
//	REP(k,6){
//		G.swap(T[k]);T[k].resize(MAXSIZE,0);
//		REP(i,G.size()) REP(j,G.size()) T[k][i+j]+=G[i]*G[j];
//	}
	ret.resize(T[0].size()+3,0);//sizeµÈ 
	REP(i,T[0].size()){
		H0=(T[2][i]+T[3][i])/2+T[4][i]+T[5][i];
		H1=(T[0][i]-T[1][i]-T[2][i]+T[3][i])/2;
		H2=(T[0][i]+T[1][i])/2-H0;
		H3=(T[2][i]-T[3][i])/2;
//		tot3+=4;
//		printf("H(%d):%d,%d,%d,%d\n",i,H0,H1,H2,H3);
		ret[i]+=H0;ret[i+1]+=H1;ret[i+2]+=H2;ret[i+3]+=H3;
	}
//	printf("X(%d)->ret(%d)\n",X.size(),ret.size());
//	printf("X:   ");REP(i,X.size()) printf("%d ",X[i]);puts("");
//	REP(k,6){printf("K:%d  ",k);
//		REP(i,T[k].size()) printf("%d ",T[k][i]);puts("");
//	}
//	printf("ret: ");REP(i,ret.size()) printf("%d ",ret[i]);puts("");puts("");
	return ret;
}
vector<int> X;
vector<LL> ans;
int main(){
	int n,m;
	int i,j,k;
	scanf("%d%d",&n,&m);
	X.resize(1<<18);
	REP(i,n){
		int now=0;
		REP(j,m) scanf("%d",&k),now=now<<2|k;
		X[now]++;
	}
	ans=solve(X);
//	printf("%d %d %d\n",tot1,tot2,tot3);
//	REP(i,ans.size()) printf("%lld ",ans[i]);puts("");
	FOR(i,0,m*3) printf("%lld ",ans[i]);
}
/*
*/

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
const LL M=1e9+7;
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int X[maxn];
int ans[28];
int cnt[maxn];
//int add[4][4]={ {0,1,2,3},
//				{1,0,1,2},
//				{2,1,0,1},
//				{3,2,1,0}};
//int add[5][5]={ {0,1,2,3},
//				{1,0,3,2},
//				{2,3,0,1},
//				{3,2,1,0}};
int add[5][5]={ {0,0,0,0},//and
				{0,1,0,1},
				{0,0,2,2},
				{0,1,2,3}};
int a[1007][5],b[1007][5],c[1007][5];
int aa[1007],bb[1007],cc[1007];
bool mark[16];
int F[5][5];
bool check(int x){
	int i,j,ii;
	REP(i,81) mark[i]=0;
	int xx=x;
	REP(i,4){
		j=xx%16;xx/=16;
		if (mark[j]||mark[15-j]) return 0;
		mark[j]=1;
	}
	REP(i,4)
		REP(j,4) F[i][j]=x%2,x/=2;
	REP(ii,256){
		REP(i,4) aa[i]=bb[i]=cc[i]=0;
		REP(i,4)REP(j,4) aa[i]+=a[ii][j]*F[i][j];
		REP(i,4)REP(j,4) bb[i]+=b[ii][j]*F[i][j];
		REP(i,4)REP(j,4) cc[i]+=c[ii][j]*F[i][j];
		REP(i,4)if (aa[i]*bb[i]!=cc[i]) return 0;
	}
	return 1;
}
int main(){
	int i,j,ii,jj;
//		REP(ii,4)REP(jj,4) printf("%d,%d:%d\n",ii,jj,add[ii][jj]);
	REP(i,16)REP(j,16){
		REP(ii,4) if ((i>>ii)&1) a[i*16+j][ii]++;
		REP(ii,4) if ((j>>ii)&1) b[i*16+j][ii]++;
		REP(ii,4)REP(jj,4) c[i*16+j][add[ii][jj]]+=a[i*16+j][ii]*b[i*16+j][jj];
	}
//	REP(i,256){
//		REP(j,4) printf("%d",a[i][j]);printf("   ");
//		REP(j,4) printf("%d",b[i][j]);printf("   ");
//		REP(j,4) printf("%d",c[i][j]);printf("\n");
//	}
	int T=powMM(2,16);
	REP(i,T){
		if (i%100000==0) printf("%d\n",i);
		if (check(i)){
			printf("%x\n",i);
			REP(ii,4){
				REP(jj,4) printf("%d",F[ii][jj]);
				puts("");
			}puts("");
		}
	}
}
/*
*/

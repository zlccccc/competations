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
const double eps=0.000000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

map<string,int> MP[2];
int ans;
int now[100];
string s;
int val;
int QBH,PPY,NZXM,PPG,WJJ,ZZZ,RYAN,HCC;
int main(){
	int i,j,n;
	scanf("%d",&n);
	FOR(i,1,n){
		cin>>s>>val;
		MP[(val%2+2)%2][s]++;
	}
	REP(QBH,2){now[0]=MP[QBH]["QBH"];
	REP(PPY,2){now[1]=MP[PPY]["PPY"]*now[0];
	REP(NZXM,2){now[2]=MP[NZXM]["NZXM"]*now[1];
	REP(PPG,2){now[3]=MP[PPG]["PPG"]*now[2];
	REP(WJJ,2){now[4]=MP[WJJ]["WJJ"]*now[3];
	REP(ZZZ,2){now[5]=MP[ZZZ]["ZZZ"]*now[4];
	REP(RYAN,2){now[6]=MP[RYAN]["RYAN"]*now[5];
	REP(HCC,2){now[7]=MP[HCC]["HCC"]*now[6];
		if ((QBH+ZZZ)*(WJJ+NZXM+PPY)*(ZZZ+HCC)*(RYAN+PPG)%2==0) ans+=now[7];
	}}}}}}}}
	printf("%d\n",ans);
}
/*
*/

#include <sstream>
#include <fstream>
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
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e4+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

pii f[507][3][2][2];//pos,more
pii calc(int x,int more,int flag1,int flag2){
	if (x==0&&more!=2) return make_pair(1,0);
	else if (x==0) return make_pair(0,0);
	if (f[x][more][flag1][flag2].first!=-1)
		return f[x][more][flag1][flag2];
	pii ret; ret.first=ret.second=0;
	int maxi,i,j,maxj;
	if (flag1) maxi=str[x]-'0'; else maxi=1;
	if (flag2) maxj=str[x]-'0'; else maxj=1;//no limit
	FOR(i,0,maxi) FOR(j,0,maxj){//i:first; j:second
		if (more==1&&j>i) continue;//must A>B
		if (more==2&&i>j) continue;//must A<B,严格大于
		if (i!=j&&more){
			if (more==1){
				pii val=calc(x-1,2,flag1&&(i==maxi),flag2&&(j==maxj));//first_choice
				add_(ret.first,val.first); add_(ret.second,val.second);
				add_(ret.second,(ll)val.first*x%M);
				// printf(" first : %d=%d\n",val.first,val.second);
				val=calc(x-1,1,flag1&&(i==maxi),flag2&&(j==maxj));//first_choice
				add_(ret.first,val.first); add_(ret.second,val.second);
				add_(ret.second,val.first);//this
			} else if (more==2){
				pii val=calc(x-1,0,flag1&&(i==maxi),flag2&&(j==maxj));
				add_(ret.first,val.first); add_(ret.second,val.second);
				add_(ret.second,M-val.first);//this
			}
		} else {
			pii val=calc(x-1,more,flag1&&(i==maxi),flag2&&(j==maxj));
			add_(ret.first,val.first); add_(ret.second,val.second);
			add_(ret.second,(M+(i-j)*val.first)%M);//this
		}
		// printf("  calc (%d %d (%d %d)):  lr= %d %d   %d-%d\n",x,more,flag1,flag2,i,j,ret.first,ret.second);
	}
	// printf("%d %d (%d %d): %d-%d\n",x,more,flag1,flag2,ret.first,ret.second);
	return f[x][more][flag1][flag2]=ret;
}
int main() {
	int T,_; scanf("%d",&T);
	FOR(_,1,T){
		int i,len,j,k,l;
		scanf("%s",str+1);
		len=strlen(str+1); reverse(str+1,str+len+1);
		REP(i,len+1) REP(j,3) REP(k,2) REP(l,2) f[i][j][k][l].first=-1;
		pii ret=calc(len,1,1,1);
		printf("%d\n",ret.second);
 	}
}
/*
*/

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
const LL maxn=1e6+7;
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
char str[maxn],S[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int id=0,idl=0,l=0;
int ID[17][1027];
void actual(int now) {
	id=id*2+now; idl++;
	if (ID[idl][id]) {
		S[l++]=ID[idl][id];
		// printf("add %c\n",ID[idl][id]);
		idl=id=0;
	}
	// printf("%d %d %d\n",now,idl,id);
}
int main() {
	int T,_t,i,j,k;
	scanf("%d",&T);
	FOR(_t,1,T) {
		scanf("%d%d",&n,&m);
		memset(ID,0,sizeof(ID));
		REP(i,m) {
			int t,id=0;
			scanf("%d%s",&t,str);
			int len=strlen(str);
			REP(j,len) id=id*2+(str[j]-'0');
			// printf("str %d %d : %d(%c)\n",len,id,t,t);
			ID[len][id]=t;
		} scanf("%s",str); int L=strlen(str);
		id=idl=0; l=0;
		int okay; okay=0;
		vector<int> v;
		REP(i,L) {
			int c=str[i];
			if ('A'<=c&&c<='Z') c-='A'-10;
			if ('a'<=c&&c<='z') c-='a'-10;
			else c-='0';
			rREP(k,4) {
				int now=(c>>k)&1; okay^=now;
				if ((int)v.size()==8) {
					if (okay) for (int x:v) actual(x);
					v.clear(); okay=0;
				} else v.push_back(now);
			}
		} S[n]=0; S[l]=0;
		puts(S);
	}
}
/*
*/

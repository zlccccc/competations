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
const LL M=998244353;
const LL maxn=1e5+107;
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
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int getid(string str){
	int ret=0;
	if (str[1]=='m') ret=str[0]-'0'+100;
	else if (str[1]=='s') ret=str[0]-'0'+200;
	else if (str[1]=='p') ret=str[0]-'0'+300;
	else if (str[1]=='z') ret=str[0]-'0'+1000+(str[0]-'0')*100;
	// cout<<str<<"   "<<ret<<"\n";
	return ret;
}
string getstr(int id){
	string ret;
	ret=to_string(id%100);
	if (id/100==1) ret+='m';
	else if (id/100==2) ret+='s';
	else if (id/100==3) ret+='p';
	else ret+='z';
	// cout<<id<<ret<<getid(ret)<<"\n";
	return ret;
}
int A[maxn],B[maxn];
vector<int> V;
void check(int x) {
	int number=0; A[x]++;
	for (int k:V) if (A[k]>=2){
		bool okay=1;
		for (int i:V) B[i]=A[i];
		B[k]-=2;
		for (int i:V) {
			if (B[i]) {
				B[i]%=3;
				int m=min(min(B[i],B[i+1]),B[i+2]);
				B[i]-=m; B[i+1]-=m; B[i+2]-=m;
			}
		}
		for (int i:V) if (B[i]) okay=0;
		number+=okay;
	}
	if (A[x]!=5&&number) cout<<getstr(x)<<"\n";
	A[x]--;
}//todo
string now;
int main() {
	int i;
	FOR(i,1,9) V.push_back(100+i);
	FOR(i,1,9) V.push_back(200+i);
	FOR(i,1,9) V.push_back(300+i);
	FOR(i,1,7) V.push_back(1000+101*i);
	for (int v:V) getstr(v);
	while (cin>>now) {
		REP(i,10000) A[i]=0; A[getid(now)]++;
		REP(i,12) cin>>now,A[getid(now)]++;
		for (int v:V) check(v); 
	}
}
/*
1s 2s 3s 4s 5s 6s 7s 8s 9s 1z 1z 3p 4p
1s 1s 1s 2s 3s 4s 5s 6s 7s 8s 9s 1s 9s
1s 1s 1s 2s 3s 4s 5s 6s 7s 8s 9s 1z 1z
*/
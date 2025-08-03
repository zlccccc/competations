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
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

string dp[47][2007];
vector<string> ans;
int pre[47][2007];
string get(string str,string Pre,int k){
	string now=str; int num=k; int i;
	if (k==0){
		if (Pre<=str) return str;
		return "";
	} REP(i,m) {
		if (str[i]!=Pre[i]) {
			num--; now[i]=Pre[i];
		} if (!num) break;
	} if (Pre<=now) return now;
	// if (now[i]!='9'){
	// 	now[i]++; return now;
	// }
	int pos=i;
	while (pos!=-1&&now[pos]=='9') pos--;
	if (pos==-1) return "";
	num=k; now=str;
	REP(i,pos) {
		if (str[i]!=Pre[i]) {
			num--; now[i]=Pre[i];
		}
	} if (now[i]!=Pre[i]+1) num--;
	now[i]=Pre[i]+1;
	if (!num) return now;
	rep(i,pos+1,m) {
		if (str[i]!='0') {
			num--; now[i]='0';
		} if (!num) break;
	} return now;
}
int main() {
	int i,j,k;
	scanf("%d%d",&n,&m);
	string A;
	REP(i,m) A+='0';
	dp[0][0]=A;
	REP(i,n) {
		string str;
		cin>>str;
		// cout<<i<<" :\n";
		REP(j,200) if (dp[i][j]!=""){
			// cout<<" "<<j<<" : "+dp[i][j]+"\n";
			REP(k,m+1) {//change_number
				string now=get(str,dp[i][j],k);
				if (now=="") continue;
				// cout<<"  "+dp[i][j]+" + "<<k<<" = "+now<<"\n";
				if (dp[i+1][j+k]==""||dp[i+1][j+k]>now)
					dp[i+1][j+k]=now,pre[i+1][j+k]=j;
			}
		}
		// puts("");
	}REP(j,200) if (dp[n][j]!="") break;
	// printf("j=%d\n",j);
	rFOR(i,1,n){
		ans.push_back(dp[i][j]);
		j=pre[i][j];
	}reverse(ans.begin(), ans.end());
	for (auto str:ans) cout<<str<<"\n";
}
/*
*/

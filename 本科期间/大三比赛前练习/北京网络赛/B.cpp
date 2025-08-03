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
template<typename T>inline void add_(T &A,ll B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b,ll MOD=M) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%MOD)
		if (b&1) ret=(LL)ret*a%MOD;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

string S[maxn];
bool check(string s,string t){
	int i=0;
	for (auto now:s) if (i<(int)t.length()&&t[i]==now) i++;
	if (i==(int)t.length()) return 1;
	return 0;
}
int main() {
	while (cin>>n) {
		int i;
		REP(i,n) cin>>S[i]; n--;
		int _n=1<<S[0].length(),sta=0;
		string ans;
		rep(sta,1,_n){
			string now;
			REP(i,(int)S[0].length()) if ((sta>>i)&1) now+=S[0][i];
			string str=now;
			REP(i,(int)now.length()){
				str=str.substr(1,str.length())+str[0];
				// cout<<str<<" "<<now<<"\n";
				if (str<now) now=str;
			}
			// pr2(sta,S[0].length()); cout<<now<<"\n";
			bool okay=1;
			FOR(i,1,n){
				bool nowokay=0;
				str=S[i]; int k;
				REP(k,(int)str.length()){
					str=str.substr(1,str.length())+str[0];
					nowokay|=check(str,now);
				} okay&=nowokay;
			}
			if (okay){
				if (ans.length()<now.length()||
					(ans.length()==now.length()&&ans>now)) ans=now; 
			}
		}if (ans.length()) cout<<ans<<"\n";
		else cout<<"0\n";
	}
}
/*
5
defabc
kedajceu
adbac
abcdef
abcdafc

8
defabcaa
kedajcea
defabcaa
defabcaa
defabcaa
defabcaa
defabcaa
*/

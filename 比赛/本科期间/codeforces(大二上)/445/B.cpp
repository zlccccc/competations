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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n;
int cnt[255];
string a;
set<string> all,now;//should(some)
int main(){
	int i;
	scanf("%d",&n);
	while(n--){
		cin>>a;
		FOR(i,'a','z') cnt[i]=0;
		for (char c:a) {cnt[c]++;if (cnt[c]>=2) return 0*puts("NO");}
		now.clear();
		for (auto s:all){//link a,s //now:maxlen=26;//all:26
			REP(i,s.size()) if (cnt[s[i]]) break;
			if (i==s.size()) now.insert(s);
			else if (s.find(a)!=string::npos){
				a=s;
			}else if (a.find(s)!=string::npos){
			}else if (i==0){
				auto pos=a.find(s[0]);
				if (pos==string::npos) return 0*puts("NO");
				auto t=s.find(a.substr(pos,a.size()-pos));
				if (t==string::npos) return 0*puts("NO");
				a=a.substr(0,pos)+s;
			}else{
				swap(a,s);
				auto pos=a.find(s[0]);
				if (pos==string::npos) return 0*puts("NO");
				auto t=s.find(a.substr(pos,a.size()-pos));
				if (t==string::npos) return 0*puts("NO");
				a=a.substr(0,pos)+s;
			}FOR(i,'a','z') cnt[i]=0;
			for (char c:a) {cnt[c]++;if (cnt[c]>=2) return 0*puts("NO");}
		}
		now.insert(a);
		all=now;
	}
	for (auto now:all) cout<<now;
}
/*
2
ac
cz
*/

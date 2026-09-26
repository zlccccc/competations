#include <cstdio>
#include <set>
#include <algorithm>
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
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline LL powMM(LL a,LL b){
    LL ret=1;
    while (b){
        if (b&1) ret=ret*a%M;
        a=a*a%M;
        b>>=1;
    }
    return ret;
}
namespace fastIO {
	#define BUF_SIZE 100000
	//fread -> read
	bool IOerror = 0;
	inline char nc() {
		static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
		if(p1 == pend) {
			p1 = buf;
			pend = buf + fread(buf, 1, BUF_SIZE, stdin);
			if(pend == p1) {
				IOerror = 1;
				return -1;
			}
		}
		return *p1++;
	}
	inline bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	inline void read(int &x) {
		char ch;
		while(blank(ch = nc()));
		if(IOerror)
			return;
		for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
	}
	#undef BUF_SIZE
};
using namespace fastIO;

struct node{
	int s,t;
}a[maxn];
bool cmp(node a,node b){
	if (a.t==b.t) return a.s<b.s;
	return a.t<b.t;
}
multiset<int> S;
multiset<int>::iterator it;
LL ans;
int all;
int n,m;
int i,j,k,now;
int main(){
	int T;
	scanf("%d",&T);
	while (T--){
		read(n);
		ans=0;all=n;
		REP(i,n) read(a[i].s),read(a[i].t),ans+=a[i].t-a[i].s;
		sort(a,a+n,cmp);
		S.clear();
		rREP(i,n){
			it=S.lower_bound(a[i].t);
			if (it!=S.end()){
				ans+=(*it)-a[i].t;
				all--;
//				printf("%d:%d\n",*it);
				S.erase(it);
			}
			S.insert(a[i].s);
		}
		printf("%lld %lld\n",all,ans);
	}
}
/*
*/


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
const LL maxn=1e6+107;
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

const int hash_times=1;
struct hash{
    int px[maxn*2],val[maxn*2],p; ll M;
    void setp(int P,int n,int Mod=1e9+7){
        int i;px[0]=1;p=P;M=Mod;
        FOR(i,1,n) px[i]=(LL)px[i-1]*p%M;
    }
    void set(char a[],int n){
        int i;val[0]=0;
        FOR(i,1,n) val[i]=((LL)val[i-1]*p+a[i-1])%M;
    }
    int get(int l,int r){
        l++;r++;
        int ret=val[r]-(LL)val[l-1]*px[r-l+1]%M;
        (ret<0)&&(ret+=M);return ret;
    }
}H[hash_times];
map<string,int> MP;
char pool[maxn*2];
int l[maxn];//left_position;length=i
char op[5],val[5];
int ans[maxn];
bool check(int i,int len) {
	bool not_okay=0; int k;
	REP(k,hash_times) {
		if (H[k].get(l[i],l[i]+len-1)!=H[k].get(l[i]+i-1-len+1,l[i]+i-1))
			not_okay=1;
	} return !not_okay;
}
int main(){
	int n,i;
	MP["do"]='a'; MP["re"]='b'; MP["mi"]='c'; MP["fa"]='d';
	MP["sol"]='e'; MP["la"]='f'; MP["si"]='g';
	scanf("%d",&n); l[0]=1e6+3;
	FOR(i,1,n) {
		scanf("%s%s",op,val);
		l[i]=l[i-1];
		if (op[0]=='a') pool[l[i]+i-1]=MP[string(val)];
		else pool[--l[i]]=MP[string(val)];
		// int j; printf("start from %d\n",l[i]);
		// FOR(j,l[i],l[i]+i-1) printf("%d",pool[j]); puts("");
	}
	srand(time(0));
	REP(i,hash_times) {
		H[i].setp(rand()%100+7,2e6+10,rand()%M+1);
		H[i].set(pool,2e6+10);
	}
	FOR(i,1,n) {
		ans[i]++;
		int l=i,r=n+1;
		while (l+1<r) {
			int mid=(l+r)/2;
			if (check(mid,mid-i)) l=mid;
			else r=mid;
		} ans[r]--;
		// printf("%d: %d-%d\n",i,i,l);
	}
	FOR(i,1,n) {
		ans[i]+=ans[i-1];
		printf("%d\n",ans[i]);
	}
}
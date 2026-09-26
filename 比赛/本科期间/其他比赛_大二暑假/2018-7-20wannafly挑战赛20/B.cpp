#include <bits/stdc++.h>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG1
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
inline void add(int &A,int B) {A+=B; (A>=M) &&(A-=M);}
inline void mul(ll &A,ll B) {(A*=B)%=M;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m;
char S[maxn];
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string() {while (~scanf("%s",S)) TaskA();}

pii A[maxn];
priority_queue<int> L;
priority_queue<pii> R;
int TaskA() {
	int i,j,k; ll v;
	scanf("%lld%d%d",&v,&n,&m);
	FOR(i,1,n) scanf("%d%d",&A[i].second,&A[i].first);//size, val
	sort(A+1,A+1+n);
	sort(A+1,A+1+m,[](pii A,pii B){
		if (A.second!=B.second) return A.second<B.second;
		return A.first>B.first;
	});
	int ans=0;ll all=0;
	if (!(m&1)){
		FOR(i,1,m) all+=A[i].first;
		FOR(i,1,m/2-1) L.push(A[i].first);
		FOR(i,m/2+1,m) R.push(make_pair(-A[i].second,A[i].first));
		pii val_1=A[m/2],val_2;
		val_2=R.top(); val_2.first=-val_2.first;
		swap(val_2.first,val_2.second);
		if (all<=v) ans=max(ans,(val_1.second+val_2.second)/2);
		FOR(i,m+1,n){
			if (A[i].second>ans){
				all+=A[i].first;
				L.push(val_1.first);
				all-=L.top(); L.pop();
				R.push(make_pair(-A[i].second,A[i].first));
				val_1=R.top(); val_1.first=-val_1.first;
				swap(val_1.first,val_1.second); R.pop();
			}
			if (all>v) break;
			val_2=R.top(); val_2.first=-val_2.first;
			swap(val_2.first,val_2.second);
			ans=max(ans,(val_1.second+val_2.second)/2);
		}
	}else{
		FOR(i,1,m) all+=A[i].first;
		FOR(i,1,m/2) L.push(A[i].first);
		FOR(i,m/2+2,m) R.push(make_pair(-A[i].second,A[i].first));
		pii val_1=A[m/2+1];
		if (all<=v) ans=max(ans,val_1.second);
		FOR(i,m+1,n){
			if (A[i].second>ans){
				all+=A[i].first;
				L.push(val_1.first);
				all-=L.top(); L.pop();
				R.push(make_pair(-A[i].second,A[i].first));
				val_1=R.top(); val_1.first=-val_1.first;
				swap(val_1.first,val_1.second); R.pop();
			}
			if (all>v) break;
			ans=max(ans,val_1.second);
		}
	} printf("%lld\n",ans);
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	TaskA();
}
/*

*/

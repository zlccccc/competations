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
#include <bitset>
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
const LL maxn=3e4+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int nxt[2000007][27];
int pos[2000007];
int st[maxn],len[maxn],ST[maxn][4],LEN[maxn][4],K[maxn];
char c[2000007],a[2000007];
bitset<30007> all[maxn];
bitset<30007> nowpos,strpos[maxn];
int tot,cnt;
void insert(char *s){//inspos
	int now=0,len=strlen(s),i;
	REP(i,len){
		if (!nxt[now][s[i]-'a']) nxt[now][s[i]-'a']=++cnt;
		now=nxt[now][s[i]-'a'];
	}if (!pos[now]) pos[now]=++tot;
}
void check(char *s,int x){
	int now=0,len=strlen(s),i;
	REP(i,len){
		if (!nxt[now][s[i]-'a']) return;
		now=nxt[now][s[i]-'a'];
		if (pos[now]) strpos[pos[now]].set(x);
	}
}
void checkans(char *s,int x){
	int now=0,len=strlen(s),i;
	REP(i,len) now=nxt[now][s[i]-'a'];
	all[x]=all[x]&strpos[pos[now]];
}
int nowst;
inline void read(int &st,int &len){
	st=nowst;
	scanf("%s",a+nowst);
	len=strlen(a+nowst);
	nowst+=len;
}
struct node{
	int k,len,i;
	node(int _k=0,int _len=0,int _i=0):k(_k),len(_len),i(_i){}
}A[maxn];
bool cmp(node a,node b){
	if (a.len!=b.len) return a.len>b.len;
	else return a.k<b.k;//1ÓÅÏÈ
}
void solve(){
	int Q;
	scanf("%d",&Q);
	nowst=0;
	int i,j;
	REP(i,Q){
		int k;
		scanf("%d",&k);K[i]=k;
		if (k==1){
			read(st[i],len[i]);
			A[i]=node(k,len[i]/2,i);
		}else if (k==2){
			read(ST[i][0],LEN[i][0]);
			read(ST[i][1],LEN[i][1]);
			read(ST[i][2],LEN[i][2]);
			read(ST[i][3],LEN[i][3]);
			A[i]=node(k,max(LEN[i][0]+LEN[i][1],LEN[i][2]+LEN[i][3]),i);
		}
	}
	sort(A,A+Q,cmp);
	nowpos.reset();
	REP(i,Q){
		if (A[i].k==1) nowpos.set(A[i].i);
		else all[A[i].i]=nowpos;
	}
	FOR(i,0,tot) strpos[i].reset();
	FOR(i,0,cnt) memset(nxt[i],0,sizeof(nxt[i])),pos[i]=0;
	cnt=tot=0;
	REP(i,Q) if (K[i]==2){
		REP(j,LEN[i][0]) c[j]=a[ST[i][0]+j];c[LEN[i][0]]=0;
		insert(c);
	}
	REP(i,Q){//·À±¬ 
		if (K[i]==1){
			REP(j,len[i]/2) c[j]=a[st[i]+j];c[len[i]/2]=0;
			check(c,i);
		}else{
			REP(j,LEN[i][0]) c[j]=a[ST[i][0]+j];c[LEN[i][0]]=0;
			checkans(c,i);
		}
	}
	FOR(i,0,tot) strpos[i].reset();
	FOR(i,0,cnt) memset(nxt[i],0,sizeof(nxt[i])),pos[i]=0;
	cnt=tot=0;
	REP(i,Q) if (K[i]==2){
		REP(j,LEN[i][1]) c[j]=a[ST[i][1]+LEN[i][1]-j-1];c[LEN[i][1]]=0;
		insert(c);
	}
	REP(i,Q){//·À±¬ 
		if (K[i]==1){
			REP(j,len[i]/2) c[j]=a[st[i]+len[i]/2-j-1];c[len[i]/2]=0;
			check(c,i);
		}else{
			REP(j,LEN[i][1]) c[j]=a[ST[i][1]+LEN[i][1]-j-1];c[LEN[i][1]]=0;
			checkans(c,i);
		}
	}
	FOR(i,0,tot) strpos[i].reset();
	FOR(i,0,cnt) memset(nxt[i],0,sizeof(nxt[i])),pos[i]=0;
	cnt=tot=0;
	REP(i,Q) if (K[i]==2){
		REP(j,LEN[i][2]) c[j]=a[ST[i][2]+j];c[LEN[i][2]]=0;
		insert(c);
	}
	REP(i,Q){//·À±¬ 
		if (K[i]==1){
			REP(j,len[i]/2) c[j]=a[st[i]+len[i]/2+j];c[len[i]/2]=0;
			check(c,i);
		}else{
			REP(j,LEN[i][2]) c[j]=a[ST[i][2]+j];c[LEN[i][2]]=0;
			checkans(c,i);
		}
	}
	FOR(i,0,tot) strpos[i].reset();
	FOR(i,0,cnt) memset(nxt[i],0,sizeof(nxt[i])),pos[i]=0;
	cnt=tot=0;
	REP(i,Q) if (K[i]==2){
		REP(j,LEN[i][3]) c[j]=a[ST[i][3]+LEN[i][3]-j-1];c[LEN[i][3]]=0;
		insert(c);
	}
	REP(i,Q){//·À±¬ 
		if (K[i]==1){
			REP(j,len[i]/2) c[j]=a[st[i]+len[i]-j-1];c[len[i]/2]=0;
			check(c,i);
		}else{
			REP(j,LEN[i][3]) c[j]=a[ST[i][3]+LEN[i][3]-j-1];c[LEN[i][3]]=0;
			checkans(c,i);
		}
	}
	REP(i,Q) if (K[i]==2) printf("%d\n",all[i].count());
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
1
10
1 abcqaq
1 abcabcqaqqaq
2 ab bc qa aq
2 a c q q
1 abcabcqaqqwq
2 ab bc qa aq
2 a c q q
1 abcq
2 a c q q
2 a b c q
*/

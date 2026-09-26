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
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=5e4+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
inline void add(int &A,int B){A+=B;(A>=M)&&(A-=M);}
inline void mul(ll &A,ll B){(A*=B)%=M;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m;
char S[maxn];

struct SAM{
	const static int maxn=4e6+7;
	int next[maxn][9],fail[maxn],len[maxn],cnt,last;
	void init(){
		cnt=0;fail[0]=-1;len[0]=0;last=0;
		memset(next[0],0,sizeof(next[0]));
	}
	void add(int c){
		int np=++cnt,p=last;
		memset(next[np],0,sizeof(next[np]));
		len[np]=len[p]+1;
		for (;p!=-1&&!next[p][c];p=fail[p]) next[p][c]=np;
		if (p==-1) fail[np]=0;
		else {
			int q=next[p][c];
			if (len[p]+1==len[q]) fail[np]=q;
			else{
				int nq=++cnt;len[nq]=len[p]+1;
				memcpy(next[nq],next[q],sizeof(next[q]));
				fail[nq]=fail[q];
				fail[np]=fail[q]=nq;
				for (;p!=-1&&next[p][c]==q;p=fail[p]) next[p][c]=nq;
			}
		} last=np;
	}
    int S[maxn],K[maxn];
    ll ans[maxn];
	ll solve(){
	    ll Ans=0; int i,j;
        FOR(i,1,cnt) S[i]=0;
        FOR(i,1,cnt) S[len[i]]++;
        FOR(i,1,cnt) S[i]+=S[i-1];
        FOR(i,1,cnt) K[S[len[i]]--]=i;
        FOR(i,1,cnt) ans[i]=0; ans[0]=1;
        FOR(i,0,cnt){
            int x=K[i]; Ans+=ans[x];
            REP(j,3) if (next[x][j]) ans[next[x][j]]+=ans[x];
        } return Ans;
	}
	char a[maxn]; int X=0;
    void dfs(int x=0,int len=0){
        int i;
        printf("%-4d :%s\n",++X,a);
        REP(i,3){
            if (next[x][i]){
                a[len]=i+'a';
                dfs(next[x][i],len+1);
                a[len]=0;
            }
        }
    }
}sam;
int mark[255];
int TaskA(){
    int i,j,k;
    scanf("%s",S);
    sam.init();
    mark['a']=0; mark['b']=1; mark['c']=2;
    REP(i,n) sam.add(mark[S[i]]); sam.add(3);
    mark['a']=0; mark['b']=2; mark['c']=1;
    REP(i,n) sam.add(mark[S[i]]); sam.add(4);
    mark['a']=1; mark['b']=0; mark['c']=2;
    REP(i,n) sam.add(mark[S[i]]); sam.add(5);
    mark['a']=1; mark['b']=2; mark['c']=0;
    REP(i,n) sam.add(mark[S[i]]); sam.add(6);
    mark['a']=2; mark['b']=0; mark['c']=1;
    REP(i,n) sam.add(mark[S[i]]); sam.add(7);
    mark['a']=2; mark['b']=1; mark['c']=0;
    REP(i,n) sam.add(mark[S[i]]); sam.add(8);
//    sam.dfs();
    ll ans=sam.solve(); ans--;
    ll len=1,maxlen=0;
    REP(i,n) if (S[i]==S[i+1]) len++;
    else maxlen=max(maxlen,len),len=1;
    ans+=3*maxlen;
//    printf("%lld\n",ans);
    printf("%lld\n",ans/6);
    return 0;
}
void initialize(){}
void Task_one(){TaskA();}
void Task_T(){int T;scanf("%d",&T);while (T--) TaskA();}
void Task_more_n(){while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m(){while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string(){while (~scanf("%s",S)) TaskA();}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_more_n();
}
/*
4
abaa
4
abab
*/

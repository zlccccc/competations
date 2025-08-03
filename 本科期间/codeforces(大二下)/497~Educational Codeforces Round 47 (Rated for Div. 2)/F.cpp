#include <bits/stdc++.h>
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
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
inline void add(int &A,int B){A+=B;(A>=M)&&(A-=M);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m;
char S[maxn];

#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
int ans[maxn];
vector<int> edge[maxn];
int pool[maxn],*st=pool,*have[maxn];
pair<int,int> Ans;
int son[maxn],dep[maxn],len[maxn];
void dfs_1(int x,int fa,int depth){
    dep[x]=depth; son[x]=0;
    for (int v:edge[x]) if (v!=fa){
        dfs_1(v,x,depth+1);
        if (len[v]>len[son[x]]) son[x]=v;
    }len[x]=len[son[x]]+1;
}
void dfs_2(int x,int fa,int top){
    if (top==x) have[x]=st,st+=len[x];
    for (int v:edge[x]) if (v!=fa&&v!=son[x]){
        dfs_2(v,x,v);
        Ans=make_pair(0,0);
    }if (son[x]) dfs_2(son[x],x,top);
    int length=dep[x]-dep[top];
    have[top][length]++;
    Ans=max(Ans,make_pair(have[top][length],-length));
    for (int v:edge[x]) if (v!=fa&&v!=son[x]){
        int i;
        REP(i,len[v]){
            int length=dep[v]+i-dep[top];
            have[top][length]+=have[v][i];
            Ans=max(Ans,make_pair(have[top][length],-length));
        }
    }ans[x]=-Ans.second+dep[top]-dep[x];
}
char write[7000000],*ed=write;
char buffer[36000000],*buf=buffer;
void read(int &x){
    for(x=0;(*buf<'0'||*buf>'9')&&*buf!='-';++buf);
    int flag=0;if (*buf=='-') flag=1,buf++;
    while('0'<=*buf&&*buf<='9')x=x*10+*buf-48,++buf;
    if (flag) x=-x;
}
int pp[20];
void print(LL x){
    if (!x) *ed++='0';
    else {
        int now=0,i;
        while (x) pp[now++]=x%10,x/=10;
        while (now) *ed++=pp[--now]+48;
    }*ed++='\n';
}
int TaskA(){
    fread(buffer,1,36000000,stdin);
    int i,j,k,q;
    read(n);
    FOR(i,1,n-1){
        int u,v;
        read(u); read(v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }dfs_1(1,0,0); dfs_2(1,0,1);
    FOR(i,1,n) print(ans[i]);
    fwrite(write,1,ed-write,stdout);
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
	TaskA();
}
/*

*/

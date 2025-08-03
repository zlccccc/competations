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
const int maxn=2e5+7;
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

struct PAM {
    int next[maxn][27];
    int fail[maxn];
    int len[maxn];//长度
    int diff[maxn];//length(this-fail)
    int anc[maxn];//diff不同的fail,共log个
    int S[maxn];//字符
    int last;//上一个字符节点
    int n,tot;//n表示字符位置
    int newnode(int l) {
        memset(next[tot],0,sizeof(next[tot]));
        len[tot]=l;//不是1...
        return tot++;
    }
    void init() {
        tot=0; last=n=0;
        newnode(0); newnode(-1);
        S[n]=-1; fail[0]=1;
    }
    int getfail(int x) {
        while (S[n-len[x]-1]!=S[n]) x=fail[x];
        return x;
    }
    int add(int c) {
        S[++n]=c;
        int cur=getfail(last);
        if (!next[cur][c]) {
            int now=newnode(len[cur]+2);
            fail[now]=next[getfail(fail[cur])][c];
            diff[now]=len[now]-len[fail[now]];
            if (diff[now]==diff[fail[now]])
                anc[now]=anc[fail[now]];
            else anc[now]=now;
            next[cur][c]=now;//这里一定要在fail后边=_=
        } return last=next[cur][c];
    }
    char a[maxn];
    void dfs(int p,int len=0) {
        int c;
        printf("%-20s (p=%-5d, length=%-5d fail=%-5d anc=%-5d diff=%-5d)",a,p,this->len[p],fail[p],anc[p],diff[p]);
        // if (p>=2) printf("%d len=%lld\n",);
        puts("");
        REP(c,26) if (next[p][c]) {
            a[len]=c+'a';
            dfs(next[p][c],len+1);
            a[len]=0;
        }
    }
} pam;
char str[maxn];
pii ans[maxn],sans[maxn];
pii T[maxn*4];//for global query
void update(int x,int pos,int L,int R) {
    if (L==R) {T[x]=ans[L-1]; T[x].second=L; return;}
    int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,L,mid);
    else update(x<<1|1,pos,mid+1,R);
    T[x]=max(T[x<<1],T[x<<1|1]);
}
pii query(int x,int l,int r,int L,int R) {
    // printf("query %d %d %d %d %d\n",x,l,r,L,R);
    if (l>r) return make_pair(-1,0);
    if (l<=L&&R<=r) return T[x];
    int mid=(L+R)/2; pii ret=make_pair(-1,0);
    if (l<=mid) ret=max(ret,query(x<<1,l,r,L,mid));
    if (mid<r) ret=max(ret,query(x<<1|1,l,r,mid+1,R));
    return ret;
}
int mark[maxn];
int main() {
    scanf("%s",str+1);
    int i,n=strlen(str+1);
    pam.init();
    // FOR(i,1,n) pam.add(str[i]-'a');
    // pam.dfs(0); pam.dfs(1);
    FOR(i,1,n) {//fin
        int k=pam.add(str[i]-'a');
        //i:=last
        update(1,i,1,n);
        ans[i]=query(1,1,i-pam.len[k],1,n);
        // printf("que %d: %d %d(maybe+1)\n",i,ans[i].first,ans[i].second);
        // printf("first query 1 - %d\n",i-pam.len[k]);
        for (int p=k; pam.len[p]>0; p=pam.fail[pam.anc[p]]) {
            int l=i-pam.len[pam.anc[p]]+1;
            int r=l+pam.diff[p]-1; l++;
            // if (l<=r) printf("update query l,r=%d - %d\n",l,r);
            sans[p]=query(1,l,r,1,n);
            if (pam.diff[p]==pam.diff[pam.fail[p]])
                sans[p]=max(sans[p],sans[pam.fail[p]]);
            ans[i]=max(ans[i],sans[p]);
        } if (ans[i].first!=-1) ans[i].first++;//value,position
        // printf("fin %d: %d %d\n",i,ans[i].first,ans[i].second);
    }
    printf("%d\n",ans[n].first);
    if (ans[n].first!=-1) {//redo it
        for (int v=n;v;v=ans[v].second-1) mark[v]=1;
        FOR(i,1,n) {
            printf("%c",str[i]);
            if (mark[i]) puts("");
        }
    }
}
/*
4 2
1 1 2
1 1 0 0
*/
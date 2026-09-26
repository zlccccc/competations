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
#include <cstdlib>
#include <iomanip>
#include <cassert>
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
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}


struct SAM{
    int next[maxn][26],fail[maxn],len[maxn];
    int cnt,last;
    void init(){
        cnt=last=0;fail[0]=-1;len[0]=0;
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
        }
        last=np;
    }
    int OK[maxn];
    int S[maxn],Q[maxn];
    int mex[150];
    int solve(){
        int i,j;
        FOR(i,1,cnt) OK[i]=0;
        FOR(i,0,cnt) S[i]=0;
        FOR(i,1,cnt) S[len[i]]++;
        FOR(i,1,cnt) S[i]+=S[i-1];
        FOR(i,1,cnt) Q[S[len[i]]--]=i;
        int t;
        rFOR(t,1,cnt) {
            i=Q[t];
            REP(j,30) mex[j]=0;
            REP(j,26) if (next[i][j]) {
                mex[OK[next[i][j]]]=1;
            }while (mex[OK[i]]) OK[i]++;
        }
    }
    int query(char a[]){
        int n=strlen(a),p=0,i;
        REP(i,n){
            assert(next[p][a[i]-'a']);
            p=next[p][a[i]-'a'];
        }
        return OK[p];
    }
    char a[maxn];
    void dfs(int x=0,int len=0){
        int i;
        printf("OK=%3d   ",OK[x]);
        printf("%-3d(fail:%-3d,len=%-2d):%s\n",x,fail[x],this->len[x],a);
        REP(i,26){
            if (next[x][i]){
                a[len]=i+'a';
                dfs(next[x][i],len+1);
                a[len]=0;
            }
        }
    }
}sam;
int T;
int n,m;
int i,j,k;
char a[maxn];
int cnt;
int main(){
    while (~scanf("%s",a)){
        sam.init();
        int n=strlen(a);
        REP(i,n) sam.add(a[i]-'a');
        sam.solve();
        cnt=0;
//        sam.dfs();
        scanf("%d",&n);
        REP(i,n){
            scanf("%s",a);
            int t=sam.query(a);
            cnt^=t;
        }//0:Bob win
        if (cnt) puts("Alice");
        else puts("Bob");
    }
}
/*
*/

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
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct linknode{
    struct node{
        int key,val;int next;
        node(){};
        node(int k,int v,int n):key(k),val(v),next(n){};
    }T[maxn];//更好地空间局部性?(雾)
    int head[maxn],size;
    void clear(){
        memset(head,-1,sizeof(head));
        size=0;
    }
    int get(int x,int y){
        for (int i=head[x];~i;i=T[i].next)
            if (T[i].key==y) return T[i].val;
        return 0;
    }
    void insert(int pos,int key,int val){
        T[size]=node(key,val,head[pos]);
        head[pos]=size++;
    }
};

struct Ptree{
    linknode next;
    int fail[maxn];
    int len[maxn],num[maxn];
    int S[maxn];
    int last;
    int n,tot;
    int newnode(int l){
        num[tot]=0;
        len[tot]=l;//不是1...
        return tot++;
    }
    void init(){
        next.clear();
        tot=0;last=n=0;
        newnode(0);newnode(-1);
        S[n]=-1;//减少特判
        fail[0]=1;
    }
    int getfail(int x){
        while(S[n-len[x]-1]!=S[n]) x=fail[x];
        return x;
    }
    LL add(int c){
        S[++n]=c;
        int cur=getfail(last);
        if (!next.get(cur,c)){
            int now=newnode(len[cur]+2);
            fail[now]=next.get(getfail(fail[cur]),c);
            num[now]=num[fail[now]]+1;
            next.insert(cur,c,now);
        }
        last=next.get(cur,c);
        return num[last];
    }
}T;
char a[maxn];
LL all[maxn],ans;
int main(){
    int i,j,n;
    scanf("%d%s",&n,a);
    T.init();
    REP(i,n) all[i+1]=(all[i]+T.add(a[i]))%M;
    T.init();
    rREP(i,n) (ans+=T.add(a[i])*all[i]%M)%=M;
    ans=(-ans+M)%M;
    (ans+=all[n]*(all[n]-1)/2%M)%=M;//MDZZ
//    FOR(i,1,n) printf("%d ",all[i]);puts("");
//    T.init();rREP(i,n) printf("%lld(%lld) ",T.add(a[i]),all[i]);puts("");puts("");
    printf("%lld\n",ans);
}
/*
*/

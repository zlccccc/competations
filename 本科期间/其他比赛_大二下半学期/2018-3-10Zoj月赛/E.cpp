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
const LL M=998244353;
const LL maxn=200000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int SIZE;
struct node{
    int u,v,id,o;
    node(){};
    node(int _u,int _v,int _id=0):u(_u),v(_v),id(_id){};
}to[maxn],re[maxn],queries[maxn];
int BID[maxn],L[maxn];
bool cmpu(node A,node B){
    if (A.u!=B.u) return A.u<B.u;
    if (A.v!=B.v) return A.v>B.v;//ÎªÁË±ÜÃâÂ©µô
    return A.id>B.id;
}bool cmpv(node A,node B){
    if (A.v!=B.v) return A.v<B.v;
    if (A.u!=B.u) return A.u<B.u;
    return A.id<B.id;
}bool cmpQ(node A,node B){
    if (A.o!=B.o) return A.o<B.o;
    if (A.v!=B.v) return A.v<B.v;
    if (A.u!=B.u) return A.u<B.u;
    return A.id<B.id;
}
int Ans[maxn];
int tot=0;
LL now;
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        int n,m,q,i,j,k;
        scanf("%d%d",&n,&q);m=n-1;
        if (q==0) SIZE=m;else SIZE=m/sqrt(q);
        if (!SIZE) SIZE++;
        FOR(i,0,(m+1)/SIZE) L[i]=0;
        FOR(i,1,m+1){BID[i]=i/SIZE;if (!L[i/SIZE]) L[i/SIZE]=i;}
        FOR(i,1,m){
            int u,v;
            scanf("%d%d",&u,&v);
            if (u>v) swap(u,v);
            to[i]=node(u,v);
            re[i]=node(u,v);
        }sort(to+1,to+m+1,cmpv);
        sort(re+1,re+m+1,cmpu);
        FOR(i,1,m){
            to[i].o=BID[lower_bound(re+1,re+1+m,to[i],cmpu)-re];
            re[i].o=BID[i];
        }
        FOR(i,1,q){
            int u,v;
            scanf("%d%d",&u,&v);
            if (u>v) swap(u,v);
            queries[i]=node(u,v,i);
            queries[i].o=BID[lower_bound(re+1,re+1+m,queries[i],cmpu)-re];
        }sort(queries+1,queries+q+1,cmpQ);
       FOR(i,1,q){
            if (i==1||queries[i].o!=queries[i-1].o){//initialize
                j=1;now=0;
            }
            for (;j<=m&&to[j].v<=queries[i].v;j++){
                if (to[j].o>queries[i].o) {//sorted by l
                    now++;
                }
            }
            int ans=now;tot++;
            for (k=L[queries[i].o];BID[k]==queries[i].o;k++){
                if (queries[i].u<=re[k].u&&re[k].v<=queries[i].v){
                    ans++;
                }
            }
            Ans[queries[i].id]=-ans+queries[i].v-queries[i].u+1;
        }
        FOR(i,1,q) printf("%d\n",Ans[i]);
    }
}
/*
*/

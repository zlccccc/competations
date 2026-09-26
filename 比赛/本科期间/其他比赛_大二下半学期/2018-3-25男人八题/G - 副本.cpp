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

//限制和没有一样的=_=
//pre_max; could
int T;
int n,m;
int i,j,k;
int fa[maxn];
int len[maxn],son[maxn],top[maxn];
int A[maxn],B[maxn],dep[maxn];//B:sum of A
vector<int> downmax[maxn];//1:query; 2:update
vector<int> downmin[maxn];//1:query; 2:update
vector<int> edge[maxn];
int Q[maxn],R[maxn];
int ans;
int main(){
    while (~scanf("%d",&n)){
        //1:topo_sort
        FOR(i,1,n) edge[i].clear();//init_1
        FOR(i,1,n){
            scanf("%d%d",&fa[i],&A[i]);
            edge[fa[i]].push_back(i);
            if (!fa[i]) Q[1]=i;
        }m=0;
        FOR(i,1,n) for (int v:edge[i]) Q[++m]=v;
        assert(n==m);
        //2:remark
        FOR(k,2,n){
            i=Q[k];
            len[i]=1;
            dep[i]=dep[fa[i]]+1;
        }
        rFOR(k,1,n) {
            i=Q[k];
            if (len[fa[i]]<len[i]+1){
                son[fa[i]]=i;
                len[fa[i]]=len[i]+1;
            }
        }
        FOR(k,1,n) {
            i=Q[k];
            if (top[i]==i){
                downmax[i].resize(len[i]*2+1,-1);
                downmin[i].resize(len[i]*2+1,-1);
            }else{
                downmax[i].clear();
                downmin[i].clear();
            }
            B[i]=B[fa[i]]+A[i];
            if (son[i]) top[son[i]]=top[i];
        }m=0;
        FOR(k,1,n){
            i=Q[k];
            for (int v:edge[i]) if (v!=son[i]) R[++m]=v;
            if (son[i]) R[++m]=son[i];
        }
        //DP//top_max->top_min
        ans=0;
        rFOR(k,1,n){
            i=R[k];
            if (top[i]==i){
                ans=max(ans,downmax[i][len[i]]);
                ans=max(ans,downmin[i][len[i]]);
                REP(i,len[i]*2+1){
                    if (~downmax[i][i]) continue;

                }
            }else{
                int f=top[i];
                int id=B[i]-B[top]+A[top]+len[top[i]]
                if (A[i]==-1){
                    if (~downmax[f][id]) downmax[f][id]=id;
                    else downmax[f][id]=downmax[f][id+1];
                    if (~downmin[f][id]) downmin[f][id]=id;
                }else {
                    if (~downmin[f][id]) downmin[f][id]=id;
                    else downmin[f][id]=downmin[f][id-1];
                    if (~downmax[f][id]) downmax[f][id]=id;
                }id-=A[i];//query_id
                ans=max(ans,downmax[f][id]-id);
            }
        }
        printf("%d\n",ans);
    }
}
/*
*/

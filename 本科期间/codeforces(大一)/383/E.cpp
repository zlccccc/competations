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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a; }
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

int ST[maxn][20],VAL[maxn];
int t_t[maxn];
void build_st(int n) {
    int i,j;
    FOR(i,0,n) {
        ST[i][0]=VAL[i];
        rep(j,1,t_t[1+i])
            ST[i][j]=min(ST[i][j-1],ST[i-(1<<(j-1))][j-1]);
    }
}
int query(int l,int r) {
    if (l>r) return INF;
    int t=t_t[r-l+1]-1;
//    printf("query:%d %d %d\n",l,r,1<<t);
//    printf(" ST:%d %d\n",ST[l+(1<<t)-1][t],ST[r][t]);
    int ret=min(ST[l+(1<<t)-1][t],ST[r][t]);
    return ret;
}

int wa[maxn],wb[maxn],wv[maxn],ws1[maxn];
int cmp(int *r,int a,int b,int l) {
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int *r,int *sa,int n,int m) {
    r[n++]=0;
    int i,j,p,*x=wa,*y=wb,*t;
    REP(i,m) ws1[i]=0;
    REP(i,n) ws1[x[i]=r[i]]++;
    rep(i,1,m) ws1[i]+=ws1[i-1];
    rREP(i,n) sa[--ws1[x[i]]]=i;
    for (j=1,p=1; p<n; j<<=1,m=p) {
        p=0; rep(i,n-j,n) y[p++]=i;
        REP(i,n) if (sa[i]>=j) y[p++]=sa[i]-j;
        REP(i,n) wv[i]=x[y[i]];
        REP(i,m) ws1[i]=0;
        REP(i,n) ws1[wv[i]]++;
        rep(i,1,m) ws1[i]+=ws1[i-1];
        rREP(i,n) sa[--ws1[wv[i]]]=y[i];
        t=x;x=y;y=t;
        p=1;x[sa[0]]=0;
        rep(i,1,n) x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
}
int rnk[maxn],height[maxn];
void getheight(int *r,int *sa,int n) {
    int i,j,k=0;
    FOR(i,1,n) rnk[sa[i]]=i;
    REP(i,n) {
        if (k) k--;
        j=sa[rnk[i]-1];
        while (r[i+k]==r[j+k]) k++;
        height[rnk[i]]=k;
    }
}
int n,m;
char C[maxn];
int s[maxn],sa[maxn];
int check(int x,int y,int l){
    int u=x,v=y; if (u>v) swap(u,v);
//    printf("check %d(%d %d): q=%d\n",l,x,y,query(u+1,v));
//    printf(" %s \n %s \nok\n",C+sa[x],C+sa[y]);
    if (query(u+1,v)>=l) return 0;
    else return x<y?-1:1;
}
bool cmprank(int x,int y){
    int ret=0,c;
    if (x>y) swap(x,y),ret^=1;
//    printf("\ncmp %d %d\n",x,y);
    if (x+m<=y){
        c=check(rnk[n+1],rnk[x],m);
        if (c) return (c<0)^ret;
        c=check(rnk[x],rnk[x+m],y-x-m);
        if (c) return (c<0)^ret;
        c=check(rnk[y-m],rnk[n+1],m);
        if (c) return (c<0)^ret;
    }else{
        c=check(rnk[n+1],rnk[x],y-x);
        if (c) return (c<0)^ret;
        c=check(rnk[n+1+(y-x)],rnk[n+1],m-(y-x));
        if (c) return (c<0)^ret;
        c=check(rnk[x],rnk[n+1+m-(y-x)],y-x);
        if (c) return (c<0)^ret;
    }return ret^1;
}
char A[maxn],B[maxn];
int val[maxn],id[maxn];
void solve_rank() {
    int i;
    scanf("%s%s",A,B);
    n=strlen(A);
    m=strlen(B);
    REP(i,n) s[i]=A[i]-'a'+1;
    s[n]='z'-'a'+2;
    REP(i,m) s[n+i+1]=B[i]-'a'+1;
    REP(i,n+m+1) C[i]=s[i]+'a'-1;
    da(s,sa,n+m+1,28);//???da wrong?
    getheight(s,sa,n+m+1);
    FOR(i,1,n+m+2) t_t[i]=t_t[i>>1]+1;
    REP(i,n+1) id[i]=i;
    FOR(i,1,n+m+1) VAL[i]=height[i];
    build_st(n+m+1);
//    FOR(i,1,n+m+1) printf("(%d)%d ",i,height[i]);puts("");
//    printf("cal:%d\n",query(15,20));
    sort(id,id+n+1,cmprank);
    REP(i,n+1) val[id[i]]=i;
    //printf("%s %s\n",A,B);
//        REP(i,n+1) printf("%d ",id[i]);puts(" <- id");
//        FOR(i,1,n+m+1) printf("(%-2d)%-5d(h=%-3d; val=%-3d): %s\n",i,sa[i],height[i],val[sa[i]],C+sa[i]);
//        FOR(i,0,n+m) printf("%d:%d; rnk=%d\n",i,val[i],rnk[i]);puts("");
}
int ans[maxn];
struct queries {
    int l,r,id;
    queries(int _l,int _r,int _id):l(_l),r(_r),id(_id){};
};
vector<queries> Q[507][507];
void solve_rmq() {
    int i,j,k,q;
    int n=strlen(A);
    int SIZE=sqrt(n)*0.4;
//    int SIZE=-1;
    FOR(i,0,n) VAL[i]=val[i];
    build_st(n);
    scanf("%d",&q);
    REP(i,q) {
        int l,r,k,x,y;
        scanf("%d%d%d%d%d",&l,&r,&k,&x,&y);
        ans[i]=INF;
        if (k>SIZE) { //solve_big
            int _l,_r,_s=l/k*k;
            _l=_s+x; _r=_s+y;
            for (; _l<=r; _l+=k,_r+=k)
                ans[i]=min(ans[i],query(max(l,_l),min(r,_r)));
        }else {//solve_small
            FOR(j,x,y){
                int _l=(l-j+k-1)/k,_r=(r+k-j)/k-1;
                if (_l>_r) continue;
//                printf("add_second (%d):(%d)%d %d\n",i,j,_l,_r);
                Q[k][j].push_back(queries(_l,_r,i));
            }
        }
    }FOR(k,1,SIZE){
        REP(i,k) if (Q[k][i].size()){
            int sz=-1;
            for (j=i;j<=n;j+=k)
                VAL[++sz]=val[j];
            if (sz==-1) continue;
            build_st(sz);
            for (auto now:Q[k][i])
                ans[now.id]=min(ans[now.id],query(now.l,now.r));
        }
    }
    REP(i,q) if (ans[i]==INF) printf("-1 ");
    else printf("%d ",id[ans[i]]);
}
int main() {
    solve_rank();
    solve_rmq();
    return 0;
}
/*
abbbbbbaaa baababaaab 10
1 2 1 0 0
2 7 8 4 7
2 3 9 2 8
3 4 6 1 1
0 8 5 2 4
2 8 10 4 7
7 10 1 0 0
1 4 6 0 2
0 9 8 0 6
4 8 5 0 1
*/

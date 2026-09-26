#include<bits/stdc++.h>
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define REP(I,N) for (I=0;I<N;I++)
using namespace std;
typedef long long LL;
const int maxn=4e5+7;
char s[maxn],str[maxn];
int len1,len2,p[maxn];
vector<int> Rseg[maxn];
vector<int> Lseg[maxn];
typedef pair<pair<int,int>,int> P;
vector<P> queL[maxn];
vector<P> queR[maxn];
void manacher(){
    int id=0,mx=0; int i;
    len1=strlen(s);
    str[0]='+'; str[1]='%';
    REP(i,len1+1) str[i*2+2]=s[i],str[i*2+3]='%';
    len2=len1*2+2;
    FOR(i,0,len2-1) {
        if (mx>i) p[i]=min(p[2*id-i],mx-i);
        else p[i]=1;
        while (str[i+p[i]]==str[i-p[i]]) p[i]++;
        if (p[i]+i>mx) mx=p[i]+i,id=i;
    }
//    FOR(i,1,len2-1) printf("%2d ",i); puts("");
//    FOR(i,1,len2-1) printf("%2c ",str[i]); puts("");
//    FOR(i,1,len2-1) printf("%2d ",p[i]); puts("");
    FOR(i,1,len2-1) {
        int l=(i+1)/2,r=(i+p[i]-1)/2;
        int ll=i-r,rr=i-l;
        if (l<=r) {
//            printf("%2d: l=%d-%d ",i,ll,rr); puts("");
//            printf("%2d: r=%d-%d ",i,l,r); puts("");
            Rseg[l].push_back(i);
            Rseg[r+1].push_back(-i);
            Lseg[ll].push_back(i);
            Lseg[rr+1].push_back(-i);
        }
    }
}
int n;
inline int lowbit(int x){return x&-x;}
LL Lsum[maxn],sum[maxn];
void add(int x,int L){
    int cnt=x<0?-1:1; x=x*cnt; L=L*cnt;
    for (;x<=n+n;x+=lowbit(x)) Lsum[x]-=L,sum[x]+=cnt;
}
inline LL getans(int x,int pos){
    LL ret=0;
    for (;x;x-=lowbit(x)) ret+=Lsum[x]+sum[x]*pos;
    return ret;
}
inline LL getans(int l,int r,int pos){
    return getans(r,pos)-getans(l-1,pos);
}
LL ans[maxn];
int main() {
    int q,i;
    scanf("%s",s);
    manacher();
    scanf("%d",&q);
    FOR(i,1,q) {
        int l,r;
        scanf("%d%d",&l,&r);
        queL[l-1].push_back(P{{l+l,l+r},-i});
        queL[r].push_back(P{{l+l,l+r},i});
        queR[l-1].push_back(P{{l+r+1,r+r},-i});
        queR[r].push_back(P{{l+r+1,r+r},i});
    } n=strlen(s);
    FOR(i,1,n){//L,R
        for (int v:Rseg[i]) {
            add(v,i-1);//pos,value
//            printf("ins: %d %d\n",v,i-1);
        }
        for (P now:queR[i]){
            int seg=now.second<0?-1:1,id=abs(now.second);
            int l=now.first.first,r=now.first.second;
            ans[id]+=seg*getans(l,r,i);
//            printf("que: %d %d(%d): (%d)%lld\n",l,r,i,now.second,seg*getans(l,r,i));
        }
    }

    FOR(i,1,n+n) Lsum[i]=sum[i]=0;
    FOR(i,1,n){//L,R
        for (int v:Lseg[i]) {
            add(v,i-1);//pos,value
//            printf("insL: %d %d\n",v,i-1);
        }
        for (P now:queL[i]){
            int seg=now.second<0?-1:1,id=abs(now.second);
            int l=now.first.first,r=now.first.second;
            ans[id]+=seg*getans(l,r,i);
//            printf("queL: %d %d(%d): (%d)%lld\n",l,r,i,now.second,seg*getans(l,r,i));
        }
    }
    FOR(i,1,q) printf("%lld\n",ans[i]);
    return 0;
}
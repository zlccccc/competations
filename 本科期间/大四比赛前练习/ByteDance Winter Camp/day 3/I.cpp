#include<bits/stdc++.h>
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
using namespace std;
const int maxn=4e6+7;
int wa[maxn],wb[maxn],wv[maxn],ws1[maxn];
int cmp(int *r,int a,int b,int l){
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int *r,int *sa,int n,int m){
    r[n++]=0;
    int i,j,p,*x=wa,*b,*y=wb,*t;
    REP(i,m) ws1[i]=0;
    REP(i,n) ws1[x[i]=r[i]]++;
    rep(i,1,m) ws1[i]+=ws1[i-1];
    rREP(i,n) sa[--ws1[x[i]]]=i;
    for (j=p=1;p<n;j<<=1,m=p) {
        p=0; rep(i,n-j,n) y[p++]=i;
        REP(i,n) if (sa[i]>=j) y[p++]=sa[i]-j;
        REP(i,n) wv[i]=x[y[i]];
        REP(i,m) ws1[i]=0;
        REP(i,n) ws1[wv[i]]++;
        rep(i,1,m) ws1[i]+=ws1[i-1];
        rREP(i,n) sa[--ws1[wv[i]]]=y[i];
        t=x; x=y; y=t;
        p=1; x[sa[0]]=0;
        rep(i,1,n) x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
}
int rnk[maxn],height[maxn];
void calheight(int *r,int *sa,int n) {
    int i,j,k=0;
    FOR(i,1,n) rnk[sa[i]]=i;
    REP(i,n) {
        if (k) k--;
        j=sa[rnk[i]-1];
        while (r[i+k]==r[j+k]) k++;
        height[rnk[i]]=k;
    }
}
char str[maxn];
int s[maxn];
int sa[maxn];
int S[maxn],id[maxn],top;
bool no[maxn],in[maxn];
pair<int,int> ans[maxn];
int n;
void upd(int len,int pos){
    int MIN=n+1;//end
    while (S[top]>=len) {//previous
        if (MIN!=n+1&&!no[S[top]]) ans[S[top]]=min(ans[S[top]],make_pair(MIN,id[top]));
        if (MIN!=n+1&&!no[S[top]]) ans[S[top]]=min(ans[S[top]],make_pair(id[top],MIN));
        //if (MIN!=n+1) printf("update1 %d: %d-%d\n",S[top],MIN,id[top]);
        if (S[top]!=len) no[S[top]]=1;//used![top]);
        // printf("pop k=%d\n",k);
        MIN=min(MIN,id[top]); top--;
    }
    if (MIN!=n+1&&pos!=n+1&&!no[len]) ans[len]=min(ans[len],make_pair(MIN,pos));
    if (MIN!=n+1&&pos!=n+1&&!no[len]) ans[len]=min(ans[len],make_pair(pos,MIN));
    //if (MIN!=n+1&&pos!=n+1) printf("update2 %d: %d-%d\n",len,MIN,pos);
    if (MIN!=n+1) S[++top]=len,id[top]=MIN;
    S[++top]=n+1,id[top]=pos;
    //for (int i=1;i<=top;i++) printf(" %d-%d\n",S[i],id[i]); puts("");
}
int main() {
    scanf("%s",str);
    n=strlen(str); int i;
    REP(i,n) s[i]=str[i]-'a'+1;
    da(s,sa,n,26+2); S[0]=-1;
    calheight(s,sa,n);
//    ans[n]=make_pair(1,1);
//    FOR(i,1,n) printf("%d ",sa[i]); puts(" <- sa");
    FOR(i,0,n) ans[i]=make_pair(n+1,n+1);
    FOR(i,1,n) {
//        printf("(%d:)%s %d\n",sa[i]+1,str+sa[i],height[i]);
        int len=height[i],pos=sa[i]+1;
        upd(len,pos); upd(n-pos+1,pos);
    } upd(0,n+1);
    int q; scanf("%d",&q);
    FOR(i,1,q){
        int x; scanf("%d",&x);
        if (ans[x].first==n+1) puts("-1 -1");
        else printf("%d %d\n",ans[x].first,ans[x].second);
    }
    return 0;
}
/*
2 1 0  <- sa
(3:)a 0
 4-3

(2:)aa 1
update 4: 4-3
 1-2
 4-2

(1:)aaa 2
update 4: 4-2
update2 2: 2-1
 1-2
 2-1
 4-1

update 4: 4-1
update 2: 1-1
update 1: 1-2
 4-4

-1 -1
1 2
1 1
1 1
*/
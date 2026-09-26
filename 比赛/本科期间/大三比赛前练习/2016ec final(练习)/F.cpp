#include <bits/stdc++.h>
#include <utility>
#include <algorithm>
using namespace std;
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define REP(I,N) for (I=0;I<N;I++)
typedef long long ll;
typedef pair<int,int> pii;
const int inf=0x3f3f3f3f;
const int maxn=8e5+7;
const ll mod=1e9+7;
ll powMM(ll a,ll b,ll M=mod){
    ll ret=1;
    for (;b;b>>=1,a=a*a%M)
        if (b&1) ret=ret*a%M;
    return ret;
}
namespace SAM{
    int next[maxn][26],fail[maxn],len[maxn];
    int cnt,last;
    void init(){
        cnt=last=0; fail[0]=-1; len[0]=0;
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
            else {
                int nq=++cnt; len[nq]=len[p]+1;
                memcpy(next[nq],next[q],sizeof(next[q]));
                fail[nq]=fail[q];
                fail[np]=fail[q]=nq;
                for (;p!=-1&&next[p][c]==q;p=fail[p]) next[p][c]=nq;
            }
        } last=np;
    }
    char A[maxn];
    void dfs(int x=0,int len=0){
        int i; printf("%s\n",A);
        REP(i,26) {
            if (next[x][i]) {
                A[len]=i+'a';
                dfs(next[x][i],len+1);
                A[len]=0;
            }
        }
    }
    pair<int,vector<int> > query(char str[]) {
        int n=strlen(str);
        int p=0,l=0,i,ret=n+1;
        vector<int> could;
        REP(i,n) {
            int c=str[i]-'a';
            if (next[p][c]) l++,p=next[p][c];
            else {
                while (p!=-1&&!next[p][c]) p=fail[p];
                if (p==-1) p=l=0;
                else l=len[p]+1,p=next[p][c];
            }// while (len[fail[p]]>=n) p=fail[p],l=len[p];//nope
            // printf("%d: l=%d\n",i+1,l);
            if (l!=i+1){
                if (l+1<ret) ret=l+1,could.clear();
                if (l+1==ret) ret=l+1,could.push_back(i-l);
            }
        } return make_pair(ret,could);
    }
} char str[maxn],tar[maxn];
int n,m,k;
int main(){
    int _,T; scanf("%d",&T);
    FOR(_,1,T){
        int i,j;
        scanf("%d",&n);
        SAM::init();
        FOR(i,1,n){
            if (i==1) {scanf("%s",tar); continue;}
            scanf("%s",str); int len=strlen(str);
            REP(j,len) SAM::add(str[j]-'a');
            SAM::last=0;
        }// SAM::dfs();
        auto ans=SAM::query(tar);
        int len=ans.first;
        printf("Case #%d: ",_);
        if (len==(int)strlen(tar)+1) puts("Impossible"); 
        else {
            vector<int> pos,nxt;
            pos=ans.second;
            REP(i,len){
                char c='z'+1;
                for (int now:pos) c=min(c,tar[now+i]);
                for (int now:pos) if (c==tar[now+i]) nxt.push_back(now);
                pos.clear(); swap(pos,nxt);
                str[i]=c;
            } str[len]=0;
            puts(str);
        }
    }
}
/*
3
2
aba
bab
3
qnu
cvbb
bnu
3
a
aa
aaa
*/
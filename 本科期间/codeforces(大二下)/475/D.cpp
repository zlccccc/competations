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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
const LL maxn=4e5+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

int ans[maxn];
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
//                pos[nq].push_back(pos[q][0]);
                for (;p!=-1&&next[p][c]==q;p=fail[p]) next[p][c]=nq;
            }
        }
        last=np;
        pos[last].push_back(len[np]);
    }
    int S[maxn],Q[maxn];
    vector<int> pos[maxn];
    vector<pair<int,int> > queries[maxn];
    void solve(){
        int t,i,j;
        FOR(i,1,cnt) S[i]=0;
        FOR(i,1,cnt) S[len[i]]++;
        FOR(i,1,cnt) S[i]+=S[i-1];
        FOR(i,1,cnt) Q[S[len[i]]--]=i;
        rFOR(t,1,cnt){
            i=Q[t];
//            printf(" %d: \n",i);
//            for (auto now:pos[i]) printf("%d ",now);puts("");
            map<int,int> MP;//剪枝吧
            if (queries[i].size())
                stable_sort(pos[i].begin(),pos[i].end());
            for (auto now:queries[i]){
                if ((int)pos[i].size()-now.first<0) ans[now.second]=-1;
                else if (MP[now.first])
                    ans[now.second]+=MP[now.first];
                else {
                    int Ans=INF,len=(int)pos[i].size()-now.first+1;
                    REP(j,len)
                        Ans=min(Ans,pos[i][j+now.first-1]-pos[i][j]);
                    MP[now.first]=Ans;
                    ans[now.second]+=Ans;
//                    printf("%d : %d %d; size=%d; ans=%d\n",i,now.first,now.second,pos[i].size(),Ans);
                }
            }
            int k=fail[i];
//            int l=pos[k].size();
//            pos[k].resize(pos[k].size()+pos[i].size());
//            merge(pos[k].begin(),pos[k].begin()+l,pos[i].begin(),pos[i].end(),pos[k].begin());
            if (pos[k].size()<pos[i].size()) pos[k].swap(pos[i]);
            for (int v:pos[i]) pos[k].push_back(v);
            vector<int>().swap(pos[i]);
//            pos[k].erase(unique(pos[k].begin(),pos[k].end()),pos[k].end());
        }
    }
    void query(char a[],int k,int pos){
        int i;LL ret=0;
        int n=strlen(a),p=0;
        REP(i,n){
            int c=a[i]-'a';
            if (next[p][c]) p=next[p][c];
            else {ans[pos]=-1;return;}
        }queries[p].push_back(make_pair(k,pos));
    }

    void print(){
        int i;
        FOR(i,1,cnt) {
        }
    }
    char a[maxn];
    void dfs(int x=0,int len=0){
        int i;
//        puts("");
        printf("%-3d(fail:%-3d,len=%-2d  pos=%-2d):%s;\n",x,fail[x],this->len[x],x?pos[x][0]:0,a);
        REP(i,26){
            if (next[x][i]){
                a[len]=i+'a';
                dfs(next[x][i],len+1);
                a[len]=0;
            }
        }
    }
}sam;
int n,q;
char A[maxn];
int main() {
    int i,j,k;
    scanf("%s",A);
    n=strlen(A);
    sam.init();
    REP(i,n) sam.add(A[i]-'a');
//    sam.dfs();
    scanf("%d",&q);
    REP(i,q){
        int k;
        scanf("%d%s",&k,A);
        ans[i]=strlen(A);
        sam.query(A,k,i);
    }sam.solve();
    REP(i,q) printf("%d\n",ans[i]);
//    printf("%d\n",timecnt);
    return 0;
}
/*
aaaaaaaaaaaaaaaaaaaaa
5
a
aa
aaa
aaaa
aaabbbbaaabababab
5
2 aaabbbbaaaba
2 baaabab
1 abbbbaaabab
6 a
1 aaabbbbaaabababab
*/

#include <bits/stdc++.h>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG1
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
inline void add(int &A,int B){A+=B;(A>=M)&&(A-=M);}
inline void tomin(int &A,int B){(A>M)&&(A=M);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m;
char S[maxn];
int A[maxn];
vector<int> big_pos[maxn],pos[maxn];

const int SIZE=1200;
void get_A(){
    int i;
    FOR(i,0,100000) {
        for (int v:pos[i]) A[v]=i;
        for (int v:big_pos[i]) A[v]=i;
    }
}
void solve_big(int *ans,int x){//get_ans
    int i; get_A();
    FOR(i,0,100000) ans[i]=INF; int pre=-INF;
    FOR(i,1,n){
        if (A[i]==x) pre=i;
        else ans[A[i]]=min(ans[A[i]],i-pre);
    } pre=INF*2;
    rFOR(i,1,n){
        if (A[i]==x) pre=i;
        else ans[A[i]]=min(ans[A[i]],pre-i);
    }
}
int solve_small(vector<int> &A,vector<int> &B){
    int i=0,ret=INF;
    for (int val:A){
        while (i<(int)B.size()&&B[i]<val)
            ret=min(ret,val-B[i++]);
    } i=0;
    for (int val:B){
        while (i<(int)A.size()&&A[i]<val)
            ret=min(ret,val-A[i++]);
    } return ret;
}
int *BIGID[maxn];
int pool[207][maxn],bigcnt;
void mergeInto(vector<int> &A,vector<int> &B){
    if (!A.size()) A.swap(B);
    if (!B.size()) return;
    int i=0; vector<int> C;
    for (auto val:A){
        while (i<(int)B.size()&&B[i]<val) C.push_back(B[i++]);
        C.push_back(val);
    } while (i<(int)B.size()) C.push_back(B[i++]);
    vector<int>().swap(B); C.swap(A);
}
void checkBig(int x){
    if (pos[x].size()>SIZE){
        if (BIGID[x]==nullptr) BIGID[x]=pool[bigcnt++];
        mergeInto(big_pos[x],pos[x]);
        solve_big(BIGID[x],x);
    }
}
int TaskA(){
    int i,j;
    int lastans=0;
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n) pos[A[i]].push_back(i);
    FOR(i,0,100000) BIGID[i]=nullptr; bigcnt=0;
    FOR(i,0,100000) checkBig(i);
    FOR(i,1,m){
        int op,x,y;
        scanf("%d%d%d",&op,&x,&y);
        x^=lastans; y^=lastans;
        if (op==1){
            if (x==y) continue;
            REP(j,bigcnt) pool[j][y]=min(pool[j][y],pool[j][x]),pool[j][x]=INF;
            bool rev=0;
            if (pos[y].size()+big_pos[y].size()<pos[x].size()+big_pos[x].size())
                rev=1, swap(x,y);
            mergeInto(pos[y],pos[x]); mergeInto(pos[y],big_pos[x]);
            checkBig(y);
            if (rev){
                swap(pos[x],pos[y]); swap(big_pos[x],big_pos[y]);
                swap(BIGID[x],BIGID[y]);
            }
        }else{
            if ((!pos[x].size()&&!big_pos[x].size())||
                (!pos[y].size()&&!big_pos[y].size())){
                lastans=INF;
            } else if (x==y){
                lastans=0;
            } else {
                lastans=solve_small(pos[x],pos[y]);
                if (BIGID[x]!=nullptr) lastans=min(lastans,BIGID[x][y]);
                if (BIGID[y]!=nullptr) lastans=min(lastans,BIGID[y][x]);
            }
            if (lastans==INF) {puts("Chtholly"); lastans=0;}
            else printf("%d\n",lastans);
        }
//        FOR(j,1,n) A[j]=0;
//        debug("actually: %d %d %d; lastans=%d\n",op,x,y,lastans); get_A();
//        FOR(j,1,n) debug("%d ",A[j]);deputs("");
    }
    return 0;
}
void initialize(){}
void Task_one(){TaskA();}
void Task_T(){int T;scanf("%d",&T);while (T--) TaskA();}
void Task_more_n(){while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m(){while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string(){while (~scanf("%s",S)) TaskA();}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_more_n_m();
}
/*
8 10
0 1 2 3 4 5 6 7
2 1 5
2 1 3
*/

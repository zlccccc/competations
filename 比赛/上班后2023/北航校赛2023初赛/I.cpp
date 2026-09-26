// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I,N) for (int I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (int I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (int I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (int I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (int I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (int I=(N),START=(S);I>=START;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

 // "1234567"
vector<string> Str={
    "1110111", // 0
    "0010010", // 1
    "1011101", // 2
    "1011011", // 3
    "0111010", // 4
    "1101011", // 5
    "1101111", // 6
    "1010010", // 7
    "1111111", // 8
    "1111011"  // 9
};

ll pw[maxn];
int MASK[10];
vector<int> items[1<<7];
void init() {
    pw[0]=1;
    rep_(i,1,10) pw[i]=pw[i-1]*10;
    REP_(i,10) {
        REP_(k,7) if (Str[i][k]=='1') MASK[i]|=1<<k;
        for (int x=MASK[i];x;x=(x-1)&MASK[i]) items[x].push_back(i);
        items[0].push_back(i);
    }
    // REP_(i,1<<7) {
    //     printf("i=%d ",i);
    //     for (int v:items[i]) printf("%d ",v); puts("");
    // }
}

int MP[10][2][2][2];
// 有三种情况可以确定值:
// 1.进位,最终结果ABC0000...(最高那位指示灯颜色要变的); 当且仅当后面无法确定value的时候触发
// 2.指示灯状态改变,而且相同的set可以分开(<=10); 需要考虑改变的过程中是否存在某个val的mask一直不变化
// 3.本身就只有一种可能; 需要计算操作几次能改变灯的状态
// 复杂度10*2*2*2; solve=20*10
int n,val[maxn];
ll query(int id,int over,int upd,int okay) {  // id; 是否已经for过一遍了(没for过的话还要for出头); 是否需要加到进位; 是否加到进位就可以区分出来
    if (id==n) return upd;
    if (MP[id][over][upd][okay]!=-INF) return MP[id][over][upd][okay];

    int mask=val[id];
    ll ret=INFF;

    int maskchg=0,maskitem=0;
    vector<vector<int>> cur;
    for (int v:items[mask]) maskitem|=1<<v;
    cur.push_back(items[mask]);

    int low=0,tag1=0,tag2=0; // tag1: 可以区分所有数字; tag2: +1的过程中数字可变化
    if (upd) low=10-items[mask][0];  // 至少加这么多

    auto update=[&](int x,bool realadd=true) {
        vector<vector<int>> nxt;
        for (auto &vec:cur) { // 检查是否可以split
            map<int,vector<int>> split;
            for (int v:vec) {
                int curmask=mask&MASK[(v+x)%10];
                if (realadd&&x+v>=10&&okay) {  // 加完可以直接分辨
                    maskchg|=1<<v;
                    nxt.push_back({v});
                } else {  // 加的过程中可以分辨
                    if (curmask!=mask) maskchg|=1<<v;
                    split[curmask].push_back(v);
                }
            }
            for (auto &p:split) nxt.push_back(p.second);
        }
        return nxt;
    };
    FOR_(x,1,low-1) cur=update(x);
    if (over) FOR_(x,low,10) cur=update(x,false);
    tag2|=(maskchg==maskitem);  // 数字在过程中有变化
    tag1|=(cur.size()==items[mask].size());  // 可以区分所有数字
    FOR_(x,low,10) { // +x; 已经加到进位了
        if (x==0) {  // 不加
            if (tag1) {
                ll sub=query(id+1,over,0,okay);
                if (sub!=-1) ret=min(ret,sub);
            }
        } else {
            auto nxt=update(x);
            // 更新+1
            tag2|=(maskchg==maskitem);

            if ((x-1)*pw[n-id-1]>=ret) break;  // 不可能更优

            if (!upd) {  // 不加时候的MAX
                if (tag1) {  // 已经可以区分当前位,希望区分后面的位(可以不加满)
                    // if (id==0) puts("start pre check");
                    ll sub=query(id+1,over||(x>1),0,tag2);  // 没必要加全就可以判断 
                    if (sub!=-1) ret=min(ret,(x-1)*pw[n-id-1]+sub);
                }
            }

            nxt.swap(cur);

            // 最小值必须加到满
            tag1|=(cur.size()==items[mask].size());  // 通过当前位区分所有数字

            if (tag1) {  // 已经可以区分了; 至少加到tag1, 就可以区分开所有sub
                // if (id==0) puts("start real check");
                ll sub=query(id+1,over||(x>1),1,(items[mask][0]+x>=10&&okay)||tag2);
                if (sub!=-1) ret=min(ret,(x-1)*pw[n-id-1]+sub);
            }
        }
        // if (id==2) 
        // if (upd==0&&okay==1) 
        // if (id==1&&over==0&&upd==1)
        if (false)
        {
            printf("  [sub] id=%d; over=%d: upd=%d; okay=%d: res=%d (x=%d; tag=%d %d)\n",id,over,upd,okay,ret,x,tag1,tag2);
            for (auto &p:cur) {
                printf("[");
                for (int v:p) printf("%d ",v);
                printf("]");
            } puts("");
        }
    }
    // printf("id=%d; over=%d: upd=%d; okay=%d: res=%d\n",id,over,upd,okay,ret);

    if (ret==INFF) ret=-1;
    MP[id][over][upd][okay]=ret;
    return ret;
}
int bruteforce() {  // 还是需要对拍一下...
    vector<vector<int>> cur;
    {
        vector<int> sol;
        sol.push_back(0);
        REP_(i,n) {
            vector<int> nxt;
            for (int k:sol) for (int v:items[val[i]]) nxt.push_back(k*10+v);
            sol.swap(nxt);
        }
        cur.push_back(sol);
        if (sol.size()==1) return 0;
    }
    FOR_(x,1,10000) {
        vector<vector<int>> nxt;
        for (auto &vec:cur) { // 检查是否可以split
            map<vector<int>,vector<int>> split;
            for (int v:vec) {
                vector<int> mask;
                for (int i=n-1,y=v+x;i>=0;i--) {
                    mask.push_back(val[i]&MASK[y%10]);
                    y/=10;
                }
                split[mask].push_back(v);
                // printf("["); for (int v:mask) pr2(v,7); printf("(%d)",v+x); printf("]");
            }
            // puts("");
            for (auto &p:split) if (p.second.size()>1) nxt.push_back(p.second);
        }
        // printf("i=%d\n",x);
        // for (auto &p:nxt) {
        //     printf("[");
        //     for (int v:p) printf("%d ",v);
        //     printf("]");
        // } puts("");
        nxt.swap(cur);
        if (cur.size()==0) return x;
    }
    return -1;
}
int solve() {
    REP_(i,10) REP_(x,2) REP_(y,2) REP_(z,2) MP[i][x][y][z]=-INF;
    cin>>n;
    REP_(i,n) {
        // 实际上考虑最高那位最少进位几次能把序列分开就可以
        string str;
        cin>>str; val[i]=0;
        REP_(k,7) if (str[k]=='1') val[i]|=1<<k;
        // pr2(mask,7); puts("");
        // for (int v:items[val[i]]) printf("%d ",v); puts("<- value");
    }
    int res=query(0,0,0,0);
    cout<<res<<endl;
    // int bf=bruteforce();
    // cout<<"bruteforce: "<<bf<<"  --  "<<res<<" diff="<<bf-res<<endl;
    return 0;
}
int check() {
    REP_(i,10) REP_(x,2) REP_(y,2) REP_(z,2) MP[i][x][y][z]=-INF;
    n=4;
    REP_(i,n) {
        // 实际上考虑最高那位最少进位几次能把序列分开就可以
        val[i]=0;
        REP_(k,7) if (rand()&1) val[i]|=1<<k;
        // pr2(mask,7); puts("");
        // for (int v:items[val[i]]) printf("%d ",v); puts("<- value");
    }
    int res=query(0,0,0,0);
    // cout<<res<<endl; return 0;
    int bf=bruteforce();
    cout<<"bruteforce: "<<bf<<"  --  "<<res<<" diff="<<bf-res<<endl;
    if (bf-res) {
        printf("%d\n",n);
        REP_(i,n) {pr2(val[i],7); puts("");}
    }
    return 0;
}
int main() {
    init();

    // FOR_(i,1,100) check();

    int T; T=1;
    scanf("%d",&T);
    FOR_(_,1,T){
        solve();
    }
}
/*
100
1
1101011
1
0111110
1
0000000
4
1011010
0101110
1100011
1001110
2
1111111
0000000
2
1111111
1001110
3
1111111
0000000
1001110
3
1111111
0000000
0000000
上面这个应该是99(不需要加满)!

100
4
1111001
0100100
0101011
0001010
*/
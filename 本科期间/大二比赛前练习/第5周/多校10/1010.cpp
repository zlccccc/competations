#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
typedef struct block
{
    int s;
    int t;
    bool operator<(const block &b) const
    {
        return this->t>b.t||(this->t==b.t&&this->s<b.s);
    }
}block;
block a[100001];
multiset<block> st;
int main()
{
    int T,e,cnt,N;
    long long sum;
    block temp,temp2;
    multiset<block>::iterator it;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        for(int i=0;i<N;i++)
        {
            scanf("%d%d",&temp.s,&temp.t);
            st.insert(temp);
        }
        cnt=0;
        sum=0;
        while(st.size())
        {
            cnt++;
            e=0;
            temp=(*st.begin());
            a[e++]=temp;
            temp2.t=temp.s-1;
            temp2.s=-1;
            while(1)
            {
                it=st.upper_bound(temp2);
                //printf("%d %d\n",(*it).t,(*it).s);
                if(it==st.end())
                    break;
                a[e++]=(*it);
                temp=(*it);
                temp2.t=temp.s;
                temp2.s=-1;
            }
            sum+=a[0].t-a[e-1].s;
            for(int i=0;i<e;i++)
                st.erase(st.find(a[i]));
        }
        printf("%d %lld\n",cnt,sum);
    }
    return 0;
}


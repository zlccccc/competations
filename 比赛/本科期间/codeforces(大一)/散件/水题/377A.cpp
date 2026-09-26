#include <iostream>
using namespace std;
int main(){
    int k,r,i;
    cin>>k>>r;
    for (i=1;((k*i)%10!=r)&&((k*i)%10!=0);i++);
    cout<<i;
}

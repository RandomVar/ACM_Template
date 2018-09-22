/*矩形面积交*/

#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define lson rt<<1
#define rson rt<<1|1
#define Lson L,mid,lson
#define Rson mid+1,R,rson
const int maxn=2005;
struct segment
{
    int l;
    int r;
    int h;
    int type;
    segment(){}
    segment(int l,int r,int h,int type):l(l),r(r),h(h),type(type){}
    bool operator <(const segment & ryh) const
    {
        return h<ryh.h;
    }
}a[maxn];
struct point
{
    int x1,y1,x2,y2,z1,z2;
    point(){}
    point(int x1,int y1,int z1,int x2,int y2,int z2):x1(x1),y1(y1),z1(z1),x2(x2),y2(y2),z2(z2){}
}cube[maxn];
int cnt[maxn<<2];
int allx[maxn];
int allz[maxn];
int one[maxn<<2],two[maxn<<2],three[maxn<<2];
void pushup(int L,int R,int rt)
{
    if(cnt[rt]>=3)
    {
        one[rt]=two[rt]=three[rt]=allx[R+1]-allx[L];
    }
    else if(cnt[rt]==2)
    {
        one[rt]=two[rt]=allx[R+1]-allx[L];
        if(L==R)
            three[rt]=0;
        else
            three[rt]=one[lson]+one[rson];
    }
    else if(cnt[rt]==1)
    {
        one[rt]=allx[R+1]-allx[L];
        if(L==R)
        {
            two[rt]=three[rt]=0;
        }
        else
        {
            three[rt]=two[lson]+two[rson];
            two[rt]=one[lson]+one[rson];
        }
    }
    else
    {
        if(L==R)
        {
            one[rt]=two[rt]=three[rt]=0;
        }
        else
        {
            one[rt]=one[lson]+one[rson];
            two[rt]=two[lson]+two[rson];
            three[rt]=three[lson]+three[rson];
        }
    }
}
void update(int l,int r,int val,int L,int R,int rt)
{
    if(l<=L&&r>=R)
    {
        cnt[rt]+=val;
        pushup(L,R,rt);
        return ;
    }
    int mid=(L+R)>>1;
    if(l<=mid)
        update(l,r,val,Lson);
    if(r>mid)
        update(l,r,val,Rson);
    pushup(L,R,rt);
}
int main()
{
    int T;
    scanf("%d",&T);
    int kase=0;
    while(T--)
    {
        int N;
        scanf("%d",&N);
        for(int i=1;i<=N;i++)
        {
            int x1,x2,y1,y2,z1,z2;
            scanf("%d%d%d%d%d%d",&x1,&y1,&z1,&x2,&y2,&z2);
            cube[i]=point(x1,y1,z1,x2,y2,z2);
            allz[i]=z1,allz[i+N]=z2;
        }
        sort(allz+1,allz+1+N*2);
        int cntz=unique(allz+1,allz+1+N*2)-allz-1;
        long long ans=0;
        for(int i=1;i<cntz;i++)
        {
            int tot=0;
            memset(cnt,0,sizeof(cnt));
            memset(one,0,sizeof(one));
            memset(two,0,sizeof(two));
            memset(three,0,sizeof(three));
            for(int j=1;j<=N;j++)
            {
                if(cube[j].z1<=allz[i]&&cube[j].z2>=allz[i+1])
                {
                    a[++tot]=segment(cube[j].x1,cube[j].x2,cube[j].y1,1);
                    allx[tot]=cube[j].x1;
                    a[++tot]=segment(cube[j].x1,cube[j].x2,cube[j].y2,-1);
                    allx[tot]=cube[j].x2;
                }
            }
            sort(allx+1,allx+1+tot);
            int m=unique(allx+1,allx+1+tot)-allx-1;
            sort(a+1,a+tot+1);
            for(int j=1;j<tot;j++)
            {
                int l=lower_bound(allx+1,allx+1+m,a[j].l)-allx;
                int r=lower_bound(allx+1,allx+1+m,a[j].r)-allx;
                if(l<r)
                    update(l,r-1,a[j].type,1,m,1);
                ans+=(long long)(three[1])*(a[j+1].h-a[j].h)*(allz[i+1]-allz[i]);
            }
        }
        printf("Case %d: %lld\n",++kase,ans);
    }
    return 0;
}

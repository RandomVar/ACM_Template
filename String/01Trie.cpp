//HDU4835
struct Trie{
    int next[maxnode][2];
    ll val[maxnode];
    int root,cnt;
    int newnode()
    {
        next[cnt][0]=next[cnt][1]=-1;
        val[cnt++]=0;
        return cnt-1;
    }
    void init()
    {
        cnt=0;
        root=newnode();
    }
    void insert(ll x)
    {
        int now=root;
        for(int i=32;i>=0;i--)//attention
        {
           int id=((x>>i)&1);
           if(next[now][id]==-1)
                next[now][id]=newnode();
            
            now=next[now][id];   
        }
        val[now]=x;
    }
    ll query(ll x)
    {
        int now=root;
        for(int i=32;i>=0;i--)
        {
            int id=((x>>i)&1);
            if(next[now][id^1]!=-1)
            {
                now=next[now][id^1];
            }
            else
            {
                now=next[now][id];
            }
        }
        return val[now];
     } 
    
};
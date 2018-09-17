
/****AC自动机 HUD-2222****/
/*以now节点结尾的后缀 与 root-fail[now]所表示的字符串 相同*/
const int NUMA=26;
struct trie{
    
   int next[maxnode][NUMA],fail[maxnode],ed[maxnode];//attention
   int root,cnt;
   int newnode(){
      for(int i=0;i<NUMA;i++)
        next[cnt][i]=-1;
      ed[cnt++]=0;
      return cnt-1;
   }
   
   void init(){
      cnt=0;
      root=newnode();
   }

   void inser(char* buf){
     int len=strlen(buf);
     int now=root;
     for(int i=0;i<len;i++){
         if(next[now][buf[i]-'a']==-1)
             next[now][buf[i]-'a']=newnode();
         now=next[now][buf[i]-'a'];
     }
     ed[now]++;
   }

   void build(){
     queue<int>que;
     fail[root]=root;
     for(int i=0;i<NUMA;i++){
        if(next[root][i]==-1)
             next[root][i]=root;
        else{
            fail[next[root][i]]=root;
            que.push(next[root][i]);
        }}
        while(!que.empty()){
            int now=que.front();
            que.pop();
            for(int i=0;i<NUMA;i++){
                if(next[now][i]==-1)
                    next[now][i]=next[fail[now]][i];
                else{
                    fail[next[now][i]]=next[fail[now]][i];
                    que.push(next[now][i]);
                }
            }
        }
     }

  int query(char* buf){
    int len=strlen(buf);
    int now=root;
    int res=0;
    for(int i=0;i<len;i++){
        now=next[now][buf[i]-'a'];
        int temp=now;
        while(temp!=root){
            res+=ed[temp];
            ed[temp]=0;
            temp=fail[temp];
        }
    }
  return res;
  }
};
char buf[maxn];
trie ac;
int main(){
    int n;
    cin>>n;
    ac.init();
    for(int i=0;i<n;i++)
        cin>>buf,ac.inser(buf);
    ac.build();
    cin>>buf;
    cout<<ac.query(buf)<<endl;
return 0;
}

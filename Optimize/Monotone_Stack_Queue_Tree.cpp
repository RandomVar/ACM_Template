/*单调栈单调队列和笛卡尔树*/
/** 单调栈 cf602D **/
/*找出左侧第一个大于它的数*/
 int top=-1;
 for(int i=1;i<=n;i++)
  {

     while(top>=0&&h[i]>=h[st[top]]) //delete the elem in stack no more larger than i
        top--;
     if(top==-1)
            //all the elem in the left no more larger than i
      else
            //the nearest left elem larger than i

    st[++top]=i;//add i to the stack
  }

/*单调队列 POJ - 2823 */
/*求长度为k的区间最小（大）值，或长度不超过k的区间最小（大）值*/
/*求长度为k的区间最小值*/
    int top=-1;
    for(int i=1;i<=k;i++)
    {
        while(top>=0&&a[i]<=a[que[top]])
            top--;

        que[++top]=i;
        b[0]=a[que[0]];
    }

    int s=0;
    for(int i=k+1;i<=n;i++)
    {
        if(que[s]==i-k) s++;
        while(top>=s&&a[i]<=a[que[top]])
            top--;

        que[++top]=i;
        b[i-k]=a[que[s]];
    }

/**笛卡尔树**/
/**
 * 中序遍历得到的序列为原数组序列
 * 节点的key值要大于其左右子节点的key值
 * 利用单调栈建树
 **/
void build() {
	int top=0;
	for(int i=1;i<=n;i++)
      l[i]=0,r[i]=0,vis[i]=0;
	for(int i=1;i<=n;i++)
     {
		int k=top;
		while (k>0&&a[stk[k-1]]<a[i]) --k;
		if (k) r[stk[k-1]]=i;//找出i左边第一个比它大的数，把i连到它的右子树
		if (k<top) l[i]=stk[k];//将该数字原来的右子树连到i的左子树
		stk[k++]=i;
		top=k;
	}
    for(int i=1;i<=n;i++)
	   vis[l[i]]=vis[r[i]]=1;
	int rt=0;
    for(int i=1;i<=n;i++)
       if (vis[i]==0)  rt=i;//find the root
}

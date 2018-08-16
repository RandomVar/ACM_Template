/**upper_bound **/

 while(l<=r)  
 {
   int mid=(l+r)/2;
   if(ok)  l=mid+1;
   else  r=mid-1;
 }
  return l;
	 

/**lower_bound **/
 int lb=-1,ub=res;
  while(ub-lb>1)
  {
    int mid=(lb+ub)/2;
    if(ok) ub=mid;
    else lb=mid;
  }
  return ub;

/*另一种好用的lower_bound*/
int ans=0;
while(l<=r)
{
  int mid=(l+r)/2;
  if(ok) l=mid+1,ans=mid;
  else r=mid-1;
}
return ans;

/**浮点数二分*/
 for(int i = 0; i < 100; i++) 
 {
      double mid = (l + r) / 2.0;
      if(check(mid)) r = mid;
      else l = mid;
  }
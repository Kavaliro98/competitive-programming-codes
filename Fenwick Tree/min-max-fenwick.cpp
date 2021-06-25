#include <bits/stdc++.h>
using namespace std;

/*
 * Min/Max fenwick tree supporting point update & range query
 * source : https://stackoverflow.com/a/34602284/8361110
 */

struct Fenwick{
   int n;
   vector<int> org, bot, top;
   function<int (int, int)> fun;
   function<bool (int, int)> op;
   Fenwick(int n, function<bool (int, int)> op): n(n), op(op) {
      fun = [op](int a, int b)->int{return op(a,b) ? a : b;};
      org.resize(n+1);
      bot.resize(n+1);
      top.resize(n+1);
   }
   void upd(int idx, int val){
      int old = org[idx];
      if(old == val) return;
      // Update org array
      org[idx]=val;
      //Update bot Tree
      for(int i=idx,v=val; i<=n ; i+=i&-i){
         if(v!=bot[i] && op(bot[i], v)){
            if(old==bot[i]){
               v = fun(v, org[i]);
               for(int x,r=1; x=(i&-i)>>r ; r++)
                  v=fun(v, bot[i-x]);
            }
            else break;
         }
         if(v==bot[i]) break;
         bot[i]=v;
      }
      //Update top Tree
      for(int i=idx,v=val; i ; i-=i&-i){
         if(v!=top[i] && op(top[i], v)){
            if(old==top[i]){
               v=fun(v, org[i]);
               for(int x,r=1; x=(i&-i)>>r ; r++)
                  if(i+x>n+1) break;
                  else v=fun(v, top[i+x]);
            }
            else break;
         }
         if(v==top[i]) break;
         top[i]=v;
      }
   }
   int qry(int L, int R){
      int val = org[L];
      int cur, pre;
      for(pre=L ; (cur=pre+(pre&-pre))<=R ; pre=cur)
         val = fun(val, top[pre]);
      val = fun(val, org[pre]);
      for(pre=R ; (cur=pre-(pre&-pre))>=L ; pre=cur)
         val = fun(val, bot[pre]);
      return val;
   }
   int qry(int pos){
      return org[pos];
   }
};


int main() {
   // minmum range qurey
   int n = 10;
   Fenwick fn_mn(n, less<int>());
   fn_mn.upd(1, 1);
   fn_mn.upd(2, -2);
   int mn = fn_mn.qry(1, 10); // = -2

   // maximum range query
   Fenwick fn_mx(n, greater<int>());
}

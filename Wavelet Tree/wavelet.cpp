#include <bits/stdc++.h>
using namespace std;


template <typename T>
struct Wavelet {
#define pb push_back
   typedef typename vector<T>::iterator iter;
   // typedef typename T* iter;
   
   struct node {
      vector<int> wav;
      node *lft, *rgt;
      int id;
   } *root = NULL; 
   
   // Alphabet range 
   const int minVal;
   const int maxVal;
   
   function<bool (T, int)> op;
   function<void (int, iter, iter)> fun;

   Wavelet(iter b, iter e,
           int minVal, int maxVal,
           function<bool (T, int)> op = [](T x, int md){return x<=md;},
           function<void (int, iter, iter)> fun = [](int, iter, iter){}) 
      : minVal(minVal), maxVal(maxVal), op(op), fun(fun) {
      vector<int> vec(b, e);
      root = build(vec.begin(), vec.end(), minVal, maxVal, NULL);
   }

   int id_count=0;
   node* build(iter b, iter e, int lo, int hi, node* p) {
      if(b==e) return NULL;
      auto& [wav,lft,rgt,id] = *(p = p ? p : new node());
      
      int md = lo+hi>>1;
      
      wav.reserve(e-b+1); wav.pb(0);

      id = id_count++;
      fun(id, b, e);
      
      for(iter it=b ; it!=e ; ++it) {
         wav.pb( wav.back() + op(*it, md) );
      }
            
      iter m = stable_partition(b, e, [=](int i){return op(i,md);});

      if(lo!=hi) {
         lft = build(b, m, lo, md, lft);
         rgt = build(m, e, md+1, hi, rgt);
      }
      return p;
   }
   // find the k-th (1-based) smallest element in [i, j)
   int quantile(int k, int i, int j, int lo, int hi, node* p) {
      auto& [wav,lft,rgt,id] = *p;

      int md = lo+hi>>1;
      int leq = wav[j]-wav[i];
      
      if(lo == hi) return lo;
      
      if(k<=leq) return quantile(k, wav[i], wav[j], lo, md, lft);
      else return quantile(k-leq, i-wav[i], j-wav[j], md+1, hi, rgt);
   }

   // count the occurrences of numbers in the range [a, b] present in the positions [i, j)
   int count(int i, int j, int a, int b, int lo, int hi, node* p) {
      if(!p) return 0;
      auto& [wav,lft,rgt,id] = *p;

      if(b < lo || hi < a) return 0;
      if(a <=lo && hi <=b) return j-i;
      int md = lo+hi>>1;

      return count(wav[i], wav[j], a, b, lo, md, lft) +
         count(i-wav[i], j-wav[j], a, b, md+1, hi, rgt); 
   }

   void getRanges(int i, int j, int a, int b, int lo, int hi, node* p, vector<tuple<int,int,int>> &rng) {
      if(!p) return;
      auto& [wav,lft,rgt,id] = *p;

      if(b < lo || hi < a) return;
      if(a <=lo && hi <=b) {
         rng.emplace_back(id, i, j-1);
         return;
      }
      int md = lo+hi>>1;

      getRanges(wav[i], wav[j], a, b, lo, md, lft);
      getRanges(i-wav[i], j-wav[j], a, b, md+1, hi, rgt); 
   }
   
   
   void clear(node* p) {
      if(!p) return;
      auto& [wav,lft,rgt,vec] = *p;
      clear(lft); clear(rgt);
      delete p;
   }

   int quantile(int k, int i, int j){ return quantile(k,i,j+1,minVal,maxVal,root); }
   int count(int i, int j, int a, int b) { return count(i,j+1,a,b,minVal,maxVal,root); }
   vector<tuple<int,int,int>> getRanges(int i, int j, int a, int b) {
      vector<tuple<int,int,int>> rng;
      getRanges(i,j+1,a,b,minVal,maxVal,root,rng);
      return rng;
   }
   void clear() { clear(root); root=NULL; }
};

int main() {
   
   auto doNothing = [](int,auto,auto)->void{};
   // Use values directly
   vector<int> vec({1,3,2,0,6,7,5,9});
   Wavelet<int> wav1(vec.begin(), vec.end(), 0, 9, less_equal<int>(), doNothing);

   vector<vector<int>> data;
   auto storeData = [&](int id, auto b, auto e)->void {
                       data.pb(vector<int>(b, e));
                    };

   // or use indecies (handy for offline queries)
   vector<int> idx({0,1,2,3,4,5,6,7});
   Wavelet<int> wav2(idx.begin(), idx.end(), 0, 9, [&](int i, int val)->bool{return vec[i]<=val;}, storeData);
}

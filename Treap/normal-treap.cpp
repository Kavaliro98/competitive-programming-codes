#include <bits/stdc++.h>
using namespace std;

#define fr first
#define sc second

struct node {
   int key, pr, sz;
   int val, mn, lzy;
   node *l, *r;
   node(int k, int x): key(k), pr(rand()), sz(1), val(x), mn(x), lzy(0), l(NULL), r(NULL) {}

   static int szOf(node *p) { return p?p->sz:0; }
   static int mnOf(node *p) { return p?p->mn:1e9; }
   
   static void upd(node *p) {
      if(!p) return;
      p->sz = szOf(p->l) + szOf(p->r) + 1;
      p->mn = min({mnOf(p->l), p->val, mnOf(p->r)});
   }
   
   static void propagate(node *p, int lzy) {
      if(!p) return;
      p->val += lzy;
      p->mn  += lzy;
      p->lzy += lzy;
   }
   
   static void push(node *p) {
      if(!p || !p->lzy) return;
      propagate(p->l, p->lzy);
      propagate(p->r, p->lzy);
      p->lzy = 0;
   }
};

template<typename T>
struct Treap {
   T* root = NULL;

   // merge subtree a with b (where a < b)
   T* merge(T* a, T* b) {
      if(!a || !b) return a ? a : b;
      if(a->pr > b->pr) {
         T::push(a);
         a->r = merge(a->r, b);
         T::upd(a);
         return a;
      }
      else {
         T::push(b);
         b->l = merge(a, b->l);
         T::upd(b);
         return b;
      }
   }

   // fr : [_, key) | sc : [key, _]
   pair<T*, T*> split(T* p, int key) {
      if(!p) return {NULL, NULL};
      T::push(p);
      if(key > p->key) { // p & p->l goes in fr
         T *a=p, *b;
         tie(a->r, b) = split(p->r, key);
         T::upd(a);
         return {a, b};
      }
      else { 
         T *a, *b=p;
         tie(a, b->l) = split(p->l, key);
         T::upd(b);
         return {a, b};
      }
   }
   
   T* insert(T* p, T* v) {
      auto [a,b] = split(p, v->key);
      return merge(a, merge(v, b));
   }
   
   T* erase(T* p, int key) {
      auto [a,b] = split(p, key);
      return merge(a, split(b, key+1).sc);
   }
};


int32_t main()
{
   Treap<node> tr;
   auto& root = tr.root;
   
   root = tr.insert(root, new node(5, 1));
   root = tr.insert(root, new node(10, 2));

   root = tr.merge(root, new node(20, 3));

   auto [lft, rgt] = tr.split(root, 15);

   node::propagate(lft, +10);

   root = tr.merge(lft, rgt);
}

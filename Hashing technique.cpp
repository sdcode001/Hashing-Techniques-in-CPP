#include<bits/stdc++.h>
using namespace std;

class Node{
public:
  int val;
  Node* ptr;
 };

class Ideal_Hash{
  int* hash_table;
public:
  Ideal_Hash(int arr[],int n){
    int max=arr[0];
    for(int i=1;i<n;i++){if(arr[i]>max){max=arr[i];}}
    hash_table=new int[max+1];
    for(int i=0;i<max+1;i++){hash_table[i]=0;}
    for(int i=0;i<n;i++){
      hash_table[arr[i]]++;
    }
  }
  ~Ideal_Hash(){delete []hash_table;}

  int search(int key){
    if(hash_table[key]!=0){return 1;}
    else{return 0;}
  }

};


class Hash_Chain{    //here hash function is h(x)=x%10;
  Node* hash_table[10];
public:
  Hash_Chain(int arr[],int n){
    for(int i=0;i<10;i++){hash_table[i]=NULL;}
    int index;
      for(int i=0;i<n;i++){
        index=arr[i]%10;
        Node* p;
        if(hash_table[index]==NULL){
          hash_table[index]=new Node;
          hash_table[index]->val=arr[i];
          hash_table[index]->ptr=NULL;
        }
        else{
          p=hash_table[index];
          int temp1=arr[i];
          while(p->ptr!=NULL){if(temp1<=p->val){swap(temp1,p->val);} p=p->ptr;}
            p->ptr=new Node;
            Node* q=p->ptr;
            q->val=temp1;
            q->ptr=NULL;
            if(p->val>q->val){swap(p->val,q->val);}
          }
        }
      }

      ~Hash_Chain(){for(int i=0;i<10;i++){delete hash_table[i];}}

      int search(int key){
             int index=key%10;
             if(hash_table[index]!=NULL){
               Node* p=hash_table[index];
               while(true){
                 if(p==NULL){break;}
                 if(p->val==key){return 1;}
                 else{p=p->ptr;}}
                 return 0;
               }
             else{return 0;}
        }

      void swap(int& a,int& b){
        int temp=a;
        a=b;
        b=temp;}
};


class Double_Hash{            //here size of hash table(2n) should be double or grater number of elements(n) so that the loading factor<=0.5
  int* hash_table;            //here 2 hash function is combined to fill the hash table at the time of collision(h'(x)) otherwise h(x)=h1(x). h'(x)={h1(x)+ i*h2(x)}%2n where h1(x)=x%2n and h2(x)=7-(x%7) and i={1,2,3,4,5....} here 7 is used as 7 is a prime number.
  int  n;                     //Double_Hash method is introduced to reduce collisions.
public:
  Double_Hash(int arr[],int size){
    n=size;
    hash_table=new int[2*n];
     for(int j=0;j<2*n;j++){hash_table[j]=0;}  //initializing each room of hash table with 0. means it is empty.
     int index,i;
     for(int j=0;j<n;j++){
       i=1;
       index=arr[j]%(2*n);   //initailly h(arr[j])=h1(arr[j]);
       if(hash_table[index]==0){hash_table[index]=arr[j];}
       else{
         index=((arr[j]%(2*n))+i*(7-(arr[j]%7)))%(2*n); //hash function h'(arr[j]) at collision time;
         while(hash_table[index]!=0){
           i++;
           index=((arr[j]%(2*n))+i*(7-(arr[j]%7)))%(2*n);
         }
         hash_table[index]=arr[j];}
      }
   }

  ~Double_Hash(){delete []hash_table;}

  int search(int key){
    int index,i;
    i=0;
    index=((key%(2*n))+i*(7-(key%7)))%(2*n);
    while(hash_table[index]!=0){
      if(key==hash_table[index]){return 1;}
      else{i++; index=((key%(2*n))+i*(7-(key%7)))%(2*n);}
    }
   return 0;
  }

};


int main(){
  int list[7]={5,25,15,35,95,4,47};
  //Hash_Chain hc(list,7);
  Double_Hash dh(list,7);
  cout<<dh.search(95);
  return 0;
}

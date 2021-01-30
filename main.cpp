#include <iostream>
#include <cstring>
#include "graph.h"

using namespace std;

int main(){
  char in[80];
  int intin;
  graph* g = new graph();
  cout << "graph creator. addvertex, addedge, removevertex, removeedge, findshortest" << endl;
  while(true){
    cout << "enter a command: " << endl;
    cin >> in;
    if(strcmp(in, "addvertex") == 0){

    }
    else if(strcmp(in, "addedge") == 0){

    }
    else if(strcmp(in, "removevertex") == 0){

    }
    else if(strcmp(in, "removeedge")==0){

    }
    else if(strcmp(in, "findshortest")==0){

    }
    else{
      cout << "invalid command" << endl;
    }
  }
}

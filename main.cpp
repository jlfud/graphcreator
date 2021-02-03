#include <iostream>
#include <cstring>
#include <vector>


using namespace std;
struct vertex{
  char name[80];
};
void dijkstra(int index1, int index2, int arr[20][20], vertex* graph[20], int currentId);
int main(){
  int arr[20][20];
  vertex* graph[20];
  for(int a = 0; a < 20; a++){
    for(int b = 0; b < 20; b++){
      arr[a][b] = 0;
    }
  }
  int currentId = 0;
  char in[80];
  int intin = 0;
  
  cout << "graph creator. addvertex, addedge, removevertex, removeedge, findshortest, print" << endl;
  while(true){
    cout << "enter a command: " << endl;
    cin.get(in, 80);
    cin.get();
    if(strcmp(in, "addvertex") == 0){
      cout << "name of vertex: " << endl;
      vertex* v = new vertex();
      cin.get(v->name, 80);
      cin.get(); 
      graph[currentId] = v;
      currentId++;
    }
    else if(strcmp(in, "addedge") == 0){
      bool added = false; 
      cout << "name of first vertice: " << endl;
      cin.get(in,80);
      cin.get();
      for(int i = 0; i < currentId; i++){
	if(strcmp(graph[i]->name, in)==0){
	  cout << "name of second vertice: " << endl;
	  cin.clear();
	  cin.get(in, 80);
	  cin.get();
	  for(int a = 0; a < currentId; a++){
	    if(strcmp(graph[a]->name, in)==0){
	      cout << "weight of edge: " << endl;
	      cin >> intin;
	      cin.get();
	      arr[i][a] = intin;
	      arr[a][i] = intin;
	      added = true; 
	    }
	  }
	  if(added){
	    break;
	  }
	}
      }
      
    }
    else if(strcmp(in, "removevertex") == 0){
      cout << "name of the vertex you would like to remove: " << endl;
      cin.get(in, 80);
      cin.get();
      for(int i = 0; i < currentId; i++){
	if(strcmp(graph[i]->name, in)==0){
	  delete graph[i];
	  for(int a = i; a < currentId; a++){
	    //i is the indexs that we deleted
	    if(a == currentId){
	      break;
	    }
	    arr[0][a] = arr[0][a+1];
	    arr[a][0] = arr[a+1][0];
	    graph[a] = graph[a+1]; 
	  }
	  currentId--;
	}
      }
    }
    else if(strcmp(in, "removeedge")==0){
      bool removed = false;
      cout << "name of first vertice: " << endl;
      cin.get(in,80);
      cin.get();
      for(int i = 0; i < currentId; i++){
	if(strcmp(graph[i]->name, in)==0){
	  cout << "name of second vertice: " << endl;
	  cin.clear();
	  cin.get(in, 80);
	  cin.get();
	  for(int a = 0; a < currentId; a++){
	    if(strcmp(graph[a]->name, in)==0){
	      arr[i][a] = 0;
	      arr[a][i] = 0;
	      removed = true;
	    }
	  }
	  if(removed){
	    break;
	  }
	}
      }
    }
    else if(strcmp(in, "findshortest")==0){
      //djistrika algorithm
      bool done = false;
      cout << "name of first vertice: " << endl;
      cin.get(in,80);
      cin.get();
      for(int i = 0; i < currentId; i++){
	if(strcmp(graph[i]->name, in)==0){
	  cout << "name of second vertice: " << endl;
	  cin.clear();
	  cin.get(in, 80);
	  cin.get();
	  for(int a = 0; a < currentId; a++){
	    if(strcmp(graph[a]->name, in)==0){
	      //call djstrika here
	      dijkstra(i, a, arr, graph, currentId);
	      done = true;
	    }
	  }
	  if(done){
	    break;
	  }
	}
      }
    }
    else if(strcmp(in, "print")==0){
      cout << "  ";
      for(int i = 0; i < currentId; i++){
	cout << graph[i]->name << " ";
      }
      cout << endl;
      for(int a = 0; a < currentId; a++){
	for(int b = 0; b < currentId; b++){
	  if(b == 0){
	    cout << graph[a]->name << " ";
	  }
	  cout << arr[a][b] << " "; 
	}
	cout << endl;
      }
    }
    else{
      cout << "invalid command" << endl;
    }
  }
}
void dijkstra(int index1, int index2, int arr[20][20], vertex* graph[20], int currentId){
  int distances[currentId]; 
  bool visited[currentId];
  vertex* previous[currentId];
  
  for(int i = 0; i < currentId; i++){
    if(i == index1){
      distances[i] = 0;
      visited[i] = false;
      previous[i] = NULL;
    }
    else if(graph[i] == NULL){
      distances[i] = 1000000;
      visited[i] = true; 
    }
    else{
      distances[i] = 10000;
      visited[i] = false;
    }
  }

  while(true){
    bool done = false; 
    for(int i = 0; i < currentId; i++){
      if(!visited[i]){
	done = true;
	break;
      }
    }
    if(done){
      break;
    }
    int current = 10000;
    int index = 0;
    for(int i = 0; i < currentId; i++){
      if(arr[index][i] != 0){
	if(current + arr[index][i] < distances[i]){
	  distances[i] = current + arr[index][i];
	  previous[i] = graph[index]; 
	}
      }
    }
    visited[index] = true;
  }

  cout << distances[index2] << endl;

  
}

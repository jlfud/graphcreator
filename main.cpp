#include <iostream>
#include <cstring>
#include <vector>


using namespace std;
//for each vertex
struct vertex{
  char name[80];
};
//prototype
void dijkstra(int index1, int index2, int arr[20][20], vertex* graph[20], int currentId);

int main(){
  int arr[20][20];
  vertex* graph[20];
  //set all distances to 0
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
      //get a vertex and simply update the array of vertexes we have
      cout << "name of vertex: " << endl;
      vertex* v = new vertex();
      cin.get(v->name, 80);
      cin.get(); 
      graph[currentId] = v;
      currentId++;
    }
    else if(strcmp(in, "addedge") == 0){
      //find the two vertices we need, then get the edge weight
      //add that to the 2d array as an int (for both src to destination and the other way around)
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
      //simply remove it from the array of vertexes, and remove it's edges from our 2d array
      //update currentId (current length) accordingly
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
      //same thing as addedge, except set the edge length to 0
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
      //find the two vertices, and call dijstrka on them
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
      //print the adjacency tree
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
  int distances[currentId];  //distances
  bool visited[currentId]; //if we have visited the vertex already
  int previous[currentId];  // the previous nodes
  
  //loop through our graph
  for(int i = 0; i < currentId; i++){
    if(i == index1){
      //the first index has 0 distance between itself and should not have a previous
      distances[i] = 0;
      visited[i] = false;
      previous[i] = -1;
    }
    else if(graph[i] == NULL){
      // if we have encountered a null vertex, we can basically ignore it
      distances[i] = 1000000;
      visited[i] = true; 
    }
    else{
      //otherwise, set distances to infinity
      distances[i] = 10000;
      visited[i] = false;
    }
  }

  while(true){
    //if we have not visited all the nodes yet, we should keep on going
    bool done = true;
    for(int i = 0; i < currentId; i++){
      if(!visited[i]){
	done = false;
	break;
      }
    }
    if(done){
      break;
    }
    int current = 10000;
    int index = 0;
    for(int i = 0; i < currentId; i++){
      if(!visited[i] && (distances[i] < current)){
	current = distances[i];
	index = i;
      }
    }
    //if there is a shorter alternative, replace it
    for(int i = 0; i < currentId; i++){
      if(arr[index][i] != 0){
	if(current + arr[index][i] < distances[i]){
	  distances[i] = current + arr[index][i];
	  previous[i] = index;
	}
      }
    }
    //we have visited this vertex
    visited[index] = true;
  }
  //print out the shortest distance left
  cout << distances[index2] << endl;

  //make a path vector, and push onto it starting from the rear, as we know the previous vertexes
  vector<vertex*> path;
  int current = index2;

  path.push_back(graph[index2]);
  while(previous[current] != index1){
    path.push_back(graph[previous[current]]);
    current=  previous[current];
  }
  
  path.push_back(graph[index1]);
  //print starting from the end since we pushed from the rear
  for(int i = path.size() - 1; i >= 0; i--){
    cout << path[i]->name << " ";
  }
  cout << endl;
}

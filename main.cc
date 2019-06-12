/* 
    Your main program goes here
*/
#include <iostream>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"

using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();

int main(int argc, char** argv){

    /* start your program */
    nm->interpret("topo.txt");
//    nm->print_all_v();
//    nm->print_all_e();
    Vertex* node = nm->get_all_nodes();
    vector<string> node_v;
    while(node!=NULL){
    node_v.push_back(node->name);
    node=node->next;
    }
//find the number of nodes with odd edges
    int *degree;
    degree = new int [node_v.size()];
    for(int i=0;i<node_v.size();i++)
      degree[i]=0;
    int odd_node=0;
    for(int i=0;i<node_v.size();i++){
      for(int j=0;j<node_v.size();j++){
        if(nm->connected(node_v[i],node_v[j])==0)
          degree[i]++;   
      }
      if(degree[i]%2==1)
        odd_node++;
    }
    for(int i=0;i<node_v.size();i++){
      cout<<"degree of "<< node_v[i]<<" = "<<degree[i]<<endl;
}
   cout << endl <<node_v.size()<<endl;

/*
    Gplot *gp = new Gplot();
    gp->gp_add(nm->elist);
    gp->gp_dump(true);
    gp->gp_export("plot");
*/
    return 0;
}

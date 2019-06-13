/* 
    Your main program goes here
*/
#include <iostream>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"
#include <vector>
#include <string>

using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();
vector<string> result_paths;



int main(int argc, char** argv){
    string current_node("a");
    /* start your program */
    nm->interpret("topo.txt");
//    nm->print_all_v();
//    nm->print_all_e();
    Vertex* node = nm->get_all_nodes();
    vector<string> node_v;//node name
    while(node!=NULL){
      node_v.push_back(node->name);
      node=node->next;
    }
    vector<vector<Edge*>> avail_paths;
    vector<vector<Edge*>> shortest_paths(node_v.size(),vector<Edge*>(node_v.size())); 
    Path *path;
    path=new Path();
    path->append(nm->elist);

//find the number of nodes with odd edges
    int *degree;
    degree = new int [node_v.size()];//degree of each node
    for(int i=0;i<node_v.size();i++)
      degree[i]=0;
    int odd_node_count=0;//# of node with odd degrees


/*    for(int i=0;i<node_v.size();i++){
      for(int j=0;j<node_v.size();j++){
        if(nm->connected(node_v[i],node_v[j])==0){
          nm->connect_r(node_v[i],node_v[j]);
          degree[i]++;
       }   
      }
      if(degree[i]%2==1)
        odd_node_count++;
    }*/

    for(int i=0;i<node_v.size()-1;i++){
      for(int j=i+1;j<node_v.size();j++){
        if(nm->connected(node_v[i],node_v[j])==0){
          if(nm->connected_d(node_v[j],node_v[i])==0)
            nm->connect(node_v[i],node_v[i]);
          else if(nm->connected_d(node_v[i],node_v[j])==0)
            nm->connect(node_v[j],node_v[i]);
          degree[i]++;
          degree[j]++;
       }   
      }
      if(degree[i]%2==1)
        odd_node_count++;
    }
    for(int i=0;i<node_v.size();i++){
      cout<<"degree of "<< node_v[i]<<" = "<<degree[i]<<endl;
}
   cout << "# of nodes is " <<node_v.size()<<endl;
//not Euler (add edge to node with odd degrees and find euler path)
    if(odd_node_count!=0){

//find node with odd degree
    Vertex *odd_degree_node[odd_node_count];
    int od=0;
    for(int i=0;i<node_v.size();i++){
      if(degree[i]%2==1){
        odd_degree_node[od]=nm->vlist[i];
        od++;
        cout <<node_v[i]<<" has odd degree!"<<endl;
      }
    }
        cout<<"# of odd degree node is "<<od<<endl;
//find edge that should be walked several times

//avail_paths = path->find_paths(node_v[2],node_v[3]);
//path->debug();
//    path->debug();

    int s=0;
    for(int i=0;i<od;i=i+2){
        avail_paths = path->find_paths(odd_degree_node[i]->name,odd_degree_node[i+1]->name);
        path->debug();
//        cout<<avail_paths[0].size()<<endl;
        for(int k=0;k<avail_paths.size();k++){
          if(shortest_paths[s].size()>avail_paths[k].size()){
            shortest_paths.at(s)=avail_paths.at(k);
          }
        }     
            s++;
    } 

    for(int i=0;i<od/2;i++){
         for(int n=0;n<shortest_paths[i].size();n++){
         nm->connect_r(shortest_paths.at(i).at(n)->head->name,shortest_paths.at(i).at(n)->tail->name);
//         cout<<shortest_paths.at(i).at(n)->head->name<<shortest_paths.at(i).at(n)->tail->name<<endl;
 }
}
    }
cout<<shortest_paths.size()<<endl;
 //   shortest_paths size problem
    for(int i=0;i<shortest_paths.size();i++){

      for(int j=0;j<shortest_paths[i].size();j++){
     cout<<"2 ";
        for(int k=0;k<node_v.size();k++){ 
          if(shortest_paths.at(i).at(j)->head->name==node_v[k]) cout<<"QQ"<<endl; 
   }
  }
 }

    for(int i=0;i<node_v.size();i++){
      cout<<"degree of "<< node_v[i]<<" = "<<degree[i]<<endl;
}




//     nm->connect_r(shortest_paths[0][0]->head->name,shortest_paths[0][0]->tail->name);
//     nm->print_all_v();
//     nm->print_all_e();

//find euler cycle with and without odd node



/*    for(int i=0;i<dfs_paths.size();i++){
      if(dfs_paths.at(i)->tail->name==dfs_paths.at(i+1)->head->name){
      result_paths.at(result)=dfs_paths.at(i)->head->name;
      result++;
      result_paths.at(result)=dfs_paths.at(i)->tail->name;
      result++;
}
}   */


int tmp_node=0;//# of last node

vector<string> result;
      result.push_back(node_v[0]);
/*    while(nm->elist!=NULL){  
    for(int i=1;i<node_v.size();i++){
      if(nm->connected(current_node,node_v[i])==0){
        nm->disconnect(current_node,node_v[i]);
        nm->disconnect(node_v[i],current_node);
//        result.pushback(node_v[i]);
        current_node = node_v[i];
        
        for(int j=0;j<node_v.size();j++){
          if(nm->connected(current_node,node_v[j])==0&&node_v[j]!=result.back()){
            nm->disconnect(current_node,node_v[i]);
            nm->disconnect(node_v[i],current_node);
            current_node = node_v[j];
}           
}       
    }
   }
}*/


    return 0;

}

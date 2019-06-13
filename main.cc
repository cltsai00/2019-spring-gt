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

vector<string> result;

string find_result(int i,int tmp,string current, vector<string>nn,int *degree);
int count_degree(int*degree);

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
    vector<vector<Edge*>> shortest_paths(1,vector<Edge*>(node_v.size())); 
    Path *path;
    path=new Path();
    path->append(nm->elist);


    int *degree;
    degree = new int [node_v.size()];//degree of each node
    for(int i=0;i<node_v.size();i++)
      degree[i]=0;
//find the number of nodes with odd edges
    int odd_node_count=0;//# of node with odd degrees

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
          if(shortest_paths.at(i).at(j)->head->name==node_v[k]||shortest_paths.at(i).at(j)->tail->name==node_v[k]) degree[k]++; 
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


int tmp_node=0;//# of last node


    result.push_back(node_v[0]);

int total_degree;
//        if(nm->connected(current_node,node_v[1])==0&&node_v[1]!=result.back())
//          find_result(1,tmp_node,current_node,node_v,degree);
//        total_degree=count_degree(degree);

     nm->print_all_e();
/*
   while(total_degree!=0){
      for(int i=0;i<node_v.size();i++){
        if(nm->connected(current_node,node_v[i])==0&&node_v[i]!=result.back()){
          current_node = find_result(i,tmp_node,current_node,node_v,degree);
          }
        else if(nm->connected(current_node,node_v[i])==0&&degree[i]==1){
          current_node = find_result(i,tmp_node,current_node,node_v,degree);
}
        total_degree=count_degree(degree);
//        cout<<"total_degree is "<<total_degree<<endl<<"current_node is "<<current_node<<endl;
//   for(int i=0;i<result.size();i++){
//    cout<<result.at(i)<<"->";
//}
  }
cout<<endl; 
nm->print_all_e();
}*/
   //cout<<"total_degree is "<<total_degree<<endl;

    return 0;

}


string find_result(int i,int tmp,string current, vector<string>nn,int* degree){
        nm->disconnect(current,nn[i]);
        nm->disconnect(nn[i],current);
        result.push_back(nn[i]);
        current = nn[i];
        degree[tmp]--;
        degree[i]--;
        cout<<"current node is"<<current;
        return current; 
      }
int count_degree(int* degree){
    int total=0;
    for(int j=0;j<sizeof(degree);j++)
      total+=degree[j];
    return total;
}

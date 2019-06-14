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

vector<string> result;//record result path
int find_result(int& i,int& tmp_node,string &current, vector<string>nn,int *degree);
int count_degree(int*degree,int i);
int od=0;//# of odd degree node


int main(int argc, char** argv){

    /* start your program */
    nm->interpret("topo.txt");//read the file

    Vertex* node = nm->get_all_nodes();

    vector<string> node_v;//save node name to a vector
    while(node!=NULL){
      node_v.push_back(node->name);
      node=node->next;
    }

    vector<vector<Edge*>> avail_paths;// tmp path
    vector<vector<Edge*>> shortest_paths(10,vector<Edge*>(node_v.size())); ///shortest path
    Path *path;
    path=new Path();

        
    string current_node(node_v[0]);//first node read in .txt us the origin

    int *degree;//degree of each node are initialed to 0
    degree = new int [node_v.size()];
    for(int i=0;i<node_v.size();i++)
      degree[i]=0;


//find the number of nodes with odd edges
   

  int odd_node_count=0;//# of node with odd degrees
    for(int i=0;i<node_v.size()-1;i++){
      for(int j=i+1;j<node_v.size();j++){
        if(nm->connected(node_v[i],node_v[j])==0){
          if(nm->connected_d(node_v[j],node_v[i])==0)
            nm->connect(node_v[i],node_v[i]);//as undirected graph, connect the other direction
          else if(nm->connected_d(node_v[i],node_v[j])==0)
            nm->connect(node_v[j],node_v[i]);//as undirected graph, connect the other direction
          degree[i]++;
          degree[j]++;
        }   
      }

      if(degree[i]%2==1)//count # of node with odd degree 
        odd_node_count++;

    }
    
      for(int i=0;i<node_v.size();i++){
        cout<<"degree of "<< node_v[i]<<" = "<<degree[i]<<endl;
      }

   cout << "# of nodes is " <<node_v.size()<<endl;

//if a graph has nodes with odd degree, it's not Euler (add edge to node with odd degrees )
    if(odd_node_count!=0){

//find node with odd degree
    Vertex *odd_degree_node[odd_node_count];
    for(int i=0;i<node_v.size();i++){
      if(degree[i]%2==1){
        odd_degree_node[od]=nm->vlist[i];
        od++;
        cout <<node_v[i]<<" has odd degree!"<<endl;
      }
    }
        cout<<"# of odd degree node is "<<od<<endl;


//find edge that should be walked several times(match nodes with odd degree)

//find path
    int s=0;
    path->append(nm->elist);
    for(int i=0;i<od;i=i+2){
        avail_paths = path->find_paths(odd_degree_node[i]->name,odd_degree_node[i+1]->name);
        path->debug();

        for(int k=0;k<avail_paths.size();k++){
          if(shortest_paths[s].size()>avail_paths[k].size()){
            shortest_paths.at(s)=avail_paths.at(k);
          }
        }     
            s++;
    } 

//connect nodes matched
    for(int i=0;i<od/2;i++){
         for(int n=0;n<shortest_paths[i].size();n++){
         nm->connect_r(shortest_paths.at(i).at(n)->head->name,shortest_paths.at(i).at(n)->tail->name);
         cout<<shortest_paths.at(i).at(n)->head->name<<shortest_paths.at(i).at(n)->tail->name<<endl;
         }
     }
    }

//record degree after matching
    for(int i=0;i<od/2;i++){
      for(int j=0;j<shortest_paths[i].size();j++){
        for(int k=0;k<node_v.size();k++){ 
          if(shortest_paths.at(i).at(j)->head->name==node_v[k]||shortest_paths.at(i).at(j)->tail->name==node_v[k]) degree[k]++;
   }
  }
 }

    for(int i=0;i<node_v.size();i++){
      cout<<"degree of "<< node_v[i]<<" = "<<degree[i]<<endl;
}


//find euler cycle 

int tmp_node=0;//# of last node

    result.push_back(current_node);//push the origin to reault vector

int total_degree;
    total_degree=count_degree(degree,node_v.size());
    cout<<"total degree:  "<<total_degree<<endl;

  
int ii;      
int back=0;//next node is back or front

//find result path
  for(int i=0;i<total_degree/2;i++) {
      int back=0;
       for( ii=tmp_node;ii<node_v.size();ii++){//next node is back 
        if(nm->connected(current_node,node_v[ii])==0){
          if(degree[ii]>0){
          back=find_result(ii,tmp_node,current_node, node_v, degree);
          break;
       }
    }              
  }
     if(back==0){//next node is front
       for(int k=0;k<node_v.size();k++){
         if(nm->connected(current_node,node_v[k])==0){
           if(degree[k]>0){
             back=find_result(k,tmp_node,current_node, node_v, degree);
             break;
           }
         }
       }
     }
  }

//print result
   cout<<endl<<endl<<endl<<endl<<"-----------------------result-----------------------"<<endl<<endl<<endl<<endl;
 for(int i=0;i<result.size();i++){
       cout << result.at(i)<<" -> ";
      }
  cout<<endl<<endl<<endl<<endl;


//output result.txt
     string output_result = "result.txt";
     ofstream out(output_result.c_str());
     for(int i=0;i<result.size()-1;i++){
       out << result.at(i)<<" -> ";
      }
     out<<result.back();
    return 0;

}

//disconnect edge walkedthrough and push to result vector
int find_result(int &ii,int& tmp_node,string &current_node, vector<string>nn,int* degree){

          nm->disconnect(current_node,nn[ii]);
          nm->disconnect(nn[ii],current_node);
          result.push_back(nn[ii]);
          current_node = nn[ii];
          degree[tmp_node]--;
          degree[ii]--;
          tmp_node=ii;
          return 1;

     
      }

//count total degree
int count_degree(int* degree,int i){
    int total=0;
    for(int j=0;j<i;j++)
      total+=degree[j];
    return total;
}

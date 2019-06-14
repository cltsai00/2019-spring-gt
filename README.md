# Graph-Theory-Project
Graph Theory (EE6622E) in National Cheng Kung University.  
-------  
## 目的  
-------  
在無向圖中，找出中國郵差問題的解  

-------  
## 解題邏輯  
-------  
1. 計算各點的degree，找出圖中odd degree的點，同時將各條edge雙向連接(視為無向)  
2. 對odd degree的node做matching  
3. 找出matching的node的最短路徑  
4. 將找出的路徑在接上一條無向edge  
5. 找到Euler cycle即為解  

-------
## 程式碼實作  
-------
1.將topo.txt以interpret存入建圖  
2.以動態的一維陣列degree存放各點的degree  
3.找出odd degree的點存入Vertex odd_degree_node中  
4.將odd_degree_node中的node兩兩matching，以二維vector avail_paths保存find_path function找到每條路徑，並比較出當  
  中最短的路徑存在二維vector  shortest_paths中  
5.從原點開始往後逐一檢查與其他node有無連接，連接則將兩個點的雙向edge進行disconnect，並將此路徑push到存放結果  
  的vector result當中，並將被連接到的點設為current node，在向後進行檢查，若後面沒有和他相連的點，則在從頭開
  始找下一個點，並重複disconnect及push等動作  
6.將result vector的結果輸出至result.txt  

#### function介紹  
1.find_result: 執行找出result時一直重複執行的disconnect、push動作  
2.count_degree: 計算所有點的degree總數，degree總數的一半為問題解的路徑長度  

-------  
## 執行結果  
-------  
1.input file - topo.txt  


   |a b |  
   |b c |  
   |b d |  
   |b g |  
   |c g |  
   |d e |    
   |d f |    
   |e f |    

------
2.output on terminal   
  ![image](https://github.com/cltsai00/2019-spring-gt/blob/master/figure/result.PNG)

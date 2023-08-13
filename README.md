# 1. Node
## 1.1. Data Private 
``` c++
private:
    char vertex;
    vector<char> edges;
```
## 1.2. Function Public
```c++
public:
    Node(char _vertex, vector<char> _edges);
    char get_vertex();
    vector<char> get_edges();
```
# 2. Graph
## 2.1. Data Private
```c++
vector<Node> nodes;
vector<vector<bool>> matrix;
map<char, vector<char>> adjacency_list;
```
## 2.2. Data Public
```c++
bool symmetria;
bool related;
bool eulerian;
bool hamiltonian;
int degrees = 0;
```
## 2.3. Constructor
```c++
Graph(vector<Node> _nodes)
    {
      nodes = _nodes;

      symmetria = is_symmetrical();
      related = is_related();
      eulerian = is_eulerian();
      hamiltonian = is_hamiltonian();
      make_matrix();
      make_adjacency_list();
    }
```
## 2.4. Functions Private
### 2.4.1. make_matrix()
  > the algorithm works comparing the **nodes.get_edges()**  with the **cmp_vertex**, with the **first for** is obtains the edges each vertex, the **second for** traverse the vector **cmp_vertex**, and with each **vertex** is comparing with the **third for** thats obtains the vertex from **node.get_edges()**. When the comparing returns true the flag is changed and degrees plus 1, too this edge is delete for no comparing again
  ```c++
  for (auto node : nodes)
  {
    for (auto cmp : cmp_vertex)
    {
      flag = false;
      for (int i=0; i < temp.size(); i++)
      {
        if (cmp == temp.at(i))
        {
          flag = true;
          degrees++;
          temp.erase(temp.begin() + i);
          break;
        }
      }
      row.push_back(flag);
    }
    matrix.push_back(row);
    row.clear();
  }
  ```
### 2.4.2. make_adjacency_list()
  > the algorithm use the **nodes.get_vertex()** and **nodes.get_edges()** to make map 
  ```c++
  for (auto node : nodes)
  {
    adjacency_list.insert(std::make_pair(node.get_vertex(), node.get_edges()));
  }
  ```
### 2.4.3. is_symmetrical() 
  > this use the matrix to check if exist symmetria, the idea is each time traverse and check lower cases, so with [ *i >= j* ] we get this 
  ```c++
    for (int i=0; i < matrix.size(); i++)
    {
      for (int j=1; j < matrix.at(i).size(); j++)
      {
        if (i >= j) continue;
        if (matrix[i][j] != matrix[j][i]) return false;
      }
    }

    return true;
  ```
### 2.4.4. is_related()
  > this algorithm obtains all edges of all vertex, clean until there no duplicates, later delete each edges. If the size is equal 0 return true, because all vertex have one edge
  ```c++
  vector<char> list_edges;
  for (const auto& node : adjacency_list) 
  {
    const vector<char>& edges = node .second;
    list_edges.insert(list_edges.end(), edges.begin(), edges.end());
  }
  
  set<char> edges_clean(list_edges.begin(), list_edges.end());
  
  for (auto node : nodes)
  {
    edges_clean.erase(node.get_vertex());
  }

  if (edges_clean.size() == 0) return true;
  else return false;
  ```
### 2.4.5. is_eulerian()
  > this algorithm count the unpair degrees of each vertex, if exist two means that exist road Euler, and if exist zero means that exist circuit Euler
  ```c++
  if (!symmetria || !related) return false;

  int unpair_nodes = 0;

  for (const auto& node : adjacency_list)
  {
    if ((node.second.size() % 2) == 1) unpair_nodes++;
  }

  if (unpair_nodes == 0 || unpair_nodes == 2) return true;

  return false;
  ```
### 2.4.6. is_hamiltonian() -> programming

## 2.5. Functions Public

### 2.5.1. Show functions 
- show_road() this function use vector to show the road, too be circuit
- show_graph() is used to show graph
- show_matrix() is used to show matrix
  
### 2.5.2. Getter Funtions
- do_euler() this function permains getter road or circuit euler
- getter_matrix() this function permains getter matrix
- getter_adjacency_list() this function permains getter adjacency list 
  


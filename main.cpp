#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <algorithm>
#include <stdio.h>

using std::vector;
using std::map;
using std::set;
using std::cout;
using std::cin;
using std::string;

class Node
{
  private:
    char vertex;
    vector<char> edges;

  public:
    Node(char _vertex, vector<char> _edges)
    {
      vertex = _vertex;
      edges = _edges;
    }

    char get_vertex();
    vector<char> get_edges();
};

class Graph {
  private:
    vector<Node> nodes;
    vector<vector<bool>> matrix;
    map<char, vector<char>> adjacency_list;
    bool symmetria;
    bool related;
    bool eulerian;
    bool hamiltonian;
    int degrees = 0;

    bool is_symmetrical();
    bool is_related();
    bool is_eulerian();
    bool is_hamiltonian();

    void make_matrix();
    void make_adjacency_list();

  public:
    Graph(vector<Node> _nodes)
    {
      nodes = _nodes;

      make_adjacency_list();
      related = is_related();

      symmetria = is_symmetrical();
      eulerian = is_eulerian();
      make_matrix();
      //hamiltonian = is_hamiltonian();
    }


    void show_graph();
    void show_matrix();
    void show_road(vector<char>);

    void do_euler();
};

int main()
{
  vector<char> edges;

  // edges = {'B', 'C', 'D'};
  // Node nodeA('A', edges);
  // edges = {'A', 'D'};
  // Node nodeB('B', edges);
  // edges = {'A', 'D'};
  // Node nodeC('C', edges);
  // edges = {'A', 'B', 'C'};
  // Node nodeD('D', edges);
  // Graph graph({nodeA, nodeB, nodeC, nodeD});
  // graph.show_graph();

  // edges = {'B', 'C', 'D', 'E'};
  // Node nodeA('A', edges);
  // edges = {'A', 'D'};
  // Node nodeB('B', edges);
  // edges = {'A'};
  // Node nodeC('C', edges);
  // edges = {'A', 'B', 'E', 'F'};
  // Node nodeD('D', edges);
  // edges = {'A', 'D', 'F'};
  // Node nodeE('E', edges);
  // edges = {'D', 'E'};
  // Node nodeF('F', edges);
  // Graph graph({nodeA, nodeB, nodeC, nodeD, nodeE, nodeF});
  // graph.show_graph();

  // edges = {'B', 'F'};
  // Node nodeA('A', edges);
  // edges = {'A', 'D', 'E', 'F'};
  // Node nodeB('B', edges);
  // edges = {'F', 'D'};
  // Node nodeC('C', edges);
  // edges = {'B', 'C', 'E', 'F'};
  // Node nodeD('D', edges);
  // edges = {'B', 'D'};
  // Node nodeE('E', edges);
  // edges = {'A', 'B', 'C', 'D'};
  // Node nodeF('F', edges);
  // Graph graph({nodeA, nodeB, nodeC, nodeD, nodeE, nodeF});
  // graph.show_graph();

  // edges = {'B', 'C', 'D', 'E'};
  // Node nodeA('A', edges);
  // edges = {'A', 'E'};
  // Node nodeB('B', edges);
  // edges = {'A', 'D'};
  // Node nodeC('C', edges);
  // edges = {'A', 'C'};
  // Node nodeD('D', edges);
  // edges = {'A', 'B'};
  // Node nodeE('E', edges);
  // Graph graph({nodeA, nodeB, nodeC, nodeD, nodeE});
  // graph.show_graph();

  // edges = {'B', 'C'};
  // Node nodeA('A', edges);
  // edges = {'A', 'D', 'F'};
  // Node nodeB('B', edges);
  // edges = {'A', 'E'};
  // Node nodeC('C', edges);
  // edges = {'B', 'F'};
  // Node nodeD('D', edges);
  // edges = {'C', 'F'};
  // Node nodeE('E', edges);
  // edges = {'B', 'D', 'E'};
  // Node nodeF('F', edges);
  // Graph graph({nodeA, nodeB, nodeC, nodeD, nodeE, nodeF});
  // graph.show_graph();

  return 0;
}

char Node::get_vertex()
{
  return vertex;
}

vector<char> Node::get_edges()
{
  return edges;
}

void Graph::show_graph()
{
  for (const auto& node : adjacency_list)
  {
    cout << "Node: " << node.first << "\tEdges: ";
    for (auto edge : node.second)
    {
      cout << edge << " ";
    }
    cout << "\n";
  }

  cout << "\n\n";

  cout << "Information graph\n\n";
  string msg_true = "true", msg_false = "false";

  if (symmetria) cout << "\tSymmetric: \t" << msg_true << "\n";
  else cout << "\tSymmetric: \t" << msg_false << "\n";

  if (related) cout << "\tRelated: \t" << msg_true << "\n";
  else cout << "\tRelated: \t" << msg_false << "\n";

  if (eulerian) cout << "\tEulerian: \t" << msg_true << "\n";
  else cout << "\tEulerian: \t" << msg_false << "\n";

  do_euler();
}

void Graph::show_road(vector<char> road)
{
  for (auto edge : road)
  {
    cout << edge  << "\t";
  }
  cout << "\n";
}

void Graph::make_matrix()
{
  vector<char> cmp_nodes;
  for (auto node : nodes)
  {
    cmp_nodes.push_back(node.get_vertex());
  }

  vector<bool> row;
  bool flag;
  for (auto node : nodes)
  {
    flag = false;
    vector<char> temp = node.get_edges();
    for (auto cmp : cmp_nodes)
    {
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
}

void Graph::make_adjacency_list()
{
  for (auto node : nodes)
  {
    adjacency_list.insert(std::make_pair(node.get_vertex(), node.get_edges()));
  }
}

void Graph::show_matrix()
{
  vector<char> str_nodes;
  cout << "\t";
  for (auto node : nodes)
  {
    str_nodes.push_back(node.get_vertex());
    cout << node.get_vertex() << "\t";
  }

  cout << "\n";
  for (int i=0; i < str_nodes.size(); i++)
  {
    cout << str_nodes[i] << "\t";
    for (auto col : matrix.at(i))
    {
      cout << col << "\t";
    }
    cout << "\n\n";
  }
}

bool Graph::is_symmetrical()
{
  for (int i=0; i < matrix.size(); i++)
  {
    for (int j=1; j < matrix.at(i).size(); j++)
    {
      if (i >= j) continue;
      //printf("(%i, %i) : ", i, j);
      //cout << matrix.at(i).at(j) << " ";
      //printf("(%i, %i) : ", j, i);
      //cout << matrix.at(j).at(i) << "\t\t";
      if (matrix[i][j] != matrix[j][i]) return false;
    }
    //cout << "\n";
  }

  return true;
}

bool Graph::is_related()
{
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
}

bool Graph::is_eulerian()
{
  if (!symmetria || !related) return false;

  int unpair_nodes = 0;

  for (const auto& node : adjacency_list)
  {
    if ((node.second.size() % 2) == 1) unpair_nodes++;
  }

  if (unpair_nodes == 0 || unpair_nodes == 2) return true;

  return false;
}

map<char, vector<char>> update(char start, char end, map<char, vector<char>> list)
{
  for (auto& it : list)
  {
    if (it.first == start)
    {
      int i = 0;
      for (auto edge : it.second)
      {
        if (edge == end) break;
        i++;
      }

      it.second.erase(it.second.begin() + i);
      break;
    }
  }

  for (auto& it : list)
  {
    if (it.first == end)
    {
      int i = 0;
      for (auto edge : it.second)
      {
        if (edge == start) break;
        i++;
      }

      it.second.erase(it.second.begin() + i);
      break;
    }
  }

  return list;
}

void Graph::do_euler()
{
  if (eulerian)
  {
    int unpair_nodes = 0;
    int size = degrees / 2;
    char start, end;
    map<char, vector<char>> temp = adjacency_list;

    for (const auto& node : adjacency_list)
    {
      if ((node.second.size() % 2) == 1) unpair_nodes++;
    }

    if (unpair_nodes == 0)
    {
      cout << "\n\ncircuit euler\n";

      start = nodes[0].get_vertex();
      char no = start;
      vector<char> circuit;
      circuit.push_back(start);

      int i;
      do
      {
        i = 0;
        for (auto& node : temp)
        {
          if (node.first == start)
          {
            if (node.second.at(i) == no && node.second.size() > 2) i = 1;
            end = node.second.at(i);
            temp = update(start, end, temp);
            size--;
            start = end;
            circuit.push_back(start);
            break;
          }
        }
      } while (size > 1);

      circuit.push_back(no);
      show_road(circuit);
    }

    if (unpair_nodes == 2)
    {
      cout << "\n\nroad euler\n";
      vector<char> road;

      for (auto node : adjacency_list)
      {
        if (node.second.size() % 2 == 1)
        {
          start = node.first;
          break;
        }
      }

      road.push_back(start);

      do
      {
        for (auto& node : temp)
        {
          if (node.first == start)
          {
            end = node.second.at(0);
            temp = update(start, end, temp);
            size--;
            start = end;
            road.push_back(start);
            break;
          }
        }
      } while (size > 0);

      show_road(road);
    }
  }
  else
  {
    cout << "Graph NO eulerian\n";
  }
}

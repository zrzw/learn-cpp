/*
 * graph.cpp
 * mini representation of an undirected graph
 *
 */

#include <iostream>
#include <vector>
#include <map>

struct Graph{
  std::vector<char> nodes;
  std::map<char, std::vector<char> > paths;
};

void init_graph(struct Graph& g, std::vector<char> nodes)
{
  g.nodes = nodes;
  for(auto n : g.nodes){
    g.paths.insert(std::pair<char, std::vector<char> >(n, {}));
  }
  return;
}

void add_path(struct Graph& g, char node1, char node2)
{
  g.paths.at(node1).push_back(node2);
  g.paths.at(node2).push_back(node1);
}


/* ostream of all the nodes & paths in the graph */
std::ostream& operator<<(std::ostream& os, const struct Graph& g)
{
  for(auto n: g.nodes){
    os << n << ":";
    for(auto p: g.paths.at(n))
      os << p << ",";
    os << "\n";
  }
  return os;
}

/* read in a (a, b) pair specifying a path between nodes */
std::istream& operator>>(std::istream& is, struct Graph& g)
{
  char c;
  char node1, node2;
  if(is>>c && c == '('){
    is >> node1;
    if(is>>c && c == ','){
      is >> c;
      if(c == ' ')
        is >> node2;
      else
        node2 = c;
      if(is>>c && c == ')'){
        add_path(g, node1, node2);
        return is;
      }
    }
  }
  return is;
}

bool is_in(const std::vector<char>& l, char c)
{
  for(auto a: l){
    if(a == c)
      return true;
  }
  return false;
}

bool path(const struct Graph& g, char from, char to)
{
  std::vector<char> open, closed;
  open.push_back(from);
  while(!open.empty()){
    char test = open.back();
    open.pop_back();
    if(test == to)
      return true;
    else
      closed.push_back(test);
    for(auto node: g.paths.at(test)){
      //add to open list if not already in closed
      if(!is_in(closed, node))
        open.push_back(node);
    }
  }
  return false;
}

int main()
{
  struct Graph g;
  std::vector<char> my_nodes {'a', 'b', 'c', 'd', 'e', 'f'};
  init_graph(g, my_nodes);
  add_path(g, 'a', 'b');
  add_path(g, 'c', 'a');
  std::cout << "add a node in the format (c, d): ";
  std::cin >> g;
  std::cout << g;
  std::cout << "is there a path from... " << std::endl;
  char from, to;
  std::cin >> from;
  std::cout << "to...";
  std::cin >> to;
  if(path(g, from, to))
    std::cout << "yes" << std::endl;
  else
    std::cout << "no" << std::endl;
  return 0;
}

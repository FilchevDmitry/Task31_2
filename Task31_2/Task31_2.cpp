#include<iostream>
#include<vector>
#include<unordered_set>
 
struct Edge {
        int src, dest;
    };

class IGraph 
{
public:
   
    virtual ~IGraph() {}
    IGraph() {};
    IGraph(IGraph* _oth) {};
    virtual void AddEdge(int from, int to) = 0; // Метод принимает вершины начала и конца ребра и добавляет ребро
    virtual int VerticesCount() const = 0; // Метод должен считать текущее количество вершин
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0; // Для конкретной вершины метод выводит в вектор “вершины” все вершины, в которые можно дойти по ребру из данной
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0; // Для конкретной вершины метод выводит в вектор “вершины” все вершины, из которых можно дойти по ребру в данную
};
class ListGraph: IGraph
{
private:
    std::vector<std::vector<int>> adjList;
public:
    ListGraph(std::vector<Edge> const& edges, int n)
    {
        adjList.resize(n);
        for (auto& edge : edges)
        {
            adjList[edge.src].push_back(edge.dest);
        }
    }
    void printGraph(ListGraph const& graph, int n)
    {
        for (int i = 0; i < n; i++)
        {
            std::cout << i << " --> ";
            for (auto v : graph.adjList[i]) {
                std::cout << v << " ";
            }
            std::cout << std::endl;
        }
    }
    virtual void AddEdge(int from, int to)
    {

    }
    virtual int VerticesCount()const
    {
        return 0;
    }
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const
    {}
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices)const
    {}
};
class MatrixGraph :IGraph
{
private:

public:

};
int main()
{
    // vector ребер Graph согласно схеме выше.
  // Обратите внимание, что vector инициализации в приведенном ниже формате будет
  // нормально работает в C++11, C++14, C++17, но не работает в C++98.
    std::vector<Edge> edges =
    {
        {0, 1}, {1, 2}, {2, 0}, {2, 1}, {3, 2}, {4, 5}, {5, 4}
    };

    // общее количество узлов в Graph (от 0 до 5)
    int n = 6;

    // построить Graph
    ListGraph graph(edges, n);

    // вывести представление списка смежности Graph
    graph.printGraph(graph, n);

    return 0;
}

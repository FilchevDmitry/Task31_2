﻿#include<iostream>
#include<vector>
using namespace std;

struct Vertex
{
    int number;
    Vertex* next;
};
struct Edge
{
    int start, end;
};
class IGraph 
{
public:
    
    virtual ~IGraph() {}
    IGraph() {};
    IGraph(IGraph* _oth) {};
    virtual void AddEdge(int from, int to) = 0; // Метод принимает вершины начала и конца ребра и добавляет ребро
    virtual int VerticesCount() const = 0; // Метод должен считать текущее количество вершин
    virtual void GetNextVertices(int vertex, vector<int>& vertices) const = 0; // Для конкретной вершины метод выводит в вектор “вершины” все вершины, в которые можно дойти по ребру из данной
    virtual void GetPrevVertices(int vertex, vector<int>& vertices) const = 0; // Для конкретной вершины метод выводит в вектор “вершины” все вершины, из которых можно дойти по ребру в данную
};
class ListGraph: public IGraph
{
private:
    int num_nodes;
    Vertex* getNewVertex(int _number, Vertex* ver)
    {
        Vertex* node = new Vertex;
        node->number = _number;
        node->next = ver;
        return node;
    }
public:
    Vertex** head;
    ListGraph(Edge _edges[], int knot, int rib)
    {
        head = new Vertex * [knot];
        this->num_nodes = knot;
        for (int i = 0; i < knot; i++)
        {
            head[i] = nullptr;
        }
        for (int i = 0; i < rib; i++)
        {
            Vertex* newNode = getNewVertex(_edges[i].end, head[_edges[i].start]);
            head[_edges[i].start] = newNode;
        }
    };
    void printGraph()
    {
        for (int i = 0; i < num_nodes; i++)
        {
            cout << i;
            Vertex* ptr = head[i];
            while (ptr != nullptr)
            {
                cout << " -> " << ptr->number;
                ptr = ptr->next;
            }
            cout << endl;
        }
    }
    virtual void AddEdge(int from, int to) override
    {
        Vertex* newNode = getNewVertex(to, head[from]);
        head[from] = newNode;
    }
    virtual int VerticesCount()const override
    {
        return num_nodes;
    }
    virtual void GetNextVertices(int vertex, vector<int>& vertices) const 
    {
        Vertex* ptr = head[vertex];
        while (ptr != nullptr)
        {
            vertices.push_back(ptr->number);
            ptr = ptr->next;
        }
    }
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices)const override
    {
        for (int i = 0; i < num_nodes; i++)
        {
      
            Vertex* ptr = head[i];
            while (ptr != nullptr)
            {
                if (ptr->number == vertex)
                {
                    vertices.push_back(i);
                }
                ptr = ptr->next;
            }
            
        }
    }
   virtual ~ListGraph()
    {
        for (int i = 0; i < num_nodes; i++)
        {
            delete[] head[i];
        }
        delete[] head;
       
    }
};
class MatrixGraph :IGraph
{
private:
    int num_nodes;
    std::vector<std::vector<int>> adjList;
public:
    MatrixGraph(Edge _edges[],int N, int n)
    {
        num_nodes = N;
        adjList.resize(N);
        for (int i = 0; i < adjList.size(); i++)
        {
            adjList[i].resize(N,0);
        }
        for (int i=0; i<n;i++)
        {
            int k=_edges[i].start;
            int m=_edges[i].end;
            adjList[k][m] = 1;
        }
    }
    void printGraph(MatrixGraph const& graph, int n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                std::cout << graph.adjList[i][j];
            }
            std::cout << std::endl;
        }
    }
    virtual void AddEdge(int from, int to)
    {
        adjList[from][to] = 1;
    }
    virtual int VerticesCount()const
    {
        return num_nodes;
    }
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const
    {
            for (int j = 0; j < adjList[vertex].size(); j++)
            {
                if (adjList[vertex][j] != 0)
                {
                    vertices.push_back(j);
                }
            }
    }
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices)const
    {
        for (int i = 0; i < num_nodes; i++)
        {
            for (int j = 0; j < adjList[i].size(); j++)
            {
                if (j==vertex && adjList[i][j]==1)
                {
                    vertices.push_back(i);
                }
            }  
        }
    }
};
int main()
{
    vector<int> vertices;
    int temp = 0;
  Edge edges[] =
    {
        {0, 1}, {1, 2}, {2, 0}, {2, 1}, {3, 2}, {4, 5}, {5, 4}
    };
    int N = 6;
    int n = sizeof(edges) / sizeof(edges[0]);
    ListGraph graph(edges,N, n);
    MatrixGraph g(edges, N,n);
    graph.printGraph();
    g.printGraph(g, N);
    cout << "Input number vertex ";
    cin >> temp;
    //graph.GetNextVertices(temp, vertices);
    //graph.GetPrevVertices(temp, vertices);
    /*g.GetNextVertices(temp, vertices);*/
    g.GetPrevVertices(temp, vertices);
    return 0;
}


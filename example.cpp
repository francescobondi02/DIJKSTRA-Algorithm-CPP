#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#define INFY 9999999
// Define the number of nodes in the field
#define N_NODES 3

using namespace std;

struct Node
{
    int id;
    int f;
    int J;
};

void printGraph(int graph[][N_NODES])
{
    for (int i = 0; i < N_NODES; i++)
    {
        for (int j = 0; j < N_NODES; j++)
        {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}

bool isAdiacent(int id1, int id2, int graph[][N_NODES])
{
    if (graph[id1 - 1][id2 - 1] != 0)
    {
        // A link has been found
        return true;
    }
    return false;
}

int p(int j, int k, int graph[][N_NODES]) // Function that return the cost of a link
{
    return graph[j - 1][k - 1];
}

void setup(Node nodes[], int ids[], int graph[][N_NODES], vector<Node> &S, vector<Node> &T)
{
    for (int i = 0; i < N_NODES; i++)
    {
        Node temp;
        temp.id = ids[i];
        if (ids[i] == 1)
        {
            // It's the first node
            temp.f = 0;
            temp.J = 0;
            S.push_back(temp);
        }
        else if (isAdiacent(ids[i], 1, graph))
        {
            temp.f = p(1, ids[i], graph);
            temp.J = 1;
            T.push_back(temp);
        }
        else
        {
            temp.f = INFY;
            T.push_back(temp);
        }
        nodes[i] = temp;
    }
}

void printData(Node nodes[])
{
    for (int i = 0; i < N_NODES; i++)
    {
        cout << "Nodo " << nodes[i].id << " ----- F:" << nodes[i].f << " / J:" << nodes[i].J << endl;
    }
}

int main()
{
    // Define the matrix
    int graph[N_NODES][N_NODES] = {};
    int ids[N_NODES] = {1, 2, 3};
    Node nodes[N_NODES] = {};

    vector<Node> S; // Starting Node (1)
    vector<Node> T; // Other nodes (2, 3)

    // Graph creation
    for (int i = 0; i < N_NODES; i++)
    {
        for (int j = i + 1; j < N_NODES; j++)
        {
            if (ids[i] != ids[j])
            {
                cout << "What is the weight of the connection between: " << ids[i] << " and " << ids[j] << endl;
                cin >> graph[i][j];
                // It should be specular
                graph[j][i] = graph[i][j];
            }
        }
    }

    printGraph(graph);

    // Setup of algorithm
    setup(nodes, ids, graph, S, T);

    printData(nodes); // Fino a qui tutto bene
    // Should start the algorithm now
    while (T.size() > 0)
    {
        // Find the minimum in T (by f)
        Node min = T[0];
        vector<Node>::iterator idMin;
        idMin = T.begin();
        for (int i = 1; i < T.size(); i++)
        {
            if (T[i].f < min.f)
            {
                // E' il nuovo minimo
                min = T[i];
                idMin = T.begin() + i;
            }
        }

        // Lo togliamo da T (toglie bene il minore prima)
        // cout << "Sto per togliere: " << min.id;
        T.erase(idMin);
        S.push_back(min);

        if (T.size() == 0)
            break;

        // Etichetta permanente
        for (int i = 0; i < T.size(); i++)
        {
            if (isAdiacent(T[i].id, min.id, graph) && (T[i].f > min.f + p(T[i].id, min.id, graph)))
            {
                T[i].f = min.f + p(T[i].id, min.id, graph);
                T[i].J = min.id;
            }
        }
    }

    // Stampo qualche info
    for (int i = 0; i < S.size(); i++)
    {
        cout << "ID NODO: " << S[i].id << " - F: " << S[i].f << " - J: " << S[i].J << endl;
    }

    return 0;
}
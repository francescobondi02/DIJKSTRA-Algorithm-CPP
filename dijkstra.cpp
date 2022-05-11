#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#define INFY 9999999
// Define the number of nodes in the field
#define N_NODES 5

using namespace std;

struct Node
{
    int id;
    int f;
    int J;
};

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

void setup(Node nodes[], vector<int> &ids, int graph[][N_NODES], vector<Node> &S, vector<Node> &T)
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

void setupIds(vector<int> &ids)
{
    for (int i = 0; i < N_NODES; i++)
    {
        ids.push_back(i + 1);
    }
}

int main()
{
    // Define the matrix
    int graph[N_NODES][N_NODES] = {};
    vector<int> ids;
    Node nodes[N_NODES] = {};

    vector<Node> S; // Starting Node (1)
    vector<Node> T; // Other nodes (2, 3)

    setupIds(ids);

    // Graph creation
    for (int i = 0; i < N_NODES; i++)
    {
        for (int j = i + 1; j < N_NODES; j++)
        {
            if (ids[i] != ids[j])
            {
                // One of the main hypothesys of Dijkstra's Algorithm is that costs NEEDS to be > 0 (not negative)
                do
                {
                    cout << "What is the cost of the connection between: " << ids[i] << " and " << ids[j] << endl;
                    cin >> graph[i][j];
                } while (graph[i][j] < 0);

                // It should be specular (non-oriented graph)
                graph[j][i] = graph[i][j];
            }
        }
    }

    // Setup of algorithm
    setup(nodes, ids, graph, S, T);

    // Body of the algorithm
    while (T.size() > 0)
    {
        // Find the minimum in T (by f)
        Node min = T[0];
        vector<Node>::iterator idMin;
        idMin = T.begin();
        // Search for the min element in the T vector
        for (int i = 1; i < T.size(); i++)
        {
            if (T[i].f < min.f)
            {
                min = T[i];
                idMin = T.begin() + i;
            }
        }

        // Erase the node from the T vector and add it in the S vector (has been analysed)
        T.erase(idMin);
        S.push_back(min);

        if (T.size() == 0)
            break;

        // We assign a permanent label to the nodes adiacent to the min one
        for (int i = 0; i < T.size(); i++)
        {
            if (isAdiacent(T[i].id, min.id, graph) && (T[i].f > min.f + p(T[i].id, min.id, graph)))
            {
                T[i].f = min.f + p(T[i].id, min.id, graph);
                T[i].J = min.id;
            }
        }
    }

    // Final Infos
    for (int i = 0; i < S.size(); i++)
        cout << "To reach NodeID " << S[i].id << ", the shortest trip goes through NodeID " << S[i].J << " and has a cost of " << S[i].f << endl;

    return 0;
}
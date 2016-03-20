#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include "tokenizer.h"
#include "graph.h"

using namespace std;

template<typename T>
void resizeFill(int count, vector<T>& v, const T& val)
{
    v.resize(count);
    fill(v.begin(), v.end(), val);
}

class TopoGraph: public Graph<string>
{
public:
    vector<NodeIndex> topoSort()
    {
        int nodeCount = _nodeNames.size();

        resetData();    
        vector<NodeIndex> solvedNodes;
        int curIndex = 0;
        for (int i = 0; i < nodeCount; i++)
        {
            if (inDegrees[i] == 0)
                solvedNodes.push_back(i);
        }
        
        while (solvedNodes.size() < nodeCount && curIndex < solvedNodes.size())
        {
            NodeIndex curNode = solvedNodes[curIndex++];
            for (auto edge: _edgeWeights[curNode])
            {
                if (--inDegrees[edge.first] == 0)
                    solvedNodes.push_back(edge.first);
            }            
        }
        
        return solvedNodes;
    }
    
private:

    void resetData()
    {
        int nodeCount = _nodeNames.size();
        resizeFill(nodeCount, inDegrees, 0);
        for (int i = 0; i < nodeCount; i++)
        {
            for (auto edge: _edgeWeights[i])
            {
                inDegrees[edge.first]++;
            }            
        }
    }

    vector<NodeIndex> inDegrees;
};

TopoGraph graph;

bool parseGraph(const string& line)
{
    Tokenizer tokenizer(line, "-> \t\n\r\b");
    string token = tokenizer.nextToken();
    if (token.length() == 0)
        return false;
    string start = token;
    token = tokenizer.nextToken();
    if (token.length() == 0)
        return false;
    string end = token;
    
    graph.addEdge(start, end, 1);
    return true;
}


void solve()
{
    auto nodes = graph.topoSort();
    if (nodes.size() == 0)
        return;
        
    if (nodes.size() != graph.getNodeCount())
    {
        cout << "Rings!" << endl;
        return;
    }
    
    cout << graph.getNodeName(nodes[0]);    
    for (int i = 1; i < nodes.size(); i++)
    {
        cout << "->" << graph.getNodeName(nodes[i]);
    }
    cout << endl;
}

int main()
{
    string line;
    do
    {
        getline(cin, line);
    } while (parseGraph(line));
    solve();    
    return 0;
}

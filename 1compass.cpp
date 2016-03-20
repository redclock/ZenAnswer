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

class PathGraph: public Graph<char>
{
public:
    int getShortestPath(NodeIndex startIndex, NodeIndex toIndex, vector<NodeIndex>& path)
    {
        if (startIndex == toIndex)
            return 0;

        resetData();    

        minWeights[startIndex] = 0;
        NodeIndex curNode = startIndex;
        
        for (int i = 0; i < _nodeNames.size(); i++)
        {
            nodeSolved[curNode] = true;
            updateNeighbour(curNode);
            curNode = getMinUnsolvedNode();
            if (curNode < 0)
                return -1;
                
            if (curNode == toIndex)
            {
                generatePath(toIndex, path);
                return minWeights[toIndex];
            }
        }
        
        return -1;        
    }
    
private:

    void resetData()
    {
        int nodeCount = _nodeNames.size();
        resizeFill(nodeCount, minWeights, -1);
        resizeFill(nodeCount, nodeSolved, false);
        resizeFill(nodeCount, preNode, -1);
    }

    void updateNeighbour(NodeIndex curNode)
    {
        int curWeight = minWeights[curNode];
        for (auto edge: _edgeWeights[curNode])
        {
            NodeIndex node = edge.first;
            int weight = edge.second;
            if (!nodeSolved[node])
            {
                int oldWeight = minWeights[node];
                int newWeight = curWeight + weight;
                if (oldWeight < 0 || newWeight < oldWeight)
                { 
                    minWeights[node] = newWeight;
                    preNode[node] = curNode;
                }
            }
        }
    }
    
    NodeIndex getMinUnsolvedNode()
    {
        int minWeight = -1;
        NodeIndex minNode = -1;
        int nodeCount = _nodeNames.size();

        for (int i = 0; i < nodeCount; i++)
        {
            if (nodeSolved[i] || minWeights[i] < 0) continue;
            if (minWeight < 0 || minWeights[i] < minWeight)
            {
                minWeight = minWeights[i];
                minNode = i;
            }
        }
        return minNode;
    }
    
    void generatePath(NodeIndex node, vector<NodeIndex>& path)
    {
        while (preNode[node] >= 0)
        {
            path.insert(path.begin(), preNode[node]);
            node = preNode[node];
        }
    }

    vector<int> minWeights;
    vector<bool> nodeSolved;
    vector<NodeIndex> preNode;
        
};

PathGraph graph;

void parseGraph(const std::string& line)
{
    Tokenizer tokenizer(line);
    while (tokenizer.hasMore())
    {
        string token = tokenizer.nextToken();
        if (token.length() > 2)
        {
            graph.addEdge(token[0], token[1], atoi(token.substr(2).c_str()));
        }
    }
}

vector<NodeIndex> parseQuery(const string& line)
{
    Tokenizer tokenizer(line, "-> \t\n\r\b");
    vector<NodeIndex> nodes;
    
    while (tokenizer.hasMore())
    {
        string token = tokenizer.nextToken();
        if (token.length() > 0)
        {
            NodeIndex index = graph.getNodeIndex(token[0]);
            if (index < 0)
            {
                cout << "Node " << token[0] << " not exists!" << endl;
                return vector<NodeIndex>();
            }
            nodes.push_back(index);
        }
    }
    return nodes;
}

void solvePath(const vector<NodeIndex>& nodes)
{
    if (nodes.size() < 2)
        return;
    
    int totalWeight = 0;
    vector<char> totalPath;    
    for (int i = 1; i < nodes.size(); i++)
    {
        vector<NodeIndex> path;
        int weight = graph.getShortestPath(nodes[i - 1], nodes[i], path);
        if (weight < 0)
        {
            cout << "No path!" << endl;
            return;
        }
        else
        {
            for (auto p: path)
            {
                totalPath.push_back(p);
            }
            totalWeight += weight;
        }
    }
    cout << "Total length is: " << totalWeight << endl;
    cout << "Path: ";
    for (auto p: totalPath)
    {
        cout << graph.getNodeName(p) << "->";        
    }
    cout << graph.getNodeName(nodes.back()) << endl;         
}

int main()
{
    string edgesLine;
    getline(cin, edgesLine);
    parseGraph(edgesLine);

    //graph.dump();
    
    string queryLine;
    getline(cin, queryLine);
    vector<NodeIndex> queryNodes = parseQuery(queryLine);
    solvePath(queryNodes);    
    return 0;
}

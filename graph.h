#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

typedef int NodeIndex;

template <typename NodeName> 
class Graph
{
public:
    Graph()
    {

    }

    void addEdge(NodeName fromName, NodeName toName, int weight)
    {
        NodeIndex fromIndex = getOrCreateNodeIndex(fromName);
        NodeIndex toIndex = getOrCreateNodeIndex(toName);
        _edgeWeights[fromIndex][toIndex] = weight;
    }
    
    NodeIndex getNodeIndex(NodeName name)
    {
        auto itr = find(_nodeNames.begin(), _nodeNames.end(), name);
        return (itr == _nodeNames.end()) ? -1 : itr - _nodeNames.begin();
    }

    NodeName getNodeName(NodeIndex index)
    {
        return _nodeNames[index];
    }
    
    NodeIndex getOrCreateNodeIndex(NodeName name)
    {
        NodeIndex index = getNodeIndex(name);
        if (index >= 0) 
            return index;
        else
            return createNode(name);
    }
    
    size_t getNodeCount() const { return _nodeNames.size(); }
    
    void dump()
    {
        cout << "Nodes: " << _nodeNames.size() << endl;
        for (size_t i = 0; i < _nodeNames.size(); i++)
        {
            cout << "  " << _nodeNames[i] << ": ";
            for (auto weights: _edgeWeights[i])
            {
                cout << _nodeNames[weights.first] << " " << weights.second << " ";
            }
            cout << endl;
        }
    }
    
protected:
    NodeIndex createNode(NodeName name)
    {
        _nodeNames.push_back(name);
        _edgeWeights.push_back(map<NodeIndex,int>());
        return _nodeNames.size() - 1;
    }   

    vector<NodeName> _nodeNames;
    vector<map<NodeIndex,int>> _edgeWeights;
};

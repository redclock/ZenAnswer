#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include "tokenizer.h"
#include "graph.h"

class Map
{
public:
    Map(int width, int height)
    : _width(width), _height(height),
    _occupied(width * height)
    {
        fill(_occupied.begin(), _occupied.end(), false);
    }
    
    void setOccupied(int x, int y, bool b)
    {
        _occupied[y * _width + x] = b;
    }
    
    bool getOccupied(int x, int y) const
    {
        return _occupied[y * _width + x];
    }
    
    bool isValidCoord(int x, int y) const
    {
        return x >= 0 && x < _width && y >= 0 && y < _height;
    }
     
private:
    int _width;
    int _height;
    vector<bool> _occupied;
};

struct Direction
{
    char name;
    int dx;
    int dy;
};

const Direction DIRS[4] = {
    { 'E', 1, 0 },
    { 'S', 0, -1 },
    { 'W', -1, 0 },
    { 'N', 0, 1 },
};

int getDirIndex(char dir)
{
    for (int i = 0; i < 4; i++)
    {
        if (DIRS[i].name == dir)
            return i;
    }
    return -1;
} 

class Rover
{
public: 
    Rover(Map& map, int x, int y, int dirIndex)
    : _map(map), _dead(false),
    _x(x), _y(y), _dirIndex(dirIndex),
    _curCommandIndex(0)
    {
    }
    
    void setCommands(const string& str)
    {
        _commands = str;
        _curCommandIndex = 0;
    }
    
    void executeOne()
    {
        if (isFinished())
        {
            cout << "END";
            return;
        }
            
        char cmd = _commands[_curCommandIndex];
        cout << cmd << "-";
        bool stay = false;
        switch (cmd)
        {
        case 'M': stay = !step(1); break;
        case 'B': stay = !step(-1); break;
        case 'L': turn(-1); break;
        case 'R': turn(1); break;
        }
        
        if (_dead)
        {
            cout << "DEAD";
        }
        else if (stay)
        {
            cout << "STAY";
        }
        else
        {
            _curCommandIndex++;
            cout << _x << "," << _y << "," << DIRS[_dirIndex].name;
        }
    }
    
    bool isFinished() const 
    {
        return _dead || _curCommandIndex >= _commands.length();
    }
    
private:
    void turn(int right)
    {
        _dirIndex = (_dirIndex + right) % 4;
    }
    
    bool step(int forward)
    {
        const Direction& dir = DIRS[_dirIndex];
        int destx = _x + dir.dx * forward; 
        int desty = _y + dir.dy * forward;
        bool isValidDest = _map.isValidCoord(destx, desty);
        if (isValidDest && _map.getOccupied(destx, desty))
            return false;
            
        _map.setOccupied(_x, _y, false);
        _x = destx;
        _y = desty;

        if (isValidDest)
            _map.setOccupied(_x, _y, true);
        else
            _dead = true;

        return true;
    }

    bool _dead;
    int _x;
    int _y;
    int _dirIndex; 
    Map& _map;
    string _commands;
    int _curCommandIndex;    
};

bool parseMapSize(const string& line, int& width, int& height)
{
    Tokenizer tokenizer(line, ", \t\n\r\b");
    string token = tokenizer.nextToken();
    if (token.length() == 0)
        return false;
    width = atoi(token.c_str());
    token = tokenizer.nextToken();
    if (token.length() == 0)
        return false;
    height = atoi(token.c_str());
    return true;
}

bool parseRoverState(const string& line, int& x, int& y, int& dir)
{
    Tokenizer tokenizer(line, ", \t\n\r\b");

    string token = tokenizer.nextToken();
    if (token.length() == 0)
        return false;
    x = atoi(token.c_str());

    token = tokenizer.nextToken();
    if (token.length() == 0)
        return false;
    y = atoi(token.c_str());

    token = tokenizer.nextToken();
    if (token.length() == 0)
        return false;
    char dirName = token[0];
    dir = getDirIndex(dirName);
    return dir >= 0;
}

bool isAllFinished(const vector<Rover>& rovers)
{
    for (auto rover: rovers)
        if (!rover.isFinished()) return false;
    return true;
}

int main()
{
    string line;
    getline(cin, line);
    int width, height;
    if (!parseMapSize(line, width, height))
    {
        cout << "Error parsing map size" << endl;
        return -1;
    }
    Map map(width, height);
    vector<Rover> rovers;
    do
    {
        getline(cin, line);
        int x, y, dir;
        if (!parseRoverState(line, x, y, dir)) break;
        rovers.push_back(Rover(map, x, y, dir));
        getline(cin, line);
        rovers.back().setCommands(line);
    } while (true);
    
    while (!isAllFinished(rovers)) 
    {
        for (int i = 0; i < rovers.size(); i++)
        {
            cout << i << ": ";
            rovers[i].executeOne();
            cout << "\t";
        }
        cout << endl;
    }
    return 0;
}
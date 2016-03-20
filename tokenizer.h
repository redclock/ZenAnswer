#include<string>
#include<ctype.h>

class Tokenizer
{
public:
    Tokenizer(const std::string& s, const std::string& sep = " \t\n\r\b"): _str(s), _sep(sep), _curIndex(0)
    {
    }
    
    bool isSep(char c) const
    {
        return _sep.find(c) != std::string::npos;    
    }
    
    std::string nextToken()
    {
        while (hasMore() && isSep(_str[_curIndex])) 
            _curIndex++;
        std::string token;
        while (hasMore() && !isSep(_str[_curIndex])) 
            token += _str[_curIndex++];
        return token;       
    }
    
    bool hasMore() const 
    {
        return _curIndex < _str.length();
    }

private:
    std::string _str;
    std::string _sep;
    int _curIndex;
};
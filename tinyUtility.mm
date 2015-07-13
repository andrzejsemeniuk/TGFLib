

#import "tinyUtility.h"

namespace tiny
{
    using namespace std;
    
    
    std::string to_string_with_comma (int n, char c)  {
        std::string number = boost::lexical_cast<std::string>(n);
        std::string r;
        r.reserve(number.length()*1.5);
        int index = 0;
        for(auto i = number.rbegin(); ; ) {
            r += *i;
            index++;
            i++;
            if (i == number.rend())
                break;
            if (index%3==0) {
                r += c;
                index=0;
            }
        }
        std::reverse(r.begin(),r.end());
        return r;
    }

    
   
    

}
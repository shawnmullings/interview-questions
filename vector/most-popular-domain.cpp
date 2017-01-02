
/** @file most-popular-domain.cpp
 *  @brief 
 *
 *  Given a list of URLs, find the most popular domain
 *  
 *  For example:
 *  
 *  http://google.com/foo/bar
 *  http://www.example.net/baz
 *  http://foo.com/a/b?c=d
 *  http://test.example.net/cat/dog
 *  http://foo.com/a/b?d=c&f=g
 *  http://example.net/hamster
 *  
 *  returns: example.net
 *
 *  @author Shawn Mullings (@shawnmullings)
 *  @bug No known bugs.
 */


/* -- Includes -- */

#include <iostream>
#include <string>
#include <algorithm> /* find() */
#include <vector>
#include <map>

/* -- End Includes -- */

class Uri
{
    public:

    std::wstring QueryString, Path, Protocol, Host, Port;

    /* Constructor */
    Uri(){}

    /* Destructor */
    ~Uri(){}

    static Uri Parse(const std::wstring &uri)
    {
        Uri result;

        typedef std::wstring::const_iterator iterator_t;

        if (uri.length() == 0)
            return result;

        iterator_t uriEnd = uri.end();

        /* Get query starting point */
        iterator_t queryStart = std::find(uri.begin(), uriEnd, L'?');

        /* Get protocol starting and ending point */
        iterator_t protocolStart = uri.begin();
        iterator_t protocolEnd = std::find(protocolStart, uriEnd, L':');

        if (protocolEnd != uriEnd)
        {
            std::wstring prot = &*(protocolEnd);
            if ((prot.length() > 3) && (prot.substr(0, 3) == L"://"))
            {
                result.Protocol = std::wstring(protocolStart, protocolEnd);
                protocolEnd += 3;
            }
            else
                /* No protocal exists */
                protocolEnd = uri.begin();
        }
        else
            /* No protocal exists - start at url begining */
            protocolEnd = uri.begin();

        /* Get host starting point */
        iterator_t hostStart = protocolEnd;
        iterator_t pathStart = std::find(hostStart, uriEnd, L'/');

        /* Check for url port */
        iterator_t hostEnd = std::find(protocolEnd, 
            (pathStart != uriEnd) ? pathStart : queryStart,
            L':');

        result.Host = std::wstring(hostStart, hostEnd);

        /* If port exists get port number */
        if ((hostEnd != uriEnd) && ((&*(hostEnd))[0] == L':'))
        {
            hostEnd++;
            iterator_t portEnd = (pathStart != uriEnd) ? pathStart : queryStart;
            result.Port = std::wstring(hostEnd, portEnd);
        }

        /* Set results uri path */
        if (pathStart != uriEnd)
            result.Path = std::wstring(pathStart, queryStart);

        /* Set results query string */
        if (queryStart != uriEnd)
            result.QueryString = std::wstring(queryStart, uri.end());

        return result;

    }
};

/**
*   Locate most popular domain (host)
*   
*   @param vector of wstrings
*   @return wstring of most popular domain
*/
std::wstring most_popular_domain(const std::vector<std::wstring> &urlsList){

     /* Map <wstring, int> of host and count */
    std::map<std::wstring, int> hostMap;

     /* Count associated with most seen host */
    int highestCount(0);

     /* Most seen host */
    std::wstring highestCountURL;

    /* Loop through vector of urls adding host to map, incrimenting host count, save host with hight count */
    for (std::vector<std::wstring>::const_iterator it = urlsList.begin(); it != urlsList.end(); ++it){
        Uri tUri = Uri::Parse((*it));
        hostMap[tUri.Host]++;

        if(highestCount < hostMap[tUri.Host]){
            highestCountURL = tUri.Host;
            highestCount = hostMap[tUri.Host];
        }
    }

    /* Return most seen host */
    return highestCountURL.data();
}


int main(int argc, char const *argv[])
{
    /* Create vector of wstrings to store urls */
    std::vector<std::wstring> urlsList;

    /* Add urls to vector */
    urlsList.push_back(L"http://google.com/foo/bar");
    urlsList.push_back(L"http://www.example.net/baz");
    urlsList.push_back(L"http://foo.com/a/b?c=d");
    urlsList.push_back(L"http://test.example.net/cat/dog");
    urlsList.push_back(L"http://foo.com/a/b?d=c&f=g");
    urlsList.push_back(L"http://example.net/hamster");
    urlsList.push_back(L"http://www.cnn.com/trump-is-an-ass");
    urlsList.push_back(L"http://www.monocle.com");
    urlsList.push_back(L"http://nytimes.com");
    urlsList.push_back(L"http://nytimes.com/hilary");
    urlsList.push_back(L"http://nytimes.com/testing-1-2-3");

    /* Print most seen host to console */
    std::wcout << L"Most popular domain is: " << most_popular_domain(urlsList) << std::endl;

    return 0;
}

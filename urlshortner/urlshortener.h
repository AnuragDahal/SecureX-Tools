#ifndef URLSHORTENER_H
#define URLSHORTENER_H

#include <string>

class UrlShortener
{
public:
    std::string shortenUrl(const std::string &longUrl);

private:
    std::string sendRequest(const std::string &url, const std::string &postData);
};

#endif

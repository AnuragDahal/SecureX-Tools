#include <iostream>
#include "urlshortener.h"
#include <curl/curl.h>

int main()
{
    // Initialize libcurl globally
    CURLcode global_init = curl_global_init(CURL_GLOBAL_ALL);
    if (global_init != CURLE_OK)
    {
        std::cerr << "curl_global_init() failed: " << curl_easy_strerror(global_init) << std::endl;
        return 1;
    }

    UrlShortener shortener;
    std::string longUrl;

    std::cout << "Enter the URL to shorten: ";
    std::getline(std::cin, longUrl); // Use std::getline to properly handle input

    std::string shortUrl = shortener.shortenUrl(longUrl);
    std::cout << "Shortened URL: " << shortUrl << std::endl;

    // Cleanup libcurl globally
    curl_global_cleanup();


    return 0;
}

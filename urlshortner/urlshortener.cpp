#include "urlshortener.h"
#include <curl/curl.h>
#include <iostream>
#include <stdexcept>
#include <nlohmann/json.hpp>

// Define the API token as a constant

const std::string API_TOKEN ="pRCIxNO6sEcSrWLvUFcztjazb1QnDEl1qcEGZXeyJPxraAtXgYlOKBsevFGz";

// Function to handle the curl response
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::string UrlShortener::shortenUrl(const std::string &longUrl)
{
    std::string apiUrl = "https://api.tinyurl.com/create";
    std::string postData = "{\"url\":\"" + longUrl + "\",\"domain\":\"tinyurl.com\",\"description\":\"\"}";
    return sendRequest(apiUrl, postData);
}

std::string UrlShortener::sendRequest(const std::string &url, const std::string &postData)
{
    CURL *curl;
    CURLcode res;
    std::string response;
    struct curl_slist *headers = NULL;

    curl = curl_easy_init();
    if (curl)
    {
        headers = curl_slist_append(headers, "Content-Type: application/json");
        std::string bearerToken = "Authorization: Bearer " + API_TOKEN;
        headers = curl_slist_append(headers, bearerToken.c_str());
        headers = curl_slist_append(headers, "accept: application/json");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        res = curl_easy_perform(curl);
        if (res == CURLE_OK)
        {
            try
            {
                auto jsonResponse = nlohmann::json::parse(response);
                std::string tinyUrl = jsonResponse["data"]["tiny_url"];
                return tinyUrl; // Return the extracted tiny_url
            }
            catch (nlohmann::json::parse_error &e)
            {
                std::cerr << "JSON parse error: " << e.what() << std::endl;
                return ""; // Return an empty string or an appropriate error message
            }
        }
        else
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    else
    {
        std::cerr << "curl_easy_init() failed" << std::endl;
    }
    return "";
}

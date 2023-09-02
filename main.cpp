#include <iostream>
#include <string>
#include <curl/curl.h>

// Функция обратного вызова Curl для получения ответа API
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

// Функция для отправки GET запросов к API
std::string MakeRequest(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Failed to perform curl request: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return response;
}

int main() {
    // Ваш персональный токен доступа
    std::string accessToken = "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";

    // Ваш запрос поиска
    std::string searchQuery = "web+development";

    // Формирование URL для выполнения поиска на GitHub API
    std::string apiUrl = "https://api.github.com/search/repositories?q=" + searchQuery;
    std::string fullUrl = apiUrl + "&access_token=" + accessToken;

    // Отправка запроса и получение ответа API
    std::string response = MakeRequest(fullUrl);

    // Обработка ответа API и извлечение информации о репозиториях
    // Отобразите результаты поиска перед пользователем
    std::cout << "Search results: " << std::endl;
    std::cout << response << std::endl;

    return 0;
}

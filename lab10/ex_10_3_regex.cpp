#include <iostream>
#include <regex>

void printLinks(const std::string& html) {
    std::regex linksRegex(R"((https?://(?:www.)?[^"^\s]*)[^>]*>\s*((?:\w+|\w+\s)+)\s*<)");
    auto match_begin = std::sregex_iterator(html.begin(), html.end(), linksRegex);
    auto match_end = std::sregex_iterator();

    std::cout << "Links:" << "\n";
    for (auto i = match_begin; i != match_end; i++) {
        std::cout << (*i)[2] << " : " << (*i)[1] << std::endl;
    }
}

void printEmails(const std::string& html) {
    std::regex emailsRegex(R"([>\s:](\w(?:\w|\.\w|-\w)*@\w(?:\w|\.\w)*\.\w+)[<\s"])");

    auto match_begin = std::sregex_iterator(html.begin(), html.end(), emailsRegex);
    auto match_end = std::sregex_iterator();

    std::cout << "Emails:" << "\n";
    for (auto i = match_begin; i != match_end; i++) {
        std::cout << " > " << (*i)[1] << '\n';
    }
}

int main() {
    // redirect input
    std::string html;
    std::string line;
    while(std::getline(std::cin, line))
    {
        html+=line;
    }
    printLinks(html);
    std::cout << '\n';
    printEmails(html);


}
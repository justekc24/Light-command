#include <iostream>
#include <fstream>
#include <string>

std::string content;
int main() {
    std::ifstream file("../html/index.html");
    if (!file) {
        std::cerr << "Erreur d'ouverture du fichier" << std::endl;
        return 1;
    }

    std::string data((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());

    std::cout << data << std::endl;
    content = data;
    return 0;
}

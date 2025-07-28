#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream input("../html/index.html");
    if (!input) {
        std::cerr << "Erreur lors de l'ouverture du fichier HTML." << std::endl;
        return 1;
    }

    std::ofstream output("generated_html.h");
    if (!output) {
        std::cerr << "Erreur lors de la création du fichier de sortie." << std::endl;
        return 1;
    }
    output <<"#include <Arduino.h>\n";
    output << "const char index_html[] PROGMEM = R\"rawliteral(\n";

    std::string line;
    while (std::getline(input, line)) {
        output << line << '\n';
    }

    output << ")rawliteral\";\n";

    std::cout << "HTML exporté avec succès dans 'generated_html.h'" << std::endl;
    return 0;
}

#include <array>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

struct Reader {
    std::array<unsigned int, 3> data;
    std::array<unsigned int, 2> towerTypes;
    std::array<std::array<unsigned char, 4>, 4> towerCoverage;
    bool conditionalTask;
    bool hasEnded;
    bool needsAnswer;
    std::string message;
};

void readData(Reader &result) {
    std::string line;
    result.conditionalTask = false;
    result.needsAnswer = false;
    
    while (std::getline(std::cin, line)) {
        if (!line.rfind('.', 0))
            return;
        
        if (!line.rfind("WRONG", 0) ||
            !line.rfind("SUCCESS", 0) ||
            !line.rfind("FAILED", 0)) {
            result.hasEnded = true;
            result.message = std::move(line);
        } else if (!line.rfind("REQ", 0)) {
            result.needsAnswer = true;
            std::stringstream(std::move(line).substr(4)) >> result.data[0] >> result.data[1] >> result.data[2];
        } else if (!line.rfind("COND", 0)) {
            result.conditionalTask = true;
        } else if (!line.rfind("TYPE", 0)) {
            std::stringstream(std::move(line).substr(5)) >> result.towerTypes[0], result.towerTypes[1];
            for (int row = 0; row < 4; row++) {
                std::getline(std::cin, line);
                std::stringstream(line)
                        >> result.towerCoverage[row][0]
                        >> result.towerCoverage[row][1]
                        >> result.towerCoverage[row][2]
                        >> result.towerCoverage[row][3];
            }
        } else {
            std::cerr << "READER ERROR: Unrecognized command: " << line << std::endl;
            result.hasEnded = true;
            return;
        }
    }
    std::cerr << "Unexpected end of input." << std::endl;
    result.hasEnded = true;
}

int main() {
    std::string teamToken = "5qvbnfKKNj";
    int seed = 2;
    std::cout << "LOGIN " << teamToken
            << " " << seed
              << std::endl << "." << std::endl;
    
    std::string line;
    unsigned int gameID;
    std::getline(std::cin, line);
    std::stringstream(std::move(line).substr(6)) >> gameID;
    char criterias[4];
    std::getline(std::cin, line);
    std::stringstream (std::move(line).substr(5))
            >> criterias[0]
            >> criterias[1]
            >> criterias[2]
            >> criterias[3];
    unsigned short populations[21][28];
    std::getline(std::cin, line);
    for (auto &row : populations) {
        std::getline(std::cin, line);
        std::stringstream sstream(line);
        for (auto &col : row) {
            sstream >> col;
        }
    }
    std::getline(std::cin, line);
    
    Reader reader{};
    
    while (true) {
        readData(reader);
        if (reader.hasEnded)
            break;
        if (!reader.needsAnswer)
            continue;
    
        // Ha szeretnetek debug uzenetet kuldeni, akkor megtehetitek.
        // Maximalisan csak 1024 * 1024 bajtot!
        std::cerr << "Send response" << std::endl;
    
        // standard out-ra meg mehet ki a megoldas! Mas ne irodjon ide ki ;)
        std::cout << "RES " << reader.data[0] << " " << reader.data[1] << " " << reader.data[2] << std::endl;
        std::cout << "PUT 0 0 " << reader.towerTypes[0] << " 0" << std::endl;
        std::cout << "." << std::endl;
    }
    
    std::cerr << "END (message): " << reader.message << std::endl;
    
    return 0;
}

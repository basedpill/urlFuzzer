#include <iostream>
#include <cpr/cpr.h>
#include <string>
#include <fstream>

std::ifstream inFile;
std::string line;
std::string dir;

void wordlist(std::string dir){
    inFile.open(dir);
    if (!inFile){
        std::cerr << "Unable to open wordlist. Is it the correct directory?";
        exit(1);
    }
}

void request(std::string link)
{
    cpr::Response x = cpr::Get(cpr::Url{ link });
    if ((x.status_code == 200) && (x.status_code <= 300)){
        std::cout << "[VALID] - " << link << " exists!\n";}
    else{
        std::cout << "[INVALID] - "<< link << " does not exist!\n";
    }
}

int main(int argc, char** argv){
    if (argc < 5) { std::cout << "Simple URL fuzzer\nRun via the command line!\n\nUse -u followed by your url with a / at the end!\nUse -d followed by the directory of your wordlist!\n"; exit(0); }
    if (std::string(argv[1]) == "-u"){
        std::cout << "\nYour URL to fuzz is: " << argv[2] << "\n" << "Sending request to le URL" << "\n";
        cpr::Response r = cpr::Get(cpr::Url{argv[2]});
        std::cout << "Status code: "<< r.status_code << "\n";
        if (r.status_code == 0){
            std::cout << "\nWebsite is not valid! Exiting...";
            exit(0);}}
    if (std::string(argv[3]) == "-d"){
        std::cout << "\nLoaded " << argv[4] << " as the wordlist\n";
        wordlist(argv[4]);
        while (getline(inFile, line)){
            std::string newline = argv[2] + line;
            request(newline);}
    }
    
    

}


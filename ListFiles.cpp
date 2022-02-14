#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;
using namespace std;
using namespace std::filesystem;

// Define el archivo de salida
FILE* outFile;

void GetDirectoryContent(string path, int tab) {
    string name;
    bool flg = false;
    fs::path p(path);
    fs::path file = p.filename();
    for (int i = 0; (tab * 3) > i; i++)fprintf(outFile, " ");
    std::fprintf(outFile, "{ ");
    std::fprintf(outFile, "\"%s\": [ ", file.string().c_str());
    if (!fs::is_empty(path)) {
        std::fprintf(outFile, "\n");
        for (const auto& entry : directory_iterator(path)) {
            if (is_regular_file(entry.path())) {
                error_code ec;
                if (ec) {
                    std::cout << ec.message() << '\n';
                }
                else {
                    try {
                        name = entry.path().filename().string();
                        uintmax_t size = file_size(entry.path(), ec);
                        if (flg) {
                            std::fprintf(outFile, ",\n");
                        }
                        for (int i = 0; (((tab+1) * 3) ) > i; i++)fprintf(outFile, " ");
                        std::fprintf(outFile, "{\"name\":\"%s\",\"size\":%lu}", name.c_str(), size);
                        flg = true;
                    }
                    catch (const std::system_error& e) {
                        name = "";
                        std::cout << "Caught system_error with code " << e.code()
                            << " meaning " << e.what() << '\n';
                    }
                }
            }
            else { // Se trata de un directorio (Probablmente)
                if (is_directory(entry.path())) {
                    if (flg) {
                        std::fprintf(outFile, ",\n");
                    }
                    GetDirectoryContent(entry.path().string(), tab + 1);
                    flg = true;
                    
                }
            }
        }
        std::fprintf(outFile, "\n");
        for (int i = 0; (tab * 3) > i; i++)fprintf(outFile, " ");
        
    }
    for (int i = 0; ((tab * 3) + 1) > i; i++)fprintf(outFile, " ");
    std::fprintf(outFile, "]\n");
    for (int i = 0; (tab * 3) > i; i++)fprintf(outFile, " ");
    std::fprintf(outFile, "}");    
}

int main(int argc, char* argv[]) {
    //argv[1];
    string path = "D:/Marcovnickov/C++";
    errno_t err;
    err = fopen_s(&outFile, "dir.json", "w");
    if (err == 0){
        if (is_directory(status(path))) {
            GetDirectoryContent(path, 0);
        } else {
            std::fprintf(outFile, "{ }");
        }
        fclose(outFile);
    } else {
        std::fprintf(outFile, "{ }");
    }
    return 0;
}
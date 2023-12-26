#include <iostream>
#include <cstdlib>
#include <shlobj.h>
#include <fstream>

bool is64Bit() {
    #ifdef _WIN64
        return true;  // Compilado como 64 bits
    #else
        return false; // Compilado como 32 bits
    #endif
}

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

bool isPythonInstalled() {
    FILE* pipe = _popen("python --version 2>&1", "r");
    if (!pipe) return false;

    char buffer[128];
    std::string result = "";

    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }

    _pclose(pipe);

    // Verifica se a string contém a versão do Python
    return result.find("Python") != std::string::npos;
}

int main() {
    // 1. Descompactar a pasta
    if (!fileExists("./DB4K-main")) {
        int unzipResult = std::system("tar -xf ./install-offline/DB4K-main.zip -C ./");

        if (unzipResult != 0) {
            std::cerr << "erro ao descompactar a pasta.\n";
            return 1;
        }
    } else {
        std::cout << "pasta ja descompactada. pulando a etapa de descompactação.\n";
    }

    // 2. Verificar se o Python já está instalado
    if (!isPythonInstalled()) {
        std::cout << "python nao encontrado.\n";

        const char* pythonInstaller = is64Bit() ? "./install-offline/python64.msi" : "./install-offline/python86.msi";
        
        int installPythonResult = std::system(pythonInstaller);

        if (installPythonResult != 0) {
            std::cerr << "erro ao instalar o python.\n";
            return 1;
        }

        std::cout << "python instalado com sucesso.\n";
    } else {
        std::cout << "python ja instalado. pulando a etapa de instalação do Python.\n";
    }

    // 3. Iniciar o Start.py
    int runPythonResult = std::system("start ./DB4K-main/start.py");

    if (runPythonResult != 0) {
        std::cerr << "erro ao executar o script python.\n";
        return 1;
    }

    return 0;
}

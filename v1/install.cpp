#include <iostream>
#include <cstdlib>
#include <fstream>

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

bool is64Bit() {
    #ifdef _WIN64
        return true;  // Compilado como 64 bits
    #else
        return false; // Compilado como 32 bits
    #endif
}

int main() {
    // 1. Verificar se o arquivo já foi baixado
    const char* repoUrl = "https://github.com/projetomymaker/DB4K/archive/main.tar.gz";
    if (!fileExists("DB4K-main.tar.gz")) {
        int downloadResult = std::system(("curl -LJO " + std::string(repoUrl)).c_str());

        if (downloadResult != 0) {
            std::cerr << "Erro ao baixar o arquivo.\n";
            return 1;
        }
    } else {
        std::cout << "Arquivo já baixado. Pulando a etapa de download.\n";
    }

    // 2. Verificar se o Python já está instalado
    if (system("python --version") != 0) {
        std::cout << "Python não encontrado.\n";

        const char* pythonUrl = is64Bit() ? "https://www.python.org/ftp/python/2.7.9/python-2.7.9.amd64.msi" : "https://www.python.org/ftp/python/2.7.9/python-2.7.9.msi";

        int installPythonResult = std::system(("curl -LJO " + std::string(pythonUrl)).c_str());

        if (installPythonResult != 0) {
            std::cerr << "Erro ao instalar o Python.\n";
            return 1;
        }

        std::string pythonInstaller = is64Bit() ? "python-2.7.9.amd64.msi" : "python-2.7.9.msi";
        int runInstallerResult = std::system(pythonInstaller.c_str());

        if (runInstallerResult != 0) {
            std::cerr << "Erro ao executar o instalador do Python.\n";
            return 1;
        }

        std::cout << "Python instalado com sucesso.\n";

    } else {
        std::cout << "Python já instalado. Pulando a etapa de instalação do Python.\n";
    }

    // 3. Verificar se a pasta já foi descompactada
    if (!fileExists("DB4K-main")) {
        int unzipResult = std::system("tar -xzf DB4K-main.tar.gz");

        if (unzipResult != 0) {
            std::cerr << "Erro ao descompactar a pasta.\n";
            return 1;
        }
    } else {
        std::cout << "Pasta já descompactada. Pulando a etapa de descompactação.\n";
    }

    // 4. Inicia o Start.py
    int runPythonResult = std::system("start DB4K-main/start.py");

    if (runPythonResult != 0) {
        std::cerr << "Erro ao executar o script Python.\n";
        return 1;
    }

    return 0;
}

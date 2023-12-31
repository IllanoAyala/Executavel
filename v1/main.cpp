
#include <iostream>
#include <fstream>
#include <cstdlib>

bool verificaConexaoInternet() {
    #ifdef _WIN32
        const char* comandoPing = "ping -n 1 www.google.com > nul";
    #else
        const char* comandoPing = "ping -c 1 www.google.com > /dev/null 2>&1";
    #endif

    int resultado = std::system(comandoPing);

    return resultado == 0;
}


int main() {
    const char* caminho_do_exe = verificaConexaoInternet() ? "Bin\\install.exe" : "Bin\\installOffline.exe";

    // Verificar se o arquivo existe
    std::ifstream arquivo(caminho_do_exe);
    if (arquivo.is_open()) {
        std::cout << "Arquivo encontrado. Iniciando..." << std::endl;
        // Iniciar o programa
        std::string comando = std::string("start \"\" \"") + caminho_do_exe + "\"";
        system(comando.c_str());
    } else {
        std::cout << "Arquivo não encontrado." << std::endl;
    }

    return 0;
}

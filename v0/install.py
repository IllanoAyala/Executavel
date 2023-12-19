import sys
import zipfile
import os

def criar_pasta(caminho):
    try:
        os.makedirs(caminho)
        print(f"Pasta criada em: {caminho}")
        return True
    except FileExistsError:
        print(f"A pasta {caminho} já existe.")
        return False
    except Exception as e:
        print(f"Erro ao criar pasta: {e}")
        return False

def descompactar_pasta(arquivo_zip, pasta_destino):
    try:
        with zipfile.ZipFile(arquivo_zip, 'r') as zip_ref:
            zip_ref.extractall(pasta_destino)
        print(f"Descompactação concluída em {pasta_destino}")
        return True
    except Exception as e:
        print(f"Erro ao descompactar pasta: {e}")
        return False

arquivo_zip = '.\DB4K-main.zip'  
pasta_destino = '.\MyMaker' 

def verifica_python():
    try:
        versao_python = sys.version
        return True
    except Exception as e:
        return False

def executar_start_py():
    try:
        diretorio_atual = os.path.dirname(os.path.abspath(__file__))
        caminho_start_py = os.path.join(diretorio_atual, "MyMaker", "DB4K-main", "start.py")
        
        subprocess.run(["python", caminho_start_py])
        
        return True
    except Exception as e:
        print(f"Erro ao executar start.py: {e}")
        return False

if __name__ == "__main__":
    criar_pasta('.\MyMaker')
    descompactar_pasta(arquivo_zip, pasta_destino)

    if verifica_python():
        
    else:
        



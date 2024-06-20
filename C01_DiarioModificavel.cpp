#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>

using namespace std;

struct Diario
{
    bool publico = true;
    bool modificavel = true;
    string autor;
    string conteudoOriginal;
    string conteudoModificado;
};

int main()
{
    Diario diario[10000];
    string nome;
    string isPublic;
    string isModdable;
    string addGrupo;
    vector<string> grupo;
    string resposta;
    string nomeArquivoGrupo;
    int n, i, j;

    cout << "Insira a quantidade de pessoas no grupo: " << endl;

    while (!(cin >> n))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora os caracteres inválidos
        cout << "Entrada inválida. Por favor, digite um numero inteiro: ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer before getline

    cout << "Nomeie o arquivo do grupo a ser criado: (coloque .txt no final do nome)" << endl;
    getline(cin, nomeArquivoGrupo);

    for (i = 0; i < n; i++)
    {
        cout << "Escreva o nome do autor do diário: " << endl;
        getline(cin, diario[i].autor);

        cout << "Escreva a mensagem que quer publicar: " << endl;
        getline(cin, diario[i].conteudoOriginal);

        cout << "Quer deixar a mensagem pública? ('S' ou 'N'): " << endl;
        getline(cin, isPublic);

        if (isPublic == "S" || isPublic == "s")
        {
            diario[i].publico = true;
        }
        else if (isPublic == "N" || isPublic == "n")
        {
            diario[i].publico = false;
        }

        cout << "Quer deixar a mensagem modificável? ('S' ou 'N'): " << endl;
        getline(cin, isModdable);

        if (isModdable == "S" || isModdable == "s")
        {
            diario[i].modificavel = true;
        }
        else if (isModdable == "N" || isModdable == "n")
        {
            diario[i].modificavel = false;
        }

        cout << "Deseja adicionar essa pessoa ao grupo? ('S' ou 'N'): " << endl;
        getline(cin, addGrupo);

        if (addGrupo == "S" || addGrupo == "s")
        {
            grupo.push_back(diario[i].autor);

            // Lê o grupo previamente salvo do arquivo
            ifstream arquivoEntrada(nomeArquivoGrupo);
            if (arquivoEntrada.is_open()) {
                string membro;
                while (getline(arquivoEntrada, membro)) {
                    grupo.push_back(membro);
                }
                arquivoEntrada.close();
            }

            // Salva o grupo no arquivo
            ofstream arquivoSaida(nomeArquivoGrupo);
            if (arquivoSaida.is_open()) {
                for (const string& membro : grupo) {
                    arquivoSaida << membro << endl;
                }
                arquivoSaida.close();
            }
        }
    }

    for (j = 0; j < n; j++)
    {
        if (diario[j].publico == true && diario[j].modificavel == true)
        {
            cout << diario[j].autor << endl;
            cout << diario[j].conteudoOriginal << endl;
            cout << " " << endl;
            cout << "Deseja modificar a mensagem? ('S' ou 'N')" << endl;
            getline(cin, resposta);

            if (resposta == "S" || resposta == "s")
            {
                cout << "Quem deseja modificar a mensagem? " << endl;
                getline(cin, nome);

                ifstream arquivoEntrada(nomeArquivoGrupo);
                bool found = false;
                if (arquivoEntrada.is_open()) {
                    string membro;
                    while (getline(arquivoEntrada, membro)) {
                        if (membro == nome) {
                            cout << "Escreva a mensagem modificada: " << endl;
                            getline(cin, diario[j].conteudoModificado);
                            cout << diario[j].conteudoModificado << endl;
                            cout << "Mensagem de " << diario[j].autor << " modificada por " << nome << endl;
                            found = true;
                            break;
                        }
                    }
                    arquivoEntrada.close();
                }

                if (!found)
                {
                    cout << "Você não faz parte do grupo." << endl;
                }
            }
        }
        else if (diario[j].publico == true && diario[j].modificavel == false)
        {
            cout << diario[j].autor << endl;
            cout << diario[j].conteudoOriginal << endl;
            cout << " " << endl;
        }
        else if (diario[j].publico == false && diario[j].modificavel == true)
        {
            cout << "Usuário anônimo" << endl;
            cout << diario[j].conteudoOriginal << endl;
            cout << " " << endl;
            cout << "Deseja modificar a mensagem? ('S' ou 'N')" << endl;
            getline(cin, resposta);

            if (resposta == "S" || resposta == "s")
            {
                cout << "Quem deseja modificar a mensagem? " << endl;
                getline(cin, nome);

                ifstream arquivoEntrada(nomeArquivoGrupo);
                bool found = false;
                if (arquivoEntrada.is_open()) {
                    string membro;
                    while (getline(arquivoEntrada, membro)) {
                        if (membro == nome) {
                            cout << "Escreva a mensagem modificada: " << endl;
                            getline(cin, diario[j].conteudoModificado);
                            cout << diario[j].conteudoModificado << endl;
                            cout << "Mensagem de usuário anônimo modificada por " << nome << endl;                  
                            found = true;
                            break;
                        }
                    }
                    arquivoEntrada.close();
                }

                if (!found)
                {
                    cout << "Você não faz parte do grupo." << endl;
                }
            }
        }
        else
        {
            cout << "Usuário anônimo" << endl;
            cout << diario[j].conteudoOriginal << endl;
            cout << " " << endl;
        }
    }

    return 0;
}


#include <iostream>
#include <string>
#include <vector> //Biblioteca para facilitar e dinamizar o uso de certos vetores, como vetores de tipo string
#include <limits> //Biblioteca para obter informações sobre as propriedades das variáveis numéricas de tipos primitivos, no caso, verificar se o valor lido para uma variável int é de fato um número
#include <fstream> //Biblioteca para manipular arquivos

using namespace std;

//struct para representar um Diário
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
    Diario diario[10000]; //Vetor diario do tipo Diario
    string nome;
    string isPublic;
    string isModdable;
    string addGrupo;
    vector<string> grupo;
    vector<string> mensagens;
    string resposta;
    string nomeArquivoGrupo;
    string nomeArquivoMensagemOriginal;
    int n, i, j;

    cout << "Insira a quantidade de pessoas no grupo: " << endl;

    //Enquanto não for digitado um número, o usuário deve escrever a quantidade novamente, assumindo que sempre será um número inteiro maior que zero
    while (!(cin >> n))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada inválida. Por favor, digite um numero inteiro: ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    //Nome do arquivo das mensagens originais
    cout << "Nomeie o arquivo das mensagens a serem gravadas: (coloque .txt no final do nome)" << endl;
    getline(cin, nomeArquivoMensagemOriginal);

    //Nome do arquivo do grupo
    cout << "Nomeie o arquivo do grupo a ser criado: (coloque .txt no final do nome)" << endl;
    getline(cin, nomeArquivoGrupo);

    //Faz a coleta das informações da struct Diario n vezes
    for (i = 0; i < n; i++)
    {
        cout << "Escreva o nome do autor do diário: " << endl;
        getline(cin, diario[i].autor);

        cout << "Escreva a mensagem que quer publicar: " << endl;
        getline(cin, diario[i].conteudoOriginal);

        //Adiciona a mensagem no vetor de mensagens apenas se não estiver presente
        if (find(mensagens.begin(), mensagens.end(), diario[i].conteudoOriginal) == mensagens.end()) {
            mensagens.push_back(diario[i].conteudoOriginal);
        }

        //Lê as mensagens previamente salvas do arquivo
        ifstream arquivoEntrada1(nomeArquivoMensagemOriginal);
        if (arquivoEntrada1.is_open()) {
            string membro;
            while (getline(arquivoEntrada1, membro)) {
                if (find(mensagens.begin(), mensagens.end(), membro) == mensagens.end()) {
                    mensagens.push_back(membro);
                }
            }
            arquivoEntrada1.close();
        }

        //Salva as mensagens no arquivo
        ofstream arquivoSaida1(nomeArquivoMensagemOriginal);
        if (arquivoSaida1.is_open()) {
            for (const string& membro : mensagens) {
                arquivoSaida1 << membro << endl;
            }
            arquivoSaida1.close();
        }

        //Permitir ou não a visibilidade do autor da mensagem
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

        //Permitir ou não o conteúdo original da mensagem ser modificado por outros membros do grupo
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

        //Caso a pessoa seja adicionada ao grupo, o nome dela é gravado no arquivo nomeado previamente a esse for
        cout << "Deseja adicionar essa pessoa ao grupo? ('S' ou 'N'): " << endl;
        getline(cin, addGrupo);

        if (addGrupo == "S" || addGrupo == "s")
        {
            // Adiciona o autor ao vetor de grupo apenas se não estiver presente
            if (find(grupo.begin(), grupo.end(), diario[i].autor) == grupo.end()) {
                grupo.push_back(diario[i].autor);
            }

            // Lê o grupo previamente salvo do arquivo
            ifstream arquivoEntrada2(nomeArquivoGrupo);
            if (arquivoEntrada2.is_open()) {
                string membro;
                while (getline(arquivoEntrada2, membro)) {
                    if (find(grupo.begin(), grupo.end(), membro) == grupo.end()) {
                        grupo.push_back(membro);
                    }
                }
                arquivoEntrada2.close();
            }

            // Salva o grupo no arquivo
            ofstream arquivoSaida2(nomeArquivoGrupo);
            if (arquivoSaida2.is_open()) {
                for (const string& membro : grupo) {
                    arquivoSaida2 << membro << endl;
                }
                arquivoSaida2.close();
            }
        }
    }

    //Irá percorrer as mensagens de todos os autores
    for (j = 0; j < n; j++)
    {
        //Caso a mensagem seja pública e a modificação seja permitida, primeiramente é exibida a mensagem e autor orignais e é perguntado ao usuário se este gostaria de modificar a mensagem
        if (diario[j].publico == true && diario[j].modificavel == true)
        {
            cout << diario[j].autor << endl;
            cout << diario[j].conteudoOriginal << endl;
            cout << " " << endl;
            cout << "Deseja modificar a mensagem? ('S' ou 'N')" << endl;
            getline(cin, resposta);

            //Caso o usuário queira modificar a mensagem e faça parte do grupo, é exibida a nova mensagem e por quem ela foi feita
            if (resposta == "S" || resposta == "s")
            {
                cout << "Quem deseja modificar a mensagem? " << endl;
                getline(cin, nome);

                //Percorre o arquivo das pessoas do grupo para verificar se quem deseja modificar a mensagem está presente nele
                ifstream arquivoEntrada2(nomeArquivoGrupo);
                bool found = false;
                if (arquivoEntrada2.is_open()) {
                    string membro;
                    while (getline(arquivoEntrada2, membro)) {
                        if (membro == nome) {
                            cout << "Escreva a mensagem modificada: " << endl;
                            getline(cin, diario[j].conteudoModificado);
                            cout << diario[j].conteudoModificado << endl;
                            cout << "Mensagem de " << diario[j].autor << " modificada por " << nome << endl;
                            found = true;
                            break;
                        }
                    }
                    arquivoEntrada2.close();
                }

                if (!found)
                {
                    cout << "Você não faz parte do grupo." << endl;
                }
            }
        }

        //Caso a mensagem seja pública mas não pode ser modificada, ela é simplesmente exibida com o autor e mensagem originais
        else if (diario[j].publico == true && diario[j].modificavel == false)
        {
            cout << diario[j].autor << endl;
            cout << diario[j].conteudoOriginal << endl;
            cout << " " << endl;
        }

        //Caso a mensagem seja privada mas possa ser modificada, primeiramente é exibida a mensagem original e depois é realizada a checagem da modificação explicada anteriormente
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

                ifstream arquivoEntrada2(nomeArquivoGrupo);
                bool found = false;
                if (arquivoEntrada2.is_open()) {
                    string membro;
                    while (getline(arquivoEntrada2, membro)) {
                        if (membro == nome) {
                            cout << "Escreva a mensagem modificada: " << endl;
                            getline(cin, diario[j].conteudoModificado);
                            cout << diario[j].conteudoModificado << endl;
                            cout << "Mensagem de usuário anônimo modificada por " << nome << endl;                  
                            found = true;
                            break;
                        }
                    }
                    arquivoEntrada2.close();
                }

                if (!found)
                {
                    cout << "Você não faz parte do grupo." << endl;
                }
            }
        }

        //Caso a mensagem seja privada e não possa ser modificada, é mostrada a mensagem original apenas
        else
        {
            cout << "Usuário anônimo" << endl;
            cout << diario[j].conteudoOriginal << endl;
            cout << " " << endl;
        }
    }

    return 0;
}

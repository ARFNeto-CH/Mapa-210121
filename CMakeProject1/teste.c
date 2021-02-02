int main(void)
{
    char opcao;
    string conversa;
    string abrir;
    string cmnd;


    cout << "Escolha uma opcao:\n\n OPCAO 1: CONVERSA \n\n OPCAO 2: COMANDOS\n\n";
    scanf(" %c", &opcao);


    // Conversa //
    do {
        switch (opcao) {
        case '1':
            string nome;
            cout << "Olá, qual seu nome?\n\n Seu nome: ";
            cin >> nome;

            break;


        case '2': {

            cout << "Qual comando deseja executar?\n\n1 - Abrir Navegador\n\n2 - Pesquisa com Google\n\n3 - Diretorios do computador\n\nComando: ";
            cin >> cmnd;


            if (cmnd == "1") {
                system("start chrome.exe");
                
            }

            if (cmnd == "2") {
                system("start chrome google.com");
                
            }

            if (cmnd == "3") {

                system("start CD C:\\");
                
            }
            }



                  // Mensagem de erro //
        case '3': {
            cout << "Digite novamente";
            break;
            }
                  
        } while (opcao != '0');
                  return 0;
                  
    }
    }
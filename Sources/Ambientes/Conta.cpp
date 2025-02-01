#include "../../Includes/Ambientes/Conta.hpp"

void AmbienteConta::Executar(Codigo &CodigoUsuario)
{
    this->CodigoUsuario = CodigoUsuario;

  while (true)
  {
    try
    {
      cout << "\033[2J\033[1;1H";

      if (this->CodigoUsuario.getValor() != "000000")
      {

        cout << "//////////////////////" << endl;
        cout << "    Ambiente Conta" << endl;
        cout << "//////////////////////" << endl;
        cout << "1 - Continuar para HUB" << endl;
        cout << "2 - Informacao da conta" << endl;         
        cout << "3 - Sair" << endl;   
        cout << "Escolha uma opcao (1 a 3): ";
        int option;
        cin >> option;

        cout << "\033[2J\033[1;1H";

        if (option == 2)
          Ler(CodigoUsuario);
        else if (option == 1)
          return;
        else if (option == 3)
          Sair();
        else
        {
          cout << "Opcao invalida" << endl;
          Executar(CodigoUsuario);
        }
      }
      else
      {
        cout << "   //////////////////////" << endl;
        cout << "       Ambiente Conta" << endl;
        cout << "   //////////////////////" << endl;
        cout << "1 - Criar conta" << endl;
        cout << "2 - Entrar" << endl;
        cout << "3 - Sair" << endl;
        cout << "Escolha uma opcao (1 a 3): ";
        string option;
        cin >> option;

        cout << "\033[2J\033[1;1H";


        if (option == "1")
        {
          Criar();
        }
        else if (option == "2")
        {
          Autenticar();
        }
        else if (option == "3")
        {
          break;
        }
        else
        {
          cout << "Opcao invalida" << endl;
              cout << "Pressione qualquer tecla para continuar.";
              cin.ignore();
              cin.get();
          Executar(CodigoUsuario);
        }
      }

      cout << endl
           << "***** OPERACAO FEITA COM SUCESSO ***** " << endl
           << endl;
    }
    catch (const std::exception &e)
    {
      cout << endl
           << "****** FALHA NA OPERACAO ******" << endl;
      cout << e.what() << endl;
      cout << "********************************" << endl
           << endl;
    }

    cout << "Pressione qualquer tecla para continuar.";
    cin.ignore();
    cin.get();
  }
}

void AmbienteConta::Criar()
{
  string senha;

  cout << "//////////////////////" << endl;
  cout << "   Criar nova conta" << endl;
  cout << "//////////////////////" << endl;
  cout << "Digite a senha da sua nova conta: " << endl;
  cout << " - A senha deve conter 5 digitos" << endl;
  cout << " - Nao pode conter digitos em duplicidade (EX.: 12234)" << endl;
  cout << " - Nao pode estar em ordem crescente ou descrescente (EX.: 12345 ou 54321)" << endl;
  cin >> senha;
  Codigo CodigoUsuarioDominio = Codigo();
  Senha SenhaDominio = Senha(senha);
  ServicoConta->Criar(CodigoUsuarioDominio, SenhaDominio);
  CodigoUsuario.setValor(CodigoUsuarioDominio.getValor());
  cout << "Sua conta foi criada. O seu codigo de acesso e: " << CodigoUsuarioDominio.getValor() << endl;
  return;
}

void AmbienteConta::Autenticar()
{
  string senha, codigo;
  cout << "//////////////////////" << endl;
  cout << "Autenticacao de Usuario" << endl;
  cout << "//////////////////////" << endl;
  cout << "Digite o codigo da sua conta: ";
  cin >> codigo;
  Codigo CodigoDominio = Codigo(codigo);
  cout << "Digite a senha da sua conta: ";
  cin >> senha;
  Senha SenhaDominio = Senha(senha);

  if (ServicoConta->Autenticar(CodigoDominio, SenhaDominio))
  {
    CodigoUsuario.setValor(CodigoDominio.getValor());
    return;
  }

  throw invalid_argument("Erro na sua autenticacao. Senha ou codigo incorretos/invalidos.");
}

void AmbienteConta::Sair()
{
  CodigoUsuario.setValor("000000");
  cout << "Voce saiu da sua conta." << endl;
}

void AmbienteConta::Ler(Codigo &CodigoUsuario)
{
  string Codigo = CodigoUsuario.getValor();
  cout << "//////////////////////" << endl;
  cout << "Codigo do usuario: " << Codigo << endl;
  cout << "//////////////////////" << endl;

}

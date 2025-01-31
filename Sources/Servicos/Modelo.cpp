#include "../../Includes/Servicos/Modelo.hpp"
#include <sys/stat.h>
#include <sys/types.h>

vector<map<string, string>> Modelo::results;

Modelo::Modelo()
{
  int error = 0;

  struct stat info;
  if (stat("./db", &info) != 0 || !(info.st_mode & S_IFDIR))
  {
    mkdir("./db", 0777);
  }

  error = sqlite3_open("./db/dev.db", &db);

  if (error)
  {
    cout << "DB Open Error: " << sqlite3_errmsg(db) << endl;
  }
}

void Modelo::CriarTableConta()
{
  ComandoSQL = "CREATE TABLE IF NOT EXISTS conta("
               "codigo VARCHAR(6) PRIMARY KEY,"
               "senha VARCHAR(5) NOT NULL);";
  this->Executar();
}

void Modelo::CriarTableViagem()
{
  ComandoSQL = "CREATE TABLE IF NOT EXISTS viagem("
               "codigo VARCHAR(6) PRIMARY KEY,"
               "nome VARCHAR(30) NOT NULL,"
               "avaliacao INTEGER(1) CHECK(rating >= 0 AND rating <= 5),"
               "codigoconta VARCHAR(6),"
               "FOREIGN KEY(codigoconta) REFERENCES conta(codigo));";
  this->Executar();
}

void Modelo::CriarTableDestino()
{
  ComandoSQL = "CREATE TABLE IF NOT EXISTS destino("
               "codigo VARCHAR(6) PRIMARY KEY,"
               "nome VARCHAR(30) NOT NULL,"
               "chegada VARCHAR(8) NOT NULL,"
               "partida VARCHAR(8) NOT NULL,"
               "avaliacao INTEGER(1) CHECK(rating >= 0 AND rating <= 5),"
               "codigoviagem VARCHAR(6),"
               "FOREIGN KEY(codigoviagem) REFERENCES viagem(codigo));";
  this->Executar();
}

void Modelo::CriarTableAtividade()
{
  ComandoSQL = "CREATE TABLE IF NOT EXISTS atividade("
               "codigo VARCHAR(6) PRIMARY KEY,"
               "nome VARCHAR(30) NOT NULL,"
               "data VARCHAR(8) NOT NULL,"
               "horario VARCHAR(5) NOT NULL,"
               "duracao INTEGER CHECK(duration >= 0 AND duration <= 360),"
               "preco INTEGER CHECK(price >= 0 AND price <= 200000),"
               "avaliacao INTEGER(1) CHECK(rating >= 0 AND rating <= 5),"
               "codigodestino VARCHAR(6),"
               "FOREIGN KEY(codigodestino) REFERENCES destino(codigo));";
  this->Executar();
}

void Modelo::CriarTableHospedagem()
{
  ComandoSQL = "CREATE TABLE IF NOT EXISTS hospedagem("
               "codigo VARCHAR(6) PRIMARY KEY,"
               "nome VARCHAR(30) NOT NULL,"
               "precodiaria INTEGER CHECK(dailyRate >= 0 AND dailyRate <= 200000),"
               "avaliacao INTEGER(1) CHECK(rating >= 0 AND rating <= 5),"
               "codigodestino VARCHAR(6),"
               "FOREIGN KEY(codigodestino) REFERENCES destino(codigo));";
  this->Executar();
}

void Modelo::CriarTables()
{
    CriarTableConta();
    CriarTableViagem();
    CriarTableDestino();
    CriarTableAtividade();
    CriarTableHospedagem();
}

Modelo::~Modelo()
{
  sqlite3_close(db);
  db = nullptr;
}

void Modelo::Executar()
{
  status = sqlite3_exec(db, ComandoSQL.c_str(), callback, nullptr, nullptr);
}

int Modelo::callback(void *data, int argc, char **argv, char **azColName)
{
  map<string, string> row;
  for (int i = 0; i < argc; i++)
  {
    row[azColName[i]] = argv[i] ? argv[i] : "NULL";
  }
  results.push_back(row);
  return 0;
}

#include "../../Includes/Servicos/Viagem.hpp"

void ModeloViagem::Criar(Codigo &CodigoUsuario, Viagem &NovaViagem)
{
  string CodigoConta = CodigoUsuario.getValor();
  string CodigoViagem = NovaViagem.get("code").getValor();
  string NomeViagem = NovaViagem.get("name").getValor();
  string AvaliacaoViagem = NovaViagem.get("rating").getValor();
  ComandoSQL = "INSERT INTO viagem (codigo, nome, avaliacao, codigoconta) VALUES ('" + CodigoViagem + "', '" + NomeViagem + "', '" + AvaliacaoViagem + "', '" + CodigoConta + "');";
  results.clear();
  this->Executar();
  if (status != SQLITE_OK)
  {
    throw invalid_argument("Erro criação da viagem");
  }
}

void ModeloViagem::Atualizar(Codigo &CodigoUsuario, Codigo &CodigoViagem, Viagem &ViagemAtualizada)
{
  ComandoSQL = "SELECT codigoconta FROM viagem WHERE codigo = '" + CodigoViagem.getValor() + "';";
  results.clear();
  this->Executar();

  if (results.empty() || results[0]["codigoconta"] != CodigoUsuario.getValor())
  {
    throw invalid_argument("Viagem não existente ou pertencente a outra conta");
  }

  string NomeViagem = ViagemAtualizada.get("nome").getValor();
  string AvaliacaoViagem = ViagemAtualizada.get("avaliacao").getValor();

  ComandoSQL = "UPDATE viagem SET nome = '" + NomeViagem + "', avaliacao = '" + AvaliacaoViagem + "' WHERE codigo = '" + CodigoViagem.getValor() + "';";
  results.clear();
  this->Executar();
  if (status != SQLITE_OK)
  {
    throw invalid_argument("Erro atualização da viagem");
  }
}

void ModeloViagem::Remover(Codigo &CodigoUsuario, Codigo &CodigoViagem)
{
  ComandoSQL = "SELECT codigoconta FROM viagem WHERE codigo = '" + CodigoViagem.getValor() + "';";
  results.clear();
  this->Executar();

  if (results.empty() || results[0]["codigoconta"] != CodigoUsuario.getValor())
  {
    throw invalid_argument("Viagem não existente ou pertencente a outra conta");
  }

  ComandoSQL = "DELETE FROM viagem WHERE codigo = '" + CodigoViagem.getValor() + "';";
  results.clear();
  this->Executar();
  if (status != SQLITE_OK)
  {
    throw invalid_argument("Erro na remoção da viagem");
  }
}

vector<Viagem> ModeloViagem::LerTudo(Codigo &CodigoUsuario)
{
  ComandoSQL = "SELECT * FROM viagem WHERE codigoconta = '" + CodigoUsuario.getValor() + "';";
  results.clear();
  this->Executar();

  if (status != SQLITE_OK)
  {
    throw invalid_argument("Erro na leitura das viagens");
  }

  vector<Viagem> Viagens;
  for (size_t i = 0; i < results.size(); i++)
  {
    Codigo codigo = Codigo(results[i]["codigo"]);
    Nome nome = Nome(results[i]["nome"]);
    Avaliacao avaliacao = Avaliacao(results[i]["avaliacao"]);
    Viagem viagem = Viagem(codigo, nome, avaliacao);
    Viagens.push_back(viagem);
  }
  return Viagens;
}

int ModeloViagem::ConsultaCusto(Codigo &CodigoUsuario, Codigo &CodigoViagem)
{
  ComandoSQL = "SELECT codigoconta FROM viagem WHERE codigo = '" + CodigoViagem.getValor() + "';";
  results.clear();
  this->Executar();

  if (results.empty() || results[0]["codigoconta"] != CodigoUsuario.getValor())
  {
    throw invalid_argument("Viagem não existente ou pertencente a outra conta");
  }

  ComandoSQL = "SELECT SUM(preco) AS custototalatividade FROM atividade WHERE codigodestino IN (SELECT codigo FROM destino WHERE codigoviagem = '" + CodigoViagem.getValor() + "');";
  results.clear();
  this->Executar();

  int CustoTotalAtividade = 0;
  if (status == SQLITE_OK && !results.empty() && results[0]["custototalatividade"] != "NULL")
  {
    CustoTotalAtividade= stoi(results[0]["custototalatividade"]);
  }

  ComandoSQL = "SELECT precodiaria, partida, chegada FROM hospedagem INNER JOIN destino ON hospedagem.codigodestino = destino.codigo WHERE destino.codigoviagem = '" + CodigoViagem.getValor() + "';";
  results.clear();
  this->Executar();

  int totalLodgingCost = 0;
  if (status == SQLITE_OK && !results.empty())
  {
    for (size_t i = 0; i < results.size(); i++)
    {
      int dailyRate = stoi(results[i]["dailyRate"]);
      Date arrival = Date(results[i]["arrival"]);
      Date departure = Date(results[i]["departure"]);
      int days = Date::calculateDateRange(arrival.getValue(), departure.getValue());
      totalLodgingCost += dailyRate * days;
    }
  }

  return totalActivityCost + totalLodgingCost;
}

vector<Destination> TravelModel::listDestinations(Code &userCode, Code &travelCode)
{
  sqlCommand = "SELECT accountCode FROM travel WHERE code = '" + travelCode.getValue() + "';";
  results.clear();
  this->execute();

  if (results.empty() || results[0]["accountCode"] != userCode.getValue())
  {
    throw invalid_argument("Viagem inexistente ou pertencente a outra conta");
  }

  sqlCommand = "SELECT * FROM destination WHERE travelCode = '" + travelCode.getValue() + "';";
  results.clear();
  this->execute();

  if (status != SQLITE_OK)
  {
    throw invalid_argument("Erro na listagem de destinos");
  }

  vector<Destination> destinations;
  for (size_t i = 0; i < results.size(); i++)
  {
    Code code = Code(results[i]["code"]);
    Name name = Name(results[i]["name"]);
    Date arrival = Date(results[i]["arrival"]);
    Date departure = Date(results[i]["departure"]);
    Rating rating = Rating(results[i]["rating"]);
    Destination destination = Destination(code, name, arrival, departure, rating);
    destinations.push_back(destination);
  }
  return destinations;
}

Destination TravelModel::consultDestination(Code &userCode, Code &destinationCode)
{
  sqlCommand = "SELECT accountCode FROM destination WHERE code = '" + destinationCode.getValue() + "';";
  results.clear();
  this->execute();

  if (results.empty() || results[0]["accountCode"] != userCode.getValue())
  {
    throw invalid_argument("Viagem inexistente ou pertencente a outra conta");
  }

  sqlCommand = "SELECT * FROM destination WHERE code = '" + destinationCode.getValue() + "';";
  results.clear();
  this->execute();

  if (results.empty())
  {
    throw invalid_argument("Destino não encontrado");
  }

  Code code = Code(results[0]["code"]);
  Name name = Name(results[0]["name"]);
  Date arrival = Date(results[0]["arrival"]);
  Date departure = Date(results[0]["departure"]);
  Rating rating = Rating(results[0]["rating"]);
  Destination destination = Destination(code, name, arrival, departure, rating);

  return destination;
}

vector<Lodging> TravelModel::listLodgings(Code &userCode, Code &destinationCode)
{
  sqlCommand = "SELECT travelCode FROM destination WHERE code = '" + destinationCode.getValue() + "';";
  results.clear();
  this->execute();

  sqlCommand = "SELECT accountCode from travel WHERE code = '" + results[0]["travelCode"] + "';";
  results.clear();
  this->execute();

  if (results.empty() || results[0]["accountCode"] != userCode.getValue())
  {
    throw invalid_argument("Informações sobre viagem inexistente ou pertencente a outra conta");
  }

  sqlCommand = "SELECT * FROM lodging WHERE destinationCode = '" + destinationCode.getValue() + "';";
  results.clear();
  this->execute();

  if (status != SQLITE_OK)
  {
    throw invalid_argument("Erro na leitura das hospedagens");
  }

  vector<Lodging> lodgings;
  for (size_t i = 0; i < results.size(); i++)
  {
    Code code = Code(results[i]["code"]);
    Name name = Name(results[i]["name"]);
    Money dailyRate = Money(results[i]["dailyRate"]);
    Rating rating = Rating(results[i]["rating"]);
    Lodging lodging = Lodging(code, name, dailyRate, rating);
    lodgings.push_back(lodging);
  }
  return lodgings;
}

vector<Activity> TravelModel::listActivities(Code &userCode, Code &destinationCode)
{
  sqlCommand = "SELECT travelCode FROM destination WHERE code = '" + destinationCode.getValue() + "';";
  results.clear();
  this->execute();

  sqlCommand = "SELECT accountCode from travel WHERE code = '" + results[0]["travelCode"] + "';";
  results.clear();
  this->execute();

  if (results.empty() || results[0]["accountCode"] != userCode.getValue())
  {
    throw invalid_argument("Informações sobre viagem inexistente ou pertencente a outra conta");
  }

  sqlCommand = "SELECT * FROM activity WHERE destinationCode = '" + destinationCode.getValue() + "';";
  results.clear();
  this->execute();

  if (status != SQLITE_OK)
  {
    throw invalid_argument("Erro na leitura das atividades");
  }

  vector<Activity> activities;
  for (size_t i = 0; i < results.size(); i++)
  {
    Code code = Code(results[i]["code"]);
    Name name = Name(results[i]["name"]);
    Date date = Date(results[i]["date"]);
    Time time = Time(results[i]["time"]);
    Duration duration = Duration(results[i]["duration"]);
    Money price = Money(results[i]["price"]);
    Rating rating = Rating(results[i]["rating"]);
    Activity activity = Activity(code, name, date, time, duration, price, rating);
    activities.push_back(activity);
  }
  return activities;
}
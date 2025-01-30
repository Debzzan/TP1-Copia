#include "../../Includes/Servicos/Atividade.hpp"

void ModeloAtividade::Criar(Codigo &CodigoUsuario, Codigo &CodigoAtividadeDestino, Atividade &NovaAtividade)
{
  ComandoSQL = "SELECT travelCode FROM destination WHERE code = '" + CodigoAtividadeDestino.getValor() + "';";
  results.clear();
  this->Executar();

  sqlCommand = "SELECT accountCode FROM travel WHERE code = '" + results[0]["travelCode"] + "';";
  results.clear();
  this->Executar();

  if (results.empty() || results[0]["accountCode"] != CodigoUsuario.getValor())
  {
    throw invalid_argument("Destino Não existente ou pertencente a outra conta");
  }

  sqlCommand = "SELECT arrival, departure FROM destination WHERE code = '" + CodigoAtividadeDestino.getValor() + "';";
  results.clear();
  this->Executar();

  if (!Data::AlcanceDatas(NovaAtividade.get("data").getValor(), results[0]["chegada"], results[0]["partida"]))
  {
    throw invalid_argument("Data da atividade fora do intervalo do destino");
  }

  string activityCode = NovaAtividade.get("code").getValue();
  string activityName = NovaAtividade.get("name").getValue();
  string activityDate = NovaAtividade.get("date").getValue();
  string activityTime = NovaAtividade.get("time").getValue();
  string activityDuration = NovaAtividade.get("duration").getValue();
  string activityPrice = NovaAtividade.get("price").getValue();
  string activityRating = NovaAtividade.get("rating").getValue();

  sqlCommand = "INSERT INTO activity (code, name, date, time, duration, price, rating, destinationCode) VALUES ('" + activityCode + "', '" + activityName + "', '" + activityDate + "', '" + activityTime + "', '" + activityDuration + "', '" + activityPrice + "', '" + activityRating + "', '" + activityDestinationCode.getValue() + "');";
  results.clear();
  this->execute();

  if (status != SQLITE_OK)
  {
    throw invalid_argument("Erro na criação da atividade");
  }
}

void ActivityModel::update(Code &userCode, Code &activityCode, Activity &updatedActivity)
{
  sqlCommand = "SELECT destinationCode FROM activity WHERE code = '" + activityCode.getValue() + "';";
  results.clear();
  this->execute();

  sqlCommand = "SELECT travelCode FROM destination WHERE code = '" + results[0]["destinationCode"] + "';";
  results.clear();
  this->execute();

  sqlCommand = "SELECT accountCode FROM travel WHERE code = '" + results[0]["travelCode"] + "';";
  results.clear();
  this->execute();

  if (results.empty() || results[0]["accountCode"] != userCode.getValue())
  {
    throw invalid_argument("Atividade inexistente ou pertencente a outra conta");
  }

  sqlCommand = "SELECT destinationCode FROM activity WHERE code = '" + activityCode.getValue() + "';";
  results.clear();
  this->execute();

  sqlCommand = "SELECT arrival, departure FROM destination WHERE code = '" + results[0]["destinationCode"] + "';";
  results.clear();
  this->execute();

  if (!Date::isWithinRange(updatedActivity.get("date").getValue(), results[0]["arrival"], results[0]["departure"]))
  {
    throw invalid_argument("Data da atividade fora do intervalo do destino");
  }

  string activityName = updatedActivity.get("name").getValue();
  string activityDate = updatedActivity.get("date").getValue();
  string activityTime = updatedActivity.get("time").getValue();
  string activityDuration = updatedActivity.get("duration").getValue();
  string activityPrice = updatedActivity.get("price").getValue();
  string activityRating = updatedActivity.get("rating").getValue();

  sqlCommand = "UPDATE activity SET name = '" + activityName + "', date = '" + activityDate + "', time = '" + activityTime + "', duration = '" + activityDuration + "', price = '" + activityPrice + "', rating = '" + activityRating + "' WHERE code = '" + activityCode.getValue() + "';";
  results.clear();
  this->execute();

  if (status != SQLITE_OK)
  {
    throw invalid_argument("Erro na atualização da atividade");
  }
}

void ActivityModel::remove(Code &userCode, Code &activityCode)
{
  sqlCommand = "SELECT destinationCode FROM activity WHERE code = '" + activityCode.getValue() + "';";
  results.clear();
  this->execute();

  sqlCommand = "SELECT travelCode FROM destination WHERE code = '" + results[0]["destinationCode"] + "';";
  results.clear();
  this->execute();

  sqlCommand = "SELECT accountCode FROM travel WHERE code = '" + results[0]["travelCode"] + "';";
  results.clear();
  this->execute();

  if (results.empty() || results[0]["accountCode"] != userCode.getValue())
  {
    throw invalid_argument("Atividade inexistente ou pertencente a outra conta");
  }

  sqlCommand = "DELETE FROM activity WHERE code = '" + activityCode.getValue() + "';";
  results.clear();
  this->execute();

  if (status != SQLITE_OK)
  {
    throw invalid_argument("Erro na remoção da atividade");
  }
}

vector<Activity> ActivityModel::read(Code &userCode)
{
  sqlCommand = "SELECT a.* FROM activity a INNER JOIN destination d ON a.destinationCode = d.code INNER JOIN travel t ON d.travelCode = t.code WHERE t.accountCode = '" + userCode.getValue() + "';";
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
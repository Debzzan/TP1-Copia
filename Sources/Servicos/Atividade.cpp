#include "../../Includes/Servicos/Atividade.hpp"

void ModeloAtividade::Criar(Codigo &CodigoUsuario, Codigo &CodigoAtividadeDestino, Atividade &NovaAtividade)
{
  ComandoSQL = "SELECT codigodestino FROM destino WHERE codigo = '" + CodigoAtividadeDestino.getValor() + "';";
  results.clear();
  this->Executar();

  ComandoSQL = "SELECT codigoconta FROM viagem WHERE codigo = '" + results[0]["codigodestino"] + "';";
  results.clear();
  this->Executar();

  if (results.empty() || results[0]["codigoconta"] != CodigoUsuario.getValor())
  {
    throw invalid_argument("Destino não existente ou pertencente a outra conta");
  }

  ComandoSQL = "SELECT chegada, partida FROM destino WHERE codigo = '" + CodigoAtividadeDestino.getValor() + "';";
  results.clear();
  this->Executar();

  if (!Data::AlcanceDatas(NovaAtividade.get("data").getValor(), results[0]["chegada"], results[0]["partida"]))
  {
    throw invalid_argument("Data da atividade fora do intervalo do destino");
  }

  string AtividadeCodigo = NovaAtividade.get("codigo").getValor();
  string AtividadeNome = NovaAtividade.get("nome").getValor();
  string AtividadeData = NovaAtividade.get("data").getValor();
  string AtividadeHorario = NovaAtividade.get("horario").getValor();
  string AtividadeDuracao = NovaAtividade.get("duracao").getValor();
  string AtividadePreco = NovaAtividade.get("preco").getValor();
  string AtividadeAvaliacao = NovaAtividade.get("avaliacao").getValor();

  ComandoSQL = "INSERT INTO atividade (codigo, nome, data, horario, duracao, preco, avaliacao, codigodestino) VALUES ('" + AtividadeCodigo + "', '" + AtividadeNome + "', '" + AtividadeData + "', '" + AtividadeHorario + "', '" + AtividadeDuracao + "', '" + AtividadePreco + "', '" + AtividadeAvaliacao + "', '" + CodigoAtividadeDestino.getValor() + "');";
  results.clear();
  this->Executar();

  if (status != SQLITE_OK)
  {
    throw invalid_argument("Erro criação atividade");
  }
}

void ModeloAtividade::Atualizar(Codigo &CodigoUsuario, Codigo &CodigoAtividade, Atividade &AtividadeAtualizada)
{
  ComandoSQL = "SELECT codigodestino FROM atividade WHERE codigo = '" + CodigoAtividade.getValor() + "';";
  results.clear();
  this->Executar();

  ComandoSQL = "SELECT codigoviagem FROM destino WHERE codigo = '" + results[0]["codigodestino"] + "';";
  results.clear();
  this->Executar();

  ComandoSQL = "SELECT codigoconta FROM viagem WHERE codigo = '" + results[0]["codigoviagem"] + "';";
  results.clear();
  this->Executar();

  if (results.empty() || results[0]["codigoconta"] != CodigoUsuario.getValor())
  {
    throw invalid_argument("Atividade não existente ou pertencente a outra conta");
  }

  ComandoSQL = "SELECT codigodestino FROM atividade WHERE codigo = '" + CodigoAtividade.getValor() + "';";
  results.clear();
  this->Executar();

  ComandoSQL = "SELECT chegada, partida FROM destino WHERE codigo = '" + results[0]["codigodestino"] + "';";
  results.clear();
  this->Executar();

  if (!Data::AlcanceDatas(AtividadeAtualizada.get("data").getValor(), results[0]["chegada"], results[0]["partida"]))
  {
    throw invalid_argument("Data da atividade fora do intervalo do destino");
  }

  string AtividadeCodigo = AtividadeAtualizada.get("codigo").getValor();
  string AtividadeNome = AtividadeAtualizada.get("nome").getValor();
  string AtividadeData = AtividadeAtualizada.get("data").getValor();
  string AtividadeHorario = AtividadeAtualizada.get("horario").getValor();
  string AtividadeDuracao = AtividadeAtualizada.get("duracao").getValor();
  string AtividadePreco = AtividadeAtualizada.get("preco").getValor();
  string AtividadeAvaliacao = AtividadeAtualizada.get("avaliacao").getValor();

  ComandoSQL = "UPDATE atividade SET nome = '" + AtividadeNome + "', data = '" + AtividadeData + "', horario = '" + AtividadeHorario + "', duracao = '" + AtividadeDuracao + "', preco = '" + AtividadePreco + "', avaliacao = '" + AtividadeAvaliacao + "' WHERE codigo = '" + CodigoAtividade.getValor() + "';";
  results.clear();
  this->Executar();

  if (status != SQLITE_OK)
  {
    throw invalid_argument("Erro na atualização da atividade");
  }
}

void ModeloAtividade::Remover(Codigo &CodigoUsuario, Codigo &CodigoAtividade)
{
  ComandoSQL = "SELECT codigodestino FROM atividade WHERE codigo = '" + CodigoAtividade.getValor() + "';";
  results.clear();
  this->Executar();

  ComandoSQL = "SELECT codigoviagem FROM destino WHERE codigo = '" + results[0]["codigodestino"] + "';";
  results.clear();
  this->Executar();

  ComandoSQL = "SELECT codigoconta FROM viagem WHERE codigo = '" + results[0]["codigoviagem"] + "';";
  results.clear();
  this->Executar();

  if (results.empty() || results[0]["codigoconta"] != CodigoUsuario.getValor())
  {
    throw invalid_argument("Atividade inexistente ou pertencente a outra conta");
  }

  ComandoSQL = "DELETE FROM atividade WHERE codigo = '" + CodigoAtividade.getValor() + "';";
  results.clear();
  this->Executar();

  if (status != SQLITE_OK)
  {
    throw invalid_argument("Erro na remoção da atividade");
  }
}

vector<Atividade> ModeloAtividade::Ler(Codigo &CodigoUsuario)
{
  ComandoSQL = "SELECT a.* FROM atividade a INNER JOIN destino d ON a.codigodestino = d.codigo INNER JOIN viagem t ON d.codigoviagem = t.codigo WHERE t.codigoconta = '" + CodigoUsuario.getValor() + "';";
  results.clear();
  this->Executar();

  if (status != SQLITE_OK)
  {
    throw invalid_argument("Erro na leitura das atividades");
  }

  vector<Atividade> atividades;
  for (size_t i = 0; i < results.size(); i++)
  {
    Codigo codigo = Codigo(results[i]["codigo"]);
    Nome nome = Nome(results[i]["nome"]);
    Data data = Data(results[i]["data"]);
    Horario horario = Horario(results[i]["horario"]);
    Duracao duracao = Duracao(results[i]["duracao"]);
    Dinheiro preco = Dinheiro(results[i]["preco"]);
    Avaliacao avaliacao = Avaliacao(results[i]["avaliacao"]);
    Atividade atividade = Atividade(codigo, nome, data, horario, duracao, preco, avaliacao);
    atividades.push_back(atividade);
  }
  return atividades;
}
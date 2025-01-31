#include "../../Includes/Servicos/Hospedagem.hpp"


void ModeloHospedagem::Criar(Codigo &CodigoUsuario, Codigo &CodigoHospedagemDestino, Hospedagem &NovaHospedagem)
{
    ComandoSQL = "SELECT codigoviagem FROM destino WHERE codigo = '" + CodigoHospedagemDestino.getValor() + "';";
    results.clear();
    this->Executar();

    ComandoSQL = "SELECT codigoconta from viagem WHERE codigo = '" + results[0]["codigoviagem"] + "';";
    results.clear();
    this->Executar();

    if (results.empty() || results[0]["codigoconta"] != CodigoUsuario.getValor())
    {
        throw invalid_argument("Viagem não existente ou pertencente a outra conta");
    }



    string CodigoHospedagem = NovaHospedagem.get("codigo").getValor();
    string NomeHospedagem = NovaHospedagem.get("nome").getValor();
    string PrecoDiariaHospedagem = NovaHospedagem.get("precodiaria").getValor();
    string AvaliacaoHospedagem = NovaHospedagem.get("avaliacao").getValor();

    ComandoSQL = "INSERT INTO hospedagem (codigo, nome, precodiaria, avaliacao, codigodestino) VALUES ('" + CodigoHospedagem + "', '" + NomeHospedagem + "', '" + PrecoDiariaHospedagem + "', '" + AvaliacaoHospedagem + "', '" + CodigoHospedagemDestino.getValor() + "');";
    results.clear();
    this->Executar();

  if (status != SQLITE_OK)
  {
    throw invalid_argument("Erro na criação da hospedagem");
  }
}

void ModeloHospedagem::Atualizar(Codigo &CodigoUsuario, Codigo &CodigoHospedagem, Hospedagem &HospedagemAtualizada)
{
    ComandoSQL = "SELECT codigodestino FROM hospedagem WHERE codigo = '" + CodigoHospedagem.getValor() + "';";
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
        throw invalid_argument("Hospedagem não existente ou pertencente a outra conta");
    }

    string NomeHospedagem = HospedagemAtualizada.get("nome").getValor();
    string PrecoDiariaHospedagem = HospedagemAtualizada.get("precodiaria").getValor();
    string AvaliacaoHospedagem = HospedagemAtualizada.get("avaliacao").getValor();

    ComandoSQL = "UPDATE hospedagem SET nome = '" + NomeHospedagem + "', precodiaria = '" + PrecoDiariaHospedagem + "', avaliacao = '" + AvaliacaoHospedagem + "' WHERE codigo = '" + CodigoHospedagem.getValor() + "';";
    results.clear();
    this->Executar();

  if (status != SQLITE_OK)
  {
    throw invalid_argument("Erro na atualização da hospedagem");
  }
}

void ModeloHospedagem::Remover(Codigo &CodigoUsuario, Codigo &CodigoHospedagem)
{

    ComandoSQL = "SELECT codigodestino FROM hospedagem WHERE codigo = '" + CodigoHospedagem.getValor() + "';";
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
        throw invalid_argument("Hospedagem inexistente ou pertencente a outra conta");
    }

    ComandoSQL = "DELETE FROM hospedagem WHERE codigo = '" + CodigoHospedagem.getValor() + "';";
    results.clear();
    this->Executar();

    if (status != SQLITE_OK)
    {
        throw invalid_argument("Erro na remoção da hospedagem");
    }
}

vector<Hospedagem> ModeloHospedagem::Ler(Codigo &CodigoUsuario)
{
    ComandoSQL = "SELECT l.* FROM hospedagem l INNER JOIN destino d ON l.codigodestino = d.codigo INNER JOIN viagem v ON d.codigoviagem = v.codigo WHERE v.codigoconta = '" + CodigoUsuario.getValor() + "';";
    results.clear();
    this->Executar();

    if (status != SQLITE_OK)
    {
        throw invalid_argument("Erro na leitura das hospedagens");
    }

    vector<Hospedagem> hospedagens;
    for (size_t i = 0; i < results.size(); i++)
    {
        Codigo codigo = Codigo(results[i]["codigo"]);
        Nome nome = Nome(results[i]["nome"]);
        Dinheiro precodiaria = Dinheiro(results[i]["precodiaria"]);
        Avaliacao avaliacao = Avaliacao(results[i]["avaliacao"]);
        Hospedagem hospedagem = Hospedagem(codigo, nome, precodiaria, avaliacao);
        hospedagens.push_back(hospedagem);
    }
    return hospedagens;
}
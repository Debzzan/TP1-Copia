#ifndef ATIVIDADE_ENTITY_INTERFACE_H
#define ATIVIDADE_ENTITY_INTERFACE_H

#include "../Dominios/Codigo.hpp"
#include "../Dominios/Nome.hpp"
#include "../Dominios/Data.hpp"
#include "../Dominios/Duracao.hpp"
#include "../Dominios/Dinheiro.hpp"
#include "../Dominios/Avaliacao.hpp"
#include "../Dominios/Horario.hpp"
#include "./Entidade.hpp"


class Atividade : public Entidade
{
private:
    Codigo codigo;
    Nome nome;
    Data data;
    Horario horario;
    Duracao duracao;
    Dinheiro preco;
    Avaliacao avaliacao;

public:
    Atividade(const Codigo &codigo, const Nome &nome, const Data &data, const Horario &horario, const Duracao &duracao, const Dinheiro &preco, const Avaliacao &avaliacao);

    void set(const Dominio &dominio, string NomeProprio) override;

    const Dominio &get(const string NomeProprio) const override;
};

#endif 
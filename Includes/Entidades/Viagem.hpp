#ifndef VIAGEM_ENTITY_INTERFACE_H
#define VIAGEM_ENTITY_INTERFACE_H

#include "../Dominios/Codigo.hpp"
#include "../Dominios/Nome.hpp"
#include "../Dominios/Data.hpp"
#include "../Dominios/Dinheiro.hpp"
#include "../Dominios/Avaliacao.hpp"
#include "./Entidade.hpp"

class Viagem : public Entidade
{
private:
    Codigo codigo;
    Nome nome;
    Avaliacao avaliacao;

public:
    Viagem(const Codigo &codigo, const Nome &nome, const Avaliacao &avaliacao);

    void set(const Dominio &dominio, string NomeProprio) override;

    const Dominio &get(const string NomeProprio) const override;
};

#endif
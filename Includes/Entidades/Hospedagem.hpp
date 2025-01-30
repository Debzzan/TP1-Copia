#ifndef HOSPEDAGEM_ENTITY_INTERFACE_H
#define HOSPEDAGEM_ENTITY_INTERFACE_H


#include "../Dominios/Codigo.hpp"
#include "../Dominios/Nome.hpp"
#include "../Dominios/Dinheiro.hpp"
#include "../Dominios/Avaliacao.hpp"
#include "./Entidade.hpp"

class Hospedagem : public Entidade
{
private:

    Codigo codigo;
    Nome nome;
    Dinheiro ValorDiaria;
    Avaliacao avaliacao;

public:
    Hospedagem(const Codigo &codigo, const Nome &nome, const Dinheiro &ValorDiaria, const Avaliacao &Avaliacao);

    void set(const Dominio &dominio, string NomeProprio) override;

    const Dominio &get(const string NomeProprio) const override;
};

#endif 
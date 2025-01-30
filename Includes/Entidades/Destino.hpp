#ifndef DESTINO_ENTITY_INTERFACE_H
#define DESTINO_ENTITY_INTERFACE_H

#include "../Dominios/Codigo.hpp"
#include "../Dominios/Nome.hpp"
#include "../Dominios/Data.hpp"
#include "../Dominios/Avaliacao.hpp"
#include "./Entidade.hpp"


class Destino : public Entidade
{
private:

    Codigo codigo;
    Nome nome;
    Data data_chegada;
    Avaliacao avaliacao;
    Data data_partida;


public:
    Destino(const Codigo &codigo, const Nome &nome, const Data &data_chegada, const Data &data_partida, const Avaliacao &avaliacao);

    void set(const Dominio &dominio, string NomeProprio) override;

    const Dominio &get(const string NomeProprio) const override;
};

#endif 
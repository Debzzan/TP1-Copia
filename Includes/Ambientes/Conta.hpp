#ifndef CONTA_AMBIENTE_INTERFACE_H
#define CONTA_AMBIENTE_INTERFACE_H

#include "../Interfaces/Apresentacao.hpp"
#include "../Interfaces/Servicos.hpp"


class AmbienteConta : public InterfaceApresentacao
{
private:
    InterfaceServicoConta *ServicoConta;

public:
    AmbienteConta(Codigo &CodigoUsuario) : InterfaceApresentacao(CodigoUsuario) {};

    void setServicoConta(InterfaceServicoConta *ServicoConta)
    {
        this->ServicoConta = ServicoConta;
    };

    void Autenticar();

    void Criar();

    void Sair();

    void Executar(Codigo &CodigoUsuario);

    ~AmbienteConta() override
    {
        delete ServicoConta;
    }

};

#endif 
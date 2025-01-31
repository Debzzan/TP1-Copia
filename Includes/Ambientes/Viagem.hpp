#ifndef VIAGEM_AMBIENTE_INTERFACE_H
#define VIAGEM_AMBIENTE_INTERFACE_H

#include "../Interfaces/Apresentacao.hpp"
#include "../Interfaces/Servicos.hpp"

class AmbienteViagem : public InterfaceApresentacao
{
private:

    InterfaceServicoViagem *ServicoViagem;

    void ConsultaCusto(Codigo CodigoViagem);

    void ListaDestinos(Codigo CodigoViagem);

    void ConsultaDestino();

    void ListaHospedagens(Codigo CodigoDestino);

    void ListaAtividades(Codigo CodigoDestino);

public:

    AmbienteViagem(Codigo &CodigoUsuario) : InterfaceApresentacao(CodigoUsuario) {};

    void setServicoViagem(InterfaceServicoViagem *ServicoViagem)
    {
        this->ServicoViagem = ServicoViagem;
    };

    void Executar(Codigo &CodigoUsuario) override;

    void Criar();

    void Atualizar();

    void Remover();

    void ListarTudo();

    void ConsultaViagem();

    ~AmbienteViagem() override
    {
        delete ServicoViagem;
    }
};

#endif 
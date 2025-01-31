#ifndef HOSPEDAGEM_AMBIENTE_HPP
#define HOSPEDAGEM_AMBIENTE_HPP

#include "../Interfaces/Apresentacao.hpp"
#include "../Interfaces/Servicos.hpp"

class AmbienteHospedagem : public InterfaceApresentacao
{
private:
    InterfaceServicoHospedagem *ServicoHospedagem;

public:

    AmbienteHospedagem(Codigo &CodigoUsuario) : InterfaceApresentacao(CodigoUsuario) {};

    void setServicoHospedagem(InterfaceServicoHospedagem *ServicoHospedagem)
    {
        this->ServicoHospedagem = ServicoHospedagem;
    };

    void Executar(Codigo &CodigoUsuario) override;

    void Criar();

    void Atualizar();

    void Remover();

    void Ler();

    ~AmbienteHospedagem() override
    {
        delete ServicoHospedagem;
    }

};

#endif 
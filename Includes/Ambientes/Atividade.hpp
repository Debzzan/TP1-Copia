#ifndef ATIVIDADE_AMBIENTE_HPP
#define ATIVIDADE_AMBIENTE_HPP

#include "../Interfaces/Apresentacao.hpp"
#include "../Interfaces/Servicos.hpp"

class AmbienteAtividade : public InterfaceApresentacao
{
private:
  InterfaceServicoAtividade *ServicoAtividade;

public:
  AmbienteAtividade(Codigo &CodigoUsuario) : InterfaceApresentacao(CodigoUsuario) {};

  void setServicoAtividade(InterfaceServicoAtividade *ServicoAtividade)
  {
    this->ServicoAtividade = ServicoAtividade;
  };

  void Executar(Codigo &CodigoUsuario);

  void Criar();

  void Atualizar();

  void Remover();

  void Ler();

  ~AmbienteAtividade() override
  {
    delete ServicoAtividade;
  }
};

#endif 
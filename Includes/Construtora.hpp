#ifndef CONSTRUTORA_INTERFACE_H
#define CONSTRUTORA_INTERFACE_H

#include "./Controladora.hpp"

#include "../Includes/Servicos/Conta.hpp"
#include "../Includes/Ambientes/Conta.hpp"

#include "../Includes/Servicos/Viagem.hpp"
#include "../Includes/Ambientes/Viagem.hpp"

#include "../Includes/Servicos/Destino.hpp"
#include "../Includes/Ambientes/Destino.hpp"

#include "../Includes/Servicos/Hospedagem.hpp"
#include "../Includes/Ambientes/Hospedagem.hpp"

#include "../Includes/Servicos/Atividade.hpp"
#include "../Includes/Ambientes/Atividade.hpp"

/**
 * @class Construtora
 * @brief Classe responsável pela construção das controladoras e serviços.
 * 
 * Esta classe fornece um método para construir e inicializar as controladoras com os serviços apropriados. 
 */
class Construtora
{
public:
  /**
   * @brief Constrói e inicializa as controladoras com os serviços apropriados.
   * @param controladora Ponteiro para a controladora a ser construída.
   */
  void construir(Controladora *controladora);
};

#endif
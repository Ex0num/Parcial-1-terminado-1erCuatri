/*
 * Cliente.h
 *
 *  Created on: 1 may. 2021
 *      Author: gabil
 */

	#ifndef CLIENTE_H_
	#define CLIENTE_H_

	#include "Relacion.h"


	int inicializar_array_cliente (Cliente* arrayRecibido, int limite);
	int buscarIndiceVacio_cliente(Cliente* arrayRecibido, int limite, int* pindiceVacioEncontrado);

	int alta_cliente (Cliente* arrayClienteRecibido, int limiteArrayRecibido, int* pidIncrementableDeClientes);
	int modificacion_cliente (Cliente* arrayClienteRecibido, int limiteArrayClienteRecibido);

	int imprimir_cliente_por_id (Cliente* arrayClienteRecibido, int limiteArrayCliente, int idIngresadoParaImprimir);
	int imprimir_cliente_por_indice (Cliente* arrayClienteRecibido, int limiteArrayCliente, int indiceIngresadoParaImprimir);
	int eliminar_cliente_por_id (Cliente* arrayClienteRecibido, int limiteArrayClienteRecibido, int idClienteRecibido);

	int utn_obtener_validar_IdCliente_devolverPosicion (Cliente* arrayClienteRecibido, int limiteArrayClienteRecibido, char* mensajeParaPedidoID, char* mensajeParaErrorID, int* valorIndiceID);


#endif /* CLIENTE_H_ */

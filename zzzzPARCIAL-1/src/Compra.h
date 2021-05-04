/*
 * Compra.h
 *
 *  Created on: 1 may. 2021
 *      Author: gabil
 */

	#ifndef COMPRA_H_
	#define COMPRA_H_

	#include "Relacion.h"


	int inicializar_array_compra (Compra* arrayRecibido, int limite);
	int buscarIndiceVacio_compra(Compra* arrayCompraRecibido, int limiteArrayCompraRecibido, int* pIndiceVacioEncontrado);
	int estadoCompra (Compra* arrayCompraRecibido, int limiteArrayCompraRecibido, int indiceDeLaCompra);
	int imprimir_compras_existentes_de_IDCliente (Compra* arrayListaCompras, int limiteListaCompras, int IdClienteRecibido);
	int contador_compras_de_un_IDCliente (Compra* arrayListaCompras, int limiteListaCompras, int IdClienteRecibido, int* pResultadoContadorCompras);
	int utn_obtener_validar_IdCompra (Compra* arrayCompraRecibido, int limiteArrayCompraRecibido, char* mensajeParaPedidoID, char* mensajeParaErrorID, int* pValorIndiceIDEncontrado);
	int calcularImporte (Compra* arrayCompraRecibido, int limiteArrayCompraRecibido, int indice, float* pResultadoCalculadoImporte);
	int contador_compras_de_un_IDCliente (Compra* arrayListaCompras, int limiteListaCompras, int IdClienteRecibido, int* pResultadoContadorCompras);
	int eliminar_compras_existentes_porIDCliente (Compra* arrayListaCompras, int limiteListaCompras, int IdClienteRecibido);


	#endif /* COMPRA_H_ */

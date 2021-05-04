/*
 * Relacion.h
 *
 *  Created on: 4 may. 2021
 *      Author: gabil
 */

	#ifndef RELACION_H_
	#define RELACION_H_


		typedef struct Pcliente
	{
		char nombre[30];
		char apellido[30];
		char cuit[18];
		int idCliente;
		int flagIsEmpty;

	}Cliente;

	typedef struct Pcompra
	{
		int contadorCantidadBarbijos;
		char colorBarbijo[32];
		char direccionDeEntrega[62];
		int estadoDeCompra;
		int IdCompra;
		int IdCliente;
		int flagIsEmpty;

	}Compra;


	int cancelar_compra (Compra* arrayCompraRecibido, int limiteArrayCompraRecibido, Cliente* arrayClienteRecibido, int limiteArrayClienteRecibido);
	int pagar_compra (Compra* arrayCompraRecibido, int limiteArrayCompraRecibido, Cliente* arrayClienteRecibido, int limiteArrayClienteRecibido);
	int realizar_compra (Compra* arrayCompraRecibido, int limiteArrayCompra, Cliente* arrayClienteRecibido, int limiteArrayClienteRecibido, int* pIDCompraAutoIncremental );
	int imprimir_cliente_por_IDCompra (Compra* arrayCompraRecibido, int limiteArrayCompraRecibido, Cliente* arrayClienteRecibido, int limiteArrayClienteRecibido, int idCompra);
	int bajar_cliente (Cliente* arrayClienteRecibido, int limiteArrayClienteRecibido, Compra* arrayCompraRecibido, int limiteArrayCompra);
	int imprimir_clientes_existentesY_CantidadCompras (Cliente* arrayClienteRecibido, int limiteArrayCliente, Compra* arrayCompraRecibido, int limiteArrayCompra);



	#endif /* RELACION_H_ */

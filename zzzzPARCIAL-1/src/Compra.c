/*
 * Compra.c
 *
 *  Created on: 1 may. 2021
 *      Author: gabil
 */

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	#include "Compra.h"
	#include "Cliente.h"
	#include "FuncionesEstandar.h"



	int inicializar_array_compra (Compra* arrayRecibido, int limite)
		{
			int retorno = -1;

			if (arrayRecibido != NULL && limite > 0)
			{
				retorno = 0;

				for (int i = 0 ; i < limite ; i++ )
				{
					arrayRecibido[i].flagIsEmpty = 1;
					arrayRecibido[i].IdCompra = 0;
				}
			}
			return retorno;
		}

	 int buscarIndiceVacio_compra(Compra* arrayCompraRecibido, int limiteArrayCompraRecibido, int* pIndiceVacioEncontrado)
	 	{
	 		int retorno = -1;

	 		if (arrayCompraRecibido != NULL && limiteArrayCompraRecibido > 0 && pIndiceVacioEncontrado != NULL) //Validamos parametros
	 		{
	 			retorno = -2;

	 			for (int i = 0 ; i < limiteArrayCompraRecibido ; i++) //Recorremos la lista de compras.
	 			{
	 				if (arrayCompraRecibido[i].flagIsEmpty == 1 && arrayCompraRecibido[i].IdCliente == 0) //Si ese indice el flagEmpty da que esta vacio y el id es 0 (como se inicializa)
	 				{
	 					*pIndiceVacioEncontrado = i; //Pasamos el valor del indice donde hay lugar para adjuntar datos de otra compra.
	 					retorno = 0;
	 					break;
	 				}
	 			}
	 		}

	 		return retorno;
	 	}




	int estadoCompra (Compra* arrayCompraRecibido, int limiteArrayCompraRecibido, int indiceDeLaCompra)
	{
		int resultado = -1;

		if (arrayCompraRecibido != NULL && limiteArrayCompraRecibido > 0 && indiceDeLaCompra < limiteArrayCompraRecibido && indiceDeLaCompra >= 0)
		{
			if (arrayCompraRecibido[indiceDeLaCompra].estadoDeCompra == 1)
			{
				resultado = 1;
			}
			else
			{
				resultado = 0;
			}
		}

		return resultado;
	}





	int calcularImporte (Compra* arrayCompraRecibido, int limiteArrayCompraRecibido, int indice, float* pResultadoCalculadoImporte)
	{
		float retorno = -1;

		if (arrayCompraRecibido != NULL && limiteArrayCompraRecibido > 0 && indice >= 0 && indice < limiteArrayCompraRecibido && pResultadoCalculadoImporte != NULL)
		{
			float multiplicador1 = 0;
			float resultado;

			multiplicador1 = arrayCompraRecibido[indice].contadorCantidadBarbijos;

			resultado = multiplicador1 * 50;
			*pResultadoCalculadoImporte = resultado;

			retorno = 0;
		}
		else
		{
			retorno = -2;
		}

		return retorno;
	}


	int utn_obtener_validar_IdCompra (Compra* arrayCompraRecibido, int limiteArrayCompraRecibido, char* mensajeParaPedidoID, char* mensajeParaErrorID, int* pValorIndiceIDEncontrado)
			 	 {
			 		 int retorno = -1;

			 		 if (arrayCompraRecibido != NULL && limiteArrayCompraRecibido > 0 && mensajeParaPedidoID != NULL && mensajeParaErrorID != NULL && pValorIndiceIDEncontrado != NULL)
			 		 {
			 			retorno = -2;
			 			char buffer[1000];
			 			int resultadoDelBuffer;
			 			int numeroIntBuffer;
			 			int flagErrorEnID = 0;

			 			printf ("%s", mensajeParaPedidoID);
			 			fflush(stdin);
			 			fgets (buffer,1000,stdin);

			 			resultadoDelBuffer = strnlen(buffer,1000);

			 			 if( resultadoDelBuffer > 6 )
			 			 {
			 				 flagErrorEnID++;
			 			 }

			 			 for (int p = 0 ; buffer[p] != '\0' ; p = p+1)
						 {
							if ( buffer[p] == '\n' )
							{
								buffer[p] = '\0';
								break;
							}
						 }

			 			 for (int i = 0 ; buffer[i] != '\0' ; i = i+1)
			 			 {
			 				if ( buffer[i] < '0' || buffer[i] > '9' )
			 				{
			 					flagErrorEnID++;
			 				}
			 			 }

			 			int flagIDEncontrado = 0;

			 			if (flagErrorEnID == 0) //Si esta todo correcto
			 			{
			 				flagIDEncontrado = 1;

			 				numeroIntBuffer = atoi(buffer); //Convetir el id ingresado en un int


			 				//HASTA ACA ES UN GET ID

			 				for ( int j = 0 ; j < limiteArrayCompraRecibido ; j = j+1 ) //Vamos a recorrer la lista de compra
			 				{
			 					if (arrayCompraRecibido[j].IdCompra == numeroIntBuffer && arrayCompraRecibido[j].flagIsEmpty == 0) //Si encontramos que un id de compra vale lo mismo que el Id que ingreso el usuario y el flagExistencia da que existe...
			 					{
			 						flagIDEncontrado = 2;
			 						retorno = numeroIntBuffer; //Retornamos el valor del ID que se ingreso y al parecer pertenece a una compra.
			 						*pValorIndiceIDEncontrado = j; //Pasamos por referencia al puntero el valor de la posicion donde pertence esa compra encontrada.
			 						break;
			 					}
			 				}

			 			}
			 			else
			 			{
			 				printf ("%s",mensajeParaErrorID);
			 				retorno = -3;
			 			}

			 			if (flagIDEncontrado == 1)
			 			{
			 				printf ("%s",mensajeParaErrorID);
			 			}
			 		 }


			 		 return retorno;

			 	 }

	int imprimir_compras_existentes_de_IDCliente (Compra* arrayListaCompras, int limiteListaCompras, int IdClienteRecibido)
	{
		int retorno = -1;

		if (arrayListaCompras != NULL && limiteListaCompras > 0 && IdClienteRecibido > 0 && IdClienteRecibido < 9999)
		{
			int contadorComprasEncontradas = 0;

			for (int i = 0 ; i < limiteListaCompras ; i++) //Recorro lista compras
			{
				if (arrayListaCompras[i].IdCliente == IdClienteRecibido &&  arrayListaCompras[i].flagIsEmpty == 0) //Si encuentra id que coincide con una comra y esta existe
				{
					contadorComprasEncontradas++;
					printf ("\nDatos de compra:"
							"\n ID-Cliente: %d"
							"\n Direccion de entrega: %s"
							" Cantidad de barbijos: %d"
							"\n Color de barbijo: %s"
							"\n Estado de la compra: %d (1 ES PAGADA | 0 ES PENDIENTE) "
							"\n ID-Compra: %d\n",arrayListaCompras[i].IdCliente, arrayListaCompras[i].direccionDeEntrega, arrayListaCompras[i].contadorCantidadBarbijos, arrayListaCompras[i].colorBarbijo, arrayListaCompras[i].estadoDeCompra, arrayListaCompras[i].IdCompra);
				}
			}

			if (contadorComprasEncontradas == 0)
			{
				printf ("\nNo se encontraron compras realizadas por el ID-Cliente ingresado.\n");
				retorno = 1;
			}
			else
			{
				retorno = 0;
			}

		}

		return retorno;
	}

	int eliminar_compras_existentes_porIDCliente (Compra* arrayListaCompras, int limiteListaCompras, int IdClienteRecibido)
	{
		int retorno = -1;

		if (arrayListaCompras != NULL &&  limiteListaCompras > 0 && IdClienteRecibido > 0) //Valido parametros
		{
			int contadorComprasBorradas = 0;

			for (int i = 0 ; i < limiteListaCompras ; i++) //Recorro lista compras
			{
				if (arrayListaCompras[i].IdCliente == IdClienteRecibido && arrayListaCompras[i].flagIsEmpty == 0) //Si el id cliente coincide con alguna compra
				{
					//La elimino, marcando el flagEmpty en vacio y poniendo su id en un valor invalido como cuando lo inicializo.

					contadorComprasBorradas++;
					arrayListaCompras[i].flagIsEmpty = 1;
					arrayListaCompras[i].IdCompra = 0;
				}
			}

			retorno = contadorComprasBorradas; //Voy a devolver por retorno la cantidad de compras que borre. Seran 0 o mas si la baja salio bien.

		}

		return retorno;
	}

	int contador_compras_de_un_IDCliente (Compra* arrayListaCompras, int limiteListaCompras, int IdClienteRecibido, int* pResultadoContadorCompras)
	  {
		  int retorno = -1;

		  if (arrayListaCompras != NULL && limiteListaCompras > 0 && IdClienteRecibido > 0 && pResultadoContadorCompras != NULL) //Valido parametros.
		  {
			  retorno = -2;

			  int contadorCompras = 0; //Creo un contador de las compras que empieza obviamente en 0.

			for (int i = 0 ; i < limiteListaCompras ; i++) //Recorrer lista de compras.
			{
				if (arrayListaCompras[i].IdCliente == IdClienteRecibido && arrayListaCompras[i].flagIsEmpty == 0) //Si hay una compra que coindice su campo de IDCliente con el ID que buscamos y el flag que existe da positivo.
				{
					contadorCompras++;
				}
			}

			if (contadorCompras == 0) //Si el contador no encontro ninguna compra devolvemos -3
			{
				retorno = -3;
			}
			else if (contadorCompras > 0) //Si se encontro una compra o mas, devuelvo 0
			{
				*pResultadoContadorCompras = contadorCompras;
				retorno = 0;
			}
		  }

		  return retorno;
	  }



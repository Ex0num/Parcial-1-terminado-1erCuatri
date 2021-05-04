/*
 * Relacion.c
 *
 *  Created on: 4 may. 2021
 *      Author: gabil
 */

	#include <stdio.h>
	#include <stdlib.h>

	#include "Cliente.h"
	#include "FuncionesEstandar.h"
	#include "Compra.h"
	#include "Relacion.h"


int cancelar_compra (Compra* arrayCompraRecibido, int limiteArrayCompraRecibido, Cliente* arrayClienteRecibido, int limiteArrayClienteRecibido)
	{
		int retorno = -1;

		if ( arrayCompraRecibido != NULL && limiteArrayCompraRecibido > 0 && arrayClienteRecibido != NULL && limiteArrayClienteRecibido > 0) //Valido parametros.
		{
			retorno = -2;

			//Pido el ID de la compra que quiero cancelar.
			int indiceObtenidoIDCompra = -1;
			int resultadoObtencionIDCompra;
			resultadoObtencionIDCompra = utn_obtener_validar_IdCompra (arrayCompraRecibido, limiteArrayCompraRecibido, "\n Ingrese el ID de la compra que quiere cancelar.\n ", "\n El id que ingreso es invalido o no se pudo encontrar una compra con ese ID.\n", &indiceObtenidoIDCompra);

			//Valido si la compra esta en un estado pendiente de pagar y si se pudo obtener una compra existente.
			int estadoDeCompraValidacion;
			estadoDeCompraValidacion = estadoCompra (arrayCompraRecibido, limiteArrayCompraRecibido, indiceObtenidoIDCompra);

			if (resultadoObtencionIDCompra > 0 && estadoDeCompraValidacion == 0) //Si solo si el estado de la compra esta en "Pendiente de pagar/cobrar y existe tal compra."
			{
				//Imprimo los datos del cliente al que le pertenece  la compra de la cual estamos refiriendonos con el ID que se valido.
				printf ("\nLos datos del cliente al cual le pertenece la compra que usted ingreso son:\n");
				imprimir_cliente_por_IDCompra (arrayCompraRecibido, limiteArrayCompraRecibido, arrayClienteRecibido, limiteArrayClienteRecibido, resultadoObtencionIDCompra);

				int resultadoDeConfirmacion;
				resultadoDeConfirmacion = utn_obtener_orden_si_no ("\n Ingrese SI o NO para confirmar la cancelacion de la compra.\n", "\n Error en el ingreso de su orden.\n", 10);
				if (resultadoDeConfirmacion == 0) //Si la confirmacion es 1 (OSEA "SI").
				{
					arrayCompraRecibido[indiceObtenidoIDCompra].flagIsEmpty = 1;
					arrayCompraRecibido[indiceObtenidoIDCompra].IdCompra = 0;

					printf ("\n La cancelacion de la compra fue exitosa.\n");
				}
				else if (resultadoDeConfirmacion == 1)
				{
					printf ("\n El proceso de cancelacion de la compra ha sido detenido y cancelado.\n");
				}


			}
			else if (estadoDeCompraValidacion == 1) //Si el estado es "Cobrado (0)"
			{
				printf ("\nLa compra no se puede cancelar porque ya fue abonada.\n");
			}

		}

		return retorno;
	}

int pagar_compra (Compra* arrayCompraRecibido, int limiteArrayCompraRecibido, Cliente* arrayClienteRecibido, int limiteArrayClienteRecibido)
	{
		int retorno = -1;

		if (arrayCompraRecibido != NULL && limiteArrayCompraRecibido > 0 && arrayClienteRecibido != NULL && limiteArrayClienteRecibido > 0)
		{
			//Pedir ID de la venta y validar que exista una venta con ese ID.
			int indiceObtenidoIDCompra;
			int resultadoObtencionIDCompra;
			resultadoObtencionIDCompra = utn_obtener_validar_IdCompra (arrayCompraRecibido, limiteArrayCompraRecibido, "\n Ingrese el ID de la compra que quiere abonar.\n ", "\n El id que ingreso es invalido o no se pudo encontrar una compra con ese ID.\n", &indiceObtenidoIDCompra);


			int estadoDeCompraValidacion = estadoCompra (arrayCompraRecibido, limiteArrayCompraRecibido, indiceObtenidoIDCompra); //Valido si la compra esta en un estado pendiente de pagar
			if (estadoDeCompraValidacion == 1)
			{
				printf ("\nLa compra ya fue abonada.\n"); //Si existe el caso de que el estado de la compra es abonado, lo aviso.
			}

			if (resultadoObtencionIDCompra > 0 && estadoDeCompraValidacion == 0) //Si la ID es valida y existe y al parecer pertenece a una compra, ademas de que la compra esta pendiente de pagarse.
			{
				//Imprimir cliente al que le pertenece la compra.
				imprimir_cliente_por_indice (arrayClienteRecibido, limiteArrayClienteRecibido, indiceObtenidoIDCompra);

				//Calculamos el importe de lo que debe pagar de esa compra. En cuestion de precio total por c/u barbijos. ( $50 * Cantidad barbijos ).
				float resultadoCalculadoImporteAPagar;
				calcularImporte (arrayCompraRecibido, limiteArrayCompraRecibido, indiceObtenidoIDCompra, &resultadoCalculadoImporteAPagar);

				//Le mostramos al usuario cuanto tiene que pagar segun el importe calculado anteriormente.
				printf ("\n El importe a pagar segun la cantidad de barbijos y el precio por c/u $50 es de: %f \n", resultadoCalculadoImporteAPagar);

				//Obtener la orden de confirmacion del pago.
				int resultadoConfirmacion;
				resultadoConfirmacion = utn_obtener_orden_si_no ("\n Para confirmar el pago de la compra ingrese SI o NO.\n", "\n Error. Por favor ingrese SI o NO \n", 10);

				if (resultadoConfirmacion == 1) //Si la confirmacion fue SI.
				{
					//Confirmamos pago.
					arrayCompraRecibido[indiceObtenidoIDCompra].estadoDeCompra = 1; // 1 SIGNIFICA -> PAGO o "COBRADA".
					printf ("\n Su compra ha sido abonada correctamente. ¡Muchas gracias! \n");
				}
				else if (resultadoConfirmacion != 1) //Si la confirmacion fue NO.
				{
					//Cancelamos el proceso de pago.
					printf ("\n El proceso de pago de la compra ha sido cancelado.\n");
				}

			}
			else
			{
				//Ya hay un printf que informa que el id no existe en co-relacion a algun cliente o es invalido.
				retorno = -2;
			}
		}
		return retorno;
	}

int realizar_compra (Compra* arrayCompraRecibido, int limiteArrayCompra, Cliente* arrayClienteRecibido, int limiteArrayClienteRecibido, int* pIDCompraAutoIncremental )
	{
		int retorno = -1;

		if (arrayCompraRecibido != NULL && limiteArrayCompra > 0 && arrayClienteRecibido != NULL && limiteArrayClienteRecibido > 0 && pIDCompraAutoIncremental != NULL) //Validamos parametros.
		{
			retorno = -2;

			//Buscamos indice vacio para nueva compra.
			int resultadoBusquedaIndiceVacio;
			int indiceVacioEncontrado; //Guardamos el indice vacio encontrado.
			resultadoBusquedaIndiceVacio = buscarIndiceVacio_compra(arrayCompraRecibido, limiteArrayCompra, &indiceVacioEncontrado);

			if (resultadoBusquedaIndiceVacio == 0) //Si hay lugar para una nueva compra, adelante.
			{
				int indiceValorIDIngresado = -1;
				int resultadoObtencionID;
				//Obtenemos el ID del cliente que desea realizar la compra, validamos si existe un cliente con ese ID y guardamos el Indice.
				resultadoObtencionID = utn_obtener_validar_IdCliente_devolverPosicion (arrayClienteRecibido, limiteArrayClienteRecibido, "\n Ingrese el ID-Cliente para poder realizar la compra. \n", "\n El ID ingresado no pertenece a ningun cliente.\n", &indiceValorIDIngresado);

				if (resultadoObtencionID > 0) //Si el ID es valido y coincidio con algun cliente en la lista.
				{
					retorno = -3;

					//Imprimir el cliente para que el usuario vea a nombre de quien va a realizar la compra (segun el id que ingreso).
					imprimir_cliente_por_id ( arrayClienteRecibido, limiteArrayClienteRecibido, resultadoObtencionID );

					Compra buffer; //Creamos buffer y empezamos la obtencion de datos.

					int resultadoObtencionCantidadBarbijos = utn_obtener_validar_Edad ("\n Ingrese la cantidad de barbijos. \n", "\n Error en el ingreso de la cantidad.\n", &buffer.contadorCantidadBarbijos, 10);
					int resultadoObtencionDireccion = utn_obtener_validar_Texto ("\n Ingrese la direccion del domicilio para la entrega. \n", "\n Error en el ingreso de la direccion.\n ", buffer.direccionDeEntrega, 60, 10);
					int resultadoObtencionColor = utn_obtener_validar_Nombre ("\n Ingrese el color de los barbijos. \n", "\n Error en el ingreso del color. \n", buffer.colorBarbijo , 32, 10);

					//Si la obtencion de datos salio bien
					if (resultadoObtencionCantidadBarbijos == 0 && resultadoObtencionDireccion == 0 &&  resultadoObtencionColor == 0)
					{
						//Cargamos al buffer el id de compra que corresponde que viene desde el puntero.
						buffer.IdCompra = *pIDCompraAutoIncremental;
						buffer.estadoDeCompra = 0; // El estado de la compra va a estar en "Pendiente de cobrar". ( PENDIENTE DE COBRAR = 0 || PAGO = 1 )
						buffer.flagIsEmpty = 0; //Ya la compra existe.
						buffer.IdCliente = resultadoObtencionID; //Guardamos tambien el valor del IDCliente que ingreso anteriormente.

						arrayCompraRecibido[indiceVacioEncontrado] = buffer; //Hacemos el pasaje de datos. (USANDO EL INDICE VACIO QUE ENCONTRAMOS AL PRINCIPIO).
						*pIDCompraAutoIncremental = *pIDCompraAutoIncremental + 1; //Le sumamos 1 al valor ID para la proxima compra.
						retorno = 0;
						printf ("La compra ha sido satisfactoria. La ID de su COMPRA realizada es: %d.\n", arrayCompraRecibido[indiceVacioEncontrado].IdCompra);
					}
					else
					{
						printf ("\n Error en la obtencion de datos.\n");
					}

				}
				else
				{
					printf ("\n Error. La ID ingresada no pertenece a ningun cliente. \n");
				}


			}
			else
			{
				printf ("\n Error. No hay lugar para mas compras.\n");
			}
		}
		return retorno;
	}



int imprimir_cliente_por_IDCompra (Compra* arrayCompraRecibido, int limiteArrayCompraRecibido, Cliente* arrayClienteRecibido, int limiteArrayClienteRecibido, int idCompra)
  {
	  int retorno = -1;

	  if ( arrayCompraRecibido != NULL && limiteArrayCompraRecibido > 0 && arrayClienteRecibido != NULL && limiteArrayClienteRecibido > 0 && idCompra > 0 && idCompra < 9999) //Valido parametros.
	  {
		  int idClienteDeLaCompraEncontrada; //Voy a guardar el id del cliente que se encuentre en la compra que encontre

		  for ( int i = 0 ; i < limiteArrayCompraRecibido ; i++ )
		  {
			  if (arrayCompraRecibido[i].IdCompra == idCompra && arrayCompraRecibido[i].flagIsEmpty == 0) //Busco por id en la lista de compras
			  {
				  idClienteDeLaCompraEncontrada = arrayCompraRecibido[i].IdCliente; //Si coincide el id de compra y existe, guardo el ID cliente en una variable.
				  break;
			  }
		  }

		  //Hago la busqueda del IdCliente que ingrese en la lista de clientes y lo imprimo
		  imprimir_cliente_por_id (arrayClienteRecibido, limiteArrayClienteRecibido, idClienteDeLaCompraEncontrada);

		retorno = 0;
	  }

	  return retorno;
  }


int bajar_cliente (Cliente* arrayClienteRecibido, int limiteArrayClienteRecibido, Compra* arrayCompraRecibido, int limiteArrayCompra)
  {
	 int retorno = -1;

	 if (arrayClienteRecibido != NULL && limiteArrayClienteRecibido > 0 && arrayCompraRecibido != NULL && limiteArrayCompra ) //Verifico parametros.
	 {
		 //Obtengo el id y verifico si es valido y si lo es, devuelvo por referencia a que cliente pertenece osease el indice. (retorno el ID validado)
		 int indiceIDDelCliente = -1;
		 int resultadoObtencionID;
		 resultadoObtencionID = utn_obtener_validar_IdCliente_devolverPosicion (arrayClienteRecibido, limiteArrayClienteRecibido,"\n Ingrese el ID del cliente a borrar \n", "\n Error, no se pudo encontrar un cliente con esa ID. \n", &indiceIDDelCliente);

		 if (resultadoObtencionID > 0) //Si la obtencion del ID salio bien y existe una posicion con ese ID.
		 {
			 //Aviso al usuario a QUE cliente va a dar de baja.
			 printf ("\n El cliente y las compras pertenecientes al mismo que va a dar de baja es el siguiente: \n");
			 imprimir_cliente_por_indice (arrayClienteRecibido, limiteArrayClienteRecibido, indiceIDDelCliente);

			 //Aviso al usuario QUE compras va a dar de baja (que pertenecen a ese cliente) SI EXISTE ALGUNA COMPRA. Sino le aviso que no hubo compras realizadas (dentro de la func).
			 imprimir_compras_existentes_de_IDCliente ( arrayCompraRecibido, limiteArrayCompra, resultadoObtencionID);

			 //Pregunto por la confirmacion de la eliminacion del cliente.
			 int resultadoDeConfirmacion;
			 resultadoDeConfirmacion = utn_obtener_orden_si_no ("\n Ingrese SI o NO para confirmar la eliminacion del cliente junto a todas sus compras. \n", "\n Error en el ingreso de su orden. Ingrese SI o NO\n", 10);
			 if (resultadoDeConfirmacion == 1) //Si solo si el resultado de la confirmacion fue "SI", continuo.
			 {
				 //Elimino todas las compras del cliente.
				 int resultadoEliminacionCompras;
				 resultadoEliminacionCompras = eliminar_compras_existentes_porIDCliente (arrayCompraRecibido, limiteArrayCompra, resultadoObtencionID);

				if (resultadoEliminacionCompras >= 0)
				{
					printf ("\nLa cantidad de compras eliminadas pertenecientes al ID-Cliente que se ingreso es de: %d\n",resultadoEliminacionCompras);
				}

				//Elimino el cliente que tenga el ID que se ingreso y se confirmo eliminar.
				int resultadoEliminacionCliente;
				resultadoEliminacionCliente = eliminar_cliente_por_id (arrayClienteRecibido, limiteArrayClienteRecibido, resultadoObtencionID);

				//Aviso que salio todo bien.
				if (resultadoEliminacionCliente == 0)
				{
					 printf ("\n La eliminacion del cliente ha sido realizada. Ya no existe el cliente ni sus compras realizadas.\n");
				}
			 }
			 else
			 {
				 printf ("\n La eliminacion del cliente fue cancelada.\n");
			 }
		 }
		 else if (resultadoObtencionID == -3) //Si el id es valido pero no se encontro un cliente con ese id.
		 {
			 printf ("\n Error, no se pudo encontrar un cliente con esa ID. \n");
		 }
		 else
		 {
			 printf ("\n Error en el ingreso de esa ID. \n");
		 }
	 }

	  return retorno;
  }


int imprimir_clientes_existentesY_CantidadCompras (Cliente* arrayClienteRecibido, int limiteArrayCliente, Compra* arrayCompraRecibido, int limiteArrayCompra)
 	{
 		int retorno = -1;

 		if (arrayClienteRecibido != NULL && limiteArrayCliente > 0 && arrayCompraRecibido != NULL && limiteArrayCompra > 0) //Valido parametros.
 		{
 			retorno = -2;

 			// Agarro la lista de clientes y me fijo cuales existen, e imprimo todos los existentes junto a sus datos.

 			printf("\nLa lista de clientes es la siguiente:\n");
 			for (int i = 0 ; i < limiteArrayCliente ; i++) //Recorro lista de clientes
 			{
 				if (arrayClienteRecibido[i].flagIsEmpty == 0 && arrayClienteRecibido[i].idCliente > 0) //Si encuentro un cliente existente. -> Imprimos datos.
 				{
 					printf ("\n"
 							"Nombre: %s\n"
 							"Apellido: %s\n"
 							"Cuit: %s\n"
 							"ID-Cliente: %d\n"
 							"INDICE: %d\n",arrayClienteRecibido[i].nombre, arrayClienteRecibido[i].apellido, arrayClienteRecibido[i].cuit, arrayClienteRecibido[i].idCliente, i);

 					// Calculo cuantas compras realizo ese cliente.
 					int contadorComprasCliente;
 					contador_compras_de_un_IDCliente (arrayCompraRecibido, limiteArrayCompra, arrayClienteRecibido[i].idCliente, &contadorComprasCliente);

 					//Imprimo la cantidad de compras que posee el cliente.
 					printf ("La cantidad de compras realizadas son: %d\n",contadorComprasCliente);
 				}
 			}
 			retorno = 0;
 		}

 		return retorno;
 	}

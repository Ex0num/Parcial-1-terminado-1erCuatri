/*
 * Codigo-FuncionesClientes.c
 *
 *  Created on: 30 abr. 2021
 *      Author: gabil
 */

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	#include "Cliente.h"
	#include "FuncionesEstandar.h"
	#include "Compra.h"



int inicializar_array_cliente (Cliente* arrayRecibido, int limite)
	{
		int retorno = -1;

		if (arrayRecibido != NULL && limite > 0)
		{
			retorno = 0;

			for (int i = 0 ; i < limite ; i++ )
			{
				arrayRecibido[i].flagIsEmpty = 1;
				arrayRecibido[i].idCliente = 0;
			}
		}
		return retorno;
	}

 int alta_cliente (Cliente* arrayClienteRecibido, int limiteArrayRecibido, int* pidIncrementableDeClientes)
 {
	 int retorno = -1;

	 if (arrayClienteRecibido != NULL && limiteArrayRecibido > 0 && pidIncrementableDeClientes != NULL) // Verifico parametros.
	 {
		 retorno = -2;

		 int indiceVacioEncontrado;
		 int resultadoDeIndiceVacio;
		 resultadoDeIndiceVacio = buscarIndiceVacio_cliente( arrayClienteRecibido, limiteArrayRecibido, &indiceVacioEncontrado); // Buscar si hay lugar vacio para cliente y devolverlo en retorno.

		 if (resultadoDeIndiceVacio == 0)
		 {
			 Cliente bufferDeCliente; // Crear un buffer para guardar los datos.

			 // Obtener datos de cliente.
			 int resultadoObtencionNombre = utn_obtener_validar_Nombre ("\n Ingrese nombre \n", "\n Error en el ingreso del nombre \n", bufferDeCliente.nombre, 30, 10);
			 int resultadoObtencionApellido = utn_obtener_validar_Apellido ("\n Ingrese apellido \n", "\n Error en el ingreso del apellido \n", bufferDeCliente.apellido, 30, 10);
			 int resultadoObtencionCuit = utn_obtener_validar_Cuit ("\n Ingrese cuit. Puede usar el guion o ingresar el numero todo junto. \n", "\n Error en el ingreso del cuit \n", bufferDeCliente.cuit, 18, 10);

			 // Validar los datos de cliente.
			 if (resultadoObtencionNombre == 0 && resultadoObtencionApellido == 0 && resultadoObtencionCuit == 0)
			 {

				bufferDeCliente.idCliente = *pidIncrementableDeClientes; // Hacer pasos finales como asignarle el ID en el buffer y poner el flagEmpty en 0
				bufferDeCliente.flagIsEmpty = 0;

				// Cargar datos del buffer a la posicion vacia encontrada anteiortemen del arrayRecibido
				arrayClienteRecibido[indiceVacioEncontrado] = bufferDeCliente;

				// incrementar el id para la proxima alta.
				 (*pidIncrementableDeClientes)++;

				 // Aviso de que salio bien el alta e informar el valor de ID.
				 printf ("\n El cliente ha sido dado de alta de forma satisfactoria. \n Su numero ID es: %d \n", arrayClienteRecibido[indiceVacioEncontrado].idCliente);
				 retorno = 0;
			 }
			 else
			 {
				printf ("\n Error en la obtencion de datos. \n");
				retorno = -4;

			 }
		 }
		 else
		 {
			 printf ("\n No hay suficiente espacio para otro cliente. \n");
			 retorno = -3;
		 }
	 }
	 return retorno;

 }

 int buscarIndiceVacio_cliente(Cliente* arrayRecibido, int limite, int* pindiceVacioEncontrado)
 	{
 		int retorno = -1;

 		if (arrayRecibido != NULL && limite > 0 && pindiceVacioEncontrado != NULL )
 		{
 			retorno = -2;

 			for (int i = 0 ; i < limite ; i++)
 			{
 				if (arrayRecibido[i].flagIsEmpty == 1)
 				{
 					*pindiceVacioEncontrado = i;
 					retorno = 0;
 					break;
 				}
 			}
 		}

 		return retorno;
 	}






  int modificacion_cliente (Cliente* arrayClienteRecibido, int limiteArrayClienteRecibido)
  {
	  int retorno = -1;

	  if (arrayClienteRecibido != NULL && limiteArrayClienteRecibido > 0) //Valido parametros
	  {
		//Pedir el ID del cliente que quiero modificar, y lo validamos para ver si existe o no ese cliente.
		int indiceIDClienteIngresado = -1;
		int resultadoObtencionIDCliente;
		resultadoObtencionIDCliente = utn_obtener_validar_IdCliente_devolverPosicion ( arrayClienteRecibido, limiteArrayClienteRecibido, "\n Ingrese ID del cliente a modificar. \n", "\n Error, no se pudo encontrar un cliente con esa ID. \n", &indiceIDClienteIngresado);

		if (resultadoObtencionIDCliente > 0) //Si la funcion salio bien
		{
			//Imprimir al usuario el cliente que va a modificar a continuacion.
			imprimir_cliente_por_indice (arrayClienteRecibido, limiteArrayClienteRecibido, indiceIDClienteIngresado);

			//Permitimos ingresar un nuevo nombre, apellido y cuit.
			Cliente bufferModificacionDatos; //Creo un buffer que le voy a guardar los nuevos datos y el ID ya validado.

 			int resultadoObtencionNombre = utn_obtener_validar_Nombre ("\n Ingrese el nuevo nombre \n", "\n Error en el ingreso del nombre \n", bufferModificacionDatos.nombre, 30, 10);
			int resultadoObtencionApellido = utn_obtener_validar_Apellido ("\n Ingrese el nuevo apellido \n", "\n Error en el ingreso del apellido \n", bufferModificacionDatos.apellido, 30, 10);
			int resultadoObtencionCuit = utn_obtener_validar_Cuit ("\n Ingrese el nuevo cuit. Puede usar el guion o ingresar el numero todo junto. \n", "\n Error en el ingreso del cuit \n", bufferModificacionDatos.cuit, 18, 10);
			bufferModificacionDatos.idCliente = resultadoObtencionIDCliente;
			bufferModificacionDatos.flagIsEmpty = 0;

			if (resultadoObtencionNombre == 0 && resultadoObtencionApellido == 0 && resultadoObtencionCuit == 0) //Si la obtencion de los nuevos datos salio bien.
			{
				arrayClienteRecibido[indiceIDClienteIngresado] = bufferModificacionDatos; //Copio los nuevos datos al indice de donde el cliente ingreso el ID.
				retorno = 0;
			}
			else
			{
				retorno = -3;
				printf ("\nLa obtencion de los nuevos datos salio mal.\n");
			}

		}
		else
		{
			printf("\n Error, no se pudo encontrar un cliente con esa ID. \n");
			retorno = -2;
		}
	  }

	  return retorno;
  }


  int utn_obtener_validar_IdCliente_devolverPosicion (Cliente* arrayClienteRecibido, int limiteArrayClienteRecibido, char* mensajeParaPedidoID, char* mensajeParaErrorID, int* valorIndiceID)
  	 {
  		 int retorno = -1;
  		int flagErrorEnID = 0;

  		 if (arrayClienteRecibido != NULL && limiteArrayClienteRecibido > 0 && mensajeParaPedidoID != NULL && mensajeParaErrorID != NULL && valorIndiceID != NULL) //Valido parametros
  		 {
  			retorno = -2;
  			char buffer[1000]; //Creo un buffer para obtener la ensalada que me pueden ingresar.
  			int resultadoDelBuffer;
  			int numeroIntBuffer;

  			printf ("%s", mensajeParaPedidoID);
  			fflush(stdin);
  			fgets (buffer,1000,stdin);

  			resultadoDelBuffer = strnlen(buffer,1000); //Guardo en resultado del buffer la longitud de lo que hay.
  			//printf ("\n EL LARGO DEL ID INGRESADO: %d\n", resultadoDelBuffer);

  			 if( resultadoDelBuffer > 5 ) //Si hay mas de 5 digitos, es un chamuyo.
  			 {
  				 flagErrorEnID++;
  			 }

  			 for (int i = 0 ; i < resultadoDelBuffer-1 ; i ++) //Recorro el buffer para revisar que solo sean numeros (Porque es un ID), excluyo ese /0.
  			 {
  				if ( buffer[i] < '0' || buffer[i] > '9' )
  				{
  					flagErrorEnID++;
  				}
  			 }

  			//printf ("\n HAY ERRORES EN CARACTERES ? -> %d \n", flagErrorEnID);

  			if (flagErrorEnID == 0) //Si no hay errores.
  			{
  				retorno = -3;
  				numeroIntBuffer = atoi(buffer); //Hacemos la conversion del char a int del ID ingresado.

  				//HASTA ACA ES UN GET ID

  				//AHORA VALIDAMOS SI ESE ID PARECE ESTAR O NO EN LA LISTA DE CLIENTES.




  				for ( int j = 0 ; j < limiteArrayClienteRecibido ; j++ ) //Recorremos lista de clientes
  				{
  					if (arrayClienteRecibido[j].idCliente == numeroIntBuffer && arrayClienteRecibido[j].flagIsEmpty == 0) //Si encuentro que un ID en la lista coincide con el que ingreso el usuario y el campo de existencia da positivo.
  					{
  						//Entonces el ID ingresado no solo es valido, sino que tambien existe en la lista de clientes.
  						retorno = numeroIntBuffer; //Devolvemos un numero >0 especificamente el ID ingresado si salio bien.

  						*valorIndiceID = j; // Pasamos por referencia el resultado de donde se encuentra ese IDCliente en la lista de clientes.
  						break;
  					}
  				}

  			}
  		 }

  		 return retorno;

  	 }



  int imprimir_cliente_por_id (Cliente* arrayClienteRecibido, int limiteArrayCliente, int idIngresadoParaImprimir)
 	{
 		int retorno = -1;

 		if (arrayClienteRecibido != NULL && limiteArrayCliente > 0 && idIngresadoParaImprimir < limiteArrayCliente)
 		{
 			retorno = -2;

 			for ( int i = 0 ; i < limiteArrayCliente ; i++ )
 			{
 				if (arrayClienteRecibido[i].idCliente == idIngresadoParaImprimir && arrayClienteRecibido[i].flagIsEmpty == 0)
 				{
 					printf ("\nLos datos del cliente son:\n Nombre: %s\n Apellido: %s\n Cuit: %s \n ID: %d\n", arrayClienteRecibido[i].nombre, arrayClienteRecibido[i].apellido, arrayClienteRecibido[i].cuit, arrayClienteRecibido[i].idCliente);
 					retorno = 0;
 					break;
 				}
 			}

 		}

 		return retorno;
 	}

  int imprimir_cliente_por_indice (Cliente* arrayClienteRecibido, int limiteArrayCliente, int indiceIngresadoParaImprimir)
 	{
 		int retorno = -1;

 		if (arrayClienteRecibido != NULL && limiteArrayCliente > 0 && indiceIngresadoParaImprimir < limiteArrayCliente)
 		{
 			retorno = -2;

			printf ("\nLos datos del cliente son:\n Nombre: %s\n Apellido: %s\n Cuit: %s \n ID: %d\n", arrayClienteRecibido[indiceIngresadoParaImprimir].nombre, arrayClienteRecibido[indiceIngresadoParaImprimir].apellido, arrayClienteRecibido[indiceIngresadoParaImprimir].cuit, arrayClienteRecibido[indiceIngresadoParaImprimir].idCliente);
			retorno = 0;
 		}
 		return retorno;
 	}




  int eliminar_cliente_por_id (Cliente* arrayClienteRecibido, int limiteArrayClienteRecibido, int idClienteRecibido)
  {
	  int retorno = -1;

	  if (arrayClienteRecibido != NULL && limiteArrayClienteRecibido > 0 && idClienteRecibido > 0 && idClienteRecibido < 9999) //Valido parametro
	  {
		  retorno = -2;

		  for ( int i = 0 ; i < limiteArrayClienteRecibido ; i++ ) 	//Recorro lista de clientes
		  {
			 if (arrayClienteRecibido[i].idCliente == idClienteRecibido && arrayClienteRecibido[i].flagIsEmpty == 0) //Si encuentro uno que coincida con el ID y existe
			 {
				 //Lo borro
				 arrayClienteRecibido[i].flagIsEmpty = 1;
				 arrayClienteRecibido[i].idCliente = 0;
				 retorno = 0;
				 break;
			 }
		  }
	  }

	  return retorno;
  }





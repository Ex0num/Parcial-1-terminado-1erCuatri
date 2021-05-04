/*
 ============================================================================
 Name        : zzzzPARCIAL-1.c
 Author      : Gabriel Lopez G
 Version     :
 Copyright   : GLG
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

	#include <stdio.h>
	#include <stdlib.h>

	#include "Cliente.h"
	#include "FuncionesEstandar.h"
	#include "Compra.h"
	#include "Relacion.h"

	#define QTY_CLIENTES 100
	#define QTY_COMPRAS  1000
	#define VERDADERO    1
	#define FALSO 		 0

int main(void)
{
	setbuf(stdout,NULL);

	int ordenDeMenu;
	Cliente clientes[QTY_CLIENTES];
	Compra compras[QTY_COMPRAS];

	int idCliente = 1;
	int idCompra = 1;

	inicializar_array_cliente (clientes, QTY_CLIENTES);
	inicializar_array_compra (compras, QTY_COMPRAS);

	do
	{
		print_menu();
		utn_obtener_validar_Orden("\n Por favor ingrese su orden. \n", "\n Error en el ingreso de su orden. \n", &ordenDeMenu);

		switch (ordenDeMenu)
		{
			case 1:
			{
				alta_cliente (clientes, QTY_CLIENTES, &idCliente); //Funciona correctamente.
				break;
			}

			case 2:
			{
				modificacion_cliente (clientes, QTY_CLIENTES); //Funciona correctamente.
				break;
			}

			case 3:
			{
				bajar_cliente (clientes, QTY_CLIENTES, compras, QTY_COMPRAS); //Funciona correctamente.
				break;
			}

			case 4:
			{
				realizar_compra (compras , QTY_COMPRAS, clientes, QTY_CLIENTES, &idCompra); //Funciona correctamente.
				break;
			}

			case 5:
			{
				pagar_compra (compras, QTY_COMPRAS, clientes, QTY_CLIENTES); //Funciona correctamente.
				break;
			}

			case 6:
			{
				cancelar_compra (compras, QTY_COMPRAS, clientes, QTY_CLIENTES);
				break;
			}

			case 7:
			{
				imprimir_clientes_existentesY_CantidadCompras (clientes, QTY_CLIENTES, compras, QTY_COMPRAS); //Funciona correctamente.
				break;
			}

			case 8:
			{

				break;
			}

			case 11:
			{
				print_despedida();
				break;
			}
		}

	}while( ordenDeMenu != 11);





}

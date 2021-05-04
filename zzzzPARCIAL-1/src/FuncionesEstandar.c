/*
 * FuncionesIndependientes.c
 *
 *  Created on: 30 abr. 2021
 *      Author: gabil
 */



	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	#include "FuncionesEstandar.h"

	int print_despedida(void)
	{
		printf ("\n ¡Hasta luego! :) \n");
		return 0;
	}

	int print_menu (void)
		{
			int retorno = 0;
			printf ("\n OPCIONES: \n"
					"1 - Alta de cliente. \n" //LISTO
					"2 - Modificacion de datos de cliente. \n" //LISTO
					"3 - Baja de cliente. \n"
					"4 - Realizar compra. \n"
					"5 - Pagar compra. \n"
					"6 - Cancelar compra. \n"
					"7 - Imprimir datos clientes existentes y su cantidad de compras. \n" //LISTO
					"8 - Informar color de barbijo mas comprado. \n"
					"9 - Cantidad de compras pendientes. \n"
					"10 - Compra con “precio por unidad” mas bajo. \n"
					"11 - Salir. \n" ); //LISTO
			return retorno;
		}

	int utn_obtener_validar_Orden (char mensajeParaPedido[], char mensajeParaError[], int* pOrdenValidada)
			{
				 int retorno = -1;

				 if ( mensajeParaPedido != NULL && mensajeParaError != NULL && pOrdenValidada != NULL )
					{
					 	retorno = -2;

						char buffer[10];
						int resultadoDelBuffer;
						int numeroIntBuffer;
						int flagErrorEnOrden = 0;

						printf ("%s", mensajeParaPedido);
						fflush(stdin);
						fgets (buffer,10,stdin);

						resultadoDelBuffer = strnlen(buffer,10);

						if (resultadoDelBuffer > 3)
						{
							flagErrorEnOrden++;
						}

						for (int i = 0 ; i < resultadoDelBuffer-1 ; i++ )
						{
							if (flagErrorEnOrden > 0)
							{
									break;
							}

							if ( buffer[i] < '0' || buffer[i] > '9')
							{
								flagErrorEnOrden++;
							}
						}

						if (flagErrorEnOrden == 0)
						{
							numeroIntBuffer = atoi(buffer);
						}

						if ( flagErrorEnOrden > 0)
						{
							printf ("%s",mensajeParaError);
							retorno = -3;
						}
						else
						{
							if (numeroIntBuffer > 11 || numeroIntBuffer < 1)
							{
								printf ("%s",mensajeParaError);
								retorno = -4;
							}
							else
							{
								*pOrdenValidada = numeroIntBuffer;
								retorno = 0;
							}
						}
				}

			 return retorno;
		}

	int utn_obtener_validar_Nombre (char mensajeParaPedido[], char mensajeParaError[], char* pCadenaAGuardar, int longitudCadenaAGuardar, int reintentos)
				{
					int retorno = -1;

					if ( mensajeParaPedido != NULL && mensajeParaError != NULL && pCadenaAGuardar != NULL && longitudCadenaAGuardar > 3 && reintentos >= 0)
					{
						char buffer[70];
						retorno = -2;
						int resultadoDelBuffer;
						int flagErrorEnNombre;

						do
						{
							flagErrorEnNombre = 0;
							printf ("%s",mensajeParaPedido);
							fflush(stdin);
							fgets (buffer,70,stdin);

							resultadoDelBuffer = strnlen(buffer,70);

							if (resultadoDelBuffer < 2)
							{
								flagErrorEnNombre++;
							}

							if (resultadoDelBuffer > 30)
							{
								flagErrorEnNombre++;
							}

							for (int j = 0 ; j < resultadoDelBuffer ; j++)
							{
								if (buffer[j] == '\n')
								{
									buffer[j] = '\0';
									break;
								}
							}

							for (int i = 0 ; buffer[i] != '\0' ; i++ )
								{
									if (flagErrorEnNombre > 0)
									{
										break;
									}

									if ( buffer[i] == ' ')
									{
										if (buffer[i+1] < 'A' || buffer [i+1] > 'Z')
										{
											flagErrorEnNombre++;
										}
									}

									if ( buffer[0] < 'A' || buffer[0] > 'Z')
									{
										{
											flagErrorEnNombre++;
										}
									}

									if ( buffer[i] < 'A' || buffer[i] > 'z' || buffer[i] == '[' || buffer[i] == ']' || buffer[i] == 92 || buffer[i] == '^' || buffer[i] == '_' || buffer[i] == '`')
									{
										if (buffer[i] == ' ')
										{
											//No pasa nada. Porque es un espacio.
										}
										else
										{
											flagErrorEnNombre++;
										}
									}
								}

							if (resultadoDelBuffer > longitudCadenaAGuardar || flagErrorEnNombre > 0)
							{
								printf ("%s \n",mensajeParaError);
								//printf ("La cantidad de errores en el flagNombre es de : %i \n", flagErrorEnNombre);
								reintentos--;
							}
							else
							{
								strcpy (pCadenaAGuardar, buffer);
								reintentos = -1;
								retorno = 0;
							}

						}while (reintentos >= 0);
					}

					return retorno;
				}

	int utn_obtener_validar_Apellido (char mensajeParaPedido[], char mensajeParaError[], char* pCadenaAGuardar, int longitudCadenaAGuardar, int reintentos)
					{
						int retorno = -1;

						if ( mensajeParaPedido != NULL && mensajeParaError != NULL && pCadenaAGuardar != NULL && longitudCadenaAGuardar > 3 && reintentos >= 0)
						{
							char buffer[70];
							retorno = -2;
							int resultadoDelBuffer;
							int flagErrorEnNombre;

							do
							{
								flagErrorEnNombre = 0;
								printf ("%s",mensajeParaPedido);
								fflush(stdin);
								fgets (buffer,70,stdin);

								resultadoDelBuffer = strnlen(buffer,70);

								if (resultadoDelBuffer < 2)
								{
									flagErrorEnNombre++;
								}

								if (resultadoDelBuffer > 30)
								{
									flagErrorEnNombre++;
								}

								for (int j = 0 ; j < resultadoDelBuffer ; j++)
								{
									if (buffer[j] == '\n')
									{
										buffer[j] = '\0';
										break;
									}
								}

								for (int i = 0 ; buffer[i] != '\0' ; i++ )
									{
										if (flagErrorEnNombre > 0)
										{
											break;
										}

										if ( buffer[i] == ' ')
										{
											if (buffer[i+1] < 'A' || buffer [i+1] > 'Z')
											{
												flagErrorEnNombre++;
											}
										}

										if ( buffer[0] < 'A' || buffer[0] > 'Z')
										{
											{
												flagErrorEnNombre++;
											}
										}

										if ( buffer[i] < 'A' || buffer[i] > 'z' || buffer[i] == '[' || buffer[i] == ']' || buffer[i] == 92 || buffer[i] == '^' || buffer[i] == '_' || buffer[i] == '`')
										{
											if (buffer[i] == ' ')
											{
												//No pasa nada. Porque es un espacio.
											}
											else
											{
												flagErrorEnNombre++;
											}
										}
									}

								if (resultadoDelBuffer > longitudCadenaAGuardar || flagErrorEnNombre > 0)
								{
									printf ("%s \n",mensajeParaError);
									//printf ("La cantidad de errores en el flagNombre es de : %i \n", flagErrorEnNombre);
									reintentos--;
								}
								else
								{
									strcpy (pCadenaAGuardar, buffer);
									reintentos = -1;
									retorno = 0;
								}

							}while (reintentos >= 0);
						}

						return retorno;
					}

	 int utn_obtener_validar_Cuit (char* mensajePedido, char* mensajeError, char* pGuardarCuit, int limitePunteroGuardarCuit, int reintentos)
	 {
		 int retorno = -1;

		 if (mensajePedido != NULL && mensajeError != NULL && pGuardarCuit != NULL && limitePunteroGuardarCuit > 14 && reintentos >= 0)
		 {
			 retorno = -2;

			 char buffer[99];
			 retorno = -2;
			 int resultadoDelBuffer;
			 int flagError;

			 do
			 {
				flagError = 0;

				printf ("%s",mensajePedido);
				fflush(stdin);
				fgets (buffer,99,stdin);

				resultadoDelBuffer = strnlen(buffer,99);

				if (resultadoDelBuffer < 10 || resultadoDelBuffer > 16)
				{
					flagError++;
				}

				for (int j = 0 ; j < resultadoDelBuffer ; j++)
				{
					if (buffer[j] == '\n')
					{
						buffer[j] = '\0';
						break;
					}
				}


				for ( int i = 0 ; i < resultadoDelBuffer ; i++ )
				{

					if (flagError > 0)
					{
						break;
					}

					if (buffer[i] < '0' || buffer[i] > '9')
					{
						//Ojo puede haber un caracter invalido.

						if (buffer[i] != ' ' && buffer[i] != '-' && buffer[i] != '\0' ) //Si ya no es ninguno de estos...
						{
							flagError++;
						}
					}
				}

				if (flagError > 0 || resultadoDelBuffer > limitePunteroGuardarCuit)
				{
					printf ("%s", mensajeError);
					reintentos--;
					retorno = -3;
				}
				else if ( flagError == 0 && limitePunteroGuardarCuit > resultadoDelBuffer)
				{
					strcpy (pGuardarCuit, buffer);
					reintentos = -1;
					retorno = 0;
				}

			 }while( reintentos >= 0);
		 }

		 return retorno;
	 }


	 int utn_obtener_validar_Edad (char mensajeParaPedido[], char mensajeParaError[], int* pEdadValidada, int reintentos)
	  	{
	  		 int retorno = -1;

	  		 if ( mensajeParaPedido != NULL && mensajeParaError != NULL &&  pEdadValidada != NULL && reintentos >= 0)
	  			{
	  				char buffer[99];
	  				retorno = -2;
	  				int resultadoDelBuffer;
	  				int numeroIntBuffer;

	  				do
	  				{
	  					int flagErrorEnEdad = 0;
	  					int contadorDeCeros = 0;
	  					printf ("%s",mensajeParaPedido);
	  					fflush(stdin);
	  					fgets (buffer,99,stdin);

	  					//printf("Do-While iteracion.\n");

	  					resultadoDelBuffer = strnlen(buffer,99);
	  					//printf ("strlen del Buffer %d\n", resultadoDelBuffer);

	  					for (int i = 0 ; i < resultadoDelBuffer-1 ; i++ )
	  					{
	  						if (flagErrorEnEdad > 0)
	  						{
	  								break;
	  						}

	  						if ( buffer[i] < '0' || buffer[i] > '9')
	  						{
	  							flagErrorEnEdad++;
	  						}

	  						if (buffer[i] == '0')
	  						{
	  							contadorDeCeros++;
	  						}
	  					}

	  					if (contadorDeCeros == resultadoDelBuffer-1)
	  					{
	  						flagErrorEnEdad++;
	  					}

	  					if (flagErrorEnEdad == 0)
	  					{
	  						numeroIntBuffer = atoi(buffer);
	  						//printf ("Atoi iteracion.\n");
	  					}

	  					if (numeroIntBuffer > 140 || numeroIntBuffer <= 0) // [PARA HUMANOS]
	  					{
	  						flagErrorEnEdad++;
	  					}

	  					//if (numeroIntBuffer > 500 || numeroIntBuffer <= 0) //[PARA ANIMALES]
	  					//{
	  					//	flagErrorEnEdad++;
	  					//}

	  					if ( flagErrorEnEdad > 0)
	  					{
	  						printf ("%s",mensajeParaError);
	  						reintentos--;
	  						//printf ("%d", flagErrorEnEdad);
	  					}
	  					else
	  					{
	  						*pEdadValidada = numeroIntBuffer;
	  						reintentos = -1;
	  						retorno = 0;
	  					}

	  				}while (reintentos >= 0);
	  			}

	  		 return retorno;
	  	}

	 int utn_obtener_validar_Texto (char mensajeParaPedido[], char mensajeParaError[], char* pCadenaAGuardar, int longitudCadenaAGuardar, int reintentos) //act
		{
			int retorno = -1;

			if (strlen (mensajeParaPedido) > 0 && strlen (mensajeParaError) > 0 && pCadenaAGuardar != NULL && longitudCadenaAGuardar > 0 && reintentos >= 0)
			{
				char buffer[999];
				retorno = -2;
				int resultadoDelBuffer;
				int flagErrorEnTexto = 0;

				do
				{
					printf ("%s",mensajeParaPedido);
					fflush(stdin);
					fgets (buffer,999,stdin);

					resultadoDelBuffer = strnlen(buffer,999);

					for (int i = 0 ; i < resultadoDelBuffer ; i++ )
					{
						if (flagErrorEnTexto > 0)
						{
							break;
						}

						if ( buffer [i] == ',' || buffer [i] == ';' || buffer [i] == ':' )
						{
							if (buffer[i+1] != ' ')
							{
								flagErrorEnTexto++;
							}

							if (buffer[i-1] == ' ')
							{
								flagErrorEnTexto++;
							}
						}
					}

					if (resultadoDelBuffer > longitudCadenaAGuardar || flagErrorEnTexto > 0)
					{
						printf ("%s",mensajeParaError);
						reintentos--;
					}
					else
					{
						strcpy (pCadenaAGuardar, buffer);
						reintentos = -1;
						retorno = 0;
					}

				}while (reintentos >= 0);
			}

			return retorno;
		}

	 int utn_obtener_orden_si_no (char* mensajePedido, char* mensajeError, int reintentos)
		 {
							int retorno = -1;

							if ( mensajePedido != NULL && mensajeError != NULL && reintentos >= 0)
							{
								char buffer[70];
								retorno = -2;
								int resultadoDelBuffer;
								int flagErrorEnOrden;

								do
								{
									flagErrorEnOrden = 0;
									printf ("%s",mensajePedido);
									fflush(stdin);
									fgets (buffer,70,stdin);

									resultadoDelBuffer = strnlen(buffer,70);

									if (resultadoDelBuffer < 3)
									{
										flagErrorEnOrden++;
									}

									if (resultadoDelBuffer > 4)
									{
										flagErrorEnOrden++;
									}

									for (int j = 0 ; j < resultadoDelBuffer ; j++)
									{
										if (buffer[j] == '\n')
										{
											buffer[j] = '\0';
											break;
										}
									}

									for (int i = 0 ; buffer[i] != '\0' ; i++ )
										{
											if (flagErrorEnOrden > 0)
											{
												break;
											}

											if (buffer[i] != 'S' && buffer[i] != 'I' && buffer[i] != 'N' && buffer[i] != 'O')
											{
												flagErrorEnOrden++;
											}

										}

									if (buffer[0] == 'N' && buffer[1] != 'O')
								    {
										flagErrorEnOrden++;
								    }

									if (buffer[0] == 'S' && buffer[1] != 'I')
									{
										flagErrorEnOrden++;
									}

									if ( flagErrorEnOrden > 0)
									{
										printf ("%s \n",mensajeError);
										//printf ("La cantidad de errores en el flagNombre es de : %i \n", flagErrorEnNombre);
										reintentos--;
										retorno = -3;
									}
									else
									{
										if (buffer[0] == 'N')
										{
											retorno = 0;
										}
										else if (buffer[0] == 'S')
										{
											retorno = 1;
										}

										reintentos = -1;
									}

								}while (reintentos >= 0);
							}

							return retorno;
						}

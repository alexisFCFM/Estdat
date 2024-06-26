#pragma once
#include "Estdat.h"
#include "misc.h"
#include "vuelos.h"
#include "pasajeros.h"
#include "boletos.h"
#include "manifiesto.h"
#include "pasesAbordar.h"

wchar_t direccion[255];

BOOL CALLBACK menu(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_INITDIALOG: {
			vuelosLimpiar();
			pasajerosLimpiar();
			boletosLimpiar();
			
			ifstream vuelosEscribir;
			vuelosEscribir.open(rutaListaVuelos, ios::in | ios::binary);
			if (vuelosEscribir.is_open()) {
				while (true) {
					Vuelos* LeerVuelos = new Vuelos;
					vuelosEscribir.read(reinterpret_cast<char*>(LeerVuelos), sizeof(Vuelos));
					if (vuelosEscribir.eof()) {
						delete LeerVuelos;
						break;
					}
					vuelosAgregar(LeerVuelos);
					
				}
			}
			vuelosEscribir.close();

			ifstream pasajerosEscribir;
			pasajerosEscribir.open(rutaListaPasajeros, ios::in | ios::binary);
			if (pasajerosEscribir.is_open()) {
				while (true) {
					Pasajeros* LeerPasajeros = new Pasajeros;
					pasajerosEscribir.read(reinterpret_cast<char*>(LeerPasajeros), sizeof(Pasajeros));
					if (pasajerosEscribir.eof()) {
						delete LeerPasajeros;
						break;
					}
					pasajerosAgregar(LeerPasajeros);

				}
			}
			pasajerosEscribir.close();

			ifstream boletosEscribir;
			boletosEscribir.open(rutaListaBoletos, ios::in | ios::binary);
			if (boletosEscribir.is_open()) {
				while (true) {
					Boletos* LeerBoletos = new Boletos;
					boletosEscribir.read(reinterpret_cast<char*>(LeerBoletos), sizeof(Boletos));
					if (boletosEscribir.eof()) {
						delete LeerBoletos;
						break;
					}
					boletosAgregar(LeerBoletos);

				}
			}
			boletosEscribir.close();

			
		vuelosActualizarLista(handler);
		pasajerosActualizarLista(handler);
		boletosActualizarLista(handler);

		return 0;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		//Vuelos
		case ID_VUELOS_REGISTRARVUELO: {
			vuelosActual = NULL;
			DialogBox(NULL, MAKEINTRESOURCE(IDD_VUELO_REGISTRO), handler, (DLGPROC)REGISTRARVUELO);
			vuelosActualizarLista(handler);
			return 0;
		}

		case ID_VUELOS_ELIMINARVUELO: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_VUELO_ELIMINAR), handler, (DLGPROC)ELIMINARVUELO);
			vuelosActualizarLista(handler);
			return 0;
		}

		case ID_VUELOS_MODIFICARVUELO: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_VUELO_MODIFICAR), handler, (DLGPROC)MODIFICARVUELO);
			vuelosActualizarLista(handler);
			return 0;
		}

		case IDC_vuelos:
		{
			
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				int seleccionado = SendDlgItemMessage(handler, IDC_vuelos, LB_GETCURSEL, NULL, NULL);
				Vuelos* aMostrar = vuelosBuscar(seleccionado);
				
				SendDlgItemMessage(handler, IDC_EDIT_VUELOS_ORIGEN, WM_SETTEXT, NULL, (LPARAM)aMostrar->vueloOrigen);
				SendDlgItemMessage(handler, IDC_EDIT_VUELOS_DESTINO, WM_SETTEXT, NULL, (LPARAM)aMostrar->vueloDestino);
				//SendDlgItemMessage(handler, IDC_Asientos_Disponibles, WM_SETTEXT, NULL, (LPARAM)aMostrar->asientos);
				//SendDlgItemMessage(handler, IDC_CentroVacuna, WM_SETTEXT, NULL, (LPARAM)aMostrar->CentroVacuna);
				//SendDlgItemMessage(handler, IDC_EDIT_HORA_SALIDA, WM_SETTEXT, NULL, (LPARAM)aMostrar->Lote);
				//SendDlgItemMessage(handler, IDC_EDIT_HORA_LLEGADA, WM_SETTEXT, NULL, (LPARAM)aMostrar->ApellidoPaterno);
				//SendDlgItemMessage(handler, IDC_ApellidoMaterno, WM_SETTEXT, NULL, (LPARAM)aMostrar->ApellidoMaterno);
				//SendDlgItemMessage(handler, IDC_Nombres, WM_SETTEXT, NULL, (LPARAM)aMostrar->Nombres);
				
				/*
					
				SendDlgItemMessage(handler, IDC_asientosDisponibles, WM_SETTEXT, NULL, (LPARAM)aMostrar->vueloAsientos);

				if (aMostrar->vueloTipoAvion == 0)
				{
					SendDlgItemMessage(handler, IDC_asientosDisponibles, WM_SETTEXT, NULL, (LPARAM)L"4");
				}

				else
				{
					SendDlgItemMessage(handler, IDC_asientosDisponibles, WM_SETTEXT, NULL, (LPARAM)L"5");
				}

				if (aMostrar->vueloClase)
				{
					SendDlgItemMessage(handler, IDC_claseAvion_EditBox, WM_SETTEXT, NULL, (LPARAM)L"Clase turista");
				}

				else
				{
					SendDlgItemMessage(handler, IDC_claseAvion_EditBox, WM_SETTEXT, NULL, (LPARAM)L"Clase ejecutiva");
					
				}
				*/

				if (aMostrar->vueloTipoAvion == 0)
				{
					SendDlgItemMessage(handler, IDC_tipoAvion_EditBox, WM_SETTEXT, NULL, (LPARAM)L"Airbus A380");
				}

				else if (aMostrar->vueloTipoAvion == 1)
				{
					SendDlgItemMessage(handler, IDC_tipoAvion_EditBox, WM_SETTEXT, NULL, (LPARAM)L"Boeing 777");
				}
				else if (aMostrar->vueloTipoAvion == 2)
				{
					SendDlgItemMessage(handler, IDC_tipoAvion_EditBox, WM_SETTEXT, NULL, (LPARAM)L"Boeing 787 Dreamliner");
				}
				else if (aMostrar->vueloTipoAvion == 3)
				{
					SendDlgItemMessage(handler, IDC_tipoAvion_EditBox, WM_SETTEXT, NULL, (LPARAM)L"Airbus A350");
				}
				else if (aMostrar->vueloTipoAvion == 4)
				{
					SendDlgItemMessage(handler, IDC_tipoAvion_EditBox, WM_SETTEXT, NULL, (LPARAM)L"Boeing 737");
				}
				else
				{
					SendDlgItemMessage(handler, IDC_tipoAvion_EditBox, WM_SETTEXT, NULL, (LPARAM)L"");
				}

				 //SendDlgItemMessage(handler, IDC_Asientos_Disponibles, WM_SETTEXT, NULL, (LPARAM)aMostrar->asientos);
				
				//SendDlgItemMessage(handler, IDC_Colonia, WM_SETTEXT, NULL, (LPARAM)aMostrar->Colonia);

				return 0;
			}
			return 0;
		}


		//Pasajero
		case ID_PASAJEROS_REGISTRARPASAJEROS: {
			pasajerosActual = NULL;
			DialogBox(NULL, MAKEINTRESOURCE(IDD_PASAJEROS_REGISTRO), handler, (DLGPROC)REGISTRARPASAJEROS);
			pasajerosActualizarLista(handler);
			return 0;
		}
		case ID_PASAJEROS_ELIMINARPASAJEROS: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_PASAJEROS_ELIMINAR), handler, (DLGPROC)ELIMINARPASAJEROS);
			pasajerosActualizarLista(handler);
			return 0;
		}
		case ID_PASAJEROS_MODIFICARPASAJEROS: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_PASAJEROS_MODIFICAR), handler, (DLGPROC)MODIFICARPASAJEROS);
			pasajerosActualizarLista(handler);
			return 0;
		}

		case ID_LISTAS_PASAJEROS:
		{
			pasajerosActualizarLista(handler);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_PASAJEROS_LISTA), handler, (DLGPROC)LISTAPASAJEROS);
			return 0;
		}
		//Boletos

		case ID_BOLETOS_COMPRARBOLETOS: {
			boletosActual = NULL;
			DialogBox(NULL, MAKEINTRESOURCE(IDD_BOLETOS_REGISTRO), handler, (DLGPROC)COMPRARBOLETOS);
			boletosActualizarLista(handler);
			return 0;
		}
		case ID_BOLETOS_CANCELARBOLETOS: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_BOLETOS_ELIMINAR), handler, (DLGPROC)CANCELARBOLETOS);
			boletosActualizarLista(handler);
			return 0;
		}
		case ID_BOLETOS_MODIFICARBOLETOS: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_BOLETOS_MODIFICAR), handler, (DLGPROC)MODIFICARBOLETOS);
			boletosActualizarLista(handler);
			return 0;
		}

		case ID_LISTAS_BOLETOS:
		{
			boletosActualizarLista(handler);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_BOLETOS_LISTA), handler, (DLGPROC)LISTABOLETOS);
			return 0;
		}
		//Manifiesto
		case ID_MISC_PASEDEABORDAR: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_PASE_ABORDAR), handler, (DLGPROC)COMPRARPASES);
			return 0;
		}
		case ID_VERMANIFIESTO_VERPORNUMERODEASIENTO: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_MANIFIESTO_NUMERO), handler, (DLGPROC)VERPORNUMERODEASIENTO);
			return 0;
		}
		case ID_VERMANIFIESTO_VERPORNOMBRE: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_MANIFIESTO_NOMBRE), handler, (DLGPROC)VERPORNOMBRE);
			return 0;
		}
		case ID_VERMANIFIESTO_VERPORAPELLIDO: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_MANIFIESTO_APELLIDO), handler, (DLGPROC)VERPORAPELLIDO);
			return 0;
		}
		//Mas opciones
		case IDOK:
		{
			if (MessageBox(handler, L"Desea exportar el vuelo actual? ", L"Exportar", MB_ICONINFORMATION | MB_OKCANCEL) == IDOK)
			{
				exportarVuelo(handler);
				return 0;
			}

			else
			{
				return 0;
			}

			return 0;
		}

		case ID_ADMIN_REGISTRARUSUARIOS: {
			if (!adminStatus) {
				MessageBox(handler, L"Se necesitan permisos de administrador para poder agregar nuevos usuarios", L"Admin", MB_ICONEXCLAMATION);
				return 0;
			}

			else {
				DialogBox(NULL, MAKEINTRESOURCE(IDD_USUARIO), handler, (DLGPROC)REGISTRARUSUARIOS);
				return 0;
			}
		}

		case ID_ADMIN_REINICIARIDSDEVUELOS: {
			if (!adminStatus) {
				MessageBox(handler, L"Se necesitan permisos de administrador para poder reiniciar los IDs de los vuelos", L"Admin", MB_ICONEXCLAMATION);
				return 0;
			}

			else {
				if (MessageBox(handler, L"Desea reiniciar los IDs de los vuelos?", L"Reparar", MB_OKCANCEL) == IDOK)
				{
					ofstream file;
					file.open(rutaDatos + "idVuelos.bin");
					file << "0" << endl;
					file.close();
					MessageBox(handler, L"Los IDs de los vuelos fueron reiniciados", L"Reparar", MB_OK);
					return 0;
				}

				else
				{
					return 0;
				}
				return 0;
			}

			return 0;	
			
		}

		case IDM_ABOUT: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ABOUTBOX), handler, (DLGPROC)ABOUTBOX);
			return 0;
		}

		default:
			return 0;
		}
	}

	case WM_CLOSE: {

		if (MessageBox(handler, L"�Desea salir de la aplicaci�n? Los cambios realizados se guardar�n.", L"Cerrando programa", MB_OKCANCEL) == IDOK)
		{
			if (!saveOnExit) {
				
				DestroyWindow(handler);
				return 0;

			}

			else {
					ofstream vuelosEscribir;
					vuelosEscribir.open(rutaListaVuelos, ios::out | ios::binary | ios::trunc);
					if (vuelosEscribir.is_open()) {

						Vuelos* vuelosAux = vuelosInicio;
						while (vuelosAux->vuelosSiguiente != vuelosInicio) {
							vuelosEscribir.write(reinterpret_cast<char*>(vuelosAux), sizeof(Vuelos));
							vuelosAux = vuelosAux->vuelosSiguiente;
						}

						vuelosEscribir.write(reinterpret_cast<char*>(vuelosAux), sizeof(Vuelos));
						vuelosEscribir.close();
					}

					ofstream pasajerosEscribir;
					pasajerosEscribir.open(rutaListaPasajeros, ios::out | ios::binary | ios::trunc);
					if (pasajerosEscribir.is_open()) {

						Pasajeros* pasajerosAux = pasajerosInicio;
						while (pasajerosAux->pasajerosSiguiente != pasajerosInicio) {
							pasajerosEscribir.write(reinterpret_cast<char*>(pasajerosAux), sizeof(Pasajeros));
							pasajerosAux = pasajerosAux->pasajerosSiguiente;
						}

						pasajerosEscribir.write(reinterpret_cast<char*>(pasajerosAux), sizeof(Pasajeros));
						pasajerosEscribir.close();
					}

					ofstream boletosEscribir;
					boletosEscribir.open(rutaListaBoletos, ios::out | ios::binary | ios::trunc);
					if (boletosEscribir.is_open()) {

						Boletos* boletosAux = boletosInicio;
						while (boletosAux->boletosSiguiente != boletosInicio) {
							boletosEscribir.write(reinterpret_cast<char*>(boletosAux), sizeof(Boletos));
							boletosAux = boletosAux->boletosSiguiente;
						}

						boletosEscribir.write(reinterpret_cast<char*>(boletosAux), sizeof(Boletos));
						boletosEscribir.close();
					}
					
					DestroyWindow(handler);
				return 0;
			}

			DestroyWindow(handler);
			return 0;
		}
		return 0;
	}

	case WM_DESTROY: {
		//PostQuitMessage(0);
		return 0;
	}

	default:
		return 0;
	}
	return false;
}


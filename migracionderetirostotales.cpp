#include "migracionderetirostotales.hpp"
#define MAIN

int main( int __argc, char *__argv[])
{    
		fns.fnArcGrabarLogx(RUTA_LOG, "*************************************************************************");
		fns.fnArcGrabarLogx(RUTA_LOG, "INICIO DEL PROCESO...");

		for(int iNumIntento=1; iNumIntento <= 10; iNumIntento++)
		{
			shRet = DEFAULT__;
			snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] INTENTO DE CONEXION: %i", __FILE__, __FUNCTION__, iNumIntento);
			fns.fnArcGrabarLogx(RUTA_LOG, cTexto);

			shRet = obtenerConexionBaseDato();
			if (shRet == OK__)
			{
				memset(cTexto, 0, sizeof(cTexto));
				snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] CONECTADO EN EL INTENTO NUMERO: %i", __FILE__, __FUNCTION__, iNumIntento);
				fns.fnArcGrabarLogx(RUTA_LOG, cTexto);
				break;
			}
			else
			{
				odbcInfxSafreaf.Close();
				odbcAdmonAfo.Close();
				odbcAforeGlobal.Close();
				odbcServiciosAfore.Close();
			}
		}
		
		if (shRet == OK__)
		{
			objRes.ReplicarSolicitudesRetirosTotales(&odbcAforeGlobal, &odbcInfxSafreaf, &odbcServiciosAfore);		
		}
		
		odbcInfxSafreaf.Close();
		odbcAdmonAfo.Close();
		odbcAforeGlobal.Close();
		odbcServiciosAfore.Close();
		snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] FIN DEL PROCESO...",__FILE__,__FUNCTION__);
		fns.fnArcGrabarLogx(RUTA_LOG, cTexto);    
}

short obtenerConexionBaseDato()
{
	FILE *fichero;
	char nombre[100] = "/sysx/progs/afore/ipadmonafore.dat";
	char cLinea[42] = {0};
	char cIpAux[42] = {0};
	char cIp1[22] = {0};
	char cIp2[22] = {0};

	memset(cIp1, 0, sizeof(cIp1));
	memset(cIp2, 0, sizeof(cIp2));

	fichero = fopen( nombre, "r" );

	if( fichero )
	{
		memset(cLinea, 0, sizeof(cLinea));
		memset(cIpAux, 0, sizeof(cIpAux));
		
		if (fgets(cLinea, 40, fichero) != NULL)
		{
			snprintf(cIpAux, strnlen(cIpAux, sizeof(cIpAux)), "%s", fichero); //LEO HASTA LA COLUMNA 34
			snprintf(cIp1, strnlen(cIp1, sizeof(cIp1)), "%s", fns.fnCadSubstring(0, 20, cIpAux));  	//LEO LOS PRIMEROS 20 CARACTERES DEL ARCHIVO (IP 1)
			snprintf(cIp2, strnlen(cIp2, sizeof(cIp2)), "%s", fns.fnCadSubstring(21, 20, cIpAux));  	//LEO LOS SIGUIENTES 20 CARACTERES DEL ARCHIVO (IP 2)
		}
		else
		{
			snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] Error al leer el archivo %s",__FILE__,__FUNCTION__, nombre);
			fns.fnArcGrabarLogx(RUTA_LOG, cTexto);
			shRet = DEFAULT__;
		}
	}

	snprintf(cIp1, strnlen(cIp1, sizeof(cIp1)), "%s", fns.fnCadTrim(cIp1));
	snprintf(cIp2, strnlen(cIp2, sizeof(cIp2)), "%s", fns.fnCadTrim(cIp2));

	if (strnlen(cIp1, sizeof(cIp1)) > 0 || strnlen(cIp2, sizeof(cIp2)) > 0)
	{
		//CONEXION AL SERVER ADMONAFORE
		memset(cIpAdmonAfore, 0, sizeof(cIpAdmonAfore));
		memmove(cIpAdmonAfore, cIp1, sizeof(cIp1));
		snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] Abriendo conexion a Postgres, AdmonAfore, IP: %s",__FILE__,__FUNCTION__, cIp1);
		fns.fnArcGrabarLogx(RUTA_LOG, cTexto);
		shRet = fns.fnConAbrirConexionPostgres(&odbcAdmonAfo, cIpAdmonAfore, (char *)BDADMONAFORE, (char *)USERADMONAFORE, cTexto);
		if(shRet != OK__) //si NO se abrió conexion a: admonafore
		{
			memset(cIpAdmonAfore, 0, sizeof(cIpAdmonAfore));
			memmove(cIpAdmonAfore, cIp2, sizeof(cIp2));
			snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] Abriendo conexion a Postgres, AdmonAfore, IP: %s",__FILE__,__FUNCTION__, cIp2);
			fns.fnArcGrabarLogx(RUTA_LOG, cTexto);
			shRet = fns.fnConAbrirConexionPostgres(&odbcAdmonAfo, cIpAdmonAfore, (char *)BDADMONAFORE, (char *)USERADMONAFORE, cTexto);
		}

		if(shRet == OK__) //si se abrió conexion a: admonafore
		{
			snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] Conexion a Postgres AdmonAfore OK, IP: %s",__FILE__,__FUNCTION__, cIpAdmonAfore);
			fns.fnArcGrabarLogx(RUTA_LOG, cTexto);

			//CONEXION A SERVER AFOREGLOBAL
			memset(cTexto,0,sizeof(cTexto));
			snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "SELECT TRIM(valor) FROM aforecontrol WHERE Tipo = 1 AND activo = 1 AND id = %i", SERV_DATABASE_AFO_GLOBAL);
			shRet = fns.fnSqlConsultarTexto(&odbcAdmonAfo, cTexto, cOutTexto);
			if(shRet == OK__)
			{					
				memset(cIpAforeGlobal, 0, sizeof(cIpAforeGlobal));
				memmove(cIpAforeGlobal, cOutTexto, sizeof(cOutTexto));
				
				snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] Abriendo conexion a Postgres, AforeGlobal, IP: %s",__FILE__,__FUNCTION__, cIpAforeGlobal);
				fns.fnArcGrabarLogx(RUTA_LOG, cTexto);
				shRet = fns.fnConAbrirConexionPostgres(&odbcAforeGlobal, cIpAforeGlobal, (char *)BDAFOREGLOBAL, (char *)USERAFOREGLOBAL, cTexto);
				if(shRet == OK__) //si se abrió conexion a AFOREglobal
				{
					snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] Conexion a Postgres AforeGlobal OK",__FILE__,__FUNCTION__);
					fns.fnArcGrabarLogx(RUTA_LOG, cTexto);
					
					//CONEXION A SERVER AFOREGLOBAL
					memset(cTexto,0,sizeof(cTexto));
					memset(cOutTexto,0,sizeof(cOutTexto));
					snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "SELECT concepto2 FROM pafhardcode WHERE tipo1 = 197;");
					shRet = fns.fnSqlConsultarTexto(&odbcAforeGlobal, cTexto, cOutTexto);
				
					memset(cIpAforeGlobal, 0, sizeof(cIpAforeGlobal));
					memmove(cIpAforeGlobal, cOutTexto, sizeof(cOutTexto));
					snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] Abriendo conexion a Postgres, serviciosafore, IP: %s",__FILE__,__FUNCTION__, cIpAforeGlobal);
					fns.fnArcGrabarLogx(RUTA_LOG, cTexto);
					shRet = fns.fnConAbrirConexionPostgres(&odbcServiciosAfore, cIpAforeGlobal, (char *)BDSERVICIOSAFORE, (char *)USERSERVICIOSAFORE, cTexto);
					if(shRet == OK__)
					{
						snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] Conexion a Postgres ServiciosAfore OK",__FILE__,__FUNCTION__);
						fns.fnArcGrabarLogx(RUTA_LOG, cTexto);
						
						//CONEXION A SERVER: INFORMIX
						memset(cTexto,0,sizeof(cTexto));
						memset(cOutTexto,0,sizeof(cOutTexto));
						snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "SELECT TRIM(valor) FROM aforecontrol WHERE Tipo = 1 AND activo = 1 AND id = %i", SERV_DATABASE_INFORMIX);
						shRet = fns.fnSqlConsultarTexto(&odbcAdmonAfo, cTexto, cOutTexto);
						if(shRet == OK__)
						{
							memset(cIpIfx, 0, sizeof(cIpIfx));
							memmove(cIpIfx, cOutTexto, sizeof(cOutTexto));
							fns.fnCadQuitarEspacioDerecha(cIpIfx);

							snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] Abriendo conexion a Informix, IP: %s",__FILE__,__FUNCTION__, cIpIfx);
							fns.fnArcGrabarLogx(RUTA_LOG, cTexto);
							shRet = fns.fnConAbrirConexionInformix(&odbcInfxSafreaf, cIpIfx, (char *)USR_BD_SAFRE_AF, (char *)PWD_BD_SAFRE_AF, (char *)BD_SAFRE_AF, cTexto);
							if(shRet == OK__)
							{
								snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] Conexion a Informix OK, IP: %s",__FILE__,__FUNCTION__, cIpIfx);
								fns.fnArcGrabarLogx(RUTA_LOG, cTexto);
							}
							else
							{	
								fns.fnArcGrabarLogx(RUTA_LOG, cTexto);
								shRet = ERR_CNX_INFX;
								odbcAdmonAfo.Close();
								odbcAforeGlobal.Close();
							}
						}
						else
						{
							fns.fnArcGrabarLogx(RUTA_LOG, cOutTexto);
							shRet = DEFAULT__;
						}
					}
					else
					{
						fns.fnArcGrabarLogx(RUTA_LOG, cTexto);
						shRet = ERR_CNX_BASE_DATO;
					}	
				}
				else
				{
					fns.fnArcGrabarLogx(RUTA_LOG, cTexto);
					shRet = ERR_CNX_BASE_DATO;
				}						
			}
			else
			{
				fns.fnArcGrabarLogx(RUTA_LOG, cOutTexto);
				shRet = ERR_CNX_BASE_DATO;
			}
		}
		else
		{
			snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] Excepcion al abrir conexion a Pgs AdmonAfore, IP: %s",__FILE__,__FUNCTION__, cIpAdmonAfore);
			fns.fnArcGrabarLogx(RUTA_LOG, cTexto);
			shRet = ERR_CNX_BASE_DATO;
		}
	}
	else
	{
		snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "%s", "fn: main, EL VALOR DE LA IP DE POSTGRESS NO ES VALIDO O ESTA VACIO, VERIFIQUE...");
		fns.fnArcGrabarLogx(RUTA_LOG, cTexto);
		shRet = DEFAULT__;
	}

	return shRet;
}

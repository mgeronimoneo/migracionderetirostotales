#include "CInfoRetFolioInfonavit.hpp"

CInfoRetFolioInfonavit::CInfoRetFolioInfonavit()
{
	// TODO Auto-generated constructor stub
}

CInfoRetFolioInfonavit::~CInfoRetFolioInfonavit()
{
	// TODO Auto-generated destructor stub
}

short CInfoRetFolioInfonavit::ReplicarRetFolioInfonavit(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore)
{
	CRetfolioinfonavit objRetFolioInfonavit(odbcServiciosAfore);

	char cNss[13] 			  = {0};
	char cFolioInfonavit[16]  = {0};
	char cTipoRetiro[3]		  = {0};
	char cFechaCaptura[12]    = {0};
	char cUsuarioCaptura[14]  = {0};
	
	char cSql[1024] 		= {0};
	char cSqlAux[1024] 		= {0};
	char cTexto[1024] 		= {0};

	int 	iRespuesta = 0;

	objFG.fnArcGrabarLogx(RUTA_LOG,"***********************************ENTRA RETFOLIOINFONAVIT***************************************");
	memset(cTexto,0,sizeof(cTexto));
	snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "FOLIO QUE SE ESTA MIGRANDO: [%i]", iFolioServicio);
	objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

	//OBTENCIÓN DE LA INFORMACION QUE SE VA A MIGRAR DE RECSERVICIOS AFORE TIMBRADO
	memset(cSql,0,sizeof(cSql));
	memset(cTexto,0,sizeof(cTexto));

	snprintf(cSql, strnlen(cSql, sizeof(cSql)), " SELECT TRIM(COALESCE(cnss,''))::char(11) AS cnss, "
						  	   "COALESCE(bconsecutivo,0) AS bconsecutivo, "
						  "TRIM(COALESCE(cfolioinfonavit,''))::char(14) AS cfolioinfonavit, "
						       "COALESCE(ifoliosolicitud,0) AS ifoliosolicitud, "
						  "TRIM(COALESCE(ctiporetiro,''))::char(1) AS ctiporetiro, "
						  "dfechacaptura::char(10) AS dfechacaptura, "
						  "TRIM(COALESCE(cusuariocaptura,''))::char(12) AS cusuariocaptura, "
						       "COALESCE(imigracionrettotsafre,0) AS imigracionrettotsafre "
						  "FROM fnconsultaretfolioinfonavitreplicart(%i);",iFolioServicio);

	objRetFolioInfonavit.ClearResults();
	if(objRetFolioInfonavit.Exec(cSql))
	{
		objRetFolioInfonavit.activarCols();
		if(objRetFolioInfonavit.leer())
		{
			memset(cNss, 0, sizeof(cNss));
			memset(cFolioInfonavit, 0, sizeof(cFolioInfonavit));
			memset(cTipoRetiro, 0, sizeof(cTipoRetiro));
			memset(cFechaCaptura, 0, sizeof(cFechaCaptura));
			memset(cUsuarioCaptura, 0, sizeof(cUsuarioCaptura));

			memmove(cNss, objRetFolioInfonavit.cNss, sizeof(11));
			memmove(cFolioInfonavit, objRetFolioInfonavit.cFolioinfonavit, sizeof(14));
			memmove(cTipoRetiro, objRetFolioInfonavit.cTiporetiro, sizeof(1));
					
			//memcpy(cFechaCaptura, objRetFolioInfonavit.cFechacaptura, 10);		
			snprintf(cFechaCaptura, strnlen(cFechaCaptura, sizeof(cFechaCaptura)), "MDY(%c%c,%c%c,%c%c%c%c)",
					objRetFolioInfonavit.cFechacaptura[5], 
					objRetFolioInfonavit.cFechacaptura[6],
					objRetFolioInfonavit.cFechacaptura[8],
					objRetFolioInfonavit.cFechacaptura[9],
					objRetFolioInfonavit.cFechacaptura[0],
					objRetFolioInfonavit.cFechacaptura[1],
					objRetFolioInfonavit.cFechacaptura[2],
					objRetFolioInfonavit.cFechacaptura[3]);		

			memmove(cUsuarioCaptura, objRetFolioInfonavit.cUsuariocaptura, sizeof(12));

			if (objRetFolioInfonavit.iFoliosolicitud == 0)
			{
				memset(cTexto, 0, sizeof(cTexto));
				snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "NO EXISTE INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
				objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
				objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
			}
			else
			{
				memset(cSqlAux,0, sizeof(cSqlAux));
				memset(cTexto,0, sizeof(cTexto));

				snprintf(cSqlAux, strnlen(cSqlAux, sizeof(cSqlAux)), "EXECUTE FUNCTION fn_guardarretfolioinfonavitreplicart('%s',%i,'%s',%i,'%s',%s,'%s');",
													cNss,
													objRetFolioInfonavit.iConsecutivo,
													cFolioInfonavit,
													objRetFolioInfonavit.iFoliosolicitud,
													cTipoRetiro,
													cFechaCaptura,
													cUsuarioCaptura
													);

				objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSqlAux, iRespuesta, cTexto);

				if (iRespuesta == 1)
				{
					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "SE MIGRO LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
					objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
				}
				else
				{
					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "NO SE PUDO MIGRAR LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "QUERY: [%s]", cSqlAux);
					
					objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
					objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
				}
			}
		}
		else
		{
			memset(cTexto, 0, sizeof(cTexto));
			snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] Error al leer la informacion que arroja el query: %s %i %s", __FILE__,__FUNCTION__, cSql, errno, strerror(errno));
			objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
		}
	}
	else
	{
		memset(cTexto, 0, sizeof(cTexto));
		snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] Error al Ejecutar el Query: %s %i %s", __FILE__,__FUNCTION__, cSql, errno, strerror(errno));
		objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
	}
}	
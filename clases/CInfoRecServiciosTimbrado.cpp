#include "CInfoRecServiciosTimbrado.hpp"

CInfoRecServiciosTimbrado::CInfoRecServiciosTimbrado()
{
	// TODO Auto-generated constructor stub
}

CInfoRecServiciosTimbrado::~CInfoRecServiciosTimbrado()
{
	// TODO Auto-generated destructor stub
}

short CInfoRecServiciosTimbrado::ReplicarRecServiciosTimbrado(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore)
{
	CTimbrado objRecSerTimbrado(odbcServiciosAfore);

	char cNss[13]			= {0};
	char cRfc[15]			= {0};
	char cFechaAlta[21]		= {0};
	char cTiposervicio[3]	= {0};
	
	char cSql[1024] 		= {0};
	char cSqlAux[1024] 		= {0};
	char cTexto[1024] 		= {0};

	int 	iRespuesta = 0;

	objFG.fnArcGrabarLogx(RUTA_LOG,"***********************************ENTRA RECSERVICIOS TIMBRADO***************************************");
	memset(cTexto,0,sizeof(cTexto));
	snprintf(cTexto, sizeof(cTexto), "FOLIO QUE SE ESTA MIGRANDO: [%i]", iFolioServicio);
	objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

	//OBTENCIÓN DE LA INFORMACION QUE SE VA A MIGRAR DE RECSERVICIOS AFORE TIMBRADO
	memset(cSql,0,sizeof(cSql));
	memset(cTexto,0,sizeof(cTexto));

	snprintf(cSql, sizeof(cSql), "SELECT  TRIM(COALESCE(nss,' '))::Char(11) AS nss, "
						  "TRIM(COALESCE(rfc,' '))::Char(13) AS rfc, "
						       "COALESCE(folioservicio,0) AS folioservicio, "
						  "TRIM(COALESCE(tiposervicio,' '))::Char(1) AS tiposervicio, "
						       "COALESCE(respuesta,0) AS respuesta, "
						       "COALESCE(migracionrettotsafre,0) AS migracionrettotsafre, "
						       "COALESCE(fechaalta,'1900-01-01 00:00:00')::char(19) AS fechaalta "
						"FROM fnconsultarecserviciostimbradoreplicart(%i);",iFolioServicio);

	objRecSerTimbrado.ClearResults();
	if(objRecSerTimbrado.Exec(cSql))
	{
		objRecSerTimbrado.activarCols();
		if(objRecSerTimbrado.leer())
		{
			memset(cNss, 0, sizeof(cNss));
			memset(cRfc, 0, sizeof(cRfc));
			memset(cFechaAlta, 0, sizeof(cFechaAlta));
			memset(cTiposervicio, 0, sizeof(cTiposervicio));

			memmove(cNss, objRecSerTimbrado.cNss, sizeof(cNss));
			memmove(cRfc, objRecSerTimbrado.cRfc, sizeof(cRfc));
			memmove(cTiposervicio, objRecSerTimbrado.cTiposervicio, sizeof(cTiposervicio));
			memmove(cFechaAlta, objRecSerTimbrado.cFechaAlta, sizeof(cFechaAlta));

			if (objRecSerTimbrado.iFolioservicio == 0)
			{
				memset(cTexto, 0, sizeof(cTexto));
				snprintf(cTexto, sizeof(cTexto), "NO EXISTE INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
				objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
				objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
			}
			else
			{
				memset(cSqlAux,0, sizeof(cSqlAux));
				memset(cTexto,0, sizeof(cTexto));

				snprintf(cSqlAux, sizeof(cSqlAux), "EXECUTE FUNCTION fn_guardarrecserviciostimbradoreplicart('%s','%s','%s',%i,'%s',%i);",
													cNss,
													cRfc,
													cFechaAlta,													
													objRecSerTimbrado.iFolioservicio,
													cTiposervicio,
													objRecSerTimbrado.iRespuesta
													);

				objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSqlAux, iRespuesta, cTexto);		

				if (iRespuesta == 1)
				{
					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, sizeof(cTexto), "SE MIGRO LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
					objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
				}
				else
				{
					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, sizeof(cTexto), "NO SE PUDO MIGRAR LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, sizeof(cTexto), "QUERY: [%s]", cSqlAux);
					
					objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
					objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
				}
			}
		}
		else
		{
			memset(cTexto, 0, sizeof(cTexto));
			snprintf(cTexto, sizeof(cTexto), "[%s][%s] Error al leer la informacion que arroja el query: %s %i %s", __FILE__,__FUNCTION__, cSql, errno, strerror(errno));
			objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
		}
	}
	else
	{
		memset(cTexto, 0, sizeof(cTexto));
		snprintf(cTexto, sizeof(cTexto), "[%s][%s] Error al Ejecutar el Query: %s %i %s", __FILE__,__FUNCTION__, cSql, errno, strerror(errno));
		objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
	}
}	
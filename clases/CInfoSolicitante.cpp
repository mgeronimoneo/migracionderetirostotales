#include "CInfoSolicitante.hpp"

CInfoSolicitante::CInfoSolicitante()
{
	// TODO Auto-generated constructor stub
}

CInfoSolicitante::~CInfoSolicitante()
{
	// TODO Auto-generated destructor stub
}

short CInfoSolicitante::ReplicarSolicitante(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore)
{
	CSolicitante objSolicitante(odbcServiciosAfore);

	char cCurp[20] 			= {0};
	char cPaterno[32] 		= {0};
	char cMaterno[32] 		= {0};
	char cNombres[32] 		= {0};
	char cTelefono[42] 		= {0};

	char cSql[1024] 		= {0};
	char cSqlAux[1024] 		= {0};
	char cTexto[1024] 		= {0};

	int 	iRespuesta = 0;

	objFG.fnArcGrabarLogx(RUTA_LOG,"***********************************ENTRA SOLICITANTE***************************************");
	memset(cTexto,0,sizeof(cTexto));
	snprintf(cTexto, sizeof(cTexto), "FOLIO QUE SE ESTA MIGRANDO: [%i]", iFolioServicio);
	objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

	//OBTENCIÓN DE LA INFORMACION QUE SE VA A MIGRAR DE SOLICITANTE
	memset(cSql,0,sizeof(cSql));
	memset(cTexto,0,sizeof(cTexto));

	snprintf(cSql, sizeof(cSql), "SELECT COALESCE(foliosolicitud,0) AS foliosolicitud, "
					"TRIM(COALESCE(curp,''))::char(18) AS curp, "
						 "COALESCE(consecutivo,0) AS consecutivo, "
				    "TRIM(COALESCE(paterno,''))::char(30) AS paterno, "
				    "TRIM(COALESCE(materno,''))::char(30) AS materno, "
				    "TRIM(COALESCE(nombres,''))::char(30) AS nombres, "
				    "TRIM(COALESCE(telefono,''))::char(40) AS telefono, "
				         "COALESCE(parencod,0) AS parencod, "
				         "COALESCE(migracionrettotsafre,0) AS mogracionrettotsafre "
		           "FROM fnconsultaretsolicitantereplicart(%i);",iFolioServicio);

	objSolicitante.ClearResults();
	if(objSolicitante.Exec(cSql))
	{
		objSolicitante.activarCols();
		if(objSolicitante.leer())
		{
			memset(cCurp, 0, sizeof(cCurp));
			memset(cPaterno, 0, sizeof(cPaterno));
			memset(cMaterno, 0, sizeof(cMaterno));
			memset(cNombres, 0, sizeof(cNombres));
			memset(cTelefono, 0, sizeof(cTelefono));

			memmove(cCurp, objSolicitante.cCurp, sizeof(cCurp));
			memmove(cPaterno, objSolicitante.cPaterno, sizeof(cPaterno));
			memmove(cMaterno, objSolicitante.cMaterno, sizeof(cMaterno));
			memmove(cNombres, objSolicitante.cNombres, sizeof(cNombres));
			memmove(cTelefono, objSolicitante.cTelefono, sizeof(cTelefono));

			if (objSolicitante.iFoliosolicitud == 0)
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

				snprintf(cSqlAux, sizeof(cSqlAux), "EXECUTE FUNCTION fn_guardarretsolicitantereplicart(%ld,'%s','%s','%s','%s',%i);",
													objSolicitante.lConsecutivo,
													cPaterno,
													cMaterno,
													cNombres,
													cTelefono,
													objSolicitante.iParencod
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
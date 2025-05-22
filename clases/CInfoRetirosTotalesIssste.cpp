#include "CInfoRetirosTotalesIssste.hpp"

CInfoRetirosTotalesIssste::CInfoRetirosTotalesIssste()
{
	// TODO Auto-generated constructor stub
}

CInfoRetirosTotalesIssste::~CInfoRetirosTotalesIssste()
{
	// TODO Auto-generated destructor stub
}
void CInfoRetirosTotalesIssste::setStSelloBiometricoSuv(ST_SELLOBIOMETRICO_SUV *stSuv)
{	
	char cTexto[5000] 		= {0};
		stSelloBiometricoSuv = stSuv;
	//memcpy(stSelloBiometricoSuv,stSuv,sizeof(stSuv));
	snprintf(cTexto, sizeof(cTexto), "[%s][%s] stSelloBiometricoSuv: cNss[%s] iIdsolicitante[%i] cCurpSolicitante[%s] cSellotrabajador[%s] cCurpAgente[%s] iConsecutivo[%i]", __FILE__,__FUNCTION__,stSelloBiometricoSuv->cNss,stSelloBiometricoSuv->iIdsolicitante,stSelloBiometricoSuv->cCurpSolicitante,stSelloBiometricoSuv->cSellotrabajador,stSelloBiometricoSuv->cCurpAgente,stSelloBiometricoSuv->iConsecutivo);
	objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
}//Termina CInfoRetirosTotalesIssste::setStSelloBiometricoSuv(ST_SELLOBIOMETRICO_SUV *stSuv)

void CInfoRetirosTotalesIssste::saveSelloBiometricoSuv(C_ODBC *odbcInfxSafreaf)
{
	objFG.fnArcGrabarLogx(RUTA_LOG,"=========== TABLA : RET_SELLOSBIOMETRICOS_SUV ===========");
	char cSql[5000] 		= {0};
	char cTexto[5000] 		= {0};
	char cAux[5000]		= {0};
	int shRespuesta		=  0;

	memset(cSql,0, sizeof(cSql));
	memset(cTexto,0, sizeof(cTexto));	
	
	snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_guardar_sellosuvtrabajador(2,'%s',%i,'%i','%s','%s','%s',0);",
	stSelloBiometricoSuv->cNss, stSelloBiometricoSuv->iConsecutivo, stSelloBiometricoSuv->iIdsolicitante, stSelloBiometricoSuv->cCurpSolicitante, 
	stSelloBiometricoSuv->cSellotrabajador, stSelloBiometricoSuv->cCurpAgente);//,stSelloBiometricoSuv->cCurpSolBene);
	
	snprintf(cTexto, sizeof(cTexto), "QUERY: [%s]", cSql);
	objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
	
	objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSql, shRespuesta, cAux);	
	
	if (shRespuesta == 1)
	{
		snprintf(cTexto, sizeof(cTexto), "SE MIGRO LA INFORMACION CON EL CONSECUTIVO: [%i]", stSelloBiometricoSuv->iConsecutivo);
		objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
	}
	else
	{
		snprintf(cTexto, sizeof(cTexto), "NO SE PUDO MIGRAR LA INFORMACION CON EL CONSECUTIVO: [%i]", stSelloBiometricoSuv->iConsecutivo);
		objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);	
	}
}///Termina CInfoRetirosTotalesIssste::saveSelloBiometricoSuv()

short CInfoRetirosTotalesIssste::ReplicarRetirosTotalesIssste(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore)
{
	CRetirostotalesissste objRetTotIssste(odbcServiciosAfore);

	char cCurp[20] 							= {0};
	char cRfc[15] 							= {0};
	char cNss[13] 							= {0};
	char cNombreafore[42] 					= {0};
	char cPaterno_afore[42] 				= {0};
	char cMaterno_afore[42] 				= {0};
	char cSecpension[4] 					= {0};
	char cTiporetiro[3] 					= {0};
	char cRegimen[4] 						= {0};
	char cTiposeguro[4] 					= {0};
	char cTipopension[4] 					= {0};
	char cCvepension[5] 					= {0};
	char cFechainiciopension[12] 			= {0};
	char cFecharesolucion[12] 				= {0};
	char cFechasolicitud[12] 				= {0};
	char cClavedocumentoprobatorio[3] 		= {0};
	char cFechanacimiento[12] 				= {0};
	char cAseguradora[5] 					= {0};
	char cActuario[9] 						= {0};
	char cNumplanprivado[10] 				= {0};
	char cDiagprocesar[5] 					= {0};
	char cFechacaptura[12] 					= {0};
	char cUsuariocaptura[17] 				= {0};
	char cFechamodifica[12] 				= {0};
	char cUsuariomodifica[17] 				= {0};
	char cFechaconfirma[12] 				= {0};
	char cUsuarioconfirma[17] 				= {0};

	char cSql[5000] 		= {0};
	char cSqlAux[5000] 		= {0};
	char cTexto[5000] 		= {0};

	int 	iRespuesta = 0;

	objFG.fnArcGrabarLogx(RUTA_LOG,"***********************************ENTRA RETIROS TOTALES ISSSTE***************************************");
	memset(cTexto,0,sizeof(cTexto));
	snprintf(cTexto, sizeof(cTexto), "FOLIO QUE SE ESTA MIGRANDO: [%i]", iFolioServicio);
	objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

	//OBTENCIÓN DE LA INFORMACION QUE SE VA A MIGRAR DE RETIROS TOTALES ISSSTE
	memset(cSql,0,sizeof(cSql));
	memset(cTexto,0,sizeof(cTexto));

	snprintf(cSql, sizeof(cSql), "SELECT COALESCE(folio,0) AS folio, "
						  "COALESCE(consecutivo,0) AS consecutivo, "
				     "TRIM(COALESCE(curp,' '))::char(18) AS curp, "
					 "TRIM(COALESCE(rfc,' '))::char(13) AS rfc, "
					 "TRIM(COALESCE(nss,' '))::char(11) AS nss, "
						  "COALESCE(foliosolicitud,0) AS foliosolicitud, "
					 "TRIM(COALESCE(nombreafore,' '))::char(40) AS nombreafore, "
					 "TRIM(COALESCE(paterno_afore,' '))::char(40) AS paterno_afore, "
					 "TRIM(COALESCE(materno_afore,' '))::char(40) AS materno_afore, "
					 "TRIM(COALESCE(secpension,' '))::char(2) AS secpension, "
					 "TRIM(COALESCE(tiporetiro,' '))::char(1) AS tiporetiro, "
					 "TRIM(COALESCE(regimen,' '))::char(2) AS regimen, "
					 "TRIM(COALESCE(tiposeguro,' '))::char(2) AS tiposeguro, "
					 "TRIM(COALESCE(tipopension,' '))::char(2) AS tipopension, "
					 "TRIM(COALESCE(cvepension,' '))::char(3) AS cvepension, "
					      "COALESCE(tipoprestacion,0) AS tipoprestacion, "
					 "TRIM(COALESCE(fechainiciopension,' '))::char(10) AS fechainiciopension, "
					 "TRIM(COALESCE(fecharesolucion,' '))::char(10) AS fecharesolucion, "
					 "TRIM(COALESCE(fechasolicitud,' '))::char(10) AS fechasolicitud, "
					 "TRIM(COALESCE(clavedocumentoprobatorio,' '))::char(1) AS clavedocumentoprobatorio, "
					 "TRIM(COALESCE(fechanacimiento,' '))::char(10) AS fechanacimiento, "
					 "TRIM(COALESCE(aseguradora,' '))::char(3) AS aseguradora, "
					 "TRIM(COALESCE(actuario,' '))::char(7) AS actuario, "
					 "TRIM(COALESCE(numplanprivado,' '))::char(8) AS numplanprivado, "
					       "COALESCE(periodopago,0) AS periodopago, "
					       "COALESCE(semanas_cotizadas,0) AS semanas_cotizadas, "
					       "COALESCE(estadcod,0) AS estadcod, "
					       "COALESCE(delegcod,0) AS delegcod, "
					 "TRIM(COALESCE(diagprocesar,' '))::char(3) AS diagprocesar, "
					 	  "COALESCE(grupo,0) AS grupo, "
				     "TRIM(COALESCE(fechacaptura,' '))::char(10) AS fechacaptura, "
				     "TRIM(COALESCE(usuariocaptura,' '))::char(15) AS usuariocaptura, "
				     "TRIM(COALESCE(fechamodifica,' '))::char(10) AS fechamodifica, "
				     "TRIM(COALESCE(usuariomodifica,' '))::char(15) AS usuariomodifica, "
				     "TRIM(COALESCE(fechaconfirma,' '))::char(10) AS fechaconfirma, "
				     "TRIM(COALESCE(usuarioconfirma,' '))::char(15) AS usuarioconfirma, "
				          "COALESCE(codigo_rechazo,0) AS codigo_rechazo, "
				          "COALESCE(estado_solicitud,0) AS estado_solicitud "
				          //"COALESCE(migracionrettolsafre,0) AS migracionrettolsafre "
					"FROM fnconsultaretirostotalesissstereplica(%i);",iFolioServicio);

	objRetTotIssste.ClearResults();
	if(objRetTotIssste.Exec(cSql))
	{
		objRetTotIssste.activarCols();
		if(objRetTotIssste.leer())
		{
			memset(cCurp, 0, sizeof(cCurp));
			memset(cRfc, 0, sizeof(cRfc));
			memset(cNss, 0, sizeof(cNss));
			memset(cNombreafore, 0, sizeof(cNombreafore));
			memset(cPaterno_afore, 0, sizeof(cPaterno_afore));
			memset(cMaterno_afore, 0, sizeof(cMaterno_afore));
			memset(cSecpension, 0, sizeof(cSecpension));
			memset(cTiporetiro, 0, sizeof(cTiporetiro));
			memset(cRegimen, 0, sizeof(cRegimen));
			memset(cTiposeguro, 0, sizeof(cTiposeguro));
			memset(cTipopension, 0, sizeof(cTipopension));
			memset(cCvepension, 0, sizeof(cCvepension));
			memset(cFechainiciopension, 0, sizeof(cFechainiciopension));
			memset(cFecharesolucion, 0, sizeof(cFecharesolucion));
			memset(cFechasolicitud, 0, sizeof(cFechasolicitud));
			memset(cClavedocumentoprobatorio, 0, sizeof(cClavedocumentoprobatorio));
			memset(cFechanacimiento, 0, sizeof(cFechanacimiento));
			memset(cAseguradora, 0, sizeof(cAseguradora));
			memset(cActuario, 0, sizeof(cActuario));
			memset(cNumplanprivado, 0, sizeof(cNumplanprivado));
			memset(cDiagprocesar, 0, sizeof(cDiagprocesar));
			memset(cFechacaptura, 0, sizeof(cFechacaptura));
			memset(cUsuariocaptura, 0, sizeof(cUsuariocaptura));
			memset(cFechamodifica, 0, sizeof(cFechamodifica));
			memset(cUsuariomodifica, 0, sizeof(cUsuariomodifica));
			memset(cFechaconfirma, 0, sizeof(cFechaconfirma));
			memset(cUsuarioconfirma, 0, sizeof(cUsuarioconfirma));

			memmove(cCurp, objRetTotIssste.cCurp, sizeof(cCurp));
			memmove(cRfc, objRetTotIssste.cRfc, sizeof(cRfc));
			memmove(cNss, objRetTotIssste.cNss, sizeof(cNss));
			memmove(cNombreafore, objRetTotIssste.cNombreafore, sizeof(cNombreafore));
			memmove(cPaterno_afore, objRetTotIssste.cPaterno_afore, sizeof(cPaterno_afore));
			memmove(cMaterno_afore, objRetTotIssste.cMaterno_afore, sizeof(cMaterno_afore));
			memmove(cSecpension, objRetTotIssste.cSecpension, sizeof(cSecpension));
			memmove(cTiporetiro, objRetTotIssste.cTiporetiro, sizeof(cTiporetiro));
			memmove(cRegimen, objRetTotIssste.cRegimen, sizeof(cRegimen));
			memmove(cTiposeguro, objRetTotIssste.cTiposeguro, sizeof(cTiposeguro));
			memmove(cTipopension, objRetTotIssste.cTipopension, sizeof(cTipopension));
			memmove(cCvepension, objRetTotIssste.cCvepension, sizeof(cCvepension));

			//memcpy(cFechainiciopension, objRetTotIssste.cFechainiciopension, 10);
			snprintf(cFechainiciopension, sizeof(cFechainiciopension), "%c%c%c%c-%c%c-%c%c",
					objRetTotIssste.cFechainiciopension[6], 
					objRetTotIssste.cFechainiciopension[7],
					objRetTotIssste.cFechainiciopension[8], 
					objRetTotIssste.cFechainiciopension[9],
					objRetTotIssste.cFechainiciopension[0],
					objRetTotIssste.cFechainiciopension[1],
					objRetTotIssste.cFechainiciopension[3],
					objRetTotIssste.cFechainiciopension[4]);

			//memcpy(cFecharesolucion, objRetTotIssste.cFecharesolucion, 10);
			snprintf(cFecharesolucion, sizeof(cFecharesolucion), "%c%c%c%c-%c%c-%c%c",
					objRetTotIssste.cFecharesolucion[6], 
					objRetTotIssste.cFecharesolucion[7],
					objRetTotIssste.cFecharesolucion[8], 
					objRetTotIssste.cFecharesolucion[9],
					objRetTotIssste.cFecharesolucion[0],
					objRetTotIssste.cFecharesolucion[1],
					objRetTotIssste.cFecharesolucion[3],
					objRetTotIssste.cFecharesolucion[4]);

			//memcpy(cFechasolicitud, objRetTotIssste.cFechasolicitud, 10);
			snprintf(cFechasolicitud, sizeof(cFechasolicitud), "%c%c%c%c-%c%c-%c%c",
					objRetTotIssste.cFechasolicitud[6], 
					objRetTotIssste.cFechasolicitud[7],
					objRetTotIssste.cFechasolicitud[8], 
					objRetTotIssste.cFechasolicitud[9],
					objRetTotIssste.cFechasolicitud[0],
					objRetTotIssste.cFechasolicitud[1],
					objRetTotIssste.cFechasolicitud[3],
					objRetTotIssste.cFechasolicitud[4]);

			memmove(cClavedocumentoprobatorio, objRetTotIssste.cClavedocumentoprobatorio, sizeof(cClavedocumentoprobatorio));
			//memcpy(cFechanacimiento, objRetTotIssste.cFechanacimiento, 10);
			snprintf(cFechanacimiento, sizeof(cFechanacimiento), "%c%c%c%c-%c%c-%c%c",
					objRetTotIssste.cFechanacimiento[6], 
					objRetTotIssste.cFechanacimiento[7],
					objRetTotIssste.cFechanacimiento[8], 
					objRetTotIssste.cFechanacimiento[9],
					objRetTotIssste.cFechanacimiento[0],
					objRetTotIssste.cFechanacimiento[1],
					objRetTotIssste.cFechanacimiento[3],
					objRetTotIssste.cFechanacimiento[4]);

			memmove(cAseguradora, objRetTotIssste.cAseguradora, sizeof(cAseguradora));
			memmove(cActuario, objRetTotIssste.cActuario, sizeof(cActuario));
			memmove(cNumplanprivado, objRetTotIssste.cNumplanprivado, sizeof(cNumplanprivado));
			memmove(cDiagprocesar, objRetTotIssste.cDiagprocesar, sizeof(cDiagprocesar));

			//memcpy(cFechacaptura, objRetTotIssste.cFechacaptura, 10);
			snprintf(cFechacaptura, sizeof(cFechacaptura), "%c%c%c%c-%c%c-%c%c",
					objRetTotIssste.cFechacaptura[6], 
					objRetTotIssste.cFechacaptura[7],
					objRetTotIssste.cFechacaptura[8], 
					objRetTotIssste.cFechacaptura[9],
					objRetTotIssste.cFechacaptura[0],
					objRetTotIssste.cFechacaptura[1],
					objRetTotIssste.cFechacaptura[3],
					objRetTotIssste.cFechacaptura[4]);

			memmove(cUsuariocaptura, objRetTotIssste.cUsuariocaptura, sizeof(cUsuariocaptura));

			//memcpy(cFechamodifica, objRetTotIssste.cFechamodifica, 10);
			snprintf(cFechamodifica, sizeof(cFechamodifica), "%c%c%c%c-%c%c-%c%c",
					objRetTotIssste.cFechamodifica[6], 
					objRetTotIssste.cFechamodifica[7],
					objRetTotIssste.cFechamodifica[8], 
					objRetTotIssste.cFechamodifica[9],
					objRetTotIssste.cFechamodifica[0],
					objRetTotIssste.cFechamodifica[1],
					objRetTotIssste.cFechamodifica[3],
					objRetTotIssste.cFechamodifica[4]);

			memmove(cUsuariomodifica, objRetTotIssste.cUsuariomodifica, sizeof(cUsuariomodifica));

			//memcpy(cFechaconfirma, objRetTotIssste.cFechaconfirma, 10);
			snprintf(cFechaconfirma, sizeof(cFechaconfirma), "%c%c%c%c-%c%c-%c%c",
					objRetTotIssste.cFechaconfirma[6], 
					objRetTotIssste.cFechaconfirma[7],
					objRetTotIssste.cFechaconfirma[8], 
					objRetTotIssste.cFechaconfirma[9],
					objRetTotIssste.cFechaconfirma[0],
					objRetTotIssste.cFechaconfirma[1],
					objRetTotIssste.cFechaconfirma[3],
					objRetTotIssste.cFechaconfirma[4]);

			memmove(cUsuarioconfirma, objRetTotIssste.cUsuarioconfirma, sizeof(cUsuarioconfirma));

			if (objRetTotIssste.iFoliosolicitud == 0)
			{
				memset(cTexto, 0, sizeof(cTexto));
				snprintf(cTexto, sizeof(cTexto), "NO EXISTE INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
				objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
				objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
			}
			else
			{

				memset(cSqlAux,0,sizeof(cSqlAux));
				memset(cTexto,0,sizeof(cTexto));

				if (objRetTotIssste.iGrupo != 0)
				{			
					snprintf(cSqlAux, sizeof(cSqlAux), "EXECUTE FUNCTION fn_guardarretirostotalesissstereplica(%i,%ld,'%s','%s','%s',%i,'%s','%s','%s','%s','%s','%s','%s','%s','%s',%i,'%s','%s','%s','%s','%s','%s','%s','%s',%i,%i,%i,%i,'%s',%i,'%s','%s','%s','%s','%s','%s',%i,%i);",
														objRetTotIssste.iFolio,
														objRetTotIssste.lConsecutivo,
														cCurp,
														cRfc,
														cNss,
														objRetTotIssste.iFoliosolicitud,
														cNombreafore,
														cPaterno_afore,
														cMaterno_afore,
														cSecpension,
														cTiporetiro,
														cRegimen,
														cTiposeguro,
														cTipopension,
														cCvepension,
														objRetTotIssste.iTipoprestacion,
														cFechainiciopension,
														cFecharesolucion,
														cFechasolicitud,
														cClavedocumentoprobatorio,
														cFechanacimiento,
														cAseguradora,
														cActuario,
														cNumplanprivado,
														objRetTotIssste.iPeriodopago,
														objRetTotIssste.iSemanas_cotizadas,
														objRetTotIssste.iEstadcod,
														objRetTotIssste.iDelegcod,
														cDiagprocesar,
														objRetTotIssste.iGrupo,
														cFechacaptura,
														cUsuariocaptura,
														cFechamodifica,
														cUsuariomodifica,
														cFechaconfirma,
														cUsuarioconfirma,
														objRetTotIssste.iCodigo_rechazo,
														objRetTotIssste.iEstado_solicitud
														);										

					objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSqlAux, iRespuesta, cTexto);

					if (iRespuesta == 1)
					{
						memset(cTexto, 0, sizeof(cTexto));
						snprintf(cTexto, sizeof(cTexto), "SE MIGRO LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
						objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
						//saveSelloBiometricoSuv(odbcInfxSafreaf);	    
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
				else
				{
					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, sizeof(cTexto), "NO SE PUDO MIGRAR LA INFORMACION CON EL FOLIO: [%i] POR QUE NO PERTENECE A UN GRUPO VALIDO", iFolioServicio);
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
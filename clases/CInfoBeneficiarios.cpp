#include "CInfoBeneficiarios.hpp"

CInfoBeneficiarios::CInfoBeneficiarios()
{
	// TODO Auto-generated constructor stub
}

CInfoBeneficiarios::~CInfoBeneficiarios()
{
	// TODO Auto-generated destructor stub
}

short CInfoBeneficiarios::ReplicarBeneficiarios(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore)
{
	CBeneficiario objBen(odbcServiciosAfore);

	char	cNss[13] 				= {0};
	char 	cApPaterno[32]			= {0};
	char 	cApMaterno[32] 			= {0};
	char 	cNombres[32] 			= {0};
	char 	cNssbenef[13] 			= {0};
	char 	cCurpbenef[20] 			= {0};
	char 	cRfcbenef[15] 			= {0};
	char 	cCorreoelect[102] 		= {0};
	char 	cNumcuenta[20] 			= {0};
	char 	cTipocuenta[3] 			= {0};
	char 	cClabe[20] 				= {0};
	char 	cFechapago[17] 			= {0};
	char 	cDomcalle[42] 			= {0};
	char 	cDomnumeroext[12] 		= {0};
	char 	cDomnumeroint[12] 		= {0};
	char 	cDomcodpos[7] 			= {0};
	char 	cDomcolonia[62] 		= {0};
	char 	cDompais[5] 			= {0};
	char 	cDomtelefono[42] 		= {0};
	char 	cNumordpago[22] 		= {0};
	char 	cFechacaptura[17] 		= {0};
	char 	cFechamodifica[17] 		= {0};
	char 	cUsuariocaptura[14]		= {0};
	char 	cUsuariomodifica[14] 	= {0};

	char	cSql[2024] 		= {0};
	char	cSqlAux[2024] 	= {0};
	char 	cTexto[2024] 	= {0};

	int 	iRespuesta = 0;

	objFG.fnArcGrabarLogx(RUTA_LOG,"***********************************ENTRA BENEFICIARIOS***************************************");
	memset(cTexto,0,sizeof(cTexto));
	snprintf(cTexto, sizeof(cTexto), "FOLIO QUE SE ESTA MIGRANDO: [%i]", iFolioServicio);
	objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);	
							
	//OBTENCIÓN DE LA INFORMACION QUE SE VA A MIGRAR DE BENEFICIARIOS
	memset(cSql,0,sizeof(cSql));
	memset(cTexto,0,sizeof(cTexto));
	
	snprintf(cSql, sizeof(cSql), "SELECT  COALESCE(iFoliosolicitud,0) as foliosolicitud, "
		                  "TRIM(COALESCE(cNss,' '))::Char(11) as nss, "
		                  "COALESCE(iConsecutivo,0)::Bigint as consecutivo, " 
		                  "COALESCE(iConsecbenef,0)::Smallint as consecbenef, "
		                  "COALESCE(iTipopago,0)::Smallint as tipopago, "
						  "COALESCE(iParencod,0)::Smallint as parencod, "
						  "TRIM(COALESCE(cPaterno,' '))::Char(30) as paterno, "
						  "TRIM(COALESCE(cMaterno,' '))::Char(30) as materno, "
						  "TRIM(COALESCE(cNombres,' '))::Char(30) as nombres, "
						  "TRIM(COALESCE(cNssbenef,' '))::Char(11) as nssbenef, "
						  "TRIM(COALESCE(cCurpbenef,' '))::Char(18) as curpbenef, "
						  "TRIM(COALESCE(cRfcbenef,' '))::Char(13) as rfcbenef, "
						  "TRIM(COALESCE(cCorreoelect,' '))::Char(100) as correoelect, "
						  "COALESCE(iPorcentaje,0)::Smallint as porcentaje, "
						  "COALESCE(iTiendacod,0)::Integer as tiendacod, "
						  "COALESCE(iBanco,0)::Smallint as banco, "
						  "COALESCE(iCodsucursal,0)::Integer as codsucursal, "
						  "COALESCE(iCodplaza,0)::Smallint as codplaza, "
						  "COALESCE(iCiudadcod,0)::Smallint as ciudadcod, "
						  "COALESCE(iEstadcod,0)::Smallint as estadcod, "
						  "TRIM(COALESCE(cNumcuenta,' '))::Char(18) as numcuenta, "
						  "TRIM(COALESCE(cTipocuenta,' '))::Char(1) as tipocuenta, "
						  "TRIM(COALESCE(cClabe,' '))::Char(18) as clabe, "
						  "COALESCE(iNumcheque,0)::Double precision as numcheque, "
						  "COALESCE(iMontoenpesos,0)::Double precision as montoenpesos, "
						  "TRIM(COALESCE(cFechapago,' '))::Char(15) as fechapago, "
						  "TRIM(COALESCE(cDomcalle,' '))::Char(40) as domcalle, "
						  "TRIM(COALESCE(cDomnumeroext,' '))::Char(10) as domnumeroext, "
						  "TRIM(COALESCE(cDomnumeroint,' '))::Char(10) as domnumeroint, "
						  "TRIM(COALESCE(cDomcodpos,' '))::Char(5) as domcodpos, "
						  "TRIM(COALESCE(cDomcolonia,' '))::Char(60) as domcolonia, "
						  "COALESCE(iDomdelega,0)::Integer as domdelega, "
						  "COALESCE(iDomciudadcod,0)::Smallint as domciudadcod, "
						  "COALESCE(iDomestadocod,0)::Smallint as domestadocod, "
						  "TRIM(COALESCE(cDompais,' '))::Char(3) as dompais, "
						  "TRIM(COALESCE(cDomtelefono,' '))::Char(40) as domtelefono, "
						  "TRIM(COALESCE(cDumordpago,' '))::Char(20) as numordpago, "
						  "TRIM(COALESCE(cFechacaptura,' '))::Char(15) as fechacaptura, "
						  "TRIM(COALESCE(cFechamodifica,' '))::Char(15) as fechamodifica, "
						  "TRIM(COALESCE(cUsuariocaptura,' '))::Char(12) as usuariocaptura, "
						  "TRIM(COALESCE(cUsuariomodifica,' '))::Char(12) as usuariomodifica, "
						  "COALESCE(iMigracionretparsafre,0)::Smallint as migracionretparsafre FROM fnconsultabeneficiariosrtreplica(%i);",iFolioServicio);

	objBen.ClearResults();
	if(objBen.Exec(cSql))
	{			
		objBen.activarCols();
		if(objBen.leer())
		{			
			memset(cNss, 0, sizeof(cNss));
			memset(cApPaterno, 0, sizeof(cApPaterno));
			memset(cApMaterno, 0, sizeof(cApMaterno));
			memset(cNombres, 0, sizeof(cNombres));
			memset(cNssbenef, 0, sizeof(cNssbenef));
			memset(cCurpbenef, 0, sizeof(cCurpbenef));
			memset(cRfcbenef, 0 , sizeof(cRfcbenef));
			memset(cCorreoelect, 0 , sizeof(cCorreoelect));
			memset(cNumcuenta, 0, sizeof(cNumcuenta));
			memset(cTipocuenta, 0, sizeof(cTipocuenta));
			memset(cClabe, 0, sizeof(cClabe));									
			memset(cFechapago, 0, sizeof(cFechapago));
			memset(cDomcalle, 0, sizeof(cDomcalle));
			memset(cDomnumeroext, 0, sizeof(cDomnumeroext));
			memset(cDomnumeroint, 0, sizeof(cDomnumeroint));
			memset(cDomcodpos, 0, sizeof(cDomcodpos));
			memset(cDomcolonia, 0, sizeof(cDomcolonia));
			memset(cDompais, 0, sizeof(cDompais));
			memset(cDomtelefono, 0, sizeof(cDomtelefono));
			memset(cNumordpago, 0, sizeof(cNumordpago));
			memset(cFechacaptura, 0, sizeof(cFechacaptura));
			memset(cFechamodifica, 0, sizeof(cFechamodifica));
			memset(cUsuariocaptura, 0, sizeof(cUsuariocaptura));
			memset(cUsuariomodifica, 0, sizeof(cUsuariomodifica));

			memmove(cNss, objBen.nss, sizeof(11));
			memmove(cApPaterno, objBen.paterno, sizeof(30));
			memmove(cApMaterno, objBen.materno, sizeof(30));
			memmove(cNombres, objBen.nombres, sizeof(30));
			memmove(cNssbenef, objBen.nssbenef, sizeof(11));
			memmove(cCurpbenef, objBen.curpbenef, sizeof(18));
			memmove(cRfcbenef, objBen.rfcbenef, sizeof(13));
			memmove(cCorreoelect, objBen.correoelect, sizeof(100));
			memmove(cNumcuenta, objBen.numcuenta, sizeof(18));
			memmove(cTipocuenta, objBen.tipocuenta, sizeof(1));
			memmove(cClabe, objBen.clabe, sizeof(18));	

			//memcpy(cFechapago, objBen.fechapago, 15);
			snprintf(cFechapago, sizeof(cFechapago), "%c%c%c%c-%c%c-%c%c",
					objBen.fechapago[6], 
					objBen.fechapago[7],
					objBen.fechapago[8], 
					objBen.fechapago[9],
					objBen.fechapago[0],
					objBen.fechapago[1],
					objBen.fechapago[3],
					objBen.fechapago[4]);

			memmove(cDomcalle, objBen.domcalle, sizeof(40));
			memmove(cDomnumeroext, objBen.domnumeroext, sizeof(10));
			memmove(cDomnumeroint, objBen.domnumeroint, sizeof(10));
			memmove(cDomcodpos, objBen.domcodpos, sizeof(5));
			memmove(cDomcolonia, objBen.domcolonia, sizeof(60));	
			memmove(cDompais, objBen.dompais, sizeof(3));
			memmove(cDomtelefono, objBen.domtelefono, sizeof(40));
			memmove(cNumordpago, objBen.numordpago, sizeof(20));

			//memcpy(cFechacaptura, objBen.fechacaptura, 15);
			snprintf(cFechacaptura, sizeof(cFechacaptura), "%c%c%c%c-%c%c-%c%c",
					objBen.fechacaptura[6], 
					objBen.fechacaptura[7],
					objBen.fechacaptura[8], 
					objBen.fechacaptura[9],
					objBen.fechacaptura[0],
					objBen.fechacaptura[1],
					objBen.fechacaptura[3],
					objBen.fechacaptura[4]);

			//memcpy(cFechamodifica, objBen.fechamodifica, 15);
			snprintf(cFechamodifica, sizeof(cFechamodifica), "%c%c%c%c-%c%c-%c%c",
					objBen.fechamodifica[6], 
					objBen.fechamodifica[7],
					objBen.fechamodifica[8], 
					objBen.fechamodifica[9],
					objBen.fechamodifica[0],
					objBen.fechamodifica[1],
					objBen.fechamodifica[3],
					objBen.fechamodifica[4]);

			memmove(cUsuariocaptura, objBen.usuariocaptura, sizeof(12));
			memmove(cUsuariomodifica, objBen.usuariomodifica, sizeof(12));

			if (objBen.foliosolicitud == 0)
			{
				memset(cTexto, 0, sizeof(cTexto));
				snprintf(cTexto, sizeof(cTexto), "NO EXISTE INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
				objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
				objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
			}
			else if (objBen.tipopago == 0)
			{	
				memset(cTexto, 0, sizeof(cTexto));
				snprintf(cTexto, sizeof(cTexto), "TIPO PAGO INCORRECTO PARA EL FOLIO: [%i]", iFolioServicio);
				objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
				objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
			}
			else
			{		
				memset(cSqlAux,0, sizeof(cSqlAux));
				memset(cTexto,0, sizeof(cTexto));
				
				snprintf(cSqlAux, sizeof(cSqlAux), "EXECUTE FUNCTION fn_guardarbeneficiariosrtreplica('%s',%ld,%i,%i,%i,'%s','%s','%s','%s','%s','%s','%s',%i,%i,%i,%i,%i,%i,%i,'%s','%s','%s', %f,%f,'%s','%s','%s','%s','%s','%s',%i,%i,%i,'%s','%s','%s','%s','%s','%s','%s');",
																							 cNss,
					                                                                         objBen.consecutivo,
					                                                                         objBen.consecbenef,
					                                                                         objBen.tipopago,
					                                                                         objBen.parencod,
					                                                                         cApPaterno,
					                                                                         cApMaterno,
					                                                                         cNombres,
					                                                                         cNssbenef,
					                                                                         cCurpbenef,
					                                                                         cRfcbenef,
					                                                                         cCorreoelect,
					                                                                         objBen.porcentaje,
					                                                                         objBen.tiendacod,
					                                                                         objBen.banco,
					                                                                         objBen.codsucursal,
					                                                                         objBen.codplaza,
					                                                                         objBen.ciudadcod,
					                                                                         objBen.estadcod,
					                                                                         cNumcuenta,
					                                                                         cTipocuenta,
					                                                                         cClabe,
					                                                                         objBen.numcheque,
					                                                                         objBen.montoenpesos,
					                                                                         cFechapago,
					                                                                         cDomcalle,
					                                                                         cDomnumeroext,
					                                                                         cDomnumeroint,
					                                                                         cDomcodpos,
					                                                                         cDomcolonia,				                                                                         
					                                                                         objBen.domdelega,
					                                                                         objBen.domciudadcod,
					                                                                         objBen.domestadocod,
					                                                                         cDompais,
					                                                                         cDomtelefono,
					                                                                         cNumordpago,
					                                                                         cFechacaptura,
					                                                                         cFechamodifica,
					                                                                         cUsuariocaptura,
					                                                                         cUsuariomodifica
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


void CInfoBeneficiarios::replicaControlBeneficiarios(int iFolioServicio, int iConsecutivo, int iCodigoMotivo, char *cTipoRetiro, C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore)
{
	CControlBeneficiario objBen(odbcServiciosAfore);

	char	cNSSTrab[13] 				= {0};

	char	cSql[2024] 		= {0};
	char	cSqlAux[2024] 	= {0};
	char 	cTexto[2024] 	= {0};

	int 	iRespuesta = 0;

	objFG.fnArcGrabarLogx(RUTA_LOG,"***********************************ENTRA CONTROL BENEFICIARIOS***************************************");
	memset(cTexto,0,sizeof(cTexto));
	snprintf(cTexto, sizeof(cTexto),"FOLIO QUE SE ESTA MIGRANDO: [%i]", iFolioServicio);
	objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);	
							
	//OBTENCIÓN DE LA INFORMACION QUE SE VA A MIGRAR DE BENEFICIARIOS
	memset(cSql,0,sizeof(cSql));
	memset(cTexto,0,sizeof(cTexto));
	
	snprintf(cSql, sizeof(cSql), "SELECT  COALESCE(iFoliosolicitud,0) as foliosolicitud, "
						  "TRIM(COALESCE(cNss,' '))::Char(11) as nsstrab, "
						  "COALESCE(iTiposolicitante,0)::Smallint as tipobeneficiario, "
						  "COALESCE(iPorcentajebeneficiario,0) as porcbeneficiario, "
						  "COALESCE(iPorcentaje,0)::Smallint as porcentajelegal "
						  "FROM fnconsultabeneficiariosrtreplica(%i);",iFolioServicio);

	objBen.ClearResults();
	if(objBen.Exec(cSql))
	{			
		objBen.activarCols();
		if(objBen.leer())
		{			
			memset(cTexto, 0, sizeof(cTexto));
			snprintf(cTexto, sizeof(cTexto), "PORCENTAJE LEGAL [%i]", objBen.porcentajelegal);
			objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

			memset(cNSSTrab, 0, sizeof(cNSSTrab));

			memmove(cNSSTrab, objBen.nsstrab, sizeof(11));

			if (objBen.foliosolicitud == 0)
			{
				memset(cTexto, 0, sizeof(cTexto));
				snprintf(cTexto, sizeof(cTexto), "NO EXISTE INFORMACION CON EL FOLIO [CONTROL_BENEF]: [%i]", iFolioServicio);
				objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
				objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
			}
			else
			{		
				memset(cSqlAux,0, sizeof(cSqlAux));
				memset(cTexto,0, sizeof(cTexto));
				
				if (objBen.tipobeneficiario == 1 || objBen.tipobeneficiario == 2 || 
				objBen.tipobeneficiario == 3 || objBen.tipobeneficiario == 4)
				{
					
					snprintf(cSqlAux, sizeof(cSqlAux), "EXECUTE FUNCTION fn_reg_ctr_benef('%s', %i, %i, %i, '%s', %i, %i);",
																							cNSSTrab,
																							iConsecutivo,
																							objBen.tipobeneficiario,
																							objBen.porcbeneficiario,
																							cTipoRetiro,
																							iCodigoMotivo,
																							objBen.porcentajelegal
																							);	
					objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSqlAux, iRespuesta, cTexto);	
				}
		

				if (iRespuesta == 1)
				{
					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, sizeof(cTexto), "SE GUARDO INFORMACION CON EL FOLIO EN RET_CTR_BENEF: [%i]", iFolioServicio);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
					objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
				}
				else
				{
					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, sizeof(cTexto), "NO SE GUARDO INFORMACION CON EL FOLIO EN RET_CTR_BENEF: [%i] TIPO DE BENEF: [%i]", iFolioServicio,objBen.tipobeneficiario);
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

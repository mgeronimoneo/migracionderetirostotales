#ifndef STRUCT_HPP_
#define STRUCT_HPP_

#include <stdio.h>
#include <string.h>


struct ST_SELLOBIOMETRICO_SUV
{
	char cNss[13];
	int iConsecutivo;	
	char cCurpSolicitante[20];
	char cSellotrabajador[16];
	char cCurpAgente[20];
	char cCurpSolBene[20];
	int iIdentificador;
	int iTipoServicio;
	int iIdsolicitante;
	int iIdentificadorPago;
	
	ST_SELLOBIOMETRICO_SUV()
	{
		memset(cNss, 			0, 	sizeof(cNss));		
		memset(cCurpSolicitante, 	0, 	sizeof(cCurpSolicitante));
		memset(cSellotrabajador, 	0, 	sizeof(cSellotrabajador));
		memset(cCurpAgente, 		0, 	sizeof(cCurpAgente));
		memset(cCurpSolBene,		0,	sizeof(cCurpSolBene));
		iConsecutivo		=0;
		iIdentificador		=0;
		iTipoServicio		=0;
		iIdsolicitante		=0;
		iIdentificadorPago	=0;
		
	}	
	///totalesimss, totalesissste, pmgissste
};//Termina struct ST_SELLOBIOMETRICO_SUV

#endif

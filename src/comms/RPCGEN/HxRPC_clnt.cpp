/*
******************************************************************************
*ID01                           IDENTIFICACION    
*
*    FICHERO   : HxRPC_clnt.cpp            ID        :   
*    PROGRAMA  : STSS                            FECHA     : 27/Mar/2006
*    SISTEMA   : FMS&FBMS                        REVISION  : $Revision: 1.2 $
*    SUBSISTEMA: HOST                            AUTOR     : Ejecutivo
*    MODULO    : EJECUTIVO PRINCIPAL             COMPA�IA  : INDRA
******************************************************************************
*DF02                       DESCRIPCION FUNCIONAL            
*
*    Metodos para el manejo del servidor RPC
*
******************************************************************************
*HC03                        HISTORIA DE CAMBIOS  
*
*    ED/REV     FECHA                                           AUTOR
*    N�-NCI:    DESCRIPCION DEL CAMBIO  
*
*    $Log: HxRPC_clnt.cpp,v $
*
*
*****************************************************************************/
/*%FIN*/
#include <memory.h> /* for memset */
#include "comms/RPCGEN/HxComServ.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = {25, 0};

int* consulto_1(const char* arg1, CLIENT* clnt)
{
    static int clnt_res;

    memset((char*)&clnt_res, 0, sizeof(clnt_res));
    if (clnt_call(clnt, consulto,
                  (xdrproc_t)xdr_wrapstring, (caddr_t)&arg1,
                  (xdrproc_t)xdr_int, (caddr_t)&clnt_res,
                  TIMEOUT) != RPC_SUCCESS)
    {
        return (NULL);
    }
    return (&clnt_res);
}

char**
leo_1(const char* arg1, CLIENT* clnt)
{
    static char* clnt_res;

    memset((char*)&clnt_res, 0, sizeof(clnt_res));
    if (clnt_call(clnt, leo,
                  (xdrproc_t)xdr_wrapstring, (caddr_t)&arg1,
                  (xdrproc_t)xdr_wrapstring, (caddr_t)&clnt_res,
                  TIMEOUT) != RPC_SUCCESS)
    {
        return (NULL);
    }
    return (&clnt_res);
}

void* escribo_1(char* arg1, const char* arg2, CLIENT* clnt)
{
    escribo_1_argument arg;
    static char        clnt_res;

    memset((char*)&clnt_res, 0, sizeof(clnt_res));
    arg.arg1 = arg1;
    arg.arg2 = (char*)arg2;
    if (clnt_call(clnt, escribo,
                  (xdrproc_t)xdr_escribo_1_argument, (caddr_t)&arg,
                  (xdrproc_t)xdr_void, (caddr_t)&clnt_res,
                  TIMEOUT) != RPC_SUCCESS)
    {
        return (NULL);
    }
    return ((void*)&clnt_res);
}

char**
get_var_address__1(char* arg1, CLIENT* clnt)
{
    static char* clnt_res;

    memset((char*)&clnt_res, 0, sizeof(clnt_res));
    if (clnt_call(clnt, Get_var_address_,
                  (xdrproc_t)xdr_wrapstring, (caddr_t)&arg1,
                  (xdrproc_t)xdr_wrapstring, (caddr_t)&clnt_res,
                  TIMEOUT) != RPC_SUCCESS)
    {
        return (NULL);
    }
    return (&clnt_res);
}

void* lista_monitor_substring_begin__1(int arg1, char* arg2, CLIENT* clnt)
{
    lista_monitor_argument arg;
    static char            clnt_res;

    memset((char*)&clnt_res, 0, sizeof(clnt_res));
    arg.arg1 = (int)arg1;
    arg.arg2 = (char*)arg2;

    memset((char*)&clnt_res, 0, sizeof(clnt_res));
    if (clnt_call(clnt, lista_Monitor_substring_begin_,
                  (xdrproc_t)xdr_lista_monitor_argument, (caddr_t)&arg,
                  (xdrproc_t)xdr_void, (caddr_t)&clnt_res,
                  TIMEOUT) != RPC_SUCCESS)
    {
        return (NULL);
    }
    return ((void*)&clnt_res);
}

char**
lista_monitor_substring_get__1(int idClient, CLIENT* clnt)
{
    lista_monitor_get_argument arg;
    static char*               clnt_res;

    memset((char*)&clnt_res, 0, sizeof(clnt_res));
    arg.arg1 = (int)idClient;

    if (clnt_call(clnt, lista_Monitor_substring_get_,
                  (xdrproc_t)xdr_lista_monitor_get_argument, (caddr_t)&arg,
                  (xdrproc_t)xdr_wrapstring, (caddr_t)&clnt_res,
                  TIMEOUT) != RPC_SUCCESS)
    {
        return (NULL);
    }
    return (&clnt_res);
}

bool_t*
lista_monitor_substring_end__1(int idClient, CLIENT* clnt)
{
    lista_monitor_end_argument arg;
    static bool_t              clnt_res;

    memset((char*)&clnt_res, 0, sizeof(clnt_res));
    arg.arg1 = (int)idClient;

    if (clnt_call(clnt, lista_Monitor_substring_end_,
                  (xdrproc_t)xdr_lista_monitor_end_argument, (caddr_t)&arg,
                  (xdrproc_t)xdr_bool, (caddr_t)&clnt_res,
                  TIMEOUT) != RPC_SUCCESS)
    {
        return (NULL);
    }
    return (&clnt_res);
}

void* killserver_1(CLIENT* clnt)
{
    static char clnt_res;

    memset((char*)&clnt_res, 0, sizeof(clnt_res));
    if (clnt_call(clnt, killServer, (xdrproc_t)xdr_void, (caddr_t)NULL,
                  (xdrproc_t)xdr_void, (caddr_t)&clnt_res,
                  TIMEOUT) != RPC_SUCCESS)
    {
        return (NULL);
    }
    return ((void*)&clnt_res);
}

char**
getmodulename_1(int arg1, CLIENT* clnt)
{
    static char* clnt_res;

    memset((char*)&clnt_res, 0, sizeof(clnt_res));
    if (clnt_call(clnt, getmodulename,
                  (xdrproc_t)xdr_int, (caddr_t)&arg1,
                  (xdrproc_t)xdr_wrapstring, (caddr_t)&clnt_res,
                  TIMEOUT) != RPC_SUCCESS)
    {
        return (NULL);
    }
    return (&clnt_res);
}

char**
getmodulenameaux_1(int arg1, CLIENT* clnt)
{
    static char* clnt_res;

    memset((char*)&clnt_res, 0, sizeof(clnt_res));
    if (clnt_call(clnt, getmodulenameaux,
                  (xdrproc_t)xdr_int, (caddr_t)&arg1,
                  (xdrproc_t)xdr_wrapstring, (caddr_t)&clnt_res,
                  TIMEOUT) != RPC_SUCCESS)
    {
        return (NULL);
    }
    return (&clnt_res);
}

void* inittiempoejecutivo_1(CLIENT* clnt)
{
    static char clnt_res;

    memset((char*)&clnt_res, 0, sizeof(clnt_res));
    if (clnt_call(clnt, initTiempoEjecutivo, (xdrproc_t)xdr_void, (caddr_t)NULL,
                  (xdrproc_t)xdr_void, (caddr_t)&clnt_res,
                  TIMEOUT) != RPC_SUCCESS)
    {
        return (NULL);
    }
    return ((void*)&clnt_res);
}

void* inittiempomodulos_1(CLIENT* clnt)
{
    static char clnt_res;

    memset((char*)&clnt_res, 0, sizeof(clnt_res));
    if (clnt_call(clnt, initTiempoModulos, (xdrproc_t)xdr_void, (caddr_t)NULL,
                  (xdrproc_t)xdr_void, (caddr_t)&clnt_res,
                  TIMEOUT) != RPC_SUCCESS)
    {
        return (NULL);
    }
    return ((void*)&clnt_res);
}

void* monitor_close_1(int idClient, CLIENT* clnt)
{
    monitor_close_argument arg;
    static bool_t          clnt_res;

    memset((char*)&clnt_res, 0, sizeof(clnt_res));
    arg.arg1 = (int)idClient;

    if (clnt_call(clnt, lista_Monitor_substring_end_,
                  (xdrproc_t)xdr_monitor_close_argument, (caddr_t)&arg,
                  (xdrproc_t)xdr_void, (caddr_t)&clnt_res,
                  TIMEOUT) != RPC_SUCCESS)
    {
        return (NULL);
    }
    return (&clnt_res);
}

#ifndef _RS_MYSQL_H
#define _RS_MYSQL_H 1
/*  $Id$
 *
 * Copyright (C) 1999 The Omega Project for Statistical Computing.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifdef _cplusplus
extern  "C" {
#endif

#include <mysql.h>
#include <mysql_com.h>
#include "getopt.h"             /* NOTE: this comes from mysql/include */
#include <string.h>

#include "RS-DBI.h"

#define RS_MYSQL_MAX_CON 100    /* typically we alloc a max of 16 */

/* MySQL connection parameters struct, allocating and freeing 
 * methods. See mysql_real_connect() for details on the params 
 * themselves.
 */
typedef struct st_sdbi_conParams {
  char *host;
  char *dbname;
  char *user;
  char *passwd;
  char *unix_socket;
  unsigned int  port; 
  unsigned int  client_flags;
} RS_MySQL_conParams;

RS_MySQL_conParams *RS_MySQL_allocConParams(void);
void                RS_MySQL_freeConParams(RS_MySQL_conParams *conParams);

/* The following functions are the S/R entry into the C implementation
 * (i.e., these are the only ones visible from R/S) we use the prefix
 * "RS_MySQL" in function names to denote this.
 * These functions are  built on top of the underlying RS_DBI manager, 
 * connection, and resultsets structures and functions (see RS-DBI.h).
 * 
 * Note: A handle is just an R/S object (see RS-DBI.h for details), i.e.,
 *       Mgr_Handle, Con_Handle, Res_Handle, Db_Handle are s_object.
 */
  
/* dbManager */
Mgr_Handle *RS_MySQL_init(s_object *config_params, s_object *reload);
s_object   *RS_MySQL_close(Mgr_Handle *mgrHandle); 

/* dbConnection */
Con_Handle *RS_MySQL_newConnection(Mgr_Handle *mgrHandle, 
				   s_object *con_params,
				   s_object *MySQLgroups);
Con_Handle *RS_MySQL_cloneConnection(Con_Handle *conHandle);
s_object   *RS_MySQL_closeConnection(Con_Handle *conHandle);
s_object   *RS_MySQL_getException(Con_Handle *conHandle);    /* err No, Msg */

/* dbResultSet */
Res_Handle *RS_MySQL_exec(Con_Handle *conHandle, s_object *statement);
s_object   *RS_MySQL_fetch(Res_Handle *rsHandle, s_object *max_rec);
s_object   *RS_MySQL_closeResultSet(Res_Handle *rsHandle); 

s_object   *RS_MySQL_validHandle(Db_Handle *handle);      /* boolean */

RS_DBI_fields *RS_MySQL_createDataMappings(Res_Handle *resHandle);
/* the following funs return named lists with meta-data for 
 * the manager, connections, and  result sets, respectively.
 */
s_object *RS_MySQL_managerInfo(Mgr_Handle *mgrHandle);
s_object *RS_MySQL_connectionInfo(Con_Handle *conHandle);
s_object *RS_MySQL_resultSetInfo(Res_Handle *rsHandle);

/* the following type names are from "mysql_com.h" */
struct {
   char *typeName;
   int  typeId;
} RS_MySQL_fieldTypes[] = {
    { "FIELD_TYPE_DECIMAL",	FIELD_TYPE_DECIMAL	},
    { "FIELD_TYPE_TINY",	FIELD_TYPE_TINY		},
    { "FIELD_TYPE_SHORT",	FIELD_TYPE_SHORT	},
    { "FIELD_TYPE_LONG",	FIELD_TYPE_LONG		},
    { "FIELD_TYPE_FLOAT",	FIELD_TYPE_FLOAT	},
    { "FIELD_TYPE_DOUBLE",	FIELD_TYPE_DOUBLE	},
    { "FIELD_TYPE_NULL",	FIELD_TYPE_NULL		},
    { "FIELD_TYPE_TIMESTAMP",   FIELD_TYPE_TIMESTAMP	},
    { "FIELD_TYPE_LONGLONG",	FIELD_TYPE_LONGLONG	},
    { "FIELD_TYPE_INT24",	FIELD_TYPE_INT24	},
    { "FIELD_TYPE_DATE",	FIELD_TYPE_DATE		},
    { "FIELD_TYPE_TIME",	FIELD_TYPE_TIME		},
    { "FIELD_TYPE_DATETIME",	FIELD_TYPE_DATETIME	},
    { "FIELD_TYPE_YEAR",	FIELD_TYPE_YEAR		},
    { "FIELD_TYPE_NEWDATE",	FIELD_TYPE_NEWDATE	},
    { "FIELD_TYPE_ENUM",	FIELD_TYPE_ENUM		},
    { "FIELD_TYPE_SET",		FIELD_TYPE_SET		},
    { "FIELD_TYPE_TINY_BLOB",	FIELD_TYPE_TINY_BLOB	},
    { "FIELD_TYPE_MEDIUM_BLOB",	FIELD_TYPE_MEDIUM_BLOB	},
    { "FIELD_TYPE_LONG_BLOB",	FIELD_TYPE_LONG_BLOB	},
    { "FIELD_TYPE_BLOB",	FIELD_TYPE_BLOB		},
    { "FIELD_TYPE_VAR_STRING",	FIELD_TYPE_VAR_STRING	},
    { "FIELD_TYPE_STRING",	FIELD_TYPE_STRING	},
    { (char *) 0,			-1		}
};

s_object *RS_MySQL_getFieldTypeNames(s_object *typeIds);
char     *RS_MySQL_getFieldTypeName(Sint typeId);

#ifdef _cplusplus
}
#endif

#endif   /* _RS_MYSQL_H */

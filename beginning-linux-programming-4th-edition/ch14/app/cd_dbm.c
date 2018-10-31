/*
   This file provides the functions for accessing the CD database.
 */

#define _XOPEN_SOURCE

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <ndbm.h>
/* The above include may need to be changed to gdbm-ndbm.h on some Linux distributions */

#include "cd_data.h"

#define CDC_FILE_BASE "cdc_data"
#define CDT_FILE_BASE "cdt_data"
#define CDC_FILE_DIR  "cdc_data.dir"
#define CDC_FILE_PAG  "cdc_data.pag"
#define CDT_FILE_DIR "cdt_data.dir"
#define CDT_FILE_PAG "cdt_data.pag"

/* Some file scope variables for accessing the database */
static DBM *cdc_dbm_ptr = NULL;
static DBM *cdt_dbm_ptr = NULL;


/* This function initializes access to the database. If the parameter
   new_database is true, then a new database is started.
 */
int database_initialize(const int new_database)
{
    int open_mode = O_RDWR;

    /* If any existing database is open then close it */
    if (cdc_dbm_ptr) dbm_close(cdc_dbm_ptr);
    if (cdt_dbm_ptr) dbm_close(cdt_dbm_ptr);

    if (new_database) {
	/* delete the old files */
	(void) unlink(CDC_FILE_PAG);
	(void) unlink(CDC_FILE_DIR);
	(void) unlink(CDT_FILE_PAG);
	(void) unlink(CDT_FILE_DIR);

	open_mode = O_CREAT | O_RDWR;
    }
    /* Open some new files, creating them if required */
    cdc_dbm_ptr = dbm_open(CDC_FILE_BASE, open_mode, 0644);
    cdt_dbm_ptr = dbm_open(CDT_FILE_BASE, open_mode, 0644);
    if (!cdc_dbm_ptr || !cdt_dbm_ptr) {
	fprintf(stderr, "Unable to create database\n");
	cdc_dbm_ptr = cdt_dbm_ptr = NULL;
	return (0);
    }
    return (1);

} /* database_initialize */

void database_close(void)
{
    if (cdc_dbm_ptr) dbm_close(cdc_dbm_ptr);
    if (cdt_dbm_ptr) dbm_close(cdt_dbm_ptr);

    cdc_dbm_ptr = cdt_dbm_ptr = NULL;

} /* database_close */

/*
   This function retrieves a single catalog entry, when passed a pointer
   pointing to catalog text string. If the entry is not found then the
   returned data has an empty catalog field. */
cdc_entry get_cdc_entry(const char *cd_catalog_ptr)
{
    cdc_entry entry_to_return;
    char entry_to_find[CAT_CAT_LEN + 1];
    datum local_data_datum;
    datum local_key_datum;

    memset(&entry_to_return, '\0', sizeof(entry_to_return));

    /* check database initialized and parameters valid */
    if (!cdc_dbm_ptr || !cdt_dbm_ptr) return (entry_to_return);
    if (!cd_catalog_ptr) return (entry_to_return);
    if (strlen(cd_catalog_ptr) >= CAT_CAT_LEN) return (entry_to_return);

    /* ensure the search key contains only the valid string and nulls */
    memset(&entry_to_find, '\0', sizeof(entry_to_find));
    strcpy(entry_to_find, cd_catalog_ptr);

    local_key_datum.dptr = (void *) entry_to_find;
    local_key_datum.dsize = sizeof(entry_to_find);

    memset(&local_data_datum, '\0', sizeof(local_data_datum));
    local_data_datum = dbm_fetch(cdc_dbm_ptr, local_key_datum);
    if (local_data_datum.dptr) {
	memcpy(&entry_to_return, (char *)local_data_datum.dptr, local_data_datum.dsize);
    }
    return (entry_to_return);
} /* get_cdc_entry */


/*
   This function retrieves a single track entry, when passed a pointer
   pointing to a catalog string and a track number. If the entry is not
   found then the returned data has an empty catalog field. */
cdt_entry get_cdt_entry(const char *cd_catalog_ptr, const int track_no)
{
    cdt_entry entry_to_return;
    char entry_to_find[CAT_CAT_LEN + 10];
    datum local_data_datum;
    datum local_key_datum;

    memset(&entry_to_return, '\0', sizeof(entry_to_return));

    /* check database initialized and parameters valid */
    if (!cdc_dbm_ptr || !cdt_dbm_ptr) return (entry_to_return);
    if (!cd_catalog_ptr) return (entry_to_return);
    if (strlen(cd_catalog_ptr) >= CAT_CAT_LEN) return (entry_to_return);

    /* setup the search key, which is a composite key of catalog entry
       and track number */
    memset(&entry_to_find, '\0', sizeof(entry_to_find));
    sprintf(entry_to_find, "%s %d", cd_catalog_ptr, track_no);

    local_key_datum.dptr = (void *) entry_to_find;
    local_key_datum.dsize = sizeof(entry_to_find);

    memset(&local_data_datum, '\0', sizeof(local_data_datum));
    local_data_datum = dbm_fetch(cdt_dbm_ptr, local_key_datum);
    if (local_data_datum.dptr) {
	memcpy(&entry_to_return, (char *) local_data_datum.dptr, local_data_datum.dsize);
    }
    return (entry_to_return);
} /* get_cdt_entry */


/* This function adds a new catalog entry. */
int add_cdc_entry(const cdc_entry entry_to_add)
{
    char key_to_add[CAT_CAT_LEN + 1];
    datum local_data_datum;
    datum local_key_datum;
    int result;

    /* check database initialized and parameters valid */
    if (!cdc_dbm_ptr || !cdt_dbm_ptr) return (0);
    if (strlen(entry_to_add.catalog) >= CAT_CAT_LEN) return (0);

    /* ensure the search key contains only the valid string and nulls */
    memset(&key_to_add, '\0', sizeof(key_to_add));
    strcpy(key_to_add, entry_to_add.catalog);

    local_key_datum.dptr = (void *) key_to_add;
    local_key_datum.dsize = sizeof(key_to_add);
    local_data_datum.dptr = (void *) &entry_to_add;
    local_data_datum.dsize = sizeof(entry_to_add);

    result = dbm_store(cdc_dbm_ptr, local_key_datum, local_data_datum, DBM_REPLACE);

    /* dbm_store() uses 0 for success */
    if (result == 0) return (1);
    return (0);

} /* add_cdc_entry */


/* This function adds a new catalog entry. The access key is the
   catalog string and track number acting as a composite key */
int add_cdt_entry(const cdt_entry entry_to_add)
{
    char key_to_add[CAT_CAT_LEN + 10];
    datum local_data_datum;
    datum local_key_datum;
    int result;

    /* check database initialized and parameters valid */
    if (!cdc_dbm_ptr || !cdt_dbm_ptr) return (0);
    if (strlen(entry_to_add.catalog) >= CAT_CAT_LEN) return (0);

    /* ensure the search key contains only the valid string and nulls */
    memset(&key_to_add, '\0', sizeof(key_to_add));
    sprintf(key_to_add, "%s %d", entry_to_add.catalog, entry_to_add.track_no);

    local_key_datum.dptr = (void *) key_to_add;
    local_key_datum.dsize = sizeof(key_to_add);
    local_data_datum.dptr = (void *) &entry_to_add;
    local_data_datum.dsize = sizeof(entry_to_add);

    result = dbm_store(cdt_dbm_ptr, local_key_datum, local_data_datum, DBM_REPLACE);

    /* dbm_store() uses 0 for success and -ve numbers for errors */
    if (result == 0)
	return (1);
    return (0);
} /* add_cdt_entry */


int del_cdc_entry(const char *cd_catalog_ptr) {
    char key_to_del[CAT_CAT_LEN + 1];
    datum local_key_datum;
    int result;

    /* check database initialized and parameters valid */
    if (!cdc_dbm_ptr || !cdt_dbm_ptr) return (0);
    if (strlen(cd_catalog_ptr) >= CAT_CAT_LEN) return (0);

    /* ensure the search key contains only the valid string and nulls */
    memset(&key_to_del, '\0', sizeof(key_to_del));
    strcpy(key_to_del, cd_catalog_ptr);

    local_key_datum.dptr = (void *) key_to_del;
    local_key_datum.dsize = sizeof(key_to_del);

    result = dbm_delete(cdc_dbm_ptr, local_key_datum);

    /* dbm_delete() uses 0 for success */
    if (result == 0) return (1);
    return (0);

} /* del_cdc_entry */

int del_cdt_entry(const char *cd_catalog_ptr, const int track_no) {
    char key_to_del[CAT_CAT_LEN + 10];
    datum local_key_datum;
    int result;

    /* check database initialized and parameters valid */
    if (!cdc_dbm_ptr || !cdt_dbm_ptr) return (0);
    if (strlen(cd_catalog_ptr) >= CAT_CAT_LEN) return (0);

    /* ensure the search key contains only the valid string and nulls */
    memset(&key_to_del, '\0', sizeof(key_to_del));
    sprintf(key_to_del, "%s %d", cd_catalog_ptr, track_no);

    local_key_datum.dptr = (void *) key_to_del;
    local_key_datum.dsize = sizeof(key_to_del);

    result = dbm_delete(cdt_dbm_ptr, local_key_datum);

    /* dbm_delete() uses 0 for success */
    if (result == 0) return (1);
    return (0);

} /* del_cdt_entry */


/* This function searches for a catalog entry, where the catalog
   text contains the provided search text. If the search text points
   to a null character then all entries are considered to match */
cdc_entry search_cdc_entry(const char *cd_catalog_ptr, int *first_call_ptr)
{
    static int local_first_call = 1;
    cdc_entry entry_to_return;
    datum local_data_datum;
    static datum local_key_datum;	/* notice this must be static */

    memset(&entry_to_return, '\0', sizeof(entry_to_return));

    /* check database initialized and parameters valid */
    if (!cdc_dbm_ptr || !cdt_dbm_ptr) return (entry_to_return);
    if (!cd_catalog_ptr || !first_call_ptr) return (entry_to_return);
    if (strlen(cd_catalog_ptr) >= CAT_CAT_LEN) return (entry_to_return);

    /* protect against never passing *first_call_ptr true */
    if (local_first_call) {
	local_first_call = 0;
	*first_call_ptr = 1;
    }
    if (*first_call_ptr) {
	*first_call_ptr = 0;
	local_key_datum = dbm_firstkey(cdc_dbm_ptr);
    } else {
	local_key_datum = dbm_nextkey(cdc_dbm_ptr);
    }

    do {
	if (local_key_datum.dptr != NULL) {
	    /* an entry was found */
	    local_data_datum = dbm_fetch(cdc_dbm_ptr, local_key_datum);
	    if (local_data_datum.dptr) {
		memcpy(&entry_to_return, (char *) local_data_datum.dptr, local_data_datum.dsize);

		/* check if search string occures in the entry */
		if (!strstr(entry_to_return.catalog, cd_catalog_ptr)) {
		    memset(&entry_to_return, '\0', sizeof(entry_to_return));
		    local_key_datum = dbm_nextkey(cdc_dbm_ptr);
		}
	    }
	}
    } while (local_key_datum.dptr &&
	     local_data_datum.dptr &&
	     (entry_to_return.catalog[0] == '\0'));
    /* Finished finding entries, either there are no more or one matched */

    return (entry_to_return);
} /* search_cdc_entry */
















#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

#include "database.h"


void error(const char* msg){

        if (errno)
                perror(msg);
        else
                printf("ERROR: %s \n", msg);
        exit(1);
}

void database_load(con_t *con){

        int rc = fread(con->db, sizeof(struct database), 1, con->file);

        if (rc != 1) error("could not load database.");
}


void row_print(const struct row *row){

        if (row == NULL)
                error("could not print row.");
        printf("\t%d\t%s\t%s\t%s\n", row->id, row->name, row->email, row->password);
}

con_t *database_open(const char* filename, char mode){

        con_t *con = malloc(sizeof(con_t));
        if (!con) error("could not allocate; out of memory.");

        con->db = malloc(sizeof(struct database));
        if (!con->db) error("could not allocate; out of memory.");

        if (mode == 'c')
                con->file = fopen(filename, "w");
        else{
                con->file = fopen(filename, "r+");

                if(con->file) database_load(con);
        }

        if(!con->file) error("failed to open the file");

        return con;
}

void database_close(con_t *con){

        if(con){
                if (con->file) fclose(con->file);
                if (con->db) free(con->db);
                free(con);
        }
}

void database_write(con_t *con){

        rewind(con->file);

        int rc = fwrite(con->db, sizeof(struct database), 1,con->file);
        if (rc != 1) error("failed to write the file.");

        rc = fflush(con->file);
        if (rc == -1) error("could not flush database.");

}

void database_create(con_t *con){

        int i = 0;
        for(i = 0; i < MAX_ROWS; i++){

                struct row row ={.id = i, .set = 0};
                con->db->rows[i] = row;
        }
}

void row_set(con_t *con, int id, const char *name, const char *email, const char *password){

        struct row *row = &con->db->rows[id];

        if (row->set == 1) error("could not set the id, already set.");

        row->set = 1;

        char *res = strncpy(row->name, name, MAX_DATA_LEN);
        if (!res) error("could not copy the name");

        res = strncpy(row->email, email, MAX_DATA_LEN);
        if (!res) error("could not copy the email");

        res = strncpy(row->password, password, MAX_DATA_LEN);
        if (!res) error("could not copy the password");
}

void row_get(con_t *con, int id){

        struct row *row = &con->db->rows[id];

        if (row->set == 0) error("row is not set");

        row_print(row);

}

void row_delete(con_t *con, int id){

        struct row row = {.id = id, .set = 0};

        con->db->rows[id] = row;

}

void database_list(con_t  *con){

        struct database *db = con->db;
        for(int i = 0; i < MAX_ROWS; i++){

                struct row *cur = &db->rows[i];
                if (cur->set == 1) row_print(cur);
        }
}


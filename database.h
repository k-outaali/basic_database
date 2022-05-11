#ifndef DATABASE_H
#define DATABASE_H

#define MAX_DATA_LEN 50
#define MAX_ROWS 100

struct row{

        int id;
        int set;
        char name[MAX_DATA_LEN];
        char email[MAX_DATA_LEN];
        char password[MAX_DATA_LEN];
};

struct database{

        struct row rows[MAX_ROWS];
};

typedef struct {

        FILE *file;
        struct database *db;
} con_t;


void error(const char* msg);


void database_load(con_t *con);


void row_print(const struct row *row);


con_t *database_open(const char *filename, char mode);


void database_close(con_t  *con);


void database_write(con_t *con);


void database_create(con_t *con);


void row_set(con_t *con, int id, const char *name, const char *email, const char *password);


void row_get(con_t *con, int id);


void row_delete(con_t *con, int id);


void database_list(con_t *con);



#endif

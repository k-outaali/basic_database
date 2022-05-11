#include <stdio>h>
#include <stdlib.h>

#include "database.h"



int main(int argc, char* argv[]){

        if (argc < 3) error("usage; ./database <dbfile> <action> [action params]. ");

        char* filename = argv[1];
        char action = argv[2][0];
        int id = 0;

        struct connection *con = database_open(filename, action);

        if (argc > 3 ){
                id = atoi(argv[3]);
                if (id >= MAX_ROWS) error("out of bound, id sould be less than MAX_ROWS");
        }

        switch(action){

                case 'c':
                        database_create(con);
                        database_write(con);
                        break;

                case 'g':
                        if (argc != 4) error("invalid arguments; ./database <dbfile> g <id>.");
                        row_get(con, id);
                        break;

                case 's':
                        if (argc != 7) error("invalid arguments; ./database <dbfile> s <id> <name> <email> <password>.");
                        row_set(con, id, argv[4], argv[5], argv[6]);
                        break;

                case 'd':
                        if (argc != 4) error("invalid arguments; ./database <dbfile> d <id>.");
                        row_delete(con, id);
                        break;

                case 'l':
                        if (argc != 3) error("invalid arguments; ./database <dbfile> l.");
                        database_list(con);
                        break;

                default: error("incorrect action, c=create, g=get, s=set, d=delete, l=list");
        }

        database_close(con);
        return 0 ;
}

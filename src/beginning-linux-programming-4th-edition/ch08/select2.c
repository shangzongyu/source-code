#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

MYSQL my_connection;
MYSQL_RES *res_ptr;
MYSQL_ROW sqlrow;

int main(int argc, char *argv[]) {
   int res;

   mysql_init(&my_connection);  
   if (mysql_real_connect(&my_connection, "localhost", "rick", 
                                              "secret", "foo", 0, NULL, 0)) {
   printf("Connection success\n");
   
   res = mysql_query(&my_connection, "SELECT childno, fname, age FROM children WHERE age > 5");

   if (res) {
      printf("SELECT error: %s\n", mysql_error(&my_connection));
   } else {
      res_ptr = mysql_use_result(&my_connection);
      if (res_ptr) {
         while ((sqlrow = mysql_fetch_row(res_ptr))) {
            printf("Fetched data...\n");
         }
         if (mysql_errno(&my_connection)) {
            printf("Retrive error: %s\n", mysql_error(&my_connection));
         }
         mysql_free_result(res_ptr);
      }
   }
   mysql_close(&my_connection);

   } else {
      fprintf(stderr, "Connection failed\n");
      if (mysql_errno(&my_connection)) {
         fprintf(stderr, "Connection error %d: %s\n",
                  mysql_errno(&my_connection), mysql_error(&my_connection));
      }
   }

   return EXIT_SUCCESS;
}


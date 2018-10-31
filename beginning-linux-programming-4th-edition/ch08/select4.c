#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

MYSQL my_connection;
MYSQL_RES *res_ptr;
MYSQL_ROW sqlrow;

void display_header();
void display_row();


int main(int argc, char *argv[]) {
   int res;
   int first_row = 1; /* Used to ensure we display the row header exactly once when data is successfully retrieved */


   mysql_init(&my_connection);  
   if (mysql_real_connect(&my_connection, "localhost", "rick", 
                                                "secret", "foo", 0, NULL, 0)) {
      printf("Connection success\n");
   
      res = mysql_query(&my_connection, "SELECT childno, fname, age FROM children WHERE age > 5");

      if (res) {
         fprintf(stderr, "SELECT error: %s\n", mysql_error(&my_connection));
      } else {
         res_ptr = mysql_use_result(&my_connection);
         if (res_ptr) {
            while ((sqlrow = mysql_fetch_row(res_ptr))) {
               if (first_row) {
                  display_header();
                  first_row = 0;
               }
               display_row();
            }
            if (mysql_errno(&my_connection)) {
             fprintf(stderr, "Retrive error: %s\n",
                                mysql_error(&my_connection));
            }
            mysql_free_result(res_ptr);
         }
      }
      mysql_close(&my_connection);
   } else {
      fprintf(stderr, "Connection failed\n");
      if (mysql_errno(&my_connection)) {
        fprintf(stderr, "Connection error %d: %s\n",
                                mysql_errno(&my_connection),
                                mysql_error(&my_connection));
        }
      }
   
   return EXIT_SUCCESS;
}


void display_header() {
   MYSQL_FIELD *field_ptr;

   printf("Column details:\n");
 
   while ((field_ptr = mysql_fetch_field(res_ptr)) != NULL) {
      printf("\t Name: %s\n", field_ptr->name);
      printf("\t Type: ");
      if (IS_NUM(field_ptr->type)) {
         printf("Numeric field\n");
      } else {
         switch(field_ptr->type) {
            case FIELD_TYPE_VAR_STRING:
               printf("VARCHAR\n");
            break;
            case FIELD_TYPE_LONG: 
               printf("LONG\n");
            break;
            default:
              printf("Type is %d, check in mysql_com.h\n", field_ptr->type);
         } /* switch */
      } /* else */

      printf("\t Max width %ld\n", field_ptr->length); /* Note on versions of MySQL before 4.0 the format should be %d, rather than %ld */
      if (field_ptr->flags & AUTO_INCREMENT_FLAG) 
         printf("\t Auto increments\n");
      printf("\n");
   } /* while */
}


void display_row() {
   unsigned int field_count;

   field_count = 0;
   while (field_count < mysql_field_count(&my_connection)) {
      if (sqlrow[field_count]) printf("%s ", sqlrow[field_count]);
      else printf("NULL");
      field_count++;
   }
   printf("\n");
}


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "app_mysql.h"

int main() {
  struct current_cd_st cd;
  struct cd_search_st cd_res;
  struct current_tracks_st ct;
  int cd_id;
  int res, i;

  database_start("rick", "secret");

  res = add_cd("Mahler", "Symphony No 1", "4596102", &cd_id);  
  printf("Result of adding a cd was %d, cd_id is %d\n", res, cd_id);

  memset(&ct, 0, sizeof(ct));
  ct.cd_id = cd_id;
  strcpy(ct.track[0], "Lansam Schleppend");
  strcpy(ct.track[1], "Kraftig bewegt");
  strcpy(ct.track[2], "Feierlich und gemesen");
  strcpy(ct.track[3], "Sturmisch bewegt");
  add_tracks(&ct);

  res = find_cds("Symphony", &cd_res);
  printf("Found %d cds, first has ID %d\n", res, cd_res.cd_id[0]);

  res = get_cd(cd_res.cd_id[0], &cd);
  printf("get_cd returned %d\n", res);

  memset(&ct, 0, sizeof(ct));
  res = get_cd_tracks(cd_res.cd_id[0], &ct);
  printf("get_cd_tracks returned %d\n", res);  
  printf("Title: %s\n", cd.title);
  i = 0;
  while (i < res) {
    printf("\ttrack %d is %s\n", i, ct.track[i]);
    i++;
  }

  res = delete_cd(cd_res.cd_id[0]);
  printf("Delete_cd returned %d\n", res);


  database_end();

  return EXIT_SUCCESS;

}

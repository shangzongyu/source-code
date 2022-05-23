<?php
# uniq_name.php: show how to use PID to create table name

#@ _GENERATE_NAME_WITH_PID_
$tbl_name = "tmp_tbl_" . posix_getpid ();
#@ _GENERATE_NAME_WITH_PID_
print ("$tbl_name\n");
?>

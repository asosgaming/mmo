<?php

$mydata = json_decode(file_get_contents('php://input'));

	echo json_encode(array('status'=>'OK', 'address'=>'174.37.205.202'));


?>

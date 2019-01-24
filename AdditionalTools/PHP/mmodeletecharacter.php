<?php

include_once "mmoconnection.php"; 

$mydata = json_decode(file_get_contents('php://input'));

$userid = $mydata ->userid;
$key = $mydata ->sessionkey;

$charid = $mydata ->charid;

$stmt = $conn->prepare("SELECT session_key FROM active_logins WHERE user_id = ?");
$stmt->bind_param("i", $userid);

$stmt->execute();
$stmt->bind_result($row_sessionkey);

if (!$stmt->fetch()) echo  json_encode(array('status'=>'You are not logged in.'));

else {
	
	if ($key == $row_sessionkey)  //  if the user owns the current active session
	{ 
		$stmt->close();
				
		$stmt = $conn->prepare("SELECT id FROM characters WHERE id = ? ");

		$stmt->bind_param("i", $charid); 

		$stmt->execute();
		
		if (!$stmt->fetch()) echo  json_encode(array('status'=>'Character not found'));
		else 
		{
			$stmt->close();
				
			$stmt = $conn->prepare("DELETE FROM characters WHERE id = ? "); //delete the character
		
			$stmt->bind_param("i", $charid); 
		
			$stmt->execute();
			
			echo json_encode(array('status'=>'OK'));
		}
	} 
}

?>

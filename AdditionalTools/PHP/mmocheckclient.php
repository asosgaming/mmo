<?php
include_once "mmoconnection.php"; 

$mydata = json_decode(file_get_contents('php://input'));

$userid = $mydata ->userid;
$key = $mydata ->sessionkey;
$charid = $mydata ->charid;

$stmt = $conn->prepare("SELECT session_key FROM active_logins WHERE user_id = ? ");

$stmt->bind_param("i", $userid); 

$stmt->execute();

$stmt->bind_result($row_sessionkey);

if (!$stmt->fetch()) echo  json_encode(array('status'=>'You are not logged in.'));

else {
 
	if ($key == $row_sessionkey)  { //  if the user owns the current active session
	
		$stmt->close();
					
		$stmt = $conn->prepare("SELECT * FROM characters WHERE id = ? AND user_id = ? "); //check that the character with this id belongs to this player
		
		$stmt->bind_param("ii", $charid, $userid); 
		
		$stmt->execute();

		if (!$stmt->fetch()) echo  json_encode(array('status'=>'Character not found'));
		else echo json_encode(array('status'=>'OK'));

	} 
	
}

?>

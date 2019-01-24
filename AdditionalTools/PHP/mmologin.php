<?php

include_once "mmoconnection.php"; 

$mydata = json_decode(file_get_contents('php://input'));

$login = $mydata ->login;
$pass = $mydata ->password;

$stmt = $conn->prepare("SELECT id, password FROM users WHERE username = ? ");

$stmt->bind_param("s", $login);  // "s" means the database expects a string

$stmt->execute();

$stmt->bind_result($row_id, $row_hash);

if ($stmt->fetch()) {

	if ( password_verify($pass, $row_hash) )  { 
		
		$userid = $row_id;
		
		$stmt->close();
		
		$sql ="DELETE FROM active_logins WHERE user_id =".$userid; //no need to use a prepared statement here
		$old_sessions = $conn->query($sql);	
						
		$randomstring = substr(md5(rand()), 7, 10);
		$sql ="INSERT INTO `active_logins` VALUES ('{$userid }', '{$randomstring}', NULL )"; //no need to use a prepared statement here
		$generatekey = $conn->query($sql);
		
		echo json_encode(array('status'=>"OK", 'sessionkey'=>$randomstring, 'userid'=> $userid));

	} 
	else echo  json_encode(array('status'=>'Login information is incorrect. Check your username and password.')); //wrong password
	
}
else echo  json_encode(array('status'=>'Login information is incorrect. Check your username and password.')); //no such username


?>

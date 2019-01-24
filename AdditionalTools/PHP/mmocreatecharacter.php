<?php

include_once "mmoconnection.php"; 

$mydata = json_decode(file_get_contents('php://input'));

$userid = $mydata ->userid;
$key = $mydata ->sessionkey;

$charname = $mydata ->name;
//$gender = $mydata ->gender;
$classid = $mydata ->classid;

$stmt = $conn->prepare("SELECT session_key FROM active_logins WHERE user_id = ? ");

$stmt->bind_param("i", $userid);  // "i" means the database expects an integer

$stmt->execute();

$stmt->bind_result($row_sessionkey);

if (!$stmt->fetch()) echo  json_encode(array('status'=>'You are not logged in.'));

else {
	 
	if ($key == $row_sessionkey)  { //  if the user owns the current active session
	
		$stmt->close();
		
		$stmt = $conn->prepare("SELECT name FROM characters WHERE name = ? ");
		
		$stmt->bind_param("s", $charname); 

		$stmt->execute();
		
		if ($stmt->fetch())  echo  json_encode(array('status'=>'This name is unavailable'));
		
		else {  //create this new character

			$stmt->close();
			
			 //id, userid, name. class, gender, health, mana, level, experience, clan, posx, posy, posz, rotation  (yaw), 5 equipment pieces, 4 hotbar slots:
		
			$stmt = $conn->prepare("INSERT INTO characters VALUES (NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, '', '', '', '', '', 'Ability\'/Game/MMO/Abilities/Heal.Heal\'', 'Ability\'/Game/MMO/Abilities/FireBlast.FireBlast\'', '', '' ) ");
			
			if ($stmt == false)
					printf("Errormessage: %s\n", $conn->error);
			
			$health = 300; $mana = 150; $level = 1; $exp = 0; 
			$posx = 6890; $posy = -3370; $posz = 20692; $yaw = 0; 
			$gender = 0; $clan = 0;
					
			$stmt->bind_param("sssssssssssss", $userid, $charname, $classid, $gender, $health, $mana, $level, $exp, $clan, $posx, $posy, $posz, $yaw ); 
		
			$stmt->execute();
			
			$error = htmlspecialchars($stmt->error);
					
			$stmt->close();
					
			
			echo json_encode(array('status'=>"OK" ));
		
		}

	} 
	
	else echo  json_encode(array('status'=>'You are not logged in.'));
}

?>

<?php

include_once "mmoconnection.php"; 

$mydata = json_decode(file_get_contents('php://input'));

$clan_name = $mydata ->clan_name; 
$character_name = $mydata ->character_name;

if ($stmt = $conn->prepare("SELECT name FROM clans WHERE name = ? ")) //check if the clan name is not taken
{
	$stmt->bind_param("s", $clan_name);  // "s" means the database expects a string

	$stmt->execute();

	if ($stmt->fetch())  echo  json_encode(array('status'=>'This clan name is unavailable'));	
	
	else {  //find the leader character

		$stmt = $conn->prepare("SELECT id, clan FROM characters WHERE name = ? ");
		$stmt->bind_param("s", $character_name);
		$stmt->bind_result($charid, $charclan);
		
		$stmt->execute();
			
		if (!$stmt->fetch())  echo  json_encode(array('status'=>'character not found'));	
		else 
		{	
			$stmt->close();
	
			if ($charclan != 0)  echo  json_encode(array('status'=>'character already has a clan'));	
					
			else // create this new clan
				{	
				
				$stmt = $conn->prepare("INSERT INTO clans VALUES (NULL, ?, ?)");
				if (!$stmt)  error_log ($conn->error);
			
				$stmt->bind_param("si", $clan_name, $charid);
				
				$stmt->execute();
				
				$stmt->close();
				
				$stmt = $conn->prepare("UPDATE characters SET clan = ? WHERE id = ?");
				
				$last_id = $conn->insert_id;
				$stmt->bind_param("ii", $last_id, $charid);
				
				$stmt->execute();
				
				echo json_encode(array('status'=>'OK' ));
				}
			
		}		

	}
}
?>

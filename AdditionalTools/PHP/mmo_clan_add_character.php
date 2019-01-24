<?php

include_once "mmoconnection.php"; 

$mydata = json_decode(file_get_contents('php://input'));

$character_name = $mydata ->character_name;
$clan_id = $mydata ->clan_id;
//find the character:

$stmt = $conn->prepare("SELECT clan FROM characters WHERE name = ? ");
$stmt->bind_param("s", $character_name);
$stmt->bind_result($found_clan_id);
$stmt->execute();
			
if (!$stmt->fetch())  echo  json_encode(array('status'=>'character not found'));	
		else 
		{	
			$stmt->close();
	
			if ($found_clan_id != 0)  echo  json_encode(array('status'=>'character is already in a clan'));	
					
			else // add the character to the clan
			{			
				$stmt = $conn->prepare("UPDATE characters SET clan = ? WHERE name = ? ");
				$stmt->bind_param("is", $clan_id, $character_name);
				$stmt->execute();

				echo json_encode(array('status'=>'OK' ));				
			}			
		}	

?>

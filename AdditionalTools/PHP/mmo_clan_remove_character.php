<?php

include_once "mmoconnection.php"; 

$mydata = json_decode(file_get_contents('php://input'));

$character_id = $mydata ->character_id;

 //find the character:

$stmt = $conn->prepare("SELECT clan FROM characters WHERE id = ? ");
$stmt->bind_param("i", $character_id);
$stmt->bind_result($clanid);
$stmt->execute();
			
if (!$stmt->fetch())  echo  json_encode(array('status'=>'character not found'));	
		else 
		{	
			$stmt->close();
	
			if ($clanid == 0)  echo  json_encode(array('status'=>'character is not in a clan'));	
					
			else // remove the character from clan
			{			
				$stmt = $conn->prepare("UPDATE characters SET clan = 0 WHERE id = ? ");
				$stmt->bind_param("i", $character_id);
				$stmt->execute();

				echo json_encode(array('status'=>'OK' ));				
			}			
		}	

?>

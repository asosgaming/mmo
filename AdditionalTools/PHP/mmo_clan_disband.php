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
					
			else // check if the character is the clan leader
			{					
				$stmt = $conn->prepare("SELECT leader_id FROM clans WHERE id = ? ");
				$stmt->bind_param("i", $clanid);
				$stmt->bind_result($leader_id);
				$stmt->execute();
				$stmt->fetch();
				
				if ($leader_id != $character_id) echo  json_encode(array('status'=>'character is not the clan leader'));	
				else
				{	//delete the clan:
					$stmt->close();
					
					$stmt = $conn->prepare("DELETE FROM clans WHERE id = ? ");
					$stmt->bind_param("i", $clanid);
					$stmt->execute();
					$stmt->close();
					
					//update all members of the deleted clan:
					$stmt = $conn->prepare("UPDATE characters SET clan = '0' WHERE clan = ?");
					$stmt->bind_param("i", $clanid);
					$stmt->execute();
					
					echo json_encode(array('status'=>'OK' ));
				}
				
			}
			
		}	

?>

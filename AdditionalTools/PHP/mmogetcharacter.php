<?php
include_once "mmoconnection.php"; 

$mydata = json_decode(file_get_contents('php://input'));
$charid = $mydata ->charid;
$userid = $mydata ->userid;

$stmt = $conn->prepare("SELECT name, health, mana, level, experience, clan, posx, posy, posz, rotation_yaw, 
equip_head, equip_chest, equip_hands, equip_legs, equip_feet, hotbar0, hotbar1, hotbar2, hotbar3 FROM characters WHERE id = ? ");

$stmt->bind_param("i", $charid);  // "i" means the database expects an integer

$stmt->execute();

$stmt->bind_result($row_name, $row_health, $row_mana, $row_level, $row_experience, $row_clan_id, $row_posx, $row_posy, $row_posz, $row_rotation_yaw, 
$row_equip_head, $row_equip_chest, $row_equip_hands, $row_equip_legs, $row_equip_feet, $row_hotbar0, $row_hotbar1, $row_hotbar2, $row_hotbar3);

  // output data of each row
if($stmt->fetch()) {

	$stmt->close();

	//store character id in session table:
	$stmt = $conn->prepare("UPDATE active_logins SET character_id = ? WHERE user_id = ? ");

	$stmt->bind_param("ii", $charid, $userid);

	$stmt->execute();

	$stmt->close();

	$inventory = array();

	$stmt = $conn->prepare("SELECT slot, item, amount FROM inventory WHERE character_id = ? ");

	$stmt->bind_param("i", $charid);

	$stmt->execute();

	$stmt->bind_result($row_slot, $row_item, $row_amount );

	while($stmt->fetch()) {

		$inventory[] = array('slot'=>$row_slot, 'item'=> $row_item, 'amount'=> $row_amount);

	}
	
	$stmt->close();
	
	$row_clan_name = '';
	if ($row_clan_id >0) //clan
	{
		$stmt = $conn->prepare("SELECT name FROM clans WHERE id = ? ");

		
		$stmt->bind_param("i", $row_clan_id);
		$stmt->bind_result($row_clan_name);
		$stmt->execute();
		$stmt->fetch();
		$stmt->close();
	}
	
	//quests:
	$quests = array();

	$stmt = $conn->prepare("SELECT quest, completed, task1, task2, task3, task4 FROM quests WHERE character_id = ? ");

	$stmt->bind_param("i", $charid);

	$stmt->execute();
	
	$stmt->bind_result($row_quest, $row_completed, $row_task1, $row_task2, $row_task3, $row_task4 );

	while($stmt->fetch()) {
		
		$quests[] = array('quest'=>$row_quest, 'completed'=> $row_completed ? 1 : 0, 'task1'=> $row_task1, 'task2'=> $row_task2, 'task3'=> $row_task3, 'task4'=> $row_task4);

	}		
	
		echo  json_encode(array('status'=>"OK", 'name'=> $row_name, 'inventory'=> $inventory, 'quests'=>$quests, 'health'=> $row_health, 
		'mana'=> $row_mana, 'level'=> $row_level, 'experience'=> $row_experience, 'clan'=> $row_clan_name,
		'posx'=> $row_posx, 'posy'=> $row_posy, 'posz'=>$row_posz, 'rotation_yaw'=> $row_rotation_yaw,
		'equip_head'=> $row_equip_head, 'equip_chest'=> $row_equip_chest, 'equip_hands'=> $row_equip_hands,
		'equip_legs'=> $row_equip_legs, 'equip_feet'=> $row_equip_feet,
		'hotbar0'=>$row_hotbar0, 'hotbar1'=>$row_hotbar1, 'hotbar2'=>$row_hotbar2, 'hotbar3'=>$row_hotbar3	));		
}

else echo  json_encode(array('status'=>'Character id '.$charid.' not found '));

?>
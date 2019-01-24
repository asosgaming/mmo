<?php

include_once "mmoconnection.php"; 

$mydata = json_decode(file_get_contents('php://input'));

$charid = $mydata ->charid;

$inventory = $mydata ->inventory;
$quests = $mydata ->quests;

$health = $mydata ->health;
$mana = $mydata ->mana;

$experience = $mydata ->experience;
$level = $mydata ->level;

$posx = $mydata ->posx;
$posy = $mydata ->posy;
$posz = $mydata ->posz;

$yaw = $mydata ->yaw;

$equip_head = $mydata ->equip_head;
$equip_chest = $mydata ->equip_chest;
$equip_hands = $mydata ->equip_hands;
$equip_legs = $mydata ->equip_legs;
$equip_feet = $mydata ->equip_feet;

$hotbar0 = $mydata ->hotbar0;
$hotbar1 = $mydata ->hotbar1;
$hotbar2 = $mydata ->hotbar2;
$hotbar3 = $mydata ->hotbar3;

$stmt = $conn->prepare("UPDATE characters SET health = ?, mana = ?, experience = ?, level = ?, posx = ?, posy = ?, posz = ?, 
	rotation_yaw = ?, equip_head = ?, equip_chest = ?, equip_hands = ?,  equip_legs = ?, equip_feet = ?, hotbar0 = ?, hotbar1 = ?, hotbar2 = ?, hotbar3 = ? WHERE id = ? ");

$stmt->bind_param("iisssssssssssssssi", $health, $mana, $experience, $level, $posx, 
	$posy, $posz, $yaw, $equip_head, $equip_chest, $equip_hands, $equip_legs, $equip_feet,
	$hotbar0, $hotbar1, $hotbar2, $hotbar3, $charid );  // "s" means the database expects a string

$stmt->execute();
	
$stmt->close();

$stmt = $conn->prepare("DELETE FROM inventory WHERE character_id = ? ");

$stmt->bind_param("i", $charid);
	
$stmt->execute();
	
$stmt->close();

$stmt = $conn->prepare("DELETE FROM quests WHERE character_id = ? ");

$stmt->bind_param("i", $charid);
	
$stmt->execute();
	
$stmt->close();

foreach ($inventory as &$entry) {

	$amount = $entry->amount;
	$slot = $entry->slot;
	$item = $entry->item;

	$stmt = $conn->prepare("INSERT INTO inventory VALUES (NULL, ?, ?, ?, ? )");

	$stmt->bind_param("iisi", $charid, $slot, $item, $amount);

	$stmt->execute();
		
	$stmt->close();
}

foreach ($quests as &$entry) {
	//error_log("found quest:".$entry->quest, 0);
	//error_log("task1:".$entry->task1, 0);
	
	$quest = $entry->quest;
	$completed = $entry->completed;
			
	if ($completed)
	{
		$stmt = $conn->prepare("INSERT INTO quests VALUES (NULL, ?, ?, ?, 0, 0, 0, 0 )");
		$stmt->bind_param("isi", $charid, $quest, $completed);
	}
	else 
	{
		$stmt = $conn->prepare("INSERT INTO quests VALUES (NULL, ?, ?, ?, ?, ?, ?, ? )");
		$stmt->bind_param("isiiiii", $charid, $quest, $completed, $entry->task1, $entry->task2, $entry->task3, $entry->task4);
	}

	$stmt->execute();
		
	$stmt->close();

}

echo json_encode(array('status'=>'OK'  ));

?>

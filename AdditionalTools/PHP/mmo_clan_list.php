<?php

include_once "mmoconnection.php"; 

$mydata = json_decode(file_get_contents('php://input'));

$output = array();

$stmt = $conn->prepare("SELECT clans.id, clans.name, clans.leader_id, characters.name, characters.id FROM clans INNER JOIN characters ON clans.id = characters.clan WHERE characters.clan != 0");
$stmt->bind_result($row_clan_id, $row_clan_name, $row_leader_id, $row_character_name, $row_character_id);
$stmt->execute();

while ($stmt->fetch())
{
	$is_leader = ($row_leader_id == $row_character_id); 
	$output[] = array('character_id'=>$row_character_id, 'character_name'=>$row_character_name, 'clan_id'=> $row_clan_id, 'clan_name'=> $row_clan_name, 'is_leader'=> $is_leader);
}


echo json_encode(array('status'=>'OK', 'clans'=>$output));

?>

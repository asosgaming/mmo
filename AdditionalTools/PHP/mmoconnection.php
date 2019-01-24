<?php
	
$servername = 'localhost'; 
$username = 'secondhand_mmo';  
$password = '111111';
$dbname = 'secondhand_mmo';

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    echo(json_encode(array('status'=>"Connection failed: " . $conn->connect_error)));
	die;
} 



?>

<?php
$host="localhost";
$user="root";
$pass= "";
$db="dht_db";
$conn=mysqli_connect($host,$user,$pass,$db);
if($conn){
    echo"connected successfull\n";
}
else{
    echo"connection failed";
}
$data=json_decode(file_get_contents("php://input"),true);
if($data){
    $distance=$data['intera'];
    $insert=mysqli_query($conn,"insert into dht_data(temperature,humidity)VALUES('$temperature','$humidity')");
    if($insert){
        echo"data insert successfull";
    }
    else{
        echo "failed to fecth data";
    }}
    else{
        echo"\n no data received from esp 32";
    }
    
?>
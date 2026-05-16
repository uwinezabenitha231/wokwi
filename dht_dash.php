<?php
include('insert_dht.php');
$sel = mysqli_query($conn, "SELECT * FROM dht_data order by timestamp desc limit 10");
if(mysqli_num_rows($sel)>0){
?>
<html>
<meta http-equi="refresh" content="3">
<table border="1">
<tr>
    <th>id</th>
    <th>temperature</th>
    <th>humidity</th>
    <th>Timestamp</th>
</tr>
</html>
<?php 
while($rows = mysqli_fetch_assoc($sel)){
?>
<tr>
    <td><?php echo $rows['id']; ?></td>
    <td><?php echo $rows['temperature']; ?></td>
    <td><?php echo $rows['humidity']; ?></td>
    <td><?php echo $rows['timestamp']; ?></td>
</tr>
<?php
}
?>
</table>
<?php
}else{
    echo "No data available in database";
}
?>

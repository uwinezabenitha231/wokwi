<?php
include('insert.php');
$sel = mysqli_query($conn, "SELECT * FROM Motion_data");
if(mysqli_num_rows($sel) > 0){
?>
<html>
<meta http-equi="refresh" content="3">
<table border="1">
<tr>
    <th>Id</th>
    <th>Motion_detected</th>
    <th>Timestamp</th>
</tr>
</html>
<?php
while($rows = mysqli_fetch_assoc($sel)){
?>
<tr>
    <td><?php echo $rows['Id']; ?></td>
    <td><?php echo $rows['Motion_detected']; ?></td>
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
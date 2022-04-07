<?php
class projectTanaman{
 public $link='';
 function __construct($SoilMoist, $SoilTemp, $WindHumU, $WindTempU, $WindHumS, $WindTempS){
  $this->connect();
  $this->storeInDB($SoilMoist, $SoilTemp, $WindHumU, $WindTempU, $WindHumS, $WindTempS);
 }
 
 function connect(){
  $this->link = mysqli_connect('localhost','root','') or die('Cannot connect to the DB');
  mysqli_select_db($this->link,'mikrokontroler') or die('Cannot select the DB');
 }
 
 function storeInDB($SoilMoist, $SoilTemp, $WindHumU, $WindTempU, $WindHumS, $WindTempS){
  $query = "insert into projectTanaman set SoilMoist='".$SoilMoist."', SoilTemp='".$SoilTemp."', WindHumU='".$WindHumU."', WindTempU='".$WindTempU."', WindHumS='".$WindHumS."', WindTempS='".$WindTempS."'";
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }
 
}

if($_GET['SoilMoist'] != '' and  $_GET['SoilTemp'] != '' and  $_GET['WindHumU'] != '' and  $_GET['WindTempU'] != '' and  $_GET['WindHumS'] != '' and  $_GET['WindTempS'] != ''){
 $projectTanaman=new projectTanaman($_GET['SoilMoist'],$_GET['SoilTemp'],$_GET['WindHumU'],$_GET['WindTempU'],$_GET['WindHumS'],$_GET['WindTempS']);
}
?>

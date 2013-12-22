<?php

include ("PHPSonos.inc.php"); 

$sonos = new PHPSonos("192.168.1.144");
$sonos->SetVolume(75);
$sonos->ClearQueue(); 

if (strpos($_GET["file"], '.') !== FALSE)
  $sonos->AddToQueue("http://192.168.1.142/holiday/" . $_GET["file"]);
else
  $sonos->AddToQueue("http://192.168.1.142/holiday/" . $_GET["file"] . ".mp3");

$sonos->SetQueue("x-rincon-queue:RINCON_"."000E58215CE4"."01400#0");
$sonos->Play();

echo "done"

?>

<?php
	if ($_GET['size'] == '500b' )
		readfile('content/file_500b.html');
	else if ($_GET['size'] == '20kb' )
		readfile('content/file_20kb.html');
?>

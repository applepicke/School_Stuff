
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
     "DTD/xhtml1-transitional.dtd"> 
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset={$pageCharset}" />
	<meta http-equiv="Content-language" content="en" />
	<meta http-equiv="expires" content="-1" />
	<meta http-equiv="pragma" content="no-cache" />
	<meta name="author" content="Dave Watson" />
	<meta name="copyright" content="GNU" />
	<meta name="robots" content="NOFOLLOW" />
	<base href="{$basehref}"/>
	<title>Algonquin College</title>
</head> 
<body>
<font face="verdana,arial" size=-1>
<center>
<img src="logoAlgonquinTopBanner.png" alt="Algonquin" /> 
<?php
   if (! isset ($_POST["username"])) {
?>
     <table cellpadding=2 cellspacing=0 border=0>
       <tr><td bgcolor="DarkGreen"><table cellpadding=0 cellspacing=0 border=0 width=100%><tr><td bgcolor="DarkGreen" align=center style="padding:2;padding-bottom:4"><b><font size=-1 color="white">Login Required: Please enter your email address and password</font></th></tr>
       <tr><td bgcolor="white" style="padding:5"><br>
       <form method="post" action="login.php" name=login>

       <center><table>
         <tr>
      <td><font face="verdana,arial" size=-1>Login:</td>
      <td><input type="text" name="username" value=""></td>
      </tr>
      <tr>
        <td><font face="verdana,arial" size=-1>Password:</td>
        <td><input type="password" name="password"></td>
      </tr>
      <tr>
        <td><font face="verdana,arial" size=-1>&nbsp;</td>
        <td><font face="verdana,arial" size=-1><input type="submit" value="Login"></td>
      </tr>
      <tr>
        <td><a href="newuser.php">New User</a></td>
        <td><a href="forgot.php">Forgot Password</a></td>
     </tr>
     <tr>
        <td colspan=2><font face="verdana,arial" size=-1>&nbsp;</td>
     </tr>
</table></center>
</form>
</td></tr></table>></td></tr></table>

<?php
   } else {
     $userName=$_POST["username"];
     $passWord=$_POST["password"];
     //     echo "<p>this is a test";
     $filePath=dirname($_SERVER["SCRIPT_FILENAME"]);
     $filename=$filePath."/data.txt";
     if (!file_exists($filename)) {
       echo "<p>Error: No Users file created - go to <a href=\"newuser.php\">New User</a> Page to add a User";
       exit;
     } else {
       $userData=file($filename);
       foreach ($userData as $line ) {
	 $userName_loc=stripos ($line,$userName);
	 if ($userName_loc !== false) {
	   //	   echo "<p>Verify Username: $userName exists: $line";
	   $user = explode(" ",$line);
	   $pass = explode (":",$user[1]);
	   //	   print_r ($user);
	   //	   print_r ($pass);
	   if (trim($pass[1]) != $passWord) {
	     echo "<p>Error: Invalid Password - try again";
	     echo "<p><a href=\"login.php\">Login</a>";
	     exit;
	   } else {
	     echo "<h1>Login Successful</h1>";
	     exit;
	   }
	 }
       }
       echo "<p>Error: Missing Username:  $userName go to <a href=\"newuser.php\">New User</a> Page to add a User";
     }
   }
?>


</body>


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
   function validate_user ($userName){
   $atLoc = strpos ($userName,"@"); 
   if ($atLoc <= 0) {
     echo "<p>Error: not a valid email address atLoc: $atLoc";
     exit;
   }
   $user = explode ("@",$userName);
   $dotLoc = strpos ($user[1],"."); 
   //   print_r ($user);
   if ($dotLoc <= 0) {
     echo "<p>Error: not a valid email address dotLoc: $dotLoc";
     exit;
   }
 }
   function validate_pass ($passWord){
     if ($passWord == "") {
       echo "<p>Error: no valid password given";
       exit;
     }
     $spLoc = strpos ($passWord," "); 
     //     print_r ($user);
     if ($spLoc !== false) {
       echo "<p>Error: not a valid password space's not allowed in password Password: $passWord spLoc: $spLoc";
       exit;
   }    
 }
   if (!isset($_POST["username"])) {
?>
     <table cellpadding=2 cellspacing=0 border=0>
<tr><td bgcolor="DarkGreen"><table cellpadding=0 cellspacing=0 border=0 width=100%><tr><td bgcolor="DarkGreen" align=center style="padding:2;padding-bottom:4"><b><font size=-1 color="white">New User: Please complete all fields</font></th></tr>
       <tr><td bgcolor="white" style="padding:5"><br>
       <form method="post" action="newuser.php" name=newuser>

       <center><table>
         <tr>
      <td><font face="verdana,arial" size=-1>email:</td>
      <td><input type="text" name="username" value=""></td>
      </tr>
      <tr>
        <td><font face="verdana,arial" size=-1>password:</td>
        <td><input type="password" name="password"></td>
      </tr>
      <tr>
        <td><font face="verdana,arial" size=-1>&nbsp;</td>
        <td><font face="verdana,arial" size=-1><input type="submit" value="Submit"></td>
      </tr>
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
     if (validate_user ($userName)) {
       echo "Error: Invalid Username: $userName";
       exit;
     }
     if (validate_pass ($passWord)){
       echo "Error: Invalid username: $userName";
       exit;
     }
     //     echo "<pre>\n";
     //     print_r($_SERVER);
     //     echo "</pre>\n";
     $filePath=dirname($_SERVER["SCRIPT_FILENAME"]);
     $filename=$filePath."/data.txt";
     if (!file_exists($filename)) {
	 echo "<p>New User Created: ".$userName;
	 $fh=fopen($filename,"w");
	 if($fh==false)
            die("<p>unable to create file:".$filename);
	 fprintf ($fh, "username:%s password:%s\n",$userName,$passWord);
	 fclose ($fh);
       } else {
	 $userData=file($filename);
	 foreach ($userData as $line ) {
	   $userName_loc=stripos ($line,$userName);
	   if ($userName_loc !== false) {
	     echo "<p>Error: Username: $userName already exists";
	     exit;
	   } else {
	     echo "<p>Adding User: ".$userName;
	     $fh=fopen($filename,"a");
	     if($fh==false)
	       die("<p>unable to create file:".$filename);
	     fprintf ($fh, "username:%s password:%s\n",$userName,$passWord);
	     fclose ($fh);

 
	   }
	 }
       }
     echo "<p><a href=\"login.php\">Login</a>";
   }
?>


</body>

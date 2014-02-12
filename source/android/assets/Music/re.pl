$i = 0;
foreach $f (glob("*.mp3")) { 
print '"';
print $f;
print '"';
print ",\/\/$i";
$i++; 
print "\n";
#$nf =~ s/(\d+)$/sprintf("%03d",$1)/e; 

}

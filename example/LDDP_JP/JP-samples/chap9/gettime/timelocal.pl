
if ($#ARGV == -1) {
	$tick = time();
} else {
	$tick = $ARGV[0];
}

@tm =  gmtime($tick);
printf "%lu -> %d/%d/%d %02d:%02d:%02d\n", 
	$tick,
	$tm[5]+1900, $tm[4]+1, $tm[3], $tm[2],$tm[1], $tm[0];


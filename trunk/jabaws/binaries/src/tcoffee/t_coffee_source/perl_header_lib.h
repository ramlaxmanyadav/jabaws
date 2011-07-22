char *PerlScriptName[]={"rec_sum.pl","count.pl","p\
rocess_list.pl","make_license.pl","CCsed.script","\
msa2bootstrap.pl","t_coffee_dpa","t_coffee_dpa2","\
tc_generic_method.pl","generic_method.tc_method","\
clustalw_method.tc_method","extract_from_pdb","ins\
tall.pl","clean_cache.pl","nature_protocol.pl","mo\
cca","dalilite.pl","wublast.pl","blastpgp.pl","ncb\
iblast_lwp.pl","wublast_lwp.pl","RNAplfold2tclib.p\
l","fasta_seq2RNAplfold_templatefile.pl","fasta_se\
q2hmmtop_fasta.pl","fasta_seq2consan_aln.pl","clus\
talw_aln2fasta_aln.pl","msf_aln2fasta_aln.pl","bla\
st_aln2fasta_aln.pl","blast_xml2fasta_aln.pl","fas\
ta_aln2fasta_aln_unique_name.pl","newick2name_list\
.pl","excel2fasta.pl","any_file2unix_file.pl","End\
List"};char *PerlScriptFile[]={"use File::Copy;\nu\
se Env qw(HOST);\nuse Env qw(HOME);\nuse Env qw(US\
ER);\n$x_field=0;\n$y_field=1;\n$interval=0;\n$fil\
e=\"stdin\";\n$print_avg=1;\n$print_sd=0;\n$print_\
sum=0;\n$print_n=0;\nforeach $value ( @ARGV)\n    \
{\n	if ($value ne $ARGV[$np]) \n	    {\n	    ;\n	 \
   }\n	elsif($value eq \"-print_all\")\n	    {\n	 \
   $print_sd=$print_avg=$print_n=$print_sum=1;\n	 \
   $np++;\n	    }\n	elsif($value eq \"-print_sum\"\
)\n	    {\n	    $print_sum=1;\n	    $print_avg=0;\\
n	    $np++;\n	    }\n	elsif($value eq \"-print_n\\
")\n	    {\n	    $print_n=1;\n	    $print_avg=0;\n\
	    $np++;\n	    }\n	elsif($value eq \"-print_avg\
\")\n	    {\n	    $print_avg=1;\n	    $print_avg=0\
;\n	    $np++;\n	    }\n	elsif($value eq \"-sd\")\\
n	    {\n	    $print_sd=1;\n	    $print_avg=0;\n	 \
   $np++;\n	    }\n	elsif($value eq \"-h\")\n	    \
{\n	    $header=1;\n	    $np++;\n	    }\n	elsif ($\
value eq \"-i\")\n	    {\n	    $interval= $ARGV[++\
$np];\n	    $np++;\n    	    }\n	elsif ($value eq \
\"-r\")\n	    {\n	    $min= $ARGV[++$np];\n	    $m\
ax= $ARGV[++$np];\n	    $np++;\n    	    }\n	\n	el\
sif ($value eq \"-x\")\n	    {\n	    $x_field= $AR\
GV[++$np]-1;\n	    $np++;\n    	    }\n	elsif ($va\
lue eq \"-y\")\n	    {\n	      \n	    while ($ARGV\
[$np+1] && !($ARGV[$np+1]=~/\\-/))\n	      {\n		$y\
_field[$nyf++]=$ARGV[++$np]-1;\n		$y_field_set=1;\\
n	      }\n\n	    $np++;\n    	    }\n	elsif ($val\
ue eq \"-file\")\n	    {\n	    $file= $ARGV[++$np]\
;\n	    $file_set=1;\n	    $np++;\n    	    }     \
  \n	elsif ( $value eq \"h\" ||  $value eq \"-h\" \
|| $value eq \"-H\" || $value eq \"-help\" || $val\
ue eq \"help\")\n	  {\n	    print STDOUT \"data_an\
alyse: Analyse and discretization of data\\n\";\n	\
    print STDOUT \"       -file:    <file containi\
ng the data to analyze>,.<def=STDIN>\\n\";\n	    p\
rint STDOUT \"       -x: <field containing the X>,\
...............<Def=0>\\n\";\n	    print STDOUT \"\
       -y: <field containing the Y>,..............\
.<Def=1>\\n\";\n	    print STDOUT \"       -i:<Int\
erval size on the X>,...............<Def=0>\\n\";\\
n	    print STDOUT \"       -i:<0:only one interva\
l>\\n\";\n	    print STDOUT \"       -r:<Range of \
the X>\\n\";\n	    print STDOUT \"       -sd: prin\
t standard deviation on the Y\";\n	    print STDOU\
T \"       -h  : print column header \\n\";\n	    \
exit (0);\n	  }\n	elsif ($value=~/-/)\n	  {\n	    \
print \"$value is not a valid FLAG[FATAL]\\n\";\n	\
    exit (0);\n	   } \n	elsif ($list eq \"\") \n	 \
   {\n	    $file=$ARGV[$np];\n	    $np++;\n	    }\\
n	\n	\n      }\n\n\n\n\n\nif ($file eq \"stdin\")\\
n	{\n	$remove_file=1;\n	$file=\"tmp$$\";\n	open (F\
, \">$file\");\n	while (<STDIN>)\n		{\n		print F $\
_;\n		}\n	close (F);\n	 \n	;}\n\n\nopen(F,$file);\\
n\nif ($interval)\n  {\n    $interval_size=($max-$\
min)/$interval;\n  }\nwhile (<F>)\n  {\n    $line=\
$_;\n    if (!/\\S/){next;}\n    @list=($line=~/(\\
\S+)/g);\n    \n    if ($interval==0){$bin=0;}\n  \
  else{$bin=int (($list[$x_field]-$min)/($interval\
_size));}\n\n    \n    if ($bin && $bin==$interval\
){$bin--;}\n    for ( $a=0; $a<$nyf; $a++)\n      \
{\n	$sum{$a}{$bin}+=$list[$y_field[$a]];\n	$sum2{$\
a}{$bin}+=$list[$y_field[$a]]*$list[$y_field[$a]];\
\n	$n{$a}{$bin}++;\n      }\n  }\n\nif (!$interval\
){$interval=1;}\nfor ( $a=0; $a<$interval; $a++)\n\
  {\n    printf ( \"%3d %3d \", $interval_size*$a,\
 $interval_size*($a+1));\n    for ( $b=0; $b<$nyf;\
 $b++)	\n      {\n	$i=$interval*$a;\n	if ( $n{$b}{\
$a}==0)\n	  {\n	    $avg=0;\n	    $sd=0;\n	  }\n	e\
lse\n	  {\n	    $avg=$sum{$b}{$a}/$n{$b}{$a};\n	  \
  $sd=sqrt($sum2{$b}{$a}*$n{$b}{$a}-$sum{$b}{$a}*$\
sum{$b}{$a})/($n{$b}{$a}*$n{$b}{$a});\n	  }\n	if (\
$print_n) {printf \"%10.4f \", $n{$b}{$a};}\n	if (\
$print_sum){printf \"%10.4f \", $sum{$b}{$a};}\n	i\
f ($print_avg){printf \"%10.4f \", $avg}\n	if ($pr\
int_sd) {printf \"%10.4f \", $sd;}\n      }\n    p\
rintf (\"\\n\");\n  }\n\n\nif ( $remove_file){unli\
nk $file;}\n","use File::Copy;\nuse Env qw(HOST);\\
nuse Env qw(HOME);\nuse Env qw(USER);\n\nforeach $\
v (@ARGV){$cl.=$v;}\n\n\nif ( $cl=~/-k(\\d+)/){$k=\
$1;}\nelse {$k=1;}\nif ( $cl=~/-w(\\d+)/){$w=$1;}\\
nelse {$w=-1;}\nif ( $cl=~/-p(\\d+)/){$p=$1;}\nels\
e {$p=-1;}\n\nwhile (<STDIN>)\n  {\n    @l=($_=~/(\
\\S+)/g);\n    $v=$l[$k-1];\n    if ( !$h{$v}){@ll\
=($v, @ll);}\n    \n    if ( $w==-1)\n      {$h{$v\
}++;}\n    else\n      {$h{$v}+=$l[$w-1];}\n\n    \
if ($p!=-1){$print{$v}=$l[$p-1];}\n\n  }\nforeach \
$v (@ll)\n  {\n    print \"$v $print{$v} $h{$v}\\n\
\";\n  }\n","\nuse Env qw(HOST);\nuse Env qw(HOME)\
;\nuse Env qw(USER);\n$random_tag=int (rand 10000)\
+1;\n$unique_prefix=\"$$.$HOST.$random_tag\";\n$qu\
eue=\"distillery.and.mid\";\n$monitor=0;\n$stderr_\
file=\"/dev/null\";\n$stdio_file=\"/dev/null\";\n$\
log_file=\"/dev/null\";\n$pause_time=0;\n$max_sub_\
jobs=60;\n$min_sub_jobs=30;\n$output_all=0;\n$var=\
'\\$';\n\nforeach $value ( @ARGV)\n    {\n	if ($va\
lue ne $ARGV[$np]) \n	    {\n	    ;\n	    }\n	elsi\
f ($value eq \"-max_sub_jobs\")\n	    {\n	    $max\
_sub_jobs= $ARGV[++$np];\n	    $np++;\n    	    }	\
\n	elsif ($value eq \"-min_sub_jobs\" )\n	    {\n	\
    $min_sub_jobs= $ARGV[++$np];\n	    $np++;\n   \
 	    }\n	elsif ($value eq \"-para\")\n	    {\n	  \
  $para=1;\n	    $monitor=1;\n	    $np++;\n    	  \
  }\n	elsif ($value eq \"-monitor\") \n	    {\n	  \
  $monitor=1;\n	    $np++;\n	    }\n	elsif ($value\
 eq \"-no_monitor\") \n	    {\n	    $monitor=0;\n	\
    $np++;\n	    }\n	elsif ($value eq \"-queue\")\\
n	    {\n	    $queue=$ARGV[++$np];\n	    $np++;\n	\
    }	\n	elsif ($value eq \"-stderr_file\")\n	    \
{\n	    $stderr_file=$ARGV[++$np];\n	    $np++;\n	\
    }\n	elsif ($value eq \"-stdio_file\")\n	    {\\
n	    $stdio_file=$ARGV[++$np];\n	    $np++;\n	   \
 }\n	elsif ($value eq \"-output_all\")\n	    {\n	 \
   $output_all=1;\n	    $np++;\n	    }\n	elsif ($v\
alue eq \"-pause\") \n	    {\n	    $pause_time=$AR\
GV[++$np];\n	    $np++;\n	    }\n	elsif ($value eq\
 \"-log\")\n	      {\n	       $log=1;\n	       \n	\
       if ($ARGV[$np+1]=~/\\-\\S+/) \n	          {\
\n		  $log_file=\"stderr\";\n	          }\n	      \
 else \n	          {\n		  $log_file=$ARGV[++$np]; \
\n		  ++$np;\n		 \n	          }\n	      }\n	elsif \
( $value eq \"-com\")\n	    {\n		\n		if (!$ARGV[$n\
p+1]=~/^\\'/) { $com=$ARGV[++$np];}\n		else {$com=\
$ARGV[++$np];}\n\n	     $np++;\n	    }\n	elsif ( $\
value eq \"-check\")\n	  {\n	    \n	    if (!$ARGV\
[$np+1]=~/^\\'/) { $check=$ARGV[++$np];}\n	    els\
e {$check=$ARGV[++$np];}\n	    $np++;\n	  }\n	elsi\
f ($com eq \"\") \n	    {\n	    $com_set=1;\n	    \
$com=$ARGV[$np];\n	    \n	    $np++;\n	    }\n	els\
if ($list eq \"\") \n	    {\n	    $list_set=1;\n	 \
   $list=$ARGV[$np];\n	    $np++;\n	    }\n	elsif \
( $var_set eq \"\")\n	    {\n	    $var_set=1;\n	  \
  $var=$ARGV[$np];\n	    $np++;\n	    }\n	}\n\n\n\\
n\nif ( $com eq \"\"){print \"You Need to Provide \
a Command [FATAL]\\n\";\n	      die;\n	     }\n\n\\
n\nif ($list_set==0) \n    {\n    $x= int (rand 10\
0000)+1;\n    $tmp_file_name=\"tmp_file_$x\";\n   \
 open ( TMP, \">$tmp_file_name\");\n    while (<ST\
DIN>)\n      {\n	print TMP $_;\n      }\n    close\
 (TMP);\n    open (F, $tmp_file_name);\n    }\nels\
e \n    {\n    open (F, $list);\n    }\n\nif ($par\
a==0) \n    {\n\n     @tc_list= <F>;\n     close (\
F); \n     \n     foreach $val(@tc_list) \n	    {\\
n	      \n	      \n	      \n	      $loc_com=$com;\\
n	      if ($check){$loc_check=$check;}\n	      \n\
	      @i_val=($val=~/([^\\s]+)/g);\n	      \n	   \
   if ( $#i_val==0)\n		{\n		  if ($check){$loc_che\
ck=~s/$var/$i_val[0]/g;}\n		  $loc_com=~s/$var/$i_\
val[0]/g;\n		}\n	      else\n		{\n		  for ($n=1; $\
n<=$#i_val+1;$n++ )\n		    {\n		      \n		      $s\
ub=\"$var$n\";\n		      \n		      $loc_com=~s/$sub\
/$i_val[$n-1]/g;\n		      if ($check){$loc_check=~\
s/$var/$i_val[0]/g;}\n		    }\n		}\n	      if ( $c\
heck && -e $loc_check)\n		{\n		  print STDERR \"sk\
ipping $loc_com...\\n\";\n		  }\n	      else\n		{\\
n		  system \"$loc_com\";\n		}\n	    }\n    exit;\\
n    }\n\nelsif ($para==1) \n    {\n    print STDE\
RR \"do parallel execution of: \\\"$com $list\\\"\\
\n\";\n    \n    if ($log==1) \n	{\n	if ($log_file\
 eq \"stdout\" || $log_file eq \"stderr\" ) \n		{\\
n		$log_file=\"\";\n	        }\n\n        else \n	\
	{\n		system \"echo LOG FILE> $log_file\";\n		\n	 \
       }\n	}\n    else	\n	{\n	open ( OUT, \">/dev/\
null\");\n	}\n	\n    \n    $id=0;\n    $n_sub=0;\n\
    while ($val=<F>) \n	    {	    	    \n	    $job\
_log[$id]=\"$HOME/tmp/$unique_prefix.$id.log_file\\
";\n	    \n	    $job=$unique_prefix.\"_$id\";\n	  \
  open (JOB, \">$job\");\n	    \n	    $loc_com=$co\
m;\n	    chop $val;\n\n	    $loc_com=~s/\\$/$val/g\
;\n	 \n	    print JOB \"#!/bin/csh\\n\";\n	    pri\
nt JOB \"#\\$ -cwd\\n\";\n	    print JOB \"#\\$ -N\
 $unique_prefix\\n\";\n	    if ($queue && !($queue\
 eq \" \")) {print JOB \"#\\$ -l $queue\\n\";}\n	 \
   print JOB \"#\\n\";	    \n            print JOB\
 \"$loc_com\\n\";\n	    print JOB \"echo FINISHED \
 >> $job_log[$id]\\n\";\n	    print JOB \"pwd\\n\"\
;\n	    \n	    close (JOB);\n	    if ( $output_all\
==1)\n		{\n		system \"qsub $job >  $unique_prefix\\
";		\n	        }\n	    else\n		{system \"qsub $job\
 -e $stderr_file -o $stdio_file >$unique_prefix\";\
	        \n	        } \n\n\n\n	    print STDERR \"\
$id: $output_all\\n\";\n	    $n_sub++;\n	    if ( \
$max_sub_jobs && $n_sub==$max_sub_jobs) \n		{\n		$\
n_sub=monitor_process($min_sub_jobs,@job_log); 		 \
\n		\n	        }	\n	   \n            unlink $uniqu\
e_prefix;\n	    sleep $pause_time;\n	    $id++;\n	\
    }\n\n    close (OUT);\n    close (F);\n\n    p\
rint STDERR \"Your $id Jobs Have Been Submited (NA\
ME=$unique_prefix)\\n\";\n    monitor_process (0, \
@job_log);\n    foreach $file(@job_log) {if (-e $f\
ile) {unlink($file);}}\n    \n    }\n\nsub monitor\
_process ( @job_list)\n    {\n    my (@job_list)=@\
_;\n    my $min_sub_jobs=shift (@job_list);\n    m\
y $n_sub_jobs;\n    my $finished;\n    my $n=0;\n\\
n    $n_sub_jobs=-1;\n    $finished=0;\n    print \
STDERR \"\\nMonitor Batch: [$min_sub_jobs]\";\n   \
    \n    while (!$finished && (($n_sub_jobs>$min_\
sub_jobs)|| $n_sub_jobs==-1) ) \n	{\n	$finished=1;\
\n	$n_sub_jobs=0;\n	$n=0;\n	foreach $file (@job_li\
st)\n	        {\n	\n		if (-e $file){;}\n		else \n	\
	    {\n		    $finished=0; $n_sub_jobs++;\n	      \
      }\n	        }\n	system \"sleep 1\";\n       \
 }\n    \n    return $n_sub_jobs;\n    }\n    \n  \
  \nif ($tmp_file_name){unlink($tmp_file_name);}\n\
","\n\nforeach ($np=0; $np<=$#ARGV; $np++)\n    {\\
n    $value=$ARGV[$np];\n\n    if ($value eq \"-fi\
le\")\n      {\n      $file= $ARGV[++$np];\n      \
}\n    elsif ($value eq \"-type\")\n      {\n     \
   $type= $ARGV[++$np];\n      }\n    elsif ($valu\
e eq \"-institute\")\n      {\n        $institute=\
 $ARGV[++$np];\n      }\n    elsif ($value eq \"-a\
uthor\")\n      {\n        $author= $ARGV[++$np];\\
n      }\n    elsif ($value eq \"-date\")\n      {\
\n        $date= $ARGV[++$np];\n      }\n     elsi\
f ($value eq \"-program\")\n      {\n        $prog\
ram= $ARGV[++$np];\n      }\n    elsif ($value eq \
\"-email\")\n      {\n        $email= $ARGV[++$np]\
;\n      }\n    else\n      {\n	print \"$value is \
an unkown argument[FATAL]\\n\";\n	exit (1);\n     \
 }\n  }\n\n\n\nopen F, $file || die;\nprint $INSTI\
TUTE;\nif ( $type eq \"c\"){print \"/*************\
*****************COPYRIGHT NOTICE*****************\
**************/\\n\";}\nif ( $type eq \"perl\"){pr\
int \"##############################COPYRIGHT NOTI\
CE##############################/\\n\";}\nif ( $ty\
pe eq \"txt\"){print \"---------------------------\
----COPYRIGHT NOTICE------------------------------\
/\\n\";}\n\n\nwhile (<F>)\n  {\n  s/\\$INSTITUTE/$\
institute/g;\n  s/\\$AUTHOR/$author/g;\n  s/\\$DAT\
E/$date/g;\n  s/\\$PROGRAM/$program/g;  \n  s/\\$E\
MAIL/$email/g;  \n  if ( $type eq \"txt\"){print $\
_;}\n  elsif ($type eq \"c\"){chop $_; print \"\\/\
*$_*\\/\\n\";}\n  elsif ($type eq \"perl\"){print \
\"\\#$_\";}\n}\nclose (F);\nif ( $type eq \"c\"){p\
rint \"/******************************COPYRIGHT NO\
TICE*******************************/\\n\";}\nif ( \
$type eq \"perl\"){print \"#######################\
#######COPYRIGHT NOTICE###########################\
###/\\n\";}\nif ( $type eq \"txt\"){print \"------\
-------------------------COPYRIGHT NOTICE---------\
---------------------/\\n\";}\n\n","\nwhile (<>)	\\
n	{\n	s/\\=cc/123456789/g;\n	s/\\bcc/\\$\\(CC\\)/g\
;\n	s/123456789/\\=cc/g;\n	print $_;\n	}\n\n","$ve\
rsion=\"1.00\";\n$rseed= int(rand(100000))+1;\n\n\\
nif ( $#ARGV==-1)\n  {\n    print \"msa2bootstrap \
-i <input_file> -input <seq|msa|matrix|tree> -n <N\
-Boostrap> -o <outtree> -tmode <nj|upgma|parsimony\
|ml> -dmode <kimura> -alignpg <t_coffee | muscle |\
 clustalw> -rtree <file> -stype <prot|cdna|dna> -r\
ecompute -system <cygwin|unix>\";\n    print \"\\n\
\\t-i: input file, can be sequneces, msa, matrix, \
trees, type is specified via -input\";\n    print \
\"\\n\\t-input: Type of input data\";\n    print \\
"\\n\\t\\tmsa: msa in fasta format\";\n    print \\
"\\n\\t\\tseq: compute an msa with -alignpg\";\n  \
  print \"\\n\\t\\tmatrix: phylipp distance matrix\
 fed directly to method -tmode [caveat: tmode=nj o\
r upgma]\";\n    print \"\\n\\t\\ttree: list of ne\
wick trees directly fed to consence in order to ge\
nerate a bootstraped tree\";\n    \n    print \"\\\
n\\t-n: number of bootstrap replicates\";\n    pri\
nt \"\\n\\t-o: name of the output tree. Files are \
not overwritten. Use -recompute to overwrite exist\
ing file\";\n    print \"\\n\\t-tmode: tree mode: \
nj|upgma|parsimony|ml\";\n    print \"\\n\\t-dmode\
: distance mode\";\n    print \"\\n\\t-alignpg: pr\
ogram for aligning sequences (t_coffee=default)\";\
\n    print \"\\n\\t-rtree: replicate tree file (d\
efault: no file)\";\n    print \"\\n\\t-rmsa: repl\
icate msa file (default: no file)\";\n    print \"\
\\n\\t-rmat: replicate matrix file (default: no fi\
le)\";\n    print \"\\n\\t-stype: sequence type: p\
rotein, dna or cdna\";\n    print \"\\n\\t-recompu\
te: force files to be overwritten\";\n    print \"\
\\n\\t-system: cygwin|unix\";\n      \n\n    \n   \
 &my_exit (EXIT_FAILURE);\n  }\nforeach $arg (@ARG\
V){$command.=\"$arg \";}\n\nprint \"CLINE: $comman\
d\\n\";\n$threshold=100;\n$trim_msa=0;\n$stype=\"p\
rot\";\nprint \"msa2bootstrap \";\n\n$system=\"cyg\
win\";\nif(($command=~/\\-system (\\S+)/))\n  {\n \
   $system=$1;\n    if ( $system eq \"cygwin\")\n \
     {\n	$exec_extension=\".exe\";\n      }\n    e\
lsif ( $system eq \"unix\")\n      {\n	$exec_exten\
sion=\"\";\n	print \"system=Unix\";die;\n      }\n\
    else\n      {\n	print \"msa2boostrap: -system=\
$system is an unknown mode [FATAL]\\n\"; die;\n   \
   }\n    \n    print \"-system $system \";\n  }\n\
if(($command=~/\\-stype (\\S+)/))\n  {\n    $stype\
=$1;\n  }\nprint \"-stype=$stype \";\n\n\n\nif(($c\
ommand=~/\\-i (\\S+)/))\n  {\n    $msa=$1;\n    pr\
int \"-i $msa \";\n  }\n\nif(($command=~/\\-rtree \
(\\S+)/))\n  {\n    $rtree=$1;\n    print \"-rtree\
=$rtree \";\n  }\n\nif(($command=~/\\-rmsa (\\S+)/\
))\n  {\n    $rmsa=$1;\n  }\nif(($command=~/\\-rma\
t (\\S+)/))\n  {\n    $rmat=$1;\n  }\n$input=\"seq\
\";\nif(($command=~/\\-input (\\S+)/))\n  {\n    $\
input=$1;\n  }\nprint \"-input=$input \";\n\n$dmod\
e=\"kimura\";\nif(($command=~/\\-dmode (\\S+)/))\n\
  {\n    $dmode=$1;\n  }\nprint \"-dmode=$dmode \"\
;\n$alignpg=\"muscle\";\nif(($command=~/\\-alignpg\
 (\\S+)/))\n  {\n    $alignpg=$1;\n  }\nprint \"-a\
lignpg=$dmode \";\n\n$tmode=\"nj\";\nif(($command=\
~/\\-tmode (\\S+)/))\n  {\n    $tmode=$1;\n  }\npr\
int \"-tmode=$tmode \";\n$recompute=0;\nif(($comma\
nd=~/\\-recompute/))\n  {\n    $recompute=1;\n    \
print \"-recompute \";\n  }\n\n$out=$msa;\n$out=~s\
/\\..*//;\n$out.=\".bph\";\nif(($command=~/\\-o (\\
\S+)/))\n  {\n    $out=$1;\n    \n  }\nprint \"-ou\
t=$out \";\nif (-e $out && !$recompute)\n  {\n    \
print \"\\nNo Computation Required $out already ex\
ists\\n\";\n    &my_exit (EXIT_SUCCESS);\n    \n  \
}\n\n$n=100;\nif(($command=~/\\-n (\\d+)/))\n  {\n\
    $n=$1;\n  }\nprint \"-n=$n \";\n$seed=3;\nif((\
$command=~/\\-s (\\d+)/))\n  {\n    $seed=$1;\n  }\
\nprint \"-s=$seed \";\n\nif(($command=~/\\-run_na\
me (\\d+)/))\n  {\n    $suffix=$1;\n  }\nelse\n  {\
\n    $msa=~/([^.]+)/;\n    $suffix=$1;\n  }\nprin\
t \"-run_name=$suffix\\n\";\n\n\nif ( $input eq \"\
seq\")\n  {\n    $seq=$msa;\n    $msa=\"$suffix.pr\
ot_msa\";\n    \n    if ($stype eq \"cdna\")\n    \
  {\n	$cdna_seq=$seq;\n	$clean_cdna_seq=&vtmpnam()\
;\n	$seq=&vtmpnam();\n	`t_coffee -other_pg seq_ref\
ormat -in $cdna_seq -action +clean_cdna >$clean_cd\
na_seq`;\n	`t_coffee -other_pg seq_reformat -in $c\
lean_cdna_seq -action +translate >$seq`;\n	\n     \
 }\n\n    if (!-e $msa || $recompute)\n      {\n	p\
rint \"\\n#####   Compute an MSA With $alignpg\\n\\
";\n	\n	if ( $alignpg eq \"t_coffee\")\n	  {`$alig\
npg $seq -outfile=$msa >/dev/null 2>/dev/null`;}\n\
	elsif ( $alignpg eq \"muscle\")\n	  {\n	    `$ali\
gnpg -in $seq > $msa 2>/dev/null`;\n	  }\n	elsif (\
 $alignpg eq \"clustalw\")\n	  {\n	    `$alignpg -\
infile=$seq -outfile=$msa -quicktree >/dev/null 2>\
/dev/null`;\n	  }\n	elsif ( $align eq \"mafft\")\n\
	  {\n	    `$alignpg $seq > $msa >/dev/null 2>/dev\
/null`;\n	  }\n	else\n	  {\n	    `$alignpg -in=$se\
q -outfile=$msa`;\n	  }\n      }\n    if (!-e $msa\
)\n      {\n	print \"\\nError: $alignpg Could Not \
produce the MSA $msa [FATAL]\\n\";\n      }\n\n   \
 if ($stype eq \"cdna\")\n      {\n	$msa2=\"$suffi\
x.cdna_msa\";\n	`t_coffee -other_pg seq_reformat -\
in $clean_cdna_seq -in2 $msa -action +thread_dna_o\
n_prot_aln -output fasta_aln  >$msa2`;\n	$msa=$msa\
2;\n      }\n    \n    $input=\"msa\";\n  }\n\n\n\\
n$seqboot_o=&vtmpnam();\n$seqboot_c=&vtmpnam();\n\\
n$protdist_o=&vtmpnam();\n$protdist_c=&vtmpnam();\\
nif ( $input eq \"msa\")\n  {\n    if ($tmode eq \\
"nj\" || $tmode eq \"upgma\"){$input=\"matrix\";}\\
n    \n    $lmsa= &vtmpnam ();\n    `t_coffee -oth\
er_pg seq_reformat -in $msa -output phylip_aln > $\
lmsa`;\n    \n    if ( -e \"outfile\"){unlink (\"o\
utfile\");}\n    # run seqboot\n  \n    if ( $n>1)\
\n      {\n	print \"Run SeqBoot .....\";\n	open (F\
, \">$seqboot_c\");\n	print F \"$lmsa\\nR\\n$n\\nY\
\\n$seed\\n\";\n	close (F);\n	`seqboot$exec_extens\
ion  < $seqboot_c`;\n	if ( -e \"outfile\"){ print \
\"[OK]\\n\";}\n	else { print \"[FAILED]\\n\";&my_e\
xit (EXIT_FAILURE);}\n	`mv outfile $seqboot_o`;\n \
     }\n    else\n      {\n	`cp $lmsa $seqboot_o`;\
\n      }\n\n    if ($rmsa){`cp $seqboot_o $rmsa`;\
}\n    \n    if ($tmode eq \"nj\" || $tmode eq \"u\
pgma\")\n      {\n	if ( $stype eq \"prot\")\n	  {\\
n	    # run protdist\n	    print \"Run Protdist [d\
mode=$dmode]\";\n	    if ($dmode eq \"kimura\")\n	\
      {\n		$dmode=\"P\\nP\\nP\";\n	      }\n	    e\
lse\n	      {\n		print \"\\n$dmode is an unknown m\
ode for Protdist [FATAL:msa2bootstrap.pl]\\n\";\n	\
	&my_exit (EXIT_FAILURE);\n	      }\n	    open (F,\
 \">$protdist_c\");\n	    if ($n>1){print F \"$seq\
boot_o\\n$dmode\\nM\\nD\\n$n\\nY\\n\";}\n	    else\
 {printf F \"$seqboot_o\\n$dmode\\nY\\n\";}\n	    \
close (F);\n	    `protdist$exec_extension  < $prot\
dist_c`;\n	    if ( -e \"outfile\"){ print \"[OK]\\
\n\";}\n	    else { print \"[FAILED]\\n\";&my_exit\
 (EXIT_FAILURE);}\n	    `mv outfile $protdist_o`;\\
n	 \n	  }\n	elsif ( $stype eq \"cdna\" || $stype e\
q \"dna\")\n	  {\n	    print \"Run dnadist [dmode=\
default\";\n	    open (F, \">$protdist_c\");\n	   \
 if ($n>1){print F \"$seqboot_o\\nM\\nD\\n$n\\nY\\\
n\";}\n	    else {printf F \"$seqboot_o\\nY\\n\";}\
\n	    close (F);\n	    `protdist$exec_extension  \
< $protdist_c`;\n	    if ( -e \"outfile\"){ print \
\"[OK]\\n\";}\n	    else { print \"[FAILED]\\n\";&\
my_exit (EXIT_FAILURE);}\n	    `mv outfile $protdi\
st_o`;\n	  }\n      }\n  }\nelsif ( $input eq \"ma\
trix\")\n  {\n    $protdist_o=&vtmpnam();\n    pri\
nt \"MSA: $msa\\n\";\n    `cp $msa $protdist_o`;\n\
    $n=1;\n  }\n\n\n\n\n\n$nb_o=&vtmpnam();\n$nb_c\
=&vtmpnam();\nif ($input eq \"matrix\" && $tmode n\
e \"parsimony\" && $tmode ne \"ml\")\n  {\n    pri\
nt \"Run neighbor [tmode=$tmode]\";\n\n    if ($tm\
ode eq \"nj\")\n      {\n	$tmode=\"\\nN\\nN\";\n  \
    }\n    elsif ( $tmode eq \"upgma\")\n      {\n\
	$tmode = \"\\nN\";\n      }\n    else\n      {\n	\
print \"\\n ERROR: $tmode is an unknown tree compu\
tation mode\\n\";\n	&my_exit (EXIT_FAILURE);\n    \
  }\n\n    open (F, \">$nb_c\");\n    if ($n>1){pr\
int F \"$protdist_o$tmode\\nM\\n$n\\n$seed\\nY\\n\\
";}\n    else {print F \"$protdist_o$tmode\\nY\\n\\
";}\n    close (F);\n\n    `neighbor$exec_extensio\
n  < $nb_c`;\n    if ( -e \"outtree\"){ print \"[N\
eighbor OK]\\n\";}\n    else { print \"[FAILED]\\n\
\";&my_exit (EXIT_FAILURE);}\n    `mv outtree $nb_\
o`;\n    unlink (\"outfile\");\n  }\nelsif ($input\
 eq \"msa\" && $tmode eq \"parsimony\")\n  {\n    \
if ( -e \"outfile\"){unlink (\"outfile\");}\n    i\
f ( -e \"outtree\"){unlink (\"outtree\");}\n    \n\
    if ($stype eq \"prot\")\n      {\n	print \"Run\
 protpars [tmode=$tmode]\";\n	open (F, \">$nb_c\")\
;\n	if ($n>1){print F \"$seqboot_o\\nM\\nD\\n$n\\n\
$seed\\n10\\nY\\n\";}\n	else {print F \"$seqboot_o\
\\nY\\n\";}\n	close (F);\n	`protpars$exec_extensio\
n  < $nb_c`;\n      }\n    elsif ( $stype eq \"dna\
\" || $stype eq \"cdna\")\n      {\n	print \"Run d\
napars [tmode=$tmode]\";\n	open (F, \">$nb_c\");\n\
	if ($n>1){print F \"$seqboot_o\\nM\\nD\\n$n\\n$se\
ed\\n10\\nY\\n\";}\n	else {print F \"$seqboot_o\\n\
Y\\n\";}\n	close (F);\n	`dnapars$exec_extension  <\
 $nb_c`;\n      }\n    if ( -e \"outtree\"){ print\
 \"[OK]\\n\";}\n    else { print \"[FAILED]\\n\";&\
my_exit (EXIT_FAILURE);}\n    `mv outtree $nb_o`;\\
n   unlink (\"outfile\");\n  }\nelsif ($input eq \\
"msa\" && $tmode eq \"ml\")\n  {\n    if ( -e \"ou\
tfile\"){unlink (\"outfile\");}\n    if ( -e \"out\
tree\"){unlink (\"outtree\");}\n    \n    if ($sty\
pe eq \"prot\")\n      {\n	print \"Error: ML impos\
sible with Protein Sequences [ERROR]\";\n	&my_exit\
 (EXIT_FAILURE);\n      }\n    elsif ( $stype eq \\
"dna\" || $stype eq \"cdna\")\n      {\n	print \"R\
un dnaml [tmode=$tmode]\";\n	open (F, \">$nb_c\");\
\n	if ($n>1){print F \"$seqboot_o\\nM\\nD\\n$n\\n$\
seed\\n10\\nY\\n\";}\n	else {print F \"$seqboot_o\\
\nY\\n\";}\n	close (F);\n	`dnaml$exec_extension  <\
 $nb_c`;\n      }\n    if ( -e \"outtree\"){ print\
 \"[OK]\\n\";}\n    else { print \"[FAILED]\\n\";&\
my_exit (EXIT_FAILURE);}\n    `mv outtree $nb_o`;\\
n   unlink (\"outfile\");\n  }\n\n\nelse\n  {\n   \
 `cp $msa $nb_o`;\n    $n=2;\n  }\n\nif ($rmsa && \
-e $seqboot_o){print \"\\nOutput List of $n Replic\
ate MSA: $rmsa\\n\";`cp $seqboot_o $rmsa`;}\nif ($\
rmat && -e $protdist_o){print \"\\nOutput List of \
$n Replicate MATRICES: $rmat\\n\";`cp $protdist_o \
$rmat`;}\nif ($rtree && -e $nb_o){print \"\\nOutpu\
t List of $n Replicate TREES: $rtree\\n\";`cp $nb_\
o $rtree`;}\n\n\n\n$con_o=&vtmpnam();\n$con_c=&vtm\
pnam();\nif ($n >1)\n  {\n    print \"Run Consense\
.....\";\n    open (F, \">$con_c\");\n    print F \
\"$nb_o\\nY\\n\";\n    close (F);\n    `consense$e\
xec_extension  < $con_c`;\n    if ( -s \"outtree\"\
  > 0) { print \"[OK]\\n\";}\n    else { print \"[\
FAILED]\\n\";&my_exit (EXIT_FAILURE);}\n    `mv ou\
ttree $con_o`;\n    unlink (\"outfile\");\n  }\nel\
se\n  {\n    `cp $nb_o $con_o`;\n  }\n\n\n`cp $con\
_o $out`;\nif ( !-e $out)\n  {\n    print \"Tree C\
omputation failed [FAILED]\\n\";\n    &my_exit (EX\
IT_FAILURE);\n  }\nelsif ($n>1)\n  {\n    print \"\
\\nOutput Bootstrapped Tree: $out\\n\";\n    $avg=\
`t_coffee -other_pg seq_reformat -in $out -action \
+avg_bootstrap`;\n    $avg=~s/\\n//g;\n    print \\
"$avg\\n\";\n  }\nelse\n  {\n    print \"\\nOutput\
 Tree: $out\\n\";\n  }\n\nopen (F, \"$out\");\nwhi\
le (<F>)\n  {\n    \n    $tree.=$_;\n  }\nclose (F\
);\n$tree=~s/\\n//g;\nprint \"BPH: $tree\\n\";\n\n\
\n&my_exit (EXIT_SUCCESS);\n\nsub my_exit \n  {\n \
   my $m=@_[0];\n    &clean_vtmpnam();\n    exit (\
$m);\n  }\nsub vtmpnam \n  {\n    my $file;\n\n\n \
   $ntmp++;\n    $file=\"tmp4msa2bootstrap.$rseed.\
$$.$ntmp\";\n    \n    push (@tmpfile, $file);\n  \
  return $file;\n  }\nsub clean_vtmpnam \n  {\n   \
 my $t;\n    foreach $t (@tmpfile)\n      {\n	if (\
 -e $t){unlink ($t)};\n      }\n  }\n","use Env;\n\
$seq_reformat=\"t_coffee -other_pg seq_reformat \"\
;\n$VersionTag=\"1.00\";\n$step=1;\n$unset=\"\";\n\
$scoreT1=$scoreT2=$nseqT=$dp_limit=$unset;\n@tl=()\
;\nchomp($tc_version=`t_coffee -version`);$tc_vers\
ion=~s/PROGRAM: //;\n\n\nprint STDERR \"\\n*******\
**************************************************\
********\";\nprint STDERR \"\\n*           HIGH LE\
VEL PROGRAM: T-COFFEE_DPA Version $VersionTag\";\n\
print STDERR \"\\n*           LOW  LEVEL PROGRAM: \
$tc_version \";\nprint STDERR \"\\n***************\
**************************************************\
\";\n\nif (!@ARGV)\n  {\n    print \"t_coffee_dpa \
accepts every t_coffee_flag.\\nType t_coffee to ob\
tain a list\\n\";\n    print \"Requires $TC_VERSIO\
N\\n\";\n    print \"Requires \";\n    print \"t_c\
offee_dpa specific flags:\\n\";\n    print \"\\t-d\
pa_master_aln....................Master alignment:\
 provided OR computed\\n\";\n    print \"\\t-dpa_m\
aster_aln....................By default, Computed \
with t_coffee -very_fast\\n\";\n    print \"\\t-dp\
a_master_aln=<file>.............Use file, (must be\
 an aln in Fasta or ClustalW\\n\";\n    print \"\\\
t-dpa_master_aln=<program>..........Compute aln wi\
th pg -in seq -out aln`\\n\";\n    print \"\\t-dpa\
_maxnseq.......................Maximum number of s\
equences in subgroups\\n\";\n    print \"\\t-dpa_m\
in_score1....................Minimum Id for two se\
quences to be grouped in ref_aln\\n\";\n    print \
\"\\t-dpa_min_score2....................Minimum Id\
 within a subgroup\\n\";\n    print \"\\t-dpa_debu\
g.........................Keep Tmp File (for debug\
 purpose)\\n\\n\";\n    \n    exit (0);\n  }\nfore\
ach $arg (@ARGV)\n  {\n    $arg_list.=\" $arg\";\n\
  }\n$arg_list=~s/[=,;]/ /g;\n\n\n($seq0, $arg_lis\
t)=&extract_val_from_arg_list(\"^\",$arg_list, \"S\
PLICE\",\"unset\");\n($seq1, $arg_list)=&extract_v\
al_from_arg_list(\"-seq\",$arg_list, \"SPLICE\",\"\
unset\");\n($seq2, $arg_list)=&extract_val_from_ar\
g_list(\"-in\",$arg_list, \"KEEP\",\"unset\");\n($\
seq3, $arg_list)=&extract_val_from_arg_list(\"-inf\
ile\",$arg_list, \"SPLICE\",\"unset\");\n($prf,  $\
arg_list)=&extract_val_from_arg_list(\"-profile\",\
$arg_list, \"SPLICE\",\"unset\");\n\n$gl{'Seq'}=$s\
eq=&vtmpnam();#file containing all the sequences\n\
\n   #1-remove sequences from -in\nif ( $arg_list \
=~/\\-in\\b/)\n  {\n    my $save, $name;\n    whil\
e($arg_list=~/\\-in\\b[^-]+(\\bS[\\w.]+)/)\n      \
{\n	$name=$1;$name=~s/^.//;\n	if ( !-e $name){$sav\
e.=\" S$name \";}\n\n	$arg_list=~s/S$name/ /;\n   \
   }\n    $arg_list=~s/\\-in\\b/\\-in $save /;\n  \
}\n   #2-prepare \n\nif (!($arg_list=~/\\-outorder\
/))\n  {\n    \n    $output_cl .=\" -outorder=$seq\
\";\n  }\n@output_flag=(\"-output\",\"-outfile\", \
\"-run_name\", \"-outorder\"); \nforeach $v1 (@out\
put_flag)\n  {\n    ($v2, $arg_list)=&extract_val_\
from_arg_list($v1,$arg_list, \"SPLICE\",\"unset\")\
;\n    if ($v2 ne \"\")\n      {\n\n	if ($v1 eq \"\
-run_name\"){$run_name=$v2;$output_cl .=\" $v1 $v2\
 \";}\n	elsif ( $v1 eq \"-outorder\")\n	  {\n	    \
if ( $v2 eq \"input\"){$v2=$seq;}\n	    $outorder=\
$v2;$output_cl .=\" $v1 $v2 \";\n	  }\n	else\n	  {\
\n	    $output_cl .=\" $v1 $v2 \";\n	  }\n      }\\
n }\n\n\n($dpa_master_aln, $arg_list)  =&extract_v\
al_from_arg_list(\"-dpa_master_aln\",$arg_list, \"\
SPLICE\", \"t_coffee\");\n$dpa_master_aln=~s/\\s//\
g;\n($nseqT, $arg_list)           =&extract_val_fr\
om_arg_list(\"-dpa_maxnseq\",$arg_list, \"SPLICE\"\
, 30);\n($scoreT1, $arg_list)         =&extract_va\
l_from_arg_list(\"-dpa_min_score1\",$arg_list, \"S\
PLICE\", 80);\n($scoreT2, $arg_list)         =&ext\
ract_val_from_arg_list(\"-dpa_min_score2\"    ,$ar\
g_list, \"SPLICE\", 30);\n($dpa_limit, $arg_list) \
      =&extract_val_from_arg_list(\"-dpa_limit\"  \
      ,$arg_list, \"SPLICE\", 0);\n($dpa_delta_id,\
 $arg_list)    =&extract_val_from_arg_list(\"-dpa_\
delta_id\"        ,$arg_list, \"SPLICE\", 1);\n($d\
pa_debug, $arg_list)       =&extract_val_from_arg_\
list(\"-dpa_debug\"           ,$arg_list, \"SPLICE\
\", 0);\n\n\n$in_seq=$seq0.\" \".$seq1.\" \".$seq2\
.\" \".$seq3;\n$in_prf=(($prf ne $unset)?\"$prf \"\
:\"\");\n&exit_dpa (($in_seq eq \"\" && $in_prf eq\
 \"\")?1:0, \"ERROR: You did not Provide any seque\
nces. Use the -seq flag [FATAL: t_coffee_dpa]\\n\"\
, EXIT_FAILURE);\n\n\nprint STDERR \"\\nSTART DPA \
COMPUTATION\";\n\n\n\nif ($in_seq=~/\\S+/)\n  {\n \
   \n    print STDERR \"\\n Step $step: Gather all\
 the sequences into the tmp file: [$seq]\";$step++\
;	\n    &my_system (\"t_coffee $in_seq -convert -q\
uiet -output fasta_seq -outfile=$seq -maxnseq 0\")\
;\n  }\n\nif ( !-e $seq){$seq=\"\";}\n\nif ($in_pr\
f=~/\\S+/)\n  {\n    $seq_in_type=\"profile\"; \n \
   $seq.= $in_prf; \n  }\nif ($seq eq \"\"){ &exit\
_dpa (1, \"\\nERROR: No Sequence FOund. Provide Se\
quences with the -seq flag [FATAL: t_coffee_dpa]\"\
, EXIT_FAILURE);}\n\n \n\nif ( $run_name)\n  {\n  \
  $suffix=$run_name;\n  }\nelsif ($in_seq=~/\\b(S[\
\\w.]+\\b)/)\n  {\n    my $suffix1, $sufffix2;\n  \
  $suffix1=$suffix2=$1;\n    $suffix2=~s/^S//;\n  \
  if ( -e $suffix1){$suffix=$suffix1;}\n    elsif \
( -e $suffix2){$suffix=$suffix2;}\n    else\n     \
 {\n	$suffix=&vtmpnam();	\n      }\n    $suffix=~s\
/\\.\\w+//;\n  }\n\nelse\n  {\n    $suffix=&vtmpna\
m();\n  }\n\n\nif (!$run_name){$output_cl.=\" -run\
_name $suffix \";}\n\n\n$gl{'Tree'}=&seq2dpa_tree \
($seq, \"$suffix.dpadnd\");\n\nprint STDERR \"\\n \
Step $step: Prepare guide tree: $gl{'Tree'}\";$ste\
p++;\n\nprint STDERR \"\\n Step $step: Identify an\
d Align Closely Related Groups\";$step++;\n%gl=&ma\
ke_one_pass (0, $scoreT1,\"Align\",%gl);\n\nprint \
STDERR \"\\n Step $step: Make Multiple Group Align\
ment\";$step++;\nwhile (!%gl ||$gl{'Ng'}>$nseqT)\n\
  {\n    %gl=&make_one_pass ($nseqT, $scoreT2,\"t_\
coffee\",%gl);\n    if ( $gl{'Newgroups'}==0){$sco\
reT2--;}    \n  }\nprint STDERR \"\\n Step $step: \
Make The Final Alignment\";$step++;\n\n\n$arg_list\
 .=$output_cl;\n\n\n%gl=&tree2group (0,0, %gl);\n$\
gl{$gl{'0'}{'File'}}{'Output'}=\"\";\n$a=0;\n&alig\
n_groups (\"t_coffee\",'0', $arg_list, \" \", %gl)\
;\n\n\n\nif ( !$dpa_keep_tmpfile){&clean_tmp_file \
(@tl);}\n\n\n\nsub seq2dpa_tree \n  {\n    my $seq\
=@_[0];\n    my $newtree=@_[1];\n    my $aln=&vtmp\
nam ();\n\n    &my_system (\"t_coffee -special_mod\
e quickaln -in $seq -outfile $aln -quiet\");\n    \
&my_system (\"$seq_reformat -in $aln -action +aln2\
tree +tree2dpatree -output newick >$newtree\");\n \
   return $newtree;\n  }	\nsub seq2dpa_tree_old \n\
  {\n    my $aln=@_[0];\n    my $newtree=@_[1];\n \
   \n    \n    &my_system(\"$seq_reformat -in $aln\
 -action +seq2dpatree -output newick > $newtree\")\
;\n    return $newtree;\n  }\nsub aln2dpa_tree \n \
 {\n    my $aln=@_[0];\n    my $newtree=&vtmpnam()\
;\n    \n    &my_system(\"$seq_reformat -in $aln -\
action +aln2tree +tree2dpatree -output newick > $n\
ewtree\");\n    return $newtree;\n  }\nsub group_f\
ile2ngroups\n  {\n    my $file=@_[0];\n    my $n;\\
n    \n    open ( F, $file);\n    while (<F>)\n   \
   {\n	$n+=/\\>/;\n      }\n    close (F);\n    re\
turn $n;\n  }\n\nsub make_one_pass\n  {\n    my ($\
N, $ID,$pg, %gl)=@_;\n    my $a;\n\n    %gl=&tree2\
group ($N,$ID,%gl);\n    if (!$gl{'Newgroups'}){re\
turn %gl;}\n    else\n      {\n	for ( $a=0; $a< $n\
g; $a++)\n	  {\n	    if ($gl{$gl{$a}{'File'}}{'Ng'\
}>1){&display_group($a, %gl);}\n	    &align_groups\
 ($pg, $a, $arg_list, \" -quiet=quiet \", %gl);\n	\
  }\n	return %gl;\n      }\n  }\n\nsub tree2group \
\n  {\n    my ($N, $ID, %gl)=@_;\n    my $prefix=&\
vtmpnam();\n    my $group_file=&vtmpnam();\n    my\
 $file;\n    my $oldtree=&vtmpnam();\n    my $n;\n\
    my $tree;\n\n\n    if ( $gl{'Ng'}==1){return %\
gl;}\n    $tree=$gl{'Tree'}; \n    \n    #1 extrac\
t the groups\n    &my_system (\"$seq_reformat -in \
$tree -action +tree2group $N $ID $prefix > $group_\
file\");\n    $n=group_file2ngroups($group_file);\\
n    \n    \n    $gl{'Newgroups'}=1;\n    if ( $n=\
=$gl{'Ng'})\n      {\n	$gl{'Newgroups'}=0;\n	retur\
n %gl;\n      }\n    $gl{'Iteration'}++;\n    $gl{\
'MaxNseq'}=$N;$gl{'MinID'}=$ID;\n    $gl{'GroupFil\
e'}=$group_file;$gl{'Ng'}=$ng=0;\n    #2 Process t\
he group list into the hash\n    open (F, $group_f\
ile);\n    while (<F>)\n      {\n	$gl{'File'}.=$_;\
\n	if (/\\>/)\n	  {\n	    $line=$_;\n	    $line=~s\
/\\>//;\n	    @list=($line=~/(\\S+)/g);\n	    $fil\
e=$gl{$ng}{'File'}=shift @list;\n	    $gl{$file}{'\
Output'}=$file;\n	    \n	    $gl{$file}{'Ng'}=$#li\
st+1;\n	    if ($gl{$file}{'Ng'}>1){ $gl{$file}{'T\
list'}=$gl{$file}{'Alist'}=\"(\";}\n	    foreach $\
l (@list)\n	      {\n	\n		$gl{$file}{'List'}.=\" $\
l \";\n		\n		if (!$gl{$l}{'Tlist'})\n		  {\n		    \
$gl{$l}{'Tlist'}=\"$l\";\n		    $gl{$l}{'Alist'}=\\
"$l\";\n		    $gl{$l}{'Nseq'}=1;\n		    $gl{$l}{'N\
g'}=1;\n		  }\n		$gl{$file}{'Tlist'}.=\"$gl{$l}{'T\
list'},\";\n		$gl{$file}{'Alist'}.=\"$gl{$l}{'Tlis\
t'}|\";\n		$gl{$file}{'Nseq'}+=$gl{$l}{'Nseq'};\n	\
      }\n	    \n\n	    chop($gl{$file}{'Tlist'});c\
hop($gl{$file}{'Alist'});\n	    if ($gl{$file}{'Ng\
'}>1){$gl{$file}{'Tlist'}.=\")\"; $gl{$file}{'Alis\
t'}.=\");\";}\n	    $ng++;\n	  }	\n      }\n    $g\
l{'Ng'}=$ng;\n    close (F);\n    \n    #3 Update \
the old tree with the new groups\n    $gl{'Tree'}=\
&vtmpnam();\n    &my_system (\"$seq_reformat -in $\
tree -action +collapse_tree $group_file -output ne\
wick > $gl{'Tree'}\");\n    \n    return %gl;\n  }\
\n\nsub display_group \n  {\n    my ($g,%gl)=@_;\n\
    my $f;\n    \n    if ( $g==-1)\n      {\n	prin\
t STDERR \"\\nIteration $gl{'Iteration'} [MaxN=$gl\
{'MaxNseq'}][MinID=$gl{'MinID'}]\";\n      }\n    \
else\n      {\n\n	$f=$gl{$g}{'File'};\n	$action=($\
gl{$f}{'Ng'}==1 || $gl{'Iteration'}==1)?\"KEEP  \"\
:\"ALIGN \";\n        print STDERR \"\\n\\t[$actio\
n][MaxN=$gl{'MaxNseq'}][MinID=$gl{'MinID'}][File $\
f][Nseq=$gl{$f}{'Nseq'}][Ngroups=$gl{$f}{'Ng'}][$g\
l{$f}{'Alist'}]\";\n      }\n  }\n      \n\n\nsub \
align_groups\n  {\n    my ($pg, $g, $arg, $extra_a\
rg,%gl)=@_;\n    my $f;\n    my $Output,$Outflag;\\
n    \n    \n    $f=$gl{$g}{'File'};\n    $Output=\
($gl{$f}{'Output'});\n    \n    if ( $pg eq \"Alig\
n\")\n      {\n	if ( !-e $f)\n	  {\n	    $command=\
\"$seq_reformat -in $gl{'Seq'}  -action +extract_a\
ln $gl{'GroupFile'}\";\n	    if ($gl{$f}{'Ng'}>1)\\
n	      {\n		&my_system ($command);\n		$command=\"\
t_coffee -special_mode quick_aln  S$f -outfile=$Ou\
tput -quiet\";\n	      }\n	  }\n	else \n	  {$comma\
nd=\"\";}\n      }\n    elsif ( -e $f)\n      {	\n\
	$Outflag=($Output)?\"-outfile=$Output\":\"\";\n	$\
command=\"$pg -infile $f $Outflag -quiet stdout $a\
rg $extra_arg -maxnseq 0 -convert -quiet stdout\";\
\n      }\n    elsif ( $gl{$f}{'Ng'}==1)\n      {\\
n	$action=($dpa_debug)?\"cp\":\"mv\";\n	$command=\\
"$action $gl{$f}{'List'} $Output\";\n      }\n    \
else\n      {\n	$Outflag=($Output)?\"-outfile=$Out\
put\":\"\";\n	$command=\"$pg -profile $gl{$f}{'Lis\
t'} $Outflag $arg $extra_arg -maxnseq 0\";\n      \
}\n    \n    &my_system ($command);\n    return $o\
utfile;\n  }\n    \nsub my_system \n  {\n    my $c\
ommand=@_[0];\n    my $force=@_[1];\n    my $statu\
s;\n\n    if ( $dpa_debug) {print STDERR \"\\nCOMM\
AND: $command\";}\n    $status=system ($command);\\
n\n    if (!$force)\n       {\n	 &exit_dpa (($stat\
us==1), \"Failed in Command:\\n$command\\n[FATAL: \
t_coffee_dpa]\\n\", EXIT_FAILURE);\n       }\n    \
\n    return $status;\n  }\n\nsub vtmpnam\n  {\n  \
  my $prefix=@_[0];\n    my $tmp_file_name;\n\n   \
 $tmp_prefix=($prefix)?$prefix:\"dpa_tmp_file_$$\"\
;\n   \n    $tmp_count++;\n    $tmp_file_name=\"$t\
mp_prefix\".\"$tmp_count\";\n    $tl[$#tl+1]=$tmp_\
file_name;\n    return $tmp_file_name;\n  }\n\nsub\
 clean_tmp_file\n  {\n\n    my $list;\n    my $fil\
e;\n    \n    if ($dpa_debug){return;}\n    $list=\
vtmpnam();\n    `ls -1 | grep $tmp_prefix>$list`;\\
n    \n    open (F,$list);\n    while ( <F>)\n    \
  {\n	$file=$_;\n	chop $file;\n	if ( -e $file){unl\
ink $file;}\n      }\n    close (F);\n    unlink $\
list;\n  }\n\n\nsub exit_dpa\n  {\n  my $condition\
=@_[0];\n  my $error_msg=@_[1];\n  my $exit_value=\
@_[2];\n  if ( $condition)\n    {\n      print \"$\
error_msg\\n\";\n      exit ($exit_value);\n    }\\
n  else\n    {\n      return;\n    }\n  \n}\nsub e\
xtract_val_from_arg_list\n  {\n    my $arg=@_[0];\\
n    my $arg_list=@_[1];\n    my $keep_flag=@_[2];\
\n    my $default_value=@_[3];\n    my $val=\"\";\\
n    \n    #protect\n    $arg_list=~s/\\s-/ \\@/g;\
\n    $arg=~s/-/\\@/g;\n    \n    #search\n    if \
($arg eq \"^\")\n      {\n	$arg_list=~/^([^@]*)/;\\
n	$val=$1;\n      }\n    else\n      {$arg_list=~/\
$arg ([^@]*)/;$val=$1;}\n    \n    #remove trailin\
g spaces\n    $val=~s/\\s*$//;\n    \n    #remove \
the parsed sequence if needed\n    if (($val ne \"\
\") && $keep_flag ne \"KEEP\")\n      {\n	if ( $ar\
g eq \"^\"){$arg_list=~s/$val/ /;}\n	else {$arg_li\
st=~s/($arg [^@]*)/ /;}\n      }\n	\n    #unprotec\
t\n    $arg_list=~s/\\@/-/g;\n    $arg=~s/\\@/-/g;\
\n    \n    if (($val eq \"\") && $default_value n\
e \"unset\"){$val=$default_value;}\n    \n    retu\
rn $val, $arg_list;\n  }\n$program=\"T-COFFEE (r25\
3)\";\n\n","\n$DEBUG=1;\n$dpa_nseq=10;\n$dpa_sim=0\
;\nif (!@ARGV)\n  {\n    `t_coffee`;\n    exit (0)\
;\n  }\nforeach $arg (@ARGV)\n  {\n    $arg_list.=\
\" $arg\";\n  }\n$max_nseq=10;\n($seq0, $arg_list)\
=&extract_val_from_arg_list(\"^\",$arg_list);\n($s\
eq1, $arg_list)=&extract_val_from_arg_list(\"-seq\\
",$arg_list);\n($seq2, $arg_list)=&extract_val_fro\
m_arg_list(\"-in\",$arg_list, \"KEEP\");\n($seq3, \
$arg_list)=&extract_val_from_arg_list(\"-infile\",\
$arg_list);\n$in_seq=$seq0.\" \".$seq1.\" \".$seq2\
.\" \".$seq3;\n\n$seq=vtmpnam();\n`t_coffee $in_se\
q -convert -output fasta_seq -outfile=$seq`;\n\n\n\
($dpa_nseq, $arg_list)=&extract_val_from_arg_list(\
\"-dpa_nseq\",$arg_list);\n($master_aln, $arg_list\
)=&extract_val_from_arg_list(\"-master_aln\",$arg_\
list);\n($sim_matrix, $arg_list)=&extract_val_from\
_arg_list(\"-sim_matrix\",$arg_list);\n($core_seq,\
 $arg_list)=&extract_val_from_arg_list(\"-core_seq\
\",$arg_list);\n($dpa_sim, $arg_list)=&extract_val\
_from_arg_list(\"-dpa_sim\",$arg_list);\n($run_nam\
e, $arg_list)=&extract_val_from_arg_list(\"-run_na\
me\",$arg_list);\n($output, $arg_list)=&extract_va\
l_from_arg_list(\"-output\",$arg_list);\n\n\n\nif \
(!$sim_mat && !$master_aln)#Compute the fast align\
ment\n  {\n    $ref_aln=vtmpnam();\n    `t_coffee \
-seq=$seq -very_fast -outfile=$ref_aln -quiet`;\n \
   \n  }\n\nif (!$sim_mat)\n  {\n    $sim_mat=vtmp\
nam();\n    `seq_reformat -in $ref_aln -output sim\
 > $sim_mat`;\n  }\n\nif ( !$core_seq)\n  {\n    $\
core_seq=vtmpnam();\n    `seq_reformat -in $ref_al\
n -action +trimTC N$max_nseq -output fasta_seq > $\
core_seq`;\n  }\n@core_name=`seq_reformat -in $cor\
e_seq -output name `; \n\n@tot_name=`seq_reformat \
-in $seq -output name `;\n\nforeach $s (@core_name\
){$s=~s/\\s//g;$hcore{$s}=1;}\nforeach $s (@tot_na\
me){$s=~s/\\s//g;}\nprint STDERR \"T-Coffee_dpa:\\\
n\";\nprint STDERR \"\\tTOTAL  SEQ: @tot_name\\n\"\
;\nprint STDERR \"\\tCHOSEN SEQ: @core_name\\n\";\\
n\n\n\nopen (F, $sim_mat);\nwhile ( <F>)\n  {\n   \
 @l=($_=~/(\\b[\\S]+\\b)/g);\n    if (($l[0] eq \"\
TOP\" || $l[0] eq \"BOT\"))\n      {\n	$s1=$l[1];$\
s2=$l[2];$v=$l[3];\n	if ($hcore{$s1} && !$hcore{$s\
2})\n	  {\n	    if (!$hseq{$s2}{\"sim\"} || $v>$hs\
eq{$s2}{\"sim\"})\n	      {\n		$hseq{$s2}{\"sim\"}\
=$v;$hseq{$s2}{\"seq\"}=$s1;\n	      }\n	  }\n    \
  }\n  }\nclose (F);\nforeach $s (@tot_name)\n  {\\
n\n    if ( !$hseq{$s}{\"seq\"}){;}\n    else\n   \
   {\n	$s2=$hseq{$s}{\"seq\"};\n	$v=$hseq{$s}{\"si\
m\"};\n		\n	if ($v>$dpa_sim)\n	  {\n	    $hseq{$s}\
{'used'}=1;\n	    $seq_list{$s2}{$seq_list{$s2}{'n\
seq'}++}=$s;\n	  }\n      }\n  }\nforeach $s (@cor\
e_name){$seq_list{$s}{$seq_list{$s}{'nseq'}++}=$s;\
$hseq{$s}{'used'}=1;}\nforeach $s (@tot_name){if (\
!$hseq{$s}{'used'}){$seq_list{'unused'}{$seq_list{\
'unused'}{'nseq'}++}=$s;}}\n\n\n$n=0;\nforeach $s \
(@core_name)\n  {\n    $ng++;\n    $n=$seq_list{$s\
}{'nseq'};\n    for (@g_list=(), $a=0; $a<$n; $a++\
){@g_list=(@g_list,$seq_list{$s}{$a});}\n\n    $g_\
seq=vtmpnam();\n    $g_aln=vtmpnam();\n    \n    p\
rint STDERR \"Group $ng: $#g_list Seq: @g_list: \"\
;\n    \n    \n    `seq_reformat -in $seq -action \
+lower +keep_name +extract_seq  @g_list -output fa\
sta_seq > $g_seq`;\n    \n    \n    if ( $#g_list=\
=0)\n      {\n	print STDERR \"[No aln]\\n\";\n	$g_\
aln=$g_seq;\n      }\n    elsif ($#g_list<$max_nse\
q) \n      {\n	print STDERR \"[t_coffee]\\n\";\n	`\
t_coffee $g_seq -outfile=$g_aln -quiet $arg_list`;\
\n      }\n    else\n      {\n	print STDERR \"[t_c\
offee_dpa]\\n\";\n	`t_coffee_dpa2 $g_seq -outfile=\
$g_aln $arg_list -sim_matrix $sim_matrix -dpa_nseq\
 $dpa_nseq`;\n      }\n    @profile_list=(@profile\
_list, $g_aln);\n  }\n\n\nprint \"UNUSED $seq_list\
{'unused'}{'nseq'}\";\n\nif ($seq_list{'unused'}{'\
nseq'})\n    {\n      $prf=vtmpnam();\n      \n   \
   `t_coffee -profile @profile_list $arg_list -out\
file=$prf -quiet`;\n      $n=$seq_list{\"unused\"}\
{'nseq'};\n      $new_seq=vtmpnam();\n      $new_p\
rf=vtmpnam();\n      for ($a=0; $a<$n-1; $a++)\n	{\
\n	  $s=$seq_list{\"unused\"}{$a};\n	  print STDER\
R \"\\nADD Sequence $s\";\n	  \n	  `seq_reformat -\
in $seq -action +lower +keep_name +extract_seq $s \
 -output fasta_seq > $new_seq`;\n	  `t_coffee -pro\
file $prf $new_seq $arg_list -outfile=$new_prf`;\n\
	  `cp $new_prf $prf`;\n	}\n      $s=$seq_list{\"u\
nused\"}{$a};\n      `seq_reformat -in $seq -actio\
n +lower +keep_name +extract_seq $s  -output fasta\
_seq > $new_seq`;\n      @profile_list=($prf, $new\
_seq);\n    }\n    \n      \nif ($run_name){$arg_l\
ist.=\" -run_name $run_name\";}\nelse \n  {\n    $\
in_seq=~/([\\w-]+)/;\n    $arg_list.=\" -run_name \
$1\";\n  }\nif ( $output){$arg_list.=\" -output $o\
utput \";}\n\n`t_coffee -profile @profile_list $ar\
g_list`;\n\n\n&clean (@tmp_file_list);\n\n\nsub vt\
mpnam\n  {\n    my $tmp_file_name;\n    $tmp_name_\
counter++;\n    $tmp_file_name=\"tmp_file_$tmp_nam\
e_counter\\_Pid$$\";\n    $tmp_file_list[$ntmp_fil\
e++]=$tmp_file_name;\n    return $tmp_file_name;\n\
  }\nsub clean\n  {\n  my @fl=@_;\n  my $file;\n  \
return;\n\n  foreach $file ( @fl)\n    {\n      if\
 ( -e $file){unlink($file);}\n    }\n}\nsub extrac\
t_val_from_arg_list\n  {\n    my $arg=@_[0];\n    \
my $arg_list=@_[1];\n    my $keep_flag=@_[2];\n   \
 #protect\n    $arg_list=~s/\\s-/ \\@/g;\n    $arg\
=~s/-/\\@/g;\n    \n    #search\n    if ($arg eq \\
"^\")\n      {\n	$arg_list=~/^([^@]*)/;\n	$val=$1;\
\n      }\n    else\n      {$arg_list=~/$arg ([^@]\
*)/;$val=$1;}\n    \n    #remove the parsed sequen\
ce if needed\n    if ($val && $keep_flag ne \"KEEP\
\")\n      {\n	if ( $arg eq \"^\"){$arg_list=~s/$v\
al/ /;}\n	else {$arg_list=~s/($arg [^@]*)/ /;}\n  \
    }\n	\n    #unprotect\n    $arg_list=~s/\\@/-/g\
;\n    $arg=~s/\\@/-/g;\n    \n    return $val, $a\
rg_list;\n  }\n\n","use Env;\nuse FileHandle;\nuse\
 Cwd;\nuse File::Path;\nuse Sys::Hostname;\n\nour \
$PIDCHILD;\nour $ERROR_DONE;\nour @TMPFILE_LIST;\n\
our $EXIT_FAILURE=1;\nour $EXIT_SUCCESS=0;\n\nour \
$REFDIR=getcwd;\nour $EXIT_SUCCESS=0;\nour $EXIT_F\
AILURE=1;\n\nour $PROGRAM=\"tc_generic_method.pl\"\
;\nour $CL=$PROGRAM;\n\nour $CLEAN_EXIT_STARTED;\n\
our $debug_lock=$ENV{\"DEBUG_LOCK\"};\nour $debug_\
cmd_exec=$ENV{\"DEBUG_CMD_EXEC\"};\nour $LOCKDIR=$\
ENV{\"LOCKDIR_4_TCOFFEE\"};\nif (!$LOCKDIR){$LOCKD\
IR=getcwd();}\nour $ERRORDIR=$ENV{\"ERRORDIR_4_TCO\
FFEE\"};\nour $ERRORFILE=$ENV{\"ERRORFILE_4_TCOFFE\
E\"};\n&set_lock ($$);\nif (isshellpid(getppid()))\
{lock4tc(getppid(), \"LLOCK\", \"LSET\", \"$$\\n\"\
);}\n      \n\n\n\n\nour $BLAST_MAX_NRUNS=2;\nour \
$COMMAND;\nour $PIDCHILD;\n\n$REF_EMAIL=\"\";\n$tm\
p_dir=\"\";\n$init_dir=\"\";\n\n\n$test=0;\nif ($t\
est==1)\n  {\n    $SERVER=\"NCBI\";\n    $query=$A\
RGV[0];\n    $hitf=$ARGV[1];\n    %s=read_fasta_se\
q($query);\n    @sl=keys(%s);\n    &blast_xml2prof\
ile (\"xx\", $s{$sl[0]}{seq},$maxid,$minid,$mincov\
, $hitf);\n    myexit ($EXIT_FAILURE);\n  }\n\nfor\
each $v(@ARGV){$cl.=\"$v \";}\n$COMMAND=$cl;\n($mo\
de)=&my_get_opt ( $cl, \"-mode=\",1,0);\n\n($A)=(&\
my_get_opt ( $cl, \"-name1=\",0,0));\n($B)=(&my_ge\
t_opt ( $cl, \"-name2=\",0,0));\n($TMPDIR)=(&my_ge\
t_opt ( $cl, \"-tmpdir=\",0,0));\n($CACHE)=(&my_ge\
t_opt ( $cl, \"-cache=\",0,0));\n($SERVER)=((&my_g\
et_opt ( $cl, \"-server=\",0,0)));\n($EMAIL)=((&my\
_get_opt ( $cl, \"-email=\",0,0)));\n\nif (!$A){$A\
=\"A\";}\nif (!$B){$B=\"B\";}\n\n\nif (!$TMPDIR)\n\
  {\n    $HOME=$ENV{HOME};\n    if ($ENV{TMP_4_TCO\
FFEE}){$TMPDIR=$ENV{TMP_4_TCOFFEE};}\n    else{$TM\
PDIR=\"$HOME/.t_coffee/tmp/\";}\n  }\nif ( ! -d $T\
MPDIR)\n  {\n    mkdir $TMPDIR;\n  }\nif ( ! -d $T\
MPDIR)\n  {\n    print \"ERROR: Could not create t\
emporary dir: $TMPDIR\\n\";\n    myexit ($EXIT_FAI\
LURE);\n  }\n\n$EMAIL=~s/XEMAILX/\\@/g;\nif (!$EMA\
IL)\n  {\n    if ($ENV{EMAIL_4_TCOFFEE}){$EMAIL=$E\
NV{EMAIL_4_TCOFFEE};}\n    elsif ($ENV{EMAIL}){$EM\
AIL=$ENV{EMAIL};}\n    else {$EMAIL=$REF_EMAIL;}\n\
  }\n\n($maxid,$minid,$mincov)=(&my_get_opt ( $cl,\
 \"-maxid=\",0,0, \"-minid=\",0,0,\"-mincov=\",0,0\
));\nif (!$cl=~/\\-maxid\\=/){$maxid=95;}\nif (!$c\
l=~/\\-minid\\=/){$minid=35;}\nif (!$cl=~/\\-minco\
v\\=/){$mincov=80;}\n\n\n\n\nif ($mode eq \"seq_ms\
a\")\n  {\n    &seq2msa($mode,&my_get_opt ( $cl, \\
"-infile=\",1,1, \"-method=\",1,2, \"-param=\",0,0\
,\"-outfile=\",1,0, \"-database=\",0,0));\n  }\nel\
sif ( $mode eq \"tblastx_msa\")\n  {\n    &seq2tbl\
astx_lib ($mode,&my_get_opt ( $cl, \"-infile=\",1,\
1, \"-outfile=\",1,0));\n  }\nelsif ( $mode eq \"t\
blastpx_msa\")\n  {\n    &seq2tblastpx_lib ($mode,\
&my_get_opt ( $cl, \"-infile=\",1,1, \"-outfile=\"\
,1,0));\n  }\nelsif ( $mode eq \"thread_pair\")\n \
 {\n    &seq2thread_pair($mode,&my_get_opt ( $cl, \
\"-infile=\",1,1, \"-pdbfile1=\",1,1, \"-method=\"\
,1,2,\"-param=\",0,0, \"-outfile=\",1,0, ));\n  }\\
nelsif ( $mode eq \"pdbid_pair\")\n  {\n    &seq2p\
dbid_pair($mode,&my_get_opt ( $cl, \"-pdbfile1=\",\
1,0, \"-pdbfile2=\",1,0, \"-method=\",1,2,\"-param\
=\",0,0, \"-outfile=\",1,0, ));\n  }\nelsif ( $mod\
e eq \"pdb_pair\")\n  {\n    &seq2pdb_pair($mode,&\
my_get_opt ( $cl, \"-pdbfile1=\",1,1, \"-pdbfile2=\
\",1,1, \"-method=\",1,2,\"-param=\",0,0, \"-outfi\
le=\",1,0, ));\n  }\nelsif ( $mode eq \"profile_pa\
ir\")\n  {\n     &seq2profile_pair($mode,&my_get_o\
pt ( $cl, \"-profile1=\",1,1, \"-profile2=\",1,1, \
\"-method=\",1,2,\"-param=\",0,0, \"-outfile=\",1,\
0 ));\n  }\nelsif ($mode eq \"pdb_template_test\")\
\n  {\n    &blast2pdb_template_test ($mode,&my_get\
_opt ( $cl, \"-infile=\",1,1));\n\n  }\nelsif ($mo\
de eq \"psi_template_test\")\n  {\n    &psiblast2p\
rofile_template_test ($mode,&my_get_opt ( $cl, \"-\
seq=\",1,1,\"-blast=\",1,1));\n\n  }\n\nelsif ( $m\
ode eq \"pdb_template\")\n  {\n    &blast2pdb_temp\
late ($mode,&my_get_opt ( $cl, \"-infile=\",1,1, \\
"-database=\",1,0, \"-method=\",1,0, \"-outfile=\"\
,1,0,\"-pdb_type=\",1,0));\n  }\n\nelsif ( $mode e\
q \"profile_template\")\n  {\n    \n    &psiblast2\
profile_template ($mode,&my_get_opt ( $cl, \"-infi\
le=\",1,1, \"-database=\",1,0, \"-method=\",1,0, \\
"-outfile=\",1,0));\n  }\nelsif ( $mode eq \"psipr\
ofile_template\")\n  {\n    &psiblast2profile_temp\
late ($mode,&my_get_opt ( $cl, \"-infile=\",1,1, \\
"-database=\",1,0, \"-method=\",1,0, \"-outfile=\"\
,1,0));\n  }\nelsif ( $mode eq \"RNA_template\")\n\
  {\n    &seq2RNA_template ($mode,&my_get_opt ( $c\
l, \"-infile=\",1,1, \"-outfile=\",1,0));\n  }\nel\
sif ( $mode eq \"tm_template\")\n  {\n    &seq2tm_\
template ($mode, \"\", &my_get_opt ( $cl, \"-infil\
e=\",1,1,\"-arch=\",1,1,\"-psv=\",1,1, \"-outfile=\
\",1,0,));\n  }\nelsif ( $mode eq \"psitm_template\
\")\n  {\n    &seq2tm_template ($mode,&my_get_opt \
( $cl, \"-database=\",1,0, \"-infile=\",1,1, \"-ar\
ch=\",1,1,\"-psv=\",1,1, \"-outfile=\",1,0,));\n  \
}\nelsif ( $mode eq \"ssp_template\")\n  {\n    &s\
eq2ssp_template ($mode,&my_get_opt ( $cl, \"-infil\
e=\",1,1,\"-seq=\",1,1,\"-obs=\",1,1, \"-outfile=\\
",1,0));\n  }\nelsif ( $mode eq \"psissp_template\\
")\n  {\n    &seq2ssp_template ($mode,&my_get_opt \
( $cl, \"-infile=\",1,1,\"-seq=\",1,1,\"-obs=\",1,\
1, \"-outfile=\",1,0));\n  }\n\nelsif ( $mode eq \\
"rna_pair\")\n{\n    &seq2rna_pair($mode,&my_get_o\
pt ( $cl, \"-pdbfile1=\",1,1, \"-pdbfile2=\",1,1, \
\"-method=\",1,2,\"-param=\",0,0, \"-outfile=\",1,\
0, ));\n}\nelsif ( $mode eq \"calc_rna_template\")\
\n{\n    &calc_rna_template($mode,&my_get_opt ( $c\
l, \"-infile=\",1,1,\"-pdbfile=\",1,1, \"-outfile=\
\",1,0));\n}\nelse\n  {\n    myexit(flush_error( \\
"$mode is an unknown mode of tc_generic_method.pl\\
"));\n  }\nmyexit ($EXIT_SUCCESS);\n\n\nsub seq2ss\
p_template\n  {\n  my ($mode, $infile,$gor_seq,$go\
r_obs,$outfile)=@_;\n  my %s, %h;\n  my $result;\n\
  my (@profiles);\n  &set_temporary_dir (\"set\",$\
infile,\"seq.pep\");\n  %s=read_fasta_seq (\"seq.p\
ep\");\n\n  \n  open (R, \">result.aln\");\n  \n  \
#print stdout \"\\n\";\n  foreach $seq (keys(%s))\\
n    {\n      \n      open (F, \">seqfile\");\n   \
   $s{$seq}{seq}=uc$s{$seq}{seq};\n      print (F \
\">$s{$seq}{name}\\n$s{$seq}{seq}\\n\");\n      cl\
ose (F);\n      $lib_name=\"$s{$seq}{name}.ssp\";\\
n      $lib_name=&clean_file_name ($lib_name);\n  \
    \n      if ($mode eq \"ssp_template\"){&seq2go\
r_prediction ($s{$seq}{name},$s{$seq}{seq}, \"seqf\
ile\", $lib_name,$gor_seq, $gor_obs);}\n      elsi\
f ($mode eq \"psissp_template\")\n	{\n	  &seq2msa_\
gor_prediction ($s{$seq}{name},$s{$seq}{seq},\"seq\
file\", $lib_name,$gor_seq, $gor_obs);\n	}\n    \n\
      if ( !-e $lib_name)\n	{\n	  myexit(flush_err\
or(\"GORIV failed to compute the secondary structu\
re of $s{$seq}{name}\"));\n	  myexit ($EXIT_FAILUR\
E);\n	}\n      else\n	{\n	  print stdout \"\\tProc\
ess: >$s{$seq}{name} _E_ $lib_name \\n\";\n	  prin\
t R \">$s{$seq}{name} _E_ $lib_name\\n\";\n	}\n   \
   unshift (@profiles, $lib_name);\n    }\n  close\
 (R);\n  &set_temporary_dir (\"unset\",$mode, $met\
hod,\"result.aln\",$outfile, @profiles);\n}\n\nsub\
 seq2tm_template\n  {\n  my ($mode, $db, $infile,$\
arch,$psv,$outfile)=@_;\n  my %s, %h;\n  my $resul\
t;\n  my (@profiles);\n  &set_temporary_dir (\"set\
\",$infile,\"seq.pep\");\n  %s=read_fasta_seq (\"s\
eq.pep\");\n\n  \n  open (R, \">result.aln\");\n  \
\n  #print stdout \"\\n\";\n  foreach $seq (keys(%\
s))\n    {\n      open (F, \">seqfile\");\n      p\
rint (F \">$s{$seq}{name}\\n$s{$seq}{seq}\\n\");\n\
      close (F);\n      $lib_name=\"$s{$seq}{name}\
.tmp\";\n      $lib_name=&clean_file_name ($lib_na\
me);\n\n      if ($mode eq \"tm_template\")\n	{\n	\
  &safe_system (\"t_coffee -other_pg fasta_seq2hmm\
top_fasta.pl -in=seqfile -out=$lib_name -arch=$arc\
h -psv=$psv\");\n	}\n      elsif ( $mode eq \"psit\
m_template\")\n	{\n	  &seq2msa_tm_prediction ($s{$\
seq}{name},$s{$seq}{seq}, $db, \"seqfile\", $lib_n\
ame,$arch, $psv);\n	}\n      if ( !-e $lib_name)\n\
	{\n	  myexit(flush_error(\"RNAplfold failed to co\
mpute the secondary structure of $s{$seq}{name}\")\
);\n	  myexit ($EXIT_FAILURE);\n	}\n      else\n	{\
\n	  print stdout \"\\tProcess: >$s{$seq}{name} _T\
_ $lib_name\\n\";\n	  print R \">$s{$seq}{name} _T\
_ $lib_name\\n\";\n	}\n      unshift (@profiles, $\
lib_name);\n    }\n  close (R);\n  &set_temporary_\
dir (\"unset\",$mode, $method,\"result.aln\",$outf\
ile, @profiles);\n}\n\nsub seq2RNA_template\n  {\n\
  my ($mode, $infile,$outfile)=@_;\n  my %s, %h, ;\
\n  my $result;\n  my (@profiles);\n  &set_tempora\
ry_dir (\"set\",$infile,\"seq.pep\");\n  %s=read_f\
asta_seq (\"seq.pep\");\n\n  \n  open (R, \">resul\
t.aln\");\n  \n  #print stdout \"\\n\";\n  foreach\
 $seq (keys(%s))\n    {\n      open (F, \">seqfile\
\");\n      print (F \">$s{$seq}{name}\\n$s{$seq}{\
seq}\\n\");\n      close (F);\n      $lib_name=\"$\
s{$seq}{name}.rfold\";\n      $lib_name=&clean_fil\
e_name ($lib_name);\n      &safe_system (\"t_coffe\
e -other_pg RNAplfold2tclib.pl -in=seqfile -out=$l\
ib_name\");\n      \n      if ( !-e $lib_name)\n	{\
\n	 myexit(flush_error(\"RNAplfold failed to compu\
te the secondary structure of $s{$seq}{name}\"));\\
n	  myexit ($EXIT_FAILURE);\n	}\n      else\n	{\n	\
  print stdout \"\\tProcess: >$s{$seq}{name} _F_ $\
lib_name\\n\";\n	  print R \">$s{$seq}{name} _F_ $\
lib_name\\n\";\n	}\n      unshift (@profiles, $lib\
_name);\n    }\n  close (R);\n  &set_temporary_dir\
 (\"unset\",$mode, $method,\"result.aln\",$outfile\
, @profiles);\n}\nsub psiblast2profile_template_te\
st\n  {\n  my ($mode, $seq,$blast)=@_;\n  my %s, %\
h, ;\n  my ($result,$psiblast_output,$profile_name\
,@profiles);\n  my $trim=0;\n  my $maxid=100;\n  m\
y $minid=0;\n  my $mincov=0;\n  my $maxcov=100;\n \
 \n  %s=read_fasta_seq ($seq);\n  open (R, \">resu\
lt.aln\");\n  \n  #print stdout \"\\n\";\n  foreac\
h $seq (keys(%s))\n    {\n      \n      open (F, \\
">seqfile\");\n      print (F \">$A\\n$s{$seq}{seq\
}\\n\");\n      close (F);\n      $psiblast_output\
=$blast;\n      if ( -e $psiblast_output)\n	{\n	  \
%profile=blast_xml2profile($s{$seq}{name}, $s{$seq\
}{seq},$maxid, $minid,$mincov,$psiblast_output);\n\
\n\n	  \n	  $profile_name=\"$s{$seq}{name}.prf\";\\
n	  $profile_name=&clean_file_name ($profile_name)\
;\n	  unshift (@profiles, $profile_name);\n	  outp\
ut_profile ($profile_name, \\%profile, $trim);\n	 \
 print stdout \"\\tProcess: >$s{$seq}{name} _R_ $p\
rofile_name [$profile{n} Seq.] [$SERVER/blast/$db]\
[$CACHE_STATUS]\\n\";\n	  print R \">$s{$seq}{name\
} _R_ $profile_name\\n\";\n	}\n    }\n  close (R);\
\n  \n  die;\n}\nsub psiblast2profile_template \n \
 {\n  my ($mode, $infile, $db, $method, $outfile)=\
@_;\n  my %s, %h, ;\n  my ($result,$psiblast_outpu\
t,$profile_name,@profiles);\n  my $trim=0;\n  &set\
_temporary_dir (\"set\",$infile,\"seq.pep\");\n  %\
s=read_fasta_seq (\"seq.pep\");\n  open (R, \">res\
ult.aln\");\n  \n  #print stdout \"\\n\";\n  forea\
ch $seq (keys(%s))\n    {\n      open (F, \">seqfi\
le\");\n      print (F \">$A\\n$s{$seq}{seq}\\n\")\
;\n      close (F);\n      $psiblast_output=&run_b\
last ($s{$seq}{name},$method, $db, \"seqfile\",\"o\
utfile\");\n      \nif ( -e $psiblast_output)\n	{\\
n	  %profile=blast_xml2profile($s{$seq}{name}, $s{\
$seq}{seq},$maxid, $minid,$mincov,$psiblast_output\
);\n	  unlink ($psiblast_output);\n	  \n	  $profil\
e_name=\"$s{$seq}{name}.prf\";\n	  $profile_name=&\
clean_file_name ($profile_name);\n	  unshift (@pro\
files, $profile_name);\n	  output_profile ($profil\
e_name, \\%profile, $trim);\n	  print stdout \"\\t\
Process: >$s{$seq}{name} _R_ $profile_name [$profi\
le{n} Seq.] [$SERVER/blast/$db][$CACHE_STATUS]\\n\\
";\n	  print R \">$s{$seq}{name} _R_ $profile_name\
\\n\";\n	}\n    }\n  close (R);\n  &set_temporary_\
dir (\"unset\",$mode, $method,\"result.aln\",$outf\
ile, @profiles);\n}\nsub blast2pdb_template_test\n\
    {\n      my ($mode,$infile)=@_;\n      my ($ma\
xid,$minid,$mincov);\n      $maxid=100;\n      $mi\
nid=0;\n      $mincov=0;\n      \n      print \"$i\
nfile\\n\";\n      \n      %p=blast_xml2profile($s\
{$seq}{name}, $s{$seq}{seq},$maxid, $minid,$mincov\
,$infile);\n      $c=1;\n      print stdout \"\\tP\
rocess: >$s{$seq}{name} [$SERVER/blast/$db][$CACHE\
_STATUS]\\n\";\n      while (!$found && $c<$p{n})\\
n	{\n	  $pdbid=&id2pdbid($p{$c}{identifyer});\n	  \
if ( length ($pdbid)>5){$pdbid=id2pdbid($p{$c}{def\
inition});}\n	  \n	  if ( length ($pdbid)>5)\n	   \
 {\n	      myexit(add_error (EXIT_FAILURE,$$,$$,ge\
tppid(), \"BLAST_FAILURE::Could Not Parse PDBID ($\
p{$c}{identifyer},$p{$c}{definition})\"));\n	    }\
\n	  \n	  \n	  if (!&pdb_is_released($pdbid))\n	  \
  {\n	      print stdout \"\\t\\t**$pdbid [PDB NOT\
 RELEASED or WITHDRAWN]\\n\";\n	      $c++;\n	    \
}\n	  elsif (!&pdb_has_right_type ($pdbid,$type))\\
n	    {\n	      my $ptype=&pdb2type ($pdbid);\n	  \
    my $etype=&type2etype($type);\n	      \n	     \
 print stdout \"\\t\\t**$pdbid [$ptype cannot be u\
sed (expected: $etype)]\\n\";\n	      $c++;\n	    \
}\n	  else\n	    {\n	      $found=1;\n	    }\n	}\n\
\n      if ($found)\n	{\n	  print stdout \"\\t\\t \
>$s{$seq}{name} _P_ $pdbid\\n\";\n	}\n      else\n\
	{\n	  print stdout \"\\t\\t >$s{$seq}{name} No Te\
mplate Selected\\n\";\n	}\n      die;\n    }\nsub \
blast2pdb_template \n  {\n  my ($mode, $infile, $d\
b, $method, $outfile,$type)=@_;\n  my %s, %h, ;\n \
 my ($result,$blast_output);\n  &set_temporary_dir\
 (\"set\",$infile,\"seq.pep\");\n  %s=read_fasta_s\
eq (\"seq.pep\");\n  open (R, \">result.aln\");\n \
 \n \n  #print stdout \"\\n\";\n  foreach $seq (ke\
ys(%s))\n    {\n      my $c;\n      my $found;\n  \
    \n      open (F, \">seqfile\");\n      print (\
F \">$A\\n$s{$seq}{seq}\\n\");\n      close (F);\n\
     \n      $blast_output=&run_blast ($s{$seq}{na\
me},$method, $db, \"seqfile\",\"outfile\");\n     \
\n      %p=blast_xml2profile($s{$seq}{name}, $s{$s\
eq}{seq},$maxid, $minid,$mincov,$blast_output);\n \
     unlink ($blast_output);\n      \n      $c=1;\\
n      print stdout \"\\tProcess: >$s{$seq}{name} \
[$SERVER/blast/$db][$CACHE_STATUS]\\n\";\n      wh\
ile (!$found && $c<$p{n})\n	{\n	  $pdbid=&id2pdbid\
($p{$c}{identifyer});\n	  if ( length ($pdbid)>5){\
$pdbid=id2pdbid($p{$c}{definition});}\n\n	  if ( l\
ength ($pdbid)>5)\n	    {\n	      myexit(add_error\
 (EXIT_FAILURE,$$,$$,getppid(), \"BLAST_FAILURE::C\
ould Not Parse PDBID ($p{$c}{identifyer},$p{$c}{de\
finition})\"));\n	    }\n	  \n\n	  if (!&pdb_is_re\
leased($pdbid))\n	    {\n	      print stdout \"\\t\
\\t**$pdbid [PDB NOT RELEASED or WITHDRAWN]\\n\";\\
n	      $c++;\n	    }\n	  elsif (!&pdb_has_right_t\
ype ($pdbid,$type))\n	    {\n	      my $ptype=&pdb\
2type ($pdbid);\n	      my $etype=&type2etype($typ\
e);\n	      \n	      print stdout \"\\t\\t**$pdbid\
 [$ptype cannot be used (expected: $etype)]\\n\";\\
n	      $c++;\n	    }\n	  else\n	    {\n	      $fo\
und=1;\n	    }\n	}\n\n      if ($found)\n	{\n	  pr\
int R \">$s{$seq}{name} _P_ $pdbid\\n\";\n	  print\
 stdout \"\\t\\t >$s{$seq}{name} _P_ $pdbid\\n\";\\
n	}\n      else\n	{\n	  print R \">$s{$seq}{name}\\
\n\";\n	  print stdout \"\\t\\t >$s{$seq}{name} No\
 Template Selected\\n\";\n	}\n    }\n  close (R);\\
n  &set_temporary_dir (\"unset\",$mode, $method,\"\
result.aln\",$outfile);\n}\nsub type2etype\n  {\n \
   my $type=shift;\n    my $etype;\n    \n    if (\
 $type=~/n/){$etype.=\"NMR \";}\n    if ( $type=~/\
d/){$etype.=\"diffraction \";}\n    if ( $type=~/m\
/){$etype.=\"model \";}\n    return $etype;\n  }\n\
sub pdb2type\n  {\n     my $pdb=shift;\n     my $f\
=vtmpnam();\n     \n     my $value= &safe_system (\
\"t_coffee -other_pg extract_from_pdb -model_type \
$pdb > $f\");\n     my $r=&file2string ($f);\n    \
 chomp($r);\n     return $r;\n   }\nsub pdb_has_ri\
ght_type\n  {\n    my $pdb=shift;\n    my $type=sh\
ift;\n    \n    my $f=vtmpnam();\n    \n    my $va\
lue= &safe_system (\"t_coffee -other_pg extract_fr\
om_pdb -model_type $pdb > $f\");\n    my $r=&file2\
string ($f);\n    chomp($r);\n\n        \n    if (\
 $r eq \"NMR\" && $type=~/n/){return 1;}\n    elsi\
f ( $r eq \"diffraction\" && $type=~/d/){return 1;\
}\n    elsif ( $r eq \"model\" && $type=~/m/){retu\
rn 1;}\n    else {return 0;}\n  }\nsub pdb_is_rele\
ased\n  {\n    my $pdb=shift;\n    my $f=vtmpnam()\
;\n    \n    $value= &safe_system (\"t_coffee -oth\
er_pg extract_from_pdb -is_released_pdb_name $pdb \
> $f\");\n    my $r=&file2string ($f);\n    chomp(\
$r);\n    return $r;\n  }\nsub blast_msa\n  {\n   \
 my ($infile,$db,$outfile)=@_;\n    my ($a, %seq);\
\n    my $seqfile;\n    my $SEQ=new FileHandle;\n \
   my $seqfile=\"seqfile\";\n    my @txt;\n    \n \
   \n    %s1=&read_fasta_seq ($db);\n    \n    for\
each $s (keys (%s1))\n      {\n	$i=$s1{$s}{order};\
\n	$s{$i}{name}=$s;\n	$s{$i}{seq}=$s1{$s}{seq};\n	\
$s{$i}{len}=length( $s{$i}{seq});\n	$s{n}++;\n    \
  }\n    \n    &safe_system (\"formatdb -i $db\");\
\n    &safe_system  (\"blastall -i $infile -d $db \
-m7 -p blastp -o io\");\n    &set_blast_type (\"io\
\");\n    \n    %FB=&xml2tag_list (\"io\", \"Itera\
tion\");\n    open (F, \">$outfile\");\n    print \
F \"! TC_LIB_FORMAT_01\\n\";\n    print F \"$s{n}\\
\n\";\n    for ( $a=0; $a<$s{n}; $a++)\n      {\n	\
print F \"$s{$a}{name} $s{$a}{len} $s{$a}{seq}\\n\\
";\n      }\n\n\n    for ( $a=0; $a<$FB{n}; $a++)\\
n      {\n	%p=blast_xml2profile ($s{$a}{name}, $s{\
$a}{seq},100, 0, 0, $FB{$a}{body});\n	my $query=$p\
{0}{name};\n	my $i= $s1{$query}{order}+1;\n	for ($\
b=1; $b<$p{n}; $b++)\n	  {\n	    my $l=length ($p{\
$b}{Qseq});\n	    my $hit=$p{$b}{definition};\n	  \
  my $Qstart=$p{$b}{Qstart};\n	    my $Hstart=$p{$\
b}{Hstart};\n	    my $identity=$p{$b}{identity};\n\
	    my @lrQ=split (//,$p{$b}{Qseq});\n	    my @lr\
H=split (//,$p{$b}{Hseq});\n	    \n	    my $j= $s1\
{$hit}{order}+1;\n	    #if ( $j==$i){next;}\n	    \
printf F \"# %d %d\\n\", $i, $j;\n	    #  print  F\
 \"\\n$p{$b}{Qseq} ($Qstart)\\n$p{$b}{Hseq} ($Hsta\
rt)\";\n	    for ($c=0; $c<$l; $c++)\n	      {\n		\
my $rQ=$lrQ[$c];\n		my $rH=$lrH[$c];\n		my $n=0;\n\
		\n		if ($rQ ne \"-\"){$n++, $Qstart++;}\n		if ($\
rH ne \"-\"){$n++; $Hstart++;}\n		\n		if ( $n==2)\\
n		  {\n		    printf F \"\\t%d %d %d\\n\", $Qstart\
-1, $Hstart-1,$identity;\n		  }\n	      }\n	  }\n \
     }\n    print F \"! SEQ_1_TO_N\\n\";\n    clos\
e (F);\n    return $output;\n  \n  }\n\nsub blast_\
msa_old\n  {\n    my ($infile,$outfile)=@_;\n    m\
y ($a, %seq);\n    %s1=&read_fasta_seq ($infile);\\
n    foreach $s (keys (%s1))\n      {\n	$i=$s1{$s}\
{order};\n	$s{$i}{name}=$s;\n	$s{$i}{seq}=$s1{$s}{\
seq};\n	$s{$i}{len}=length( $s{$i}{seq});\n	$s{n}+\
+;\n      }\n    &safe_system (\"formatdb -i $infi\
le\");\n    &safe_system (\"blastall -i $infile -d\
 $infile -m7 -o io\");\n    &set_blast_type (\"io\\
");\n    \n    %FB=&xml2tag_list (\"io\", \"Iterat\
ion\");\n    \n    open (F, \">$outfile\");\n    p\
rint F \"! TC_LIB_FORMAT_01\\n\";\n    print F \"$\
s{n}\\n\";\n    for ( $a=0; $a<$s{n}; $a++)\n     \
 {\n	print F \"$s{$a}{name} $s{$a}{len} $s{$a}{seq\
}\\n\";\n      }\n    for ( $a=0; $a<$FB{n}; $a++)\
\n      {\n	%p=blast_xml2profile ($s{$a}{name}, $s\
{$a}{seq},100, 0, 0, $FB{$a}{body});\n	for ($b=1; \
$b<$p{n}; $b++)\n	  {\n	    my $l=length ($p{$b}{Q\
seq});\n	    my $hit=$p{$b}{definition};\n	    my \
$Qstart=$p{$b}{Qstart};\n	    my $Hstart=$p{$b}{Hs\
tart};\n	    my $identity=$p{$b}{identity};\n	    \
my @lrQ=split (//,$p{$b}{Qseq});\n	    my @lrH=spl\
it (//,$p{$b}{Hseq});\n	    my $i= $s1{$s{$a}{name\
}}{order}+1;\n	    my $j= $s1{$hit}{order}+1;\n	  \
  #if ( $j==$i){next;}\n	    printf F \"# %d %d\\n\
\", $i, $j;\n	    #  print  F \"\\n$p{$b}{Qseq} ($\
Qstart)\\n$p{$b}{Hseq} ($Hstart)\";\n	    for ($c=\
0; $c<$l; $c++)\n	      {\n		my $rQ=$lrQ[$c];\n		m\
y $rH=$lrH[$c];\n		my $n=0;\n		\n		if ($rQ ne \"-\\
"){$n++, $Qstart++;}\n		if ($rH ne \"-\"){$n++; $H\
start++;}\n		\n		if ( $n==2)\n		  {\n		    printf \
F \"\\t%d %d %d\\n\", $Qstart-1, $Hstart-1,$identi\
ty;\n		  }\n	      }\n	  }\n      }\n    print F \\
"! SEQ_1_TO_N\\n\";\n    close (F);\n    return $o\
utput;\n  \n  }\n\nsub seq2msa\n  {\n    my ($mode\
, $infile, $method, $param, $outfile,$database)=@_\
;\n    &set_temporary_dir (\"set\",$infile,\"seq.p\
ep\", $database, \"db.pep\");\n    $param.=\" >/de\
v/null 2>&1 \";\n    \n    \n    #make sure test.p\
ep is in FASTA\n    &safe_system (\"t_coffee -othe\
r_pg seq_reformat -in seq.pep -output fasta_seq > \
x\");\n    `mv x seq.pep`;\n    \n    if ( $method\
 eq \"blastp\")\n      {\n	&blast_msa (\"seq.pep\"\
, \"db.pep\",\"result.aln\");\n      }\n    elsif \
( $method eq \"muscle\")\n      {\n	`muscle -in se\
q.pep -out result.aln $param`;\n      }\n    elsif\
 ( $method eq \"probcons\")\n      {\n	`probcons s\
eq.pep >result.aln 2>/dev/null`;\n      }\n    els\
if ( $method eq \"mafft\")\n      {\n	`mafft --qui\
et --localpair --maxiterate 1000 seq.pep> result.a\
ln  2>/dev/null`\n      }\n    elsif ( $method=~/p\
rank/)\n      {\n	`$method -d=seq.pep -o=result.al\
n -quiet 2>/dev/null`;\n	`mv result.aln.1.fas resu\
lt.aln`;\n      }\n    else\n      {\n	`$method -i\
nfile=seq.pep -outfile=result.aln`;\n      }\n    \
\n    &set_temporary_dir (\"unset\",$mode, $method\
,\"result.aln\",$outfile);\n    myexit ($EXIT_SUCC\
ESS);\n  }\n\nsub seq2thread_pair\n  {\n    my ($m\
ode, $infile, $pdbfile1, $method, $param, $outfile\
)=@_;\n    &set_temporary_dir (\"set\",$infile,\"s\
eq.pep\",$pdbfile1,\"struc.pdb\");\n    if ($metho\
d eq \"fugueali\")\n      {\n	#Env Variable that n\
eed to be defined for Fugue\n	if (!$ENV{FUGUE_LIB_\
LIST}){$ENV{FUGUE_LIB_LIST}=\"DUMMY\";}\n	if (!$EN\
V{HOMSTRAD_PATH})  {$ENV{HOMSTRAD_PATH}=\"DUMMY\";\
}\n	if (!$ENV{HOMS_PATH}){$ENV{HOMS_PATH}=\"DUMMY\\
";}\n	\n	`joy struc.pdb >x 2>x`;\n	&check_file(\"s\
truc.tem\", \"Joy failed [FATAL:$PROGRAM/$method]\\
");\n	`melody -t struc.tem >x 2>x`;\n	&check_file(\
\"struc.tem\", \"Melody failed [FATAL:$PROGRAM/$me\
thod]\");\n	`fugueali -seq seq.pep -prf struc.fug \
-print > tmp_result.aln`;\n	\n	&check_file(\"tmp_r\
esult.aln\", \"Fugue failed [FATAL:$PROGRAM/$metho\
d]\");\n	&safe_system (\"t_coffee -other_pg seq_re\
format -in tmp_result.aln -output fasta_aln >resul\
t.aln\");\n      }\n    elsif ( $method eq \"t_cof\
fee\")\n      {\n	&safe_system (\"t_coffee -in Pst\
ruc.pdb Sseq.pep Mslow_pair -outfile result.aln -q\
uiet\");\n      }\n    else\n      {\n	&safe_syste\
m (\"$method -infile=seq.pep -pdbfile1=struc.pdb -\
outfile=result.aln $param>x 2>x\");\n      }\n    \
&set_temporary_dir (\"unset\",$mode,$method,\"resu\
lt.aln\",$outfile);\n    myexit ($EXIT_SUCCESS);\n\
  }\nsub seq2pdbid_pair\n  {\n    my ($mode, $pdbf\
ile1, $pdbfile2, $method, $param, $outfile)=@_;\n \
   my ($name);\n\n    \n    &set_temporary_dir (\"\
set\");\n    $name=$pdbfile1.\" \".$pdbfile2;\n\n \
   if (    &cache_file(\"GET\",\"\",\"$name\",\"$m\
ethod\",\"dali\",$outfile,\"EBI\"))\n      {return\
 $outfile;}\n    else\n      {\n	if ($method eq \"\
daliweb\")\n	  {\n	    $pdbfile1=~/(....)(.)/;\n	 \
   $id1=$1; $c1=$2;\n	    \n	    $pdbfile2=~/(....\
)(.)/;\n	    $id2=$1; $c2=$2;\n	    \n	    $comman\
d=\"t_coffee -other_pg dalilite.pl --pdb1 $id1 --c\
hainid1 $c1 --pdb2 $id2 --chainid2 $c2 --email=$EM\
AIL  >dali_stderr 2>dali_stderr\";\n	    $dali=`$c\
ommand`;\n	    \n	    open (F, \"dali_stderr\");\n\
	    while (<F>)\n	      {\n		if ( /JobId: dalilit\
e-(\\S+)/)\n		{\n		  $jobid=$1;\n		}\n	      }\n	 \
   close (F);\n	    unlink (\"dali_stderr\");\n	  \
  \n	    $output1=\"dalilite-$jobid.txt\";\n	    i\
f ( -e $output1)\n	      {\n		unlink ($output1);\n\
		&url2file (\"http://www.ebi.ac.uk/Tools/es/cgi-b\
in/jobresults.cgi/dalilite/dalilite-$jobid/aln.htm\
l\", \"output2\");\n		\n		if ( -e \"output2\")\n		\
  {\n		    my ($seq1, $seq2);\n		    $seq1=$seq2=\\
"\";\n		    \n		    open (F, \"output2\");\n		    \
while (<F>)\n		      {\n			$l=$_;\n			if ( $l=~/Qu\
ery\\s+(\\S+)/)\n			  {\n			    $seq1.=$1;\n			  }\
\n			elsif ( $l=~/Sbjct\\s+(\\S+)/)\n			  {\n			  \
  $seq2.=$1;\n			  }\n		      }\n		    close (F);\\
n		    unlink (\"output2\");\n		    if ($seq1 ne \\
"\" && $seq2 ne \"\")\n		      {\n			$output3=\">$\
A\\n$seq1\\n>$B\\n$seq2\\n\";\n			$output3=~s/\\./\
-/g;\n			open (F, \">result.aln\");\n			print F \"\
$output3\";\n			close (F);\n		      }\n		  }\n	   \
   }\n	  }\n      }\n    &cache_file(\"SET\",\"\",\
\"$name\",\"$method\",\"dali\",\"result.aln\",\"EB\
I\");\n    &set_temporary_dir (\"unset\",$mode, $m\
ethod, \"result.aln\",$outfile);\n    myexit ($EXI\
T_SUCCESS);\n  }\nsub seq2pdb_pair\n  {\n    my ($\
mode, $pdbfile1, $pdbfile2, $method, $param, $outf\
ile)=@_;\n    \n    &set_temporary_dir (\"set\",$p\
dbfile1,\"pdb1.pdb\",$pdbfile2,\"pdb2.pdb\");\n   \
 if ($method eq \"t_coffee\")\n      {\n	&safe_sys\
tem (\"t_coffee -in Ppdb1.pdb Ppdb2.pdb -quiet -ou\
tfile=result.aln\");\n      }\n    elsif ( $method\
 eq \"DaliLite\")\n      {\n	if ( &safe_system (\"\
DaliLite -pairwise pdb1.pdb pdb2.pdb >tmp1\")==$EX\
IT_SUCCESS)\n	  {\n	     my ($seq1, $seq2);\n	    \
 $seq1=$seq2=\"\";\n		    \n	     open (F, \"tmp1\\
");\n	     while (<F>)\n	       {\n		 $l=$_;\n		 i\
f ( $l=~/Query\\s+(\\S+)/)\n		   {\n		     $seq1.=\
$1;\n		   }\n		 elsif ( $l=~/Sbjct\\s+(\\S+)/)\n		\
   {\n		     $seq2.=$1;\n		   }\n	       }\n	     \
close (F);\n	     unlink (\"tmp1\");\n	     if ($s\
eq1 ne \"\" && $seq2 ne \"\")\n	       {\n		 my $o\
utput3=\">$A\\n$seq1\\n>$B\\n$seq2\\n\";\n		 $outp\
ut3=~s/\\./-/g;\n		 open (F, \">result.aln\");\n		\
 print F \"$output3\";\n		 close (F);\n	       }\n\
	   }\n	else\n	  {\n	    print \"ERROR: DalLite fa\
iled to align the considered structures[tc_generic\
_method.pl]\\n\";\n	  }    \n      }\n    elsif ( \
$method eq \"TMalign\")\n      {\n	if ( &safe_syst\
em (\"TMalign pdb1.pdb pdb2.pdb >tmp1\")==$EXIT_SU\
CCESS)\n	  {\n	    `tail -4 tmp1 > tmp2`;\n	    \n\
	    open (F, \"tmp2\");\n	    while (<F>)\n	     \
 {\n		unshift(@l, $_);\n	      }\n	    close (F);\\
n	    open (F, \">result.aln\");\n	    $l[3]=~s/[^\
a-zA-Z0-9-]/\\-/g;\n	    $l[1]=~s/[^a-zA-Z0-9-]/\\\
-/g;\n	    print F \">$A\\n$l[3]\\n>$B\\n$l[1]\\n\\
";\n	    close (F);\n	  }\n	else\n	  {\n	    print\
 \"ERROR: TMalign failed to align the considered s\
tructures[tc_generic_method.pl]\\n\";\n	    `rm re\
sult.aln >/dev/null 2>/dev/null`;\n	  }\n      }\n\
    elsif ( $method eq \"mustang\")\n      {\n	if \
( &safe_system (\"mustang -i pdb1.pdb pdb2.pdb -F \
fasta >/dev/null 2>/dev/null\")==$EXIT_SUCCESS)\n	\
  {\n	    `mv results.afasta result.aln`;\n	  }\n	\
else\n	  {\n	    print \"ERROR: mustang failed to \
align the considered structures[tc_generic_method.\
pl]\\n\";\n	    `rm result.aln >/dev/null 2>/dev/n\
ull`;\n	  }\n      }\n    else\n      {\n	if ( &sa\
fe_system (\"$method -pdbfile1=pdb1.pep -pdbfile2=\
pdb2.pdb -outfile=result.aln $param>x 2>x\")==$EXI\
T_SUCCESS)\n	  {\n	    `mv results.afasta result.a\
ln`;\n	  }\n	else\n	  {\n	    print \"ERROR: $meth\
od failed to align the considered structures[tc_ge\
neric_method.pl]\\n\";\n	    `rm result.aln >/dev/\
null 2>/dev/null`;\n	  }\n      }\n    &set_tempor\
ary_dir (\"unset\",$mode, $method, \"result.aln\",\
$outfile);\n    myexit ($EXIT_SUCCESS);\n  }\n\nsu\
b seq2profile_pair\n  {\n    my ($mode, $profile1,\
 $profile2, $method, $param, $outfile)=@_;\n    \n\
    \n    if ($method eq \"clustalw\")\n      {\n	\
&set_temporary_dir (\"set\",$profile1,\"prf1.aln\"\
,$profile2,\"prf2.aln\");\n	`clustalw -profile1=pr\
f1.aln -profile2=prf2.aln -outfile=result.aln`;\n	\
&set_temporary_dir (\"unset\",$mode, $method, \"re\
sult.aln\",$outfile);\n      }\n    elsif ( $metho\
d eq \"hhalign\")\n      {\n	hhalign ( $profile1,$\
profile2,$outfile,$param);\n      }\n    else\n   \
   {\n	\n	`$method -profile1=prf1.aln -profile2=pr\
f2.aln -outfile=result.aln $param>x 2>x`;\n      }\
\n   \n    myexit ($EXIT_SUCCESS);\n  }\n\nsub pg_\
is_installed\n  {\n    my @ml=@_;\n    my ($r, $p,\
 $m);\n    my $supported=0;\n    \n    my $p=shift\
 (@ml);\n    if ($p=~/::/)\n      {\n	if (safe_sys\
tem (\"perl -M$p -e 1\")==$EXIT_SUCCESS){return 1;\
}\n	else {return 0;}\n      }\n    else\n      {\n\
	$r=`which $p 2>/dev/null`;\n	if ($r eq \"\"){$r=0\
;}\n	else {$r=1;}\n	\n	if ($r==0 && is_blast_packa\
ge ($p)){return pg_is_installed (\"legacy_blast.pl\
\");}\n	else {return $r;}\n      }\n  }\n\nsub is_\
blast_package\n  {\n    my $p=shift;\n    if ( $p=\
~/blastp/){return 1;}\n    elsif ($p=~/blastall/){\
return 1;}\n    elsif ($p=~/blastn/){return 1;}\n \
   elsif ($p=~/blastx/){return 1;}\n    elsif ($p=\
~/formatdb/){return 1;}\n    else {return 0;}\n  }\
\n    \nsub check_internet_connection\n  {\n    my\
 $internet;\n    my $tmp;\n    &check_configuratio\
n ( \"wget\"); \n    \n    $tmp=&vtmpnam ();\n    \
\n    if     (&pg_is_installed    (\"wget\")){`wge\
t www.google.com -O$tmp >/dev/null 2>/dev/null`;}\\
n    elsif  (&pg_is_installed    (\"curl\")){`curl\
 www.google.com -o$tmp >/dev/null 2>/dev/null`;}\n\
    \n    if ( !-e $tmp || -s $tmp < 10){$internet\
=0;}\n    else {$internet=1;}\n    if (-e $tmp){un\
link $tmp;}\n\n    return $internet;\n  }\nsub che\
ck_pg_is_installed\n  {\n    my @ml=@_;\n    my $r\
=&pg_is_installed (@ml);\n    if (!$r && $p=~/::/)\
\n      {\n	print STDERR \"\\nYou Must Install the\
 perl package $p on your system.\\nRUN:\\n\\tsudo \
perl -MCPAN -e 'install $pg'\\n\";\n      }\n    e\
lsif (!$r)\n      {\n	myexit(flush_error(\"\\nProg\
ram $p Supported but Not Installed on your system\\
"));\n      }\n    else\n      {\n	return 1;\n    \
  }\n  }\nsub set_temporary_dir\n  {\n    my @list\
=@_;\n    my $dir_mode, $a, $mode, $method;\n  \n \
   $dir_mode=shift (@list);\n\n    \n    if ( $dir\
_mode eq \"set\")\n      {\n	$initial_dir=cwd();\n\
	if ( !$tmp_dir)\n	  {\n	    $rand=rand (100000);\\
n	    $tmp_dir=\"$TMPDIR/tmp4tcoffee_profile_pair_\
dir_$$\\_P_$rand\";\n	  }\n	if ( !-d $tmp_dir)\n	 \
 {\n	    push (@TMPDIR_LIST, $tmp_dir);\n	    `mkd\
ir $tmp_dir`;\n	  }\n	\n	for ( $a=0; $a<=$#list; $\
a+=2)\n	      {\n		if (-e $list[$a]){ `cp $list[$a\
] $tmp_dir/$list[$a+1]`;}\n	      }\n	chdir $tmp_d\
ir;\n      }\n    elsif ( $dir_mode eq \"unset\")\\
n      {\n	$mode=shift (@list);\n	$method=shift (@\
list);\n	\n	if (!-e $list[0])\n	  {\n	   myexit(fl\
ush_error(\"Program $method failed to produce $lis\
t[1]\" ));\n	    myexit ($EXIT_FAILURE);\n	  }\n	e\
lse\n	  {\n	    chdir $initial_dir;\n	    # `t_cof\
fee -other_pg seq_reformat -in $tmp_dir/$list[0] -\
output fasta_aln -out $tmp_dir/result2.aln`;\n	   \
 `cp $tmp_dir/$list[0] $tmp_dir/result2.aln`;\n	  \
  if ( $list[1] eq \"stdout\")\n	      {\n		open (\
F, \"$tmp_dir/result2.aln\");\n		while (<F>){print\
 $_;}close(F);\n	      }\n	    else\n	      {\n		`\
mv $tmp_dir/result2.aln $list[1]`;\n	      }\n	   \
 shift (@list); shift (@list);\n	    foreach $f (@\
list)\n	      {\n		if (-e (\"$tmp_dir/$f\")){`mv $\
tmp_dir/$f .`;}\n	      }\n	  }\n      }\n  }\n\n\\
n\n\nsub my_get_opt\n  {\n    my @list=@_;\n    my\
 $cl, $a, $argv, @argl;\n    \n    @argl=();\n    \
$cl=shift @list;\n    for ( $a=0; $a<=$#list; $a+=\
3)\n      {\n	$option=$list[$a];\n	$optional=$list\
[$a+1];\n	$status=$list[$a+2];\n	$argv=\"\";\n	if \
($cl=~/$option(\\S+)/){$argv=$1;}\n	@argl=(@argl,$\
argv);\n	\n	\n	#$optional:0=>optional\n	#$optional\
:1=>must be set\n	#$status: 0=>no requirement\n	#$\
status: 1=>must be an existing file\n	#$status: 2=\
>must be an installed package\n	\n\n	if ($optional\
==0){;}\n	elsif ( $optional==1 && $argv eq \"\")\n\
	  {\n	    myexit(flush_error( \"ERROR: Option $op\
tion must be set\"));\n	    myexit ($EXIT_FAILURE)\
;\n	  }\n	if ($status==0){;}\n	elsif ($status ==1 \
&& $argv ne \"\" && !-e $argv)\n	  {\n	    myexit(\
flush_error( \"File $argv must exist\"));\n	    my\
exit ($EXIT_FAILURE);\n	  }\n	elsif ( $status==2 &\
& $argv ne \"\" && &check_pg_is_installed ($argv)=\
=0)\n	  {\n	    myexit(flush_error( \" $argv is no\
t installed\"));\n	    myexit ($EXIT_FAILURE);\n	 \
 }\n      }\n\n    return @argl;\n    }\n\nsub che\
ck_file \n  {\n    my ($file, $msg)=@_;\n\n    if \
( !-e $file)\n      {\n	myexit(flush_error(\"$msg\\
"));\n      }\n    }\nsub hhalign\n  {\n    my ($a\
ln1, $aln2, $outfile, $param)=@_;\n    my $h1, $h2\
;\n    \n    $h{0}{index}=0;\n    $h{1}{index}=1;\\
n    \n    $h{0}{aln}=$aln1;\n    $h{1}{aln}=$aln2\
;\n\n   \n\n    %{$h{0}}=aln2psi_profile (%{$h{0}}\
);\n    %{$h{1}}=aln2psi_profile (%{$h{1}});\n\n  \
  $param=~s/#S/ /g;\n    $param=~s/#M/\\-/g;\n    \
$param=~s/#E/\\=/g;\n    \n\n    \n    $command=\"\
hhalign -i $h{0}{a3m} -t $h{1}{a3m} -tc $outfile.t\
mp -rank 1 -mapt 0 $param\";\n    `$command`;\n   \
 \n  #  `hhalign -i $h{0}{a3m} -t $h{1}{a3m} -tc $\
outfile.tmp -rank 1 -mapt 0 -gapf 0.8 -gapg 0.8`;\\
n    \n\n    # To run global use the following\n  \
  \n    open (I, \"$outfile.tmp\");\n    open (O, \
\">$outfile\");\n    $h{0}{cons}=s/\\./x/g;\n    $\
h{1}{cons}=s/\\./x/g;\n\n    print O \"! TC_LIB_FO\
RMAT_01\\n2\\n$h{0}{name} $h{0}{len} $h{0}{seq}\\n\
$h{1}{name} $h{1}{len} $h{1}{seq}\\n#1 2\\n\";\n  \
  \n    while (<I>)\n      {\n	if (/(\\d+)\\s+(\\d\
+)\\s+(\\d+)/)\n	  {\n	    print O \"\\t$h{0}{$1}\\
\t$h{1}{$2}\\t$3\\n\";\n	  }\n      }\n    print O\
 \"! SEQ_1_TO_N\\n\";\n\n    close (O);\n    close\
 (I);\n  }\n\nsub aln2psi_profile\n  {\n    my (%h\
)=@_;\n    my ($aln,$i,$hv, $a, @c, $n);\n   \n   \
 $i=$h{index};\n    $aln=$h{aln};\n\n    `cp $aln \
$$.hhh_aln`;\n    $command=\"t_coffee -other_pg se\
q_reformat -in $aln -output hasch\";\n    $hv=`$co\
mmand`;chomp ($hv);\n    \n    $h{a2m}=\"$tmp/$hv.\
tmp4hhpred.a2m\";\n    $h{a3m}=\"$tmp/$hv.tmp4hhpr\
ed.a3m\";\n    if ( -e $h{a3m}){;}\n    else\n    \
  {\n	`hhconsensus  -M 50 -i $h{aln} -oa2m $h{a2m}\
`;\n	if (!-e $h{a2m})\n	  {\n	    print STDERR \"P\
rogram tc_generic_method.pl FAILED to run:\\n\\thh\
consensus  -M 50 -i $h{aln} -oa2m $h{a2m}\";\n	   \
 myexit ($EXIT_FAILURE);\n	  }\n	\n	`hhconsensus  \
-M 50 -i $h{aln} -oa3m $h{a3m}`;\n	if (!-e $h{a3m}\
)\n	  {\n	    print STDERR \"Program tc_generic_me\
thod.pl FAILED to run:\\n\\thhconsensus  -M 50 -i \
$h{aln} -oa3m $h{a3m}\";\n	    myexit ($EXIT_FAILU\
RE);\n	  }\n       `buildali.pl $h{a3m} -n 1`;\n  \
    }\n    \n    \n    $h{a2m_seq}=`head -n 2 $h{a\
2m} | grep -v \">\"`;chomp ($h{a2m_seq});\n    $h{\
a3m_seq}=`head -n 2 $h{a3m} | grep -v \">\"`;chomp\
 ($h{a3m_seq});\n    $h{cons}=$h{a2m_seq};\n    $h\
{seq}=`head -n 2 $h{aln} | grep -v \">\"`;chomp ($\
h{seq});\n    \n    \n\n    @c=split (//, $h{cons}\
);\n    $h{len}=$#c+1;\n    for ($n=0,$a=0, $b=0; \
$a<$h{len};$a++)\n      {\n	if ( $c[$a]=~/[A-Z]/)\\
n	  {\n	    $h{++$n}=++$b;\n\n	  }\n	elsif ( $c[$a\
]=~/[a-z\\.]/)\n	  {\n	    ++$b;\n	  }\n      }\n \
   \n    $name=`head -n 2 $h{aln} | grep \">\"`;\n\
    $name=~/\\>(\\S+)/;\n    $h{name}=$1;\n    \n \
   `cp $h{a2m} $i.a2m`;\n    `cp $h{a3m} $i.a3m`;\\
n    `cp $h{aln} $i.hh_aln`;\n    \n    return %h;\
\n  }\n\nsub read_fasta_seq \n  {\n    my $f=@_[0]\
;\n    my %hseq;\n    my (@seq, @com, @name);\n   \
 my ($a, $s,$nseq);\n\n    open (F, $f);\n    whil\
e (<F>)\n      {\n	$s.=$_;\n      }\n    close (F)\
;\n\n    \n    @name=($s=~/>(\\S*).*\\n[^>]*/g);\n\
    \n    @seq =($s=~/>.*.*\\n([^>]*)/g);\n    @co\
m =($s=~/>\\S*(.*)\\n([^>]*)/g);\n\n    \n    $nse\
q=$#name+1;\n    \n    for ($a=0; $a<$nseq; $a++)\\
n      {\n	my $s;\n	my $n=$name[$a];\n	$hseq{$n}{n\
ame}=$n;\n	$seq[$a]=~s/[^A-Za-z]//g;\n	$hseq{$n}{o\
rder}=$a;\n	$hseq{$n}{seq}=$seq[$a];\n	$hseq{$n}{c\
om}=$com[$a];\n	\n      }\n    return %hseq;\n  }\\
n\nsub file_contains \n  {\n    my ($file, $tag, $\
max)=(@_);\n    my ($n);\n    $n=0;\n    \n    if \
( !-e $file && ($file =~/$tag/)) {return 1;}\n    \
elsif ( !-e $file){return 0;}\n    else \n      {\\
n	open (FC, \"$file\");\n	while ( <FC>)\n	  {\n	  \
  if ( ($_=~/$tag/))\n	      {\n		close (FC);\n		r\
eturn 1;\n	      }\n	    elsif ($max && $n>$max)\n\
	      {\n		close (FC);\n		return 0;\n	      }\n	 \
   $n++;\n	  }\n      }\n    close (FC);\n    retu\
rn 0;\n  }\n	    \n	  \nsub file2string\n  {\n    \
my $f=@_[0];\n    my $string, $l;\n    open (F,\"$\
f\");\n    while (<F>)\n      {\n\n	$l=$_;\n	#chom\
p ($l);\n	$string.=$l;\n      }\n    close (F);\n \
   $string=~s/\\r\\n//g;\n    $string=~s/\\n//g;\n\
    return $string;\n  }\n\n\nsub my_get_opt\n  {\\
n    my @list=@_;\n    my $cl, $a, $argv, @argl;\n\
    \n    @argl=();\n    $cl=shift @list;\n    for\
 ( $a=0; $a<=$#list; $a+=3)\n      {\n	$option=$li\
st[$a];\n	$optional=$list[$a+1];\n	$status=$list[$\
a+2];\n	$argv=\"\";\n	if ($cl=~/$option(\\S+)/){$a\
rgv=$1;}\n	@argl=(@argl,$argv);\n	\n	\n	#$optional\
:0=>optional\n	#$optional:1=>must be set\n	#$statu\
s: 0=>no requirement\n	#$status: 1=>must be an exi\
sting file\n	#$status: 2=>must be an installed pac\
kage\n	\n\n	if ($optional==0){;}\n	elsif ( $option\
al==1 && $argv eq \"\")\n	  {\n\n	    myexit(flush\
_error(\"Option $option must be set\"));\n	   \n	 \
 }\n	if ($status==0){;}\n	elsif ($status ==1 && $a\
rgv ne \"\" && !-e $argv)\n	  {\n	     myexit(flus\
h_error(\"File $argv must exist\"));\n	   \n	  }\n\
	elsif ( $status==2 && $argv ne \"\" && &check_pg_\
is_installed ($argv)==0)\n	  {\n	    myexit(flush_\
error(\"$argv is not installed\"));\n	   \n	  }\n \
     }\n\n    return @argl;\n    }\n\nsub tag2valu\
e \n  {\n    \n    my $tag=(@_[0]);\n    my $word=\
(@_[1]);\n    my $return;\n    \n    $tag=~/$word=\
\"([^\"]+)\"/;\n    $return=$1;\n    return $retur\
n;\n  }\n      \nsub hit_tag2pdbid\n  {\n    my $t\
ag=(@_[0]);\n    my $pdbid;\n       \n    $tag=~/i\
d=\"(\\S+)\"/;\n    $pdbid=$1;\n    $pdbid=~s/_//;\
\n    return $pdbid;\n  }\nsub id2pdbid\n  {\n    \
my $in=@_[0];\n    my $id;\n    \n    $in=~/(\\S+)\
/;\n    $id=$in;\n    $id=~s/PDB/pdb/g;\n    \n   \
 if ($id =~/pdb(.*)/){$id=$1;}\n    elsif ( $id=~/\
(\\S+)\\s+mol:protein/){$id=$1;}\n    $id=~s/[:|�\
��_]//g;\n    return $id;\n  }\nsub set_blast_ty\
pe \n  {\n    my $file =@_[0];\n    if (&file_cont\
ains ($file,\"EBIApplicationResult\",100)){$BLAST_\
TYPE=\"EBI\";}\n    elsif (&file_contains ($file,\\
"NCBI_BlastOutput\",100)) {$BLAST_TYPE=\"NCBI\";}\\
n    else\n      {\n	$BLAST_TYPE=\"\";\n      }\n \
   return $BLAST_TYPE;\n  }\nsub is_valid_blast_xm\
l\n    {\n      my $file=shift;\n      my $line;\n\
      \n      \n      if ( !-e $file) {return 0;}\\
n      $line=&file2tail ($file,100);\n      if ( $\
line=~/<\\/EBIApplicationResult/ || $line=~/<\\/NC\
BI_BlastOutput/ || $line=~/<\\/BlastOutput/ ){retu\
rn 1;}\n      return 0;\n    }\nsub file2blast_fla\
vor\n      {\n	my $file=shift;\n	if (&file_contain\
s ($file,\"EBIApplicationResult\",100)){return \"E\
BI\";}\n	elsif (&file_contains ($file,\"NCBI_Blast\
Output\",100)){return \"NCBI\";}\n	else {return \"\
UNKNOWN\";}\n      }\nsub blast_xml2profile \n  {\\
n    my ($name,$seq,$maxid, $minid, $mincov, $file\
)=(@_);\n    my (%p, $a, $string, $n);\n    \n    \
\n\n    if ($BLAST_TYPE eq \"EBI\" || &file_contai\
ns ($file,\"EBIApplicationResult\",100)){%p=ebi_bl\
ast_xml2profile(@_);}\n    elsif ($BLAST_TYPE eq \\
"NCBI\" || &file_contains ($file,\"NCBI_BlastOutpu\
t\",100)){%p=ncbi_blast_xml2profile(@_);}\n    els\
e \n      {\n	myexit(add_error ( $$,$$,getppid(), \
\"BLAST_FAILURE::unkown XML\",$CL));\n      }\n   \
 for ($a=0; $a<$p{n}; $a++)\n      {\n	my $name=$p\
{$a}{name};\n	$p{$name}{seq}=$p{$a}{seq};\n	$p{$na\
me}{index}=$a;\n      }\n    return %p;\n  }\nsub \
ncbi_tblastx_xml2lib_file \n  {\n    my  ($outlib,\
$string)=(@_);\n    my ($L,$l, $a,$b,$c,$d,$i,$nhi\
ts,@identifyerL);\n    my (%ITERATION);\n      \n \
   open (F, \">>$outlib\");\n    \n    $seq=~s/[^a\
-zA-Z]//g;\n    $L=length ($seq);\n    \n    %ITER\
ATION=xml2tag_list ($string, \"Iteration\");\n    \
for ($i=0; $i<$ITERATION{n};$i++)\n      {\n	my ($\
qindex, $qlen, %hit, $string);\n	$string=$ITERATIO\
N{$i}{body};\n\n	$qindex=xmltag2value($string,\"It\
eration_iter-num\");\n	$qlen  =xmltag2value($strin\
g,\"Iteration_query-len\");\n	%hit=&xml2tag_list  \
($string, \"Hit\");\n\n	for ($a=0; $a<$hit{n}; $a+\
+)\n	  {\n	    my ($string);\n	    $string=$hit{$a\
}{body};\n	 \n	    $hindex=xmltag2value($string,\"\
Hit_accession\")+1;\n	    if ($hindex<=$qindex){ne\
xt;}\n	    else  {print F  \"# $qindex $hindex\\n\\
";}\n		   \n	   \n	    $hlen=xmltag2value  ($strin\
g,\"Hit_len\");\n	    %HSP=&xml2tag_list  ($string\
, \"Hsp\");\n	   \n	    for ($b=0; $b<$HSP{n}; $b+\
+)\n	      {\n		my ($string, $qs,$qe,$qf,$hs,$he,$\
hf,$s, $d, $e);\n		$string=$HSP{$b}{body};\n	\n		$\
qs=xmltag2value  ($string,\"Hsp_query-from\");\n		\
$qe=xmltag2value  ($string,\"Hsp_query-to\");\n		$\
qf=xmltag2value  ($string,\"Hsp_query-frame\");\n\\
n		$hs=xmltag2value  ($string,\"Hsp_hit-from\");\n\
		$he=xmltag2value  ($string,\"Hsp_hit-to\");\n		$\
hf=xmltag2value  ($string,\"Hsp_hit-frame\");\n		\\
n		$s=xmltag2value  ($string,\"Hsp_identity\");\n	\
	$l=xmltag2value  ($string,\"Hsp_align-len\");\n		\
$s=int(($s*100)/$l);\n		\n		if ($qf>0)\n		  {$rqs=\
$qs; $rqe=$qe;}\n		else\n		  {\n		    $rqe=($qlen-\
$qs)+1;\n		    $rqs=($qlen-$qe)+1;\n		  }\n		\n		i\
f ($hf>0)\n		  {$rhs=$hs; $rhe=$he;}\n		else\n		  \
{\n		    $rhe=($hlen-$hs)+1;\n		    $rhs=($hlen-$h\
e)+1;\n		  }\n		for ($d=0,$e=$rqs; $e<$rqe; $e++,$\
d++)\n		  {\n		    my ($r1,$r2);\n		    $r1=$e;\n	\
	    $r2=$rhs+$d;\n		    print F \" $r1 $r2 $s 0\\\
n\";\n		  }\n	      }\n	  }\n      }\n    print F \
\"! SEQ_1_TO_N\\n\";\n    \n    close (F);\n    re\
turn %lib;\n  }\n\nsub ncbi_tblastpx_xml2lib_file \
\n  {\n    my  ($outlib,$string,%s)=(@_);\n    my \
($L,$l, $a,$b,$c,$d,$i,$nhits,@identifyerL);\n    \
my (%ITERATION,%hdes, %qdes);\n      \n    open (F\
, \">>$outlib\");\n    \n    $seq=~s/[^a-zA-Z]//g;\
\n    $L=length ($seq);\n    \n    %ITERATION=xml2\
tag_list ($string, \"Iteration\");\n    for ($i=0;\
 $i<$ITERATION{n};$i++)\n      {\n	my ($qindex, $q\
len, %hit, $string);\n	$string=$ITERATION{$i}{body\
};\n\n	$qdef=xmltag2value($string,\"Iteration_quer\
y-def\");\n	%qdes=&tblastpx_name2description($qdef\
,%s);\n	$qlen  =xmltag2value($string,\"Iteration_q\
uery-len\");\n	%hit=&xml2tag_list  ($string, \"Hit\
\");\n\n	for ($a=0; $a<$hit{n}; $a++)\n	  {\n	    \
my ($string);\n	    $string=$hit{$a}{body};\n	    \
$hdef=xmltag2value($string,\"Hit_def\");\n	    %hd\
es=&tblastpx_name2description($hdef,%s);\n	    if \
($hdes{index}<=$qdes{index}){next;}\n	    else  {p\
rint F  \"# $qdes{index} $hdes{index}\\n\";}\n		  \
 \n	   \n	    $hlen=xmltag2value  ($string,\"Hit_l\
en\");\n	    %HSP=&xml2tag_list  ($string, \"Hsp\"\
);\n	   \n	    for ($b=0; $b<$HSP{n}; $b++)\n	    \
  {\n		my ($string, $l,$qs,$qe,$qf,$hs,$he,$hf,$s,\
 $d, $e, @s1, @s2);\n		$string=$HSP{$b}{body};\n	\\
n		$qs=xmltag2value  ($string,\"Hsp_query-from\");\
\n		$qe=xmltag2value  ($string,\"Hsp_query-to\");\\
n		$qf=$qdes{frame};\n		$qseq=xmltag2value  ($stri\
ng,\"Hsp_qseq\");\n		\n		$hs=xmltag2value  ($strin\
g,\"Hsp_hit-from\");\n		$he=xmltag2value  ($string\
,\"Hsp_hit-to\");\n		$hf=$hdes{frame};\n		$hseq=xm\
ltag2value  ($string,\"Hsp_hseq\");\n		\n		$s=xmlt\
ag2value  ($string,\"Hsp_identity\");\n		$l=xmltag\
2value  ($string,\"Hsp_align-len\");\n		$s=int(($s\
*100)/$l);\n		@s1=tblastpx_hsp2coordinates($qseq,$\
qs,$qe,%qdes);\n		@s2=tblastpx_hsp2coordinates($hs\
eq,$hs,$he,%hdes);\n		\n		\n		for ($f=0; $f<=$#s1;\
 $f++)\n		  {\n		    if ($s1[$f]==-1 || $s2[$f]==-\
1){next;}\n		    else \n		      {\n			print F \" $\
s1[$f] $s2[$f] $s 0\\n\";\n		      }\n		  }\n	    \
  }\n	  }\n      }\n    print F \"! SEQ_1_TO_N\\n\\
";\n    \n    close (F);\n    return %lib;\n  }\ns\
ub tblastpx_hsp2coordinates\n  {\n    my ($seq, $s\
, $e, %des)=@_;\n    my @list;\n    my @sa;\n    m\
y @gap=(-1,-1,-1);\n    \n    $s=$des{start}+3*($s\
-1);\n  \n    if ($des{strand} eq \"d\"){;}\n    e\
lse {$s=($des{length}-$s)+1;}\n    \n    foreach $\
c (split (//,$seq))\n      {\n	if ( $c eq '-'){pus\
h (@list,@gap);}\n	elsif ($des{strand} eq \"d\")\n\
	  {\n	    push(@list,$s++,$s++,$s++);\n	  }\n	els\
e\n	  {\n	    push(@list, $s--,$s--,$s--);\n	  }\n\
      }\n    return @list;\n  }\n\nsub tblastpx_na\
me2description\n  {\n    my ($name, %s)=@_;\n    m\
y @at=split(\"__\", $name);\n    my %des;\n\n    $\
des{name}=$at[0];\n    $des{strand}=$at[1];\n    \\
n    $des{start}=$at[2];\n    $des{end}=$at[3];\n \
   $des{length}=$at[4];\n    $des{index}=$s{$at[0]\
}{order}+1;\n    return %des;\n  }  \nsub ncbi_bla\
st_xml2profile \n  {\n    my ($name,$seq,$maxid, $\
minid, $mincov, $string)=(@_);\n    my ($L,$l, $a,\
$b,$c,$d,$nhits,@identifyerL);\n    \n    \n    $s\
eq=~s/[^a-zA-Z]//g;\n    $L=length ($seq);\n   \n \
   #This is causing the NCBI parser to fail when I\
teration_query-def is missing \n    #%query=&xml2t\
ag_list ($string, \"Iteration_query-def\");\n    #\
$name=$query{0}{body};\n    \n    %hit=&xml2tag_li\
st ($string, \"Hit\");\n    \n    \n    for ($nhit\
s=0,$a=0; $a<$hit{n}; $a++)\n      {\n	my ($ldb,$i\
d, $identity, $expectation, $start, $end, $coverag\
e, $r);\n	my (%ID,%DE,%HSP);\n	\n	$ldb=\"\";\n\n	%\
ID=&xml2tag_list ($hit{$a}{body}, \"Hit_id\");\n	$\
identifyer=$ID{0}{body};\n	\n	%DE=&xml2tag_list ($\
hit{$a}{body}, \"Hit_def\");\n	$definition=$DE{0}{\
body};\n	\n	%HSP=&xml2tag_list ($hit{$a}{body}, \"\
Hsp\");\n	for ($b=0; $b<$HSP{n}; $b++)\n	  {\n	   \
 my (%START,%END,%E,%I,%Q,%M);\n\n	 \n	    %START=\
&xml2tag_list ($HSP{$b}{body}, \"Hsp_query-from\")\
;\n	    %HSTART=&xml2tag_list ($HSP{$b}{body}, \"H\
sp_hit-from\");\n	    \n	    %LEN=  &xml2tag_list \
($HSP{$b}{body}, \"Hsp_align-len\");\n	    %END=  \
&xml2tag_list ($HSP{$b}{body}, \"Hsp_query-to\");\\
n	    %HEND=  &xml2tag_list ($HSP{$b}{body}, \"Hsp\
_hit-to\");\n	    %E=&xml2tag_list     ($HSP{$b}{b\
ody}, \"Hsp_evalue\");\n	    %I=&xml2tag_list     \
($HSP{$b}{body}, \"Hsp_identity\");\n	    %Q=&xml2\
tag_list     ($HSP{$b}{body}, \"Hsp_qseq\");\n	   \
 %M=&xml2tag_list     ($HSP{$b}{body}, \"Hsp_hseq\\
");\n	    \n	    for ($e=0; $e<$Q{n}; $e++)\n\n	  \
    {\n		$qs=$Q{$e}{body};\n		$ms=$M{$e}{body};\n	\
	\n		$expectation=$E{$e}{body};\n		$identity=($LEN\
{$e}{body}==0)?0:$I{$e}{body}/$LEN{$e}{body}*100;\\
n		$start=$START{$e}{body};\n		$end=$END{$e}{body}\
;\n		$Hstart=$HSTART{$e}{body};\n		$Hend=$HEND{$e}\
{body};\n	\n		$coverage=($L)?(($end-$start)*100)/$\
L:0;\n	\n		if ($identity>$maxid || $identity<$mini\
d || $coverage<$mincov){next;}\n		@lr1=(split (//,\
$qs));\n		@lr2=(split (//,$ms));\n		$l=$#lr1+1;\n	\
	for ($c=0;$c<$L;$c++){$p[$nhits][$c]=\"-\";}\n		f\
or ($d=0,$c=0; $c<$l; $c++)\n		  {\n		    $r=$lr1[\
$c];\n		    if ( $r=~/[A-Za-z]/)\n		      {\n			\n\
			$p[$nhits][$d + $start-1]=$lr2[$c];\n			$d++;\n\
		      }\n		  }\n		$Qseq[$nhits]=$qs;\n		$Hseq[$n\
hits]=$ms;\n		$QstartL[$nhits]=$start;\n		$HstartL\
[$nhits]=$Hstart;\n		$identityL[$nhits]=$identity;\
\n		$endL[$nhits]=$end;\n		$definitionL[$nhits]=$d\
efinition;\n		$identifyerL[$nhits]=$identifyer;\n	\
	$comment[$nhits]=\"$ldb|$identifyer [Eval=$expect\
ation][id=$identity%][start=$Hstart end=$Hend]\";\\
n		$nhits++;\n	      }\n	  }\n      }\n    \n    \\
n    $profile{n}=0;\n    $profile{$profile{n}}{nam\
e}=$name;\n    $profile{$profile{n}}{seq}=$seq;\n \
   $profile {n}++;\n    \n    for ($a=0; $a<$nhits\
; $a++)\n      {\n	$n=$a+1;\n	\n	$profile{$n}{name\
}=\"$name\\_$a\";\n	$profile{$n}{seq}=\"\";\n	$pro\
file{$n}{Qseq}=$Qseq[$a];\n	$profile{$n}{Hseq}=$Hs\
eq[$a];\n	$profile{$n}{Qstart}=$QstartL[$a];\n	$pr\
ofile{$n}{Hstart}=$HstartL[$a];\n	$profile{$n}{ide\
ntity}=$identityL[$a];\n	$profile{$n}{definition}=\
$definitionL[$a];\n	$profile{$n}{identifyer}=$iden\
tifyerL[$a];\n	$profile{$n}{comment}=$comment[$a];\
\n\n	for ($b=0; $b<$L; $b++)\n	  {\n	    if ($p[$a\
][$b])\n	      {\n		$profile{$n}{seq}.=$p[$a][$b];\
\n	      }\n	    else\n	      {\n		$profile{$n}{se\
q}.=\"-\";\n	      }\n	  }\n      }\n    \n    $pr\
ofile{n}=$nhits+1;\n    return %profile;\n  }\nsub\
 ebi_blast_xml2profile \n  {\n    my ($name,$seq,$\
maxid, $minid, $mincov, $string)=(@_);\n    my ($L\
,$l, $a,$b,$c,$d,$nhits,@identifyerL,$identifyer);\
\n    \n\n    \n    $seq=~s/[^a-zA-Z]//g;\n    $L=\
length ($seq);\n    %hit=&xml2tag_list ($string, \\
"hit\");\n    \n    for ($nhits=0,$a=0; $a<$hit{n}\
; $a++)\n      {\n	my ($ldb,$id, $identity, $expec\
tation, $start, $end, $coverage, $r);\n	my (%Q,%M,\
%E,%I);\n	\n	$ldb=&tag2value ($hit{$a}{open}, \"da\
tabase\");\n	$identifyer=&tag2value ($hit{$a}{open\
}, \"id\");\n\n	$description=&tag2value ($hit{$a}{\
open}, \"description\");\n	\n	%Q=&xml2tag_list ($h\
it{$a}{body}, \"querySeq\");\n	%M=&xml2tag_list ($\
hit{$a}{body}, \"matchSeq\");\n	%E=&xml2tag_list (\
$hit{$a}{body}, \"expectation\");\n	%I=&xml2tag_li\
st ($hit{$a}{body}, \"identity\");\n	\n\n	for ($b=\
0; $b<$Q{n}; $b++)\n	  {\n\n	    $qs=$Q{$b}{body};\
\n	    $ms=$M{$b}{body};\n	    \n	    $expectation\
=$E{$b}{body};\n	    $identity=$I{$b}{body};\n	   \
 \n	    	    \n	    $start=&tag2value ($Q{$b}{open\
}, \"start\");\n	    $end=&tag2value ($Q{$b}{open}\
, \"end\");\n	    $startM=&tag2value ($M{$b}{open}\
, \"start\");\n	    $endM=&tag2value ($M{$b}{open}\
, \"end\");\n	    $coverage=(($end-$start)*100)/$L\
;\n	    \n	   # print \"$id: ID: $identity COV: $c\
overage [$start $end]\\n\";\n	    \n	    if ($iden\
tity>$maxid || $identity<$minid || $coverage<$minc\
ov){next;}\n	    # print \"KEEP\\n\";\n\n	    \n	 \
   @lr1=(split (//,$qs));\n	    @lr2=(split (//,$m\
s));\n	    $l=$#lr1+1;\n	    for ($c=0;$c<$L;$c++)\
{$p[$nhits][$c]=\"-\";}\n	    for ($d=0,$c=0; $c<$\
l; $c++)\n	      {\n		$r=$lr1[$c];\n		if ( $r=~/[A\
-Za-z]/)\n		  {\n		    \n		    $p[$nhits][$d + $st\
art-1]=$lr2[$c];\n		    $d++;\n		  }\n	      }\n	 \
 \n	    $Qseq[$nhits]=$qs;\n	    $Hseq[$nhits]=$ms\
;\n	    $QstartL[$nhits]=$start;\n	    $HstartL[$n\
hits]=$Hstart;\n	    $identityL[$nhits]=$identity;\
\n	    $endL[$nhits]=$end;\n	    $definitionL[$nhi\
ts]=$definition;\n	    $identifyerL[$nhits]=$ident\
ifyer;\n	    $comment[$nhits]=\"$ldb|$identifyer [\
Eval=$expectation][id=$identity%][start=$startM en\
d=$endM]\";\n	    $nhits++;\n	  }\n      }\n    \n\
    $profile{n}=0;\n    $profile{$profile{n}}{name\
}=$name;\n    $profile{$profile{n}}{seq}=$seq;\n  \
  $profile {n}++;\n    \n    for ($a=0; $a<$nhits;\
 $a++)\n      {\n	$n=$a+1;\n	$profile{$n}{name}=\"\
$name\\_$a\";\n	$profile{$n}{seq}=\"\";\n	$profile\
{$n}{Qseq}=$Qseq[$a];\n	$profile{$n}{Hseq}=$Hseq[$\
a];\n	$profile{$n}{Qstart}=$QstartL[$a];\n	$profil\
e{$n}{Hstart}=$HstartL[$a];\n	$profile{$n}{identit\
y}=$identityL[$a];\n	$profile{$n}{definition}=$def\
initionL[$a];	\n	$profile{$n}{identifyer}=$identif\
yerL[$a];\n	$profile{$n}{comment}=$comment[$a];\n\\
n	for ($b=0; $b<$L; $b++)\n	  {\n	    if ($p[$a][$\
b])\n	      {\n		$profile{$n}{seq}.=$p[$a][$b];\n	\
      }\n	    else\n	      {\n		$profile{$n}{seq}.\
=\"-\";\n	      }\n	  }\n      }\n    $profile{n}=\
$nhits+1;\n    \n    return %profile;\n  }\nsub ou\
tput_profile\n  {\n    my ($outfile,$profileR, $tr\
im)=(@_);\n    my ($a);\n    my %profile=%$profile\
R;\n    my $P= new FileHandle;\n    my $tmp=vtmpna\
m();\n    \n    open ($P, \">$tmp\");\n    for ($a\
=0; $a<$profile{n}; $a++)\n      {\n	print $P \">$\
profile{$a}{name} $profile{$a}{comment}\\n$profile\
{$a}{seq}\\n\";\n      }\n    close ($P);\n\n    i\
f ( $trim)\n      {\n	&safe_system (\"t_coffee -ot\
her_pg seq_reformat -in $tmp -action +trim _aln_%%\
$trim\\_K1 -output fasta_aln -out $outfile\");\n  \
    }\n    else\n      {\n	&safe_system (\"mv $tmp\
 $outfile\");\n      }\n    return;\n  }\nsub blas\
t_xml2hit_list\n  {\n    my $string=(@_[0]);\n    \
return &xml2tag_list ($string, \"hit\");\n  }\nsub\
 xmltag2value\n  {\n    my ($string_in, $tag)=@_;\\
n    my %TAG;\n    %TAG=xml2tag_list ($string_in, \
$tag);\n    return $TAG{0}{body};\n  }\n      \nsu\
b xml2tag_list  \n  {\n    my ($string_in,$tag)=@_\
;\n    my $tag_in, $tag_out;\n    my %tag;\n    \n\
    if (-e $string_in)\n      {\n	$string=&file2st\
ring ($string_in);\n      }\n    else\n      {\n	$\
string=$string_in;\n      }\n    $tag_in1=\"<$tag \
\";\n    $tag_in2=\"<$tag>\";\n    $tag_out=\"/$ta\
g>\";\n    $string=~s/>/>##1/g;\n    $string=~s/</\
##2</g;\n    $string=~s/##1/<#/g;\n    $string=~s/\
##2/#>/g;\n    @l=($string=~/(\\<[^>]+\\>)/g);\n  \
  $tag{n}=0;\n    $in=0;$n=-1;\n  \n \n\n    forea\
ch $t (@l)\n      {\n\n	$t=~s/<#//;\n	$t=~s/#>//;\\
n	\n	if ( $t=~/$tag_in1/ || $t=~/$tag_in2/)\n	  {\\
n	 \n	    $in=1;\n	    $tag{$tag{n}}{open}=$t;\n	 \
   $n++;\n	    \n	  }\n	elsif ($t=~/$tag_out/)\n	 \
 {\n	    \n\n	    $tag{$tag{n}}{close}=$t;\n	    $\
tag{n}++;\n	    $in=0;\n	  }\n	elsif ($in)\n	  {\n\
	   \n	    $tag{$tag{n}}{body}.=$t;\n	  }\n      }\
\n  \n    return %tag;\n  }\n\n\nsub seq2gor_predi\
ction \n  {\n    my ($name, $seq,$infile, $outfile\
, $gor_seq, $gor_obs)=(@_);\n    my ($l);\n    \n \
   `gorIV -prd $infile -seq $gor_seq -obs $gor_obs\
 > gor_tmp`;\n    open (GR, \">$outfile\");\n    o\
pen (OG, \"gor_tmp\");\n\n    while (<OG>)\n      \
{\n	\n	$l=$_;\n	if ($l=~/\\>/){print GR \"$l\";}\n\
	elsif ( $l=~/Predicted Sec. Struct./)\n	  {\n	   \
 $l=~s/Predicted Sec. Struct\\.//;\n	    print GR \
\"$l\";\n	  }\n      }\n    close (GR);\n    close\
 (OG);\n    return;\n  }\nsub seq2msa_tm_predictio\
n \n  {\n    my ($name, $seq, $db, $infile, $outfi\
le, $arch, $psv)=(@_);\n    my (%p,%gseq,%R, $blas\
t_output, %s, $l);\n    my $R2=new FileHandle;\n  \
  my $db=\"uniprot\";\n    my $method=\"psitm\";\n\
    my $SERVER=\"EBI\";\n    \n    $blast_output=&\
run_blast ($name,\"blastp\", $db, $infile, \"outfi\
le\");\n    \n    if (&cache_file(\"GET\",$infile,\
$name,$method,$db,$outfile,$SERVER))\n      {\n	pr\
int \"\\tPSITM: USE Cache\\n\";\n	return $outfile;\
\n      }\n    else\n      {\n	$CACHE_STATUS=\"COM\
PUTE CACHE\";\n	%p=blast_xml2profile($name,$seq,$m\
axid, $minid,$mincov,$blast_output);\n	\n	\n	open \
(F, \">tm_input\");\n	for (my $a=0; $a<$p{n}; $a++\
)\n	  {\n	    my $s;\n	    \n	    $s=$p{$a}{seq};\\
n	    $s=uc($s);\n	    print F \">$p{$a}{name}\\n$\
s\\n\";\n	    #print stdout \">$p{$a}{name}\\n$s\\\
n\";\n	  }\n	close (F);\n	print \"\\tPSITM: kept  \
$p{n} Homologues for Sequence $p{0}{name}\\n\";\n	\
&safe_system (\"t_coffee -other_pg fasta_seq2hmmto\
p_fasta.pl -in=tm_input -out=$outfile -output=cons\
 -cov=70 -trim=95 -arch=$arch -psv=$psv\");\n	unli\
nk (\"tm_input\");\n	&cache_file(\"SET\",$infile,$\
name,$method,$db,$outfile,$SERVER);\n	return;\n   \
   }\n  }\n\n\nsub seq2msa_gor_prediction \n  {\n \
   my ($name, $seq,$infile, $outfile, $gor_seq, $g\
or_obs)=(@_);\n    my (%p,%gseq,%R, $blast_output,\
 %s, $l);\n    my $R2=new FileHandle;\n    my $db=\
\"uniprot\";\n    my $method=\"psigor\";\n    my $\
SERVER=\"EBI\";\n    \n    $blast_output=&run_blas\
t ($name,\"blastp\", \"uniprot\", $infile, \"outfi\
le\");\n    \n    if (&cache_file(\"GET\",$infile,\
$name,$method,$db,$outfile,$SERVER))\n      {\n	pr\
int \"\\tPSIGOR: USE Cache\\n\";\n	return $outfile\
;\n      }\n    else\n      {\n	$CACHE_STATUS=\"CO\
MPUTE CACHE\";\n	%p=blast_xml2profile($name,$seq,$\
maxid, $minid,$mincov,$blast_output);\n	\n	\n	open\
 (F, \">gor_input\");\n	for (my $a=0; $a<$p{n}; $a\
++)\n	  {\n	    my $s;\n	    \n	    $s=$p{$a}{seq}\
;\n	    $s=uc($s);\n	    print F \">$p{$a}{name}\\\
n$s\\n\";\n	    #print stdout \">$p{$a}{name}\\n$s\
\\n\";\n	  }\n	close (F);\n	print \"\\tGORTM: kept\
  $p{n} Homologues for Sequence $p{0}{name}\\n\";\\
n	&safe_system (\"t_coffee -other_pg fasta_seq2hmm\
top_fasta.pl -in=gor_input -out=$outfile -output=c\
ons -cov=70 -trim=95 -gor_seq=$gor_seq -gor_obs=$g\
or_obs -mode=gor\");\n	unlink (\"tm_input\");\n	&c\
ache_file(\"SET\",$infile,$name,$method,$db,$outfi\
le,$SERVER);\n	return;\n      }\n  }\n\n\n\nsub ru\
n_blast\n  {\n    my ($name, $method, $db, $infile\
, $outfile, $run)=(@_);\n    if (!$run){$run=1;}\n\
    \n    \n    if (&cache_file(\"GET\",$infile,$n\
ame,$method,$db,$outfile,$SERVER) && is_valid_blas\
t_xml ($outfile))\n      {return $outfile;}\n    e\
lse\n      {\n	$CACHE_STATUS=\"COMPUTE CACHE\";\n	\
if ( $SERVER eq \"EBI_SOAP\")\n	  {\n	    &check_c\
onfiguration (\"EMAIL\",\"SOAP::Light\",\"INTERNET\
\");\n	    \n	    $cl_method=$method;\n	    if ($c\
l_method =~/wu/)\n	      {\n		$cl_method=~s/wu//;\\
n		if ( $cl_method eq \"psiblast\")\n		  {\n		    \
add_warning($$,$$,\"PSI BLAST cannot be used with \
the wuBLAST Client. Use server=EBI Or server=LOCAL\
. blastp will be used instead\");\n		    $cl_metho\
d=\"blastp\";\n		  }\n		\n		$command=\"t_coffee -o\
ther_pg wublast.pl --email $EMAIL $infile -D $db -\
p $cl_method --outfile $outfile -o xml>/dev/null 2\
>/dev/null\";\n		&safe_system ( $command);\n		if (\
-e \"$outfile.xml\") {`mv $outfile.xml $outfile`;}\
\n	      }\n	    else\n	      {\n		if ($cl_method \
eq \"psiblast\"){$cl_method =\"blastp -j5\";}\n		\\
n		$command=\"t_coffee -other_pg blastpgp.pl --ema\
il $EMAIL $infile -d $db --outfile $outfile -p $cl\
_method --mode PSI-Blast>/dev/null 2>/dev/null\";\\
n		&safe_system ( $command);\n		\n		if (-e \"$outf\
ile.xml\") {`mv $outfile.xml $outfile`;}\n	      }\
\n	  }\n	elsif ($SERVER eq \"EBI_REST\" || $SERVER\
 eq \"EBI\")\n	  {\n	   \n	    $cl_method=$method;\
\n	    &check_configuration(\"EMAIL\",\"XML::Simpl\
e\", \"INTERNET\");\n	    if ($db eq \"uniprot\"){\
$db1=\"uniprotkb\";}\n	    else {$db1=$db;}\n	    \
\n\n	    if ($cl_method =~/wu/)\n	      {\n		$cl_m\
ethod=~s/wu//;\n		if ( $cl_method eq \"psiblast\")\
{$cl_method=\"blastp\";}\n		\n		$command=\"t_coffe\
e -other_pg wublast_lwp.pl --email $EMAIL -D $db1 \
-p $cl_method --outfile $outfile --align 7 --stype\
 protein $infile>/dev/null 2>/dev/null\";\n		\n	  \
    }\n	    else\n	      {\n		if ( $cl_method =~/p\
siblast/){$cl_method =\"blastp -j5\";}\n		$command\
=\"t_coffee -other_pg ncbiblast_lwp.pl --email $EM\
AIL -D $db1 -p $cl_method --outfile $outfile --ali\
gn 7 --stype protein $infile>/dev/null 2>/dev/null\
\";\n	      }\n	    &safe_system ( $command,5);\n	\
    if (-e \"$outfile.out.xml\") {`mv $outfile.out\
.xml $outfile`;}\n	    elsif (-e \"$outfile.xml.xm\
l\"){`mv $outfile.xml.xml $outfile`;}\n	    elsif \
(-e \"$outfile.out..xml\") {`mv $outfile.out..xml \
$outfile`;}\n	    elsif (-e \"$outfile.xml..xml\")\
{`mv $outfile.xml..xml $outfile`;}\n	  }\n	elsif (\
$SERVER eq \"NCBI\")\n	  {\n	    &check_configurat\
ion (\"blastcl3\",\"INTERNET\");\n	    if ($db eq \
\"uniprot\"){$cl_db=\"nr\";}\n	    else {$cl_db=$d\
b;}\n	    \n	    if ( $method eq \"psiblast\")\n	 \
     {\n		add_warning($$,$$,\"PSI BLAST cannot be \
used with the NCBI BLAST Client. Use server=EBI Or\
 server=LOCAL. blastp will be used instead\");\n		\
$cl_method=\"blastp\";\n	      }\n	    else\n	    \
  {\n		$cl_method=$method;\n	      }\n	    $comman\
d=\"blastcl3 -p $cl_method -d $cl_db -i $infile -o\
 $outfile -m 7\";\n	    &safe_system ($command);\n\
	  }\n	elsif ($SERVER =~/CLIENT_(.*)/)\n	  {\n	   \
 my $client=$1;\n	    $command=\"$client -p $metho\
d -d $db -i $infile -o $outfile -m 7\";\n	    &saf\
e_system ($command);\n	  }\n	elsif ( $SERVER eq \"\
LOCAL_blastall\")\n	  {\n	    &check_configuration\
 (\"blastall\");\n	    if ($method eq \"blastp\")\\
n	      {\n		$command=\"blastall -d $db -i $infile\
 -o $outfile -m7 -p blastp\";\n	      }\n	    &saf\
e_system ($command);\n	  }\n	elsif ( $SERVER eq \"\
LOCAL\")\n	  {\n	    \n	    if ($ENV{\"BLAST_DB_DI\
R\"})\n	      {\n		$x=$ENV{\"BLAST_DB_DIR\"};\n		$\
cl_db=\"$x$db\";\n	      }\n	    else\n	      {\n	\
	$cl_db=$db;\n	      }\n	    \n	    if ($method eq\
 \"blastp\")\n	      {\n		&check_configuration(\"b\
lastpgp\");\n		$command=\"blastpgp -d $cl_db -i $i\
nfile -o $outfile -m7 -j1\";\n	      }\n	    elsif\
 ($method eq \"psiblast\")\n	      {\n		&check_con\
figuration(\"blastpgp\");\n		$command=\"blastpgp -\
d $cl_db -i $infile -o $outfile -m7 -j5\";\n	     \
 }\n	    elsif ($method eq \"blastn\")\n	      {\n\
		&check_configuration(\"blastall\");\n		$command=\
\"blastall -p blastn -d $cl_db -i $infile -o $outf\
ile -m7 -W6\";\n	      }	\n	    &safe_system ($com\
mand);\n	  }\n	else\n	  {\n	    \n	    myexit(add_\
error (EXIT_FAILURE,$$,$$,getppid(), \"BLAST_FAILU\
RE::UnknownServer\",$CL));\n	  }\n	\n	if ( !-e $ou\
tfile || !&is_valid_blast_xml($outfile))\n	  {\n	 \
   \n	    if ( -e $outfile)\n	      {\n		add_warni\
ng ($$,$$,\"Corrupted Blast Output (Run $run)\");\\
n		unlink($outfile);\n	      }\n	    \n	    if ( $\
run==$BLAST_MAX_NRUNS)\n	      {\n	\n		myexit(add_\
error (EXIT_FAILURE,$$,$$,getppid(), \"BLAST_FAILU\
RE::UnknownReason\", \"$command\"));\n	      }\n	 \
   else\n	      {\n		my $out;\n		if ($SERVER eq \"\
NCBI\") {$SERVER=\"EBI\"; }\n		elsif ($SERVER eq \\
"EBI\"){$SERVER=\"NCBI\";}\n		add_warning ($$,$$,\\
"Blast for $name failed (Run: $run out of $BLAST_M\
AX_NRUNS. Use $SERVER)\");\n		$out=&run_blast ($na\
me, $method, $db,$infile, $outfile, $run+1);\n		if\
 ($SERVER eq \"NCBI\") {$SERVER=\"EBI\"; }\n		elsi\
f ($SERVER eq \"EBI\"){$SERVER=\"NCBI\";}\n		retur\
n $out;\n	      }\n	  }\n	\n	&cache_file(\"SET\",$\
infile,$name,$method,$db,$outfile,$SERVER);\n	#sys\
tem (\"cp $outfile ~/Dropbox/tmp/cedric.out\");\n	\
#die;\n	return $outfile;\n      }\n  }\n\nsub cach\
e_file\n  {\n    my ($cache_mode,$infile,$name,$me\
thod,$db, $outfile,$server)=(@_);\n    my $cache_f\
ile;\n    #Protect names so that they can be turne\
d into legal filenames\n    $name=&clean_file_name\
 ($name);\n\n    if ($db=~/\\//)\n      {\n	$db=~/\
([^\\/]+)$/;\n	$db=$1;\n      }\n    $cache_file_s\
h=\"$name.$method.$db.$server.tmp\";\n    $cache_f\
ile=\"$CACHE/$name.$method.$db.$server.tmp\";\n   \
 \n    if ($infile ne \"\")\n      {\n	$cache_file\
_infile_sh=\"$name.$method.$db.$server.infile.tmp\\
";\n	$cache_file_infile=\"$CACHE/$name.$method.$db\
.$server.infile.tmp\";\n      }\n    \n    if ($ca\
che_mode eq \"GET\")\n      {\n	if ($CACHE eq \"\"\
 || $CACHE eq \"no\" || $CACHE eq \"ignore\"  || $\
CACHE eq \"local\" || $CACHE eq \"update\"){return\
 0;}\n	elsif ( !-d $CACHE)\n	  {\n	    print STDER\
R \"ERROR: Cache Dir: $CACHE Does not Exist\";\n	 \
   return 0;\n	  }\n	else\n	  {\n	    if ( -e $cac\
he_file && &fasta_file1_eq_fasta_file2($infile,$ca\
che_file_infile)==1)\n	      {\n		`cp $cache_file \
$outfile`;\n		$CACHE_STATUS=\"READ CACHE\";\n		ret\
urn 1;\n	      }\n	  }\n      }\n    elsif ($cache\
_mode eq \"SET\")\n      {\n	if ($CACHE eq \"\" ||\
 $CACHE eq \"no\" || $CACHE eq \"ignore\"  || $CAC\
HE eq \"local\" || $CACHE eq \"update\"){return 0;\
}\n	elsif ( !-d $CACHE)\n	  {\n	    print STDERR \\
"ERROR: Cache Dir: $CACHE Does not Exist\";\n	    \
return 0;\n	  }\n	elsif (-e $outfile)\n	  {\n	    \
`cp $outfile $cache_file`;\n	    if ($cache_file_i\
nfile ne \"\"){ `cp $infile $cache_file_infile`;}\\
n\n	    #functions for updating the cache\n	    #`\
t_coffee -other_pg clean_cache.pl -file $cache_fil\
e_sh -dir $CACHE`;\n	    #`t_coffee -other_pg clea\
n_cache.pl -file $cache_file_infile_sh -dir $CACHE\
`;\n	    return 1;\n	  }\n      }\n    $CACHE_STAT\
US=\"COMPUTE CACHE\";\n    return 0;\n  }\nsub fil\
e1_eq_file2\n  {\n    my ($f1, $f2)=@_;\n    if ( \
$f1 eq \"\"){return 1;}\n    elsif ( $f2 eq \"\"){\
return 1;}\n    elsif ( !-e $f1){return 0;}\n    e\
lsif ( !-e $f2){return 0;}\n    elsif ($f1 eq \"\"\
 || $f2 eq \"\" || `diff $f1 $f2` eq \"\"){return \
1;}\n    \n    return 0;\n  }\nsub clean_file_name\
 \n  {\n    my $name=@_[0];\n    \n    $name=~s/[^\
A-Za-z1-9.-]/_/g;\n    return $name;\n  }\nsub url\
2file\n  {\n    my ($address, $out)=(@_);\n    \n \
   if (&pg_is_installed (\"wget\"))\n	{\n	  return\
 &safe_system (\"wget $address -O$out >/dev/null 2\
>/dev/null\");\n	}\n    elsif (&pg_is_installed (\\
"curl\"))\n      {\n	return &safe_system (\"curl $\
address -o$out >/dev/null 2>/dev/null\");\n      }\
\n    else\n      {\n	myexit(flus_error(\"neither \
curl nor wget are installed. Imnpossible to fectch\
 remote file\"));\n	exit ($EXIT_FAILURE);\n      }\
\n  }\nsub fasta_file1_eq_fasta_file2\n  {\n    my\
 ($f1, $f2)=@_;\n    my (%s1, %s2);\n    my @names\
;\n    %s1=read_fasta_seq ($f1);\n    %s2=read_fas\
ta_seq ($f2);\n\n    @names=(keys (%s1));\n    \n \
   foreach $n (keys(%s1))\n      {\n	if ($s1{$n}{s\
eq} ne $s2{$n}{seq}){return 0;}\n      } \n    \n \
   foreach $n (keys(%s2))\n      {\n	if ($s1{$n}{s\
eq} ne $s2{$n}{seq}){return 0;}\n      }\n    retu\
rn 1;\n  }\n	\n\n\nsub read_template_file\n{\n	my \
$pdb_templates = @_[0];\n	open (TEMP, \"<$pdb_temp\
lates\");\n	my %temp_h;\n	while (<TEMP>)\n{\n		$li\
ne = $_;\n 		$line =~/(\\S+)\\s(\\S+)/;\n 		$temp_\
h{$1}= $2;\n}\n	close(TEMP);\n	return %temp_h;\n}\\
n\nsub calc_rna_template\n{\n	my ($mode, $infile, \
$pdbfile, $outfile)=@_;\n	my %s, %h ;\n	my $result\
;\n	my (@profiles);\n	&set_temporary_dir (\"set\",\
$infile,\"seq.pep\");\n	%s=read_fasta_seq (\"seq.p\
ep\");\n	\n	%pdb_template_h = &read_template_file(\
$pdbfile);\n	my $pdb_chain;\n	open (R, \">result.a\
ln\");\n\n\n	#print stdout \"\\n\";\n	foreach $seq\
 (keys(%s))\n	{\n		if ($pdb_template_h{$seq} eq \"\
\")\n		{\n			next;\n		}\n		open (F, \">seqfile\");\
\n		print (F \">$s{$seq}{name}\\n$s{$seq}{seq}\\n\\
");\n		close (F);\n		$pdb_chain = $pdb_template_h{\
$seq};\n		$lib_name=\"$s{$seq}{name}.rfold\";\n		$\
lib_name=&clean_file_name ($lib_name);\n		\n 		saf\
e_system (\"secondary_struc.py seqfile $CACHE$pdb_\
chain  $lib_name\");\n		\n		if ( !-e $lib_name)\n	\
	{\n		myexit(flush_error(\"RNAplfold failed to com\
pute the secondary structure of $s{$seq}{name}\"))\
;\n			myexit ($EXIT_FAILURE);\n		}\n		else\n		{\n	\
		print stdout \"\\tProcess: >$s{$seq}{name} _F_ $\
lib_name\\n\";\n			print R \">$s{$seq}{name} _F_ $\
lib_name\\n\";\n		}\n		unshift (@profiles, $lib_na\
me);\n	}\n	close (R);\n	&set_temporary_dir (\"unse\
t\",$mode, $method,\"result.aln\",$outfile, @profi\
les);\n}\n\n\n\nsub seq2rna_pair{\n	my ($mode, $pd\
bfile1, $pdbfile2, $method, $param, $outfile)=@_;\\
n	\n	if ($method eq \"runsara.py\")\n	{\n		open(TM\
P,\"<$pdbfile1\");\n		my $count = 0;\n		my $line;\\
n		while (<TMP>)\n		{\n			$line = $_;\n			if ($cou\
nt ==1)\n			{\n				last;\n			}\n			$count += 1;\n	\
	}\n\n		\n		$chain1 = substr($line,length($line)-3\
,1);\n\n		close TMP;\n		open(TMP,\"<$pdbfile2\");\\
n		my $count = 0;\n		while (<TMP>)\n		{\n			$line \
= $_;\n			if ($count ==1)\n			{\n				last;\n			}\n\
			$count += 1;\n		}\n		$chain2 = substr($line,len\
gth($line)-3,1);\n		close TMP;\n\n		$tmp_file=&vtm\
pnam();\n	\n		safe_system(\"runsara.py $pdbfile1 $\
chain1 $pdbfile2 $chain2 -s -o $tmp_file --limitat\
ion 5000 > /dev/null 2> /dev/null\") == 0 or die \\
"sara did not work $!\\n\";\n		open(TMP,\"<$tmp_fi\
le\") or die \"cannot open the sara tmp file:$!\\n\
\";\n		open(OUT,\">$outfile\") or die \"cannot ope\
n the $outfile file:$!\\n\";\n\n		my $switch = 0;\\
n		my $seqNum = 0;\n		foreach my $line (<TMP>)\n		\
{\n			next unless ($line=~/SARAALI/);\n			if ($lin\
e=~/>/)\n			{\n				$switch =0;\n				print OUT \">s\
eq$seqNum\\n\";\n				$seqNum++;				\n			}\n			if (\
$switch < 2){\n				$switch++;\n				next;\n			}\n	\\
n			if ($line =~/REMARK\\s+SARAALI\\s+([^\\*]+)\\*\
/)\n			{\n				my $string = $1;\n				print OUT \"$s\
tring\\n\";\n			}\n		}\n		close TMP; \n		close OUT\
;\n		unlink($tmp_file);\n	}\n}\n\nsub seq2tblastx_\
lib\n  {\n    my ($mode, $infile, $outfile)=@_;\n \
   my (%s, $method,$nseq);\n\n    $method=$mode;\n\
    &set_temporary_dir (\"set\",$infile,\"infile\"\
);\n    %s=read_fasta_seq(\"infile\");\n    \n    \
\n    foreach $seq (keys(%s))\n      {\n	$slist[$s\
{$seq}{order}]=$s{$seq}{seq};\n	$sname[$s{$seq}{or\
der}]=$s{$seq}{name};\n	$slen[$s{$seq}{order}]=len\
gth ($s{$seq}{seq});\n      }\n    $nseq=$#sname+1\
;\n    open (F, \">outfile\");\n    print F \"! TC\
_LIB_FORMAT_01\\n\";\n    print F \"$nseq\\n\";\n \
   for ($a=0; $a<$nseq;$a++)\n      {\n	print F \"\
$sname[$a] $slen[$a]  $slist[$a]\\n\"\n      }\n  \
  close (F);\n    &safe_system (\"formatdb -i infi\
le -p F\");\n    &safe_system (\"blastall -p tblas\
tx -i infile -d infile -m 7 -S1>blast.output\");\n\
    \n    ncbi_tblastx_xml2lib_file (\"outfile\", \
file2string (\"blast.output\"));\n    &set_tempora\
ry_dir (\"unset\",$mode, $method, \"outfile\",$out\
file);\n    myexit ($EXIT_SUCCESS);\n    }\nsub se\
q2tblastpx_lib\n  {\n    my ($mode, $infile, $outf\
ile)=@_;\n    my (%s, $method,$nseq);\n    $method\
=$mode;\n    &set_temporary_dir (\"set\",$infile,\\
"infile\");\n    %s=read_fasta_seq(\"infile\");\n \
   \n    foreach $seq (keys(%s))\n      {\n	$slist\
[$s{$seq}{order}]=$s{$seq}{seq};\n	$sname[$s{$seq}\
{order}]=$s{$seq}{name};\n	$slen[$s{$seq}{order}]=\
length ($s{$seq}{seq});\n      }\n    $nseq=$#snam\
e+1;\n    open (F, \">outfile\");\n    print F \"!\
 TC_LIB_FORMAT_01\\n\";\n    print F \"$nseq\\n\";\
\n    for ($a=0; $a<$nseq;$a++)\n      {\n	print F\
 \"$sname[$a] $slen[$a]  $slist[$a]\\n\"\n      }\\
n    close (F);\n    &safe_system(\"t_coffee -othe\
r_pg seq_reformat -in infile -output tblastx_db1 >\
 tblastxdb\");\n    &safe_system (\"formatdb -i tb\
lastxdb -p T\");\n    &safe_system (\"blastall -p \
blastp -i tblastxdb -d tblastxdb -m7 >blast.output\
\");\n    ncbi_tblastpx_xml2lib_file (\"outfile\",\
 file2string (\"blast.output\"), %s);\n    &set_te\
mporary_dir (\"unset\",$mode, $method, \"outfile\"\
,$outfile);\n    myexit ($EXIT_SUCCESS);\n    }\n\\
n\n    \n\n\n\nsub file2head\n      {\n	my $file =\
 shift;\n	my $size = shift;\n	my $f= new FileHandl\
e;\n	my $line;\n	open ($f,$file);\n	read ($f,$line\
, $size);\n	close ($f);\n	return $line;\n      }\n\
sub file2tail\n      {\n	my $file = shift;\n	my $s\
ize = shift;\n	my $f= new FileHandle;\n	my $line;\\
n	\n	open ($f,$file);\n	seek ($f,$size*-1, 2);\n	r\
ead ($f,$line, $size);\n	close ($f);\n	return $lin\
e;\n      }\n\n\nsub vtmpnam\n      {\n	my $r=rand\
(100000);\n	my $f=\"file.$r.$$\";\n	while (-e $f)\\
n	  {\n	    $f=vtmpnam();\n	  }\n	push (@TMPFILE_L\
IST, $f);\n	return $f;\n      }\n\nsub myexit\n  {\
\n    my $code=@_[0];\n    if ($CLEAN_EXIT_STARTED\
==1){return;}\n    else {$CLEAN_EXIT_STARTED=1;}\n\
    ### ONLY BARE EXIT\n    exit ($code);\n  }\nsu\
b set_error_lock\n    {\n      my $name = shift;\n\
      my $pid=$$;\n\n      \n      &lock4tc ($$,\"\
LERROR\", \"LSET\", \"$$ -- ERROR: $name $PROGRAM\\
\n\");\n      return;\n    }\nsub set_lock\n  {\n \
   my $pid=shift;\n    my $msg= shift;\n    my $p=\
getppid();\n    &lock4tc ($pid,\"LLOCK\",\"LRESET\\
",\"$p$msg\\n\");\n  }\nsub unset_lock\n   {\n    \
 \n    my $pid=shift;\n    &lock4tc ($pid,\"LLOCK\\
",\"LRELEASE\",\"\");\n  }\nsub shift_lock\n  {\n \
   my $from=shift;\n    my $to=shift;\n    my $fro\
m_type=shift;\n    my $to_type=shift;\n    my $act\
ion=shift;\n    my $msg;\n    \n    if (!&lock4tc(\
$from, $from_type, \"LCHECK\", \"\")){return 0;}\n\
    $msg=&lock4tc ($from, $from_type, \"LREAD\", \\
"\");\n    &lock4tc ($from, $from_type,\"LRELEASE\\
", $msg);\n    &lock4tc ($to, $to_type, $action, $\
msg);\n    return;\n  }\nsub isshellpid\n  {\n    \
my $p=shift;\n    if (!lock4tc ($p, \"LLOCK\", \"L\
CHECK\")){return 0;}\n    else\n      {\n	my $c=lo\
ck4tc($p, \"LLOCK\", \"LREAD\");\n	if ( $c=~/-SHEL\
L-/){return 1;}\n      }\n    return 0;\n  }\nsub \
isrootpid\n  {\n    if(lock4tc (getppid(), \"LLOCK\
\", \"LCHECK\")){return 0;}\n    else {return 1;}\\
n  }\nsub lock4tc\n	{\n	  my ($pid,$type,$action,$\
value)=@_;\n	  my $fname;\n	  my $host=hostname;\n\
	  \n	  if ($type eq \"LLOCK\"){$fname=\"$LOCKDIR/\
.$pid.$host.lock4tcoffee\";}\n	  elsif ( $type eq \
\"LERROR\"){ $fname=\"$LOCKDIR/.$pid.$host.error4t\
coffee\";}\n	  elsif ( $type eq \"LWARNING\"){ $fn\
ame=\"$LOCKDIR/.$pid.$host.warning4tcoffee\";}\n	 \
 \n	  if ($debug_lock)\n	    {\n	      print STDER\
R \"\\n\\t---lock4tc(tcg): $action => $fname =>$va\
lue (RD: $LOCKDIR)\\n\";\n	    }\n\n	  if    ($act\
ion eq \"LCHECK\") {return -e $fname;}\n	  elsif (\
$action eq \"LREAD\"){return file2string($fname);}\
\n	  elsif ($action eq \"LSET\") {return string2fi\
le ($value, $fname, \">>\");}\n	  elsif ($action e\
q \"LRESET\") {return string2file ($value, $fname,\
 \">\");}\n	  elsif ($action eq \"LRELEASE\") \n	 \
   {\n	      if ( $debug_lock)\n		{\n		  my $g=new\
 FileHandle;\n		  open ($g, \">>$fname\");\n		  pr\
int $g \"\\nDestroyed by $$\\n\";\n		  close ($g);\
\n		  safe_system (\"mv $fname $fname.old\");\n		}\
\n	      else\n		{\n		  unlink ($fname);\n		}\n	  \
  }\n	  return \"\";\n	}\n	\nsub file2string\n	{\n\
	  my $file=@_[0];\n	  my $f=new FileHandle;\n	  m\
y $r;\n	  open ($f, \"$file\");\n	  while (<$f>){$\
r.=$_;}\n	  close ($f);\n	  return $r;\n	}\nsub st\
ring2file \n    {\n    my ($s,$file,$mode)=@_;\n  \
  my $f=new FileHandle;\n    \n    open ($f, \"$mo\
de$file\");\n    print $f  \"$s\";\n    close ($f)\
;\n  }\n\nBEGIN\n    {\n      srand;\n    \n      \
$SIG{'SIGUP'}='signal_cleanup';\n      $SIG{'SIGIN\
T'}='signal_cleanup';\n      $SIG{'SIGQUIT'}='sign\
al_cleanup';\n      $SIG{'SIGILL'}='signal_cleanup\
';\n      $SIG{'SIGTRAP'}='signal_cleanup';\n     \
 $SIG{'SIGABRT'}='signal_cleanup';\n      $SIG{'SI\
GEMT'}='signal_cleanup';\n      $SIG{'SIGFPE'}='si\
gnal_cleanup';\n      \n      $SIG{'SIGKILL'}='sig\
nal_cleanup';\n      $SIG{'SIGPIPE'}='signal_clean\
up';\n      $SIG{'SIGSTOP'}='signal_cleanup';\n   \
   $SIG{'SIGTTIN'}='signal_cleanup';\n      $SIG{'\
SIGXFSZ'}='signal_cleanup';\n      $SIG{'SIGINFO'}\
='signal_cleanup';\n      \n      $SIG{'SIGBUS'}='\
signal_cleanup';\n      $SIG{'SIGALRM'}='signal_cl\
eanup';\n      $SIG{'SIGTSTP'}='signal_cleanup';\n\
      $SIG{'SIGTTOU'}='signal_cleanup';\n      $SI\
G{'SIGVTALRM'}='signal_cleanup';\n      $SIG{'SIGU\
SR1'}='signal_cleanup';\n\n\n      $SIG{'SIGSEGV'}\
='signal_cleanup';\n      $SIG{'SIGTERM'}='signal_\
cleanup';\n      $SIG{'SIGCONT'}='signal_cleanup';\
\n      $SIG{'SIGIO'}='signal_cleanup';\n      $SI\
G{'SIGPROF'}='signal_cleanup';\n      $SIG{'SIGUSR\
2'}='signal_cleanup';\n\n      $SIG{'SIGSYS'}='sig\
nal_cleanup';\n      $SIG{'SIGURG'}='signal_cleanu\
p';\n      $SIG{'SIGCHLD'}='signal_cleanup';\n    \
  $SIG{'SIGXCPU'}='signal_cleanup';\n      $SIG{'S\
IGWINCH'}='signal_cleanup';\n      \n      $SIG{'I\
NT'}='signal_cleanup';\n      $SIG{'TERM'}='signal\
_cleanup';\n      $SIG{'KILL'}='signal_cleanup';\n\
      $SIG{'QUIT'}='signal_cleanup';\n      \n    \
  our $debug_lock=$ENV{\"DEBUG_LOCK\"};\n      \n \
     \n      \n      \n      foreach my $a (@ARGV)\
{$CL.=\" $a\";}\n      if ( $debug_lock ){print ST\
DERR \"\\n\\n\\n********** START PG: $PROGRAM ****\
*********\\n\";}\n      if ( $debug_lock ){print S\
TDERR \"\\n\\n\\n**********(tcg) LOCKDIR: $LOCKDIR\
 $$ *************\\n\";}\n      if ( $debug_lock )\
{print STDERR \"\\n --- $$ -- $CL\\n\";}\n      \n\
	     \n      \n      \n    }\nsub flush_error\n  \
{\n    my $msg=shift;\n    return add_error ($EXIT\
_FAILURE,$$, $$,getppid(), $msg, $CL);\n  }\nsub a\
dd_error \n  {\n    my $code=shift;\n    my $rpid=\
shift;\n    my $pid=shift;\n    my $ppid=shift;\n \
   my $type=shift;\n    my $com=shift;\n    \n    \
$ERROR_DONE=1;\n    lock4tc ($rpid, \"LERROR\",\"L\
SET\",\"$pid -- ERROR: $type\\n\");\n    lock4tc (\
$$, \"LERROR\",\"LSET\", \"$pid -- COM: $com\\n\")\
;\n    lock4tc ($$, \"LERROR\",\"LSET\", \"$pid --\
 STACK: $ppid -> $pid\\n\");\n   \n    return $cod\
e;\n  }\nsub add_warning \n  {\n    my $rpid=shift\
;\n    my $pid =shift;\n    my $command=shift;\n  \
  my $msg=\"$$ -- WARNING: $command\\n\";\n    pri\
nt STDERR \"$msg\";\n    lock4tc ($$, \"LWARNING\"\
, \"LSET\", $msg);\n  }\n\nsub signal_cleanup\n  {\
\n    print dtderr \"\\n**** $$ (tcg) was killed\\\
n\";\n    &cleanup;\n    exit ($EXIT_FAILURE);\n  \
}\nsub clean_dir\n  {\n    my $dir=@_[0];\n    if \
( !-d $dir){return ;}\n    elsif (!($dir=~/tmp/)){\
return ;}#safety check 1\n    elsif (($dir=~/\\*/)\
){return ;}#safety check 2\n    else\n      {\n	`r\
m -rf $dir`;\n      }\n    return;\n  }\nsub clean\
up\n  {\n    #print stderr \"\\n----tc: $$ Kills $\
PIDCHILD\\n\";\n    #kill (SIGTERM,$PIDCHILD);\n  \
  my $p=getppid();\n    $CLEAN_EXIT_STARTED=1;\n  \
  \n    \n    \n    if (&lock4tc($$,\"LERROR\", \"\
LCHECK\", \"\"))\n      {\n	my $ppid=getppid();\n	\
if (!$ERROR_DONE) \n	  {\n	    &lock4tc($$,\"LERRO\
R\", \"LSET\", \"$$ -- STACK: $p -> $$\\n\");\n	  \
  &lock4tc($$,\"LERROR\", \"LSET\", \"$$ -- COM: $\
CL\\n\");\n	  }\n      }\n    my $warning=&lock4tc\
($$, \"LWARNING\", \"LREAD\", \"\");\n    my $erro\
r=&lock4tc($$,  \"LERROR\", \"LREAD\", \"\");\n   \
 #release error and warning lock if root\n    \n  \
  if (isrootpid() && ($warning || $error) )\n     \
 {\n	\n	print STDERR \"**************** Summary **\
***********\\n$error\\n$warning\\n\";\n\n	&lock4tc\
($$,\"LERROR\",\"RELEASE\",\"\");\n	&lock4tc($$,\"\
LWARNING\",\"RELEASE\",\"\");\n      } \n    \n   \
 \n    foreach my $f (@TMPFILE_LIST)\n      {\n	if\
 (-e $f){unlink ($f);} \n      }\n    foreach my $\
d (@TMPDIR_LIST)\n      {\n	clean_dir ($d);\n     \
 }\n    #No More Lock Release\n    #&lock4tc($$,\"\
LLOCK\",\"LRELEASE\",\"\"); #release lock \n\n    \
if ( $debug_lock ){print STDERR \"\\n\\n\\n*******\
*** END PG: $PROGRAM ($$) *************\\n\";}\n  \
  if ( $debug_lock ){print STDERR \"\\n\\n\\n*****\
*****(tcg) LOCKDIR: $LOCKDIR $$ *************\\n\"\
;}\n  }\nEND \n  {\n    \n    &cleanup();\n  }\n  \
 \nsub blast_com2new_blast_com\n    {\n      my $c\
om=shift;\n      if ($ENV{\"NCBI_BLAST_4_TCOFFEE\"\
} eq \"OLD\"){return $com;}\n      elsif (!&pg_is_\
installed(\"legacy_blast.pl\")){return $com;}\n   \
   else \n	{\n	  if ($com=~/formatdb/)\n	    {\n	 \
     $com=~s/formatdb/makeblastdb/;\n	      $com=~\
s/\\-i/\\-in/;\n	      if ($com =~/pF/){$com=~s/\\\
-pF/\\-dbtype nucl/;}\n	      if ($com =~/p F/){$c\
om=~s/\\-p F/\\-dbtype nucl/;}\n	      $com=\"$com\
 -logfile /dev/null\";\n	      return $com;\n	    \
}\n	  elsif (&is_blast_package($com))\n	    {\n	  \
    my $path;\n	      \n	      if ( $ENV{\"NCBI_BI\
N_4_TCOFFEE\"}){$path=$ENV{\"NCBI_BLAST_4_TCOFFEE\\
"};}\n	      else\n		{\n		  $path=`which legacy_bl\
ast.pl`;\n		  $path=~s/\\/legacy_blast\\.pl//;\n		\
  chomp ($path);\n		}\n	      $path=\"--path $path\
\";\n	      if ( $com=~/\\>\\>/){$com=~s/\\>\\>/ $\
path \\>\\>/;}\n	      elsif ( $com=~/\\>/){$com=~\
s/\\>/ $path \\>/;}\n	      else {$com.=\" $path\"\
;}\n	      $com=\"legacy_blast.pl $com\";\n	      \
\n	      return $com;\n	    }\n	}\n    }\nsub safe\
_system \n{\n  my $com=shift;\n  my $ntry=shift;\n\
  my $ctry=shift;\n  my $pid;\n  my $status;\n  my\
 $ppid=getppid();\n  if ($com eq \"\"){return 1;}\\
n  \n  if ( ($com=~/^blast/) ||($com=~/^formatdb/)\
){$com=&blast_com2new_blast_com($com);} \n\n  if (\
($pid = fork ()) < 0){return (-1);}\n  if ($pid ==\
 0)\n    {\n      set_lock($$, \" -SHELL- $com (tc\
g)\");\n      if( $debug_cmd_exec ) { printf \"exe\
c: %s\\n\", $com; } \n      exec ($com);\n    }\n \
 else\n    {\n      lock4tc ($$, \"LLOCK\", \"LSET\
\", \"$pid\\n\");#update parent\n      $PIDCHILD=$\
pid;\n    }\n  if ($debug_lock){printf STDERR \"\\\
n\\t .... safe_system (fasta_seq2hmm)  p: $$ c: $p\
id COM: $com\\n\";}\n\n  waitpid ($pid,WTERMSIG);\\
n\n  shift_lock ($pid,$$, \"LWARNING\",\"LWARNING\\
", \"LSET\");\n\n  if ($? == $EXIT_FAILURE || lock\
4tc($pid, \"LERROR\", \"LCHECK\", \"\"))\n    {\n \
     if ($ntry && $ctry <$ntry)\n	{\n\n	  add_warn\
ing ($$,$$,\"$com failed [retry: $ctry out of $ntr\
y]\");\n	  lock4tc ($pid, \"LRELEASE\", \"LERROR\"\
, \"\");\n	  #if ($com=~/EBI/){$com=~s/EBI/NCBI/;}\
\n	  #elsif ($com=~/NCBI/){$com=~s/NCBI/EBI/;}\n	 \
 \n	  return safe_system ($com, $ntry, ++$ctry);\n\
	}\n      elsif ($ntry == -1)\n	{\n	  if (!shift_l\
ock ($pid, $$, \"LERROR\", \"LWARNING\", \"LSET\")\
)\n	    {\n	      add_warning ($$,$$,\"$com failed\
\");\n	    }\n	  else\n	    {\n	      lock4tc ($pi\
d, \"LRELEASE\", \"LERROR\", \"\");\n	    }\n	  re\
turn $?;}\n      else\n	{\n	  if (!shift_lock ($pi\
d,$$, \"LERROR\",\"LERROR\", \"LSET\"))\n	    {\n	\
      myexit(add_error ($EXIT_FAILURE,$$,$pid,getp\
pid(), \"UNSPECIFIED system\", $com));\n	    }\n	}\
\n    }\n  return $?;\n}\n\nsub check_configuratio\
n \n    {\n      my @l=@_;\n      my $v;\n      fo\
reach my $p (@l)\n	{\n	  \n	  if   ( $p eq \"EMAIL\
\")\n	    { \n	      if ( !($EMAIL=~/@/))\n		{\n		\
add_warning($$,$$,\"Could Not Use EMAIL\");\n		mye\
xit(add_error ($EXIT_FAILURE,$$,$$,getppid(),\"EMA\
IL\",\"$CL\"));\n	      }\n	    }\n	  elsif( $p eq\
 \"INTERNET\")\n	    {\n	      if ( !&check_intern\
et_connection())\n		{\n		  myexit(add_error ($EXIT\
_FAILURE,$$,$$,getppid(),\"INTERNET\",\"$CL\"));\n\
		}\n	    }\n	  elsif( $p eq \"wget\")\n	    {\n	 \
     if (!&pg_is_installed (\"wget\") && !&pg_is_i\
nstalled (\"curl\"))\n		{\n		  myexit(add_error ($\
EXIT_FAILURE,$$,$$,getppid(),\"PG_NOT_INSTALLED:wg\
et\",\"$CL\"));\n		}\n	    }\n	  elsif( !(&pg_is_i\
nstalled ($p)))\n	    {\n	      myexit(add_error (\
$EXIT_FAILURE,$$,$$,getppid(),\"PG_NOT_INSTALLED:$\
p\",\"$CL\"));\n	    }\n	}\n      return 1;\n    }\
\n\n$program=\"T-COFFEE (r550)\";\n\n","*TC_METHOD\
_FORMAT_01\n******************generic_method.tc_me\
thod*************\n*\n*       Incorporating new me\
thods in T-Coffee\n*       Cedric Notredame 26/08/\
08\n*\n*******************************************\
************\n*This file is a method file\n*Copy i\
t and adapt it to your need so that the method \n*\
you want to use can be incorporated within T-Coffe\
e\n***********************************************\
********\n*                  USAGE                \
              *\n*********************************\
**********************\n*This file is passed to t_\
coffee via -in:\n*\n*	t_coffee -in Mgeneric_method\
.method\n*\n*	The method is passed to the shell us\
ing the following\n*call:\n*<EXECUTABLE><PARAM1><I\
N_FLAG><seq_file><PARAM2><OUT_FLAG><outname><PARAM\
>\n*\n*Conventions:\n*<FLAG_NAME> 	<TYPE>		<VALUE>\
\n*<VALUE>:	no_name 	<=> Replaced with a space\n*<\
VALUE>:	&nbsp	<=> Replaced with a space\n*\n******\
*************************************************\\
n*                  ALN_MODE                      \
     *\n******************************************\
*************\n*pairwise   ->all Vs all (no self )\
[(n2-n)/2aln]\n*m_pairwise ->all Vs all (no self)[\
n^2-n]^2\n*s_pairwise ->all Vs all (self): [n^2-n]\
/2 + n\n*multiple   ->All the sequences in one go\\
n*\nALN_MODE		pairwise\n*\n***********************\
********************************\n*               \
   OUT_MODE                           *\n*********\
**********************************************\n* \
mode for the output:\n*External methods: \n* aln -\
> alignmnent File (Fasta or ClustalW Format)\n* li\
b-> Lib file (TC_LIB_FORMAT_01)\n*Internal Methods\
:\n* fL -> Internal Function returning a List (Lib\
rairie)\n* fA -> Internal Function returning an Al\
ignmnent\n*\nOUT_MODE		aln\n**********************\
*********************************\n*              \
    SEQ_TYPE                           *\n********\
***********************************************\n*\
G: Genomic, S: Sequence, P: PDB, R: Profile\n*Exam\
ples:\n*SEQTYPE	S	sequences against sequences (def\
ault)\n*SEQTYPE	S_P	sequence against structure\n*S\
EQTYPE	P_P	structure against structure\n*SEQTYPE	P\
S	mix of sequences and structure	\n*\nSEQ_TYPE	S\n\
*\n\n*********************************************\
**********\n*                COMMAND LINE         \
                *\n*EXECUTABLE PARAM1 IN_FLAG OUT_\
FLAG PARAM             *\n************************\
*******************************\n*****************\
**************************************\n*         \
         EXECUTABLE                         *\n***\
**************************************************\
**\n*name of the executable\n*passed to the shell:\
 executable\n*	\nEXECUTABLE	tc_generic_method.pl\n\
*\n***********************************************\
********\n*                  IN_FLAG              \
               *\n********************************\
***********************\n*IN_FLAG\n*flag indicatin\
g the name of the in coming sequences\n*IN_FLAG S \
no_name ->no flag\n*IN_FLAG S &bnsp-in&bnsp -> \" \
-in \"\n*\nIN_FLAG		-infile=\n*\n*****************\
**************************************\n*         \
         OUT_FLAG                           *\n***\
**************************************************\
**\n*OUT_FLAG\n*flag indicating the name of the ou\
t-coming data\n*same conventions as IN_FLAG\n*OUT_\
FLAG	S no_name ->no flag\n*if you want to redirect\
, pass the parameters via PARAM1\n*set OUT_FLAG to\
 >\n*\nOUT_FLAG		-outfile=\n*\n*******************\
************************************\n*           \
       PARAM_1                              *\n***\
**************************************************\
**\n*<EXECUTABLE><PARAM1><IN_FLAG><seq_file><PARAM\
2><OUT_FLAG><outname><PARAM>\n*Parameters sent to \
the EXECUTABLE and specified *before* IN_FLAG \n*I\
f there is more than 1 PARAM line, the lines are\n\
*concatenated\n*Command_line: @EP@PARAM@-gapopen%e\
10%s-gapext%e20\n*	%s white space\n*	%e equal sign\
\n*\n*PARAM1	\n*\n*\n*\n**************************\
*****************************\n*                  \
PARAM_2                              *\n**********\
*********************************************\n*<E\
XECUTABLE><PARAM1><IN_FLAG><seq_file><PARAM2><OUT_\
FLAG><outname><PARAM>\n*Parameters sent to the EXE\
CUTABLE and specified \n*after* IN_FLAG and *befor\
e* OUT_FLAG\n*If there is more than 1 PARAM line, \
the lines are\n*concatenated\n*\n*PARAM1	\n*\n*\n*\
**************************************************\
****\n*                  PARAM                    \
          *\n*************************************\
******************\n*<EXECUTABLE><PARAM1><IN_FLAG>\
<seq_file><PARAM2><OUT_FLAG><outname><PARAM>\n*Par\
ameters sent to the EXECUTABLE and specified *afte\
r* OUT_FLAG\n*If there is more than 1 PARAM line, \
the lines are\n*concatenated\n*\nPARAM	-mode=seq_m\
sa -method=clustalw\nPARAM   -OUTORDER=INPUT -NEWT\
REE=core -align -gapopen=-15\n*\n*****************\
**************************************\n*         \
         END                                *\n***\
**************************************************\
**\n","*TC_METHOD_FORMAT_01\n***************clusta\
lw_method.tc_method*********\nEXECUTABLE	clustalw\\
nALN_MODE		pairwise\nIN_FLAG		-INFILE=\nOUT_FLAG		\
-OUTFILE=\nOUT_MODE		aln\nPARAM		-gapopen=-10\nSEQ\
_TYPE		S\n****************************************\
*********\n","$VersionTag =                       \
                                                  \
                                                  \
        2.43;\nuse Env;\nuse FileHandle;\nuse Cwd;\
\nuse File::Path;\nuse Sys::Hostname;\nour $PIDCHI\
LD;\nour $ERROR_DONE;\nour @TMPFILE_LIST;\nour $EX\
IT_FAILURE=1;\nour $EXIT_SUCCESS=0;\n\nour $REFDIR\
=getcwd;\nour $EXIT_SUCCESS=0;\nour $EXIT_FAILURE=\
1;\n\nour $PROGRAM=\"extract_from_pdb\";\nour $CL=\
$PROGRAM;\n\nour $CLEAN_EXIT_STARTED;\nour $debug_\
lock=$ENV{\"DEBUG_LOCK\"};\nour $LOCKDIR=$ENV{\"LO\
CKDIR_4_TCOFFEE\"};\nif (!$LOCKDIR){$LOCKDIR=getcw\
d();}\nour $ERRORDIR=$ENV{\"ERRORDIR_4_TCOFFEE\"};\
\nour $ERRORFILE=$ENV{\"ERRORFILE_4_TCOFFEE\"};\n&\
set_lock ($$);\nif (isshellpid(getppid())){lock4tc\
(getppid(), \"LLOCK\", \"LSET\", \"$$\\n\");}\n   \
   \nour $SILENT=\" >/dev/null 2>/dev/null\";\nour\
 $INTERNET=-1;\n\n\n\n\n\n\n\nour $BLAST_MAX_NRUNS\
=2;\nour $EXIT_SUCCESS=0;\nour $EXIT_FAILURE=1;\no\
ur $CONFIGURATION=-1;\nour $REF_EMAIL=\"\";\nour $\
PROGRAM=\"extract_from_pdb\";\n\n\nmy %onelett_pro\
t=&fill_onelett_prot();\nmy %threelett_prot=&fill_\
threelett_prot();\nmy %onelett_RNA=&fill_onelett_R\
NA();\nmy %threelett_RNA=&fill_threelett_RNA();\nm\
y %onelett_DNA=&fill_onelett_DNA();\nmy %threelett\
_DNA=&fill_threelett_DNA();\n\n\n\n\n\nmy %onelett\
 = (\n'P' => \\%onelett_prot,\n'D' => \\%onelett_D\
NA,\n'R' => \\%onelett_RNA\n);\n\n\nmy %threelett \
= (\n'P' => \\%threelett_prot,\n'D' => \\%threelet\
t_DNA,\n'R' => \\%threelett_RNA\n);\n\n\n\n\n\n\n\\
nif($ARGV[0]=~/help/ ||$ARGV[0]=~/man/ || $ARGV[0]\
=~/HELP/ || $ARGV[0]=~/Man/ || $ARGV[0] eq \"-h\" \
 || $ARGV[0] eq \"-H\"  )\n{die \"SYNTAX: extract_\
from_pdb Version $VersionTag	\n	Minimum:          \
   [extract_from_pdb file] \n			   OR \n			     [.\
.. | extract_from_pdb]\n 	Flags (Default setting o\
n the first line)\n	   -version...................\
[Returns the Version Number]\n           -force...\
..................[Forces the file to be treated l\
ike a PDB file]\n                                 \
     [Regenerates the header and SEQRES fields]\n \
          -force_name................[Forces the f\
ile to be named after name]]\n           -infile..\
...file...........[Flag can be omited]\n			       \
       [File must be pdb or fro pgm]\n            \
                          [File can also be compre\
ssed Z or gz]\n                                   \
   [In the case of a compressed file, you can omit\
 the gz|Z extension]\n           -netfile.........\
..........[File will be fetch from the net using w\
get]\n                                      [wget \
or curl must be installed]\n                      \
                [ftp://ftp.gnu.org/pub/gnu/wget/]\\
n                                      [http://cur\
l.haxx.se/]\n                                     \
 [Must also be used to retrieve the file from a lo\
cal pdb copy (cf netaddress)]\n           -netaddr\
ess................[Address used for the retrievin\
g the netfile]\n                                  \
    [http://www.rcsb.org/pdb/cgi/export.cgi/%%.pdb\
.gz?format=PDB&pdbId=%%&compression=gz]\n         \
                             [http://www.expasy.ch\
/cgi-bin/get-pdb-entry.pl?%%]\n                   \
                   [local -> will get the file fro\
m pdb_dir (see pdb_dir)]\n           -netcompressi\
on............[Extension if the netfile comes comp\
ressed]\n                                      [gz\
]\n           -pdb_dir...................[address \
of the repertory where the pdb is installed]\n    \
                                  [Supports standa\
rd ftp style installation OR every stru in DIR]\n \
                                     [Give the ...\
./pdb/structure/ dir]\n                           \
           [If value omitted, the pg gets it from \
the env variable PDB_DIR]\n           -netcompress\
ion_pg.........[gunzip]\n           -is_pdb_name..\
........name.[Returns 1 if the name is a PDB ID, 0\
 otherwise]\n           -model_type...........name\
.[Returns the model type if valid PDB name]\n     \
      -is_released_pdb_name name.[Returns 1 if the\
 name corresponds to a released PDB file]\n       \
    -get_pdb_chains.....name...[Returns the list o\
f chains corresponding to the entry]\n           -\
get_pdb_id.........name...[Returns the PDB id with\
in the provided pdb file]\n           -get_fugue_n\
ame.....name...[Turns a name into a name valid for\
 fugue]\n                                      [Us\
es the netaddress to do so]\n	   -chain......FIRST\
..........[Extract the first chain only]\n		      \
 A B C..........[Extract Several chains if needed]\
\n		       ALL............[Extract all the chains]\
	\n           -ligand.....ALL............[Extract \
the ligands in the chain (HETATM)]\n              \
         <name1>,<name2>[Extract All the named lig\
nds]\n	   -ligand_only...............[Extract only\
 the ligands]\n           -ligand_list............\
...[Extract the list of ligands]\n	   -coor.......\
<start>..<end>.[Coordinates of the fragment to ext\
ract]\n			              [Omit end to include the C\
ter]\n           -num........absolute.......[absol\
ute: relative to the seq] \n                      \
 file...........[file: relative to file]\n        \
   -num_out....new............[new: start 1->L]\n \
                      old............[old: keep th\
e file coordinates]\n           -delete.....<start\
>..<end>.[Delete from residue start to residue end\
]\n	   -atom.......CA.............[Atoms to includ\
e, ALL for all of them]\n		       CA O N.........[\
Indicate several atoms if needed]\n	   -code......\
.3..............[Use the 1 letter code or the 3 le\
tters code]\n	   -mode.......raw............[Outpu\
t original pdb file]\n                       pdb..\
..........[Output something that looks like pdb]\n\
		       fasta..........[Output the sequences in f\
asta format]\n		       simple.........[Output a fo\
rmat easy to parse in C ]\n            -seq_field.\
.ATOM...........[Field used to extract the sequenc\
e]\n		       SEQRES.........[Use the complete sequ\
ence]\n	   -seq.......................[Equivalent \
to  -mode fasta]\n	   -model......1..............[\
Chosen Model in an NMR file]\n           -nodiagno\
stic..............[Switches Error Messages off]\n \
          -debug.....................[Sets the DEB\
UG ON]\n           -no_remote_pdb_dir.........[Do \
not look for a remote file]\n           -cache_pdb\
.................[Cache Value, default is $HOME/.t\
_coffee/cache, other values: NO<=> No cache]\n\n  \
    Environement Variables\n           These varia\
bles can be set from the environement\n           \
Command line values with the corresponding flag su\
perseed evironement value\n           NO_REMOTE_PD\
B_DIR..........[Prevents the program from searchin\
g remote file: faster]\n           PDB_DIR........\
............[Indicates where PDB file must be fetc\
hed (localy)]\n\n	 PROBLEMS: please contact cedric\
.notredame\\@europe.com\\n\";\n	 exit ($EXIT_SUCCE\
SS);\n}\n\n$np=0;\n$n_para=$#ARGV;\n$model=1;\n$pd\
b_dir=$ENV{'PDB_DIR'};if ($pdb_dir){$pdb_dir.=\"/\\
";}\n$debug=$ENV{'DEBUG_EXTRACT_FROM_PDB'};\n\n$no\
_remote_pdb_dir=$ENV{NO_REMOTE_PDB_DIR};\n$HOME=$E\
NV{'HOME'};\nif ( $ENV{CACHE_4_TCOFFEE})\n{$cache=\
$ENV{CACHE_4_TCOFFEE};}\nelse\n{\n    $cache=\"$HO\
ME/.t_coffee/cache/\";\n}\n\n   \n$netaddress=\"ht\
tp://www.rcsb.org/pdb/files/%%.pdb.gz\";\n$netcomp\
ression_pg=\"gunzip\";\n$netcompression=\"gz\";\n\\
nforeach ($np=0; $np<=$n_para; $np++)\n  {        \
\n    $value=$ARGV[$np];\n   \n    if  ($np==0 && \
!($value=~/^-.*/))\n      { \n	$pdb_file= $ARGV[$n\
p];\n      }\n    elsif ( !($value=~/^-.*/))\n    \
  {\n	print \"@ARGV\";\n	die;\n      } \n    \n   \
 elsif ($value eq \"-nodiagnostic\"){$nodiagnostic\
=1;}\n    elsif ($value eq \"-force\")\n      {\n	\
$force_pdb=1;\n      }\n    elsif ($value eq \"-fo\
rce_name\")\n      {\n	$force_name=$ARGV[++$np];\n\
	$force_pdb=1;\n      }\n    \n    elsif ($value e\
q \"-is_pdb_name\")\n      {\n	$pdb_file= $ARGV[++\
$np];	\n	$is_pdb_name=1;	\n      } \n    elsif ($v\
alue eq \"-is_released_pdb_name\")\n      {\n	$pdb\
_file= $ARGV[++$np];	\n	$is_released_pdb_name=1;\n\
      }\n    elsif ($value eq \"-model_type\")\n  \
    {\n	$pdb_file= $ARGV[++$np];	\n	$model_type=1;\
\n      }\n    elsif ($value eq \"-debug\")\n{\n	$\
debug=1;\n}\n    elsif ($value eq \"-get_pdb_chain\
s\")\n{\n	$pdb_file= $ARGV[++$np];\n	$get_pdb_chai\
ns=1;\n}\n    elsif ($value eq \"-get_pdb_ligands\\
")\n{\n	$get_pdb_ligands=1;\n}\n    \n    elsif ($\
value eq \"-get_pdb_id\")\n{\n	$pdb_file= $ARGV[++\
$np];\n	$get_pdb_id=1;\n	\n}\n    \n    elsif ( $v\
alue eq \"-get_fugue_name\")\n{\n	$pdb_file= $ARGV\
[++$np];\n	$get_fugue_name=1;\n}\n    elsif ( $val\
ue eq \"-infile\")\n{\n       $pdb_file= $ARGV[++$\
np];\n} \n    elsif ($value eq \"-netfile\")\n{\n	\
$netfile=1;\n	if ( !($ARGV[$np+1]=~/^-.*/)){$pdb_f\
ile= $ARGV[++$np];}\n}\n    elsif (  $value eq \"-\
num\")\n{\n       $numbering= $ARGV[++$np];\n}\n  \
  elsif (  $value eq \"-num_out\")\n{\n       $num\
bering_out= $ARGV[++$np];\n}\n    elsif ( $value e\
q \"-netaddress\")\n{\n	$netadress=$ARGV[++$np];\n\
}\n     \n    elsif ( $value eq \"-netcompression\\
")\n{\n	 $netcompression=$ARGV[++$np];\n}\n    els\
if ( $value eq \"-pdb_dir\")\n{\n	 if ( !($ARGV[$n\
p+1]=~/^-.*/)){$pdb_dir= \"$ARGV[++$np]/\";}\n}\n \
    elsif ( $value eq \"-no_remote_pdb_dir\")\n{\n\
	$no_remote_pdb_dir=1;\n	if ( !($ARGV[$np+1]=~/^-.\
*/)){$pdb_dir= \"$ARGV[++$np]/\";}\n}\n    elsif (\
 $value eq \"-cache\")\n{\n	$cache=$ARGV[++$np];\n\
}\n    \n    elsif ($value eq \"-netcompression_pg\
\")\n{\n	  $netcompression_pg=$ARGV[++$np];\n}\n  \
   elsif ($value eq \"-mode\")\n{\n       $MODE=$A\
RGV[++$np];\n}\n\n    elsif ( $value eq \"-model\"\
)\n{\n       $model= $ARGV[++$np];\n}\n    elsif (\
$value eq \"-seq_field\" )\n{\n       $seq_field= \
$ARGV[++$np];\n}   \n    elsif ($value eq \"-coor\\
" )\n{\n       $start= $ARGV[++$np];\n  \n       i\
f (($ARGV[$np+1] eq \"\") ||($ARGV[$np+1]=~/^-.*/)\
){$end=\"*\";} \n       else {$end=   $ARGV[++$np]\
;}     \n       $coor_set=1;\n}\n    elsif ($value\
 eq \"-delete\" )\n{\n       $delete_start= $ARGV[\
++$np];\n       $delete_end= $ARGV[++$np];\n      \
 $delete_set=1;\n}\n    elsif  ($value eq \"-code\\
")\n{\n       $code= $ARGV[++$np];\n}\n    elsif  \
($value eq \"-no_hetatm\")\n{\n       $no_hetatm=1\
;\n}\n    elsif ($value eq \"-chain\")\n{\n       \
while (!($ARGV[$np+1] eq \"\") &&!($ARGV[$np+1]=~/\
^-.*/))\n{\n	      ++$np;\n	      @c_chain=(@chain\
,  $ARGV[$np]);\n	      $hc_chain{$ARGV[$np]}=$#c_\
chain+1;\n}           \n}\n    elsif ($value eq \"\
-atom\")\n{\n\n       while (!($ARGV[$np+1] eq \"\\
") && !($ARGV[$np+1]=~/^-.*/))\n{\n	      ++$np;\n\
	      $atom[$n_atom++]=  $ARGV[$np];\n	      $ato\
m_list{$ARGV[$np]}=1;	      \n} \n       \n}\n    \
elsif ( $value eq \"-unfold\")\n{\n	$unfold=1;\n}\\
n    elsif ($value eq \"-seq\" ||$value eq \"-fast\
a\" )\n{\n       $MODE=\"fasta\";\n}\n    elsif ( \
$value eq \"-version\")\n{\n	print STDERR  \"\\nex\
tract_from_pdb: Version $VersionTag\\n\";\n	&myexi\
t ($EXIT_SUCCESS);\n}\n    elsif ( $value eq \"-li\
gand\")\n{\n	while (!($ARGV[$np+1] eq \"\") && !($\
ARGV[$np+1]=~/^-.*/))\n{\n	    ++$np;\n	    $ligan\
d=1;\n	    $ligand_list{$ARGV[$np]}=1;	      \n} \\
n	$hc_chain{'LIGAND'}=1;\n}\n    elsif ( $value eq\
 \"-ligand_only\")\n{\n	$ligand_only=1;\n}\n}\nif \
( $debug)\n{\n    print STDERR \"\\n[DEBUG:extract\
_from_pdb] NO_REMOTE_PDB_DIR: $no_remote_pdb_dir\\\
n\";\n    print STDERR \"\\n[DEBUG:extract_from_pd\
b] PDB_DIR: $pdb_dir\\n\";\n}\n\n\nif ( $is_pdb_na\
me)\n  {\n    if (&remote_is_pdb_name($pdb_file))\\
n      {\n	print \"1\";\n      }\n    else\n      \
{\n	print \"0\";\n      }\n    exit ($EXIT_SUCCESS\
);\n  }\n\nif ( $is_released_pdb_name)\n  {\n    \\
n    if (&is_released($pdb_file))\n      {\n	print\
 \"1\";\n      }\n    else\n      {\n	print \"0\";\
\n      }\n    exit ($EXIT_SUCCESS);\n  }\nif ($mo\
del_type)\n  {\n   \n    printf \"%s\", &pdb2model\
_type($pdb_file);\n    exit ($EXIT_SUCCESS);\n    \
\n  }\n    \n\nif (!$force_name)\n{\n    $pdb_file\
=~/([^\\/]*)$/;\n    $force_name=$1;\n}\n\n$local_\
pdb_file=$pdb_file;\n\nif ( $debug){print STDERR \\
"\\n[DEBUG: extract_from_pdb] Scan For $local_pdb_\
file\\n\";}\n\n$mem=$no_remote_pdb_dir;\n$no_remot\
e_pdb_dir=1;\n$tmp_pdb_file=get_pdb_file ($local_p\
db_file);\n\nif ( !-e $tmp_pdb_file || $tmp_pdb_fi\
le eq \"\")\n  {\n    $local_pdb_file=$pdb_file;\n\
    ($local_pdb_file, $suffix_chain)=&pdb_name2nam\
e_and_chain($local_pdb_file);\n\n    if ($local_pd\
b_file)\n      {\n	if ( $debug){print STDERR \"\\n\
Split $pdb_file into $local_pdb_file and $suffix_c\
hain \\n\";}\n	$tmp_pdb_file=get_pdb_file ($local_\
pdb_file);\n	if ( $tmp_pdb_file ne \"\")\n	  {\n	 \
   @c_chain=();\n	    @c_chain=($suffix_chain);\n	\
    %hc_chain=();\n	    $hc_chain{$suffix_chain}=1\
;\n	  }\n      }\n  }\n\n$no_remote_pdb_dir=$mem;\\
nif ($no_remote_pdb_dir==0)\n  {\n    \n    if ( !\
-e $tmp_pdb_file || $tmp_pdb_file eq \"\")\n      \
{\n	\n	$local_pdb_file=$pdb_file;\n	($local_pdb_fi\
le, $suffix_chain)=&pdb_name2name_and_chain($local\
_pdb_file);\n	if ($local_pdb_file)\n	  {\n	    \n	\
    if ( $debug){print STDERR \"\\nSplit $pdb_file\
 into $local_pdb_file and $suffix_chain \\n\";}\n	\
    \n	    $tmp_pdb_file=get_pdb_file ($local_pdb_\
file);    \n	    \n	    if ( $tmp_pdb_file ne \"\"\
)\n	      {\n		@c_chain=();\n		@c_chain=($suffix_c\
hain);\n		%hc_chain=();\n		$hc_chain{$suffix_chain\
}=1;\n	      }\n	  }\n      }\n  }\n\nif ( $debug)\
{print STDERR \"\\n$pdb_file copied into ##$tmp_pd\
b_file##\\n\";}\n\nif ( !-e $tmp_pdb_file || $tmp_\
pdb_file eq \"\")\n{\n	if ($is_pdb_name)\n{\n	    \
print \"0\\n\"; exit ($EXIT_SUCCESS);\n}\n	else\n{\
\n  \n	    print \"\\nEXTRACT_FROM_PDB: NO RESULT \
for $pdb_file\\n\";\n	    &myexit ($EXIT_SUCCESS);\
	\n}\n}\n\n\n\n\n%molecule_type=&pdbfile2chaintype\
($tmp_pdb_file);\nif ( $debug){print STDERR \"\\n\\
\tSequence Type determined\\n\";}\n\n$pdb_id=&get_\
pdb_id ($tmp_pdb_file);\nif ( $debug){print STDERR\
 \"\\n\\tID: $pdb_id (for $tmp_pdb_file)\\n\";}\n\\
nif ( $pdb_id eq \"\"){$pdb_id=$force_name;}\n\n@f\
_chain=&get_chain_list ($tmp_pdb_file);\nif ( $deb\
ug){print STDERR \"\\n\\tChain_list:@f_chain\\n\";\
}\n\nif ( $get_pdb_chains)\n{\n    print \"@f_chai\
n\\n\";\n    &myexit ($EXIT_SUCCESS);\n}\nif ( $ge\
t_pdb_ligands)\n{\n    %complete_ligand_list=&get_\
ligand_list ($tmp_pdb_file);\n    print $complete_\
ligand_list{\"result\"};\n    &myexit ($EXIT_SUCCE\
SS);\n}\n\nelsif ( $get_pdb_id ||$get_fugue_name )\
\n{\n    if    (@c_chain && $c_chain[0] eq \"FIRST\
\"){$pdb_id=$pdb_id.$f_chain[0];}\n    elsif (@c_c\
hain && $c_chain[0] ne \" \"){$pdb_id=$pdb_id.$c_c\
hain[0];}\n    \n    print \"$pdb_id\\n\";\n    &m\
yexit ($EXIT_SUCCESS);\n    \n}\nelsif ( $is_pdb_n\
ame)\n{\n    printf \"1\\n\";\n    &myexit ($EXIT_\
SUCCESS);\n}\n\n\n\n$structure_file=vtmpnam();\n\n\
if ( $debug){print STDERR \"\\n\\tCheck_point #1: \
$tmp_pdb_file  $structure_file\\n\";}\n\n$INFILE=v\
fopen (\"$tmp_pdb_file\", \"r\"); \n$TMP=vfopen (\\
"$structure_file\", \"w\");\n\n$print_model=1;\n$i\
n_model=0;\n\nif ( $debug){print STDERR \"\\n\\tCh\
eck_point #2\\n\";}\nwhile ( <$INFILE>)\n{\n  my $\
first_model=0;\n  $line=$_;\n\n  if ( !$first_mode\
l && ($line =~/^MODEL\\s*(\\d*)/))\n    {\n      $\
first_model=$1;\n      if ($model==1){$model=$firs\
t_model;}\n    }\n  \n  if (($line =~/^MODEL\\s*(\\
\d*)/))\n    {\n      if ($1==$model)\n	{\n	  $in_\
model=1;\n	  $print_model=1;\n	  $is_nmr=1;\n	}\n \
     elsif ( $in_model==0)\n	{\n	  $print_model=0;\
\n	}\n      elsif ( $in_model==1)\n	{\n	  last;\n	\
}\n    }\n  if ($print_model){print $TMP $line;}  \
\n}\nclose ($TMP);\nclose ($INFILE);\n\nif ( $debu\
g){print STDERR \"\\n\\tCheck_point #3\\n\";}	\n\n\
  if ($numbering eq \"\"){$numbering=\"absolute\";\
}\n  if ($numbering_out eq \"\"){$numbering_out=\"\
new\";}\n\n  if ( $delete_set && $coor_set) {die \\
"-delete and -coor are mutually exclusive, sorry\\\
n\";}\n  if ( $n_atom==0){$atom_list[$n_atom++]=\"\
ALL\";$atom_list{$atom_list[0]}=1;}\n  if ( $seq_f\
ield eq \"\"){$seq_field=\"ATOM\";}\n  \n  if ( $M\
ODE eq \"\"){$MODE=\"pdb\";}\n  elsif ( $MODE eq \\
"simple\" && $code==0){$code=1;}\n\n  if ( $code==\
0){$code=3;}\n\n\nif ($f_chain[0] eq \" \"){$hc_ch\
ain{' '}=1;$c_chain[0]=\" \";}\nelsif (!@c_chain){\
$hc_chain{FIRST}=1;$c_chain[0]=\"FIRST\";}#make su\
re the first chain is taken by default\n\nif    ($\
hc_chain{ALL}) \n{\n      @c_chain=@f_chain;\n    \
  foreach $e (@c_chain){$hc_chain{$e}=1;}\n}\nelsi\
f($hc_chain{FIRST})\n{\n	@c_chain=($f_chain[0]);\n\
	$hc_chain{$f_chain[0]}=1;\n}\n\n\n$MAIN_HOM_CODE=\
&get_main_hom_code ($structure_file);\n$INFILE=vfo\
pen ($structure_file, \"r\");\n\n\nif ( $MODE eq \\
"raw_pdb\" || $MODE eq \"raw\")\n{\n    while (<$I\
NFILE>)\n{	print \"$_\";}\n    close ( $INFILE);\n\
    &myexit($EXIT_SUCCESS);\n}    \nif ( $MODE eq \
\"raw4fugue\" )\n{\n    while (<$INFILE>)\n{	\n	$l\
=$_;\n	if ($l=~/^SEQRES/)\n{\n	    \n	    $c= subs\
tr($l,11,1);\n	    if ($hc_chain {$c}){print \"$l\\
";}\n}\n	elsif ( $l=~/^ATOM/)\n{\n	    $c=substr($\
l,21,1);\n	    if ($hc_chain {$c}){print \"$l\";}\\
n}\n}\n    close ( $INFILE);\n    &myexit($EXIT_SU\
CCESS);\n}    \n\nif ( $MODE eq \"pdb\")\n{\n\n   \
 $read_header=0;\n    while (<$INFILE>) \n{\n	    \
$line=$_;\n	    if    ($line =~ /^HEADER/){print \\
"$line\";$read_header=1;}\n}\n    close ($INFILE);\
\n\n    if (!$read_header)\n{\n	print \"HEADER    \
UNKNOWN                                 00-JAN-00 \
  $force_name\\n\";\n}\n\n    $INFILE=vfopen ($str\
ucture_file, \"r\");\n    \n    print \"COMPND   1\
 CHAIN:\";\n    $last=pop(@c_chain);\n    foreach \
$c ( @c_chain){ print \" $c,\";}\n    if ( $last e\
q \" \"){print \" NULL;\\n\";}\n    else \n{\n    \
  print \" $last;\\n\";\n}\n    @c_chain=(@c_chain\
, $last);\n    \n    print \"REMARK Output of the \
program extract_from_pdb (Version $VersionTag)\\n\\
";\n    print \"REMARK Legal PDB format not Guaran\
teed\\n\";\n    print \"REMARK This format is not \
meant to be used in place of the PDB format\\n\";\\
n    print \"REMARK The header refers to the origi\
nal entry\\n\";\n    print \"REMARK The sequence f\
rom the original file has been taken in the field:\
 $seq_field\\n\";\n    print \"REMARK extract_from\
_pdb, 2001, 2002, 2003, 2004, 2005 2006 (c) CNRS a\
nd Cedric Notredame\\n\";   \n    if ( $coor_set)\\
n{\n       print \"REMARK Partial chain: Start $st\
art End $end\\n\";\n}\n    if ( $is_nmr)\n{\n     \
  print \"REMARK NMR structure: MODEL $model\\n\";\
\n}\n   \n    if ( $n_atom!=0)\n{\n       print \"\
REMARK Contains Coordinates of: \";\n       foreac\
h $a (@atom){print \"$a \";}\n       print \"\\n\"\
;\n}  \n}\n\n\n\n\nmy $residue_index = -999;\nmy $\
old_c = \"TemporaryChain\";\n\nwhile (<$INFILE>) \\
n{\n	$line=$_;\n\n\n	if ($line =~ /^SEQRES/)\n{\n\\
n		@field=/(\\S*)\\s*/g;\n\n		$c= substr($_,11,1);\
\n\n		\n		$l=$#field;\n		for ($a=4; $a<$#field ;)\\
n{\n			if (!$onelett{$molecule_type{$c}}->{$field[\
$a]})\n{\n				splice @field, $a, 1;\n}\n			else \n\
{\n				$a++;\n}\n}\n	\n		if ( $c ne $in_chain)\n{\\
n			$pdb_chain_list[$n_pdb_chains]=$c;\n			$pdb_ch\
ain_len [$n_pdb_chains]=$len;\n			$in_chain=$c;\n	\
		$n_pdb_chains++;\n}\n	\n		for ( $a=4; $a<$#field\
;$a++)\n{\n			@{$complete_seq{$c}}->[$complete_seq\
_len{$c}++]=$field[$a];\n}\n}\n    elsif ( $line=~\
/^ATOM/ || ($line=~/^HETATM/ && &is_aa(substr($lin\
e,17,3),substr($line,21,1)) && !$no_hetatm))\n{\n\\
n	 \n    $RAW_AT_ID=$AT_ID=substr($line,12,4);\n	$\
RES_ID=&is_aa(substr($line,17,3),substr($line,21,1\
));\n	$CHAIN=substr($line,21,1);\n\n    $RES_NO=su\
bstr($line,22,4);\n	$HOM_CODE=substr ($line, 26, 1\
);\n	$TEMP=substr($line,60,6);\n	\n	$TEMP=~s/\\s//\
g;\n        $AT_ID=~s/\\s//g;\n	$RES_ID=~s/\\s//g;\
\n        $RES_NO=~s/\\s//g;\n		\n	if ( $HOM_CODE \
ne $MAIN_HOM_CODE){next;}\n	elsif ( $already_read2\
{$CHAIN}{$RES_ID}{$AT_ID}{$RES_NO}){next;}\n	else{\
$already_read2{$CHAIN}{$RES_ID}{$AT_ID}{$RES_NO}=1\
;}\n	\n	\n	if ($coor_set && $numbering eq \"file\"\
 && $residue_index ne $RES_NO)\n{\n	    \n	    if \
( $RES_NO<=$start){$real_start{$CHAIN}++;}\n	    i\
f ( $RES_NO<=$end){$real_end{$CHAIN}++;}\n}\n	elsi\
f ($numbering eq \"absolute\")\n{\n	    $real_star\
t{$CHAIN}=$start;\n	    $real_end{$CHAIN}=$end;\n}\
\n\n        $KEY=\"ALL\";\n        if ( $CHAIN ne \
$in_atom_chain)\n{\n	    \n	  $pdb_atom_chain_list\
[$n_pdb_atom_chains]=$c;\n	  $pdb_atom_chain_len [\
$n_pdb_atom_chains]=$len;\n	  $in_atom_chain=$c;\n\
	  $n_pdb_atom_chains++;\n}\n	\n	if ( $residue_ind\
ex ne $RES_NO)\n{\n	     $residue_index = $RES_NO;\
\n	     @{$atom_seq{$CHAIN}}->[$atom_seq_len{$CHAI\
N}++]=$RES_ID;;\n}\n}\n\n}\nclose ($INFILE);\n\n\n\
\n\n\n\n$INFILE=vfopen ($structure_file, \"r\");\n\
foreach $c (@c_chain)\n{\n\n	if    ( $seq_field eq\
 \"SEQRES\"){@pdb_seq=@{$complete_seq{$c}};}\n	els\
if ( $seq_field eq \"ATOM\")  {@pdb_seq=@{$atom_se\
q{$c}};}\n	\n\n	$full_length=$l=$#pdb_seq+1;\n		\n\
	if ( $real_end{$c}==\"*\"){$real_end{$c}=$full_le\
ngth;}\n	if ( $coor_set)\n{	   \n\n	   if ( $real_\
end{$c} < $l){splice @pdb_seq, $real_end{$c}, $l;}\
\n	   if ( $real_start{$c} < $l){splice @pdb_seq, \
0, $real_start{$c}-1;}	  	   \n	   $l=$#pdb_seq;\n\
}\n\n	elsif ( $delete_set)\n{\n	   splice @pdb_seq\
, $delete_start, $delete_end-$delete_start+1;\n	  \
 $l=$#pdb_seq;\n}\n	\n	$new_fasta_name=\"$pdb_id$c\
\";\n	if ( $coor_set)\n{\n	   if ( $n_pdb_chains==\
0){$new_fasta_name=\"$new_fasta_name$c\";}\n	   $n\
ew_fasta_name= $new_fasta_name.\"\\_$start\\_$end\\
";\n}\n	   \n	if ( $MODE eq \"pdb\")\n{\n	   $nl=1\
;\n	   $n=0;\n	   \n	   foreach $res ( @pdb_seq)\n\
		{\n		if ( !$n)\n		{\n		\n		 printf \"SEQRES %3d \
%1s %4d  \", $nl,$c, $l;\n		 $nl++;\n	}\n	     $re\
s=~s/\\s//g;\n	     \n	     if ($code==1){ printf \
\"%3s \",$onelett{$molecule_type{$c}}->{$res};}\n	\
     elsif  ($code==3){ printf \"%3s \",$res};\n	 \
    \n	     $n++;		  \n	     if ( $n==13){$n=0;pri\
nt \"\\n\";}\n}\n	  if ( $n!=0){print \"\\n\"; $n=\
0;}\n}\n	elsif ( $MODE eq \"simple\")\n{\n	  print\
 \"# SIMPLE_PDB_FORMAT\\n\";\n	  if ( $new_fasta_n\
ame eq \" \"){$new_fasta_name=\"dummy_name\";}\n	 \
 print \">$new_fasta_name\\n\";\n\n	  foreach $res\
 ( @pdb_seq)\n{\n	      print \"$onelett{$molecule\
_type{$c}}->{$res}\";\n}\n	  print \"\\n\";\n}\n	e\
lsif ( $MODE eq \"fasta\")\n{\n	  $n=0;\n	  print \
\">$new_fasta_name\\n\";\n	  \n	  foreach $res ( @\
pdb_seq)\n{\n\n	      print \"$onelett{$molecule_t\
ype{$c}}->{$res}\";\n              $n++;\n	      i\
f ( $n==60){print \"\\n\"; $n=0;}\n}\n	  print \"\\
\n\"; \n}\n}\n\nif ( $MODE eq \"fasta\")\n{\n     \
&myexit($EXIT_SUCCESS);\n  \n}\n\n  \n  $charcount\
=0;\n  $inchain=\"BEGIN\";\n  $n=0;\n  while (<$IN\
FILE>) \n{\n    $line=$_;\n     \n    if ($line =~\
/^ATOM/  ||  ($line=~/^HETATM/))\n{\n	$line_header\
=\"UNKNWN\";\n	$RES_ID=substr($line,17,3);\n	$chai\
n = substr($line,21,1);\n\n	if ($line =~/^ATOM/)\n\
{\n	    $line_header=\"ATOM\";\n	    $RES_ID=(&is_\
aa($RES_ID,$chain))?&is_aa($RES_ID,$chain):$RES_ID\
;\n}\n	elsif ($line=~/^HETATM/ && ($ligand_list {$\
RES_ID} ||$ligand_list {'ALL'} || !&is_aa($RES_ID,\
$chain)))\n{\n	    $line_header=\"HETATM\";\n}\n	e\
lsif ($line=~/^HETATM/ && (&is_aa($RES_ID,$chain) \
&& !$no_hetatm))\n{\n	    $line_header=\"ATOM\";\n\
	    $RES_ID=&is_aa($RES_ID,$chain);\n}\n	else\n{\\
n	    next;\n}\n\n	\n\n	$X=substr($line,30,8);    \
 \n	$Y=substr($line,38,8);\n	$Z=substr($line,46,8)\
;\n	$TEMP=substr($line,60,6);\n	\n	$RAW_AT_ID=$AT_\
ID=substr($line,12,4);\n	$CHAIN=substr($line,21,1)\
;\n	$RES_NO=substr($line,22,4);\n	$HOM_CODE=substr\
 ($line, 26, 1);\n	\n	$X=~s/\\s//g;\n	$Y=~s/\\s//g\
;\n	$Z=~s/\\s//g;\n	$TEMP=~s/\\s//g;\n	\n	$AT_ID=~\
s/\\s//g;\n	$RES_ID=~s/\\s//g;\n	$RES_NO=~s/\\s//g\
;\n\n	\n	if ( $HOM_CODE ne $MAIN_HOM_CODE){next;}\\
n	elsif ( $already_read{$CHAIN}{$RES_ID}{$AT_ID}{$\
RES_NO}){next;}\n	else{$already_read{$CHAIN}{$RES_\
ID}{$AT_ID}{$RES_NO}=1;}\n	\n	$KEY=\"ALL\";\n\n   \
   	if ( $RES_NO ==0){$start_at_zero=1;}\n\n	$RES_\
NO+=$start_at_zero;    \n	\n	if ( $current_chain n\
e $CHAIN)\n{\n	    $current_chain=$CHAIN;\n	    $p\
os=$current_residue=0;\n	    $offset=($coor_set)?(\
$real_start{$CHAIN}-1):0;\n	    if    ( $seq_field\
 eq \"SEQRES\"){@ref_seq=@{$complete_seq{$CHAIN}};\
}\n	    elsif ( $seq_field eq \"ATOM\")  {@ref_seq\
=@{$atom_seq{$CHAIN}};}\n}\n	\n	if ($current_resid\
ue != $RES_NO)\n{\n	    $current_residue=$RES_NO;\\
n	    if    ( $seq_field eq \"SEQRES\"){$pos=$curr\
ent_residue;}\n	    elsif ( $seq_field eq \"ATOM\"\
){$pos++;}\n}\n	\n	\n	if ($n_atom==0 || $atom_list\
{$AT_ID}==1 || $atom_list{$KEY}==1)\n{ 	\n	    \n	\
    $do_it=(!@c_chain || $hc_chain{$CHAIN} ||$hc_c\
hain{'LIGAND'} );\n	    \n	    $do_it= ($do_it==1)\
 && ($coor_set==0 ||($pos>=$real_start{$CHAIN} && \
$pos<=$real_end{$CHAIN}));\n	    $do_it= ($do_it==\
1) && ($delete_set==0 || $pos<$delete_start ||$pos\
>$delete_end );\n	    if ($ligand==0 && $line_head\
er eq \"HETATM\" ){$do_it=0;}\n	    if ($ligand_on\
ly==1 && $line_header eq \"ATOM\" ){$do_it=0;}\n	 \
   if ($ligand==1 && $line_header eq \"HETATM\" &&\
 $ligand_list{$RES_ID}==0 && $ligand_list{\"ALL\"}\
==0){$do_it=0;} \n	    \n	    \n	    if ( $do_it)\\
n{\n		$n++;\n		$out_pos=$pos;\n		\n	       if ( $d\
elete_set)\n{\n		  if ( $out_pos< $delete_start){;\
}\n		  else {$offset=$delete_end-$delete_start;}\n\
}       \n	       \n	       if ( $numbering_out eq\
 \"new\"){$out_pos-=$offset;}\n	       elsif ( $nu\
mbering_out eq \"old\"){$out_pos=$RES_NO;}\n	     \
  \n       \n	       \n	       if ( $code==1){$RES\
_ID=$onelett{$molecule_type{$c}}->{$RES_ID};}\n	  \
  \n	       if ($unfold)\n{\n		   $unfolded_x+=5;\\
n		   $X=$unfolded_x;\n		   $Y=0;\n		   $Z=0;\n		 \
  $float=1;\n}\n	       else\n{\n		   $float=3;\n}\
\n\n	       if ( $MODE eq \"pdb\")\n{\n		   printf\
 \"%-6s%5d %-4s %3s %s%4d    %8.3f%8.3f%8.3f  1.00\
 %5.2f\\n\",$line_header, $n, $RAW_AT_ID,$RES_ID,$\
CHAIN,$out_pos, $X, $Y, $Z,$TEMP;		  \n}\n	       \
elsif ( $MODE eq \"simple\")\n{\n		    if ( $RES_I\
D eq \"\"){$RES_ID=\"X\";}\n		  printf \"%-6s %5s \
%s %2s %4d    %8.3f %8.3f %8.3f\\n\",$line_header,\
 $AT_ID, $RES_ID,($CHAIN eq\"\" || $CHAIN eq \" \"\
)?\"A\":$CHAIN,$out_pos, $X, $Y, $Z,$TEMP;\n}\n\n}\
\n}\n}\n}\nprint \"\\n\";\nclose($INFILE);\n\n\nif\
 ( $error ne \"\") \n{$error=$error.\"\\nDiagnosti\
c:    SEQRES and the residues in ATOM are probably\
 Incompatible\\n\";\n    $error=$error.  \"Recomen\
dation: Rerun with '-fix 1' in order to ignore the\
 SEQRES sequences\\n\";\n}\nif (!$nodiagnostic){pr\
int STDERR $error;}\n&myexit ( $EXIT_SUCCESS);\n\n\
sub is_released \n  {\n    my ($r);\n    my $in=@_\
[0];\n    my $name=&remote_is_pdb_name ($in);\n   \
 my $hold=&remote_is_on_hold($in);\n    \n    $r=(\
$name && !$hold)?1:0;\n    return $r;\n  }\nsub re\
mote_is_pdb_name \n{\n    my $in=@_[0];\n    my ($\
ref_file, $pdb);\n    my ($value,$value1,$value2);\
\n\n    if ( $in=~/[^\\w\\d\\:\\_]/){return 0;}\n \
   $ref_file=\"$cache/pdb_entry_type.txt\";\n    \\
n    if ( !-e $ref_file || (-M $ref_file)>2 || -z \
$ref_file)\n      {\n	&url2file(\"ftp://ftp.wwpdb.\
org/pub/pdb/derived_data/pdb_entry_type.txt\", $re\
f_file);\n      }\n    $pdb=substr ($in,0, 4);\n  \
  chomp(($value1=`grep -c $pdb $ref_file`));\n    \
$pdb=lc($pdb);\n    chomp(($value2=`grep -c $pdb $\
ref_file`));\n    $value=($value1 || $value2)?1:0;\
\n    $value=($value>0)?1:0;\n    \n    return $va\
lue;\n  }\n\nsub pdb2model_type\n{\n    my $in=@_[\
0];\n    my ($ref_file, $pdb);\n    my ($value, $r\
et);\n\n    if ( $in=~/[^\\w\\d\\:\\_]/){return 0;\
}\n    $ref_file=\"$cache/pdb_entry_type.txt\";\n \
   \n    if ( !-e $ref_file || (-M $ref_file)>2 ||\
 -z $ref_file)\n      {\n	&url2file(\"ftp://ftp.ww\
pdb.org/pub/pdb/derived_data/pdb_entry_type.txt\",\
 $ref_file);\n      }\n    $pdb=substr ($in,0, 4);\
\n    $pdb=lc($pdb);\n    \n    chomp(($value=`gre\
p $pdb $ref_file`));\n    \n    $value=~/^\\S+\\s+\
\\S+\\s+(\\S+)/;\n    $ret=$1;\n    if ( $ret eq\"\
\"){return \"UNKNOWN\";}\n    \n    return $ret;\n\
  }\nsub remote_is_on_hold\n  {\n    my $in=@_[0];\
\n    my ($ref_file, $pdb);\n    my ($value1, $val\
ue2,$value);\n    \n    if ( $in=~/[^\\w\\d\\:\\_]\
/){return 0;}\n    $ref_file=\"$cache/unreleased.x\
ml\";\n    \n    if ( !-e $ref_file || (-M $ref_fi\
le)>2 || -z $ref_file)\n      {\n	&url2file(\"http\
://www.rcsb.org/pdb/rest/getUnreleased\",$ref_file\
);\n      }\n    \n    $pdb=substr ($in,0, 4);\n  \
  chomp(($value1=`grep -c $pdb $ref_file`));\n    \
$pdb=lc($pdb);\n    chomp(($value2=`grep -c $pdb $\
ref_file`));\n    $value=($value1 || $value2)?1:0;\
\n    $value=($value>0)?1:0;\n    return $value;\n\
  }\nsub is_pdb_file\n{\n    my @arg=@_;\n\n    if\
 ( !-e $arg[0]){return 0;}\n    \n    $F=vfopen ($\
arg[0], \"r\");\n    while ( <$F>)\n{\n	if (/^HEAD\
ER/)\n{\n	    close $F;\n	    return 1;\n}\n	elsif\
 ( /^SEQRES/)\n{\n	    close $F;\n	    return 1;\n\
}\n	elsif ( /^ATOM/)\n{\n	    close $F;\n	    retu\
rn 1;\n}\n}\n    return 0;\n}\nsub get_pdb_id\n{\n\
    my $header_file=@_[0];\n    my $id;\n    my $F\
= new FileHandle;\n    \n    \n    $F=vfopen (\"$h\
eader_file\", \"r\");\n\n    while ( <$F>)\n      \
{\n	if ( /HEADER/)\n	  {\n	    if ($debug){print \\
"$_\";}\n	    $id=substr($_,62,4 );\n	    return $\
id;\n	  }\n      }\n    close ($F);\n    \n    ret\
urn \"\";\n}\n\nsub get_ligand_list\n{\n    my $pd\
b_file=@_[0];\n    my $chain;\n    my $ligand;\n  \
  my %complete_ligand_list;\n    \n\n    $F=vfopen\
 ($pdb_file, \"r\");\n    while ( <$F>)\n{\n	if ( \
/^HETATM/)\n{\n	    $line=$_;\n	    $chain=substr(\
$line,21,1);\n	    $ligand=substr($line,17,3);\n	 \
   \n	    if (!$complete_ligand_list{$chain}{$liga\
nd})\n{\n		\n		$complete_ligand_list{\"result\"}.=\
\"CHAIN $chain LIGAND $ligand\\n\";\n		$complete_l\
igand_list{$chain}{$ligand}=1;\n}\n}\n}\n    close\
 ($F);\n    return %complete_ligand_list;\n}\n\nsu\
b get_chain_list \n{\n    my $header_file;\n    my\
 @chain_list;\n    my @list;\n    my $n_chains;\n \
   my %chain_hasch;\n    my $pdb_file=@_[0];\n    \
my $c;\n    my %hasch;\n    my $chain;\n  \n    \n\
    $F=vfopen ($pdb_file, \"r\");\n    while ( <$F\
>)\n{\n\n\n	if (/SEQRES\\s+\\d+\\s+(\\S+)/)\n	  {\\
n	    $chain = substr($_,11,1);$chain=~s/\\s//g;if\
 ( $chain eq \"\"){$chain=\" \";}\n	    if (!$hasc\
h{$chain}){$hasch{$chain}=1;push @chain_list, $cha\
in;}\n	  }\n	if (/^ATOM/ || /^HETATM/)\n	  {\n	   \
 $chain = substr($_,21,1); $chain=~s/\\s//g;if ( $\
chain eq \"\"){$chain=\" \";}\n	    if (!$hasch{$c\
hain}){$hasch{$chain}=1;push @chain_list, $chain;}\
\n	  }\n      }\n\n\nclose ($F);\nif (!@chain_list\
)\n  {\n    @chain_list=(\"A\");\n  }\n\n\nreturn \
@chain_list;\n}\n\nsub token_is_in_list\n{\n\n    \
my @list=@_;\n    my $a;\n    \n    for ($a=1; $a<\
=$#list; $a++)\n{\n	if ( $list[$a] eq $list[0]){re\
turn $a;}\n}\n}\n\nsub pdb_name2name_and_chain \n{\
\n    my $pdb_file=@_[0];\n    my $pdb_file_in;\n \
   my @array;\n    my $chain;\n    my $c;\n\n    $\
pdb_file_in=$pdb_file;\n\n    $pdb_file=~/^(.{4})/\
;$pdb_id=$1;\n    @array=($pdb_file=~/([\\w])/g);\\
n  \n  \n    $chain=uc ($array[4]);\n    $chain=($\
chain eq \"\")?\"FIRST\":$chain;\n    \n    return\
 ( $pdb_id, $chain);\n\n    if ( $#array==3){retur\
n ($pdb_id, \"FIRST\");}\n    elsif ( $#array<4){ \
return ($pdb_id, \"\");}\n    else {return ( $pdb_\
id, $chain);}\n      \n    \n    \n}\nsub get_main\
_hom_code \n{\n    my $pdb_file=@_[0];\n    my %ho\
m, $n, $best, $best_h;\n    open (F, $pdb_file);\n\
    while (<F>)\n{\n	if ( $_=~/^ATOM/)\n{\n	    $h\
=substr ($_,26, 1);\n	    $n=++$hom{$h};\n	    if \
($n>$best)\n{\n		$best=$n;\n		$best_h=$h;\n}\n}\n}\
\n    close (F);\n    return $best_h;\n}\n\n\nsub \
get_pdb_file \n{\n    my ($pdb_file_in)=(@_);\n   \
 my $result;\n    my @letter;\n    my @chain;\n   \
 my $v;\n    my $pdb_file=$pdb_file_in;\n\n    $pd\
b_file=($pdb_file_in=~/\\S+_S_(\\S+)/)?$1:$pdb_fil\
e_in;\n    \n    if ($no_remote_pdb_dir==0)\n     \
 {\n	$no_remote_pdb_dir=1;\n	$result=get_pdb_file3\
 ($pdb_file);\n	$no_remote_pdb_dir=0;\n	if ( $resu\
lt){return $result;}\n	else\n	  {\n	    \n	    lc \
($pdb_file);\n	    $result=get_pdb_file3($pdb_file\
);\n	    return  $result;\n	  }\n      }\n    else\
\n      {\n	return get_pdb_file3 ($pdb_file);\n   \
   }\n    \n  }\n\nsub get_pdb_file3 \n{\n    my $\
pdb_file_in=@_[0];\n    my $result;\n    my @lette\
r;\n    my @chain;\n    my $lcfile;\n    my $ucfil\
e;\n    my $pdb_file=$pdb_file_in;\n    \n    $lcf\
ile=lc $pdb_file;\n    $ucfile=uc $pdb_file;\n\n  \
  if ( ($result=get_pdb_file2 ($pdb_file))){return\
 $result;}\n    \n\n    if ($lcfile ne $pdb_file &\
& ($result=get_pdb_file2 ($lcfile))){return $resul\
t;}\n    if ($ucfile ne $pdb_file && ($result=get_\
pdb_file2 ($ucfile))){return $result;}\n    \n   \\
n    \n    return \"\";\n}\nsub get_pdb_file2\n{\n\
    my $pdb_file=@_[0];\n    my $return_value;\n  \
  \n    $return_value=\"\";\n    \n    if ( ($resu\
lt=get_pdb_file1 ($pdb_file))){$return_value=$resu\
lt;}\n    elsif ( !($pdb_file=~/\\.pdb/) && !($pdb\
_file=~/\\.PDB/))\n{\n	if ( ($result=get_pdb_file1\
 (\"$pdb_file.pdb\"))){$return_value=$result;}\n	e\
lsif ( ($result=get_pdb_file1 (\"$pdb_file.PDB\"))\
){$return_value=$result;}\n\n	elsif ( ($result=get\
_pdb_file1 (\"pdb$pdb_file.pdb\"))){$return_value=\
$result;}	\n	elsif ( ($result=get_pdb_file1 (\"pdb\
$pdb_file.PDB\"))){$return_value=$result;}\n	elsif\
 ( ($result=get_pdb_file1 (\"PDB$pdb_file.PDB\")))\
{$return_value=$result;}\n	elsif ( ($result=get_pd\
b_file1 (\"PDB$pdb_file.pdb\"))){$return_value=$re\
sult;}\n	\n	\n	elsif ( ($result=get_pdb_file1 (\"$\
pdb_file.ent\"))){$return_value=$result;}\n	elsif \
( ($result=get_pdb_file1 (\"pdb$pdb_file.ent\"))){\
$return_value=$result;}\n	elsif ( ($result=get_pdb\
_file1 (\"PDB$pdb_file.ent\"))){$return_value=$res\
ult;}\n\n	elsif ( ($result=get_pdb_file1 (\"$pdb_f\
ile.ENT\"))){$return_value=$result;}\n	elsif ( ($r\
esult=get_pdb_file1 (\"pdb$pdb_file.ENT\"))){$retu\
rn_value=$result;}\n	elsif ( ($result=get_pdb_file\
1 (\"PDB$pdb_file.ENT\"))){$return_value=$result;}\
\n	\n	\n	\n}\n    return $return_value;\n}\n    \n\
sub get_pdb_file1\n{\n    my ($pdb_file)=(@_);\n  \
  my $return_value;\n    \n\n    $return_value=\"\\
";\n    if ( ($result=get_pdb_file0 ($pdb_file))){\
$return_value=$result;}\n    elsif ( ($result=get_\
pdb_file0 (\"$pdb_file.Z\"))){$return_value=$resul\
t;}\n    elsif ( ($result=get_pdb_file0 (\"$pdb_fi\
le.gz\"))){$return_value=$result;}\n    elsif ( ($\
result=get_pdb_file0 (\"$pdb_file.GZ\"))){$return_\
value=$result;}\n    return $return_value;\n}\nsub\
 get_pdb_file0 \n{ \n    my ($pdb_file, $attempt)=\
(@_);\n    my $pdb_file=@_[0];\n    my $tmp_pdb_fi\
le;    \n    my $return_value;\n\n    if ( !$attem\
pt){$attempt=1;}\n    \n    $local_pdb_file=\"$pdb\
_file\";\n    if ( $local_pdb_file eq \"\")\n{\n	$\
tmp_pdb_file=vtmpnam();\n	open F, \">$tmp_pdb_file\
\";\n	\n	while (<STDIN>){print F \"$_\";}\n	close \
(F);\n	\n	if (-e $tmp_pdb_file && &is_pdb_file ( $\
local_pdb_file))\n{return $tmp_pdb_file;}\n}\n\n  \
  $local_pdb_file=\"$pdb_file\";\n    &debug_print\
 (\"\\nTry access local file: $local_pdb_file\");\\
n    \n    $local_pdb_file=&check_pdb_file4compres\
sion ($local_pdb_file);\n    if ( -e $local_pdb_fi\
le && (&is_pdb_file ($local_pdb_file) || $force_pd\
b))\n{\n	&debug_print ( \"\\n\\tIs in Current Dir\\
");\n	$tmp_pdb_file=vtmpnam();\n	`cp $local_pdb_fi\
le $tmp_pdb_file`;\n	return $tmp_pdb_file;\n}\n   \
 else\n{\n	&debug_print (\"\\n\\tFile Not in Curre\
nt Dir\");\n}\n\n    if ($pdb_file=~/^pdb/||$pdb_f\
ile=~/^PDB/){$pdb_div=substr ($pdb_file, 4, 2);}\n\
    else\n{\n	  $pdb_div=substr ($pdb_file, 1, 2);\
\n}\n    $local_pdb_file=\"$pdb_dir/$pdb_div/$pdb_\
file\";\n    $local_pdb_file=&check_pdb_file4compr\
ession ( $local_pdb_file);\n    &debug_print (\"\\\
nTry access file From PDB_DIR: $local_pdb_file\");\
\n    if ($pdb_dir && -e $local_pdb_file && &is_pd\
b_file ($local_pdb_file))\n{\n	&debug_print ( \"\\\
n\\tIs in Local PDB DIR\");\n	$tmp_pdb_file=vtmpna\
m();\n	`cp $local_pdb_file $tmp_pdb_file`;\n	retur\
n $tmp_pdb_file;\n}\n\n    $local_pdb_file=\"$pdb_\
dir/$pdb_file\";\n    $local_pdb_file=&check_pdb_f\
ile4compression ( $local_pdb_file);\n    &debug_pr\
int (\"\\nTry access file From PDB_DIR: local_pdb_\
file\");\n    if ($pdb_dir && -e $local_pdb_file &\
& &is_pdb_file ($local_pdb_file))\n{\n	&debug_prin\
t ( \"\\n\\tIs in Local PDB DIR\");\n	$tmp_pdb_fil\
e=vtmpnam();\n	`cp $local_pdb_file $tmp_pdb_file`;\
\n	return $tmp_pdb_file;\n}\n\n    $local_pdb_file\
=\"$pdb_dir$pdb_file\";\n    $local_pdb_file=&chec\
k_pdb_file4compression ( $local_pdb_file);\n    &d\
ebug_print (\"\\nTry access file From PDB_DIR: $lo\
cal_pdb_file\");\n    if ($pdb_dir && -e $local_pd\
b_file && &is_pdb_file ($local_pdb_file))\n{\n	&de\
bug_print ( \"\\n\\tIs in Local PDB DIR\");\n	$tmp\
_pdb_file=vtmpnam();\n	`cp $local_pdb_file $tmp_pd\
b_file`;\n	return $tmp_pdb_file;\n}\n    else\n{&d\
ebug_print ( \"\\n\\tNot In Local Pdb Dir\");}\n\n\
    if ($cache ne \"NO\" && $cache ne \"no\")\n{\n\
\n	$local_pdb_file=\"$cache/$pdb_file\";\n	$local_\
pdb_file=&check_pdb_file4compression ( $local_pdb_\
file);\n	&debug_print(\"\\nTry access file From Ca\
che: $local_pdb_file\");\n	if (-e $local_pdb_file \
&& &is_pdb_file ($local_pdb_file))\n{\n	    &debug\
_print ( \"\\n\\tIs in T-Coffee Cache\");\n	    $t\
mp_pdb_file=vtmpnam();\n	    `cp $local_pdb_file $\
tmp_pdb_file`;\n	    return $tmp_pdb_file;\n}\n	el\
se{&debug_print ( \"\\n\\tNot in Cache Dir\");}\n}\
\n\nif (!$no_remote_pdb_dir) \n  {\n    my $value=\
&is_released ($pdb_file);\n    my $return_value=\"\
\";\n    if ($value==1)\n      {\n	\n	&debug_print\
 (\"\\n*******************************************\
**********\\nTry Remote Access for $pdb_file\");\n\
	$tmp_pdb_file=vtmpnam();\n	$netcommand=$netaddres\
s;\n	$netcommand=~s/%%/$pdb_file/g;\n	&url2file(\"\
$netcommand\", \"$tmp_pdb_file.$netcompression\");\
\n	&debug_print(\"\\nREMOTE: $netcommand\\n\");\n	\
\n	$compressed_tmp_file_name=\"$tmp_pdb_file.$netc\
ompression\";\n	\n	if ($netcompression && -B $comp\
ressed_tmp_file_name)\n	  {\n	    my $r;\n	    &de\
bug_print (\"\\n\\tFile Found Remotely\");\n	    i\
f (($r=safe_system ( \"$netcompression_pg $compres\
sed_tmp_file_name\")!=$EXIT_SUCCESS) && $attempts<\
5)\n	      {\n		&debug_print (\"\\n\\tProper Downl\
oad Failed Try again\");\n		unlink $compressed_tmp\
_file_name;\n		print \"\\nFailed to Download $comp\
ressed_tmp_file_name. New Attempt $attempt/5\\n\";\
\n		return &get_pdb_file0($pdb_file, $attempt+1);\\
n	      }\n	    elsif ($r== $EXIT_SUCCESS)\n	     \
 {\n		&debug_print (\"\\n\\tProper Download Succee\
ded \");\n		$return_value=$tmp_pdb_file;\n	      }\
\n	    else\n	      {\n		&debug_print (\"\\n\\tPro\
per Download Failed \");\n		&debug_print (\"\\nFil\
e Not Found Remotely\");\n		unlink $compressed_tmp\
_file_name;\n	      }\n	  }\n	else\n	  {\n\n	    &\
debug_print (\"\\nFile Not Found Remotely\");\n	  \
  unlink $compressed_tmp_file_name;\n	  }\n	#Updat\
e cache if required\n	if ($cache ne \"no\" && $cac\
he ne \"update\" && -e $return_value)\n	  {\n	    \
`cp $return_value $cache/$pdb_file.pdb`;\n	    #`t\
_coffee -other_pg clean_cache.pl -file $pdb_file.p\
db -dir $cache`;\n	  }\n      }\n    &debug_print \
(\"\\nRemote Download Finished\");\n    return $re\
turn_value;\n  }\nreturn \"\";\n}\n\nsub check_pdb\
_file4compression \n{\n    my $file=@_[0];\n    my\
 $tmp;\n    my $r;\n    \n    $tmp=&vtmpnam();\n  \
  if (-e $tmp){unlink $tmp;}\n    \n    $file=~s/\\
\/\\//\\//g;\n    if    (-B $file && ($file=~/\\.Z\
/)) {`cp $file $tmp.Z`;`rm $tmp`;`gunzip $tmp.Z $S\
ILENT`;$r=$tmp;}\n    elsif (-B $file && ($file=~/\
\\.gz/)){`cp $file $tmp.gz`;`gunzip $tmp.gz $SILEN\
T`;return $r=$tmp;}\n    elsif (-B $file ){`cp $fi\
le $tmp.gz`;`gunzip $tmp.gz $SILENT`;$r=$tmp;}\n  \
  elsif ( -e $file ) {$r= $file;}\n    elsif ( -e \
\"$file.gz\" ){ `cp $file.gz $tmp.gz`;`gunzip     \
$tmp.gz $SILENT`;$r=$tmp;}    \n    elsif ( -e \"$\
file.Z\") {`cp $file.Z  $tmp.Z`; `gunzip $tmp.Z $S\
ILENT`;$r=$tmp;}\n    else  {$r= $file;}\n\n    if\
 ( -e \"$tmp.Z\"){unlink \"$tmp.Z\";}\n    if ( -e\
 \"$tmp.gz\"){unlink \"$tmp.gz\";}\n    \n    retu\
rn $r;\n    \n}\n\n\n\n\n\n    \n\n\n\n\n\n\n\nsub\
 vfopen \n{\n    my $file=@_[0];\n    my $mode=@_[\
1];\n    my $tmp;\n    my $F = new FileHandle;\n  \
  \n    \n    $tmp=$file;\n	\n    \n    if ( $mode\
 eq \"r\" && !-e $file){ myexit(flush_error (\"Can\
not open file $file\"));}\n    elsif ($mode eq \"w\
\"){$tmp=\">$file\";}\n    elsif ($mode eq \"a\"){\
$tmp=\">>$file\";}\n    \n    \n    open ($F,$tmp)\
;\n    return $F;\n}\nsub debug_print\n{\n    my $\
message =@_[0];\n    if ($debug){print STDERR \"NO\
_REMOTE_PDB_DIR: $no_remote_pdb_dir - $message [DE\
BUG:extract_from_pdb]\";}\n    return;\n}\nsub is_\
aa \n{\n    my ($aa, $chain) =@_;\n\n    my $one;\\
n    my $trhee;\n    \n    if ( $onelett{$molecule\
_type{$chain}}->{$aa} eq 'X' || !$onelett{$molecul\
e_type{$chain}}->{$aa} ){return '';}\n    else\n  \
    {\n	$one=$onelett{$molecule_type{$chain}}->{$a\
a};\n\n	$three=$threelett{$molecule_type{$chain}}-\
>{$one};\n	\n\n	return $three;\n      }\n  }\n\n\n\
\n\n\nsub url2file\n{\n    my ($address, $out, $wg\
et_arg, $curl_arg)=(@_);\n    my ($pg, $flag, $r, \
$arg, $count);\n    \n    if (!$CONFIGURATION){&ch\
eck_configuration (\"wget\", \"INTERNET\", \"gzip\\
");$CONFIGURATION=1;}\n    \n    if (&pg_is_instal\
led (\"wget\"))   {$pg=\"wget\"; $flag=\"-O\";$arg\
=$wget_arg;}\n    elsif (&pg_is_installed (\"curl\\
")){$pg=\"curl\"; $flag=\"-o\";$arg=$curl_arg;}\n \
   return safe_system (\"$pg $flag$out $address >/\
dev/null 2>/dev/null\");\n\n}\n\n\n\n\nsub pdbfile\
2chaintype\n  {\n    my $file=@_[0];\n    my %ct;\\
n    my $F;\n    \n    $F=vfopen ($file, \"r\");\n\
    while (<$F>)\n      {\n	my $line=$_;\n	if ($li\
ne =~/^ATOM/)\n	  {\n	    my $C=substr($line,21,1)\
;\n	    if (!$ct{$C})\n	      {	\n		my $r=substr($\
line,17,3);\n		$r=~s/\\s+//;\n		if (length ($r)==1\
){$ct{$C}=\"R\";}\n		elsif (length ($r)==2){$ct{$C\
}=\"D\";}\n		elsif (length ($r)==3){$ct{$C}=\"P\";\
}\n		else \n		  {\n		    myexit(flush_error(\"ERRO\
R: Could not read RES_ID field in file $file\"));\\
n		  }\n	      }\n	  }\n      }\n    close ($F);\n\
    return %ct;\n  }\n   \n    \n\n\n\nsub fill_th\
reelett_RNA\n{\n\n	my %threelett=(\n	'A', '  A',\n\
	'T', '  T',\n	'U', '  U',\n	'C', '  C',\n	'G', ' \
 G',\n	'I', '  I', #Inosine\n	);\n	\n	return %thre\
elett;\n\n}\n\n\nsub fill_onelett_RNA\n{\n	my   %o\
nelett=(\n	'  A' => 'A',\n	'  T' => 'T',\n	'  U' =\
> 'U',\n	'  C' => 'C',\n	'  G' => 'G',\n	'CSL' => \
'X',\n	'UMS' => 'X',\n	'  I' => 'I',\n	'A' => 'A',\
\n	'T' => 'T',\n	'U' => 'U',\n	'C' => 'C',\n	'G' =\
> 'G',\n	'I' => 'I',\n	);\n\n	return %onelett;\n\n\
}\n\n\nsub fill_onelett_DNA\n{\n	my   %onelett=(\n\
	' DA', 'A',\n	' DT', 'T',\n	' DC', 'C',\n	' DG', \
'G',\n	'DA', 'A',\n	'DT', 'T',\n	'DC', 'C',\n	'DG'\
, 'G',\n	);\n\n	return %onelett;\n\n}\n\nsub fill_\
threelett_DNA\n{\n\n	my %threelett=(\n	'A', ' DA',\
\n	'T', ' DT',\n	'C', ' DC',\n	'G', ' DG',\n	);\n\\
n	return %threelett;\n\n}\n\n\n\n\nsub fill_threel\
ett_prot\n{  \n  my %threelett;\n\n  %threelett=(\\
n'A', 'ALA',\n'C', 'CYS',\n'D', 'ASP',\n'E', 'GLU'\
,\n'F', 'PHE',\n'G', 'GLY',\n'H', 'HIS',\n'I', 'IL\
E',\n'K', 'LYS',\n'L', 'LEU',\n'N', 'ASN',\n'M', '\
MET',\n'P', 'PRO',\n'Q', 'GLN',\n'R', 'ARG',\n'S',\
 'SER',\n'T', 'THR',\n'V', 'VAL',\n'W', 'TRP',\n'Y\
', 'TYR',\n);\n\nreturn %threelett;\n\n\n}\n\nsub \
fill_onelett_prot\n{\n    my %onelett;\n    \n    \
%onelett=(\n\n'10A', 'X',\n'11O', 'X',\n'12A', 'X'\
,\n'13P', 'X',\n'13R', 'X',\n'13S', 'X',\n'14W', '\
X',\n'15P', 'X',\n'16A', 'X',\n'16G', 'X',\n'1AN',\
 'X',\n'1AP', 'X',\n'1AR', 'X',\n'1BH', 'X',\n'1BO\
', 'X',\n'1C5', 'X',\n'1CU', 'X',\n'1DA', 'X',\n'1\
GL', 'X',\n'1GN', 'X',\n'1IN', 'X',\n'1LU', 'L',\n\
'1MA', 'X',\n'1MC', 'X',\n'1MG', 'X',\n'1MZ', 'X',\
\n'1NA', 'X',\n'1NB', 'X',\n'1NI', 'X',\n'1PA', 'A\
',\n'1PC', 'X',\n'1PE', 'X',\n'1PG', 'X',\n'1PI', \
'A',\n'1PM', 'X',\n'1PN', 'X',\n'1PU', 'X',\n'1PY'\
, 'X',\n'1UN', 'X',\n'24T', 'X',\n'25T', 'X',\n'26\
P', 'X',\n'2AB', 'X',\n'2AM', 'X',\n'2AN', 'X',\n'\
2AP', 'X',\n'2AR', 'X',\n'2AS', 'D',\n'2BL', 'X',\\
n'2BM', 'X',\n'2CP', 'X',\n'2DA', 'X',\n'2DG', 'X'\
,\n'2DP', 'X',\n'2DT', 'X',\n'2EP', 'X',\n'2EZ', '\
X',\n'2FG', 'X',\n'2FL', 'X',\n'2FP', 'X',\n'2FU',\
 'X',\n'2GL', 'X',\n'2GP', 'X',\n'2HP', 'X',\n'2IB\
', 'X',\n'2IP', 'X',\n'2LU', 'L',\n'2MA', 'X',\n'2\
MD', 'X',\n'2ME', 'X',\n'2MG', 'X',\n'2ML', 'L',\n\
'2MO', 'X',\n'2MR', 'R',\n'2MU', 'X',\n'2MZ', 'X',\
\n'2NO', 'X',\n'2NP', 'X',\n'2OG', 'X',\n'2PA', 'X\
',\n'2PC', 'X',\n'2PE', 'X',\n'2PG', 'X',\n'2PH', \
'X',\n'2PI', 'X',\n'2PL', 'X',\n'2PP', 'X',\n'2PU'\
, 'X',\n'2SI', 'X',\n'2TB', 'X',\n'34C', 'X',\n'35\
G', 'X',\n'3AA', 'X',\n'3AD', 'X',\n'3AH', 'H',\n'\
3AN', 'X',\n'3AP', 'X',\n'3AT', 'X',\n'3BT', 'X',\\
n'3CH', 'X',\n'3CN', 'X',\n'3CO', 'X',\n'3CP', 'X'\
,\n'3DR', 'X',\n'3EP', 'X',\n'3FM', 'X',\n'3GA', '\
X',\n'3GP', 'X',\n'3HB', 'X',\n'3HC', 'X',\n'3HP',\
 'X',\n'3IB', 'X',\n'3ID', 'X',\n'3IN', 'X',\n'3MA\
', 'X',\n'3MB', 'X',\n'3MC', 'X',\n'3MD', 'D',\n'3\
MF', 'X',\n'3MP', 'X',\n'3MT', 'X',\n'3OL', 'X',\n\
'3PA', 'X',\n'3PG', 'X',\n'3PO', 'X',\n'3PP', 'X',\
\n'3PY', 'X',\n'49A', 'X',\n'4AB', 'X',\n'4AM', 'X\
',\n'4AN', 'X',\n'4AP', 'X',\n'4BA', 'X',\n'4BT', \
'X',\n'4CA', 'X',\n'4CO', 'X',\n'4HP', 'X',\n'4IP'\
, 'X',\n'4MO', 'X',\n'4MV', 'X',\n'4MZ', 'X',\n'4N\
C', 'X',\n'4NP', 'X',\n'4OX', 'X',\n'4PB', 'X',\n'\
4PN', 'X',\n'4PP', 'X',\n'4SC', 'X',\n'4SU', 'X',\\
n'4TB', 'X',\n'55C', 'X',\n'5AD', 'X',\n'5AN', 'X'\
,\n'5AT', 'X',\n'5CM', 'X',\n'5GP', 'X',\n'5HP', '\
E',\n'5HT', 'X',\n'5IT', 'X',\n'5IU', 'X',\n'5MB',\
 'X',\n'5MC', 'X',\n'5MD', 'X',\n'5MP', 'X',\n'5MU\
', 'X',\n'5NC', 'X',\n'5OB', 'X',\n'5PA', 'X',\n'5\
PV', 'X',\n'6AB', 'X',\n'6CT', 'X',\n'6HA', 'X',\n\
'6HC', 'X',\n'6HG', 'X',\n'6HT', 'X',\n'6IN', 'X',\
\n'6MO', 'X',\n'6MP', 'X',\n'6PG', 'X',\n'6WO', 'X\
',\n'70U', 'X',\n'7DG', 'X',\n'7HP', 'X',\n'7I2', \
'X',\n'7MG', 'X',\n'7MQ', 'X',\n'7NI', 'X',\n'87Y'\
, 'X',\n'8AD', 'X',\n'8BR', 'X',\n'8IG', 'X',\n'8I\
N', 'X',\n'8OG', 'X',\n'95A', 'X',\n'9AD', 'X',\n'\
9AM', 'X',\n'9AP', 'X',\n'9DG', 'X',\n'9DI', 'X',\\
n'9HX', 'X',\n'9OH', 'X',\n'9TA', 'X',\n'A12', 'X'\
,\n'A15', 'X',\n'A23', 'X',\n'A24', 'X',\n'A26', '\
X',\n'A2G', 'X',\n'A2P', 'X',\n'A32', 'X',\n'A3P',\
 'X',\n'A4P', 'X',\n'A5P', 'X',\n'A70', 'X',\n'A76\
', 'X',\n'A77', 'X',\n'A78', 'X',\n'A79', 'X',\n'A\
80', 'X',\n'A85', 'X',\n'A88', 'X',\n'A9A', 'X',\n\
'AA3', 'X',\n'AA4', 'X',\n'AA6', 'X',\n'AAA', 'X',\
\n'AAB', 'X',\n'AAC', 'X',\n'AAE', 'X',\n'AAG', 'R\
',\n'AAH', 'X',\n'AAM', 'X',\n'AAN', 'X',\n'AAP', \
'X',\n'AAR', 'R',\n'AAS', 'X',\n'AAT', 'X',\n'ABA'\
, 'X',\n'ABC', 'X',\n'ABD', 'X',\n'ABE', 'X',\n'AB\
H', 'X',\n'ABI', 'X',\n'ABK', 'X',\n'ABM', 'X',\n'\
ABN', 'X',\n'ABP', 'X',\n'ABR', 'X',\n'ABS', 'X',\\
n'ABU', 'X',\n'AC1', 'X',\n'AC2', 'X',\n'ACA', 'X'\
,\n'ACB', 'D',\n'ACC', 'C',\n'ACD', 'X',\n'ACE', '\
X',\n'ACH', 'X',\n'ACI', 'X',\n'ACL', 'R',\n'ACM',\
 'X',\n'ACN', 'X',\n'ACO', 'X',\n'ACP', 'X',\n'ACQ\
', 'X',\n'ACR', 'X',\n'ACS', 'X',\n'ACT', 'X',\n'A\
CV', 'V',\n'ACX', 'X',\n'ACY', 'X',\n'AD2', 'X',\n\
'AD3', 'X',\n'ADC', 'X',\n'ADD', 'X',\n'ADE', 'X',\
\n'ADH', 'X',\n'ADI', 'X',\n'ADM', 'X',\n'ADN', 'X\
',\n'ADP', 'X',\n'ADQ', 'X',\n'ADR', 'X',\n'ADS', \
'X',\n'ADT', 'X',\n'ADU', 'X',\n'ADW', 'X',\n'ADX'\
, 'X',\n'AE2', 'X',\n'AEA', 'X',\n'AEB', 'X',\n'AE\
I', 'D',\n'AEN', 'X',\n'AET', 'T',\n'AF1', 'X',\n'\
AF3', 'X',\n'AFA', 'D',\n'AFP', 'X',\n'AG7', 'X',\\
n'AGB', 'X',\n'AGF', 'X',\n'AGL', 'X',\n'AGM', 'R'\
,\n'AGN', 'X',\n'AGP', 'X',\n'AGS', 'X',\n'AGU', '\
X',\n'AH0', 'X',\n'AH1', 'X',\n'AHA', 'X',\n'AHB',\
 'D',\n'AHC', 'X',\n'AHF', 'X',\n'AHG', 'X',\n'AHH\
', 'X',\n'AHM', 'X',\n'AHO', 'X',\n'AHP', 'X',\n'A\
HS', 'X',\n'AHT', 'Y',\n'AHU', 'X',\n'AHX', 'X',\n\
'AI1', 'X',\n'AI2', 'X',\n'AIB', 'X',\n'AIC', 'X',\
\n'AIM', 'X',\n'AIP', 'X',\n'AIQ', 'X',\n'AIR', 'X\
',\n'AJ3', 'X',\n'AKB', 'X',\n'AKG', 'X',\n'AKR', \
'X',\n'AL1', 'X',\n'AL2', 'X',\n'AL3', 'X',\n'AL4'\
, 'X',\n'AL5', 'X',\n'AL6', 'X',\n'AL7', 'X',\n'AL\
8', 'X',\n'AL9', 'X',\n'ALA', 'A',\n'ALB', 'X',\n'\
ALC', 'X',\n'ALD', 'L',\n'ALE', 'X',\n'ALF', 'X',\\
n'ALG', 'X',\n'ALL', 'X',\n'ALM', 'A',\n'ALN', 'A'\
,\n'ALO', 'T',\n'ALP', 'X',\n'ALQ', 'X',\n'ALR', '\
X',\n'ALS', 'X',\n'ALT', 'A',\n'ALY', 'K',\n'ALZ',\
 'X',\n'AMA', 'X',\n'AMB', 'X',\n'AMC', 'X',\n'AMD\
', 'X',\n'AMG', 'X',\n'AMH', 'X',\n'AMI', 'X',\n'A\
ML', 'X',\n'AMN', 'X',\n'AMO', 'X',\n'AMP', 'X',\n\
'AMQ', 'X',\n'AMR', 'X',\n'AMS', 'X',\n'AMT', 'X',\
\n'AMU', 'X',\n'AMW', 'X',\n'AMX', 'X',\n'AMY', 'X\
',\n'ANA', 'X',\n'ANB', 'X',\n'ANC', 'X',\n'AND', \
'X',\n'ANE', 'X',\n'ANI', 'X',\n'ANL', 'X',\n'ANO'\
, 'X',\n'ANP', 'X',\n'ANS', 'X',\n'ANT', 'X',\n'AO\
E', 'X',\n'AOP', 'X',\n'AP1', 'X',\n'AP2', 'X',\n'\
AP3', 'X',\n'AP4', 'X',\n'AP5', 'X',\n'AP6', 'X',\\
n'APA', 'X',\n'APB', 'X',\n'APC', 'X',\n'APE', 'F'\
,\n'APF', 'X',\n'APG', 'X',\n'APH', 'A',\n'API', '\
X',\n'APL', 'X',\n'APM', 'X',\n'APN', 'G',\n'APP',\
 'X',\n'APQ', 'X',\n'APR', 'X',\n'APS', 'X',\n'APT\
', 'X',\n'APU', 'X',\n'APX', 'X',\n'APY', 'X',\n'A\
PZ', 'X',\n'AQS', 'X',\n'AR1', 'X',\n'AR2', 'X',\n\
'ARA', 'X',\n'ARB', 'X',\n'ARC', 'X',\n'ARD', 'X',\
\n'ARG', 'R',\n'ARH', 'X',\n'ARI', 'X',\n'ARM', 'R\
',\n'ARN', 'X',\n'ARO', 'R',\n'ARP', 'X',\n'ARQ', \
'X',\n'ARS', 'X',\n'AS1', 'R',\n'AS2', 'X',\n'ASA'\
, 'D',\n'ASB', 'D',\n'ASC', 'X',\n'ASD', 'X',\n'AS\
E', 'X',\n'ASF', 'X',\n'ASI', 'X',\n'ASK', 'D',\n'\
ASL', 'X',\n'ASM', 'N',\n'ASO', 'X',\n'ASP', 'D',\\
n'ASQ', 'X',\n'ASU', 'X',\n'ATA', 'X',\n'ATC', 'X'\
,\n'ATD', 'X',\n'ATF', 'X',\n'ATG', 'X',\n'ATH', '\
X',\n'ATM', 'X',\n'ATO', 'X',\n'ATP', 'X',\n'ATQ',\
 'X',\n'ATR', 'X',\n'ATT', 'X',\n'ATY', 'X',\n'ATZ\
', 'X',\n'AUC', 'X',\n'AUR', 'X',\n'AVG', 'X',\n'A\
XP', 'X',\n'AYA', 'A',\n'AZ2', 'X',\n'AZA', 'X',\n\
'AZC', 'X',\n'AZD', 'X',\n'AZE', 'X',\n'AZI', 'X',\
\n'AZL', 'X',\n'AZM', 'X',\n'AZR', 'X',\n'AZT', 'X\
',\n'B12', 'X',\n'B1F', 'F',\n'B2A', 'A',\n'B2F', \
'F',\n'B2I', 'I',\n'B2V', 'V',\n'B3I', 'X',\n'B3P'\
, 'X',\n'B7G', 'X',\n'B96', 'X',\n'B9A', 'X',\n'BA\
1', 'X',\n'BAA', 'X',\n'BAB', 'X',\n'BAC', 'X',\n'\
BAF', 'X',\n'BAH', 'X',\n'BAI', 'X',\n'BAK', 'X',\\
n'BAL', 'A',\n'BAM', 'X',\n'BAO', 'X',\n'BAP', 'X'\
,\n'BAR', 'X',\n'BAS', 'X',\n'BAT', 'F',\n'BAY', '\
X',\n'BAZ', 'X',\n'BB1', 'X',\n'BB2', 'X',\n'BBA',\
 'X',\n'BBH', 'X',\n'BBS', 'X',\n'BBT', 'X',\n'BBZ\
', 'X',\n'BCA', 'X',\n'BCB', 'X',\n'BCC', 'X',\n'B\
CD', 'X',\n'BCL', 'X',\n'BCN', 'X',\n'BCR', 'X',\n\
'BCS', 'C',\n'BCT', 'X',\n'BCY', 'X',\n'BCZ', 'X',\
\n'BDA', 'X',\n'BDG', 'X',\n'BDK', 'X',\n'BDM', 'X\
',\n'BDN', 'X',\n'BDS', 'X',\n'BE1', 'X',\n'BE2', \
'X',\n'BEA', 'X',\n'BEF', 'X',\n'BEN', 'X',\n'BEO'\
, 'X',\n'BEP', 'X',\n'BER', 'X',\n'BES', 'X',\n'BE\
T', 'X',\n'BEZ', 'X',\n'BF2', 'X',\n'BFA', 'X',\n'\
BFD', 'X',\n'BFP', 'X',\n'BFS', 'X',\n'BFU', 'X',\\
n'BG6', 'X',\n'BGF', 'X',\n'BGG', 'X',\n'BGL', 'X'\
,\n'BGN', 'X',\n'BGP', 'X',\n'BGX', 'X',\n'BH4', '\
X',\n'BHA', 'X',\n'BHC', 'X',\n'BHD', 'D',\n'BHO',\
 'X',\n'BHS', 'X',\n'BIC', 'X',\n'BIN', 'X',\n'BIO\
', 'X',\n'BIP', 'X',\n'BIS', 'X',\n'BIZ', 'X',\n'B\
JH', 'X',\n'BJI', 'X',\n'BJP', 'X',\n'BLA', 'X',\n\
'BLB', 'X',\n'BLE', 'L',\n'BLG', 'P',\n'BLI', 'X',\
\n'BLM', 'X',\n'BLV', 'X',\n'BLY', 'K',\n'BM1', 'X\
',\n'BM2', 'X',\n'BM5', 'X',\n'BM9', 'X',\n'BMA', \
'X',\n'BMD', 'X',\n'BME', 'X',\n'BMP', 'X',\n'BMQ'\
, 'X',\n'BMS', 'X',\n'BMT', 'T',\n'BMU', 'X',\n'BM\
Y', 'X',\n'BMZ', 'X',\n'BNA', 'X',\n'BNG', 'X',\n'\
BNI', 'X',\n'BNN', 'F',\n'BNO', 'L',\n'BNS', 'X',\\
n'BNZ', 'X',\n'BO3', 'X',\n'BO4', 'X',\n'BOC', 'X'\
,\n'BOG', 'X',\n'BOM', 'X',\n'BOT', 'X',\n'BOX', '\
X',\n'BOZ', 'X',\n'BPA', 'X',\n'BPB', 'X',\n'BPD',\
 'X',\n'BPG', 'X',\n'BPH', 'X',\n'BPI', 'X',\n'BPJ\
', 'X',\n'BPM', 'X',\n'BPN', 'X',\n'BPO', 'X',\n'B\
PP', 'X',\n'BPT', 'X',\n'BPY', 'X',\n'BRB', 'X',\n\
'BRC', 'X',\n'BRE', 'X',\n'BRI', 'X',\n'BRL', 'X',\
\n'BRM', 'X',\n'BRN', 'X',\n'BRO', 'X',\n'BRS', 'X\
',\n'BRU', 'X',\n'BRZ', 'X',\n'BSB', 'X',\n'BSI', \
'X',\n'BSP', 'X',\n'BT1', 'X',\n'BT2', 'X',\n'BT3'\
, 'X',\n'BTA', 'L',\n'BTB', 'X',\n'BTC', 'C',\n'BT\
D', 'X',\n'BTN', 'X',\n'BTP', 'X',\n'BTR', 'W',\n'\
BU1', 'X',\n'BUA', 'X',\n'BUB', 'X',\n'BUC', 'X',\\
n'BUG', 'X',\n'BUL', 'X',\n'BUM', 'X',\n'BUQ', 'X'\
,\n'BUT', 'X',\n'BVD', 'X',\n'BX3', 'X',\n'BYS', '\
X',\n'BZ1', 'X',\n'BZA', 'X',\n'BZB', 'X',\n'BZC',\
 'X',\n'BZD', 'X',\n'BZF', 'X',\n'BZI', 'X',\n'BZM\
', 'X',\n'BZO', 'X',\n'BZP', 'X',\n'BZQ', 'X',\n'B\
ZS', 'X',\n'BZT', 'X',\n'C02', 'X',\n'C11', 'X',\n\
'C1O', 'X',\n'C20', 'X',\n'C24', 'X',\n'C2F', 'X',\
\n'C2O', 'X',\n'C2P', 'X',\n'C3M', 'X',\n'C3P', 'X\
',\n'C3X', 'X',\n'C48', 'X',\n'C4M', 'X',\n'C4X', \
'X',\n'C5C', 'X',\n'C5M', 'X',\n'C5P', 'X',\n'C5X'\
, 'X',\n'C60', 'X',\n'C6C', 'X',\n'C6M', 'X',\n'C7\
8', 'X',\n'C8E', 'X',\n'CA3', 'X',\n'CA5', 'X',\n'\
CAA', 'X',\n'CAB', 'X',\n'CAC', 'X',\n'CAD', 'X',\\
n'CAF', 'C',\n'CAG', 'X',\n'CAH', 'X',\n'CAL', 'X'\
,\n'CAM', 'X',\n'CAN', 'X',\n'CAO', 'X',\n'CAP', '\
X',\n'CAQ', 'X',\n'CAR', 'X',\n'CAS', 'C',\n'CAT',\
 'X',\n'CAV', 'X',\n'CAY', 'C',\n'CAZ', 'X',\n'CB3\
', 'X',\n'CB4', 'X',\n'CBA', 'X',\n'CBD', 'X',\n'C\
BG', 'X',\n'CBI', 'X',\n'CBL', 'X',\n'CBM', 'X',\n\
'CBN', 'X',\n'CBO', 'X',\n'CBP', 'X',\n'CBS', 'X',\
\n'CBX', 'X',\n'CBZ', 'X',\n'CC0', 'X',\n'CC1', 'X\
',\n'CCC', 'X',\n'CCH', 'X',\n'CCI', 'X',\n'CCM', \
'X',\n'CCN', 'X',\n'CCO', 'X',\n'CCP', 'X',\n'CCR'\
, 'X',\n'CCS', 'C',\n'CCV', 'X',\n'CCY', 'X',\n'CD\
1', 'X',\n'CDC', 'X',\n'CDE', 'X',\n'CDF', 'X',\n'\
CDI', 'X',\n'CDL', 'X',\n'CDM', 'X',\n'CDP', 'X',\\
n'CDR', 'X',\n'CDU', 'X',\n'CE1', 'X',\n'CEA', 'C'\
,\n'CEB', 'X',\n'CEC', 'X',\n'CED', 'X',\n'CEF', '\
X',\n'CEH', 'X',\n'CEM', 'X',\n'CEO', 'X',\n'CEP',\
 'X',\n'CEQ', 'X',\n'CER', 'X',\n'CES', 'G',\n'CET\
', 'X',\n'CFC', 'X',\n'CFF', 'X',\n'CFM', 'X',\n'C\
FO', 'X',\n'CFP', 'X',\n'CFS', 'X',\n'CFX', 'X',\n\
'CGN', 'X',\n'CGP', 'X',\n'CGS', 'X',\n'CGU', 'E',\
\n'CH2', 'X',\n'CH3', 'X',\n'CHA', 'X',\n'CHB', 'X\
',\n'CHD', 'X',\n'CHF', 'X',\n'CHG', 'G',\n'CHI', \
'X',\n'CHN', 'X',\n'CHO', 'X',\n'CHP', 'G',\n'CHR'\
, 'X',\n'CHS', 'F',\n'CHT', 'X',\n'CHX', 'X',\n'CI\
C', 'X',\n'CIN', 'X',\n'CIP', 'X',\n'CIR', 'X',\n'\
CIT', 'X',\n'CIU', 'X',\n'CKI', 'X',\n'CL1', 'X',\\
n'CL2', 'X',\n'CLA', 'X',\n'CLB', 'A',\n'CLC', 'S'\
,\n'CLD', 'A',\n'CLE', 'L',\n'CLF', 'X',\n'CLK', '\
S',\n'CLL', 'X',\n'CLM', 'X',\n'CLN', 'X',\n'CLO',\
 'X',\n'CLP', 'X',\n'CLQ', 'X',\n'CLR', 'X',\n'CLS\
', 'X',\n'CLT', 'X',\n'CLX', 'X',\n'CLY', 'X',\n'C\
MA', 'R',\n'CMC', 'X',\n'CMD', 'X',\n'CME', 'C',\n\
'CMG', 'X',\n'CMK', 'X',\n'CMN', 'X',\n'CMO', 'X',\
\n'CMP', 'X',\n'CMR', 'X',\n'CMS', 'X',\n'CMT', 'C\
',\n'CMX', 'X',\n'CNA', 'X',\n'CNC', 'X',\n'CND', \
'X',\n'CNH', 'X',\n'CNM', 'X',\n'CNN', 'X',\n'CNO'\
, 'X',\n'CNP', 'X',\n'CO2', 'X',\n'CO3', 'X',\n'CO\
5', 'X',\n'CO8', 'X',\n'COA', 'X',\n'COB', 'X',\n'\
COC', 'X',\n'COD', 'X',\n'COE', 'X',\n'COF', 'X',\\
n'COH', 'X',\n'COI', 'X',\n'COJ', 'X',\n'COL', 'X'\
,\n'COM', 'X',\n'CON', 'X',\n'COP', 'X',\n'COR', '\
X',\n'COS', 'X',\n'COT', 'X',\n'COY', 'X',\n'CP1',\
 'G',\n'CP2', 'X',\n'CP4', 'X',\n'CPA', 'X',\n'CPB\
', 'X',\n'CPC', 'X',\n'CPD', 'X',\n'CPG', 'X',\n'C\
PH', 'X',\n'CPI', 'X',\n'CPM', 'X',\n'CPN', 'G',\n\
'CPO', 'X',\n'CPP', 'X',\n'CPQ', 'X',\n'CPR', 'X',\
\n'CPS', 'X',\n'CPT', 'X',\n'CPU', 'X',\n'CPV', 'X\
',\n'CPY', 'X',\n'CR1', 'X',\n'CR6', 'X',\n'CRA', \
'X',\n'CRB', 'X',\n'CRC', 'X',\n'CRG', 'X',\n'CRH'\
, 'X',\n'CRO', 'T',\n'CRP', 'X',\n'CRQ', 'X',\n'CR\
S', 'X',\n'CRT', 'X',\n'CRY', 'X',\n'CSA', 'C',\n'\
CSB', 'X',\n'CSD', 'C',\n'CSE', 'C',\n'CSH', 'X',\\
n'CSI', 'X',\n'CSN', 'X',\n'CSO', 'C',\n'CSP', 'C'\
,\n'CSR', 'C',\n'CSS', 'C',\n'CST', 'X',\n'CSW', '\
C',\n'CSX', 'C',\n'CSY', 'X',\n'CSZ', 'C',\n'CT3',\
 'X',\n'CTA', 'X',\n'CTB', 'X',\n'CTC', 'X',\n'CTD\
', 'X',\n'CTH', 'T',\n'CTO', 'X',\n'CTP', 'X',\n'C\
TR', 'X',\n'CTS', 'X',\n'CTT', 'X',\n'CTY', 'X',\n\
'CTZ', 'X',\n'CU1', 'X',\n'CUA', 'X',\n'CUC', 'X',\
\n'CUL', 'X',\n'CUO', 'X',\n'CUZ', 'X',\n'CVI', 'X\
',\n'CXF', 'X',\n'CXL', 'X',\n'CXM', 'M',\n'CXN', \
'X',\n'CXP', 'X',\n'CXS', 'X',\n'CY1', 'C',\n'CY3'\
, 'X',\n'CYB', 'X',\n'CYC', 'X',\n'CYF', 'C',\n'CY\
G', 'C',\n'CYH', 'X',\n'CYL', 'X',\n'CYM', 'C',\n'\
CYN', 'X',\n'CYO', 'X',\n'CYP', 'X',\n'CYQ', 'C',\\
n'CYS', 'C',\n'CYU', 'X',\n'CYY', 'X',\n'CYZ', 'X'\
,\n'CZH', 'X',\n'CZZ', 'C',\n'D12', 'X',\n'D13', '\
X',\n'D16', 'X',\n'D18', 'X',\n'D19', 'X',\n'D1P',\
 'X',\n'D24', 'X',\n'D34', 'X',\n'D35', 'X',\n'D4D\
', 'X',\n'D4T', 'X',\n'D6G', 'X',\n'DA2', 'R',\n'D\
A3', 'X',\n'DA6', 'X',\n'DA7', 'X',\n'DAA', 'X',\n\
'DAB', 'X',\n'DAC', 'X',\n'DAD', 'X',\n'DAE', 'X',\
\n'DAF', 'X',\n'DAG', 'X',\n'DAH', 'A',\n'DAJ', 'X\
',\n'DAK', 'X',\n'DAL', 'A',\n'DAM', 'A',\n'DAN', \
'X',\n'DAO', 'X',\n'DAP', 'X',\n'DAQ', 'X',\n'DAR'\
, 'R',\n'DAS', 'D',\n'DAT', 'X',\n'DAU', 'X',\n'DA\
V', 'X',\n'DBA', 'X',\n'DBD', 'X',\n'DBF', 'X',\n'\
DBG', 'X',\n'DBI', 'X',\n'DBV', 'X',\n'DBY', 'Y',\\
n'DCA', 'X',\n'DCB', 'X',\n'DCE', 'X',\n'DCF', 'X'\
,\n'DCG', 'X',\n'DCH', 'X',\n'DCI', 'I',\n'DCL', '\
X',\n'DCM', 'X',\n'DCP', 'X',\n'DCS', 'X',\n'DCT',\
 'X',\n'DCY', 'C',\n'DCZ', 'X',\n'DDA', 'X',\n'DDB\
', 'X',\n'DDC', 'X',\n'DDF', 'X',\n'DDG', 'X',\n'D\
DH', 'X',\n'DDL', 'X',\n'DDM', 'X',\n'DDO', 'L',\n\
'DDP', 'X',\n'DDQ', 'X',\n'DDT', 'Y',\n'DDU', 'X',\
\n'DEA', 'X',\n'DEB', 'X',\n'DEC', 'X',\n'DEF', 'X\
',\n'DEL', 'X',\n'DEM', 'X',\n'DEN', 'X',\n'DEP', \
'X',\n'DEQ', 'X',\n'DES', 'X',\n'DET', 'X',\n'DFC'\
, 'X',\n'DFG', 'X',\n'DFI', 'X',\n'DFL', 'X',\n'DF\
O', 'X',\n'DFP', 'X',\n'DFR', 'X',\n'DFT', 'X',\n'\
DFV', 'X',\n'DFX', 'X',\n'DG2', 'X',\n'DG3', 'X',\\
n'DG6', 'X',\n'DGA', 'X',\n'DGD', 'X',\n'DGG', 'X'\
,\n'DGL', 'E',\n'DGN', 'Q',\n'DGP', 'X',\n'DGT', '\
X',\n'DGX', 'X',\n'DH2', 'X',\n'DHA', 'A',\n'DHB',\
 'X',\n'DHC', 'X',\n'DHD', 'X',\n'DHE', 'X',\n'DHF\
', 'X',\n'DHG', 'X',\n'DHI', 'H',\n'DHL', 'X',\n'D\
HM', 'X',\n'DHN', 'V',\n'DHP', 'X',\n'DHQ', 'X',\n\
'DHR', 'X',\n'DHS', 'X',\n'DHT', 'X',\n'DHU', 'X',\
\n'DHY', 'X',\n'DHZ', 'X',\n'DI2', 'X',\n'DI3', 'G\
',\n'DI4', 'X',\n'DI5', 'X',\n'DIA', 'X',\n'DIC', \
'X',\n'DIF', 'X',\n'DIG', 'X',\n'DII', 'X',\n'DIL'\
, 'I',\n'DIM', 'X',\n'DIO', 'X',\n'DIP', 'X',\n'DI\
Q', 'X',\n'DIS', 'X',\n'DIT', 'X',\n'DIV', 'V',\n'\
DIX', 'X',\n'DIY', 'X',\n'DKA', 'X',\n'DLA', 'X',\\
n'DLE', 'L',\n'DLF', 'X',\n'DLS', 'K',\n'DLY', 'K'\
,\n'DM1', 'X',\n'DM2', 'X',\n'DM3', 'X',\n'DM4', '\
X',\n'DM5', 'X',\n'DM6', 'X',\n'DM7', 'X',\n'DM8',\
 'X',\n'DM9', 'X',\n'DMA', 'X',\n'DMB', 'X',\n'DMC\
', 'X',\n'DMD', 'X',\n'DME', 'X',\n'DMF', 'X',\n'D\
MG', 'G',\n'DMH', 'N',\n'DMI', 'X',\n'DMJ', 'X',\n\
'DML', 'X',\n'DMM', 'X',\n'DMN', 'X',\n'DMO', 'X',\
\n'DMP', 'X',\n'DMQ', 'X',\n'DMR', 'X',\n'DMS', 'X\
',\n'DMT', 'X',\n'DMV', 'X',\n'DMY', 'X',\n'DNC', \
'X',\n'DND', 'X',\n'DNH', 'X',\n'DNJ', 'X',\n'DNN'\
, 'X',\n'DNP', 'X',\n'DNQ', 'X',\n'DNR', 'X',\n'DO\
2', 'X',\n'DO3', 'X',\n'DOA', 'X',\n'DOB', 'X',\n'\
DOC', 'X',\n'DOH', 'D',\n'DOM', 'X',\n'DOS', 'X',\\
n'DOX', 'X',\n'DP5', 'X',\n'DP7', 'X',\n'DPA', 'X'\
,\n'DPC', 'X',\n'DPD', 'X',\n'DPE', 'X',\n'DPG', '\
X',\n'DPH', 'F',\n'DPM', 'X',\n'DPN', 'F',\n'DPO',\
 'X',\n'DPP', 'X',\n'DPR', 'P',\n'DPS', 'X',\n'DPT\
', 'X',\n'DPX', 'X',\n'DPY', 'X',\n'DPZ', 'X',\n'D\
QH', 'X',\n'DQN', 'X',\n'DR1', 'X',\n'DRB', 'X',\n\
'DRC', 'X',\n'DRI', 'X',\n'DRP', 'X',\n'DRT', 'X',\
\n'DRU', 'X',\n'DSA', 'X',\n'DSB', 'X',\n'DSC', 'X\
',\n'DSD', 'X',\n'DSE', 'S',\n'DSI', 'X',\n'DSN', \
'S',\n'DSP', 'D',\n'DSR', 'X',\n'DSS', 'X',\n'DSX'\
, 'X',\n'DSY', 'X',\n'DTB', 'X',\n'DTD', 'X',\n'DT\
H', 'T',\n'DTN', 'X',\n'DTO', 'X',\n'DTP', 'X',\n'\
DTQ', 'X',\n'DTR', 'W',\n'DTT', 'X',\n'DTY', 'Y',\\
n'DUD', 'X',\n'DUO', 'X',\n'DUR', 'X',\n'DUT', 'X'\
,\n'DVA', 'V',\n'DVR', 'X',\n'DX9', 'X',\n'DXA', '\
X',\n'DXB', 'X',\n'DXC', 'X',\n'DXG', 'X',\n'DXX',\
 'X',\n'DZF', 'X',\n'E09', 'X',\n'E20', 'X',\n'E2P\
', 'X',\n'E3G', 'X',\n'E4N', 'X',\n'E4P', 'X',\n'E\
64', 'X',\n'E6C', 'X',\n'E96', 'X',\n'E97', 'X',\n\
'EA2', 'X',\n'EAA', 'X',\n'EAP', 'X',\n'EBP', 'X',\
\n'EBW', 'X',\n'ECO', 'X',\n'EDA', 'X',\n'EDC', 'X\
',\n'EDE', 'X',\n'EDO', 'X',\n'EDR', 'X',\n'EEB', \
'X',\n'EEE', 'X',\n'EFC', 'X',\n'EFZ', 'X',\n'EG1'\
, 'X',\n'EG2', 'X',\n'EG3', 'X',\n'EGC', 'X',\n'EG\
L', 'X',\n'EHP', 'A',\n'EIC', 'X',\n'EJT', 'X',\n'\
ELA', 'X',\n'EMB', 'X',\n'EMC', 'X',\n'EMD', 'X',\\
n'EMM', 'X',\n'EMO', 'X',\n'EMP', 'X',\n'EMR', 'X'\
,\n'ENA', 'X',\n'ENC', 'X',\n'ENH', 'X',\n'ENO', '\
X',\n'ENP', 'X',\n'EOA', 'X',\n'EOH', 'X',\n'EOT',\
 'X',\n'EOX', 'X',\n'EPA', 'X',\n'EPE', 'X',\n'EPH\
', 'X',\n'EPI', 'X',\n'EPN', 'X',\n'EPO', 'X',\n'E\
PT', 'X',\n'EPU', 'X',\n'EPX', 'X',\n'EPY', 'X',\n\
'EQI', 'X',\n'EQP', 'X',\n'EQU', 'X',\n'ERG', 'X',\
\n'ERI', 'X',\n'ERY', 'X',\n'ESC', 'X',\n'ESD', 'X\
',\n'ESI', 'X',\n'ESO', 'X',\n'ESP', 'X',\n'EST', \
'X',\n'ESX', 'X',\n'ETA', 'X',\n'ETC', 'X',\n'ETD'\
, 'X',\n'ETF', 'X',\n'ETH', 'X',\n'ETI', 'X',\n'ET\
N', 'X',\n'ETO', 'X',\n'ETP', 'X',\n'ETR', 'X',\n'\
ETS', 'X',\n'ETY', 'X',\n'EU3', 'X',\n'EUG', 'X',\\
n'EYS', 'C',\n'F09', 'X',\n'F2B', 'X',\n'F3S', 'X'\
,\n'F42', 'X',\n'F43', 'X',\n'F4S', 'X',\n'F6B', '\
X',\n'F6P', 'X',\n'F89', 'X',\n'FA1', 'X',\n'FA5',\
 'F',\n'FAA', 'X',\n'FAB', 'X',\n'FAC', 'X',\n'FAD\
', 'X',\n'FAF', 'X',\n'FAG', 'X',\n'FAM', 'X',\n'F\
AR', 'X',\n'FAS', 'X',\n'FAT', 'X',\n'FBA', 'X',\n\
'FBE', 'X',\n'FBI', 'X',\n'FBP', 'X',\n'FBQ', 'X',\
\n'FBS', 'X',\n'FBT', 'X',\n'FBU', 'X',\n'FCA', 'X\
',\n'FCB', 'X',\n'FCI', 'X',\n'FCN', 'X',\n'FCO', \
'X',\n'FCR', 'X',\n'FCT', 'X',\n'FCX', 'X',\n'FCY'\
, 'C',\n'FD1', 'F',\n'FD2', 'F',\n'FD3', 'F',\n'FD\
4', 'F',\n'FDA', 'X',\n'FDC', 'X',\n'FDI', 'X',\n'\
FDP', 'X',\n'FDS', 'X',\n'FE2', 'X',\n'FEA', 'X',\\
n'FEL', 'X',\n'FEM', 'X',\n'FEN', 'X',\n'FEO', 'X'\
,\n'FEP', 'X',\n'FER', 'X',\n'FES', 'X',\n'FFB', '\
X',\n'FFC', 'X',\n'FFF', 'X',\n'FFO', 'X',\n'FGL',\
 'G',\n'FHB', 'X',\n'FHC', 'X',\n'FHP', 'X',\n'FHU\
', 'X',\n'FID', 'X',\n'FII', 'X',\n'FIP', 'X',\n'F\
K5', 'X',\n'FKA', 'X',\n'FKI', 'X',\n'FKP', 'X',\n\
'FL2', 'X',\n'FL9', 'X',\n'FLA', 'A',\n'FLC', 'X',\
\n'FLD', 'X',\n'FLE', 'L',\n'FLF', 'X',\n'FLO', 'X\
',\n'FLP', 'X',\n'FLT', 'Y',\n'FLU', 'X',\n'FLX', \
'X',\n'FM1', 'X',\n'FM2', 'X',\n'FMA', 'X',\n'FMB'\
, 'X',\n'FMC', 'X',\n'FME', 'M',\n'FMN', 'X',\n'FM\
P', 'X',\n'FMR', 'X',\n'FMS', 'X',\n'FMT', 'X',\n'\
FNE', 'X',\n'FNP', 'X',\n'FNS', 'X',\n'FOC', 'X',\\
n'FOE', 'X',\n'FOG', 'F',\n'FOH', 'X',\n'FOK', 'X'\
,\n'FOL', 'X',\n'FON', 'X',\n'FOP', 'X',\n'FOR', '\
X',\n'FOS', 'X',\n'FPA', 'X',\n'FPC', 'X',\n'FPI',\
 'X',\n'FPO', 'X',\n'FPP', 'X',\n'FPT', 'X',\n'FQP\
', 'X',\n'FRA', 'X',\n'FRD', 'F',\n'FRU', 'X',\n'F\
S3', 'X',\n'FS4', 'X',\n'FSB', 'X',\n'FSO', 'X',\n\
'FSX', 'X',\n'FTC', 'X',\n'FTP', 'X',\n'FTR', 'W',\
\n'FTT', 'X',\n'FTY', 'Y',\n'FUA', 'X',\n'FUC', 'X\
',\n'FUM', 'X',\n'FUP', 'X',\n'FVF', 'X',\n'FXP', \
'X',\n'FXV', 'X',\n'FYA', 'F',\n'G16', 'X',\n'G1P'\
, 'X',\n'G20', 'X',\n'G21', 'X',\n'G23', 'X',\n'G2\
6', 'X',\n'G28', 'X',\n'G2F', 'X',\n'G37', 'X',\n'\
G39', 'X',\n'G3H', 'X',\n'G3P', 'X',\n'G4D', 'X',\\
n'G6D', 'X',\n'G6P', 'X',\n'G6Q', 'X',\n'G7M', 'X'\
,\n'GA2', 'X',\n'GAA', 'X',\n'GAB', 'X',\n'GAC', '\
X',\n'GAI', 'X',\n'GAL', 'X',\n'GAM', 'X',\n'GAN',\
 'X',\n'GAO', 'X',\n'GAP', 'X',\n'GAR', 'G',\n'GAS\
', 'X',\n'GAT', 'X',\n'GBC', 'X',\n'GBI', 'X',\n'G\
BP', 'X',\n'GBS', 'X',\n'GBX', 'X',\n'GC4', 'X',\n\
'GCA', 'X',\n'GCD', 'X',\n'GCG', 'G',\n'GCH', 'G',\
\n'GCK', 'X',\n'GCL', 'X',\n'GCM', 'X',\n'GCN', 'X\
',\n'GCO', 'X',\n'GCP', 'X',\n'GCR', 'X',\n'GCS', \
'X',\n'GCU', 'X',\n'GD3', 'X',\n'GDB', 'X',\n'GDM'\
, 'X',\n'GDN', 'X',\n'GDP', 'X',\n'GDS', 'X',\n'GD\
U', 'X',\n'GE1', 'X',\n'GE2', 'X',\n'GE3', 'X',\n'\
GEA', 'X',\n'GEL', 'X',\n'GEM', 'X',\n'GEN', 'X',\\
n'GEP', 'X',\n'GER', 'X',\n'GFP', 'X',\n'GGB', 'X'\
,\n'GGL', 'E',\n'GGP', 'X',\n'GHP', 'G',\n'GIP', '\
X',\n'GIS', 'X',\n'GKR', 'X',\n'GL2', 'X',\n'GL3',\
 'G',\n'GL4', 'X',\n'GL5', 'X',\n'GL7', 'X',\n'GL9\
', 'X',\n'GLA', 'X',\n'GLB', 'X',\n'GLC', 'X',\n'G\
LD', 'X',\n'GLE', 'X',\n'GLF', 'X',\n'GLG', 'X',\n\
'GLH', 'Q',\n'GLI', 'X',\n'GLL', 'X',\n'GLM', 'G',\
\n'GLN', 'Q',\n'GLO', 'X',\n'GLP', 'X',\n'GLR', 'X\
',\n'GLS', 'X',\n'GLT', 'X',\n'GLU', 'E',\n'GLV', \
'X',\n'GLW', 'X',\n'GLY', 'G',\n'GLZ', 'X',\n'GM1'\
, 'X',\n'GMA', 'X',\n'GMC', 'X',\n'GMH', 'X',\n'GM\
P', 'X',\n'GMY', 'X',\n'GN7', 'X',\n'GNA', 'X',\n'\
GNB', 'X',\n'GNH', 'X',\n'GNP', 'X',\n'GNT', 'X',\\
n'GOA', 'X',\n'GOL', 'X',\n'GOX', 'X',\n'GP1', 'X'\
,\n'GP3', 'X',\n'GP4', 'X',\n'GP6', 'X',\n'GP8', '\
X',\n'GPB', 'E',\n'GPC', 'X',\n'GPE', 'X',\n'GPG',\
 'X',\n'GPI', 'X',\n'GPJ', 'X',\n'GPL', 'K',\n'GPM\
', 'X',\n'GPN', 'G',\n'GPP', 'X',\n'GPR', 'X',\n'G\
PS', 'X',\n'GPX', 'X',\n'GR1', 'X',\n'GR3', 'X',\n\
'GR4', 'X',\n'GSA', 'X',\n'GSB', 'X',\n'GSC', 'G',\
\n'GSE', 'S',\n'GSH', 'X',\n'GSP', 'X',\n'GSR', 'X\
',\n'GSS', 'X',\n'GT9', 'C',\n'GTA', 'X',\n'GTB', \
'X',\n'GTD', 'X',\n'GTE', 'X',\n'GTH', 'T',\n'GTN'\
, 'X',\n'GTO', 'X',\n'GTP', 'X',\n'GTR', 'X',\n'GT\
S', 'X',\n'GTT', 'X',\n'GTX', 'X',\n'GTZ', 'X',\n'\
GU7', 'X',\n'GUA', 'X',\n'GUD', 'X',\n'GUM', 'X',\\
n'GUN', 'X',\n'GUP', 'X',\n'GUR', 'X',\n'GW3', 'X'\
,\n'GZZ', 'X',\n'H2B', 'X',\n'H2P', 'H',\n'H2S', '\
X',\n'H2U', 'X',\n'H4B', 'X',\n'H5M', 'P',\n'H5P',\
 'X',\n'HAA', 'X',\n'HAB', 'X',\n'HAC', 'A',\n'HAD\
', 'X',\n'HAE', 'X',\n'HAG', 'X',\n'HAI', 'X',\n'H\
AM', 'X',\n'HAP', 'X',\n'HAQ', 'X',\n'HAR', 'R',\n\
'HAS', 'X',\n'HAV', 'V',\n'HAX', 'X',\n'HAZ', 'X',\
\n'HBA', 'X',\n'HBC', 'X',\n'HBD', 'X',\n'HBI', 'X\
',\n'HBO', 'X',\n'HBU', 'X',\n'HBY', 'X',\n'HC0', \
'X',\n'HC1', 'X',\n'HC4', 'X',\n'HCA', 'X',\n'HCC'\
, 'X',\n'HCI', 'X',\n'HCS', 'X',\n'HDA', 'X',\n'HD\
D', 'X',\n'HDF', 'X',\n'HDN', 'X',\n'HDS', 'X',\n'\
HDZ', 'X',\n'HE1', 'X',\n'HE6', 'X',\n'HEA', 'X',\\
n'HEB', 'X',\n'HEC', 'X',\n'HED', 'X',\n'HEE', 'X'\
,\n'HEF', 'X',\n'HEG', 'X',\n'HEM', 'X',\n'HEN', '\
X',\n'HEO', 'X',\n'HEP', 'X',\n'HEU', 'X',\n'HEV',\
 'X',\n'HEX', 'X',\n'HEZ', 'X',\n'HF1', 'X',\n'HFA\
', 'X',\n'HFP', 'X',\n'HGA', 'Q',\n'HGB', 'X',\n'H\
GC', 'X',\n'HGI', 'X',\n'HGU', 'X',\n'HHO', 'X',\n\
'HHP', 'X',\n'HIB', 'X',\n'HIC', 'H',\n'HII', 'X',\
\n'HIN', 'X',\n'HIO', 'X',\n'HIP', 'H',\n'HIS', 'H\
',\n'HLE', 'X',\n'HLT', 'X',\n'HMA', 'A',\n'HMB', \
'X',\n'HMC', 'X',\n'HMD', 'X',\n'HMF', 'A',\n'HMG'\
, 'X',\n'HMH', 'X',\n'HMI', 'L',\n'HMM', 'X',\n'HM\
N', 'X',\n'HMO', 'X',\n'HMP', 'X',\n'HMR', 'R',\n'\
HNI', 'X',\n'HNP', 'X',\n'HOA', 'X',\n'HOE', 'X',\\
n'HOH', 'X',\n'HOM', 'X',\n'HOP', 'X',\n'HOQ', 'X'\
,\n'HP1', 'A',\n'HP2', 'A',\n'HP3', 'X',\n'HPA', '\
X',\n'HPB', 'X',\n'HPC', 'X',\n'HPD', 'X',\n'HPE',\
 'A',\n'HPG', 'X',\n'HPH', 'F',\n'HPP', 'X',\n'HPQ\
', 'F',\n'HPR', 'X',\n'HPT', 'X',\n'HPY', 'X',\n'H\
QO', 'X',\n'HQQ', 'X',\n'HQU', 'X',\n'HRG', 'R',\n\
'HRI', 'X',\n'HSA', 'X',\n'HSE', 'S',\n'HSF', 'X',\
\n'HSM', 'X',\n'HSO', 'H',\n'HSP', 'X',\n'HT1', 'X\
',\n'HT2', 'X',\n'HTA', 'X',\n'HTL', 'X',\n'HTO', \
'X',\n'HTP', 'X',\n'HTR', 'W',\n'HUP', 'X',\n'HUX'\
, 'X',\n'HV5', 'A',\n'HV7', 'X',\n'HV8', 'X',\n'HX\
A', 'X',\n'HXC', 'X',\n'HXP', 'X',\n'HY1', 'X',\n'\
HYA', 'X',\n'HYB', 'X',\n'HYD', 'X',\n'HYG', 'X',\\
n'HYP', 'P',\n'I06', 'X',\n'I10', 'X',\n'I11', 'X'\
,\n'I17', 'X',\n'I2P', 'X',\n'I3N', 'X',\n'I3P', '\
X',\n'I40', 'X',\n'I48', 'X',\n'I4B', 'X',\n'I52',\
 'X',\n'I5P', 'X',\n'I84', 'G',\n'IAG', 'G',\n'IAS\
', 'X',\n'IB2', 'X',\n'IBB', 'X',\n'IBP', 'X',\n'I\
BR', 'X',\n'IBS', 'X',\n'IBZ', 'X',\n'IC1', 'X',\n\
'ICA', 'X',\n'ICI', 'X',\n'ICL', 'X',\n'ICP', 'X',\
\n'ICT', 'X',\n'ICU', 'X',\n'ID2', 'X',\n'IDC', 'X\
',\n'IDG', 'X',\n'IDH', 'X',\n'IDM', 'X',\n'IDO', \
'X',\n'IDP', 'X',\n'IDR', 'X',\n'IDS', 'X',\n'IDT'\
, 'X',\n'IDU', 'X',\n'IFG', 'X',\n'IFP', 'X',\n'IG\
L', 'X',\n'IGN', 'X',\n'IGP', 'X',\n'IGU', 'X',\n'\
IH1', 'X',\n'IH2', 'X',\n'IH3', 'X',\n'IHB', 'X',\\
n'IHN', 'X',\n'IHP', 'X',\n'IIC', 'X',\n'IIL', 'I'\
,\n'IIP', 'X',\n'IK2', 'X',\n'IKT', 'X',\n'ILA', '\
I',\n'ILE', 'I',\n'ILG', 'X',\n'ILO', 'X',\n'ILX',\
 'I',\n'IM1', 'X',\n'IM2', 'X',\n'IMC', 'X',\n'IMD\
', 'X',\n'IME', 'X',\n'IMF', 'X',\n'IMG', 'X',\n'I\
MH', 'X',\n'IMI', 'X',\n'IML', 'I',\n'IMM', 'X',\n\
'IMN', 'X',\n'IMO', 'X',\n'IMP', 'X',\n'IMR', 'X',\
\n'IMU', 'X',\n'IN0', 'D',\n'IN1', 'R',\n'IN2', 'K\
',\n'IN3', 'L',\n'IN4', 'X',\n'IN5', 'A',\n'IN6', \
'L',\n'IN7', 'X',\n'IN8', 'X',\n'IN9', 'X',\n'INA'\
, 'L',\n'INB', 'X',\n'INC', 'X',\n'IND', 'X',\n'IN\
E', 'X',\n'INF', 'F',\n'ING', 'F',\n'INH', 'R',\n'\
INI', 'X',\n'INJ', 'X',\n'INK', 'X',\n'INL', 'X',\\
n'INM', 'X',\n'INN', 'A',\n'INO', 'X',\n'INP', 'X'\
,\n'INQ', 'X',\n'INR', 'X',\n'INS', 'X',\n'INT', '\
V',\n'INU', 'X',\n'INV', 'X',\n'INW', 'X',\n'INX',\
 'X',\n'INY', 'X',\n'INZ', 'X',\n'IOA', 'X',\n'IOB\
', 'X',\n'IOC', 'X',\n'IOD', 'X',\n'IOE', 'X',\n'I\
OF', 'X',\n'IOH', 'X',\n'IOL', 'X',\n'IOP', 'X',\n\
'IP1', 'X',\n'IP2', 'X',\n'IP3', 'X',\n'IP4', 'X',\
\n'IPA', 'X',\n'IPB', 'X',\n'IPD', 'X',\n'IPG', 'G\
',\n'IPH', 'X',\n'IPL', 'X',\n'IPM', 'X',\n'IPN', \
'X',\n'IPO', 'F',\n'IPP', 'X',\n'IPS', 'X',\n'IPT'\
, 'X',\n'IPU', 'X',\n'IPY', 'A',\n'IQB', 'X',\n'IQ\
P', 'X',\n'IQS', 'X',\n'IR3', 'X',\n'IRI', 'X',\n'\
IRP', 'X',\n'ISA', 'X',\n'ISF', 'X',\n'ISO', 'X',\\
n'ISP', 'X',\n'ISQ', 'X',\n'ISU', 'X',\n'ITM', 'X'\
,\n'ITP', 'X',\n'ITR', 'W',\n'ITS', 'X',\n'ITU', '\
X',\n'IU5', 'X',\n'IUM', 'X',\n'IUR', 'X',\n'IVA',\
 'X',\n'IYG', 'G',\n'IYR', 'Y',\n'J77', 'X',\n'J78\
', 'X',\n'J80', 'X',\n'JE2', 'X',\n'JEN', 'X',\n'J\
ST', 'X',\n'K21', 'X',\n'KAH', 'X',\n'KAI', 'X',\n\
'KAM', 'X',\n'KAN', 'X',\n'KAP', 'X',\n'KCP', 'X',\
\n'KCX', 'K',\n'KDO', 'X',\n'KEF', 'X',\n'KET', 'X\
',\n'KGR', 'X',\n'KH1', 'X',\n'KIF', 'X',\n'KIV', \
'V',\n'KNI', 'X',\n'KPH', 'K',\n'KTH', 'X',\n'KTN'\
, 'X',\n'KTP', 'X',\n'KWT', 'X',\n'L04', 'X',\n'L1\
P', 'X',\n'L24', 'E',\n'L2P', 'X',\n'L34', 'E',\n'\
L37', 'E',\n'L3P', 'X',\n'L4P', 'X',\n'L75', 'X',\\
n'LAC', 'X',\n'LAD', 'X',\n'LAK', 'X',\n'LAM', 'X'\
,\n'LAR', 'X',\n'LAT', 'X',\n'LAX', 'X',\n'LCO', '\
X',\n'LCP', 'X',\n'LCS', 'X',\n'LDA', 'X',\n'LDO',\
 'L',\n'LDP', 'X',\n'LEA', 'X',\n'LEO', 'X',\n'LEU\
', 'L',\n'LG2', 'X',\n'LG6', 'X',\n'LGC', 'X',\n'L\
GP', 'X',\n'LHG', 'X',\n'LHY', 'F',\n'LI1', 'X',\n\
'LIG', 'X',\n'LIL', 'X',\n'LIM', 'X',\n'LIN', 'X',\
\n'LIO', 'X',\n'LIP', 'X',\n'LLA', 'X',\n'LLP', 'K\
',\n'LLY', 'K',\n'LMG', 'X',\n'LML', 'X',\n'LMT', \
'X',\n'LMU', 'X',\n'LMZ', 'X',\n'LNK', 'X',\n'LNL'\
, 'X',\n'LNO', 'X',\n'LOF', 'X',\n'LOL', 'L',\n'LO\
M', 'X',\n'LOR', 'X',\n'LOS', 'X',\n'LOV', 'L',\n'\
LOX', 'X',\n'LP1', 'X',\n'LP2', 'R',\n'LPA', 'X',\\
n'LPC', 'X',\n'LPF', 'X',\n'LPL', 'X',\n'LPM', 'X'\
,\n'LPP', 'X',\n'LRB', 'X',\n'LRU', 'X',\n'LS1', '\
X',\n'LS2', 'X',\n'LS3', 'X',\n'LS4', 'X',\n'LS5',\
 'X',\n'LTA', 'X',\n'LTL', 'X',\n'LTR', 'W',\n'LUM\
', 'X',\n'LVS', 'L',\n'LXC', 'X',\n'LY2', 'X',\n'L\
Y3', 'X',\n'LYA', 'X',\n'LYB', 'X',\n'LYC', 'X',\n\
'LYD', 'X',\n'LYM', 'K',\n'LYN', 'X',\n'LYS', 'K',\
\n'LYT', 'X',\n'LYW', 'X',\n'LYZ', 'K',\n'M1A', 'X\
',\n'M1G', 'X',\n'M2G', 'X',\n'M3L', 'K',\n'M6P', \
'X',\n'M6T', 'X',\n'M7G', 'X',\n'MA1', 'X',\n'MA2'\
, 'X',\n'MA3', 'X',\n'MA4', 'X',\n'MA6', 'X',\n'MA\
A', 'A',\n'MAB', 'X',\n'MAC', 'X',\n'MAE', 'X',\n'\
MAG', 'X',\n'MAH', 'X',\n'MAI', 'R',\n'MAK', 'X',\\
n'MAL', 'X',\n'MAM', 'X',\n'MAN', 'X',\n'MAO', 'X'\
,\n'MAP', 'X',\n'MAR', 'X',\n'MAS', 'X',\n'MAT', '\
X',\n'MAU', 'X',\n'MAZ', 'X',\n'MBA', 'X',\n'MBD',\
 'X',\n'MBG', 'X',\n'MBH', 'X',\n'MBN', 'X',\n'MBO\
', 'X',\n'MBR', 'X',\n'MBS', 'X',\n'MBV', 'X',\n'M\
BZ', 'X',\n'MCA', 'X',\n'MCD', 'X',\n'MCE', 'X',\n\
'MCG', 'G',\n'MCI', 'X',\n'MCN', 'X',\n'MCP', 'X',\
\n'MCT', 'X',\n'MCY', 'X',\n'MD2', 'X',\n'MDA', 'X\
',\n'MDC', 'X',\n'MDG', 'X',\n'MDH', 'X',\n'MDL', \
'X',\n'MDM', 'X',\n'MDN', 'X',\n'MDP', 'X',\n'ME6'\
, 'X',\n'MEB', 'X',\n'MEC', 'X',\n'MEL', 'X',\n'ME\
N', 'N',\n'MEP', 'X',\n'MER', 'X',\n'MES', 'X',\n'\
MET', 'M',\n'MEV', 'X',\n'MF2', 'X',\n'MF3', 'M',\\
n'MFB', 'X',\n'MFD', 'X',\n'MFU', 'X',\n'MG7', 'X'\
,\n'MGA', 'X',\n'MGB', 'X',\n'MGD', 'X',\n'MGG', '\
R',\n'MGL', 'X',\n'MGN', 'Q',\n'MGO', 'X',\n'MGP',\
 'X',\n'MGR', 'X',\n'MGS', 'X',\n'MGT', 'X',\n'MGU\
', 'X',\n'MGY', 'G',\n'MHB', 'X',\n'MHF', 'X',\n'M\
HL', 'L',\n'MHM', 'X',\n'MHO', 'M',\n'MHS', 'H',\n\
'MHZ', 'X',\n'MIA', 'X',\n'MIC', 'X',\n'MID', 'X',\
\n'MIL', 'X',\n'MIM', 'X',\n'MIN', 'G',\n'MIP', 'X\
',\n'MIS', 'S',\n'MIT', 'X',\n'MJI', 'X',\n'MK1', \
'X',\n'MKC', 'X',\n'MLA', 'X',\n'MLC', 'X',\n'MLE'\
, 'L',\n'MLN', 'X',\n'MLT', 'X',\n'MLY', 'K',\n'ML\
Z', 'K',\n'MM3', 'X',\n'MM4', 'X',\n'MMA', 'X',\n'\
MMC', 'X',\n'MME', 'M',\n'MMO', 'R',\n'MMP', 'X',\\
n'MMQ', 'X',\n'MMT', 'X',\n'MN1', 'X',\n'MN2', 'X'\
,\n'MN3', 'X',\n'MN5', 'X',\n'MN7', 'X',\n'MN8', '\
X',\n'MNA', 'X',\n'MNB', 'X',\n'MNC', 'X',\n'MNG',\
 'X',\n'MNL', 'L',\n'MNO', 'X',\n'MNP', 'X',\n'MNQ\
', 'X',\n'MNS', 'X',\n'MNT', 'X',\n'MNV', 'V',\n'M\
O1', 'X',\n'MO2', 'X',\n'MO3', 'X',\n'MO4', 'X',\n\
'MO5', 'X',\n'MO6', 'X',\n'MOA', 'X',\n'MOB', 'X',\
\n'MOC', 'X',\n'MOE', 'X',\n'MOG', 'X',\n'MOH', 'X\
',\n'MOL', 'X',\n'MOO', 'X',\n'MOP', 'X',\n'MOR', \
'X',\n'MOS', 'X',\n'MOT', 'X',\n'MOX', 'X',\n'MP1'\
, 'X',\n'MP3', 'X',\n'MPA', 'X',\n'MPB', 'X',\n'MP\
C', 'X',\n'MPD', 'X',\n'MPG', 'X',\n'MPH', 'M',\n'\
MPI', 'X',\n'MPJ', 'M',\n'MPL', 'X',\n'MPN', 'X',\\
n'MPO', 'X',\n'MPP', 'X',\n'MPQ', 'G',\n'MPR', 'X'\
,\n'MPS', 'X',\n'MQ0', 'X',\n'MQ7', 'X',\n'MQ8', '\
X',\n'MQ9', 'X',\n'MQI', 'X',\n'MR2', 'X',\n'MRC',\
 'X',\n'MRM', 'X',\n'MRP', 'X',\n'MS2', 'X',\n'MSA\
', 'X',\n'MSB', 'X',\n'MSD', 'X',\n'MSE', 'M',\n'M\
SF', 'X',\n'MSI', 'X',\n'MSO', 'M',\n'MSQ', 'X',\n\
'MST', 'X',\n'MSU', 'X',\n'MTA', 'X',\n'MTB', 'X',\
\n'MTC', 'X',\n'MTD', 'X',\n'MTE', 'X',\n'MTF', 'X\
',\n'MTG', 'X',\n'MTO', 'X',\n'MTS', 'X',\n'MTT', \
'X',\n'MTX', 'X',\n'MTY', 'Y',\n'MUG', 'X',\n'MUP'\
, 'X',\n'MUR', 'X',\n'MVA', 'V',\n'MW1', 'X',\n'MW\
2', 'X',\n'MXA', 'X',\n'MXY', 'X',\n'MYA', 'X',\n'\
MYC', 'X',\n'MYG', 'X',\n'MYR', 'X',\n'MYS', 'X',\\
n'MYT', 'X',\n'MZM', 'X',\n'N1T', 'X',\n'N25', 'X'\
,\n'N2B', 'X',\n'N3T', 'X',\n'N4B', 'X',\n'NA2', '\
X',\n'NA5', 'X',\n'NA6', 'X',\n'NAA', 'X',\n'NAB',\
 'X',\n'NAC', 'X',\n'NAD', 'X',\n'NAE', 'X',\n'NAF\
', 'X',\n'NAG', 'X',\n'NAH', 'X',\n'NAI', 'X',\n'N\
AL', 'A',\n'NAM', 'A',\n'NAN', 'X',\n'NAO', 'X',\n\
'NAP', 'X',\n'NAQ', 'X',\n'NAR', 'X',\n'NAS', 'X',\
\n'NAU', 'X',\n'NAV', 'X',\n'NAW', 'X',\n'NAX', 'X\
',\n'NAY', 'X',\n'NBA', 'X',\n'NBD', 'X',\n'NBE', \
'X',\n'NBG', 'X',\n'NBN', 'X',\n'NBP', 'X',\n'NBS'\
, 'X',\n'NBU', 'X',\n'NCA', 'X',\n'NCB', 'A',\n'NC\
D', 'X',\n'NCH', 'X',\n'NCM', 'X',\n'NCN', 'X',\n'\
NCO', 'X',\n'NCR', 'X',\n'NCS', 'X',\n'ND4', 'X',\\
n'NDA', 'X',\n'NDC', 'X',\n'NDD', 'X',\n'NDO', 'X'\
,\n'NDP', 'X',\n'NDT', 'X',\n'NEA', 'X',\n'NEB', '\
X',\n'NED', 'X',\n'NEM', 'H',\n'NEN', 'X',\n'NEO',\
 'X',\n'NEP', 'H',\n'NEQ', 'X',\n'NES', 'X',\n'NET\
', 'X',\n'NEV', 'X',\n'NFA', 'F',\n'NFE', 'X',\n'N\
FG', 'X',\n'NFP', 'X',\n'NFS', 'X',\n'NG6', 'X',\n\
'NGA', 'X',\n'NGL', 'X',\n'NGM', 'X',\n'NGO', 'X',\
\n'NGP', 'X',\n'NGT', 'X',\n'NGU', 'X',\n'NH2', 'X\
',\n'NH3', 'X',\n'NH4', 'X',\n'NHD', 'X',\n'NHE', \
'X',\n'NHM', 'X',\n'NHP', 'X',\n'NHR', 'X',\n'NHS'\
, 'X',\n'NI1', 'X',\n'NI2', 'X',\n'NIC', 'X',\n'NI\
D', 'X',\n'NIK', 'X',\n'NIO', 'X',\n'NIP', 'X',\n'\
NIT', 'X',\n'NIU', 'X',\n'NIY', 'Y',\n'NLA', 'X',\\
n'NLE', 'L',\n'NLG', 'X',\n'NLN', 'L',\n'NLP', 'L'\
,\n'NM1', 'X',\n'NMA', 'A',\n'NMB', 'X',\n'NMC', '\
G',\n'NMD', 'X',\n'NME', 'X',\n'NMN', 'X',\n'NMO',\
 'X',\n'NMQ', 'X',\n'NMX', 'X',\n'NMY', 'X',\n'NNH\
', 'R',\n'NNO', 'X',\n'NO2', 'X',\n'NO3', 'X',\n'N\
OA', 'X',\n'NOD', 'X',\n'NOJ', 'X',\n'NON', 'X',\n\
'NOP', 'X',\n'NOR', 'X',\n'NOS', 'X',\n'NOV', 'X',\
\n'NOX', 'X',\n'NP3', 'X',\n'NPA', 'X',\n'NPC', 'X\
',\n'NPD', 'X',\n'NPE', 'X',\n'NPF', 'X',\n'NPH', \
'C',\n'NPI', 'X',\n'NPL', 'X',\n'NPN', 'X',\n'NPO'\
, 'X',\n'NPP', 'X',\n'NPT', 'X',\n'NPY', 'X',\n'NR\
G', 'R',\n'NRI', 'X',\n'NS1', 'X',\n'NS5', 'X',\n'\
NSP', 'X',\n'NTA', 'X',\n'NTB', 'X',\n'NTC', 'X',\\
n'NTH', 'X',\n'NTM', 'X',\n'NTP', 'X',\n'NTS', 'X'\
,\n'NTU', 'X',\n'NTZ', 'X',\n'NU1', 'X',\n'NVA', '\
V',\n'NVI', 'X',\n'NVP', 'X',\n'NW1', 'X',\n'NYP',\
 'X',\n'O4M', 'X',\n'OAA', 'X',\n'OAI', 'X',\n'OAP\
', 'X',\n'OAR', 'X',\n'OAS', 'S',\n'OBA', 'X',\n'O\
BN', 'X',\n'OC1', 'X',\n'OC2', 'X',\n'OC3', 'X',\n\
'OC4', 'X',\n'OC5', 'X',\n'OC6', 'X',\n'OC7', 'X',\
\n'OCL', 'X',\n'OCM', 'X',\n'OCN', 'X',\n'OCO', 'X\
',\n'OCP', 'X',\n'OCS', 'C',\n'OCT', 'X',\n'OCV', \
'K',\n'OCY', 'C',\n'ODA', 'X',\n'ODS', 'X',\n'OES'\
, 'X',\n'OET', 'X',\n'OF1', 'X',\n'OF2', 'X',\n'OF\
3', 'X',\n'OFL', 'X',\n'OFO', 'X',\n'OHE', 'X',\n'\
OHO', 'X',\n'OHT', 'X',\n'OIC', 'X',\n'OIP', 'X',\\
n'OKA', 'X',\n'OLA', 'X',\n'OLE', 'X',\n'OLI', 'X'\
,\n'OLO', 'X',\n'OMB', 'X',\n'OMC', 'X',\n'OMD', '\
X',\n'OME', 'X',\n'OMG', 'X',\n'OMP', 'X',\n'OMT',\
 'M',\n'OMU', 'X',\n'ONE', 'X',\n'ONL', 'L',\n'ONP\
', 'X',\n'OPA', 'X',\n'OPD', 'X',\n'OPE', 'X',\n'O\
PG', 'X',\n'OPH', 'X',\n'OPN', 'X',\n'OPP', 'X',\n\
'OPR', 'R',\n'ORN', 'X',\n'ORO', 'X',\n'ORP', 'X',\
\n'OSB', 'X',\n'OSS', 'X',\n'OTA', 'X',\n'OTB', 'X\
',\n'OTE', 'X',\n'OTG', 'X',\n'OUT', 'X',\n'OVA', \
'X',\n'OWQ', 'X',\n'OXA', 'X',\n'OXE', 'X',\n'OXI'\
, 'X',\n'OXL', 'X',\n'OXM', 'X',\n'OXN', 'X',\n'OX\
O', 'X',\n'OXP', 'X',\n'OXS', 'X',\n'OXY', 'X',\n'\
P11', 'A',\n'P24', 'X',\n'P28', 'X',\n'P2P', 'X',\\
n'P2U', 'X',\n'P3M', 'X',\n'P4C', 'X',\n'P4P', 'X'\
,\n'P5P', 'X',\n'P6G', 'X',\n'PA1', 'X',\n'PA2', '\
X',\n'PA3', 'X',\n'PA4', 'X',\n'PA5', 'X',\n'PAA',\
 'X',\n'PAB', 'X',\n'PAC', 'X',\n'PAD', 'X',\n'PAE\
', 'X',\n'PAG', 'X',\n'PAH', 'X',\n'PAI', 'X',\n'P\
AL', 'D',\n'PAM', 'X',\n'PAN', 'X',\n'PAO', 'X',\n\
'PAP', 'A',\n'PAQ', 'F',\n'PAR', 'X',\n'PAS', 'X',\
\n'PAT', 'W',\n'PBA', 'X',\n'PBB', 'X',\n'PBC', 'X\
',\n'PBF', 'F',\n'PBG', 'X',\n'PBI', 'X',\n'PBM', \
'X',\n'PBN', 'X',\n'PBP', 'X',\n'PBR', 'X',\n'PBZ'\
, 'X',\n'PC2', 'X',\n'PCA', 'E',\n'PCB', 'X',\n'PC\
D', 'X',\n'PCE', 'X',\n'PCG', 'X',\n'PCH', 'X',\n'\
PCL', 'X',\n'PCM', 'X',\n'PCP', 'X',\n'PCR', 'X',\\
n'PCS', 'X',\n'PCU', 'X',\n'PCV', 'X',\n'PCY', 'X'\
,\n'PD1', 'X',\n'PDA', 'X',\n'PDC', 'X',\n'PDD', '\
A',\n'PDE', 'A',\n'PDI', 'X',\n'PDL', 'A',\n'PDN',\
 'X',\n'PDO', 'X',\n'PDP', 'X',\n'PDT', 'X',\n'PDU\
', 'X',\n'PE2', 'X',\n'PE6', 'X',\n'PEA', 'X',\n'P\
EB', 'X',\n'PEC', 'X',\n'PED', 'X',\n'PEE', 'X',\n\
'PEF', 'X',\n'PEG', 'X',\n'PEL', 'X',\n'PEO', 'X',\
\n'PEP', 'X',\n'PEQ', 'X',\n'PER', 'X',\n'PET', 'X\
',\n'PFB', 'X',\n'PFC', 'X',\n'PFG', 'X',\n'PFL', \
'X',\n'PFM', 'X',\n'PFZ', 'X',\n'PG4', 'X',\n'PG5'\
, 'X',\n'PG6', 'X',\n'PGA', 'X',\n'PGC', 'X',\n'PG\
D', 'X',\n'PGE', 'X',\n'PGG', 'G',\n'PGH', 'X',\n'\
PGL', 'X',\n'PGO', 'X',\n'PGP', 'X',\n'PGQ', 'X',\\
n'PGR', 'X',\n'PGS', 'X',\n'PGU', 'X',\n'PGX', 'X'\
,\n'PGY', 'G',\n'PH1', 'X',\n'PH2', 'X',\n'PH3', '\
X',\n'PHA', 'F',\n'PHB', 'X',\n'PHC', 'X',\n'PHD',\
 'X',\n'PHE', 'F',\n'PHG', 'X',\n'PHH', 'X',\n'PHI\
', 'F',\n'PHL', 'F',\n'PHM', 'X',\n'PHN', 'X',\n'P\
HO', 'X',\n'PHP', 'X',\n'PHQ', 'X',\n'PHS', 'H',\n\
'PHT', 'X',\n'PHW', 'P',\n'PHY', 'X',\n'PI1', 'X',\
\n'PI2', 'X',\n'PI3', 'X',\n'PI4', 'X',\n'PI5', 'X\
',\n'PI6', 'X',\n'PI7', 'X',\n'PI8', 'X',\n'PI9', \
'X',\n'PIA', 'X',\n'PIB', 'X',\n'PIC', 'X',\n'PID'\
, 'X',\n'PIG', 'X',\n'PIH', 'X',\n'PIM', 'X',\n'PI\
N', 'X',\n'PIO', 'X',\n'PIP', 'X',\n'PIQ', 'X',\n'\
PIR', 'X',\n'PIV', 'X',\n'PKF', 'X',\n'PL1', 'X',\\
n'PL9', 'X',\n'PLA', 'D',\n'PLC', 'X',\n'PLE', 'L'\
,\n'PLG', 'G',\n'PLH', 'X',\n'PLM', 'X',\n'PLP', '\
X',\n'PLS', 'S',\n'PLT', 'W',\n'PLU', 'L',\n'PLY',\
 'X',\n'PMA', 'X',\n'PMB', 'X',\n'PMC', 'X',\n'PME\
', 'F',\n'PML', 'X',\n'PMM', 'X',\n'PMO', 'X',\n'P\
MP', 'X',\n'PMS', 'X',\n'PMY', 'X',\n'PN2', 'X',\n\
'PNA', 'X',\n'PNB', 'X',\n'PNC', 'G',\n'PND', 'X',\
\n'PNE', 'A',\n'PNF', 'X',\n'PNG', 'X',\n'PNI', 'X\
',\n'PNL', 'X',\n'PNM', 'X',\n'PNN', 'X',\n'PNO', \
'X',\n'PNP', 'X',\n'PNQ', 'X',\n'PNS', 'X',\n'PNT'\
, 'X',\n'PNU', 'X',\n'PO2', 'X',\n'PO4', 'X',\n'PO\
B', 'X',\n'POC', 'X',\n'POL', 'X',\n'POM', 'P',\n'\
PON', 'X',\n'POP', 'X',\n'POR', 'X',\n'POS', 'X',\\
n'PP1', 'X',\n'PP2', 'X',\n'PP3', 'A',\n'PP4', 'X'\
,\n'PP5', 'X',\n'PP6', 'X',\n'PP7', 'X',\n'PP8', '\
N',\n'PP9', 'X',\n'PPB', 'X',\n'PPC', 'X',\n'PPD',\
 'X',\n'PPE', 'E',\n'PPG', 'X',\n'PPH', 'F',\n'PPI\
', 'X',\n'PPJ', 'V',\n'PPL', 'X',\n'PPM', 'X',\n'P\
PN', 'A',\n'PPO', 'X',\n'PPP', 'X',\n'PPQ', 'X',\n\
'PPR', 'X',\n'PPS', 'X',\n'PPT', 'X',\n'PPU', 'X',\
\n'PPX', 'F',\n'PPY', 'X',\n'PPZ', 'X',\n'PQ0', 'X\
',\n'PQN', 'X',\n'PQQ', 'X',\n'PR1', 'X',\n'PR2', \
'X',\n'PR3', 'X',\n'PRA', 'X',\n'PRB', 'X',\n'PRC'\
, 'X',\n'PRD', 'X',\n'PRE', 'X',\n'PRF', 'X',\n'PR\
H', 'X',\n'PRI', 'P',\n'PRL', 'X',\n'PRN', 'X',\n'\
PRO', 'P',\n'PRP', 'X',\n'PRR', 'A',\n'PRS', 'P',\\
n'PRZ', 'X',\n'PS0', 'X',\n'PSA', 'X',\n'PSD', 'X'\
,\n'PSE', 'X',\n'PSF', 'S',\n'PSG', 'X',\n'PSI', '\
X',\n'PSO', 'X',\n'PSQ', 'X',\n'PSS', 'X',\n'PST',\
 'X',\n'PSU', 'X',\n'PT1', 'X',\n'PT3', 'X',\n'PTA\
', 'X',\n'PTC', 'X',\n'PTD', 'X',\n'PTE', 'X',\n'P\
TH', 'Y',\n'PTL', 'X',\n'PTM', 'Y',\n'PTN', 'X',\n\
'PTO', 'X',\n'PTP', 'X',\n'PTR', 'Y',\n'PTS', 'X',\
\n'PTT', 'X',\n'PTU', 'X',\n'PTY', 'X',\n'PUA', 'X\
',\n'PUB', 'X',\n'PUR', 'X',\n'PUT', 'X',\n'PVA', \
'X',\n'PVB', 'X',\n'PVH', 'H',\n'PVL', 'X',\n'PXA'\
, 'X',\n'PXF', 'X',\n'PXG', 'X',\n'PXP', 'X',\n'PX\
Y', 'X',\n'PXZ', 'X',\n'PY2', 'X',\n'PY4', 'X',\n'\
PY5', 'X',\n'PY6', 'X',\n'PYA', 'A',\n'PYC', 'X',\\
n'PYD', 'X',\n'PYE', 'X',\n'PYL', 'X',\n'PYM', 'X'\
,\n'PYO', 'X',\n'PYP', 'X',\n'PYQ', 'X',\n'PYR', '\
X',\n'PYS', 'X',\n'PYT', 'X',\n'PYX', 'X',\n'PYY',\
 'X',\n'PYZ', 'X',\n'PZQ', 'X',\n'Q82', 'X',\n'QNC\
', 'X',\n'QND', 'X',\n'QSI', 'Q',\n'QTR', 'X',\n'Q\
UA', 'X',\n'QUE', 'X',\n'QUI', 'X',\n'QUO', 'X',\n\
'R11', 'X',\n'R12', 'X',\n'R13', 'X',\n'R18', 'X',\
\n'R1P', 'X',\n'R56', 'X',\n'R5P', 'X',\n'RA2', 'X\
',\n'RAD', 'X',\n'RAI', 'X',\n'RAL', 'X',\n'RAM', \
'X',\n'RAN', 'X',\n'RAP', 'X',\n'RBF', 'X',\n'RBU'\
, 'X',\n'RCA', 'X',\n'RCL', 'X',\n'RCO', 'X',\n'RD\
C', 'X',\n'RDF', 'W',\n'RE9', 'X',\n'REA', 'X',\n'\
RED', 'K',\n'REO', 'X',\n'REP', 'X',\n'RET', 'X',\\
n'RFA', 'X',\n'RFB', 'X',\n'RFL', 'X',\n'RFP', 'X'\
,\n'RG1', 'X',\n'RGS', 'X',\n'RH1', 'X',\n'RHA', '\
X',\n'RHC', 'X',\n'RHD', 'X',\n'RHM', 'X',\n'RHO',\
 'X',\n'RHQ', 'X',\n'RHS', 'X',\n'RIA', 'X',\n'RIB\
', 'X',\n'RIC', 'X',\n'RIF', 'X',\n'RIN', 'X',\n'R\
IP', 'X',\n'RIT', 'X',\n'RMB', 'X',\n'RMN', 'X',\n\
'RMP', 'X',\n'RNG', 'X',\n'RNS', 'X',\n'RNT', 'X',\
\n'RO2', 'X',\n'RO4', 'X',\n'ROC', 'N',\n'ROI', 'X\
',\n'ROM', 'X',\n'RON', 'V',\n'ROP', 'X',\n'ROS', \
'X',\n'ROX', 'X',\n'RPA', 'X',\n'RPD', 'X',\n'RPH'\
, 'X',\n'RPL', 'X',\n'RPP', 'X',\n'RPR', 'X',\n'RP\
X', 'X',\n'RQ3', 'X',\n'RR1', 'X',\n'RR6', 'X',\n'\
RRS', 'X',\n'RS1', 'X',\n'RS2', 'X',\n'RS7', 'X',\\
n'RSS', 'X',\n'RTA', 'X',\n'RTB', 'X',\n'RTC', 'X'\
,\n'RTL', 'X',\n'RUB', 'X',\n'RUN', 'X',\n'RWJ', '\
X',\n'RXP', 'X',\n'S02', 'X',\n'S11', 'X',\n'S1H',\
 'S',\n'S27', 'X',\n'S2C', 'C',\n'S3P', 'X',\n'S4U\
', 'X',\n'S57', 'X',\n'S58', 'X',\n'S5H', 'X',\n'S\
6G', 'X',\n'S80', 'X',\n'SAA', 'X',\n'SAB', 'X',\n\
'SAC', 'S',\n'SAD', 'X',\n'SAE', 'X',\n'SAF', 'X',\
\n'SAH', 'C',\n'SAI', 'C',\n'SAL', 'X',\n'SAM', 'M\
',\n'SAN', 'X',\n'SAP', 'X',\n'SAR', 'X',\n'SAS', \
'X',\n'SB1', 'X',\n'SB2', 'X',\n'SB3', 'X',\n'SB4'\
, 'X',\n'SB5', 'X',\n'SB6', 'X',\n'SBA', 'L',\n'SB\
B', 'X',\n'SBD', 'A',\n'SBI', 'X',\n'SBL', 'A',\n'\
SBN', 'X',\n'SBO', 'X',\n'SBR', 'X',\n'SBS', 'X',\\
n'SBT', 'X',\n'SBU', 'X',\n'SBX', 'X',\n'SC4', 'X'\
,\n'SCA', 'X',\n'SCC', 'X',\n'SCD', 'X',\n'SCH', '\
C',\n'SCI', 'X',\n'SCL', 'X',\n'SCM', 'X',\n'SCN',\
 'X',\n'SCO', 'X',\n'SCP', 'S',\n'SCR', 'X',\n'SCS\
', 'X',\n'SCV', 'C',\n'SCY', 'C',\n'SD8', 'X',\n'S\
DK', 'X',\n'SDZ', 'X',\n'SE4', 'X',\n'SEA', 'X',\n\
'SEB', 'S',\n'SEC', 'X',\n'SEG', 'A',\n'SEI', 'X',\
\n'SEL', 'S',\n'SEM', 'X',\n'SEO', 'X',\n'SEP', 'S\
',\n'SER', 'S',\n'SES', 'X',\n'SET', 'S',\n'SEU', \
'X',\n'SF4', 'X',\n'SFG', 'X',\n'SFN', 'X',\n'SFO'\
, 'X',\n'SGA', 'X',\n'SGC', 'X',\n'SGL', 'X',\n'SG\
M', 'X',\n'SGN', 'X',\n'SGP', 'X',\n'SHA', 'X',\n'\
SHC', 'X',\n'SHF', 'X',\n'SHH', 'X',\n'SHP', 'G',\\
n'SHR', 'E',\n'SHT', 'T',\n'SHU', 'X',\n'SI2', 'X'\
,\n'SIA', 'X',\n'SIF', 'X',\n'SIG', 'X',\n'SIH', '\
X',\n'SIM', 'X',\n'SIN', 'X',\n'SKD', 'X',\n'SKF',\
 'X',\n'SLB', 'X',\n'SLE', 'X',\n'SLZ', 'K',\n'SMA\
', 'X',\n'SMC', 'C',\n'SME', 'M',\n'SML', 'X',\n'S\
MM', 'M',\n'SMN', 'X',\n'SMP', 'X',\n'SMS', 'X',\n\
'SN1', 'X',\n'SN6', 'X',\n'SN7', 'X',\n'SNC', 'C',\
\n'SNN', 'X',\n'SNP', 'X',\n'SO1', 'X',\n'SO2', 'X\
',\n'SO3', 'X',\n'SO4', 'X',\n'SOA', 'X',\n'SOC', \
'C',\n'SOM', 'X',\n'SOR', 'X',\n'SOT', 'X',\n'SOX'\
, 'X',\n'SPA', 'X',\n'SPB', 'X',\n'SPC', 'X',\n'SP\
D', 'X',\n'SPE', 'X',\n'SPG', 'X',\n'SPH', 'X',\n'\
SPI', 'X',\n'SPK', 'X',\n'SPM', 'X',\n'SPN', 'X',\\
n'SPO', 'X',\n'SPP', 'X',\n'SPS', 'X',\n'SPY', 'X'\
,\n'SQU', 'X',\n'SRA', 'X',\n'SRB', 'X',\n'SRD', '\
X',\n'SRL', 'X',\n'SRM', 'X',\n'SRS', 'X',\n'SRY',\
 'X',\n'SSA', 'X',\n'SSB', 'X',\n'SSG', 'X',\n'SSP\
', 'X',\n'ST1', 'X',\n'ST2', 'X',\n'ST3', 'X',\n'S\
T4', 'X',\n'ST5', 'X',\n'ST6', 'X',\n'STA', 'X',\n\
'STB', 'X',\n'STE', 'X',\n'STG', 'X',\n'STI', 'X',\
\n'STL', 'X',\n'STN', 'X',\n'STO', 'X',\n'STP', 'X\
',\n'STR', 'X',\n'STU', 'X',\n'STY', 'Y',\n'SU1', \
'X',\n'SU2', 'X',\n'SUC', 'X',\n'SUI', 'X',\n'SUL'\
, 'X',\n'SUR', 'X',\n'SVA', 'S',\n'SWA', 'X',\n'T1\
6', 'X',\n'T19', 'X',\n'T23', 'X',\n'T29', 'X',\n'\
T33', 'X',\n'T3P', 'X',\n'T42', 'A',\n'T44', 'X',\\
n'T5A', 'X',\n'T6A', 'T',\n'T6P', 'X',\n'T80', 'X'\
,\n'T87', 'X',\n'TA1', 'X',\n'TAA', 'X',\n'TAB', '\
X',\n'TAC', 'X',\n'TAD', 'X',\n'TAF', 'X',\n'TAM',\
 'X',\n'TAP', 'X',\n'TAR', 'X',\n'TAS', 'X',\n'TAU\
', 'X',\n'TAX', 'X',\n'TAZ', 'X',\n'TB9', 'X',\n'T\
BA', 'X',\n'TBD', 'X',\n'TBG', 'G',\n'TBH', 'X',\n\
'TBM', 'T',\n'TBO', 'X',\n'TBP', 'X',\n'TBR', 'X',\
\n'TBS', 'X',\n'TBT', 'X',\n'TBU', 'X',\n'TBZ', 'X\
',\n'TC4', 'X',\n'TCA', 'X',\n'TCB', 'X',\n'TCH', \
'X',\n'TCK', 'X',\n'TCL', 'X',\n'TCM', 'X',\n'TCN'\
, 'X',\n'TCP', 'X',\n'TCR', 'W',\n'TCS', 'X',\n'TC\
Z', 'X',\n'TDA', 'X',\n'TDB', 'X',\n'TDG', 'X',\n'\
TDP', 'X',\n'TDR', 'X',\n'TDX', 'X',\n'TEA', 'X',\\
n'TEM', 'X',\n'TEN', 'X',\n'TEO', 'X',\n'TEP', 'X'\
,\n'TER', 'X',\n'TES', 'X',\n'TET', 'X',\n'TFA', '\
X',\n'TFB', 'X',\n'TFH', 'X',\n'TFI', 'X',\n'TFK',\
 'X',\n'TFP', 'X',\n'THA', 'X',\n'THB', 'X',\n'THC\
', 'T',\n'THD', 'X',\n'THE', 'X',\n'THF', 'X',\n'T\
HJ', 'X',\n'THK', 'X',\n'THM', 'X',\n'THN', 'X',\n\
'THO', 'T',\n'THP', 'X',\n'THQ', 'X',\n'THR', 'T',\
\n'THS', 'X',\n'THT', 'X',\n'THU', 'X',\n'THX', 'X\
',\n'THZ', 'X',\n'TI1', 'X',\n'TI2', 'X',\n'TI3', \
'P',\n'TIA', 'X',\n'TIH', 'A',\n'TK4', 'X',\n'TLA'\
, 'X',\n'TLC', 'X',\n'TLM', 'X',\n'TLN', 'X',\n'TL\
X', 'X',\n'TM5', 'X',\n'TM6', 'X',\n'TMA', 'X',\n'\
TMB', 'T',\n'TMC', 'X',\n'TMD', 'T',\n'TME', 'X',\\
n'TMF', 'X',\n'TML', 'K',\n'TMM', 'X',\n'TMN', 'X'\
,\n'TMP', 'X',\n'TMQ', 'X',\n'TMR', 'X',\n'TMT', '\
X',\n'TMZ', 'X',\n'TNB', 'C',\n'TND', 'X',\n'TNK',\
 'X',\n'TNP', 'X',\n'TNT', 'X',\n'TOA', 'X',\n'TOB\
', 'X',\n'TOC', 'X',\n'TOL', 'X',\n'TOP', 'X',\n'T\
OS', 'X',\n'TOT', 'X',\n'TP1', 'G',\n'TP2', 'P',\n\
'TP3', 'E',\n'TP4', 'E',\n'TP7', 'T',\n'TPA', 'X',\
\n'TPE', 'X',\n'TPF', 'X',\n'TPI', 'X',\n'TPL', 'W\
',\n'TPM', 'X',\n'TPN', 'G',\n'TPO', 'T',\n'TPP', \
'X',\n'TPQ', 'A',\n'TPR', 'P',\n'TPS', 'X',\n'TPT'\
, 'X',\n'TPV', 'X',\n'TPX', 'X',\n'TPY', 'X',\n'TQ\
3', 'X',\n'TQ4', 'X',\n'TQ5', 'X',\n'TQ6', 'X',\n'\
TR1', 'X',\n'TRA', 'X',\n'TRB', 'X',\n'TRC', 'X',\\
n'TRD', 'X',\n'TRE', 'X',\n'TRF', 'W',\n'TRG', 'K'\
,\n'TRH', 'X',\n'TRI', 'X',\n'TRJ', 'X',\n'TRM', '\
X',\n'TRN', 'W',\n'TRO', 'W',\n'TRP', 'W',\n'TRQ',\
 'X',\n'TRS', 'X',\n'TRX', 'W',\n'TRZ', 'X',\n'TS2\
', 'X',\n'TS3', 'X',\n'TS4', 'X',\n'TS5', 'X',\n'T\
SA', 'X',\n'TSB', 'X',\n'TSI', 'X',\n'TSM', 'X',\n\
'TSN', 'X',\n'TSP', 'X',\n'TSU', 'X',\n'TTA', 'X',\
\n'TTE', 'X',\n'TTN', 'X',\n'TTO', 'X',\n'TTP', 'X\
',\n'TTX', 'X',\n'TXL', 'X',\n'TYA', 'Y',\n'TYB', \
'Y',\n'TYD', 'X',\n'TYI', 'Y',\n'TYL', 'X',\n'TYM'\
, 'W',\n'TYN', 'Y',\n'TYQ', 'Y',\n'TYR', 'Y',\n'TY\
S', 'Y',\n'TYV', 'X',\n'TYY', 'A',\n'TZB', 'X',\n'\
TZC', 'X',\n'TZE', 'X',\n'TZL', 'X',\n'TZO', 'X',\\
n'TZP', 'X',\n'U01', 'X',\n'U02', 'X',\n'U03', 'X'\
,\n'U04', 'X',\n'U05', 'X',\n'U0E', 'X',\n'U10', '\
X',\n'U18', 'X',\n'U2G', 'X',\n'U3P', 'X',\n'U49',\
 'X',\n'U55', 'X',\n'U5P', 'X',\n'U66', 'X',\n'U89\
', 'X',\n'U8U', 'X',\n'UAA', 'X',\n'UAG', 'A',\n'U\
AP', 'X',\n'UAR', 'X',\n'UC1', 'X',\n'UC2', 'X',\n\
'UC3', 'X',\n'UC4', 'X',\n'UD1', 'X',\n'UD2', 'X',\
\n'UDP', 'X',\n'UDX', 'X',\n'UFG', 'X',\n'UFM', 'X\
',\n'UFP', 'X',\n'UGA', 'X',\n'UIN', 'X',\n'UKP', \
'A',\n'UM3', 'X',\n'UMA', 'A',\n'UMG', 'X',\n'UMP'\
, 'X',\n'UNA', 'X',\n'UND', 'X',\n'UNI', 'X',\n'UN\
K', 'X',\n'UNN', 'X',\n'UNX', 'X',\n'UP5', 'X',\n'\
UP6', 'X',\n'UPA', 'X',\n'UPF', 'X',\n'UPG', 'X',\\
n'UPP', 'X',\n'UQ1', 'X',\n'UQ2', 'X',\n'UQ6', 'X'\
,\n'UR2', 'X',\n'URA', 'X',\n'URE', 'X',\n'URF', '\
X',\n'URI', 'X',\n'URS', 'X',\n'UTP', 'X',\n'UVC',\
 'X',\n'UVW', 'X',\n'V35', 'X',\n'V36', 'X',\n'V4O\
', 'X',\n'V7O', 'X',\n'VAA', 'V',\n'VAC', 'X',\n'V\
AD', 'V',\n'VAF', 'V',\n'VAG', 'X',\n'VAL', 'V',\n\
'VAN', 'X',\n'VAS', 'X',\n'VAX', 'X',\n'VDX', 'X',\
\n'VDY', 'X',\n'VG1', 'X',\n'VIB', 'X',\n'VIR', 'X\
',\n'VIT', 'X',\n'VK3', 'X',\n'VO3', 'X',\n'VO4', \
'X',\n'VS1', 'F',\n'VS2', 'F',\n'VS3', 'F',\n'VS4'\
, 'F',\n'VXA', 'X',\n'W01', 'X',\n'W02', 'X',\n'W0\
3', 'X',\n'W11', 'X',\n'W33', 'X',\n'W35', 'X',\n'\
W42', 'X',\n'W43', 'X',\n'W54', 'X',\n'W56', 'X',\\
n'W59', 'X',\n'W71', 'X',\n'W84', 'X',\n'W8R', 'X'\
,\n'W91', 'X',\n'WAY', 'X',\n'WCC', 'X',\n'WO2', '\
X',\n'WO4', 'X',\n'WRB', 'X',\n'WRR', 'X',\n'WRS',\
 'X',\n'WW7', 'X',\n'X2F', 'X',\n'X7O', 'X',\n'XAA\
', 'X',\n'XAN', 'X',\n'XAO', 'X',\n'XBB', 'X',\n'X\
BP', 'X',\n'XDN', 'X',\n'XDP', 'X',\n'XIF', 'X',\n\
'XIM', 'X',\n'XK2', 'X',\n'XL1', 'X',\n'XLS', 'X',\
\n'XMP', 'X',\n'XN1', 'X',\n'XN2', 'X',\n'XN3', 'X\
',\n'XUL', 'X',\n'XV6', 'X',\n'XYD', 'X',\n'XYH', \
'X',\n'XYL', 'X',\n'XYP', 'X',\n'XYS', 'X',\n'YOF'\
, 'Y',\n'YRR', 'X',\n'YT3', 'X',\n'YZ9', 'X',\n'Z3\
4', 'G',\n'Z5A', 'X',\n'ZAF', 'X',\n'ZAP', 'X',\n'\
ZEB', 'X',\n'ZEN', 'X',\n'ZES', 'X',\n'ZID', 'X',\\
n'ZMR', 'X',\n'ZN3', 'X',\n'ZNH', 'X',\n'ZNO', 'X'\
,\n'ZO3', 'X',\n'ZPR', 'P',\n'ZRA', 'A',\n'ZST', '\
X',\n'ZYA', 'A',\n\n\n'ASN','N');\n} \n\n\nsub fil\
e2head\n      {\n	my $file = shift;\n	my $size = s\
hift;\n	my $f= new FileHandle;\n	my $line;\n	open \
($f,$file);\n	read ($f,$line, $size);\n	close ($f)\
;\n	return $line;\n      }\nsub file2tail\n      {\
\n	my $file = shift;\n	my $size = shift;\n	my $f= \
new FileHandle;\n	my $line;\n	\n	open ($f,$file);\\
n	seek ($f,$size*-1, 2);\n	read ($f,$line, $size);\
\n	close ($f);\n	return $line;\n      }\n\n\nsub v\
tmpnam\n      {\n	my $r=rand(100000);\n	my $f=\"fi\
le.$r.$$\";\n	while (-e $f)\n	  {\n	    $f=vtmpnam\
();\n	  }\n	push (@TMPFILE_LIST, $f);\n	return $f;\
\n      }\n\nsub myexit\n  {\n    my $code=@_[0];\\
n    if ($CLEAN_EXIT_STARTED==1){return;}\n    els\
e {$CLEAN_EXIT_STARTED=1;}\n    ### ONLY BARE EXIT\
\n    exit ($code);\n  }\nsub set_error_lock\n    \
{\n      my $name = shift;\n      my $pid=$$;\n\n \
     \n      &lock4tc ($$,\"LERROR\", \"LSET\", \"\
$$ -- ERROR: $name $PROGRAM\\n\");\n      return;\\
n    }\nsub set_lock\n  {\n    my $pid=shift;\n   \
 my $msg= shift;\n    my $p=getppid();\n    &lock4\
tc ($pid,\"LLOCK\",\"LRESET\",\"$p$msg\\n\");\n  }\
\nsub unset_lock\n   {\n     \n    my $pid=shift;\\
n    &lock4tc ($pid,\"LLOCK\",\"LRELEASE\",\"\");\\
n  }\nsub shift_lock\n  {\n    my $from=shift;\n  \
  my $to=shift;\n    my $from_type=shift;\n    my \
$to_type=shift;\n    my $action=shift;\n    my $ms\
g;\n    \n    if (!&lock4tc($from, $from_type, \"L\
CHECK\", \"\")){return 0;}\n    $msg=&lock4tc ($fr\
om, $from_type, \"LREAD\", \"\");\n    &lock4tc ($\
from, $from_type,\"LRELEASE\", $msg);\n    &lock4t\
c ($to, $to_type, $action, $msg);\n    return;\n  \
}\nsub isshellpid\n  {\n    my $p=shift;\n    if (\
!lock4tc ($p, \"LLOCK\", \"LCHECK\")){return 0;}\n\
    else\n      {\n	my $c=lock4tc($p, \"LLOCK\", \\
"LREAD\");\n	if ( $c=~/-SHELL-/){return 1;}\n     \
 }\n    return 0;\n  }\nsub isrootpid\n  {\n    if\
(lock4tc (getppid(), \"LLOCK\", \"LCHECK\")){retur\
n 0;}\n    else {return 1;}\n  }\nsub lock4tc\n	{\\
n	  my ($pid,$type,$action,$value)=@_;\n	  my $fna\
me;\n	  my $host=hostname;\n	  \n	  if ($type eq \\
"LLOCK\"){$fname=\"$LOCKDIR/.$pid.$host.lock4tcoff\
ee\";}\n	  elsif ( $type eq \"LERROR\"){ $fname=\"\
$LOCKDIR/.$pid.$host.error4tcoffee\";}\n	  elsif (\
 $type eq \"LWARNING\"){ $fname=\"$LOCKDIR/.$pid.$\
host.warning4tcoffee\";}\n	  \n	  if ($debug_lock)\
\n	    {\n	      print STDERR \"\\n\\t---lock4tc(t\
cg): $action => $fname =>$value (RD: $LOCKDIR)\\n\\
";\n	    }\n\n	  if    ($action eq \"LCHECK\") {re\
turn -e $fname;}\n	  elsif ($action eq \"LREAD\"){\
return file2string($fname);}\n	  elsif ($action eq\
 \"LSET\") {return string2file ($value, $fname, \"\
>>\");}\n	  elsif ($action eq \"LRESET\") {return \
string2file ($value, $fname, \">\");}\n	  elsif ($\
action eq \"LRELEASE\") \n	    {\n	      if ( $deb\
ug_lock)\n		{\n		  my $g=new FileHandle;\n		  open\
 ($g, \">>$fname\");\n		  print $g \"\\nDestroyed \
by $$\\n\";\n		  close ($g);\n		  safe_system (\"m\
v $fname $fname.old\");\n		}\n	      else\n		{\n		\
  unlink ($fname);\n		}\n	    }\n	  return \"\";\n\
	}\n	\nsub file2string\n	{\n	  my $file=@_[0];\n	 \
 my $f=new FileHandle;\n	  my $r;\n	  open ($f, \"\
$file\");\n	  while (<$f>){$r.=$_;}\n	  close ($f)\
;\n	  return $r;\n	}\nsub string2file \n    {\n   \
 my ($s,$file,$mode)=@_;\n    my $f=new FileHandle\
;\n    \n    open ($f, \"$mode$file\");\n    print\
 $f  \"$s\";\n    close ($f);\n  }\n\nBEGIN\n    {\
\n      srand;\n    \n      $SIG{'SIGUP'}='signal_\
cleanup';\n      $SIG{'SIGINT'}='signal_cleanup';\\
n      $SIG{'SIGQUIT'}='signal_cleanup';\n      $S\
IG{'SIGILL'}='signal_cleanup';\n      $SIG{'SIGTRA\
P'}='signal_cleanup';\n      $SIG{'SIGABRT'}='sign\
al_cleanup';\n      $SIG{'SIGEMT'}='signal_cleanup\
';\n      $SIG{'SIGFPE'}='signal_cleanup';\n      \
\n      $SIG{'SIGKILL'}='signal_cleanup';\n      $\
SIG{'SIGPIPE'}='signal_cleanup';\n      $SIG{'SIGS\
TOP'}='signal_cleanup';\n      $SIG{'SIGTTIN'}='si\
gnal_cleanup';\n      $SIG{'SIGXFSZ'}='signal_clea\
nup';\n      $SIG{'SIGINFO'}='signal_cleanup';\n  \
    \n      $SIG{'SIGBUS'}='signal_cleanup';\n    \
  $SIG{'SIGALRM'}='signal_cleanup';\n      $SIG{'S\
IGTSTP'}='signal_cleanup';\n      $SIG{'SIGTTOU'}=\
'signal_cleanup';\n      $SIG{'SIGVTALRM'}='signal\
_cleanup';\n      $SIG{'SIGUSR1'}='signal_cleanup'\
;\n\n\n      $SIG{'SIGSEGV'}='signal_cleanup';\n  \
    $SIG{'SIGTERM'}='signal_cleanup';\n      $SIG{\
'SIGCONT'}='signal_cleanup';\n      $SIG{'SIGIO'}=\
'signal_cleanup';\n      $SIG{'SIGPROF'}='signal_c\
leanup';\n      $SIG{'SIGUSR2'}='signal_cleanup';\\
n\n      $SIG{'SIGSYS'}='signal_cleanup';\n      $\
SIG{'SIGURG'}='signal_cleanup';\n      $SIG{'SIGCH\
LD'}='signal_cleanup';\n      $SIG{'SIGXCPU'}='sig\
nal_cleanup';\n      $SIG{'SIGWINCH'}='signal_clea\
nup';\n      \n      $SIG{'INT'}='signal_cleanup';\
\n      $SIG{'TERM'}='signal_cleanup';\n      $SIG\
{'KILL'}='signal_cleanup';\n      $SIG{'QUIT'}='si\
gnal_cleanup';\n      \n      our $debug_lock=$ENV\
{\"DEBUG_LOCK\"};\n      \n      \n      \n      \\
n      foreach my $a (@ARGV){$CL.=\" $a\";}\n     \
 if ( $debug_lock ){print STDERR \"\\n\\n\\n******\
**** START PG: $PROGRAM *************\\n\";}\n    \
  if ( $debug_lock ){print STDERR \"\\n\\n\\n*****\
*****(tcg) LOCKDIR: $LOCKDIR $$ *************\\n\"\
;}\n      if ( $debug_lock ){print STDERR \"\\n --\
- $$ -- $CL\\n\";}\n      \n	     \n      \n      \
\n    }\nsub flush_error\n  {\n    my $msg=shift;\\
n    return add_error ($EXIT_FAILURE,$$, $$,getppi\
d(), $msg, $CL);\n  }\nsub add_error \n  {\n    my\
 $code=shift;\n    my $rpid=shift;\n    my $pid=sh\
ift;\n    my $ppid=shift;\n    my $type=shift;\n  \
  my $com=shift;\n    \n    $ERROR_DONE=1;\n    lo\
ck4tc ($rpid, \"LERROR\",\"LSET\",\"$pid -- ERROR:\
 $type\\n\");\n    lock4tc ($$, \"LERROR\",\"LSET\\
", \"$pid -- COM: $com\\n\");\n    lock4tc ($$, \"\
LERROR\",\"LSET\", \"$pid -- STACK: $ppid -> $pid\\
\n\");\n   \n    return $code;\n  }\nsub add_warni\
ng \n  {\n    my $rpid=shift;\n    my $pid =shift;\
\n    my $command=shift;\n    my $msg=\"$$ -- WARN\
ING: $command\\n\";\n    print STDERR \"$msg\";\n \
   lock4tc ($$, \"LWARNING\", \"LSET\", $msg);\n  \
}\n\nsub signal_cleanup\n  {\n    print dtderr \"\\
\n**** $$ (tcg) was killed\\n\";\n    &cleanup;\n \
   exit ($EXIT_FAILURE);\n  }\nsub clean_dir\n  {\\
n    my $dir=@_[0];\n    if ( !-d $dir){return ;}\\
n    elsif (!($dir=~/tmp/)){return ;}#safety check\
 1\n    elsif (($dir=~/\\*/)){return ;}#safety che\
ck 2\n    else\n      {\n	`rm -rf $dir`;\n      }\\
n    return;\n  }\nsub cleanup\n  {\n    #print st\
derr \"\\n----tc: $$ Kills $PIDCHILD\\n\";\n    #k\
ill (SIGTERM,$PIDCHILD);\n    my $p=getppid();\n  \
  $CLEAN_EXIT_STARTED=1;\n    \n    \n    \n    if\
 (&lock4tc($$,\"LERROR\", \"LCHECK\", \"\"))\n    \
  {\n	my $ppid=getppid();\n	if (!$ERROR_DONE) \n	 \
 {\n	    &lock4tc($$,\"LERROR\", \"LSET\", \"$$ --\
 STACK: $p -> $$\\n\");\n	    &lock4tc($$,\"LERROR\
\", \"LSET\", \"$$ -- COM: $CL\\n\");\n	  }\n     \
 }\n    my $warning=&lock4tc($$, \"LWARNING\", \"L\
READ\", \"\");\n    my $error=&lock4tc($$,  \"LERR\
OR\", \"LREAD\", \"\");\n    #release error and wa\
rning lock if root\n    \n    if (isrootpid() && (\
$warning || $error) )\n      {\n	\n	print STDERR \\
"**************** Summary *************\\n$error\\\
n$warning\\n\";\n\n	&lock4tc($$,\"LERROR\",\"RELEA\
SE\",\"\");\n	&lock4tc($$,\"LWARNING\",\"RELEASE\"\
,\"\");\n      } \n    \n    \n    foreach my $f (\
@TMPFILE_LIST)\n      {\n	if (-e $f){unlink ($f);}\
 \n      }\n    foreach my $d (@TMPDIR_LIST)\n    \
  {\n	clean_dir ($d);\n      }\n    #No More Lock \
Release\n    #&lock4tc($$,\"LLOCK\",\"LRELEASE\",\\
"\"); #release lock \n\n    if ( $debug_lock ){pri\
nt STDERR \"\\n\\n\\n********** END PG: $PROGRAM (\
$$) *************\\n\";}\n    if ( $debug_lock ){p\
rint STDERR \"\\n\\n\\n**********(tcg) LOCKDIR: $L\
OCKDIR $$ *************\\n\";}\n  }\nEND \n  {\n  \
  \n    &cleanup();\n  }\n   \n\nsub safe_system \\
n{\n  my $com=shift;\n  my $ntry=shift;\n  my $ctr\
y=shift;\n  my $pid;\n  my $status;\n  my $ppid=ge\
tppid();\n  if ($com eq \"\"){return 1;}\n  \n  \n\
\n  if (($pid = fork ()) < 0){return (-1);}\n  if \
($pid == 0)\n    {\n      set_lock($$, \" -SHELL- \
$com (tcg)\");\n      exec ($com);\n    }\n  else\\
n    {\n      lock4tc ($$, \"LLOCK\", \"LSET\", \"\
$pid\\n\");#update parent\n      $PIDCHILD=$pid;\n\
    }\n  if ($debug_lock){printf STDERR \"\\n\\t .\
... safe_system (fasta_seq2hmm)  p: $$ c: $pid COM\
: $com\\n\";}\n\n  waitpid ($pid,WTERMSIG);\n\n  s\
hift_lock ($pid,$$, \"LWARNING\",\"LWARNING\", \"L\
SET\");\n\n  if ($? == $EXIT_FAILURE || lock4tc($p\
id, \"LERROR\", \"LCHECK\", \"\"))\n    {\n      i\
f ($ntry && $ctry <$ntry)\n	{\n	  add_warning ($$,\
$$,\"$com failed [retry: $ctry]\");\n	  lock4tc ($\
pid, \"LRELEASE\", \"LERROR\", \"\");\n	  return s\
afe_system ($com, $ntry, ++$ctry);\n	}\n      elsi\
f ($ntry == -1)\n	{\n	  if (!shift_lock ($pid, $$,\
 \"LERROR\", \"LWARNING\", \"LSET\"))\n	    {\n	  \
    add_warning ($$,$$,\"$com failed\");\n	    }\n\
	  else\n	    {\n	      lock4tc ($pid, \"LRELEASE\\
", \"LERROR\", \"\");\n	    }\n	  return $?;}\n   \
   else\n	{\n	  if (!shift_lock ($pid,$$, \"LERROR\
\",\"LERROR\", \"LSET\"))\n	    {\n	      myexit(a\
dd_error ($EXIT_FAILURE,$$,$pid,getppid(), \"UNSPE\
CIFIED system\", $com));\n	    }\n	}\n    }\n  ret\
urn $?;\n}\n\nsub check_configuration \n    {\n   \
   my @l=@_;\n      my $v;\n      foreach my $p (@\
l)\n	{\n	  \n	  if   ( $p eq \"EMAIL\")\n	    { \n\
	      if ( !($EMAIL=~/@/))\n		{\n		add_warning($$\
,$$,\"Could Not Use EMAIL\");\n		myexit(add_error \
($EXIT_FAILURE,$$,$$,getppid(),\"EMAIL\",\"$CL\"))\
;\n	      }\n	    }\n	  elsif( $p eq \"INTERNET\")\
\n	    {\n	      if ( !&check_internet_connection(\
))\n		{\n		  myexit(add_error ($EXIT_FAILURE,$$,$$\
,getppid(),\"INTERNET\",\"$CL\"));\n		}\n	    }\n	\
  elsif( $p eq \"wget\")\n	    {\n	      if (!&pg_\
is_installed (\"wget\") && !&pg_is_installed (\"cu\
rl\"))\n		{\n		  myexit(add_error ($EXIT_FAILURE,$\
$,$$,getppid(),\"PG_NOT_INSTALLED:wget\",\"$CL\"))\
;\n		}\n	    }\n	  elsif( !(&pg_is_installed ($p))\
)\n	    {\n	      myexit(add_error ($EXIT_FAILURE,\
$$,$$,getppid(),\"PG_NOT_INSTALLED:$p\",\"$CL\"));\
\n	    }\n	}\n      return 1;\n    }\nsub pg_is_in\
stalled\n  {\n    my @ml=@_;\n    my $r, $p, $m;\n\
    my $supported=0;\n    \n    my $p=shift (@ml);\
\n    if ($p=~/::/)\n      {\n	if (safe_system (\"\
perl -M$p -e 1\")==$EXIT_SUCCESS){return 1;}\n	els\
e {return 0;}\n      }\n    else\n      {\n	$r=`wh\
ich $p 2>/dev/null`;\n	if ($r eq \"\"){return 0;}\\
n	else {return 1;}\n      }\n  }\n\n\n\nsub check_\
internet_connection\n  {\n    my $internet;\n    m\
y $tmp;\n    &check_configuration ( \"wget\"); \n \
   \n    $tmp=&vtmpnam ();\n    \n    if     (&pg_\
is_installed    (\"wget\")){`wget www.google.com -\
O$tmp >/dev/null 2>/dev/null`;}\n    elsif  (&pg_i\
s_installed    (\"curl\")){`curl www.google.com -o\
$tmp >/dev/null 2>/dev/null`;}\n    \n    if ( !-e\
 $tmp || -s $tmp < 10){$internet=0;}\n    else {$i\
nternet=1;}\n    if (-e $tmp){unlink $tmp;}\n\n   \
 return $internet;\n  }\nsub check_pg_is_installed\
\n  {\n    my @ml=@_;\n    my $r=&pg_is_installed \
(@ml);\n    if (!$r && $p=~/::/)\n      {\n	print \
STDERR \"\\nYou Must Install the perl package $p o\
n your system.\\nRUN:\\n\\tsudo perl -MCPAN -e 'in\
stall $pg'\\n\";\n      }\n    elsif (!$r)\n      \
{\n	myexit(flush_error(\"\\nProgram $p Supported b\
ut Not Installed on your system\"));\n      }\n   \
 else\n      {\n	return 1;\n      }\n  }\n\n\n","u\
se Cwd;\nuse Env;\nuse File::Path;\nuse FileHandle\
;\nuse strict;\n\n\nour (%MODE, %PG, %ENV_SET, %SU\
PPORTED_OS);\n\n\nour $EXIT_SUCCESS=0;\nour $EXIT_\
FAILURE=1;\nour $INTERNET=0;\n\nour $CP=\"cp \"; #\
was causing a crash on MacOSX\nour $SILENT=\">/dev\
/null 2>/dev/null\";\nour $WEB_BASE=\"http://www.t\
coffee.org\";\nour $TCLINKDB_ADDRESS=\"$WEB_BASE/R\
esources/tclinkdb.txt\";\nour $OS=get_os();\nour $\
ROOT=&get_root();\nour $CD=cwd();\nour $CDIR=$CD;\\
nour $HOME=$ENV{'HOME'};\n\nour $OSNAME=$ENV{'OSNA\
ME'};\nour $OSARCH=$ENV{'OSARCH'};\nour $REPO_ROOT\
=\"\";\n\nour $TCDIR;\nour $TCCACHE;\nour $TCTMP;\\
nour $TCM;\nour $TCMETHODS;\nour $TCPLUGINS;\nour \
$PLUGINS_DIR=\"\";\nour $INSTALL_DIR=\"\";\n\nour \
$CXX=\"g++\";\nour $CXXFLAGS=\"\";\n\nour $CPP=\"g\
++\";\nour $CPPFLAGS=\"\";\n\nour $CC=\"gcc\";\nou\
r $CFLAGS=\"\";\n\nour $FC=\"f77\";\nour $FFLAGS=\\
"\";\n\nmy $install=\"all\";\nmy $default_update_a\
ction=\"no_update\";\nmy @required_applications=(\\
"wget_OR_curl\");\nmy @smode=(\"all\", \"clean\", \
\"install\");\n\n&initialize_PG();\n\nmy $cl=join(\
 \" \", @ARGV);\nif ($#ARGV==-1 || ($cl=~/-h/) ||(\
$cl=~/-H/) )\n  {\n     print \"\\n!!!!!!! ./insta\
ll  t_coffee             --> installs t_coffee onl\
y\";\n     print \"\\n!!!!!!! ./install  all      \
            --> installs all the modes [mcoffee, e\
xpresso, psicoffee,rcoffee..]\";\n     print \"\\n\
!!!!!!! ./install  [mcoffee|rcoffee|..] --> instal\
ls the specified mode\";\n     print \"\\n!!!!!!! \
./install  -h                   --> print usage\\n\
\\n\";\n     if ( $#ARGV==-1){exit ($EXIT_FAILURE)\
;}\n   }\n     \nif (($cl=~/-h/) ||($cl=~/-H/) )\n\
  {\n    my $m;\n    print \"\\n\\n!!!!!!! advance\
d mode\\n\";\n    foreach $m ((keys (%MODE)),@smod\
e)\n      {\n	print \"!!!!!!!       ./install $m\\\
n\";\n      }\n    \n    print \"!!!!!!! ./install\
 [target:package|mode|] [-update|-force|-exec=dir|\
-dis=dir|-root|-tclinkdb=file|-] [CC=|FCC=|CXX=|CF\
LAGS=|CXXFLAGS=]\\n\";\n    print \"!!!!!!! ./inst\
all clean    [removes all executables]\\n\";\n    \
print \"!!!!!!! ./install [optional:target] -updat\
e               [updates package already installed\
]\\n\";\n    print \"!!!!!!! ./install [optional:t\
arget] -force                [Forces recompilation\
 over everything]\\n\";\n    \n    print \"!!!!!!!\
 ./install [optional:target] -root                \
 [You are running as root]\\n\";\n    print \"!!!!\
!!! ./install [optional:target] -exec=/foo/bar/   \
    [address for the T-Coffee executable]\\n\";\n \
   print \"!!!!!!! ./install [optional:target] -di\
s=/foo/bar/        [Address where distributions sh\
ould be stored]\\n\";\n    print \"!!!!!!! ./insta\
ll [optional:target] -tclinkdb=foo|update  [file c\
ontaining all the packages to be installed]\\n\";\\
n    print \"!!!!!!! ./install [optional:target] -\
clean                [clean everything]\\n\";\n   \
 print \"!!!!!!! ./install [optional:target] -plug\
ins              [plugins directory]\\n\";\n    pr\
int \"!!!!!!! ./install [optional:target] -tcdir=/\
foor/bar      [base path where T-Coffee will be in\
stalled]\\n\";\n    print \"!!!!!!! ./install [opt\
ional:target] -repo=/path/to/repo   [binaries repo\
sitory root directory]\\n\";\n    print \"!!!!!!! \
mode:\";\n    foreach $m (keys(%MODE)){print \"$m \
\";}\n    print \"\\n\";\n    print \"!!!!!!! Pack\
ages:\";\n    foreach $m (keys (%PG)){print \"$m \\
";}\n    print \"\\n\";\n    \n    print \"\\n\\n\\
";\n    exit ($EXIT_FAILURE);\n  }\n\n\n\nmy (@arg\
l)=($cl=~/(\\S+=[^=]+)\\s\\w+=/g);\npush (@argl, (\
$cl=~/(\\S+=[^=]+\\S)\\s*$/g));\n\nforeach $a (@ar\
gl)\n  {\n    if ( ($cl=~/CXX=(.*)/)){$CXX=$1;}\n \
   if ( ($cl=~/-CC=(.*)/    )){$CC=$1;}\n    if ( \
($cl=~/-FC=(.*)/    )){$FC=$1;}\n    if ( ($cl=~/-\
CFLAGS=(.*)/)){$CFLAGS=$1;}\n    if ( ($cl=~/-CXXF\
LAGS=(.*)/)){$CXXFLAGS=$1;}\n  }\nour ($ROOT_INSTA\
LL, $NO_QUESTION, $default_update_action,$BINARIES\
_ONLY,$force, $default_update_action, $INSTALL_DIR\
, $PLUGINS_DIR, $DISTRIBUTIONS,$tclinkdb, $proxy, \
$clean);\nif ( ($cl=~/-root/)){$ROOT_INSTALL=1;}\n\
if ( ($cl=~/-no_question/)){$NO_QUESTION=1;}\nif (\
 ($cl=~/-update/)){$default_update_action=\"update\
\";}\nif ( ($cl=~/-binaries/)){$BINARIES_ONLY=1;}\\
nif ( ($cl=~/-force/)){$force=1;$default_update_ac\
tion=\"update\"}\nif ( ($cl=~/-exec=\\s*(\\S+)/)){\
$INSTALL_DIR=$1;}\nif ( ($cl=~/-plugins=\\s*(\\S+)\
/)){$PLUGINS_DIR=$1;}\nif ( ($cl=~/-dis=\\s*(\\S+)\
/)){$DISTRIBUTIONS=$1;}\n\nif ( ($cl=~/-tclinkdb=\\
\s*(\\S+)/)){$tclinkdb=$1;}\nif ( ($cl=~/-proxy=\\\
s*(\\S+)/)){$proxy=$1;}\nif ( ($cl=~/-clean/)){$cl\
ean=1;}\nif ( ($cl=~/-repo=\\s*(\\S+)/)){ $REPO_RO\
OT=$1; }\nif ( ($cl=~/-tcdir=\\s*(\\S+)/)){ $TCDIR\
=$1; }\nif ($tclinkdb){&update_tclinkdb ($tclinkdb\
);}\n\n\nif( $REPO_ROOT ne \"\" ) {\n	if( $OSNAME \
eq \"\" ) { print \"You have specified the reposit\
ory folder but the required \\\"OSNAME\\\" envirom\
ent variable is missing. \\n\"; exit 1; } \n	if( $\
OSARCH eq \"\" ) { print \"You have specified the \
repository folder but the required \\\"OSARCH\\\" \
enviroment variable is missing. \\n\"; exit 1; } \\
n}\n\n\nif(!$TCDIR) { $TCDIR=\"$HOME/.t_coffee\"; \
}\n&add_dir ($TCDIR);\n&add_dir ($TCCACHE=\"$TCDIR\
/cache\");\n&add_dir ($TCTMP=\"$CDIR/tmp\");\n&add\
_dir ($TCM=\"$TCDIR/mcoffee\");\n&add_dir ($TCMETH\
ODS=\"$TCDIR/methods\");\n&add_dir ($TCPLUGINS=\"$\
TCDIR/plugins/$OS\");\n\n\nour $BASE=\"$CD/bin\";\\
nour $BIN=\"$BASE/binaries/$OS\";\nour $DOWNLOAD_D\
IR=\"$BASE/download\";\nour $DOWNLOAD_FILE=\"$DOWN\
LOAD_DIR/files\";\nour $TMP=\"$BASE/tmp\";\n\n&add\
_dir($BASE);\n&add_dir($BIN);\n&add_dir($DOWNLOAD_\
DIR);\n&add_dir($DOWNLOAD_FILE);\nif (!$DISTRIBUTI\
ONS){$DISTRIBUTIONS=\"$DOWNLOAD_DIR/distributions\\
";}\n&add_dir ($DISTRIBUTIONS);\n&add_dir ($TMP);\\
n\n\nif    (!$PLUGINS_DIR && !$ROOT_INSTALL){$PLUG\
INS_DIR=$TCPLUGINS;}\nelsif (!$PLUGINS_DIR &&  $RO\
OT_INSTALL){$PLUGINS_DIR=\"/usr/local/bin/\";}\n\n\
if    (!$INSTALL_DIR && !$ROOT_INSTALL){$INSTALL_D\
IR=\"$HOME/bin/\";mkpath ($INSTALL_DIR);}\nelsif (\
!$INSTALL_DIR &&  $ROOT_INSTALL){$INSTALL_DIR=\"/u\
sr/local/bin/\";}\n\nif (-d \"mcoffee\"){`cp mcoff\
ee/* $TCM`;}\n\n\nour $ENV_FILE=\"$TCDIR/t_coffee_\
env\";\n&env_file2putenv ($ENV_FILE);\n&set_proxy(\
$proxy);\nmy ($target, $p, $r);\n$target=$p;\n\nfo\
reach $p (  ((keys (%PG)),(keys(%MODE)),(@smode)) \
)\n  {\n    if ($ARGV[0] eq $p && $target eq \"\")\
{$target=$p;}\n  }\nif ($target eq \"\"){exit ($EX\
IT_FAILURE);}\n\n\nforeach $r (@required_applicati\
ons)\n  {\n    my @app_list;\n    my $i;\n    $i=0\
;\n    \n    @app_list=split (/_OR_/, $r);\n    fo\
reach my $pg (@app_list)\n      {\n	$i+=&pg_is_ins\
talled ($pg);\n      }\n    if ($i==0)\n      {\n \
     print \"One of the following packages must be\
 installed to proceed: \";\n      foreach my $pg (\
@app_list)\n	{\n	  print (\"$pg \");\n	}\n      di\
e;\n    }\n  }\n\n\n\n\n\n\n&sign_license_ni();\n\\
n\n$PG{C}{compiler}=get_C_compiler($CC);\n$PG{Fort\
ran}{compiler}=get_F_compiler($FC);\n$PG{CXX}{comp\
iler}=$PG{CPP}{compiler}=$PG{GPP}{compiler}=get_CX\
X_compiler($CXX);\nif ($CXXFLAGS){$PG{CPP}{options\
}=$PG{GPP}{options}=$PG{CXX}{options}=$CXXFLAGS;}\\
nif ($CFLAGS){$PG{C}{options}=$CFLAGS;}\nforeach m\
y $c (keys(%PG))\n  {\n    my $arguments;\n    if \
($PG{$c}{compiler})\n      {\n	$arguments=\"$PG{$c\
}{compiler_flag}=$PG{$c}{compiler} \";\n	if ($PG{$\
c}{options})\n	  {\n	    $arguments.=\"$PG{$c}{opt\
ions_flag}=$PG{$c}{options} \";\n	  }\n	$PG{$c}{ar\
guments}=$arguments;\n      }\n  }\n\nif ($PG{$tar\
get}){$PG{$target}{install}=1;}\nelse\n  {\n    fo\
reach my $pg (keys(%PG))\n      {\n	if ( $target e\
q \"all\" || ($PG{$pg}{mode}=~/$target/))\n	  {\n	\
    $PG{$pg} {install}=1;\n	  }\n      }\n  }\n\nf\
oreach my $pg (keys(%PG))\n  {\n    if (!$PG{$pg}{\
update_action}){$PG{$pg}{update_action}=$default_u\
pdate_action;}\n    elsif ($PG{$pg}{update_action}\
 eq \"never\"){$PG{$pg}{install}=0;}\n    if ( $fo\
rce && $PG{$pg}{install})\n      {\n	`rm $BIN/$pg \
$BIN/$pg.exe $SILENT`;\n      }\n    if ($PG{$pg}{\
update_action} eq \"update\" && $PG{$pg}{install})\
{$PG{$pg}{update}=1;}\n  }\n\nif (($target=~/clean\
/))\n  {\n    print \"------- cleaning executables\
 -----\\n\";\n    `rm bin/* $SILENT`;\n    exit ($\
EXIT_SUCCESS);\n  }\n\nif ( !$PG{$target}){print \\
"------- Installing T-Coffee Modes\\n\";}\n\nforea\
ch my $m (keys(%MODE))\n  {\n    if ( $target eq \\
"all\" || $target eq $m)\n      {\n	print \"\\n---\
---- The installer will now install the $m compone\
nts $MODE{$m}{description}\\n\";\n	foreach my $pg \
(keys(%PG))\n	  {\n	    if ( $PG{$pg}{mode} =~/$m/\
 && $PG{$pg}{install})\n	      {\n		if ($PG{$pg}{t\
ouched}){print \"------- $PG{$pg}{dname}: already \
processed\\n\";}\n		else {$PG{$pg}{success}=&insta\
ll_pg($pg);$PG{$pg}{touched}=1;}\n	      }\n	  }\n\
      }\n  }\n\nif ( $PG{$target}){print \"-------\
 Installing Individual Package\\n\";}\nforeach my \
$pg (keys (%PG))\n  {\n    \n    if ( $PG{$pg}{ins\
tall} && !$PG{$pg}{touched})\n      {\n	print \"\\\
n------- Install $pg\\n\";\n	$PG{$pg}{success}=&in\
stall_pg($pg);$PG{$pg}{touched}=1;\n      }\n  }\n\
print \"------- Finishing The installation\\n\";\n\
my $final_report=&install ($INSTALL_DIR);\n\nprint\
 \"\\n\";\nprint \"*******************************\
**************************************\\n\";\nprin\
t \"********              INSTALLATION SUMMARY    \
      *****************\\n\";\nprint \"***********\
**************************************************\
********\\n\";\nprint \"------- SUMMARY package In\
stallation:\\n\";\nprint \"-------   Executable In\
stalled in: $PLUGINS_DIR\\n\";\n\nforeach my $pg (\
keys(%PG))\n  {\n    if ( $PG{$pg}{install})\n    \
  {\n	my $bin_status=($PG{$pg}{from_binary} && $PG\
{$pg}{success})?\"[from binary]\":\"\";\n	if     (\
 $PG{$pg}{new} && !$PG{$pg}{old})                 \
    {print \"*------        $PG{$pg}{dname}: insta\
lled $bin_status\\n\"; $PG{$pg}{status}=1;}\n	elsi\
f  ( $PG{$pg}{new} &&  $PG{$pg}{old})             \
        {print \"*------        $PG{$pg}{dname}: u\
pdated $bin_status\\n\"  ; $PG{$pg}{status}=1;} \n\
	elsif  (!$PG{$pg}{new} &&  $PG{$pg}{old} && !$PG{\
$pg}{update}){print \"*------        $PG{$pg}{dnam\
e}: previous\\n\" ; $PG{$pg}{status}=1;}\n	elsif  \
(!$PG{$pg}{new} &&  $PG{$pg}{old} &&  $PG{$pg}{upd\
ate}){print \"*------        $PG{$pg}{dname}: fail\
ed update (previous installation available)\\n\";$\
PG{$pg}{status}=0;}\n	else                        \
                                  {print \"*------\
        $PG{$pg}{dname}: failed installation\\n\";\
$PG{$pg}{status}=0;}\n      }\n  }\nmy $failure;\n\
\nif ( !$PG{$target}){print \"*------ SUMMARY mode\
 Installation:\\n\";}\nforeach my $m (keys(%MODE))\
\n  {\n  \n    if ( $target eq \"all\" || $target \
eq $m)\n      {\n	my $succesful=1;\n	foreach my $p\
g (keys(%PG))\n	  {\n	    if (($PG{$pg}{mode}=~/$m\
/) && $PG{$pg}{install} && $PG{$pg}{status}==0)\n	\
      {\n		$succesful=0;\n		print \"*!!!!!!       \
$PG{$pg}{dname}: Missing\\n\";\n	      }\n	  }\n	i\
f ( $succesful)\n	  {\n	    $MODE{$m}{status}=1;\n\
	    print \"*------       MODE $MODE{$m}{dname} S\
UCCESSFULLY installed\\n\";\n	  }\n	else\n	  {\n	 \
   $failure++;\n	    $MODE{$m}{status}=0;\n	    pr\
int \"*!!!!!!       MODE $MODE{$m}{dname} UNSUCCES\
SFULLY installed\\n\";\n	  }\n      }\n  }\n\n    \
\n      \nif ($clean==1 && ($BASE=~/install4tcoffe\
e/) ){print \"*------ Clean Installation Directory\
: $BASE\\n\";`rm -rf $BASE`;}\nforeach my $pg (key\
s(%PG)){if ($PG{$pg}{install} && $PG{$pg}{status}=\
=0){exit ($EXIT_FAILURE);}}\n\nif ($failure)\n  {\\
n    print \"*************************************\
********************************\\n\";\n    print \
\"********     SOME PACKAGES FAILED TO INSTALL    \
    *****************\\n\";\n    print \"*********\
**************************************************\
**********\\n\";\n    print \"\\nSome of the repor\
ted failures may be due to connectivity problems\"\
;\n    print \"\\nRerun the installation and the i\
nstaller will specifically try to install the miss\
ing packages\";\n    print \"\\nIf this Fails, go \
to the original website and install the package ma\
nually\";\n  }\n\nprint \"************************\
*********************************************\\n\"\
;\nprint \"********              FINALIZE YOUR INS\
TALLATION    *****************\\n\";\nprint \"****\
**************************************************\
***************\\n\";\nprint \"------- Your execut\
ables are in:\\n\"; \nprint \"-------       $PLUGI\
NS_DIR:\\n\";\nprint \"------- Add this directory \
to your path with the following command:\\n\";\npr\
int \"-------       export PATH=$PLUGINS_DIR:\\$PA\
TH\\n\";\nprint \"------- Make this permanent by a\
dding this line to the file:\\n\";\nprint \"------\
-       $HOME/.bashrc\\n\";\nexit ($EXIT_SUCCESS);\
  \n  \nsub get_CXX_compiler\n  {\n    my $c=@_[0]\
;\n    my (@clist)=(\"g++\");\n    \n    return ge\
t_compil ($c, @clist);\n }\nsub get_C_compiler\n  \
{\n    my $c=@_[0];\n    my (@clist)=(\"gcc\", \"c\
c\", \"icc\");\n    \n    return get_compil ($c, @\
clist);\n }\n\nsub get_F_compiler\n  {\n    my ($c\
)=@_[0];\n    my @clist=(\"f77\", \"g77\",\"g95\",\
 \"gfortran\", \"ifort\");\n    return get_compil \
($c, @clist);\n  } \n       \nsub get_compil\n  {\\
n    my ($fav,@clist)=(@_);\n    \n    #return the\
 first compiler found installed in the system. Che\
ck first the favorite\n    foreach my $c ($fav,@cl\
ist)\n      {\n	if  (&pg_is_installed ($c)){return\
 $c;}\n      }\n    return \"\";\n  }\nsub exit_if\
_pg_not_installed\n  {\n    my (@arg)=(@_);\n    \\
n    foreach my $p (@arg)\n      {\n	if ( !&pg_is_\
installed ($p))\n	  {\n	    print \"!!!!!!!! The $\
p utility must be installed for this installation \
to proceed [FATAL]\\n\";\n	    die;\n	  }\n      }\
\n    return 1;\n  }\nsub set_proxy\n  {\n    my (\
$proxy)=(@_);\n    my (@list,$p);\n    \n    @list\
= (\"HTTP_proxy\", \"http_proxy\", \"HTTP_PROXY\",\
 \"ALL_proxy\", \"all_proxy\",\"HTTP_proxy_4_TCOFF\
EE\",\"http_proxy_4_TCOFFEE\");\n    \n    if (!$p\
roxy)\n      {\n	foreach my $p (@list)\n	  {\n	   \
 if ( ($ENV_SET{$p}) || $ENV{$p}){$proxy=$ENV{$p};\
}\n	  }\n      }\n    foreach my $p(@list){$ENV{$p\
}=$proxy;}\n  }\n	\nsub check_internet_connection\\
n  {\n    my $internet;\n    \n    if ( -e \"x\"){\
unlink (\"x\");}\n    if     (&pg_is_installed    \
(\"wget\")){`wget www.google.com -Ox >/dev/null 2>\
/dev/null`;}\n    elsif  (&pg_is_installed    (\"c\
url\")){`curl www.google.com -ox >/dev/null 2>/dev\
/null`;}\n    else\n      {\n	printf stderr \"\\nE\
RROR: No pg for remote file fetching [wget or curl\
][FATAL]\\n\";\n	exit ($EXIT_FAILURE);\n      }\n \
   \n    if ( !-e \"x\" || -s \"x\" < 10){$interne\
t=0;}\n    else {$internet=1;}\n    if (-e \"x\"){\
unlink \"x\";}\n    return $internet;\n  }\nsub ur\
l2file\n  {\n    my ($cmd, $file,$wget_arg, $curl_\
arg)=(@_);\n    my ($exit,$flag, $pg, $arg);\n    \
\n    if ($INTERNET || check_internet_connection (\
)){$INTERNET=1;}\n    else\n      {\n	print STDERR\
 \"ERROR: No Internet Connection [FATAL:install.pl\
]\\n\";\n	exit ($EXIT_FAILURE);\n      }\n    \n  \
  if     (&pg_is_installed    (\"wget\")){$pg=\"wg\
et\"; $flag=\"-O\";$arg=\"--tries=2 --connect-time\
out=10 $wget_arg\";}\n    elsif  (&pg_is_installed\
    (\"curl\")){$pg=\"curl\"; $flag=\"-o\";$arg=$c\
url_arg;}\n    else\n      {\n	printf stderr \"\\n\
ERROR: No pg for remote file fetching [wget or cur\
l][FATAL]\\n\";\n	exit ($EXIT_FAILURE);\n      }\n\
    \n    \n    if (-e $file){unlink($file);}\n   \
 $exit=system \"$pg $cmd $flag$file $arg\";\n    r\
eturn $exit;\n  }\n\nsub pg_is_installed\n  {\n   \
 my ($p, $dir)=(@_);\n    my ($r,$m, $ret);\n    m\
y ($supported, $language, $compil);\n    \n  \n   \
 if ( $PG{$p})\n      {\n	$language=$PG{$p}{langua\
ge2};\n	$compil=$PG{$language}{compiler};\n      }\
\n    \n    if ( $compil eq \"CPAN\")\n      {\n	i\
f ( system (\"perl -M$p -e 1\")==$EXIT_SUCCESS){$r\
et=1;}\n	else {$ret=0;}\n      }\n    elsif ($dir)\
\n      {\n	if (-e \"$dir/$p\" || -e \"$dir/$p\\.e\
xe\"){$ret=1;}\n	else {$ret=0;}\n      }\n    elsi\
f (-e \"$PLUGINS_DIR/$p\" || -e \"$PLUGINS_DIR/$p.\
exe\"){$ret=1;}\n    else\n      {\n	$r=`which $p \
2>/dev/null`;\n	if ($r eq \"\"){$ret=0;}\n	else {$\
ret=1;}\n      }\n   \n    return $ret;\n  }\nsub \
install\n  {\n    my ($new_bin)=(@_);\n    my ($co\
pied, $report);\n\n    \n    if (!$ROOT_INSTALL)\n\
      {\n	\n	if (-e \"$BIN/t_coffee\"){`$CP $BIN/t\
_coffee $INSTALL_DIR`};\n	`cp $BIN/* $PLUGINS_DIR`\
;\n	$copied=1;\n      }\n    else\n      {\n	$copi\
ed=&root_run (\"You must be root to finalize the i\
nstallation\", \"$CP $BIN/* $INSTALL_DIR $SILENT\"\
);\n      }\n    \n     \n  if ( !$copied)\n    {\\
n      $report=\"*!!!!!! Installation unsuccesful.\
 The executables have been left in $BASE/bin\\n\";\
\n    }\n  elsif ( $copied && $ROOT)\n    {\n     \
 $report=\"*------ Installation succesful. Your ex\
ecutables have been copied in $new_bin and are on \
your PATH\\n\";\n    }\n  elsif ( $copied && !$ROO\
T)\n    {\n      $report= \"*!!!!!! T-Coffee and a\
ssociated packages have been copied in: $new_bin\\\
n\";\n      $report.=\"*!!!!!! This address is NOT\
 in your PATH sytem variable\\n\";\n      $report.\
=\"*!!!!!! You can do so by adding the following l\
ine in your ~/.bashrc file:\\n\";\n      $report.=\
\"*!!!!!! export PATH=$new_bin:\\$PATH\\n\";\n    \
}\n  return $report;\n}\n\nsub sign_license_ni\n  \
{\n    my $F=new FileHandle;\n    open ($F, \"lice\
nse.txt\");\n    while (<$F>)\n      {\n	print \"$\
_\";\n      }\n    close ($F);\n    \n    return;\\
n  }\n\nsub install_pg\n  {\n    my ($pg)=(@_);\n \
   my ($report, $previous, $language, $compiler, $\
return);\n    \n    if (!$PG{$pg}{install}){return\
 1;}\n    \n    $previous=&pg_is_installed ($pg);\\
n    \n    if ($PG{$pg}{update_action} eq \"no_upd\
ate\" && $previous)\n      {\n	$PG{$pg}{old}=1;\n	\
$PG{$pg}{new}=0;\n	$return=1;\n      }\n    else\n\
      {\n	$PG{$pg}{old}=$previous;\n	\n	if ($PG{$p\
g} {language2} eq \"Perl\"){&install_perl_package \
($pg);}\n	elsif ($BINARIES_ONLY && &install_binary\
_package ($pg)){$PG{$pg}{from_binary}=1;}\n	elsif \
(&install_source_package ($pg)){;}\n	else \n	  {\n\
	    \n	    if (!&supported_os($OS))\n	      {\n		\
print \"!!!!!!!! $pg compilation failed, binary un\
supported for $OS\\n\"; \n	      }\n	    elsif (!(\
$PG{$pg}{from_binary}=&install_binary_package ($pg\
)))\n	      {\n		print \"!!!!!!!! $pg compilation \
and  binary installation failed\\n\";\n	      }\n	\
  }\n	$PG{$pg}{new}=$return=&pg_is_installed ($pg,\
$BIN);\n      }\n\n    \n    return $return;\n  }\\
nsub install_perl_package\n  {\n    my ($pg)=(@_);\
\n    my ($report, $language, $compiler);\n    \n \
   $language=$PG{$pg} {language2};\n    $compiler=\
$PG{$language}{compiler};\n    \n    if (!&pg_is_i\
nstalled ($pg))\n      {\n	if ( $OS eq \"windows\"\
){`perl -M$compiler -e 'install $pg'`;}\n	elsif ( \
$ROOT eq \"sudo\"){system (\"sudo perl -M$compiler\
 -e 'install $pg'\");}\n	else {system (\"su root -\
c perl -M$compiler -e 'install $pg'\");}\n      }\\
n    return &pg_is_installed ($pg);\n  }\n\n\n\nsu\
b install_source_package\n  {\n    my ($pg)=(@_);\\
n    my ($report, $download, $arguments, $language\
, $address, $name, $ext, $main_dir, $distrib);\n  \
  my $wget_tmp=\"$TMP/wget.tmp\";\n    my (@fl);\n\
    if ( -e \"$BIN/$pg\" || -e \"$BIN/$pg.exe\"){r\
eturn 1;}\n    \n    #\n    # check if the module \
exists in the repository cache \n    #\n	if( repo_\
load($pg) ) {\n		return 1;\n	}\n    \n    if ($pg \
eq \"t_coffee\")  {return   &install_t_coffee ($pg\
);}\n    elsif ($pg eq \"TMalign\"){return   &inst\
all_TMalign ($pg);}\n    \n    chdir $DISTRIBUTION\
S;\n    \n    $download=$PG{$pg}{source};\n    \n \
   if (($download =~/tgz/))\n      {\n	($address,$\
name,$ext)=($download=~/(.+\\/)([^\\/]+)(\\.tgz).*\
/);\n      }\n    elsif (($download=~/tar\\.gz/))\\
n      {\n	($address,$name,$ext)=($download=~/(.+\\
\/)([^\\/]+)(\\.tar\\.gz).*/);\n      }\n    elsif\
 (($download=~/tar/))\n      {\n	($address,$name,$\
ext)=($download=~/(.+\\/)([^\\/]+)(\\.tar).*/);\n \
     }\n    else\n      {\n	($address,$name)=($dow\
nload=~/(.+\\/)([^\\/]+)/);\n	$ext=\"\";\n      }\\
n    $distrib=\"$name$ext\";\n    \n    if ( !-d $\
pg){mkdir $pg;}\n    chdir $pg;\n   \n    #get the\
 distribution if available\n    if ( -e \"$DOWNLOA\
D_DIR/$distrib\")\n      {\n	`$CP $DOWNLOAD_DIR/$d\
istrib .`;\n      }\n    #UNTAR and Prepare everyt\
hing\n    if (!-e \"$name.tar\" && !-e \"$name\")\\
n      {\n	&check_rm ($wget_tmp);\n	print \"\\n---\
---- Downloading/Installing $pg\\n\";\n	\n	if (!-e\
 $distrib && &url2file (\"$download\", \"$wget_tmp\
\")==$EXIT_SUCCESS)\n	  {\n	    \n	    `mv $wget_t\
mp $distrib`;\n	    `$CP $distrib $DOWNLOAD_DIR/`;\
\n	  }\n\n	if (!-e $distrib)\n	  {\n	    print \"!\
!!!!!! Download of $pg distribution failed\\n\";\n\
	    print \"!!!!!!! Check Address: $PG{$pg}{sourc\
e}\\n\";\n	    return 0;\n	  }\n	print \"\\n------\
- unzipping/untaring $name\\n\";\n	if (($ext =~/z/\
))\n	  { \n	    &flush_command (\"gunzip $name$ext\
\");\n	    \n	  }\n	if (($ext =~/tar/) || ($ext =~\
/tgz/))\n	  {\n	    &flush_command(\"tar -xvf $nam\
e.tar\");\n	  }\n      }\n    #Guess and enter the\
 distribution directory\n    @fl=ls($p);\n    fore\
ach my $f (@fl)\n      {\n	if (-d $f)\n	  {\n	    \
$main_dir=$f;\n	  }\n      }\n    if (-d $main_dir\
)\n	  \n      {\n	chdir $main_dir;}\n    else\n   \
   {\n	print \"Error: $main_dir does not exist\";\\
n      }\n    print \"\\n------- Compiling/Install\
ing $pg\\n\";\n    `make clean $SILENT`;\n    \n  \
  \n    #\n    # SAP module\n    #\n    if ($pg eq\
 \"sap\")\n      {\n	if (-e \"./configure\")\n	  {\
\n	    #new sap distribution\n	    if ($OS eq \"ma\
cosx\")\n	      {\n		&replace_line_in_file (\"./sr\
c/galloc.h\", \"malloc.h\",  \"\");\n		&replace_li\
ne_in_file (\"./src/pdbprot.h\", \"malloc.h\", \"\\
");\n		&replace_line_in_file (\"./src/pdbprot.c\",\
 \"malloc.h\", \"\");\n	      }\n	    \n	    &flus\
h_command (\"./configure\");\n	    &flush_command \
(\"make clean\");\n	    &flush_command (\"make\");\
\n	    &check_cp (\"./src/$pg\", \"$BIN\");\n	    \
repo_store(\"./src/$pg\");\n	  }\n	else\n	  {\n	  \
  #old style distribution\n	    `rm *.o sap  sap.e\
xe ./util/aa/*.o  ./util/wt/.o $SILENT`;\n	    &fl\
ush_command (\"make $arguments sap\");\n	    &chec\
k_cp ($pg, \"$BIN\");\n	    repo_store($pg);\n	  }\
\n      }\n    \n    #\n    # CLUSTALW2 module\n  \
  #\n    elsif ($pg eq \"clustalw2\")\n      {\n	&\
flush_command(\"./configure\");\n	&flush_command(\\
"make $arguments\");\n	&check_cp (\"./src/$pg\", \\
"$BIN\");\n	repo_store(\"./src/$pg\");\n      }\n \
   \n    #\n    # FSA module\n    # \n    elsif ($\
pg eq \"fsa\")\n      {\n	&flush_command(\"./confi\
gure --prefix=$BIN\");\n	&flush_command(\"make $ar\
guments\");\n	&flush_command (\"make install\");\n\
\n	repo_store(\"fsa\", \"$BIN/bin\");\n	`mv $BIN/b\
in/* $BIN`;\n	`rmdir $BIN/bin`;\n      }\n    \n  \
  #\n    # CLUSTALW module\n    #\n    elsif ($pg \
eq \"clustalw\")\n      {\n	&flush_command(\"make \
$arguments clustalw\");\n	`$CP $pg $BIN $SILENT`;\\
n	repo_store($pg);\n      }\n    \n    #\n    # MA\
FFT module\n    #\n    elsif ($pg eq \"mafft\")\n \
     {\n	my $base=cwd();\n	my $c;\n	\n	#compile co\
re\n	mkpath (\"./mafft/bin\");\n	mkpath (\"./mafft\
/lib\");\n	chdir \"$base/core\";\n	`make clean $SI\
LENT`;\n	&flush_command (\"make $arguments\");\n	&\
flush_command (\"make install LIBDIR=../mafft/lib \
BINDIR=../mafft/bin\");\n	\n	#compile extension\n	\
chdir \"$base/extensions\";\n	`make clean $SILENT`\
;\n	&flush_command (\"make $arguments\");\n	&flush\
_command (\"make install LIBDIR=../mafft/lib BINDI\
R=../mafft/bin\");\n	\n	#put everything in mafft a\
nd copy the compiled stuff in bin\n	chdir \"$base\\
";\n	if ($ROOT_INSTALL)\n	  {\n	    &root_run (\"Y\
ou Must be Root to Install MAFFT\\n\", \"mkdir /us\
r/local/mafft/;$CP mafft/lib/* /usr/local/mafft;$C\
P mafft/lib/mafft* /usr/local/bin ;$CP mafft/bin/m\
afft /usr/local/bin/; \");\n	  }\n	else\n	  {\n	  \
  `$CP mafft/lib/*  $BIN`;\n	    `$CP mafft/bin/ma\
fft  $BIN`;\n	  }\n	`tar -cvf mafft.tar mafft`;\n	\
`gzip mafft.tar`;\n	`mv mafft.tar.gz $BIN`;\n	\n	r\
epo_store(\"mafft/bin/mafft\", \"mafft/lib/\", \"$\
BIN/mafft.tar.gz\");\n      }\n      \n    #\n    \
# DIALIGN-TX module\n    #\n    elsif ( $pg eq \"d\
ialign-tx\" )\n      {\n	my $f;\n	my $base=cwd();\\
n\n	chdir \"./source\";\n	if ($OS eq \"macosx\"){&\
flush_command (\"cp makefile.MAC_OS makefile\");}\\
n\n	&flush_command (\" make CPPFLAGS='-O3 -funroll\
-loops' all\");\n	\n	chdir \"..\";\n	&check_cp (\"\
./source/$pg\", \"$BIN\");\n	repo_store(\"./source\
/$pg\");\n      }\n      \n    #\n    # DIALIGN-T \
module \n    # (is the same as dialign-tx, but it \
is mantained for backward name compatibility with \
tcoffee)\n    #\n    elsif ( $pg eq \"dialign-t\" \
)\n      {\n	my $f;\n	my $base=cwd();\n\n	chdir \"\
./source\";\n	if ($OS eq \"macosx\"){&flush_comman\
d (\"cp makefile.MAC_OS makefile\");}\n\n	&flush_c\
ommand (\" make CPPFLAGS='-O3 -funroll-loops' all\\
");\n	\n	chdir \"..\";\n	&check_cp (\"./source/dia\
lign-tx\", \"$BIN/dialign-t\");\n	repo_store(\"$BI\
N/dialign-t\");	\n      }      \n      \n    #\n  \
  # POA module\n    #\n    elsif ($pg eq \"poa\")\\
n      {\n	&flush_command (\"make $arguments poa\"\
);\n	&check_cp (\"$pg\", \"$BIN\");\n	repo_store(\\
"$pg\");\n      }\n     \n     \n    #\n    # PROB\
CONS module\n    #\n    elsif ( $pg eq \"probcons\\
")\n      {\n	&add_C_libraries(\"./ProbabilisticMo\
del.h\", \"list\", \"cstring\");\n	\n	`rm *.exe $S\
ILENT`;\n	&flush_command (\"make $arguments probco\
ns\");\n	&check_cp(\"$pg\", \"$BIN/$pg\");\n	repo_\
store(\"$pg\");\n      }\n      \n    #\n    # PRO\
BCONS RNA module\n    #\n    elsif ( $pg eq \"prob\
consRNA\")\n      {\n	&add_C_libraries(\"./Probabi\
listicModel.h\", \"list\", \"cstring\");\n	&add_C_\
libraries(\"./Main.cc\", \"iomanip\", \"cstring\",\
\"climits\");\n	`rm *.exe $SILENT`;\n	&flush_comma\
nd (\"make $arguments probcons\");\n	&check_cp(\"p\
robcons\", \"$BIN/$pg\");\n	repo_store(\"$BIN/$pg\\
");\n      }\n\n	#\n	# MUSCLE module\n	#\n    elsi\
f (  $pg eq \"muscle\")\n      {	\n	`rm *.o muscle\
 muscle.exe $SILENT`;\n	if ($OS eq \"macosx\" || $\
OS eq \"linux\")\n	  {\n	    &replace_line_in_file\
 (\"./Makefile\", \"LDLIBS = -lm -static\",  \"LDL\
IBS = -lm\");\n	  }\n	elsif ($OS eq \"windows\")\n\
	  {\n	    &replace_line_in_file (\"./intmath.cpp\\
",  \"double log2e\",      \"double cedric_log\");\
\n	    &replace_line_in_file (\"./intmath.cpp\",  \
\"double log2\",       \"double log_notuse\");\n	 \
   &replace_line_in_file (\"./intmath.cpp\",  \"do\
uble cedric_log\", \"double log2e\");\n	  }\n	&flu\
sh_command (\"make $arguments all\");\n	&check_cp(\
\"$pg\", \"$BIN\");\n	repo_store(\"$pg\");	\n     \
 }\n      \n     #\n     # MUS4 module\n     #\n  \
   elsif (  $pg eq \"mus4\")\n      {\n	`rm *.o mu\
scle muscle.exe $SILENT`;\n	&flush_command (\"./mk\
\");\n	&check_cp(\"$pg\", \"$BIN\");\n	repo_store(\
\"$pg\");	\n      }\n      \n    #\n    # PCMA mod\
ule\n    #\n    elsif ( $pg eq \"pcma\")\n      {\\
n	if ($OS eq \"macosx\")\n	  {\n	    &replace_line\
_in_file (\"./alcomp2.c\", \"malloc.h\",  \"\");\n\
	  }\n	&flush_command (\"make $arguments pcma\");\\
n	&check_cp(\"$pg\", \"$BIN\");\n	repo_store(\"$pg\
\");	\n      }\n      \n    #\n    # KALIGN module\
\n    #\n    elsif ($pg eq \"kalign\")\n      {\n	\
&flush_command (\"./configure\");\n	&flush_command\
(\"make $arguments\");\n	&check_cp (\"$pg\",$BIN);\
\n	repo_store(\"$pg\");	\n      }\n      \n    #\n\
    # AMAP module\n    #\n    elsif ( $pg eq \"ama\
p\")\n      {\n	&add_C_libraries(\"./Amap.cc\", \"\
iomanip\", \"cstring\",\"climits\");	\n	`make clea\
n $SILENT`;\n	&flush_command (\"make $arguments al\
l\");\n	&check_cp (\"$pg\", $BIN);\n	repo_store(\"\
$pg\");	\n      }\n      \n    #\n    # PRODA modu\
le\n    #\n    elsif ( $pg eq \"proda\")\n      {\\
n	&add_C_libraries(\"AlignedFragment.h\", \"vector\
\", \"iostream\", \"cstring\",\"cstdlib\");\n	&add\
_C_libraries(\"Main.cc\", \"vector\", \"climits\")\
;	\n	&add_C_libraries(\"Sequence.cc\", \"stdlib.h\\
", \"cstdio\");	\n	&flush_command (\"make $argumen\
ts all\");\n	&check_cp (\"$pg\", $BIN);\n	repo_sto\
re(\"$pg\");	\n      }\n      \n    #\n    # PRANK\
 module\n    #\n    elsif ( $pg eq \"prank\")\n   \
   {\n	&flush_command (\"make $arguments all\");\n\
	&check_cp (\"$pg\", $BIN);\n	repo_store(\"$pg\");\
	\n      }\n      \n    #\n    # !!!! MUSTANG modu\
le\n    #\n     elsif ( $pg eq \"mustang\")\n     \
 {\n	&flush_command (\"rm ./bin/*\");\n	&flush_com\
mand (\"make $arguments all\");\n\n	if ( $OS=~/win\
dows/){&flush_command(\"cp ./bin/* $BIN/mustang.ex\
e\");}\n	else {&flush_command(\"cp ./bin/* $BIN/mu\
stang\");}\n	\n	repo_store(\"$BIN/mustang\");\n   \
   }\n\n	#\n	# RNAplfold module\n	#\n    elsif ( $\
pg eq \"RNAplfold\")\n      {\n	&flush_command(\".\
/configure\");\n	&flush_command (\"make $arguments\
 all\");\n	&check_cp(\"./Progs/RNAplfold\", \"$BIN\
\");\n	&check_cp(\"./Progs/RNAalifold\", \"$BIN\")\
;\n	&check_cp(\"./Progs/RNAfold\", \"$BIN\");\n	\n\
	repo_store(\"./Progs/RNAplfold\", \"./Progs/RNAal\
ifold\", \"./Progs/RNAfold\");\n      }\n      \n \
   #\n    # !!! RETREE module\n    #\n    elsif ( \
$pg eq \"retree\")\n      {\n	chdir \"src\";\n	&fl\
ush_command (\"make $arguments all\");\n	&flush_co\
mmand (\"make put\");\n	system \"cp ../exe/* $BIN\\
";\n	\n	repo_store(\"retree\", \"../exe\");\n     \
 }\n	\n    chdir $CDIR;\n    return &pg_is_install\
ed ($pg, $BIN);\n  }\n\nsub install_t_coffee\n  {\\
n    my ($pg)=(@_);\n    my ($report,$cflags, $arg\
uments, $language, $compiler) ;\n    #1-Install T-\
Coffee\n    chdir \"t_coffee_source\";\n    &flush\
_command (\"make clean\");\n    print \"\\n-------\
 Compiling T-Coffee\\n\";\n    $language=$PG{$pg} \
{language2};\n    $arguments=$PG{$language}{argume\
nts};\n    if (!($arguments =~/CFLAGS/)){$argument\
s .= \" CFLAGS=-O2 \";}\n\n    if ( $CC ne \"\"){&\
flush_command (\"make -i $arguments t_coffee\");}\\
n    &check_cp ($pg, $BIN);\n    \n    chdir $CDIR\
;\n    return &pg_is_installed ($pg, $BIN);\n  }\n\
sub install_TMalign\n  {\n    my ($pg)=(@_);\n    \
my $report;\n    chdir \"t_coffee_source\";\n    p\
rint \"\\n------- Compiling TMalign\\n\";\n    `rm\
 TMalign TMalign.exe $SILENT`;\n    if ( $FC ne \"\
\"){&flush_command (\"make -i $PG{Fortran}{argumen\
ts} TMalign\");}\n    &check_cp ($pg, $BIN);\n    \
repo_store($pg);\n\n    if ( !-e \"$BIN/$pg\" && p\
g_has_binary_distrib ($pg))\n      {\n	print \"!!!\
!!!! Compilation of $pg impossible. Will try to in\
stall from binary\\n\";\n	return &install_binary_p\
ackage ($pg);\n      }\n    chdir $CDIR;\n    retu\
rn &pg_is_installed ($pg, $BIN);\n  }\n\nsub pg_ha\
s_binary_distrib\n  {\n    my ($pg)=(@_);\n    if \
($PG{$pg}{windows}){return 1;}\n    elsif ($PG{$pg\
}{osx}){return 1;}\n    elsif ($PG{$pg}{linux}){re\
turn 1;}\n    return 0;\n  }\nsub install_binary_p\
ackage\n  {\n    my ($pg)=(@_);\n    my ($base,$re\
port,$name, $download, $arguments, $language, $dir\
);\n    my $isdir;\n    &input_os();\n    \n    if\
 (!&supported_os($OS)){return 0;}\n    if ( $PG{$p\
g}{binary}){$name=$PG{$pg}{binary};}\n    else \n \
     {\n	$name=$pg;\n	if ( $OS eq \"windows\"){$na\
me.=\".exe\";}\n      }\n    \n    $download=\"$WE\
B_BASE/Packages/Binaries/$OS/$name\";\n    \n    $\
base=cwd();\n    chdir $TMP;\n    \n    if (!-e $n\
ame)\n      {\n	`rm x $SILENT`;\n	if ( url2file(\"\
$download\",\"x\")==$EXIT_SUCCESS)\n	  {\n	    `mv\
 x $name`;\n	  }\n      }\n    \n    if (!-e $name\
)\n      {\n	print \"!!!!!!! $PG{$pg}{dname}: Down\
load of $pg binary failed\\n\";\n	print \"!!!!!!! \
$PG{$pg}{dname}: Check Address: $download\\n\";\n	\
return 0;\n      }\n    print \"\\n------- Install\
ing $pg\\n\";\n    \n    if ($name =~/tar\\.gz/)\n\
      {\n	`gunzip  $name`;\n	`tar -xvf $pg.tar`;\n\
	chdir $pg;\n	if ( $pg eq \"mafft\")\n	  {\n	    i\
f ($ROOT_INSTALL)\n	      {\n		&root_run (\"You Mu\
st be Roor to Install MAFFT\\n\", \"$CP mafft/bin/\
* /usr/local/mafft;mkdir /usr/local/mafft/; $CP ma\
fft/lib/* /usr/local/bin/\");\n	      }\n	    else\
\n	      {\n		`$CP $TMP/$pg/bin/* $BIN $SILENT`;\n\
		`$CP $TMP/$pg/lib/* $BIN $SILENT`;\n	      }\n	 \
 }\n	else\n	  {\n	    if (-e \"$TMP/$pg/data\"){`$\
CP $TMP/$pg/data/* $TCM $SILENT`;}\n	    if (!($pg\
=~/\\*/)){`rm -rf $pg`;}\n	  }\n      }\n    else\\
n      {\n	&check_cp (\"$pg\", \"$BIN\");\n	`chmod\
 u+x $BIN/$pg`; \n	unlink ($pg);\n      }\n    chd\
ir $base;\n    $PG{$pg}{from_binary}=1;\n    retur\
n &pg_is_installed ($pg, $BIN);\n  }\n\nsub add_di\
r \n  {\n    my $dir=@_[0];\n    \n    if (!-e $di\
r && !-d $dir)\n      {\n	my @l;\n	umask (0000);\n\
	@l=mkpath ($dir,{mode => 0777});\n	\n      }\n   \
 else\n      {\n	return 0;\n      }\n  }\nsub chec\
k_rm \n  {\n    my ($file)=(@_);\n    \n    if ( -\
e $file)\n      {\n	return unlink($file);\n      }\
\n    return 0;\n  }\nsub check_cp\n  {\n    my ($\
from, $to)=(@_);\n    if ( !-e $from && -e \"$from\
\\.exe\"){$from=\"$from\\.exe\";}\n    if ( !-e $f\
rom){return 0;}\n        \n    `$CP $from $to`;\n \
   return 1;\n  }\n\nsub repo_store \n{\n   # chec\
k that all required data are available\n   if( $RE\
PO_ROOT eq \"\" ) { return; }\n\n\n    # extract t\
he package name from the specified path\n    my $p\
g =`basename $_[0]`;\n    chomp($pg);\n	\n    my $\
VER = $PG{$pg}{version};\n    my $CACHE = \"$REPO_\
ROOT/$pg/$VER/$OSNAME-$OSARCH\"; \n    \n    print\
 \"-------- Storing package: \\\"$pg\\\" to path: \
$CACHE\\n\";\n    \n    # clean the cache path if \
exists and create it again\n    `rm -rf $CACHE`;\n\
    `mkdir -p $CACHE`;\n    \n 	for my $path (@_) \
{\n\n	    # check if it is a single file \n	 	if( \
-f $path ) {\n	    	`cp $path $CACHE`;\n		}\n		# .\
. or a directory, in this case copy all the conten\
t \n		elsif( -d $path ) {\n			opendir(IMD, $path);\
\n			my @thefiles= readdir(IMD);\n			closedir(IMD)\
;\n			\n			for my $_file (@thefiles) {\n				if( $_\
file ne \".\" && $_file ne \"..\") {\n	    			`cp \
$path/$_file $CACHE`;\n				}\n			}\n		} \n	}	   \n\
    \n	\n}   \n\nsub repo_load \n{\n    my ($pg)=(\
@_);\n\n    # check that all required data are ava\
ilable\n    if( $REPO_ROOT eq \"\" ) { return 0; }\
\n\n    my $VER = $PG{$pg}{version};\n    my $CACH\
E = \"$REPO_ROOT/$pg/$VER/$OSNAME-$OSARCH\"; \n   \
 if( !-e \"$CACHE/$pg\" ) {\n   	 	print \"-------\
- Module \\\"$pg\\\" NOT found on repository cache\
.\\n\";\n    	return 0;\n    }\n    \n    print \"\
-------- Module \\\"$pg\\\" found on repository ca\
che. Using copy on path: $CACHE\\n\";\n    `cp $CA\
CHE/* $BIN`;\n    return 1;\n}\n\nsub check_file_l\
ist_exists \n  {\n    my ($base, @flist)=(@_);\n  \
  my $f;\n\n    foreach $f (@flist)\n      {\n	if \
( !-e \"$base/$f\"){return 0;}\n      }\n    retur\
n 1;\n  }\nsub ls\n  {\n    my $f=@_[0];\n    my @\
fl;\n    chomp(@fl=`ls -1 $f`);\n    return @fl;\n\
  }\nsub flush_command\n  {\n    my $command=@_[0]\
;\n    my $F=new FileHandle;\n    open ($F, \"$com\
mand|\");\n    while (<$F>){print \"    --- $_\";}\
\n    close ($F);\n  }    \n\nsub input_installati\
on_directory\n  {\n    my $dir=@_[0];\n    my $new\
;\n    \n    print \"------- The current installat\
ion directory is: [$dir]\\n\";\n    print \"??????\
? Return to keep the default or new value:\";\n   \
\n    if ($NO_QUESTION==0)\n      {\n	chomp ($new=\
<stdin>);\n	while ( $new ne \"\" && !input_yes (\"\
You have entered $new. Is this correct? ([y]/n):\"\
))\n	  {\n	    print \"???????New installation dir\
ectory:\";\n	    chomp ($new=<stdin>);\n	  }\n	$di\
r=($new eq \"\")?$dir:$new;\n	$dir=~s/\\/$//;\n   \
   }\n    \n    if ( -d $dir){return $dir;}\n    e\
lsif (&root_run (\"You must be root to create $dir\
\",\"mkdir $dir\")==$EXIT_SUCCESS){return $dir;}\n\
    else\n      {\n	print \"!!!!!!! $dir could not\
 be created\\n\";\n	if ( $NO_QUESTION)\n	  {\n	   \
 return \"\";\n	  }\n	elsif ( &input_yes (\"??????\
? Do you want to provide a new directory([y]/n)?:\\
"))\n	  {\n	    return input_installation_director\
y ($dir);\n	  }\n	else\n	  {\n	    return \"\";\n	\
  }\n      }\n    \n  }\nsub input_yes\n  {\n    m\
y $question =@_[0];\n    my $answer;\n\n    if ($N\
O_QUESTION==1){return 1;}\n    \n    if ($question\
 eq \"\"){$question=\"??????? Do you wish to proce\
ed ([y]/n)?:\";}\n    print $question;\n    chomp(\
$answer=lc(<STDIN>));\n    if (($answer=~/^y/) || \
$answer eq \"\"){return 1;}\n    elsif ( ($answer=\
~/^n/)){return 0;}\n    else\n      {\n	return inp\
ut_yes($question);\n      }\n  }\nsub root_run\n  \
{\n    my ($txt, $cmd)=(@_);\n    \n    if ( syste\
m ($cmd)==$EXIT_SUCCESS){return $EXIT_SUCCESS;}\n \
   else \n      {\n	print \"------- $txt\\n\";\n	i\
f ( $ROOT eq \"sudo\"){return system (\"sudo $cmd\\
");}\n	else {return system (\"su root -c \\\"$cmd\\
\\"\");}\n      }\n  }\nsub get_root\n  {\n    if \
(&pg_is_installed (\"sudo\")){return \"sudo\";}\n \
   else {return \"su\";}\n  }\n\nsub get_os\n  {\n\
    my $raw_os=`uname`;\n    my $os;\n\n    $raw_o\
s=lc ($raw_os);\n    \n    if ($raw_os =~/cygwin/)\
{$os=\"windows\";}\n    elsif ($raw_os =~/linux/){\
$os=\"linux\";}\n    elsif ($raw_os =~/osx/){$os=\\
"macosx\";}\n    elsif ($raw_os =~/darwin/){$os=\"\
macosx\";}\n    else\n      {\n	$os=$raw_os;\n    \
  }\n    return $os;\n  }\nsub input_os\n  {\n    \
my $answer;\n    if ($OS) {return $OS;}\n    \n   \
 print \"??????? which os do you use: [w]indows, [\
l]inux, [m]acosx:?\";\n    $answer=lc(<STDIN>);\n\\
n    if (($answer=~/^m/)){$OS=\"macosx\";}\n    el\
sif ( ($answer=~/^w/)){$OS=\"windows\";}\n    elsi\
f ( ($answer=~/^linux/)){$OS=\"linux\";}\n    \n  \
  else\n      {\n	return &input_os();\n      }\n  \
  return $OS;\n  }\n\nsub supported_os\n  {\n    m\
y ($os)=(@_[0]);\n    return $SUPPORTED_OS{$os};\n\
  }\n    \n    \n\n\nsub update_tclinkdb \n  {\n  \
  my $file =@_[0];\n    my $name;\n    my $F=new F\
ileHandle;\n    my ($download, $address, $name, $l\
, $db);\n    \n    if ( $file eq \"update\"){$file\
=$TCLINKDB_ADDRESS;}\n    \n    if ( $file =~/http\
:\\/\\// || $file =~/ftp:\\/\\//)\n      {\n	($add\
ress, $name)=($download=~/(.*)\\/([^\\/]+)$/);\n	`\
rm x $SILENT`;\n	if (&url2file ($file,\"x\")==$EXI\
T_SUCCESS)\n	  {\n	    print \"------- Susscessful\
 upload of $name\";\n	    `mv x $name`;\n	    $fil\
e=$name;\n	  }\n      }\n    open ($F, \"$file\");\
\n    while (<$F>)\n      {\n	my $l=$_;\n	if (($l \
=~/^\\/\\//) || ($db=~/^#/)){;}\n	elsif ( !($l =~/\
\\w/)){;}\n	else\n	  {\n	    my @v=split (/\\s+/, \
$l);\n	    if ( $l=~/^MODE/)\n	      {\n		$MODE{$v\
[1]}{$v[2]}=$v[3];\n	      }\n	    elsif ($l=~/^PG\
/)\n	      {\n		$PG{$v[1]}{$v[2]}=$v[3];\n	      }\
\n	  }\n      }\n    close ($F);\n    &post_proces\
s_PG();\n    return;\n  }\n\n\n\nsub initialize_PG\
\n  {\n\n$PG{\"t_coffee\"}{\"4_TCOFFEE\"}=\"TCOFFE\
E\";\n$PG{\"t_coffee\"}{\"type\"}=\"sequence_multi\
ple_aligner\";\n$PG{\"t_coffee\"}{\"ADDRESS\"}=\"h\
ttp://www.tcoffee.org\";\n$PG{\"t_coffee\"}{\"lang\
uage\"}=\"C\";\n$PG{\"t_coffee\"}{\"language2\"}=\\
"C\";\n$PG{\"t_coffee\"}{\"source\"}=\"http://www.\
tcoffee.org/Packages/T-COFFEE_distribution.tar.gz\\
";\n$PG{\"t_coffee\"}{\"update_action\"}=\"always\\
";\n$PG{\"t_coffee\"}{\"mode\"}=\"tcoffee,mcoffee,\
rcoffee,expresso,3dcoffee\";\n$PG{\"clustalw2\"}{\\
"4_TCOFFEE\"}=\"CLUSTALW2\";\n$PG{\"clustalw2\"}{\\
"type\"}=\"sequence_multiple_aligner\";\n$PG{\"clu\
stalw2\"}{\"ADDRESS\"}=\"http://www.clustal.org\";\
\n$PG{\"clustalw2\"}{\"language\"}=\"C++\";\n$PG{\\
"clustalw2\"}{\"language2\"}=\"CXX\";\n$PG{\"clust\
alw2\"}{\"source\"}=\"http://www.clustal.org/downl\
oad/2.0.10/clustalw-2.0.10-src.tar.gz\";\n$PG{\"cl\
ustalw2\"}{\"mode\"}=\"mcoffee,rcoffee\";\n$PG{\"c\
lustalw2\"}{\"version\"}=\"2.0.10\";\n$PG{\"clusta\
lw\"}{\"4_TCOFFEE\"}=\"CLUSTALW\";\n$PG{\"clustalw\
\"}{\"type\"}=\"sequence_multiple_aligner\";\n$PG{\
\"clustalw\"}{\"ADDRESS\"}=\"http://www.clustal.or\
g\";\n$PG{\"clustalw\"}{\"language\"}=\"C\";\n$PG{\
\"clustalw\"}{\"language2\"}=\"C\";\n$PG{\"clustal\
w\"}{\"source\"}=\"http://www.clustal.org/download\
/1.X/ftp-igbmc.u-strasbg.fr/pub/ClustalW/clustalw1\
.82.UNIX.tar.gz\";\n$PG{\"clustalw\"}{\"mode\"}=\"\
mcoffee,rcoffee\";\n$PG{\"clustalw\"}{\"version\"}\
=\"1.82\";\n$PG{\"dialign-t\"}{\"4_TCOFFEE\"}=\"DI\
ALIGNT\";\n$PG{\"dialign-t\"}{\"type\"}=\"sequence\
_multiple_aligner\";\n$PG{\"dialign-t\"}{\"ADDRESS\
\"}=\"http://dialign-tx.gobics.de/\";\n$PG{\"diali\
gn-t\"}{\"DIR\"}=\"/usr/share/dialign-tx/\";\n$PG{\
\"dialign-t\"}{\"language\"}=\"C\";\n$PG{\"dialign\
-t\"}{\"language2\"}=\"C\";\n$PG{\"dialign-t\"}{\"\
source\"}=\"http://dialign-tx.gobics.de/DIALIGN-TX\
_1.0.2.tar.gz\";\n$PG{\"dialign-t\"}{\"mode\"}=\"m\
coffee\";\n$PG{\"dialign-t\"}{\"binary\"}=\"dialig\
n-t\";\n$PG{\"dialign-t\"}{\"version\"}=\"1.0.2\";\
\n$PG{\"dialign-tx\"}{\"4_TCOFFEE\"}=\"DIALIGNTX\"\
;\n$PG{\"dialign-tx\"}{\"type\"}=\"sequence_multip\
le_aligner\";\n$PG{\"dialign-tx\"}{\"ADDRESS\"}=\"\
http://dialign-tx.gobics.de/\";\n$PG{\"dialign-tx\\
"}{\"DIR\"}=\"/usr/share/dialign-tx/\";\n$PG{\"dia\
lign-tx\"}{\"language\"}=\"C\";\n$PG{\"dialign-tx\\
"}{\"language2\"}=\"C\";\n$PG{\"dialign-tx\"}{\"so\
urce\"}=\"http://dialign-tx.gobics.de/DIALIGN-TX_1\
.0.2.tar.gz\";\n$PG{\"dialign-tx\"}{\"mode\"}=\"mc\
offee\";\n$PG{\"dialign-tx\"}{\"binary\"}=\"dialig\
n-tx\";\n$PG{\"dialign-tx\"}{\"version\"}=\"1.0.2\\
";\n$PG{\"poa\"}{\"4_TCOFFEE\"}=\"POA\";\n$PG{\"po\
a\"}{\"type\"}=\"sequence_multiple_aligner\";\n$PG\
{\"poa\"}{\"ADDRESS\"}=\"http://www.bioinformatics\
.ucla.edu/poa/\";\n$PG{\"poa\"}{\"language\"}=\"C\\
";\n$PG{\"poa\"}{\"language2\"}=\"C\";\n$PG{\"poa\\
"}{\"source\"}=\"http://downloads.sourceforge.net/\
poamsa/poaV2.tar.gz\";\n$PG{\"poa\"}{\"DIR\"}=\"/u\
sr/share/\";\n$PG{\"poa\"}{\"FILE1\"}=\"blosum80.m\
at\";\n$PG{\"poa\"}{\"mode\"}=\"mcoffee\";\n$PG{\"\
poa\"}{\"binary\"}=\"poa\";\n$PG{\"poa\"}{\"versio\
n\"}=\"2.0\";\n$PG{\"probcons\"}{\"4_TCOFFEE\"}=\"\
PROBCONS\";\n$PG{\"probcons\"}{\"type\"}=\"sequenc\
e_multiple_aligner\";\n$PG{\"probcons\"}{\"ADDRESS\
\"}=\"http://probcons.stanford.edu/\";\n$PG{\"prob\
cons\"}{\"language2\"}=\"CXX\";\n$PG{\"probcons\"}\
{\"language\"}=\"C++\";\n$PG{\"probcons\"}{\"sourc\
e\"}=\"http://probcons.stanford.edu/probcons_v1_12\
.tar.gz\";\n$PG{\"probcons\"}{\"mode\"}=\"mcoffee\\
";\n$PG{\"probcons\"}{\"binary\"}=\"probcons\";\n$\
PG{\"probcons\"}{\"version\"}=\"1.12\";\n$PG{\"maf\
ft\"}{\"4_TCOFFEE\"}=\"MAFFT\";\n$PG{\"mafft\"}{\"\
type\"}=\"sequence_multiple_aligner\";\n$PG{\"maff\
t\"}{\"ADDRESS\"}=\"http://align.bmr.kyushu-u.ac.j\
p/mafft/online/server/\";\n$PG{\"mafft\"}{\"langua\
ge\"}=\"C\";\n$PG{\"mafft\"}{\"language\"}=\"C\";\\
n$PG{\"mafft\"}{\"source\"}=\"http://align.bmr.kyu\
shu-u.ac.jp/mafft/software/mafft-6.603-with-extens\
ions-src.tgz\";\n$PG{\"mafft\"}{\"windows\"}=\"htt\
p://align.bmr.kyushu-u.ac.jp/mafft/software/mafft-\
6.603-mingw.tar\";\n$PG{\"mafft\"}{\"mode\"}=\"mco\
ffee,rcoffee\";\n$PG{\"mafft\"}{\"binary\"}=\"maff\
t.tar.gz\";\n$PG{\"mafft\"}{\"version\"}=\"6.603\"\
;\n$PG{\"muscle\"}{\"4_TCOFFEE\"}=\"MUSCLE\";\n$PG\
{\"muscle\"}{\"type\"}=\"sequence_multiple_aligner\
\";\n$PG{\"muscle\"}{\"ADDRESS\"}=\"http://www.dri\
ve5.com/muscle/\";\n$PG{\"muscle\"}{\"language\"}=\
\"C++\";\n$PG{\"muscle\"}{\"language2\"}=\"GPP\";\\
n$PG{\"muscle\"}{\"source\"}=\"http://www.drive5.c\
om/muscle/downloads3.7/muscle3.7_src.tar.gz\";\n$P\
G{\"muscle\"}{\"windows\"}=\"http://www.drive5.com\
/muscle/downloads3.7/muscle3.7_win32.zip\";\n$PG{\\
"muscle\"}{\"linux\"}=\"http://www.drive5.com/musc\
le/downloads3.7/muscle3.7_linux_ia32.tar.gz\";\n$P\
G{\"muscle\"}{\"mode\"}=\"mcoffee,rcoffee\";\n$PG{\
\"muscle\"}{\"version\"}=\"3.7\";\n$PG{\"mus4\"}{\\
"4_TCOFFEE\"}=\"MUS4\";\n$PG{\"mus4\"}{\"type\"}=\\
"sequence_multiple_aligner\";\n$PG{\"mus4\"}{\"ADD\
RESS\"}=\"http://www.drive5.com/muscle/\";\n$PG{\"\
mus4\"}{\"language\"}=\"C++\";\n$PG{\"mus4\"}{\"la\
nguage2\"}=\"GPP\";\n$PG{\"mus4\"}{\"source\"}=\"h\
ttp://www.drive5.com/muscle/muscle4.0_src.tar.gz\"\
;\n$PG{\"mus4\"}{\"mode\"}=\"mcoffee,rcoffee\";\n$\
PG{\"mus4\"}{\"version\"}=\"4.0\";\n$PG{\"pcma\"}{\
\"4_TCOFFEE\"}=\"PCMA\";\n$PG{\"pcma\"}{\"type\"}=\
\"sequence_multiple_aligner\";\n$PG{\"pcma\"}{\"AD\
DRESS\"}=\"ftp://iole.swmed.edu/pub/PCMA/\";\n$PG{\
\"pcma\"}{\"language\"}=\"C\";\n$PG{\"pcma\"}{\"la\
nguage2\"}=\"C\";\n$PG{\"pcma\"}{\"source\"}=\"ftp\
://iole.swmed.edu/pub/PCMA/pcma.tar.gz\";\n$PG{\"p\
cma\"}{\"mode\"}=\"mcoffee\";\n$PG{\"pcma\"}{\"ver\
sion\"}=\"1.0\";\n$PG{\"kalign\"}{\"4_TCOFFEE\"}=\\
"KALIGN\";\n$PG{\"kalign\"}{\"type\"}=\"sequence_m\
ultiple_aligner\";\n$PG{\"kalign\"}{\"ADDRESS\"}=\\
"http://msa.cgb.ki.se\";\n$PG{\"kalign\"}{\"langua\
ge\"}=\"C\";\n$PG{\"kalign\"}{\"language2\"}=\"C\"\
;\n$PG{\"kalign\"}{\"source\"}=\"http://msa.cgb.ki\
.se/downloads/kalign/current.tar.gz\";\n$PG{\"kali\
gn\"}{\"mode\"}=\"mcoffee\";\n$PG{\"kalign\"}{\"ve\
rsion\"}=\"1.0\";\n$PG{\"amap\"}{\"4_TCOFFEE\"}=\"\
AMAP\";\n$PG{\"amap\"}{\"type\"}=\"sequence_multip\
le_aligner\";\n$PG{\"amap\"}{\"ADDRESS\"}=\"http:/\
/bio.math.berkeley.edu/amap/\";\n$PG{\"amap\"}{\"l\
anguage\"}=\"C++\";\n$PG{\"amap\"}{\"language2\"}=\
\"CXX\";\n$PG{\"amap\"}{\"source\"}=\"http://amap-\
align.googlecode.com/files/amap.2.0.tar.gz\";\n$PG\
{\"amap\"}{\"mode\"}=\"mcoffee\";\n$PG{\"amap\"}{\\
"version\"}=\"2.0\";\n$PG{\"proda\"}{\"4_TCOFFEE\"\
}=\"PRODA\";\n$PG{\"proda\"}{\"type\"}=\"sequence_\
multiple_aligner\";\n$PG{\"proda\"}{\"ADDRESS\"}=\\
"http://proda.stanford.edu\";\n$PG{\"proda\"}{\"la\
nguage\"}=\"C++\";\n$PG{\"proda\"}{\"language2\"}=\
\"CXX\";\n$PG{\"proda\"}{\"source\"}=\"http://prod\
a.stanford.edu/proda_1_0.tar.gz\";\n$PG{\"proda\"}\
{\"mode\"}=\"mcoffee\";\n$PG{\"proda\"}{\"version\\
"}=\"1.0\";\n$PG{\"fsa\"}{\"4_TCOFFEE\"}=\"FSA\";\\
n$PG{\"fsa\"}{\"type\"}=\"sequence_multiple_aligne\
r\";\n$PG{\"fsa\"}{\"ADDRESS\"}=\"http://fsa.sourc\
eforge.net/\";\n$PG{\"fsa\"}{\"language\"}=\"C++\"\
;\n$PG{\"fsa\"}{\"language2\"}=\"CXX\";\n$PG{\"fsa\
\"}{\"source\"}=\"http://sourceforge.net/projects/\
fsa/files/fsa-1.15.3.tar.gz/download/\";\n$PG{\"fs\
a\"}{\"mode\"}=\"mcoffee\";\n$PG{\"fsa\"}{\"versio\
n\"}=\"1.15.3\";\n$PG{\"prank\"}{\"4_TCOFFEE\"}=\"\
PRANK\";\n$PG{\"prank\"}{\"type\"}=\"sequence_mult\
iple_aligner\";\n$PG{\"prank\"}{\"ADDRESS\"}=\"htt\
p://www.ebi.ac.uk/goldman-srv/prank/\";\n$PG{\"pra\
nk\"}{\"language\"}=\"C++\";\n$PG{\"prank\"}{\"lan\
guage2\"}=\"CXX\";\n$PG{\"prank\"}{\"source\"}=\"h\
ttp://www.ebi.ac.uk/goldman-srv/prank/src/prank/pr\
ank.src.100303.tgz\";\n$PG{\"prank\"}{\"mode\"}=\"\
mcoffee\";\n$PG{\"prank\"}{\"version\"}=\"100303\"\
;\n$PG{\"sap\"}{\"4_TCOFFEE\"}=\"SAP\";\n$PG{\"sap\
\"}{\"type\"}=\"structure_pairwise_aligner\";\n$PG\
{\"sap\"}{\"ADDRESS\"}=\"http://mathbio.nimr.mrc.a\
c.uk/wiki/Software\";\n$PG{\"sap\"}{\"language\"}=\
\"C\";\n$PG{\"sap\"}{\"language2\"}=\"C\";\n$PG{\"\
sap\"}{\"source\"}=\"http://mathbio.nimr.mrc.ac.uk\
/download/sap-1.1.1.tar.gz\";\n$PG{\"sap\"}{\"mode\
\"}=\"expresso,3dcoffee\";\n$PG{\"sap\"}{\"version\
\"}=\"1.1.1\";\n$PG{\"TMalign\"}{\"4_TCOFFEE\"}=\"\
TMALIGN\";\n$PG{\"TMalign\"}{\"type\"}=\"structure\
_pairwise_aligner\";\n$PG{\"TMalign\"}{\"ADDRESS\"\
}=\"http://zhang.bioinformatics.ku.edu/TM-align/TM\
align.f\";\n$PG{\"TMalign\"}{\"language\"}=\"Fortr\
an\";\n$PG{\"TMalign\"}{\"language2\"}=\"Fortran\"\
;\n$PG{\"TMalign\"}{\"source\"}=\"http://zhang.bio\
informatics.ku.edu/TM-align/TMalign.f\";\n$PG{\"TM\
align\"}{\"linux\"}=\"http://zhang.bioinformatics.\
ku.edu/TM-align/TMalign_32.gz\";\n$PG{\"TMalign\"}\
{\"mode\"}=\"expresso,3dcoffee\";\n$PG{\"TMalign\"\
}{\"version\"}=\"1.0\";\n$PG{\"mustang\"}{\"4_TCOF\
FEE\"}=\"MUSTANG\";\n$PG{\"mustang\"}{\"type\"}=\"\
structure_pairwise_aligner\";\n$PG{\"mustang\"}{\"\
ADDRESS\"}=\"http://www.cs.mu.oz.au/~arun/mustang\\
";\n$PG{\"mustang\"}{\"language\"}=\"C++\";\n$PG{\\
"mustang\"}{\"language2\"}=\"CXX\";\n$PG{\"mustang\
\"}{\"source\"}=\"http://ww2.cs.mu.oz.au/~arun/mus\
tang/mustang_v3.2.1.tgz\";\n$PG{\"mustang\"}{\"mod\
e\"}=\"expresso,3dcoffee\";\n$PG{\"mustang\"}{\"ve\
rsion\"}=\"3.2.1\";\n$PG{\"lsqman\"}{\"4_TCOFFEE\"\
}=\"LSQMAN\";\n$PG{\"lsqman\"}{\"type\"}=\"structu\
re_pairwise_aligner\";\n$PG{\"lsqman\"}{\"ADDRESS\\
"}=\"empty\";\n$PG{\"lsqman\"}{\"language\"}=\"emp\
ty\";\n$PG{\"lsqman\"}{\"language2\"}=\"empty\";\n\
$PG{\"lsqman\"}{\"source\"}=\"empty\";\n$PG{\"lsqm\
an\"}{\"update_action\"}=\"never\";\n$PG{\"lsqman\\
"}{\"mode\"}=\"expresso,3dcoffee\";\n$PG{\"align_p\
db\"}{\"4_TCOFFEE\"}=\"ALIGN_PDB\";\n$PG{\"align_p\
db\"}{\"type\"}=\"structure_pairwise_aligner\";\n$\
PG{\"align_pdb\"}{\"ADDRESS\"}=\"empty\";\n$PG{\"a\
lign_pdb\"}{\"language\"}=\"empty\";\n$PG{\"align_\
pdb\"}{\"language2\"}=\"empty\";\n$PG{\"align_pdb\\
"}{\"source\"}=\"empty\";\n$PG{\"align_pdb\"}{\"up\
date_action\"}=\"never\";\n$PG{\"align_pdb\"}{\"mo\
de\"}=\"expresso,3dcoffee\";\n$PG{\"fugueali\"}{\"\
4_TCOFFEE\"}=\"FUGUE\";\n$PG{\"fugueali\"}{\"type\\
"}=\"structure_pairwise_aligner\";\n$PG{\"fugueali\
\"}{\"ADDRESS\"}=\"http://www-cryst.bioc.cam.ac.uk\
/fugue/download.html\";\n$PG{\"fugueali\"}{\"langu\
age\"}=\"empty\";\n$PG{\"fugueali\"}{\"language2\"\
}=\"empty\";\n$PG{\"fugueali\"}{\"source\"}=\"empt\
y\";\n$PG{\"fugueali\"}{\"update_action\"}=\"never\
\";\n$PG{\"fugueali\"}{\"mode\"}=\"expresso,3dcoff\
ee\";\n$PG{\"dalilite.pl\"}{\"4_TCOFFEE\"}=\"DALIL\
ITEc\";\n$PG{\"dalilite.pl\"}{\"type\"}=\"structur\
e_pairwise_aligner\";\n$PG{\"dalilite.pl\"}{\"ADDR\
ESS\"}=\"built_in\";\n$PG{\"dalilite.pl\"}{\"ADDRE\
SS2\"}=\"http://www.ebi.ac.uk/Tools/webservices/se\
rvices/dalilite\";\n$PG{\"dalilite.pl\"}{\"languag\
e\"}=\"Perl\";\n$PG{\"dalilite.pl\"}{\"language2\"\
}=\"Perl\";\n$PG{\"dalilite.pl\"}{\"source\"}=\"em\
pty\";\n$PG{\"dalilite.pl\"}{\"update_action\"}=\"\
never\";\n$PG{\"dalilite.pl\"}{\"mode\"}=\"express\
o,3dcoffee\";\n$PG{\"probconsRNA\"}{\"4_TCOFFEE\"}\
=\"PROBCONSRNA\";\n$PG{\"probconsRNA\"}{\"type\"}=\
\"RNA_multiple_aligner\";\n$PG{\"probconsRNA\"}{\"\
ADDRESS\"}=\"http://probcons.stanford.edu/\";\n$PG\
{\"probconsRNA\"}{\"language\"}=\"C++\";\n$PG{\"pr\
obconsRNA\"}{\"language2\"}=\"CXX\";\n$PG{\"probco\
nsRNA\"}{\"source\"}=\"http://probcons.stanford.ed\
u/probconsRNA.tar.gz\";\n$PG{\"probconsRNA\"}{\"mo\
de\"}=\"mcoffee,rcoffee\";\n$PG{\"probconsRNA\"}{\\
"version\"}=\"1.0\";\n$PG{\"sfold\"}{\"4_TCOFFEE\"\
}=\"CONSAN\";\n$PG{\"sfold\"}{\"type\"}=\"RNA_pair\
wise_aligner\";\n$PG{\"sfold\"}{\"ADDRESS\"}=\"htt\
p://selab.janelia.org/software/consan/\";\n$PG{\"s\
fold\"}{\"language\"}=\"empty\";\n$PG{\"sfold\"}{\\
"language2\"}=\"empty\";\n$PG{\"sfold\"}{\"source\\
"}=\"empty\";\n$PG{\"sfold\"}{\"update_action\"}=\\
"never\";\n$PG{\"sfold\"}{\"mode\"}=\"rcoffee\";\n\
$PG{\"RNAplfold\"}{\"4_TCOFFEE\"}=\"RNAPLFOLD\";\n\
$PG{\"RNAplfold\"}{\"type\"}=\"RNA_secondarystruct\
ure_predictor\";\n$PG{\"RNAplfold\"}{\"ADDRESS\"}=\
\"http://www.tbi.univie.ac.at/~ivo/RNA/\";\n$PG{\"\
RNAplfold\"}{\"language\"}=\"C\";\n$PG{\"RNAplfold\
\"}{\"language2\"}=\"C\";\n$PG{\"RNAplfold\"}{\"so\
urce\"}=\"http://www.tbi.univie.ac.at/~ivo/RNA/Vie\
nnaRNA-1.7.2.tar.gz\";\n$PG{\"RNAplfold\"}{\"mode\\
"}=\"rcoffee,\";\n$PG{\"RNAplfold\"}{\"version\"}=\
\"1.7.2\";\n$PG{\"retree\"}{\"4_TCOFFEE\"}=\"PHYLI\
P\";\n$PG{\"retree\"}{\"type\"}=\"RNA_secondarystr\
ucture_predictor\";\n$PG{\"retree\"}{\"ADDRESS\"}=\
\"http://evolution.gs.washington.edu/phylip/\";\n$\
PG{\"retree\"}{\"language\"}=\"C\";\n$PG{\"retree\\
"}{\"language2\"}=\"C\";\n$PG{\"retree\"}{\"source\
\"}=\"http://evolution.gs.washington.edu/phylip/do\
wnload/phylip-3.69.tar.gz\";\n$PG{\"retree\"}{\"mo\
de\"}=\"trmsd,\";\n$PG{\"retree\"}{\"version\"}=\"\
3.69\";\n$PG{\"hmmtop\"}{\"4_TCOFFEE\"}=\"HMMTOP\"\
;\n$PG{\"hmmtop\"}{\"type\"}=\"protein_secondaryst\
ructure_predictor\";\n$PG{\"hmmtop\"}{\"ADDRESS\"}\
=\"www.enzim.hu/hmmtop/\";\n$PG{\"hmmtop\"}{\"lang\
uage\"}=\"C\";\n$PG{\"hmmtop\"}{\"language2\"}=\"C\
\";\n$PG{\"hmmtop\"}{\"source\"}=\"empty\";\n$PG{\\
"hmmtop\"}{\"update_action\"}=\"never\";\n$PG{\"hm\
mtop\"}{\"mode\"}=\"tcoffee\";\n$PG{\"gorIV\"}{\"4\
_TCOFFEE\"}=\"GOR4\";\n$PG{\"gorIV\"}{\"type\"}=\"\
protein_secondarystructure_predictor\";\n$PG{\"gor\
IV\"}{\"ADDRESS\"}=\"http://mig.jouy.inra.fr/logic\
iels/gorIV/\";\n$PG{\"gorIV\"}{\"language\"}=\"C\"\
;\n$PG{\"gorIV\"}{\"language2\"}=\"C\";\n$PG{\"gor\
IV\"}{\"source\"}=\"http://mig.jouy.inra.fr/logici\
els/gorIV/GOR_IV.tar.gz\";\n$PG{\"gorIV\"}{\"updat\
e_action\"}=\"never\";\n$PG{\"gorIV\"}{\"mode\"}=\\
"tcoffee\";\n$PG{\"wublast.pl\"}{\"4_TCOFFEE\"}=\"\
EBIWUBLASTc\";\n$PG{\"wublast.pl\"}{\"type\"}=\"pr\
otein_homology_predictor\";\n$PG{\"wublast.pl\"}{\\
"ADDRESS\"}=\"built_in\";\n$PG{\"wublast.pl\"}{\"A\
DDRESS2\"}=\"http://www.ebi.ac.uk/Tools/webservice\
s/services/wublast\";\n$PG{\"wublast.pl\"}{\"langu\
age\"}=\"Perl\";\n$PG{\"wublast.pl\"}{\"language2\\
"}=\"Perl\";\n$PG{\"wublast.pl\"}{\"source\"}=\"em\
pty\";\n$PG{\"wublast.pl\"}{\"update_action\"}=\"n\
ever\";\n$PG{\"wublast.pl\"}{\"mode\"}=\"psicoffee\
,expresso,accurate\";\n$PG{\"blastpgp.pl\"}{\"4_TC\
OFFEE\"}=\"EBIBLASTPGPc\";\n$PG{\"blastpgp.pl\"}{\\
"type\"}=\"protein_homology_predictor\";\n$PG{\"bl\
astpgp.pl\"}{\"ADDRESS\"}=\"built_in\";\n$PG{\"bla\
stpgp.pl\"}{\"ADDRESS2\"}=\"http://www.ebi.ac.uk/T\
ools/webservices/services/blastpgp\";\n$PG{\"blast\
pgp.pl\"}{\"language\"}=\"Perl\";\n$PG{\"blastpgp.\
pl\"}{\"language2\"}=\"Perl\";\n$PG{\"blastpgp.pl\\
"}{\"source\"}=\"empty\";\n$PG{\"blastpgp.pl\"}{\"\
update_action\"}=\"never\";\n$PG{\"blastpgp.pl\"}{\
\"mode\"}=\"psicoffee,expresso,accurate\";\n$PG{\"\
blastcl3\"}{\"4_TCOFFEE\"}=\"NCBIWEBBLAST\";\n$PG{\
\"blastcl3\"}{\"type\"}=\"protein_homology_predict\
or\";\n$PG{\"blastcl3\"}{\"ADDRESS\"}=\"ftp://ftp.\
ncbi.nih.gov/blast/executables/LATEST\";\n$PG{\"bl\
astcl3\"}{\"language\"}=\"C\";\n$PG{\"blastcl3\"}{\
\"language2\"}=\"C\";\n$PG{\"blastcl3\"}{\"source\\
"}=\"empty\";\n$PG{\"blastcl3\"}{\"update_action\"\
}=\"never\";\n$PG{\"blastcl3\"}{\"mode\"}=\"psicof\
fee,expresso,3dcoffee\";\n$PG{\"blastpgp\"}{\"4_TC\
OFFEE\"}=\"NCBIBLAST\";\n$PG{\"blastpgp\"}{\"type\\
"}=\"protein_homology_predictor\";\n$PG{\"blastpgp\
\"}{\"ADDRESS\"}=\"ftp://ftp.ncbi.nih.gov/blast/ex\
ecutables/LATEST\";\n$PG{\"blastpgp\"}{\"language\\
"}=\"C\";\n$PG{\"blastpgp\"}{\"language2\"}=\"C\";\
\n$PG{\"blastpgp\"}{\"source\"}=\"empty\";\n$PG{\"\
blastpgp\"}{\"update_action\"}=\"never\";\n$PG{\"b\
lastpgp\"}{\"mode\"}=\"psicoffee,expresso,3dcoffee\
\";\n$PG{\"SOAP::Lite\"}{\"4_TCOFFEE\"}=\"SOAPLITE\
\";\n$PG{\"SOAP::Lite\"}{\"type\"}=\"library\";\n$\
PG{\"SOAP::Lite\"}{\"ADDRESS\"}=\"http://cpansearc\
h.perl.org/src/MKUTTER/SOAP-Lite-0.710.08/Makefile\
.PL\";\n$PG{\"SOAP::Lite\"}{\"language\"}=\"Perl\"\
;\n$PG{\"SOAP::Lite\"}{\"language2\"}=\"Perl\";\n$\
PG{\"SOAP::Lite\"}{\"source\"}=\"empty\";\n$PG{\"b\
lastpgp\"}{\"update_action\"}=\"never\";\n$PG{\"SO\
AP::Lite\"}{\"mode\"}=\"none\";\n$PG{\"XML::Simple\
\"}{\"4_TCOFFEE\"}=\"XMLSIMPLE\";\n$PG{\"XML::Simp\
le\"}{\"type\"}=\"library\";\n$PG{\"XML::Simple\"}\
{\"ADDRESS\"}=\"http://search.cpan.org/~grantm/XML\
-Simple-2.18/lib/XML/Simple.pm\";\n$PG{\"XML::Simp\
le\"}{\"language\"}=\"Perl\";\n$PG{\"XML::Simple\"\
}{\"language2\"}=\"Perl\";\n$PG{\"XML::Simple\"}{\\
"source\"}=\"empty\";\n$PG{\"XML::Simple\"}{\"mode\
\"}=\"psicoffee,expresso,accurate\";\n$MODE{\"tcof\
fee\"}{\"name\"}=\"tcoffee\";\n$MODE{\"rcoffee\"}{\
\"name\"}=\"rcoffee\";\n$MODE{\"3dcoffee\"}{\"name\
\"}=\"3dcoffee\";\n$MODE{\"mcoffee\"}{\"name\"}=\"\
mcoffee\";\n$MODE{\"expresso\"}{\"name\"}=\"expres\
so\";\n$MODE{\"trmsd\"}{\"name\"}=\"trmsd\";\n$MOD\
E{\"accurate\"}{\"name\"}=\"accurate\";\n$MODE{\"s\
eq_reformat\"}{\"name\"}=\"seq_reformat\";\n\n\n$P\
G{C}{compiler}=\"gcc\";\n$PG{C}{compiler_flag}=\"C\
C\";\n$PG{C}{options}=\"\";\n$PG{C}{options_flag}=\
\"CFLAGS\";\n$PG{C}{type}=\"compiler\";\n\n$PG{\"C\
XX\"}{compiler}=\"g++\";\n$PG{\"CXX\"}{compiler_fl\
ag}=\"CXX\";\n$PG{\"CXX\"}{options}=\"\";\n$PG{\"C\
XX\"}{options_flag}=\"CXXFLAGS\";\n$PG{CXX}{type}=\
\"compiler\";\n\n$PG{\"CPP\"}{compiler}=\"g++\";\n\
$PG{\"CPP\"}{compiler_flag}=\"CPP\";\n$PG{\"CPP\"}\
{options}=\"\";\n$PG{\"CPP\"}{options_flag}=\"CPPF\
LAGS\";\n$PG{CPP}{type}=\"compiler\";\n\n$PG{\"GPP\
\"}{compiler}=\"g++\";\n$PG{\"GPP\"}{compiler_flag\
}=\"GPP\";\n$PG{\"GPP\"}{options}=\"\";\n$PG{\"GPP\
\"}{options_flag}=\"CFLAGS\";\n$PG{GPP}{type}=\"co\
mpiler\";\n\n$PG{Fortran}{compiler}=\"g77\";\n$PG{\
Fortran}{compiler_flag}=\"FCC\";\n$PG{Fortran}{typ\
e}=\"compiler\";\n\n$PG{Perl}{compiler}=\"CPAN\";\\
n$PG{Perl}{type}=\"compiler\";\n\n$SUPPORTED_OS{ma\
cox}=\"Macintosh\";\n$SUPPORTED_OS{linux}=\"Linux\\
";\n$SUPPORTED_OS{windows}=\"Cygwin\";\n\n\n\n$MOD\
E{t_coffee}{description}=\" for regular multiple s\
equence alignments\";\n$MODE{rcoffee} {description\
}=\" for RNA multiple sequence alignments\";\n\n$M\
ODE{psicoffee} {description}=\" for Homology Exten\
ded multiple sequence alignments\";\n$MODE{express\
o}{description}=\" for very accurate structure bas\
ed multiple sequence alignments\";\n$MODE{\"3dcoff\
ee\"}{description}=\" for multiple structure align\
ments\";\n$MODE{mcoffee} {description}=\" for comb\
ining alternative multiple sequence alignment pack\
ages\\n------- into a unique meta-package. The ins\
taller will upload several MSA packages and compil\
e them\\n\n\";\n\n\n&post_process_PG();\nreturn;\n\
}\n\nsub post_process_PG\n  {\n    my $p;\n    \n \
   %PG=&name2dname (%PG);\n    %MODE=&name2dname(%\
MODE);\n    foreach $p (keys(%PG)){if ( $PG{$p}{ty\
pe} eq \"compiler\"){$PG{$p}{update_action}=\"neve\
r\";}}\n    \n  }\n\nsub name2dname\n  {\n    my (\
%L)=(@_);\n    my ($l, $ml);\n    \n    foreach my\
 $pg (keys(%L))\n      {\n	$l=length ($pg);\n	if (\
 $l>$ml){$ml=$l;}\n      }\n    $ml+=1;\n    forea\
ch my $pg (keys(%L))\n      {\n	my $name;\n	$l=$ml\
-length ($pg);\n	$name=$pg;\n	for ( $b=0; $b<$l; $\
b++)\n	  {\n	    $name .=\" \";\n	  }\n	$L{$pg}{dn\
ame}=$name;\n      }\n    return %L;\n  }\n\nsub e\
nv_file2putenv\n  {\n    my $f=@_[0];\n    my $F=n\
ew FileHandle;\n    my $n;\n    \n    open ($F, \"\
$f\");\n    while (<$F>)\n      {\n	my $line=$_;\n\
	my($var, $value)=($_=~/(\\S+)\\=(\\S*)/);\n	$ENV{\
$var}=$value;\n	$ENV_SET{$var}=1;\n	$n++;\n      }\
\n    close ($F);\n    return $n;\n  }\n\nsub repl\
ace_line_in_file\n  {\n    my ($file, $wordin, $wo\
rdout)=@_;\n    my $O=new FileHandle;\n    my $I=n\
ew FileHandle;\n    my $l;\n    if (!-e $file){ret\
urn;}\n    \n    system (\"mv $file $file.old\");\\
n    open ($O, \">$file\");\n    open ($I, \"$file\
.old\");\n    while (<$I>)\n      {\n	$l=$_;\n	if \
(!($l=~/$wordin/)){print $O \"$l\";}\n	elsif ( $wo\
rdout ne \"\"){$l=~s/$wordin/$wordout/g;print $O \\
"$l\";}\n      }\n    close ($O);\n    close ($I);\
\n    return;\n  }\n\nsub add_C_libraries\n  {\n  \
 my ($file,$first,@list)=@_;\n   \n    my $O=new F\
ileHandle;\n    my $I=new FileHandle;\n    my ($l,\
$anchor);\n    if (!-e $file){return;}\n   \n    $\
anchor=\"#include <$first>\";\n	 \n    system (\"m\
v $file $file.old\");\n    open ($O, \">$file\");\\
n    open ($I, \"$file.old\");\n    while (<$I>)\n\
      {\n	$l=$_;\n	print $O \"$l\";\n	if (!($l=~/$\
anchor/))\n	   {\n	    \n	    foreach my $lib (@li\
st)\n	       {\n                  print $O \"#incl\
ude <$lib>\\n\";\n	       }\n           }\n      }\
\n    close ($O);\n    close ($I);\n    return;\n \
   }\n","use Env;\nuse Cwd;\n@suffix=(\"tmp\", \"t\
emp\", \"cache\", \"t_coffee\", \"core\", \"tcoffe\
e\");\n\nif ($#ARGV==-1)\n  {\n    print \"clean_c\
ache.pl -file <file to add in -dir> -dir=<dir> -si\
ze=<value in Mb>\\n0: unlimited -1 always.\\nWill \
only clean directories matching:[\";\n    foreach \
$k(@suffix){print \"*$k* \";}\n    print \"]\\n\";\
\n    exit (EXIT_FAILURE);\n  }\n\n$cl=join (\" \"\
,@ARGV);\nif (($cl=~/\\-no_action/))\n  {\n    exi\
t (EXIT_SUCCESS);\n  }\n\nif (($cl=~/\\-debug/))\n\
  {\n    $DEBUG=1;\n  }\nelse\n  {\n    $DEBUG=0;\\
n  }\n\nif (($cl=~/\\-dir=(\\S+)/))\n  {\n    $dir\
=$1;\n  }\nelse\n  {\n    $dir=\"./\";\n  }\n\nif \
($cl=~/\\-file=(\\S+)/)\n  {\n    $file=$1;\n  }\n\
else\n  {\n    $file=0;\n  }\n\nif ($cl=~/\\-size=\
(\\S+)/)\n  {\n    $max_size=$1;\n  }\nelse\n  {\n\
    $max_size=0;#unlimited\n  }\nif ($cl=~/\\-forc\
e/)\n  {\n    $force=1;\n  }\nelse\n  {\n    $forc\
e=0;\n  }\n\nif ($cl=~/\\-age=(\\S+)/)\n  {\n    $\
max_age=$1;\n  }\nelse\n  {\n    $max_age=0;#unlim\
ited\n  }\n\n$max_size*=1000000;\nif ( ! -d $dir)\\
n  {\n    print STDERR \"\\nCannot process $dir: d\
oes not exist \\n\";\n    exit (EXIT_FAILURE);\n  \
}\n\nif ( !($dir=~/^\\//))\n  {\n    $base=cwd();\\
n    $dir=\"$base/$dir\";\n  }\n\n$proceed=0;\nfor\
each $s (@suffix)\n  {\n    \n    if (($dir=~/$s/)\
){$proceed=1;}\n    $s=uc ($s);\n    if (($dir=~/$\
s/)){$proceed=1;}\n  }\nif ( $proceed==0)\n  {\n  \
  print STDERR \"Clean_cache.pl can only clean dir\
ectories whose absolute path name contains the fol\
lowing strings:\";\n    foreach $w (@suffix) {prin\
t STDERR \"$w \";$w=lc($w); print STDERR \"$w \";}\
\n    print STDERR \"\\nCannot process $dir\\n\";\\
n    exit (EXIT_FAILURE);\n  }\n\n$name_file=\"$di\
r/name_file.txt\";\n$size_file=\"$dir/size_file.tx\
t\";\nif ( $force){&create_ref_file ($dir,$name_fi\
le,$size_file);}\nif ($file){&add_file ($dir, $nam\
e_file, $size_file, $file);}\n&clean_dir ($dir, $n\
ame_file, $size_file, $max_size,$max_age);\nexit (\
EXIT_SUCCESS);\n\nsub clean_dir \n  {\n    my ($di\
r, $name_file, $size_file, $max_size, $max_age)=@_\
;\n    my ($tot_size, $size, $f, $s);\n\n  \n    $\
tot_size=&get_tot_size ($dir, $name_file, $size_fi\
le);\n\n    if ( $tot_size<=$max_size){return ;}\n\
    else {$max_size/=2;}\n    \n    #recreate the \
name file in case some temprary files have not bee\
n properly registered\n    &create_ref_file ($dir,\
 $name_file, $size_file, $max_age);\n  \n    $new_\
name_file=&vtmpnam();\n    open (R, \"$name_file\"\
);\n    open (W, \">$new_name_file\");\n    while \
(<R>)\n      {\n	my $line=$_;\n	\n	($f, $s)=($line\
=~/(\\S+) (\\S+)/);\n	if ( !($f=~/\\S/)){next;}\n	\
\n	elsif ($max_size && $tot_size>=$max_size && !($\
f=~/name_file/))\n	  {\n	    remove ( \"$dir/$f\")\
;\n	    $tot_size-=$s;\n	  }\n	elsif ( $max_age &&\
 -M(\"$dir/$f\")>=$max_age)\n	  {\n	    remove ( \\
"$dir/$f\");\n	    $tot_size-=$s;\n	  }\n	else\n	 \
 {\n	    print W \"$f $s\\n\";\n	  }\n      }\n   \
 close (R);\n    close (W);\n    open (F, \">$size\
_file\");\n    print F \"$tot_size\";\n    if ( -e\
 $new_name_file){`mv $new_name_file $name_file`;}\\
n    close (F);\n  }\nsub get_tot_size\n  {\n    m\
y ($dir, $name_file, $size_file)=@_;\n    my $size\
;\n    \n    if ( !-d $dir){return 0;}\n    if ( !\
-e $name_file)\n      {\n	\n	&create_ref_file ($di\
r, $name_file, $size_file);\n      }\n    open (F,\
 \"$size_file\");\n    $size=<F>;\n    close (F);\\
n    chomp ($size);\n    return $size;\n  }\nsub s\
ize \n  {\n    my $f=@_[0];\n\n    if ( !-d $f){re\
turn -s($f);}\n    else {return &dir2size($f);}\n \
 }\nsub dir2size\n  {\n    my $d=@_[0];\n    my ($\
s, $f);\n    \n    if ( !-d $d) {return 0;}\n    \\
n    foreach $f (&dir2list ($d))\n      {\n	if ( -\
d $f){$s+=&dir2size (\"$d/$f\");}\n	else {$s+= -s \
\"$dir/$f\";}\n      }\n    return $s;\n  }\n\nsub\
 remove \n  {\n    my $file=@_[0];\n    my ($f);\n\
    \n    debug_print( \"--- $file ---\\n\");\n   \
 if (($file eq \".\") || ($file eq \"..\") || ($fi\
le=~/\\*/)){return EXIT_FAILURE;}\n    elsif ( !-d\
 $file)\n      {\n	debug_print (\"unlink $file\\n\\
");\n	if (-e $file){unlink ($file);}\n      }\n   \
 elsif ( -d $file)\n      {\n	debug_print (\"+++++\
+++ $file +++++++\\n\");\n	foreach $f (&dir2list($\
file))\n	  {\n	    &remove (\"$file/$f\");\n	  }\n\
	debug_print (\"rmdir $file\\n\");\n	rmdir $file;\\
n      }\n    else\n      {\n	debug_print (\"?????\
???? $file ????????\\n\");\n      }\n    return EX\
IT_SUCCESS;\n  }\n\nsub dir2list\n  {\n    my $dir\
=@_[0];\n    my (@list1, @list2,@list3, $l);\n\n  \
  opendir (DIR,$dir);\n    @list1=readdir (DIR);\n\
    closedir (DIR);\n    \n    foreach $l (@list1)\
\n      {\n	if ( $l ne \".\" && $l ne \"..\"){@lis\
t2=(@list2, $l);}\n      }\n    @list3 = sort { (-\
M \"$dir/$list2[$b]\") <=> (-M \"$dir/$list2[$a]\"\
)} @list2;\n    return @list3;\n    \n  }\n\nsub d\
ebug_print\n  {\n    \n    if ($DEBUG==1){print @_\
;}\n    \n  }\nsub create_ref_file\n  {\n    my ($\
dir,$name_file,$size_file)=@_;\n    my ($f, $s, $t\
ot_size, @l);\n    \n    if ( !-d $dir){return;}\n\
    \n    @l=&dir2list ($dir);\n    open (F, \">$n\
ame_file\");\n    foreach $f (@l)\n      {\n	$s=&s\
ize(\"$dir/$f\");\n	$tot_size+=$s;\n	print F \"$f \
$s\\n\";\n      }\n    &myecho ($tot_size, \">$siz\
e_file\");\n    close (F);\n  }\nsub add_file \n  \
{\n    my ($dir,$name_file,$size_file,$file)=@_;\n\
    my ($s, $tot_size);\n    \n    if ( !-d $dir) \
  {return;}\n    if ( !-e \"$dir/$file\" ) {return\
;}\n    if ( !-e $name_file){&create_ref_file ($di\
r,$name_file,$size_file);}\n					    \n    $s=&siz\
e(\"$dir/$file\");\n    open (F, \">>$name_file\")\
;\n    print F \"$file\\n\";\n    close (F);\n\n  \
  $tot_size=&get_tot_size ($dir,$name_file,$size_f\
ile);\n    $tot_size+=$s;\n    &myecho ($tot_size,\
 \">$size_file\");\n    \n  }\n	\nsub myecho\n  {\\
n    my ($string, $file)=@_;\n    open (ECHO, $fil\
e) || die;\n    print ECHO \"$string\";\n    close\
 (ECHO);\n  }\n    \n		\n	\nsub vtmpnam\n  {\n    \
my $tmp_file_name;\n    $tmp_name_counter++;\n    \
$tmp_file_name=\"tmp_file_for_clean_cache_pdb$$.$t\
mp_name_counter\";\n    $tmp_file_list[$ntmp_file+\
+]=$tmp_file_name;\n    if ( -e $tmp_file_name) {r\
eturn &vtmpnam ();}\n    else {return $tmp_file_na\
me;}\n  }\n","\nmy $address=\"http://www.tcoffee.o\
rg/Projects/Datasets/NatureMethodsDataset.tar.gz\"\
;\nmy $out=\"NatureMethodsDataset.tar.gz\";\n&url2\
file ($address,$out);\n\nif ( -e $out)\n  {\n    \\
n    system (\"gunzip NatureMethodsDataset.tar.gz\\
");\n    system (\"tar -xvf NatureMethodsDataset.t\
ar\");\n    \n    print \"Your Data Set is in the \
Folder NatureMethodsDataset\\n\";\n  }\nelse \n  {\
\n    print \"Could not Download Dataset --- Web s\
ite may be down -- Try again later\\n\";\n  }\n\n\\
n\n\nsub url2file\n{\n    my ($address, $out, $wge\
t_arg, $curl_arg)=(@_);\n    my ($pg, $flag, $r, $\
arg, $count);\n    \n    if (!$CONFIGURATION){&che\
ck_configuration (\"wget\", \"INTERNET\", \"gzip\"\
);$CONFIGURATION=1;}\n    \n    if (&pg_is_install\
ed (\"wget\"))   {$pg=\"wget\"; $flag=\"-O\";$arg=\
$wget_arg;}\n    elsif (&pg_is_installed (\"curl\"\
)){$pg=\"curl\"; $flag=\"-o\";$arg=$curl_arg;}\n  \
  return system (\"$pg $address $flag $out>/dev/nu\
ll 2>/dev/null\");\n\n}\n\nsub pg_is_installed\n  \
{\n    my @ml=@_;\n    my $r, $p, $m;\n    my $sup\
ported=0;\n    \n    my $p=shift (@ml);\n    if ($\
p=~/::/)\n      {\n	if (system (\"perl -M$p -e 1\"\
)==$EXIT_SUCCESS){return 1;}\n	else {return 0;}\n \
     }\n    else\n      {\n	$r=`which $p 2>/dev/nu\
ll`;\n	if ($r eq \"\"){return 0;}\n	else {return 1\
;}\n      }\n  }\nsub check_configuration \n    {\\
n      my @l=@_;\n      my $v;\n      foreach my $\
p (@l)\n	{\n	  \n	  if   ( $p eq \"EMAIL\")\n	    \
{ \n	      if ( !($EMAIL=~/@/))\n		{\n		  exit (EX\
IT_FAILURE);\n		}\n	    }\n	  elsif( $p eq \"INTER\
NET\")\n	    {\n	      if ( !&check_internet_conne\
ction())\n		{\n		  exit (EXIT_FAILURE);\n		}\n	   \
 }\n	  elsif( $p eq \"wget\")\n	    {\n	      if (\
!&pg_is_installed (\"wget\") && !&pg_is_installed \
(\"curl\"))\n		{\n		  exit (EXIT_FAILURE);\n		}\n	\
    }\n	  elsif( !(&pg_is_installed ($p)))\n	    {\
\n	      exit (EXIT_FAILURE);\n	    }\n	}\n      r\
eturn 1;\n    }\nsub check_internet_connection\n  \
{\n    my $internet;\n    my $tmp;\n    &check_con\
figuration ( \"wget\"); \n    \n    $tmp=&vtmpnam \
();\n    \n    if     (&pg_is_installed    (\"wget\
\")){`wget www.google.com -O$tmp >/dev/null 2>/dev\
/null`;}\n    elsif  (&pg_is_installed    (\"curl\\
")){`curl www.google.com -o$tmp >/dev/null 2>/dev/\
null`;}\n    \n    if ( !-e $tmp || -s $tmp < 10){\
$internet=0;}\n    else {$internet=1;}\n    if (-e\
 $tmp){unlink $tmp;}\n\n    return $internet;\n  }\
\n\nsub vtmpnam\n      {\n	my $r=rand(100000);\n	m\
y $f=\"file.$r.$$\";\n	while (-e $f)\n	  {\n	    $\
f=vtmpnam();\n	  }\n	push (@TMPFILE_LIST, $f);\n	r\
eturn $f;\n      }\n\n","\n$t_coffee=\"t_coffee\";\
\n\nforeach $value ( @ARGV)\n  {\n    $seq_file=$s\
eq_file.\" \".$value;\n  }\n\n$name=$ARGV[0];\n$na\
me=~s/\\.[^\\.]*$//;\n$lib_name=\"$name.mocca_lib\\
";\n$type=`t_coffee $seq_file -get_type -quiet`;\n\
chop ($type);\n\nif ( $type eq \"PROTEIN\"){$lib_m\
ode=\"lalign_rs_s_pair -lalign_n_top 20\";}\nelsif\
 ( $type eq\"DNA\"){$lib_mode=\"lalign_rs_s_dna_pa\
ir -lalign_n_top 40\";}\n\nif ( !(-e $lib_name))\n\
  {\n	  \n  $command=\"$t_coffee -mocca -seq_weigh\
t=no -cosmetic_penalty=0 -mocca_interactive -in $l\
ib_mode -out_lib $lib_name -infile $seq_file\";\n \
 \n  }\nelsif ( (-e $lib_name))\n  {\n  $command=\\
"$t_coffee -mocca -seq_weight=no -cosmetic_penalty\
=0 -mocca_interactive -in $lib_name -infile $seq_f\
ile\";\n  \n  }\n\nsystem ($command);\n\nexit;\n\n\
","my $WSDL = 'http://www.ebi.ac.uk/Tools/webservi\
ces/wsdl/WSDaliLite.wsdl';\n\nuse SOAP::Lite;\nuse\
 Data::Dumper;\nuse Getopt::Long qw(:config no_ign\
ore_case bundling);\nuse File::Basename;\n\nmy $ch\
eckInterval = 5;\n\nmy %params=(\n	    'async' => \
'1', # Use async mode and simulate sync mode in cl\
ient\n	    );\nGetOptions(\n    'pdb1=s'     => \\\
$params{'sequence1'},\n    'chainid1=s' => \\$para\
ms{'chainid1'},\n    'pdb2=s'     => \\$params{'se\
quence2'},\n    'chainid2=s' => \\$params{'chainid\
2'},\n    \"help|h\"	 => \\$help, # Usage info\n  \
  \"async|a\"	 => \\$async, # Asynchronous submiss\
ion\n    \"polljob\"	 => \\$polljob, # Get results\
\n    \"status\"	 => \\$status, # Get status\n    \
\"jobid|j=s\"  => \\$jobid, # JobId\n    \"email|S\
=s\"  => \\$params{email}, # E-mail address\n    \\
"trace\"      => \\$trace, # SOAP messages\n    \"\
sequence=s\" => \\$sequence, # Input PDB\n    );\n\
\nmy $scriptName = basename($0, ());\nif($help) {\\
n    &usage();\n    exit(0);\n}\n\nif($trace) {\n \
   print \"Tracing active\\n\";\n    SOAP::Lite->i\
mport(+trace => 'debug');\n}\n\nmy $soap = SOAP::L\
ite\n    ->service($WSDL)\n    ->on_fault(sub {\n \
       my $soap = shift;\n        my $res = shift;\
\n        # Throw an exception for all faults\n   \
     if(ref($res) eq '') {\n            die($res);\
\n        } else {\n            die($res->faultstr\
ing);\n        }\n        return new SOAP::SOM;\n \
   }\n               );\n\nif( !($polljob || $stat\
us) &&\n    !( defined($params{'sequence1'}) && de\
fined($params{'sequence2'}) )\n    ) {\n    print \
STDERR 'Error: bad option combination', \"\\n\";\n\
    &usage();\n    exit(1);\n}\nelsif($polljob && \
defined($jobid)) {\n    print \"Getting results fo\
r job $jobid\\n\";\n    getResults($jobid);\n}\nel\
sif($status && defined($jobid)) {\n    print STDER\
R \"Getting status for job $jobid\\n\";\n    my $r\
esult = $soap->checkStatus($jobid);\n    print STD\
OUT \"$result\", \"\\n\";\n    if($result eq 'DONE\
') {\n	print STDERR \"To get results: $scriptName \
--polljob --jobid $jobid\\n\";\n    }\n}\nelse {\n\
    if(-f $params{'sequence1'}) {\n	$params{'seque\
nce1'} = read_file($params{'sequence1'});\n    }\n\
    if(-f $params{'sequence2'}) {\n	$params{'seque\
nce2'} = read_file($params{'sequence2'});\n    }\n\
\n    my $jobid;\n    my $paramsData = SOAP::Data-\
>name('params')->type(map=>\\%params);\n    # For \
SOAP::Lite 0.60 and earlier parameters are passed \
directly\n    if($SOAP::Lite::VERSION eq '0.60' ||\
 $SOAP::Lite::VERSION =~ /0\\.[1-5]/) {\n        $\
jobid = $soap->runDaliLite($paramsData);\n    }\n \
   # For SOAP::Lite 0.69 and later parameter handl\
ing is different, so pass\n    # undef's for templ\
ated params, and then pass the formatted args.\n  \
  else {\n        $jobid = $soap->runDaliLite(unde\
f,\n				     $paramsData);\n    }\n\n    if (defin\
ed($async)) {\n	print STDOUT $jobid, \"\\n\";\n   \
     print STDERR \"To check status: $scriptName -\
-status --jobid $jobid\\n\";\n    } else { # Synch\
ronous mode\n        print STDERR \"JobId: $jobid\\
\n\";\n        sleep 1;\n        getResults($jobid\
);\n    }\n}\n\nsub clientPoll($) {\n    my $jobid\
 = shift;\n    my $result = 'PENDING';\n    # Chec\
k status and wait if not finished\n    #print STDE\
RR \"Checking status: $jobid\\n\";\n    while($res\
ult eq 'RUNNING' || $result eq 'PENDING') {\n     \
   $result = $soap->checkStatus($jobid);\n        \
print STDERR \"$result\\n\";\n        if($result e\
q 'RUNNING' || $result eq 'PENDING') {\n          \
  # Wait before polling again.\n            sleep \
$checkInterval;\n        }\n    }\n}\n\nsub getRes\
ults($) {\n    $jobid = shift;\n    # Check status\
, and wait if not finished\n    clientPoll($jobid)\
;\n    # Use JobId if output file name is not defi\
ned\n    unless(defined($outfile)) {\n        $out\
file=$jobid;\n    }\n    # Get list of data types\\
n    my $resultTypes = $soap->getResults($jobid);\\
n    # Get the data and write it to a file\n    if\
(defined($outformat)) { # Specified data type\n   \
     my $selResultType;\n        foreach my $resul\
tType (@$resultTypes) {\n            if($resultTyp\
e->{type} eq $outformat) {\n                $selRe\
sultType = $resultType;\n            }\n        }\\
n        $res=$soap->poll($jobid, $selResultType->\
{type});\n        write_file($outfile.'.'.$selResu\
ltType->{ext}, $res);\n    } else { # Data types a\
vailable\n        # Write a file for each output t\
ype\n        for my $resultType (@$resultTypes){\n\
            #print \"Getting $resultType->{type}\\\
n\";\n            $res=$soap->poll($jobid, $result\
Type->{type});\n            write_file($outfile.'.\
'.$resultType->{ext}, $res);\n        }\n    }\n}\\
n\nsub read_file($) {\n    my $filename = shift;\n\
    open(FILE, $filename);\n    my $content;\n    \
my $buffer;\n    while(sysread(FILE, $buffer, 1024\
)) {\n	$content.= $buffer;\n    }\n    close(FILE)\
;\n    return $content;\n}\n\nsub write_file($$) {\
\n    my ($tmp,$entity) = @_;\n    print STDERR \"\
Creating result file: \".$tmp.\"\\n\";\n    unless\
(open (FILE, \">$tmp\")) {\n	return 0;\n    }\n   \
 syswrite(FILE, $entity);\n    close (FILE);\n    \
return 1;\n}\n\nsub usage {\n    print STDERR <<EO\
F\nDaliLite\n========\n\nPairwise comparison of pr\
otein structures\n\n[Required]\n\n  --pdb1        \
        : str  : PDB ID for structure 1\n  --pdb2 \
               : str  : PDB ID for structure 2\n\n\
[Optional]\n\n  --chain1              : str  : Cha\
in identifer in structure 1\n  --chain2           \
   : str  : Chain identifer in structure 2\n\n[Gen\
eral]\n\n  -h, --help            :      : prints t\
his help text\n  -S, --email           : str  : us\
er email address\n  -a, --async           :      :\
 asynchronous submission\n      --status          \
:      : poll for the status of a job\n      --pol\
ljob         :      : poll for the results of a jo\
b\n  -j, --jobid           : str  : jobid for an a\
synchronous job\n  -O, --outfile         : str  : \
file name for results (default is jobid)\n      --\
trace	        :      : show SOAP messages being in\
terchanged \n\nSynchronous job:\n\n  The results/e\
rrors are returned as soon as the job is finished.\
\n  Usage: $scriptName --email <your\\@email> [opt\
ions] pdbFile [--outfile string]\n  Returns: saves\
 the results to disk\n\nAsynchronous job:\n\n  Use\
 this if you want to retrieve the results at a lat\
er time. The results \n  are stored for up to 24 h\
ours. \n  The asynchronous submission mode is reco\
mmended when users are submitting \n  batch jobs o\
r large database searches	\n  Usage: $scriptName -\
-email <your\\@email> --async [options] pdbFile\n \
 Returns: jobid\n\n  Use the jobid to query for th\
e status of the job. \n  Usage: $scriptName --stat\
us --jobid <jobId>\n  Returns: string indicating t\
he status of the job:\n    DONE - job has finished\
\n    RUNNING - job is running\n    NOT_FOUND - jo\
b cannot be found\n    ERROR - the jobs has encoun\
tered an error\n\n  When done, use the jobid to re\
trieve the status of the job. \n  Usage: $scriptNa\
me --polljob --jobid <jobId> [--outfile string]\n\\
n[Help]\n\n  For more detailed help information re\
fer to\n  http://www.ebi.ac.uk/DaliLite/\nEOF\n;\n\
}\n","my $WSDL = 'http://www.ebi.ac.uk/Tools/webse\
rvices/wsdl/WSWUBlast.wsdl';\n\nuse strict;\nuse S\
OAP::Lite;\nuse Getopt::Long qw(:config no_ignore_\
case bundling);\nuse File::Basename;\n\nmy $checkI\
nterval = 15;\n\nmy $numOpts = scalar(@ARGV);\nmy \
($outfile, $outformat, $help, $async, $polljob, $s\
tatus, $ids, $jobid, $trace, $sequence);\nmy %para\
ms= ( # Defaults\n	      'async' => 1, # Force int\
o async mode\n	      'exp' => 10.0, # E-value thre\
shold\n	      'numal' => 50, # Maximum number of a\
lignments\n	      'scores' => 100, # Maximum numbe\
r of scores\n            );\nGetOptions( # Map the\
 options into variables\n    \"program|p=s\"     =\
> \\$params{program}, # BLAST program\n    \"datab\
ase|D=s\"    => \\$params{database}, # Search data\
base\n    \"matrix|m=s\"      => \\$params{matrix}\
, # Scoring matrix\n    \"exp|E=f\"         => \\$\
params{exp}, # E-value threshold\n    \"echofilter\
|e\"    => \\$params{echofilter}, # Display filter\
ed sequence\n    \"filter|f=s\"      => \\$params{\
filter}, # Low complexity filter name\n    \"align\
ments|b=i\"  => \\$params{numal}, # Number of alig\
nments\n    \"scores|s=i\"      => \\$params{score\
s}, # Number of scores\n    \"sensitivity|S=s\" =>\
 \\$params{sensitivity}, # Search sensitivity\n   \
 \"sort|t=s\"	      => \\$params{sort}, # Sort hit\
s by...\n    \"stats|T=s\"       => \\$params{stat\
s}, # Scoring statistic to use\n    \"strand|d=s\"\
      => \\$params{strand}, # Strand to use in DNA\
 vs. DNA search\n    \"topcombon|c=i\"   => \\$par\
ams{topcombon}, # Consistent sets of HSPs\n    \"o\
utfile=s\"       => \\$outfile, # Output file\n   \
 \"outformat|o=s\"   => \\$outformat, # Output for\
mat\n    \"help|h\"	      => \\$help, # Usage info\
\n    \"async|a\"	      => \\$async, # Asynchronou\
s mode\n    \"polljob\"	      => \\$polljob, # Get\
 results\n    \"status\"	      => \\$status, # Get\
 job status\n    \"ids\"             => \\$ids, # \
Get ids from result\n    \"jobid|j=s\"       => \\\
$jobid, # JobId\n    \"email=s\"         => \\$par\
ams{email}, # E-mail address\n    \"trace\"       \
    => \\$trace, # SOAP trace\n    \"sequence=s\" \
     => \\$sequence, # Query sequence\n    );\n\nm\
y $scriptName = basename($0, ());\nif($help || $nu\
mOpts == 0) {\n    &usage();\n    exit(0);\n}\n\ni\
f($trace){\n    print STDERR \"Tracing active\\n\"\
;\n    SOAP::Lite->import(+trace => 'debug');\n}\n\
\nmy $soap = SOAP::Lite\n    ->service($WSDL)\n   \
 ->proxy('http://localhost/',\n    #proxy => ['htt\
p' => 'http://your.proxy.server/'], # HTTP proxy\n\
    timeout => 600, # HTTP connection timeout\n   \
 )\n    ->on_fault(sub { # SOAP fault handler\n   \
     my $soap = shift;\n        my $res = shift;\n\
        # Throw an exception for all faults\n     \
   if(ref($res) eq '') {\n            die($res);\n\
        } else {\n            die($res->faultstrin\
g);\n        }\n        return new SOAP::SOM;\n   \
 }\n               );\n\nif( !($polljob || $status\
 || $ids) &&\n    !( defined($ARGV[0]) || defined(\
$sequence) )\n    ) {\n    print STDERR 'Error: ba\
d option combination', \"\\n\";\n    &usage();\n  \
  exit(1);\n}\nelsif($polljob && defined($jobid)) \
{\n    print \"Getting results for job $jobid\\n\"\
;\n    getResults($jobid);\n}\nelsif($status && de\
fined($jobid)) {\n    print STDERR \"Getting statu\
s for job $jobid\\n\";\n    my $result = $soap->ch\
eckStatus($jobid);\n    print STDOUT \"$result\\n\\
";\n    if($result eq 'DONE') {\n	print STDERR \"T\
o get results: $scriptName --polljob --jobid $jobi\
d\\n\";\n    }\n}  \nelsif($ids && defined($jobid)\
) {\n    print STDERR \"Getting ids from job $jobi\
d\\n\";\n    getIds($jobid);\n}\nelse {\n    # Pre\
pare input data\n    my $content;\n    my (@conten\
ts) = ();\n    if(-f $ARGV[0] || $ARGV[0] eq '-') \
{	\n	$content={type=>'sequence',content=>read_file\
($ARGV[0])};	\n    }\n    if($sequence) {	\n	if(-f\
 $sequence || $sequence eq '-') {	\n	    $content=\
{type=>'sequence',content=>read_file($ARGV[0])};	\\
n	} else {\n	    $content={type=>'sequence',conten\
t=>$sequence};\n	}\n    }\n    push @contents, $co\
ntent;\n\n    # Submit the job\n    my $paramsData\
 = SOAP::Data->name('params')->type(map=>\\%params\
);\n    my $contentData = SOAP::Data->name('conten\
t')->value(\\@contents);\n    # For SOAP::Lite 0.6\
0 and earlier parameters are passed directly\n    \
if($SOAP::Lite::VERSION eq '0.60' || $SOAP::Lite::\
VERSION =~ /0\\.[1-5]/) {\n        $jobid = $soap-\
>runWUBlast($paramsData, $contentData);\n    }\n  \
  # For SOAP::Lite 0.69 and later parameter handli\
ng is different, so pass\n    # undef's for templa\
ted params, and then pass the formatted args.\n   \
 else {\n        $jobid = $soap->runWUBlast(undef,\
 undef,\n				   $paramsData, $contentData);\n    }\
\n\n    # Asynchronous mode: output jobid and exit\
.\n    if (defined($async)) {\n	print STDOUT $jobi\
d, \"\\n\";\n        print STDERR \"To check statu\
s: $scriptName --status --jobid $jobid\\n\";\n    \
}\n    # Synchronous mode: try to get results\n   \
 else {\n        print STDERR \"JobId: $jobid\\n\"\
;\n        sleep 1;\n        getResults($jobid);\n\
    }\n}\n\nsub getIds($) {\n    my $jobid = shift\
;\n    my $results = $soap->getIds($jobid);\n    f\
or my $result (@$results){\n	print \"$result\\n\";\
\n    }\n}\n\nsub clientPoll($) {\n    my $jobid =\
 shift;\n    my $result = 'PENDING';\n    # Check \
status and wait if not finished\n    while($result\
 eq 'RUNNING' || $result eq 'PENDING') {\n        \
$result = $soap->checkStatus($jobid);\n        pri\
nt STDERR \"$result\\n\";\n        if($result eq '\
RUNNING' || $result eq 'PENDING') {\n            #\
 Wait before polling again.\n            sleep $ch\
eckInterval;\n        }\n    }\n}\n\nsub getResult\
s($) {\n    my $jobid = shift;\n    my $res;\n    \
# Check status, and wait if not finished\n    clie\
ntPoll($jobid);\n    # Use JobId if output file na\
me is not defined\n    unless(defined($outfile)) {\
\n        $outfile=$jobid;\n    }\n    # Get list \
of data types\n    my $resultTypes = $soap->getRes\
ults($jobid);\n    # Get the data and write it to \
a file\n    if(defined($outformat)) { # Specified \
data type\n	if($outformat eq 'xml') {$outformat = \
'toolxml';}\n	if($outformat eq 'txt') {$outformat \
= 'tooloutput';}\n        my $selResultType;\n    \
    foreach my $resultType (@$resultTypes) {\n    \
        if($resultType->{type} eq $outformat) {\n \
               $selResultType = $resultType;\n    \
        }\n        }\n        $res=$soap->poll($jo\
bid, $selResultType->{type});\n	if($outfile eq '-'\
) {\n	     write_file($outfile, $res);\n	} else {\\
n	    write_file($outfile.'.'.$selResultType->{ext\
}, $res);\n	}\n    } else { # Data types available\
\n        # Write a file for each output type\n   \
     for my $resultType (@$resultTypes){\n        \
    #print STDERR \"Getting $resultType->{type}\\n\
\";\n            $res=$soap->poll($jobid, $resultT\
ype->{type});\n	    if($outfile eq '-') {\n		write\
_file($outfile, $res);\n	    } else {\n		write_fil\
e($outfile.'.'.$resultType->{ext}, $res);\n	    }\\
n        }\n    }\n}\n\nsub read_file($) {\n    my\
 $filename = shift;\n    my ($content, $buffer);\n\
    if($filename eq '-') {\n	while(sysread(STDIN, \
$buffer, 1024)) {\n	    $content .= $buffer;\n	}\n\
    }\n    else { # File\n	open(FILE, $filename) o\
r die \"Error: unable to open input file\";\n	whil\
e(sysread(FILE, $buffer, 1024)) {\n	    $content .\
= $buffer;\n	}\n	close(FILE);\n    }\n    return $\
content;\n}\n\nsub write_file($$) {\n    my ($file\
name, $data) = @_;\n    print STDERR 'Creating res\
ult file: ' . $filename . \"\\n\";\n    if($filena\
me eq '-') {\n	print STDOUT $data;\n    }\n    els\
e {\n	open(FILE, \">$filename\") or die \"Error: u\
nable to open output file\";\n	syswrite(FILE, $dat\
a);\n	close(FILE);\n    }\n}\n\nsub usage {\n    p\
rint STDERR <<EOF\nWU-BLAST\n========\n\nRapid seq\
uence database search programs utilizing the BLAST\
 algorithm.\n   \n[Required]\n\n      --email     \
  : str  : user email address \n  -p, --program	  \
  : str  : BLAST program to use: blastn, blastp, b\
lastx, \n                             tblastn or t\
blastx\n  -D, --database    : str  : database to s\
earch\n  seqFile           : file : query sequence\
 data file (\"-\" for STDIN)\n\n[Optional]\n\n  -m\
, --matrix	    : str  : scoring matrix\n  -E, --ex\
p	    : real : 0<E<= 1000. Statistical significanc\
e threshold\n                             for repo\
rting database sequence matches.\n  -e, --echofilt\
er  :      : display the filtered query sequence i\
n the output\n  -f, --filter	    : str  : activate\
s filtering of the query sequence\n  -b, --alignme\
nts  : int  : number of alignments to be reported\\
n  -s, --scores	    : int  : number of scores to b\
e reported\n  -S, --sensitivity : str  :\n  -t, --\
sort	    : str  :\n  -T, --stats       : str  :\n \
 -d, --strand      : str  : DNA strand to search w\
ith in DNA vs. DNA searches \n  -c, --topcombon   \
:      :\n\n[General]	\n\n  -h, --help       :    \
  : prints this help text\n  -a, --async      :   \
   : forces to make an asynchronous query\n      -\
-status     :      : poll for the status of a job\\
n      --polljob    :      : poll for the results \
of a job\n  -j, --jobid      : str  : jobid that w\
as returned when an asynchronous job \n           \
                 was submitted.\n  -O, --outfile  \
  : str  : name of the file results should be writ\
ten to \n                            (default is b\
ased on the jobid; \"-\" for STDOUT)\n  -o, --outf\
ormat  : str  : txt or xml output (no file is writ\
ten)\n      --trace	   :      : show SOAP messages\
 being interchanged \n\nSynchronous job:\n\n  The \
results/errors are returned as soon as the job is \
finished.\n  Usage: $scriptName --email <your\\@em\
ail> [options...] seqFile\n  Returns: saves the re\
sults to disk\n\nAsynchronous job:\n\n  Use this i\
f you want to retrieve the results at a later time\
. The results \n  are stored for up to 24 hours. \\
n  The asynchronous submission mode is recommended\
 when users are submitting \n  batch jobs or large\
 database searches	\n  Usage: $scriptName --async \
--email <your\\@email> [options...] seqFile\n  Ret\
urns : jobid\n\n  Use the jobid to query for the s\
tatus of the job. \n  Usage: $scriptName --status \
--jobid <jobId>\n  Returns : string indicating the\
 status of the job:\n    DONE - job has finished\n\
    RUNNING - job is running\n    NOT_FOUND - job \
cannot be found\n    ERROR - the jobs has encounte\
red an error\n\n  When done, use the jobid to retr\
ieve the status of the job. \n  Usage: $scriptName\
 --polljob --jobid <jobId> [--outfile string]\n  R\
eturns: saves the results to disk\n\n[Help]\n\nFor\
 more detailed help information refer to \nhttp://\
www.ebi.ac.uk/blast2/WU-Blast2_Help_frame.html\n \\
nEOF\n;\n}\n","\nmy $WSDL = 'http://www.ebi.ac.uk/\
Tools/webservices/wsdl/WSBlastpgp.wsdl';\n\nuse SO\
AP::Lite;\nuse Getopt::Long qw(:config no_ignore_c\
ase bundling);\nuse File::Basename;\n\nmy $checkIn\
terval = 15;\n\nmy %params=(\n	    'async' => '1',\
 # Use async mode and simulate sync mode in client\
\n	    );\nGetOptions(\n    \"mode=s\"           =\
> \\$params{mode}, # Search mode: PSI-Blast or PHI\
-Blast\n    \"database|d=s\"     => \\$params{data\
base}, # Database to search\n    \"matrix|M=s\"   \
    => \\$params{matrix},# Scoring maxtrix\n    \"\
exp|e=f\"          => \\$params{exp}, # E-value\n \
   \"expmulti|h=f\"     => \\$params{expmulti}, # \
E-value\n    \"filter|F=s\"       => \\$params{fil\
ter}, # Low complexity filter\n    \"dropoff|X=i\"\
      => \\$params{dropoff}, # Dropoff score\n    \
\"finaldropoff|Z=i\" => \\$params{finaldropoff}, #\
 Final dropoff score\n    \"scores|v=i\"       => \
\\$params{scores}, # Max number of scores\n    \"a\
lign=i\"          => \\$params{align}, # Alignment\
 view\n    \"startregion|S=i\"  => \\$params{start\
region}, # Start of region in query\n    \"endregi\
on|H=i\"    => \\$params{endregion}, # End of regi\
on in query\n    \"maxpasses|j=i\"    => \\$params\
{maxpasses}, # Number of PSI iterations\n    \"ope\
ngap|G=i\"      => \\$params{opengap}, # Gap open \
penalty\n    \"extendgap|E=i\"    => \\$params{ext\
endgap}, # Gap extension penalty\n    \"pattern=s\\
"        => \\$params{pattern}, # PHI-BLAST patter\
n\n    \"usagemode|p=s\"    => \\$params{usagemode\
}, # PHI-BLAST program\n    \"appxml=s\"         =\
> \\$params{appxml}, # Application XML\n    \"sequ\
ence=s\"       => \\$sequence, # Query sequence\n \
   \"help\"	       => \\$help, # Usage info\n    \\
"polljob\"	       => \\$polljob, # Get results\n  \
  \"status\"	       => \\$status, # Get status\n  \
  \"ids\"      	       => \\$ids, # Get ids from r\
esult\n    \"jobid=s\"          => \\$jobid, # Job\
Id\n    \"outfile=s\"        => \\$outfile, # Outp\
ut filename\n    \"outformat|o=s\"    => \\$outfor\
mat, # Output file format\n    \"async|a\"	       \
=> \\$async, # Async submission\n    \"email=s\"  \
        => \\$params{email}, # User e-mail address\
\n    \"trace\"            => \\$trace, # Show SOA\
P messages\n    );\n\nmy $scriptName = basename($0\
, ());\nif($help) {\n    &usage();\n    exit(0);\n\
}\n\nif ($trace){\n    print \"Tracing active\\n\"\
;\n    SOAP::Lite->import(+trace => 'debug');\n}\n\
\nmy $soap = SOAP::Lite\n    ->service($WSDL)\n   \
 ->on_fault(sub {\n        my $soap = shift;\n    \
    my $res = shift;\n        # Throw an exception\
 for all faults\n        if(ref($res) eq '') {\n  \
          die($res);\n        } else {\n          \
  die($res->faultstring);\n        }\n        retu\
rn new SOAP::SOM;\n    }\n               );\n\nif(\
 !($polljob || $status || $ids) &&\n    !( (define\
d($ARGV[0]) && -f $ARGV[0]) || defined($sequence) \
)\n    ) {\n    print STDERR 'Error: bad option co\
mbination', \"\\n\";\n    &usage();\n    exit(1);\\
n}\nelsif($polljob && defined($jobid)) {\n    prin\
t \"Getting results for job $jobid\\n\";\n    getR\
esults($jobid);\n}\nelsif($status && defined($jobi\
d)) {\n    print STDERR \"Getting status for job $\
jobid\\n\";\n    my $result = $soap->checkStatus($\
jobid);\n    print STDOUT $result, \"\\n\";\n    i\
f($result eq 'DONE') {\n	print STDERR \"To get res\
ults: $scriptName --polljob --jobid $jobid\\n\";\n\
    }\n}  \nelsif($ids && defined($jobid)) {\n    \
print STDERR \"Getting ids from job $jobid\\n\";\n\
    getIds($jobid);\n}\nelse {\n    if(-f $ARGV[0]\
) {	\n	$content={type=>'sequence', content=>read_f\
ile($ARGV[0])};	\n    }\n    if($sequence) {	\n	if\
(-f $sequence) {\n	    $content={type=>'sequence',\
 content=>read_file($sequence)};	\n	} else {\n	   \
 $content={type=>'sequence', content=>$sequence};\\
n	}\n    }\n    push @content, $content;\n\n    my\
 $jobid;\n    my $paramsData = SOAP::Data->name('p\
arams')->type(map=>\\%params);\n    my $contentDat\
a = SOAP::Data->name('content')->value(\\@content)\
;\n    # For SOAP::Lite 0.60 and earlier parameter\
s are passed directly\n    if($SOAP::Lite::VERSION\
 eq '0.60' || $SOAP::Lite::VERSION =~ /0\\.[1-5]/)\
 {\n        $jobid = $soap->runBlastpgp($paramsDat\
a, $contentData);\n    }\n    # For SOAP::Lite 0.6\
9 and later parameter handling is different, so pa\
ss\n    # undef's for templated params, and then p\
ass the formatted args.\n    else {\n        $jobi\
d = $soap->runBlastpgp(undef, undef,\n				    $par\
amsData, $contentData);\n    }\n\n    if (defined(\
$async)) {\n	print STDOUT $jobid, \"\\n\";\n      \
  print STDERR \"To check status: $scriptName --st\
atus --jobid $jobid\\n\";\n    } else { # Synchron\
ous mode\n        print STDERR \"JobId: $jobid\\n\\
";\n        sleep 1;\n        getResults($jobid);\\
n    }\n}\n\nsub getIds($) {\n    $jobid = shift;\\
n    my $results = $soap->getIds($jobid);\n    for\
 $result (@$results){\n	print \"$result\\n\";\n   \
 }\n}\n\nsub clientPoll($) {\n    my $jobid = shif\
t;\n    my $result = 'PENDING';\n    # Check statu\
s and wait if not finished\n    #print STDERR \"Ch\
ecking status: $jobid\\n\";\n    while($result eq \
'RUNNING' || $result eq 'PENDING') {\n        $res\
ult = $soap->checkStatus($jobid);\n        print S\
TDERR \"$result\\n\";\n        if($result eq 'RUNN\
ING' || $result eq 'PENDING') {\n            # Wai\
t before polling again.\n            sleep $checkI\
nterval;\n        }\n    }\n}\n\nsub getResults($)\
 {\n    $jobid = shift;\n    # Check status, and w\
ait if not finished\n    clientPoll($jobid);\n    \
# Use JobId if output file name is not defined\n  \
  unless(defined($outfile)) {\n        $outfile=$j\
obid;\n    }\n    # Get list of data types\n    my\
 $resultTypes = $soap->getResults($jobid);\n    # \
Get the data and write it to a file\n    if(define\
d($outformat)) { # Specified data type\n        my\
 $selResultType;\n        foreach my $resultType (\
@$resultTypes) {\n            if($resultType->{typ\
e} eq $outformat) {\n                $selResultTyp\
e = $resultType;\n            }\n        }\n      \
  $res=$soap->poll($jobid, $selResultType->{type})\
;\n        write_file($outfile.'.'.$selResultType-\
>{ext}, $res);\n    } else { # Data types availabl\
e\n        # Write a file for each output type\n  \
      for my $resultType (@$resultTypes){\n       \
     #print \"Getting $resultType->{type}\\n\";\n \
           $res=$soap->poll($jobid, $resultType->{\
type});\n            write_file($outfile.'.'.$resu\
ltType->{ext}, $res);\n        }\n    }\n}\n\nsub \
read_file($) {\n    my $filename = shift;\n    ope\
n(FILE, $filename);\n    my $content;\n    my $buf\
fer;\n    while(sysread(FILE, $buffer, 1024)) {\n	\
$content.= $buffer;\n    }\n    close(FILE);  \n  \
  return $content;\n}\n\nsub write_file($$) {\n   \
 my ($tmp,$entity) = @_;\n    print STDERR \"Creat\
ing result file: \".$tmp.\"\\n\";\n    unless(open\
 (FILE, \">$tmp\")) {\n	return 0;\n    }\n    sysw\
rite(FILE, $entity);\n    close (FILE);\n    retur\
n 1;\n}\n\nsub usage {\n    print STDERR <<EOF\nBl\
astpgp\n========\n   \nThe blastpgp program implem\
ents the PSI-BLAST and PHI-BLAST variations\nof NC\
BI BLAST.\n\nFor more detailed help information re\
fer to\nhttp://www.ebi.ac.uk/blastpgp/blastpsi_hel\
p_frame.html\n \nBlastpgp specific options:\n\n[Re\
quired]\n\n      --mode            : str  : search\
 mode to use: PSI-Blast or PHI-Blast\n  -d, --data\
base        : str  : protein database to search\n \
 seqFile               : file : query sequence\n\n\
[Optional]\n\n  -M, --matrix          : str  : sco\
ring matrix\n  -e, --exp             : real : Expe\
ctation value\n  -h, --expmulti        : real : th\
reshold (multipass model)\n  -F, --filter         \
 : str  : filter query sequence with SEG [T,F]\n  \
-m, --align           : int  : alignment view opti\
on:\n                                 0 - pairwise\
, 1 - M/S identities,\n                           \
      2 - M/S non-identities, 3 - Flat identities,\
\n                                 4 - Flat non-id\
entities\n  -G, --opengap         : int  : cost to\
 open a gap\n  -E, --extendgap       : int  : cost\
 to extend a gap\n  -g, --gapalign        : str  :\
 Gapped [T,F]\n  -v, --scores          : int  : nu\
mber of scores to be reported\n  -j, --maxpasses  \
     : int  : number of iterations\n  -X, --dropof\
f         : int  : Dropoff score\n  -Z, --finaldro\
poff    : int  : Dropoff for final alignment\n  -S\
, --startregion     : int  : Start of required reg\
ion in query\n  -H, --endregion       : int  : End\
 of required region in query\n  -k, --pattern     \
    : str  : Hit File (PHI-BLAST only)\n  -p, --us\
agemode       : str  : Program option (PHI-BLAST o\
nly):\n                                 blastpgp, \
patseedp, seedp\n\n[General]\n\n      --help      \
      :      : prints this help text\n  -a, --asyn\
c           :      : forces to make an asynchronou\
s query\n      --status          :      : poll for\
 the status of a job\n      --polljob         :   \
   : poll for the results of a job\n      --jobid \
          : str  : jobid of an asynchronous job\n \
     --ids             :      : get hit identifier\
s for result \n  -O, --outfile         : str  : na\
me of the file results should be written to\n     \
                            (default is based on t\
he jobid)\n  -o, --outformat       : str  : txt or\
 xml output (no file is written)\n      --trace   \
        :      : show SOAP messages being intercha\
nged\n\nSynchronous job:\n\n  The results/errors a\
re returned as soon as the job is finished.\n  Usa\
ge: blastpgp.pl --email <your@email> [options...] \
seqfile\n  Returns: saves the results to disk\n\nA\
synchronous job:\n\n  Use this if you want to retr\
ieve the results at a later time. The results\n  a\
re stored for up to 24 hours.\n  The asynchronous \
submission mode is recommended when users are subm\
itting\n  batch jobs or large database searches\n \
 Usage: blastpgp.pl --email <your@email> --async [\
options...] seqFile\n  Returns: jobid\n\n  Use the\
 jobid to query for the status of the job.\n  Usag\
e: blastpgp.pl --status --jobid <jobId>\n  Returns\
: string indicating the status of the job\n    DON\
E - job has finished\n    RUNNING - job is running\
\n    NOT_FOUND - job cannot be found\n    ERROR -\
 the jobs has encountered an error\n\n  When done,\
 use the jobid to retrieve the results of the job.\
\n  Usage: blastpgp.pl --polljob --jobid <jobId> [\
--outfile <fileName>]\n  Returns: saves the result\
s to disk\nEOF\n;\n}\n","\n=head1 NAME\n\nncbiblas\
t_lwp.pl\n\n=head1 DESCRIPTION\n\nNCBI BLAST REST \
web service Perl client using L<LWP>.\n\nTested wi\
th:\n\n=over\n\n=item *\nL<LWP> 5.79, L<XML::Simpl\
e> 2.12 and Perl 5.8.3\n\n=item *\nL<LWP> 5.805, L\
<XML::Simple> 2.14 and Perl 5.8.7\n\n=item *\nL<LW\
P> 5.820, L<XML::Simple> 2.18 and Perl 5.10.0 (Ubu\
ntu 9.04)\n\n=back\n\nFor further information see:\
\n\n=over\n\n=item *\nL<http://www.ebi.ac.uk/Tools\
/webservices/services/sss/ncbi_blast_rest>\n\n=ite\
m *\nL<http://www.ebi.ac.uk/Tools/webservices/tuto\
rials/perl>\n\n=back\n\n=head1 VERSION\n\n$Id: ncb\
iblast_lwp.pl 1317 2009-09-03 15:44:11Z hpm $\n\n=\
cut\n\nuse strict;\nuse warnings;\n\nuse English;\\
nuse LWP;\nuse XML::Simple;\nuse Getopt::Long qw(:\
config no_ignore_case bundling);\nuse File::Basena\
me;\nuse Data::Dumper;\n\nmy $baseUrl = 'http://ww\
w.ebi.ac.uk/Tools/services/rest/ncbiblast';\n\nmy \
$checkInterval = 3;\n\nmy $outputLevel = 1;\n\nmy \
$numOpts = scalar(@ARGV);\nmy %params = ( 'debugLe\
vel' => 0 );\n\nmy %tool_params = ();\nGetOptions(\
\n\n	# Tool specific options\n	'program|p=s'  => \\
\$tool_params{'program'},   # blastp, blastn, blas\
tx, etc.\n	'database|D=s' => \\$params{'database'}\
,       # Database(s) to search\n	'matrix|m=s'   =\
> \\$tool_params{'matrix'},    # Scoring martix to\
 use\n	'exp|E=f'      => \\$tool_params{'exp'},   \
    # E-value threshold\n	'filter|f=s'   => \\$too\
l_params{'filter'},    # Low complexity filter\n	'\
align|A=i'    => \\$tool_params{'align'},     # Pa\
irwise alignment format\n	'scores|s=i'   => \\$too\
l_params{'scores'},    # Number of scores\n	'align\
ments|n=i' => \\$tool_params{'alignments'},   # Nu\
mber of alignments\n	'dropoff|d=i'    => \\$tool_p\
arams{'dropoff'},      # Dropoff score\n	'match_sc\
ores=s' => \\$tool_params{'match_scores'}, # Match\
/missmatch scores\n	'match|u=i'      => \\$params{\
'match'},             # Match score\n	'mismatch|v=\
i'   => \\$params{'mismatch'},          # Mismatch\
 score\n	'gapopen|o=i'    => \\$tool_params{'gapop\
en'},      # Open gap penalty\n	'gapext|x=i'     =\
> \\$tool_params{'gapext'},       # Gap extension \
penality\n	'gapalign|g'     => \\$tool_params{'gap\
align'},     # Optimise gap alignments\n	'stype=s'\
 => \\$tool_params{'stype'},    # Sequence type\n	\
'seqrange=s' => \\$tool_params{'seqrange'},    # Q\
uery subsequence\n	'sequence=s' => \\$params{'sequ\
ence'},         # Query sequence\n	'multifasta' =>\
 \\$params{'multifasta'},       # Multiple fasta i\
nput\n\n	# Compatability options, old command-line\
\n	'numal|n=i'     => \\$params{'numal'},        #\
 Number of alignments\n	'opengap|o=i'   => \\$para\
ms{'opengap'},      # Open gap penalty\n	'extendga\
p|x=i' => \\$params{'extendgap'},    # Gap extensi\
on penality\n	\n	# Generic options\n	'email=s'    \
   => \\$params{'email'},          # User e-mail a\
ddress\n	'title=s'       => \\$params{'title'},   \
       # Job title\n	'outfile=s'     => \\$params{\
'outfile'},        # Output file name\n	'outformat\
=s'   => \\$params{'outformat'},      # Output fil\
e type\n	'jobid=s'       => \\$params{'jobid'},   \
       # JobId\n	'help|h'        => \\$params{'hel\
p'},           # Usage help\n	'async'         => \\
\$params{'async'},          # Asynchronous submiss\
ion\n	'polljob'       => \\$params{'polljob'},    \
    # Get results\n	'resultTypes'   => \\$params{'\
resultTypes'},    # Get result types\n	'status'   \
     => \\$params{'status'},         # Get status\\
n	'params'        => \\$params{'params'},         \
# List input parameters\n	'paramDetail=s' => \\$pa\
rams{'paramDetail'},    # Get details for paramete\
r\n	'quiet'         => \\$params{'quiet'},        \
  # Decrease output level\n	'verbose'       => \\$\
params{'verbose'},        # Increase output level\\
n	'debugLevel=i'  => \\$params{'debugLevel'},     \
# Debug output level\n	'baseUrl=s'     => \\$baseU\
rl,                  # Base URL for service.\n);\n\
if ( $params{'verbose'} ) { $outputLevel++ }\nif (\
 $params{'$quiet'} )  { $outputLevel-- }\n\n&print\
_debug_message( 'MAIN', 'LWP::VERSION: ' . $LWP::V\
ERSION,\n	1 );\n\n&print_debug_message( 'MAIN', \"\
params:\\n\" . Dumper( \\%params ),           11 )\
;\n&print_debug_message( 'MAIN', \"tool_params:\\n\
\" . Dumper( \\%tool_params ), 11 );\n\nmy $script\
Name = basename( $0, () );\n\nif ( $params{'help'}\
 || $numOpts == 0 ) {\n	&usage();\n	exit(0);\n}\n\\
n&print_debug_message( 'MAIN', 'baseUrl: ' . $base\
Url, 1 );\n\nif (\n	!(\n		   $params{'polljob'}\n	\
	|| $params{'resultTypes'}\n		|| $params{'status'}\
\n		|| $params{'params'}\n		|| $params{'paramDetai\
l'}\n	)\n	&& !( defined( $ARGV[0] ) || defined( $p\
arams{'sequence'} ) )\n  )\n{\n\n	# Bad argument c\
ombination, so print error message and usage\n	pri\
nt STDERR 'Error: bad option combination', \"\\n\"\
;\n	&usage();\n	exit(1);\n}\n\nelsif ( $params{'pa\
rams'} ) {\n	&print_tool_params();\n}\n\nelsif ( $\
params{'paramDetail'} ) {\n	&print_param_details( \
$params{'paramDetail'} );\n}\n\nelsif ( $params{'s\
tatus'} && defined( $params{'jobid'} ) ) {\n	&prin\
t_job_status( $params{'jobid'} );\n}\n\nelsif ( $p\
arams{'resultTypes'} && defined( $params{'jobid'} \
) ) {\n	&print_result_types( $params{'jobid'} );\n\
}\n\nelsif ( $params{'polljob'} && defined( $param\
s{'jobid'} ) ) {\n	&get_results( $params{'jobid'} \
);\n}\n\nelse {\n\n	# Multiple input sequence mode\
, assume fasta format.\n	if ( $params{'multifasta'\
} ) {\n		&multi_submit_job();\n	}\n\n	# Entry iden\
tifier list file.\n	elsif (( defined( $params{'seq\
uence'} ) && $params{'sequence'} =~ m/^\\@/ )\n		|\
| ( defined( $ARGV[0] ) && $ARGV[0] =~ m/^\\@/ ) )\
\n	{\n		my $list_filename = $params{'sequence'} ||\
 $ARGV[0];\n		$list_filename =~ s/^\\@//;\n		&list\
_file_submit_job($list_filename);\n	}\n\n	# Defaul\
t: single sequence/identifier.\n	else {\n\n		# Loa\
d the sequence data and submit.\n		&submit_job( &l\
oad_data() );\n	}\n}\n\n=head1 FUNCTIONS\n\n=cut\n\
\n\n=head2 rest_request()\n\nPerform a REST reques\
t.\n\n  my $response_str = &rest_request($url);\n\\
n=cut\n\nsub rest_request {\n	print_debug_message(\
 'rest_request', 'Begin', 11 );\n	my $requestUrl =\
 shift;\n	print_debug_message( 'rest_request', 'UR\
L: ' . $requestUrl, 11 );\n\n	# Create a user agen\
t\n	my $ua = LWP::UserAgent->new();\n	'$Revision: \
1317 $' =~ m/(\\d+)/;\n	$ua->agent(\"EBI-Sample-Cl\
ient/$1 ($scriptName; $OSNAME) \" . $ua->agent());\
\n	$ua->env_proxy;\n\n	# Perform the request\n	my \
$response = $ua->get($requestUrl);\n	print_debug_m\
essage( 'rest_request', 'HTTP status: ' . $respons\
e->code,\n		11 );\n\n	# Check for HTTP error codes\
\n	if ( $response->is_error ) {\n		$response->cont\
ent() =~ m/<h1>([^<]+)<\\/h1>/;\n		die 'http statu\
s: ' . $response->code . ' ' . $response->message \
. '  ' . $1;\n	}\n	print_debug_message( 'rest_requ\
est', 'End', 11 );\n\n	# Return the response data\\
n	return $response->content();\n}\n\n=head2 rest_g\
et_parameters()\n\nGet list of tool parameter name\
s.\n\n  my (@param_list) = &rest_get_parameters();\
\n\n=cut\n\nsub rest_get_parameters {\n	print_debu\
g_message( 'rest_get_parameters', 'Begin', 1 );\n	\
my $url                = $baseUrl . '/parameters/'\
;\n	my $param_list_xml_str = rest_request($url);\n\
	my $param_list_xml     = XMLin($param_list_xml_st\
r);\n	my (@param_list)       = @{ $param_list_xml-\
>{'id'} };\n	print_debug_message( 'rest_get_parame\
ters', 'End', 1 );\n	return (@param_list);\n}\n\n=\
head2 rest_get_parameter_details()\n\nGet details \
of a tool parameter.\n\n  my $paramDetail = &rest_\
get_parameter_details($param_name);\n\n=cut\n\nsub\
 rest_get_parameter_details {\n	print_debug_messag\
e( 'rest_get_parameter_details', 'Begin', 1 );\n	m\
y $parameterId = shift;\n	print_debug_message( 're\
st_get_parameter_details',\n		'parameterId: ' . $p\
arameterId, 1 );\n	my $url                  = $bas\
eUrl . '/parameterdetails/' . $parameterId;\n	my $\
param_detail_xml_str = rest_request($url);\n	my $p\
aram_detail_xml     = XMLin($param_detail_xml_str)\
;\n	print_debug_message( 'rest_get_parameter_detai\
ls', 'End', 1 );\n	return ($param_detail_xml);\n}\\
n\n=head2 rest_run()\n\nSubmit a job.\n\n  my $job\
_id = &rest_run($email, $title, \\%params );\n\n=c\
ut\n\nsub rest_run {\n	print_debug_message( 'rest_\
run', 'Begin', 1 );\n	my $email  = shift;\n	my $ti\
tle  = shift;\n	my $params = shift;\n	print_debug_\
message( 'rest_run', 'email: ' . $email, 1 );\n	if\
 ( defined($title) ) {\n		print_debug_message( 're\
st_run', 'title: ' . $title, 1 );\n	}\n	print_debu\
g_message( 'rest_run', 'params: ' . Dumper($params\
), 1 );\n\n	# User agent to perform http requests\\
n	my $ua = LWP::UserAgent->new();\n	$ua->env_proxy\
;\n\n	# Clean up parameters\n	my (%tmp_params) = %\
{$params};\n	$tmp_params{'email'} = $email;\n	$tmp\
_params{'title'} = $title;\n	foreach my $param_nam\
e ( keys(%tmp_params) ) {\n		if ( !defined( $tmp_p\
arams{$param_name} ) ) {\n			delete $tmp_params{$p\
aram_name};\n		}\n	}\n\n	# Submit the job as a POS\
T\n	my $url = $baseUrl . '/run';\n	my $response = \
$ua->post( $url, \\%tmp_params );\n	print_debug_me\
ssage( 'rest_run', 'HTTP status: ' . $response->co\
de, 11 );\n	print_debug_message( 'rest_run',\n		'r\
equest: ' . $response->request()->content(), 11 );\
\n\n	# Check for HTTP error codes\n	if ( $response\
->is_error ) {\n		$response->content() =~ m/<h1>([\
^<]+)<\\/h1>/;\n		die 'http status: ' . $response-\
>code . ' ' . $response->message . '  ' . $1;\n	}\\
n\n	# The job id is returned\n	my $job_id = $respo\
nse->content();\n	print_debug_message( 'rest_run',\
 'End', 1 );\n	return $job_id;\n}\n\n=head2 rest_g\
et_status()\n\nCheck the status of a job.\n\n  my \
$status = &rest_get_status($job_id);\n\n=cut\n\nsu\
b rest_get_status {\n	print_debug_message( 'rest_g\
et_status', 'Begin', 1 );\n	my $job_id = shift;\n	\
print_debug_message( 'rest_get_status', 'jobid: ' \
. $job_id, 2 );\n	my $status_str = 'UNKNOWN';\n	my\
 $url        = $baseUrl . '/status/' . $job_id;\n	\
$status_str = &rest_request($url);\n	print_debug_m\
essage( 'rest_get_status', 'status_str: ' . $statu\
s_str, 2 );\n	print_debug_message( 'rest_get_statu\
s', 'End', 1 );\n	return $status_str;\n}\n\n=head2\
 rest_get_result_types()\n\nGet list of result typ\
es for finished job.\n\n  my (@result_types) = &re\
st_get_result_types($job_id);\n\n=cut\n\nsub rest_\
get_result_types {\n	print_debug_message( 'rest_ge\
t_result_types', 'Begin', 1 );\n	my $job_id = shif\
t;\n	print_debug_message( 'rest_get_result_types',\
 'jobid: ' . $job_id, 2 );\n	my (@resultTypes);\n	\
my $url                      = $baseUrl . '/result\
types/' . $job_id;\n	my $result_type_list_xml_str \
= &rest_request($url);\n	my $result_type_list_xml \
    = XMLin($result_type_list_xml_str);\n	(@result\
Types) = @{ $result_type_list_xml->{'type'} };\n	p\
rint_debug_message( 'rest_get_result_types',\n		sc\
alar(@resultTypes) . ' result types', 2 );\n	print\
_debug_message( 'rest_get_result_types', 'End', 1 \
);\n	return (@resultTypes);\n}\n\n=head2 rest_get_\
result()\n\nGet result data of a specified type fo\
r a finished job.\n\n  my $result = rest_get_resul\
t($job_id, $result_type);\n\n=cut\n\nsub rest_get_\
result {\n	print_debug_message( 'rest_get_result',\
 'Begin', 1 );\n	my $job_id = shift;\n	my $type   \
= shift;\n	print_debug_message( 'rest_get_result',\
 'jobid: ' . $job_id, 1 );\n	print_debug_message( \
'rest_get_result', 'type: ' . $type,    1 );\n	my \
$url    = $baseUrl . '/result/' . $job_id . '/' . \
$type;\n	my $result = &rest_request($url);\n	print\
_debug_message( 'rest_get_result', length($result)\
 . ' characters',\n		1 );\n	print_debug_message( '\
rest_get_result', 'End', 1 );\n	return $result;\n}\
\n\n\n=head2 print_debug_message()\n\nPrint debug \
message at specified debug level.\n\n  &print_debu\
g_message($method_name, $message, $level);\n\n=cut\
\n\nsub print_debug_message {\n	my $function_name \
= shift;\n	my $message       = shift;\n	my $level \
        = shift;\n	if ( $level <= $params{'debugLe\
vel'} ) {\n		print STDERR '[', $function_name, '()\
] ', $message, \"\\n\";\n	}\n}\n\n=head2 print_too\
l_params()\n\nPrint list of tool parameters.\n\n  \
&print_tool_params();\n\n=cut\n\nsub print_tool_pa\
rams {\n	print_debug_message( 'print_tool_params',\
 'Begin', 1 );\n	my (@param_list) = &rest_get_para\
meters();\n	foreach my $param ( sort(@param_list) \
) {\n		print $param, \"\\n\";\n	}\n	print_debug_me\
ssage( 'print_tool_params', 'End', 1 );\n}\n\n=hea\
d2 print_param_details()\n\nPrint details of a too\
l parameter.\n\n  &print_param_details($param_name\
);\n\n=cut\n\nsub print_param_details {\n	print_de\
bug_message( 'print_param_details', 'Begin', 1 );\\
n	my $paramName = shift;\n	print_debug_message( 'p\
rint_param_details', 'paramName: ' . $paramName, 2\
 );\n	my $paramDetail = &rest_get_parameter_detail\
s($paramName);\n	print $paramDetail->{'name'}, \"\\
\t\", $paramDetail->{'type'}, \"\\n\";\n	print $pa\
ramDetail->{'description'}, \"\\n\";\n	foreach my \
$value ( @{ $paramDetail->{'values'}->{'value'} } \
) {\n		print $value->{'value'};\n		if ( $value->{'\
defaultValue'} eq 'true' ) {\n			print \"\\t\", 'd\
efault';\n		}\n		print \"\\n\";\n		print \"\\t\", \
$value->{'label'}, \"\\n\";\n	}\n	print_debug_mess\
age( 'print_param_details', 'End', 1 );\n}\n\n=hea\
d2 print_job_status()\n\nPrint status of a job.\n\\
n  &print_job_status($job_id);\n\n=cut\n\nsub prin\
t_job_status {\n	print_debug_message( 'print_job_s\
tatus', 'Begin', 1 );\n	my $jobid = shift;\n	print\
_debug_message( 'print_job_status', 'jobid: ' . $j\
obid, 1 );\n	if ( $outputLevel > 0 ) {\n		print ST\
DERR 'Getting status for job ', $jobid, \"\\n\";\n\
	}\n	my $result = &rest_get_status($jobid);\n	prin\
t \"$result\\n\";\n	if ( $result eq 'FINISHED' && \
$outputLevel > 0 ) {\n		print STDERR \"To get resu\
lts: $scriptName --polljob --jobid \" . $jobid\n		\
  . \"\\n\";\n	}\n	print_debug_message( 'print_job\
_status', 'End', 1 );\n}\n\n=head2 print_result_ty\
pes()\n\nPrint available result types for a job.\n\
\n  &print_result_types($job_id);\n\n=cut\n\nsub p\
rint_result_types {\n	print_debug_message( 'result\
_types', 'Begin', 1 );\n	my $jobid = shift;\n	prin\
t_debug_message( 'result_types', 'jobid: ' . $jobi\
d, 1 );\n	if ( $outputLevel > 0 ) {\n		print STDER\
R 'Getting result types for job ', $jobid, \"\\n\"\
;\n	}\n	my $status = &rest_get_status($jobid);\n	i\
f ( $status eq 'PENDING' || $status eq 'RUNNING' )\
 {\n		print STDERR 'Error: Job status is ', $statu\
s,\n		  '. To get result types the job must be fin\
ished.', \"\\n\";\n	}\n	else {\n		my (@resultTypes\
) = &rest_get_result_types($jobid);\n		if ( $outpu\
tLevel > 0 ) {\n			print STDOUT 'Available result \
types:', \"\\n\";\n		}\n		foreach my $resultType (\
@resultTypes) {\n			print STDOUT $resultType->{'id\
entifier'}, \"\\n\";\n			if ( defined( $resultType\
->{'label'} ) ) {\n				print STDOUT \"\\t\", $resu\
ltType->{'label'}, \"\\n\";\n			}\n			if ( defined\
( $resultType->{'description'} ) ) {\n				print ST\
DOUT \"\\t\", $resultType->{'description'}, \"\\n\\
";\n			}\n			if ( defined( $resultType->{'mediaTyp\
e'} ) ) {\n				print STDOUT \"\\t\", $resultType->\
{'mediaType'}, \"\\n\";\n			}\n			if ( defined( $r\
esultType->{'fileSuffix'} ) ) {\n				print STDOUT \
\"\\t\", $resultType->{'fileSuffix'}, \"\\n\";\n		\
	}\n		}\n		if ( $status eq 'FINISHED' && $outputLe\
vel > 0 ) {\n			print STDERR \"\\n\", 'To get resu\
lts:', \"\\n\",\n			  \"  $scriptName --polljob --\
jobid \" . $params{'jobid'} . \"\\n\",\n			  \"  $\
scriptName --polljob --outformat <type> --jobid \"\
\n			  . $params{'jobid'} . \"\\n\";\n		}\n	}\n	pr\
int_debug_message( 'result_types', 'End', 1 );\n}\\
n\n=head2 submit_job()\n\nSubmit a job to the serv\
ice.\n\n  &submit_job($seq);\n\n=cut\n\nsub submit\
_job {\n	print_debug_message( 'submit_job', 'Begin\
', 1 );\n\n	# Set input sequence\n	$tool_params{'s\
equence'} = shift;\n\n	# Load parameters\n	&load_p\
arams();\n\n	# Submit the job\n	my $jobid = &rest_\
run( $params{'email'}, $params{'title'}, \\%tool_p\
arams );\n\n	# Simulate sync/async mode\n	if ( def\
ined( $params{'async'} ) ) {\n		print STDOUT $jobi\
d, \"\\n\";\n		if ( $outputLevel > 0 ) {\n			print\
 STDERR\n			  \"To check status: $scriptName --sta\
tus --jobid $jobid\\n\";\n		}\n	}\n	else {\n		if (\
 $outputLevel > 0 ) {\n			print STDERR \"JobId: $j\
obid\\n\";\n		}\n		sleep 1;\n		&get_results($jobid\
);\n	}\n	print_debug_message( 'submit_job', 'End',\
 1 );\n}\n\n=head2 multi_submit_job()\n\nSubmit mu\
ltiple jobs assuming input is a collection of fast\
a formatted sequences.\n\n  &multi_submit_job();\n\
\n=cut\n\nsub multi_submit_job {\n	print_debug_mes\
sage( 'multi_submit_job', 'Begin', 1 );\n	my $jobI\
dForFilename = 1;\n	$jobIdForFilename = 0 if ( def\
ined( $params{'outfile'} ) );\n	my (@filename_list\
) = ();\n\n	# Query sequence\n	if ( defined( $ARGV\
[0] ) ) {    # Bare option\n		if ( -f $ARGV[0] || \
$ARGV[0] eq '-' ) {    # File\n			push( @filename_\
list, $ARGV[0] );\n		}\n	}\n	if ( $params{'sequenc\
e'} ) {                   # Via --sequence\n		if (\
 -f $params{'sequence'} || $params{'sequence'} eq \
'-' ) {    # File\n			push( @filename_list, $param\
s{'sequence'} );\n		}\n	}\n\n	$/ = '>';\n	foreach \
my $filename (@filename_list) {\n		open( my $INFIL\
E, '<', $filename )\n		  or die \"Error: unable to\
 open file $filename ($!)\";\n		while (<$INFILE>) \
{\n			my $seq = $_;\n			$seq =~ s/>$//;\n			if ( $\
seq =~ m/(\\S+)/ ) {\n				print STDERR \"Submittin\
g job for: $1\\n\"\n				  if ( $outputLevel > 0 );\
\n				$seq = '>' . $seq;\n				&print_debug_message\
( 'multi_submit_job', $seq, 11 );\n				&submit_job\
($seq);\n				$params{'outfile'} = undef if ( $jobI\
dForFilename == 1 );\n			}\n		}\n		close $INFILE;\\
n	}\n	print_debug_message( 'multi_submit_job', 'En\
d', 1 );\n}\n\n=head2 list_file_submit_job()\n\nSu\
bmit multiple jobs using a file containing a list \
of entry identifiers as \ninput.\n\n  &list_file_s\
ubmit_job($list_filename)\n\n=cut\n\nsub list_file\
_submit_job {\n	my $filename         = shift;\n	my\
 $jobIdForFilename = 1;\n	$jobIdForFilename = 0 if\
 ( defined( $params{'outfile'} ) );\n\n	# Iterate \
over identifiers, submitting each job\n	open( my $\
LISTFILE, '<', $filename )\n	  or die 'Error: unab\
le to open file ' . $filename . ' (' . $! . ')';\n\
	while (<$LISTFILE>) {\n		my $line = $_;\n		chomp(\
$line);\n		if ( $line ne '' ) {\n			&print_debug_m\
essage( 'list_file_submit_job', 'line: ' . $line, \
2 );\n			if ( $line =~ m/\\w:\\w/ ) {    # Check t\
his is an identifier\n				print STDERR \"Submittin\
g job for: $line\\n\"\n				  if ( $outputLevel > 0\
 );\n				&submit_job($line);\n			}\n			else {\n			\
	print STDERR\n\"Warning: line \\\"$line\\\" is no\
t recognised as an identifier\\n\";\n			}\n		}\n		\
$params{'outfile'} = undef if ( $jobIdForFilename \
== 1 );\n	}\n	close $LISTFILE;\n}\n\n=head2 load_d\
ata()\n\nLoad sequence data from file or option sp\
ecified on the command-line.\n\n  &load_data();\n\\
n=cut\n\nsub load_data {\n	print_debug_message( 'l\
oad_data', 'Begin', 1 );\n	my $retSeq;\n\n	# Query\
 sequence\n	if ( defined( $ARGV[0] ) ) {    # Bare\
 option\n		if ( -f $ARGV[0] || $ARGV[0] eq '-' ) {\
    # File\n			$retSeq = &read_file( $ARGV[0] );\n\
		}\n		else {                                     \
# DB:ID or sequence\n			$retSeq = $ARGV[0];\n		}\n\
	}\n	if ( $params{'sequence'} ) {                 \
  # Via --sequence\n		if ( -f $params{'sequence'} \
|| $params{'sequence'} eq '-' ) {    # File\n			$r\
etSeq = &read_file( $params{'sequence'} );\n		}\n	\
	else {    # DB:ID or sequence\n			$retSeq = $para\
ms{'sequence'};\n		}\n	}\n	print_debug_message( 'l\
oad_data', 'End', 1 );\n	return $retSeq;\n}\n\n=he\
ad2 load_params()\n\nLoad job parameters from comm\
and-line options.\n\n  &load_params();\n\n=cut\n\n\
sub load_params {\n	print_debug_message( 'load_par\
ams', 'Begin', 1 );\n\n	# Database(s) to search\n	\
my (@dbList) = split /[ ,]/, $params{'database'};\\
n	$tool_params{'database'} = \\@dbList;\n\n	# Matc\
h/missmatch\n	if ( $params{'match'} && $params{'mi\
ssmatch'} ) {\n		$tool_params{'match_scores'} =\n	\
	  $params{'match'} . ',' . $params{'missmatch'};\\
n	}\n	\n	# Compatability options, old command-line\
\n	if(!$tool_params{'alignments'} && $params{'numa\
l'}) {\n		$tool_params{'alignments'} = $params{'nu\
mal'};\n	}\n	if(!$tool_params{'gapopen'} && $param\
s{'opengap'}) {\n		$tool_params{'gapopen'} = $para\
ms{'opengap'};\n	}\n	if(!$tool_params{'gapext'} &&\
 $params{'extendgap'}) {\n		$tool_params{'gapext'}\
 = $params{'extendgap'};\n	}\n\n	print_debug_messa\
ge( 'load_params', 'End', 1 );\n}\n\n=head2 client\
_poll()\n\nClient-side job polling.\n\n  &client_p\
oll($job_id);\n\n=cut\n\nsub client_poll {\n	print\
_debug_message( 'client_poll', 'Begin', 1 );\n	my \
$jobid  = shift;\n	my $status = 'PENDING';\n\n	my \
$errorCount = 0;\n	while ($status eq 'RUNNING'\n		\
|| $status eq 'PENDING'\n		|| ( $status eq 'ERROR'\
 && $errorCount < 2 ) )\n	{\n		$status = rest_get_\
status($jobid);\n		print STDERR \"$status\\n\" if \
( $outputLevel > 0 );\n		if ( $status eq 'ERROR' )\
 {\n			$errorCount++;\n		}\n		elsif ( $errorCount \
> 0 ) {\n			$errorCount--;\n		}\n		if (   $status \
eq 'RUNNING'\n			|| $status eq 'PENDING'\n			|| $s\
tatus eq 'ERROR' )\n		{\n\n			# Wait before pollin\
g again.\n			sleep $checkInterval;\n		}\n	}\n	prin\
t_debug_message( 'client_poll', 'End', 1 );\n	retu\
rn $status;\n}\n\n=head2 get_results()\n\nGet the \
results for a job identifier.\n\n  &get_results($j\
ob_id);\n\n=cut\n\nsub get_results {\n	print_debug\
_message( 'get_results', 'Begin', 1 );\n	my $jobid\
 = shift;\n	print_debug_message( 'get_results', 'j\
obid: ' . $jobid, 1 );\n\n	# Verbose\n	if ( $outpu\
tLevel > 1 ) {\n		print 'Getting results for job '\
, $jobid, \"\\n\";\n	}\n\n	# Check status, and wai\
t if not finished\n	client_poll($jobid);\n\n	# Use\
 JobId if output file name is not defined\n	unless\
 ( defined( $params{'outfile'} ) ) {\n		$params{'o\
utfile'} = $jobid;\n	}\n\n	# Get list of data type\
s\n	my (@resultTypes) = rest_get_result_types($job\
id);\n\n	# Get the data and write it to a file\n	i\
f ( defined( $params{'outformat'} ) ) {    # Speci\
fied data type\n		my $selResultType;\n		foreach my\
 $resultType (@resultTypes) {\n			if ( $resultType\
->{'identifier'} eq $params{'outformat'} ) {\n				\
$selResultType = $resultType;\n			}\n		}\n		if ( d\
efined($selResultType) ) {\n			my $result =\n			  \
rest_get_result( $jobid, $selResultType->{'identif\
ier'} );\n			if ( $params{'outfile'} eq '-' ) {\n	\
			write_file( $params{'outfile'}, $result );\n			\
}\n			else {\n				write_file(\n					$params{'outfi\
le'} . '.'\n					  . $selResultType->{'identifier'\
} . '.'\n					  . $selResultType->{'fileSuffix'},\\
n					$result\n				);\n			}\n		}\n		else {\n			die\
 'Error: unknown result format \"' . $params{'outf\
ormat'} . '\"';\n		}\n	}\n	else {    # Data types \
available\n		      # Write a file for each output \
type\n		for my $resultType (@resultTypes) {\n			if\
 ( $outputLevel > 1 ) {\n				print STDERR 'Getting\
 ', $resultType->{'identifier'}, \"\\n\";\n			}\n	\
		my $result = rest_get_result( $jobid, $resultTyp\
e->{'identifier'} );\n			if ( $params{'outfile'} e\
q '-' ) {\n				write_file( $params{'outfile'}, $re\
sult );\n			}\n			else {\n				write_file(\n					$p\
arams{'outfile'} . '.'\n					  . $resultType->{'id\
entifier'} . '.'\n					  . $resultType->{'fileSuff\
ix'},\n					$result\n				);\n			}\n		}\n	}\n	print\
_debug_message( 'get_results', 'End', 1 );\n}\n\n=\
head2 read_file()\n\nRead a file into a scalar. Th\
e special filename '-' can be used to read from \n\
standard input (STDIN).\n\n  my $data = &read_file\
($filename);\n\n=cut\n\nsub read_file {\n	print_de\
bug_message( 'read_file', 'Begin', 1 );\n	my $file\
name = shift;\n	print_debug_message( 'read_file', \
'filename: ' . $filename, 2 );\n	my ( $content, $b\
uffer );\n	if ( $filename eq '-' ) {\n		while ( sy\
sread( STDIN, $buffer, 1024 ) ) {\n			$content .= \
$buffer;\n		}\n	}\n	else {    # File\n		open( my $\
FILE, '<', $filename )\n		  or die \"Error: unable\
 to open input file $filename ($!)\";\n		while ( s\
ysread( $FILE, $buffer, 1024 ) ) {\n			$content .=\
 $buffer;\n		}\n		close($FILE);\n	}\n	print_debug_\
message( 'read_file', 'End', 1 );\n	return $conten\
t;\n}\n\n=head2 write_file()\n\nWrite data to a fi\
le. The special filename '-' can be used to write \
to \nstandard output (STDOUT).\n\n  &write_file($f\
ilename, $data);\n\n=cut\n\nsub write_file {\n	pri\
nt_debug_message( 'write_file', 'Begin', 1 );\n	my\
 ( $filename, $data ) = @_;\n	print_debug_message(\
 'write_file', 'filename: ' . $filename, 2 );\n	if\
 ( $outputLevel > 0 ) {\n		print STDERR 'Creating \
result file: ' . $filename . \"\\n\";\n	}\n	if ( $\
filename eq '-' ) {\n		print STDOUT $data;\n	}\n	e\
lse {\n		open( my $FILE, '>', $filename )\n		  or \
die \"Error: unable to open output file $filename \
($!)\";\n		syswrite( $FILE, $data );\n		close($FIL\
E);\n	}\n	print_debug_message( 'write_file', 'End'\
, 1 );\n}\n\n=head2 usage()\n\nPrint program usage\
 message.\n\n  &usage();\n\n=cut\n\nsub usage {\n	\
print STDERR <<EOF\nNCBI BLAST\n==========\n   \nR\
apid sequence database search programs utilizing t\
he BLAST algorithm\n    \n[Required]\n\n  -p, --pr\
ogram      : str  : BLAST program to use, see --pa\
ramDetail program\n  -D, --database     : str  : d\
atabase(s) to search, space separated. See\n      \
                        --paramDetail database\n  \
    --stype        : str  : query sequence type, s\
ee --paramDetail stype\n  seqFile            : fil\
e : query sequence (\"-\" for STDIN, \\@filename f\
or\n                              identifier list \
file)\n\n[Optional]\n\n  -m, --matrix       : str \
 : scoring matrix, see --paramDetail matrix\n  -e,\
 --exp          : real : 0<E<= 1000. Statistical s\
ignificance threshold \n                          \
    for reporting database sequence matches.\n  -f\
, --filter       :      : filter the query sequenc\
e for low complexity \n                           \
   regions, see --paramDetail filter\n  -A, --alig\
n        : int  : pairwise alignment format, see -\
-paramDetail align\n  -s, --scores       : int  : \
number of scores to be reported\n  -n, --alignment\
s   : int  : number of alignments to report\n  -u,\
 --match        : int  : Match score (BLASTN only)\
\n  -v, --mismatch     : int  : Mismatch score (BL\
ASTN only)\n  -o, --gapopen      : int  : Gap open\
 penalty\n  -x, --gapext       : int  : Gap extens\
ion penalty\n  -d, --dropoff      : int  : Drop-of\
f\n  -g, --gapalign     :      : Optimise gapped a\
lignments\n      --seqrange     : str  : region wi\
thin input to use as query\n      --multifasta   :\
      : treat input as a set of fasta formatted se\
quences\n\n[General]\n\n  -h, --help        :     \
 : prints this help text\n      --async       :   \
   : forces to make an asynchronous query\n      -\
-email       : str  : e-mail address\n      --titl\
e       : str  : title for job\n      --status    \
  :      : get job status\n      --resultTypes :  \
    : get available result types for job\n      --\
polljob     :      : poll for the status of a job\\
n      --jobid       : str  : jobid that was retur\
ned when an asynchronous job \n                   \
          was submitted.\n      --outfile     : st\
r  : file name for results (default is jobid;\n   \
                          \"-\" for STDOUT)\n     \
 --outformat   : str  : result format to retrieve\\
n      --params      :      : list input parameter\
s\n      --paramDetail : str  : display details fo\
r input parameter\n      --quiet       :      : de\
crease output\n      --verbose     :      : increa\
se output\n      --trace       :      : show SOAP \
messages being interchanged \n   \nSynchronous job\
:\n\n  The results/errors are returned as soon as \
the job is finished.\n  Usage: $scriptName --email\
 <your\\@email> [options...] seqFile\n  Returns: r\
esults as an attachment\n\nAsynchronous job:\n\n  \
Use this if you want to retrieve the results at a \
later time. The results \n  are stored for up to 2\
4 hours. 	\n  Usage: $scriptName --async --email <\
your\\@email> [options...] seqFile\n  Returns: job\
id\n\n  Use the jobid to query for the status of t\
he job. If the job is finished, \n  it also return\
s the results/errors.\n  Usage: $scriptName --poll\
job --jobid <jobId> [--outfile string]\n  Returns:\
 string indicating the status of the job and if ap\
plicable, results \n  as an attachment.\n\nFurther\
 information:\n\n  http://www.ebi.ac.uk/Tools/webs\
ervices/services/sss/ncbi_blast_rest\n  http://www\
.ebi.ac.uk/Tools/webservices/tutorials/perl\n\nSup\
port/Feedback:\n\n  http://www.ebi.ac.uk/support/\\
nEOF\n}\n\n=head1 FEEDBACK/SUPPORT\n\nPlease conta\
ct us at L<http://www.ebi.ac.uk/support/> if you h\
ave any \nfeedback, suggestions or issues with the\
 service or this client.\n\n=cut\n","\n=head1 NAME\
\n\nwublast_lwp.pl\n\n=head1 DESCRIPTION\n\nWU-BLA\
ST REST web service Perl client using L<LWP>.\n\nT\
ested with:\n\n=over\n\n=item *\nL<LWP> 5.79, L<XM\
L::Simple> 2.12 and Perl 5.8.3\n\n=item *\nL<LWP> \
5.805, L<XML::Simple> 2.14 and Perl 5.8.7\n\n=item\
 *\nL<LWP> 5.820, L<XML::Simple> 2.18 and Perl 5.1\
0.0 (Ubuntu 9.04)\n\n=back\n\nFor further informat\
ion see:\n\n=over\n\n=item *\nL<http://www.ebi.ac.\
uk/Tools/webservices/services/sss/wu_blast_rest>\n\
\n=item *\nL<http://www.ebi.ac.uk/Tools/webservice\
s/tutorials/perl>\n\n=back\n\n=head1 VERSION\n\n$I\
d: wublast_lwp.pl 1317 2009-09-03 15:44:11Z hpm $\\
n\n=cut\n\nuse strict;\nuse warnings;\n\nuse Engli\
sh;\nuse LWP;\nuse XML::Simple;\nuse Getopt::Long \
qw(:config no_ignore_case bundling);\nuse File::Ba\
sename;\nuse Data::Dumper;\n\nmy $baseUrl = 'http:\
//www.ebi.ac.uk/Tools/services/rest/wublast';\n\nm\
y $checkInterval = 3;\n\nmy $outputLevel = 1;\n\nm\
y $numOpts = scalar(@ARGV);\nmy %params = ( 'debug\
Level' => 0 );\n\nmy %tool_params = ();\nGetOption\
s(\n\n	# Tool specific options\n	'program|p=s'    \
 => \\$tool_params{'program'},      # BLAST progra\
m\n	'database|D=s'    => \\$params{'database'},   \
  # Search database\n	'matrix|m=s'      => \\$tool\
_params{'matrix'},       # Scoring matrix\n	'exp|E\
=f'         => \\$tool_params{'exp'},          # E\
-value threshold\n	'viewfilter|e'    => \\$tool_pa\
rams{'viewfilter'},   # Display filtered sequence\\
n	'filter|f=s'      => \\$tool_params{'filter'},  \
     # Low complexity filter name\n	'alignments|n=\
i'  => \\$tool_params{'alignments'},   # Number of\
 alignments\n	'scores|s=i'      => \\$tool_params{\
'scores'},       # Number of scores\n	'sensitivity\
|S=s' => \\$tool_params{'sensitivity'},  # Search \
sensitivity\n	'sort|t=s'        => \\$tool_params{\
'sort'},         # Sort hits by...\n	'stats|T=s'  \
     => \\$tool_params{'stats'},        # Scoring \
statistic to use\n	'strand|d=s'      => \\$tool_pa\
rams{'strand'},       # Strand to use\n	'topcombon\
|c=i'   => \\$tool_params{'topcombon'},    # Consi\
stent sets of HSPs\n	'align|A=i'       => \\$tool_\
params{'align'},   # Pairwise alignment format\n	'\
stype=s' => \\$tool_params{'stype'},    # Sequence\
 type 'protein' or 'dna'\n	'sequence=s' => \\$para\
ms{'sequence'},         # Query sequence file or D\
B:ID\n	'multifasta' => \\$params{'multifasta'},   \
    # Multiple fasta input\n\n	# Compatability opt\
ions, old command-line.\n	'echofilter|e'    => \\$\
params{'echofilter'},   # Display filtered sequenc\
e\n	'b=i'  => \\$params{'numal'},        # Number \
of alignments\n	'appxml=s'        => \\$params{'ap\
pxml'},       # Application XML\n\n	# Generic opti\
ons\n	'email=s'       => \\$params{'email'},      \
    # User e-mail address\n	'title=s'       => \\$\
params{'title'},          # Job title\n	'outfile=s\
'     => \\$params{'outfile'},        # Output fil\
e name\n	'outformat=s'   => \\$params{'outformat'}\
,      # Output file type\n	'jobid=s'       => \\$\
params{'jobid'},          # JobId\n	'help|h'      \
  => \\$params{'help'},           # Usage help\n	'\
async'         => \\$params{'async'},          # A\
synchronous submission\n	'polljob'       => \\$par\
ams{'polljob'},        # Get results\n	'resultType\
s'   => \\$params{'resultTypes'},    # Get result \
types\n	'status'        => \\$params{'status'},   \
      # Get status\n	'params'        => \\$params{\
'params'},         # List input parameters\n	'para\
mDetail=s' => \\$params{'paramDetail'},    # Get d\
etails for parameter\n	'quiet'         => \\$param\
s{'quiet'},          # Decrease output level\n	've\
rbose'       => \\$params{'verbose'},        # Inc\
rease output level\n	'debugLevel=i'  => \\$params{\
'debugLevel'},     # Debug output level\n	'baseUrl\
=s'     => \\$baseUrl,                  # Base URL\
 for service.\n);\nif ( $params{'verbose'} ) { $ou\
tputLevel++ }\nif ( $params{'$quiet'} )  { $output\
Level-- }\n\n&print_debug_message( 'MAIN', 'LWP::V\
ERSION: ' . $LWP::VERSION,\n	1 );\n\n&print_debug_\
message( 'MAIN', \"params:\\n\" . Dumper( \\%param\
s ),           11 );\n&print_debug_message( 'MAIN'\
, \"tool_params:\\n\" . Dumper( \\%tool_params ), \
11 );\n\nmy $scriptName = basename( $0, () );\n\ni\
f ( $params{'help'} || $numOpts == 0 ) {\n	&usage(\
);\n	exit(0);\n}\n\n&print_debug_message( 'MAIN', \
'baseUrl: ' . $baseUrl, 1 );\n\nif (\n	!(\n		   $p\
arams{'polljob'}\n		|| $params{'resultTypes'}\n		|\
| $params{'status'}\n		|| $params{'params'}\n		|| \
$params{'paramDetail'}\n	)\n	&& !( defined( $ARGV[\
0] ) || defined( $params{'sequence'} ) )\n  )\n{\n\
\n	# Bad argument combination, so print error mess\
age and usage\n	print STDERR 'Error: bad option co\
mbination', \"\\n\";\n	&usage();\n	exit(1);\n}\n\n\
elsif ( $params{'params'} ) {\n	&print_tool_params\
();\n}\n\nelsif ( $params{'paramDetail'} ) {\n	&pr\
int_param_details( $params{'paramDetail'} );\n}\n\\
nelsif ( $params{'status'} && defined( $params{'jo\
bid'} ) ) {\n	&print_job_status( $params{'jobid'} \
);\n}\n\nelsif ( $params{'resultTypes'} && defined\
( $params{'jobid'} ) ) {\n	&print_result_types( $p\
arams{'jobid'} );\n}\n\nelsif ( $params{'polljob'}\
 && defined( $params{'jobid'} ) ) {\n	&get_results\
( $params{'jobid'} );\n}\n\nelse {\n\n	# Multiple \
input sequence mode, assume fasta format.\n	if ( $\
params{'multifasta'} ) {\n		&multi_submit_job();\n\
	}\n\n	# Entry identifier list file.\n	elsif (( de\
fined( $params{'sequence'} ) && $params{'sequence'\
} =~ m/^\\@/ )\n		|| ( defined( $ARGV[0] ) && $ARG\
V[0] =~ m/^\\@/ ) )\n	{\n		my $list_filename = $pa\
rams{'sequence'} || $ARGV[0];\n		$list_filename =~\
 s/^\\@//;\n		&list_file_submit_job($list_filename\
);\n	}\n\n	# Default: single sequence/identifier.\\
n	else {\n\n		# Load the sequence data and submit.\
\n		&submit_job( &load_data() );\n	}\n}\n\n=head1 \
FUNCTIONS\n\n=cut\n\n\n=head2 rest_request()\n\nPe\
rform a REST request.\n\n  my $response_str = &res\
t_request($url);\n\n=cut\n\nsub rest_request {\n	p\
rint_debug_message( 'rest_request', 'Begin', 11 );\
\n	my $requestUrl = shift;\n	print_debug_message( \
'rest_request', 'URL: ' . $requestUrl, 11 );\n\n	#\
 Create a user agent\n	my $ua = LWP::UserAgent->ne\
w();\n	'$Revision: 1317 $' =~ m/(\\d+)/;\n	$ua->ag\
ent(\"EBI-Sample-Client/$1 ($scriptName; $OSNAME) \
\" . $ua->agent());\n	$ua->env_proxy;\n\n	# Perfor\
m the request\n	my $response = $ua->get($requestUr\
l);\n	print_debug_message( 'rest_request', 'HTTP s\
tatus: ' . $response->code,\n		11 );\n\n	# Check f\
or HTTP error codes\n	if ( $response->is_error ) {\
\n		$response->content() =~ m/<h1>([^<]+)<\\/h1>/;\
\n		die 'http status: ' . $response->code . ' ' . \
$response->message . '  ' . $1;\n	}\n	print_debug_\
message( 'rest_request', 'End', 11 );\n\n	# Return\
 the response data\n	return $response->content();\\
n}\n\n=head2 rest_get_parameters()\n\nGet list of \
tool parameter names.\n\n  my (@param_list) = &res\
t_get_parameters();\n\n=cut\n\nsub rest_get_parame\
ters {\n	print_debug_message( 'rest_get_parameters\
', 'Begin', 1 );\n	my $url                = $baseU\
rl . '/parameters/';\n	my $param_list_xml_str = re\
st_request($url);\n	my $param_list_xml     = XMLin\
($param_list_xml_str);\n	my (@param_list)       = \
@{ $param_list_xml->{'id'} };\n	print_debug_messag\
e( 'rest_get_parameters', 'End', 1 );\n	return (@p\
aram_list);\n}\n\n=head2 rest_get_parameter_detail\
s()\n\nGet details of a tool parameter.\n\n  my $p\
aramDetail = &rest_get_parameter_details($param_na\
me);\n\n=cut\n\nsub rest_get_parameter_details {\n\
	print_debug_message( 'rest_get_parameter_details'\
, 'Begin', 1 );\n	my $parameterId = shift;\n	print\
_debug_message( 'rest_get_parameter_details',\n		'\
parameterId: ' . $parameterId, 1 );\n	my $url     \
             = $baseUrl . '/parameterdetails/' . $\
parameterId;\n	my $param_detail_xml_str = rest_req\
uest($url);\n	my $param_detail_xml     = XMLin($pa\
ram_detail_xml_str);\n	print_debug_message( 'rest_\
get_parameter_details', 'End', 1 );\n	return ($par\
am_detail_xml);\n}\n\n=head2 rest_run()\n\nSubmit \
a job.\n\n  my $job_id = &rest_run($email, $title,\
 \\%params );\n\n=cut\n\nsub rest_run {\n	print_de\
bug_message( 'rest_run', 'Begin', 1 );\n	my $email\
  = shift;\n	my $title  = shift;\n	my $params = sh\
ift;\n	print_debug_message( 'rest_run', 'email: ' \
. $email, 1 );\n	if ( defined($title) ) {\n		print\
_debug_message( 'rest_run', 'title: ' . $title, 1 \
);\n	}\n	print_debug_message( 'rest_run', 'params:\
 ' . Dumper($params), 1 );\n\n	# User agent to per\
form http requests\n	my $ua = LWP::UserAgent->new(\
);\n	$ua->env_proxy;\n\n	# Clean up parameters\n	m\
y (%tmp_params) = %{$params};\n	$tmp_params{'email\
'} = $email;\n	$tmp_params{'title'} = $title;\n	fo\
reach my $param_name ( keys(%tmp_params) ) {\n		if\
 ( !defined( $tmp_params{$param_name} ) ) {\n			de\
lete $tmp_params{$param_name};\n		}\n	}\n\n	# Subm\
it the job as a POST\n	my $url = $baseUrl . '/run'\
;\n	my $response = $ua->post( $url, \\%tmp_params \
);\n	print_debug_message( 'rest_run', 'HTTP status\
: ' . $response->code, 11 );\n	print_debug_message\
( 'rest_run',\n		'request: ' . $response->request(\
)->content(), 11 );\n\n	# Check for HTTP error cod\
es\n	if ( $response->is_error ) {\n		$response->co\
ntent() =~ m/<h1>([^<]+)<\\/h1>/;\n		die 'http sta\
tus: ' . $response->code . ' ' . $response->messag\
e . '  ' . $1;\n	}\n\n	# The job id is returned\n	\
my $job_id = $response->content();\n	print_debug_m\
essage( 'rest_run', 'End', 1 );\n	return $job_id;\\
n}\n\n=head2 rest_get_status()\n\nCheck the status\
 of a job.\n\n  my $status = &rest_get_status($job\
_id);\n\n=cut\n\nsub rest_get_status {\n	print_deb\
ug_message( 'rest_get_status', 'Begin', 1 );\n	my \
$job_id = shift;\n	print_debug_message( 'rest_get_\
status', 'jobid: ' . $job_id, 2 );\n	my $status_st\
r = 'UNKNOWN';\n	my $url        = $baseUrl . '/sta\
tus/' . $job_id;\n	$status_str = &rest_request($ur\
l);\n	print_debug_message( 'rest_get_status', 'sta\
tus_str: ' . $status_str, 2 );\n	print_debug_messa\
ge( 'rest_get_status', 'End', 1 );\n	return $statu\
s_str;\n}\n\n=head2 rest_get_result_types()\n\nGet\
 list of result types for finished job.\n\n  my (@\
result_types) = &rest_get_result_types($job_id);\n\
\n=cut\n\nsub rest_get_result_types {\n	print_debu\
g_message( 'rest_get_result_types', 'Begin', 1 );\\
n	my $job_id = shift;\n	print_debug_message( 'rest\
_get_result_types', 'jobid: ' . $job_id, 2 );\n	my\
 (@resultTypes);\n	my $url                      = \
$baseUrl . '/resulttypes/' . $job_id;\n	my $result\
_type_list_xml_str = &rest_request($url);\n	my $re\
sult_type_list_xml     = XMLin($result_type_list_x\
ml_str);\n	(@resultTypes) = @{ $result_type_list_x\
ml->{'type'} };\n	print_debug_message( 'rest_get_r\
esult_types',\n		scalar(@resultTypes) . ' result t\
ypes', 2 );\n	print_debug_message( 'rest_get_resul\
t_types', 'End', 1 );\n	return (@resultTypes);\n}\\
n\n=head2 rest_get_result()\n\nGet result data of \
a specified type for a finished job.\n\n  my $resu\
lt = rest_get_result($job_id, $result_type);\n\n=c\
ut\n\nsub rest_get_result {\n	print_debug_message(\
 'rest_get_result', 'Begin', 1 );\n	my $job_id = s\
hift;\n	my $type   = shift;\n	print_debug_message(\
 'rest_get_result', 'jobid: ' . $job_id, 1 );\n	pr\
int_debug_message( 'rest_get_result', 'type: ' . $\
type,    1 );\n	my $url    = $baseUrl . '/result/'\
 . $job_id . '/' . $type;\n	my $result = &rest_req\
uest($url);\n	print_debug_message( 'rest_get_resul\
t', length($result) . ' characters',\n		1 );\n	pri\
nt_debug_message( 'rest_get_result', 'End', 1 );\n\
	return $result;\n}\n\n\n=head2 print_debug_messag\
e()\n\nPrint debug message at specified debug leve\
l.\n\n  &print_debug_message($method_name, $messag\
e, $level);\n\n=cut\n\nsub print_debug_message {\n\
	my $function_name = shift;\n	my $message       = \
shift;\n	my $level         = shift;\n	if ( $level \
<= $params{'debugLevel'} ) {\n		print STDERR '[', \
$function_name, '()] ', $message, \"\\n\";\n	}\n}\\
n\n=head2 print_tool_params()\n\nPrint list of too\
l parameters.\n\n  &print_tool_params();\n\n=cut\n\
\nsub print_tool_params {\n	print_debug_message( '\
print_tool_params', 'Begin', 1 );\n	my (@param_lis\
t) = &rest_get_parameters();\n	foreach my $param (\
 sort(@param_list) ) {\n		print $param, \"\\n\";\n\
	}\n	print_debug_message( 'print_tool_params', 'En\
d', 1 );\n}\n\n=head2 print_param_details()\n\nPri\
nt details of a tool parameter.\n\n  &print_param_\
details($param_name);\n\n=cut\n\nsub print_param_d\
etails {\n	print_debug_message( 'print_param_detai\
ls', 'Begin', 1 );\n	my $paramName = shift;\n	prin\
t_debug_message( 'print_param_details', 'paramName\
: ' . $paramName, 2 );\n	my $paramDetail = &rest_g\
et_parameter_details($paramName);\n	print $paramDe\
tail->{'name'}, \"\\t\", $paramDetail->{'type'}, \\
"\\n\";\n	print $paramDetail->{'description'}, \"\\
\n\";\n	foreach my $value ( @{ $paramDetail->{'val\
ues'}->{'value'} } ) {\n		print $value->{'value'};\
\n		if ( $value->{'defaultValue'} eq 'true' ) {\n	\
		print \"\\t\", 'default';\n		}\n		print \"\\n\";\
\n		print \"\\t\", $value->{'label'}, \"\\n\";\n	}\
\n	print_debug_message( 'print_param_details', 'En\
d', 1 );\n}\n\n=head2 print_job_status()\n\nPrint \
status of a job.\n\n  &print_job_status($job_id);\\
n\n=cut\n\nsub print_job_status {\n	print_debug_me\
ssage( 'print_job_status', 'Begin', 1 );\n	my $job\
id = shift;\n	print_debug_message( 'print_job_stat\
us', 'jobid: ' . $jobid, 1 );\n	if ( $outputLevel \
> 0 ) {\n		print STDERR 'Getting status for job ',\
 $jobid, \"\\n\";\n	}\n	my $result = &rest_get_sta\
tus($jobid);\n	print \"$result\\n\";\n	if ( $resul\
t eq 'FINISHED' && $outputLevel > 0 ) {\n		print S\
TDERR \"To get results: $scriptName --polljob --jo\
bid \" . $jobid\n		  . \"\\n\";\n	}\n	print_debug_\
message( 'print_job_status', 'End', 1 );\n}\n\n=he\
ad2 print_result_types()\n\nPrint available result\
 types for a job.\n\n  &print_result_types($job_id\
);\n\n=cut\n\nsub print_result_types {\n	print_deb\
ug_message( 'result_types', 'Begin', 1 );\n	my $jo\
bid = shift;\n	print_debug_message( 'result_types'\
, 'jobid: ' . $jobid, 1 );\n	if ( $outputLevel > 0\
 ) {\n		print STDERR 'Getting result types for job\
 ', $jobid, \"\\n\";\n	}\n	my $status = &rest_get_\
status($jobid);\n	if ( $status eq 'PENDING' || $st\
atus eq 'RUNNING' ) {\n		print STDERR 'Error: Job \
status is ', $status,\n		  '. To get result types \
the job must be finished.', \"\\n\";\n	}\n	else {\\
n		my (@resultTypes) = &rest_get_result_types($job\
id);\n		if ( $outputLevel > 0 ) {\n			print STDOUT\
 'Available result types:', \"\\n\";\n		}\n		forea\
ch my $resultType (@resultTypes) {\n			print STDOU\
T $resultType->{'identifier'}, \"\\n\";\n			if ( d\
efined( $resultType->{'label'} ) ) {\n				print ST\
DOUT \"\\t\", $resultType->{'label'}, \"\\n\";\n		\
	}\n			if ( defined( $resultType->{'description'} \
) ) {\n				print STDOUT \"\\t\", $resultType->{'de\
scription'}, \"\\n\";\n			}\n			if ( defined( $res\
ultType->{'mediaType'} ) ) {\n				print STDOUT \"\\
\t\", $resultType->{'mediaType'}, \"\\n\";\n			}\n\
			if ( defined( $resultType->{'fileSuffix'} ) ) {\
\n				print STDOUT \"\\t\", $resultType->{'fileSuf\
fix'}, \"\\n\";\n			}\n		}\n		if ( $status eq 'FIN\
ISHED' && $outputLevel > 0 ) {\n			print STDERR \"\
\\n\", 'To get results:', \"\\n\",\n			  \"  $scri\
ptName --polljob --jobid \" . $params{'jobid'} . \\
"\\n\",\n			  \"  $scriptName --polljob --outforma\
t <type> --jobid \"\n			  . $params{'jobid'} . \"\\
\n\";\n		}\n	}\n	print_debug_message( 'result_type\
s', 'End', 1 );\n}\n\n=head2 submit_job()\n\nSubmi\
t a job to the service.\n\n  &submit_job($seq);\n\\
n=cut\n\nsub submit_job {\n	print_debug_message( '\
submit_job', 'Begin', 1 );\n\n	# Set input sequenc\
e\n	$tool_params{'sequence'} = shift;\n\n	# Load p\
arameters\n	&load_params();\n\n	# Submit the job\n\
	my $jobid = &rest_run( $params{'email'}, $params{\
'title'}, \\%tool_params );\n\n	# Simulate sync/as\
ync mode\n	if ( defined( $params{'async'} ) ) {\n	\
	print STDOUT $jobid, \"\\n\";\n		if ( $outputLeve\
l > 0 ) {\n			print STDERR\n			  \"To check status\
: $scriptName --status --jobid $jobid\\n\";\n		}\n\
	}\n	else {\n		if ( $outputLevel > 0 ) {\n			print\
 STDERR \"JobId: $jobid\\n\";\n		}\n		sleep 1;\n		\
&get_results($jobid);\n	}\n	print_debug_message( '\
submit_job', 'End', 1 );\n}\n\n=head2 multi_submit\
_job()\n\nSubmit multiple jobs assuming input is a\
 collection of fasta formatted sequences.\n\n  &mu\
lti_submit_job();\n\n=cut\n\nsub multi_submit_job \
{\n	print_debug_message( 'multi_submit_job', 'Begi\
n', 1 );\n	my $jobIdForFilename = 1;\n	$jobIdForFi\
lename = 0 if ( defined( $params{'outfile'} ) );\n\
	my (@filename_list) = ();\n\n	# Query sequence\n	\
if ( defined( $ARGV[0] ) ) {    # Bare option\n		i\
f ( -f $ARGV[0] || $ARGV[0] eq '-' ) {    # File\n\
			push( @filename_list, $ARGV[0] );\n		}\n	}\n	if\
 ( $params{'sequence'} ) {                   # Via\
 --sequence\n		if ( -f $params{'sequence'} || $par\
ams{'sequence'} eq '-' ) {    # File\n			push( @fi\
lename_list, $params{'sequence'} );\n		}\n	}\n\n	$\
/ = '>';\n	foreach my $filename (@filename_list) {\
\n		open( my $INFILE, '<', $filename )\n		  or die\
 \"Error: unable to open file $filename ($!)\";\n	\
	while (<$INFILE>) {\n			my $seq = $_;\n			$seq =~\
 s/>$//;\n			if ( $seq =~ m/(\\S+)/ ) {\n				print\
 STDERR \"Submitting job for: $1\\n\"\n				  if ( \
$outputLevel > 0 );\n				$seq = '>' . $seq;\n				&\
print_debug_message( 'multi_submit_job', $seq, 11 \
);\n				&submit_job($seq);\n				$params{'outfile'}\
 = undef if ( $jobIdForFilename == 1 );\n			}\n		}\
\n		close $INFILE;\n	}\n	print_debug_message( 'mul\
ti_submit_job', 'End', 1 );\n}\n\n=head2 list_file\
_submit_job()\n\nSubmit multiple jobs using a file\
 containing a list of entry identifiers as \ninput\
.\n\n  &list_file_submit_job($list_filename)\n\n=c\
ut\n\nsub list_file_submit_job {\n	my $filename   \
      = shift;\n	my $jobIdForFilename = 1;\n	$jobI\
dForFilename = 0 if ( defined( $params{'outfile'} \
) );\n\n	# Iterate over identifiers, submitting ea\
ch job\n	open( my $LISTFILE, '<', $filename )\n	  \
or die 'Error: unable to open file ' . $filename .\
 ' (' . $! . ')';\n	while (<$LISTFILE>) {\n		my $l\
ine = $_;\n		chomp($line);\n		if ( $line ne '' ) {\
\n			&print_debug_message( 'list_file_submit_job',\
 'line: ' . $line, 2 );\n			if ( $line =~ m/\\w:\\\
w/ ) {    # Check this is an identifier\n				print\
 STDERR \"Submitting job for: $line\\n\"\n				  if\
 ( $outputLevel > 0 );\n				&submit_job($line);\n	\
		}\n			else {\n				print STDERR\n\"Warning: line \
\\\"$line\\\" is not recognised as an identifier\\\
n\";\n			}\n		}\n		$params{'outfile'} = undef if (\
 $jobIdForFilename == 1 );\n	}\n	close $LISTFILE;\\
n}\n\n=head2 load_data()\n\nLoad sequence data fro\
m file or option specified on the command-line.\n\\
n  &load_data();\n\n=cut\n\nsub load_data {\n	prin\
t_debug_message( 'load_data', 'Begin', 1 );\n	my $\
retSeq;\n\n	# Query sequence\n	if ( defined( $ARGV\
[0] ) ) {    # Bare option\n		if ( -f $ARGV[0] || \
$ARGV[0] eq '-' ) {    # File\n			$retSeq = &read_\
file( $ARGV[0] );\n		}\n		else {                  \
                   # DB:ID or sequence\n			$retSeq\
 = $ARGV[0];\n		}\n	}\n	if ( $params{'sequence'} )\
 {                   # Via --sequence\n		if ( -f $\
params{'sequence'} || $params{'sequence'} eq '-' )\
 {    # File\n			$retSeq = &read_file( $params{'se\
quence'} );\n		}\n		else {    # DB:ID or sequence\\
n			$retSeq = $params{'sequence'};\n		}\n	}\n	prin\
t_debug_message( 'load_data', 'End', 1 );\n	return\
 $retSeq;\n}\n\n=head2 load_params()\n\nLoad job p\
arameters from command-line options.\n\n  &load_pa\
rams();\n\n=cut\n\nsub load_params {\n	print_debug\
_message( 'load_params', 'Begin', 1 );\n\n	# Datab\
ase(s) to search\n	my (@dbList) = split /[ ,]/, $p\
arams{'database'};\n	$tool_params{'database'} = \\\
@dbList;\n\n	# Compatability options, old command-\
line.\n	if(!$tool_params{'viewfilter'} && $params{\
'echofilter'}) {\n		$tool_params{'viewfilter'} = '\
true';\n	}\n	if(!$tool_params{'alignments'} && $pa\
rams{'numal'}) {\n		$tool_params{'alignments'} = $\
params{'numal'};\n	}\n	# TODO: set alignment forma\
t option to get NCBI BLAST XML.\n	if($params{'appx\
ml'}) {\n		$tool_params{'align'} = '';\n	}\n\n	pri\
nt_debug_message( 'load_params', 'End', 1 );\n}\n\\
n=head2 client_poll()\n\nClient-side job polling.\\
n\n  &client_poll($job_id);\n\n=cut\n\nsub client_\
poll {\n	print_debug_message( 'client_poll', 'Begi\
n', 1 );\n	my $jobid  = shift;\n	my $status = 'PEN\
DING';\n\n	my $errorCount = 0;\n	while ($status eq\
 'RUNNING'\n		|| $status eq 'PENDING'\n		|| ( $sta\
tus eq 'ERROR' && $errorCount < 2 ) )\n	{\n		$stat\
us = rest_get_status($jobid);\n		print STDERR \"$s\
tatus\\n\" if ( $outputLevel > 0 );\n		if ( $statu\
s eq 'ERROR' ) {\n			$errorCount++;\n		}\n		elsif \
( $errorCount > 0 ) {\n			$errorCount--;\n		}\n		i\
f (   $status eq 'RUNNING'\n			|| $status eq 'PEND\
ING'\n			|| $status eq 'ERROR' )\n		{\n\n			# Wait\
 before polling again.\n			sleep $checkInterval;\n\
		}\n	}\n	print_debug_message( 'client_poll', 'End\
', 1 );\n	return $status;\n}\n\n=head2 get_results\
()\n\nGet the results for a job identifier.\n\n  &\
get_results($job_id);\n\n=cut\n\nsub get_results {\
\n	print_debug_message( 'get_results', 'Begin', 1 \
);\n	my $jobid = shift;\n	print_debug_message( 'ge\
t_results', 'jobid: ' . $jobid, 1 );\n\n	# Verbose\
\n	if ( $outputLevel > 1 ) {\n		print 'Getting res\
ults for job ', $jobid, \"\\n\";\n	}\n\n	# Check s\
tatus, and wait if not finished\n	client_poll($job\
id);\n\n	# Use JobId if output file name is not de\
fined\n	unless ( defined( $params{'outfile'} ) ) {\
\n		$params{'outfile'} = $jobid;\n	}\n\n	# Get lis\
t of data types\n	my (@resultTypes) = rest_get_res\
ult_types($jobid);\n\n	# Get the data and write it\
 to a file\n	if ( defined( $params{'outformat'} ) \
) {    # Specified data type\n		my $selResultType;\
\n		foreach my $resultType (@resultTypes) {\n			if\
 ( $resultType->{'identifier'} eq $params{'outform\
at'} ) {\n				$selResultType = $resultType;\n			}\\
n		}\n		if ( defined($selResultType) ) {\n			my $r\
esult =\n			  rest_get_result( $jobid, $selResultT\
ype->{'identifier'} );\n			if ( $params{'outfile'}\
 eq '-' ) {\n				write_file( $params{'outfile'}, $\
result );\n			}\n			else {\n				write_file(\n					\
$params{'outfile'} . '.'\n					  . $selResultType-\
>{'identifier'} . '.'\n					  . $selResultType->{'\
fileSuffix'},\n					$result\n				);\n			}\n		}\n		\
else {\n			die 'Error: unknown result format \"' .\
 $params{'outformat'} . '\"';\n		}\n	}\n	else {   \
 # Data types available\n		      # Write a file fo\
r each output type\n		for my $resultType (@resultT\
ypes) {\n			if ( $outputLevel > 1 ) {\n				print S\
TDERR 'Getting ', $resultType->{'identifier'}, \"\\
\n\";\n			}\n			my $result = rest_get_result( $job\
id, $resultType->{'identifier'} );\n			if ( $param\
s{'outfile'} eq '-' ) {\n				write_file( $params{'\
outfile'}, $result );\n			}\n			else {\n				write_\
file(\n					$params{'outfile'} . '.'\n					  . $re\
sultType->{'identifier'} . '.'\n					  . $resultTy\
pe->{'fileSuffix'},\n					$result\n				);\n			}\n	\
	}\n	}\n	print_debug_message( 'get_results', 'End'\
, 1 );\n}\n\n=head2 read_file()\n\nRead a file int\
o a scalar. The special filename '-' can be used t\
o read from \nstandard input (STDIN).\n\n  my $dat\
a = &read_file($filename);\n\n=cut\n\nsub read_fil\
e {\n	print_debug_message( 'read_file', 'Begin', 1\
 );\n	my $filename = shift;\n	print_debug_message(\
 'read_file', 'filename: ' . $filename, 2 );\n	my \
( $content, $buffer );\n	if ( $filename eq '-' ) {\
\n		while ( sysread( STDIN, $buffer, 1024 ) ) {\n	\
		$content .= $buffer;\n		}\n	}\n	else {    # File\
\n		open( my $FILE, '<', $filename )\n		  or die \\
"Error: unable to open input file $filename ($!)\"\
;\n		while ( sysread( $FILE, $buffer, 1024 ) ) {\n\
			$content .= $buffer;\n		}\n		close($FILE);\n	}\\
n	print_debug_message( 'read_file', 'End', 1 );\n	\
return $content;\n}\n\n=head2 write_file()\n\nWrit\
e data to a file. The special filename '-' can be \
used to write to \nstandard output (STDOUT).\n\n  \
&write_file($filename, $data);\n\n=cut\n\nsub writ\
e_file {\n	print_debug_message( 'write_file', 'Beg\
in', 1 );\n	my ( $filename, $data ) = @_;\n	print_\
debug_message( 'write_file', 'filename: ' . $filen\
ame, 2 );\n	if ( $outputLevel > 0 ) {\n		print STD\
ERR 'Creating result file: ' . $filename . \"\\n\"\
;\n	}\n	if ( $filename eq '-' ) {\n		print STDOUT \
$data;\n	}\n	else {\n		open( my $FILE, '>', $filen\
ame )\n		  or die \"Error: unable to open output f\
ile $filename ($!)\";\n		syswrite( $FILE, $data );\
\n		close($FILE);\n	}\n	print_debug_message( 'writ\
e_file', 'End', 1 );\n}\n\n=head2 usage()\n\nPrint\
 program usage message.\n\n  &usage();\n\n=cut\n\n\
sub usage {\n	print STDERR <<EOF\nWU-BLAST\n======\
==\n   \nRapid sequence database search programs u\
tilizing the BLAST algorithm\n    \n[Required]\n\n\
  -p, --program      : str  : BLAST program to use\
, see --paramDetail program\n  -D, --database     \
: str  : database(s) to search, space separated. S\
ee\n                              --paramDetail da\
tabase\n      --stype        : str  : query sequen\
ce type, see --paramDetail stype\n  seqFile       \
     : file : query sequence (\"-\" for STDIN, \\@\
filename for\n                              identi\
fier list file)\n\n[Optional]\n\n  -m, --matrix   \
    : str  : scoring matrix, see --paramDetail mat\
rix\n  -e, --exp          : real : 0<E<= 1000. Sta\
tistical significance threshold \n                \
              for reporting database sequence matc\
hes.\n  -e, --viewfilter   :      : display the fi\
ltered query sequence\n  -f, --filter       : str \
 : filter the query sequence for low complexity \n\
                              regions, see --param\
Detail filter\n  -A, --align        : int  : pairw\
ise alignment format, see --paramDetail align\n  -\
s, --scores       : int  : number of scores to be \
reported\n  -b, --alignments   : int  : number of \
alignments to report\n  -S, --sensitivity  : str  \
: sensitivity of the search, \n                   \
           see --paramDetail sensitivity\n  -t, --\
sort	     : str  : sort order for hits, see --para\
mDetail sort\n  -T, --stats        : str  : statis\
tical model, see --paramDetail stats\n  -d, --stra\
nd       : str  : DNA strand to search with,\n    \
                          see --paramDetail strand\
\n  -c, --topcombon    : str  : consistent sets of\
 HSPs\n      --multifasta   :      : treat input a\
s a set of fasta formatted sequences\n\n[General]\\
n\n  -h, --help        :      : prints this help t\
ext\n      --async       :      : forces to make a\
n asynchronous query\n      --email       : str  :\
 e-mail address\n      --title       : str  : titl\
e for job\n      --status      :      : get job st\
atus\n      --resultTypes :      : get available r\
esult types for job\n      --polljob     :      : \
poll for the status of a job\n      --jobid       \
: str  : jobid that was returned when an asynchron\
ous job \n                             was submitt\
ed.\n      --outfile     : str  : file name for re\
sults (default is jobid;\n                        \
     \"-\" for STDOUT)\n      --outformat   : str \
 : result format to retrieve\n      --params      \
:      : list input parameters\n      --paramDetai\
l : str  : display details for input parameter\n  \
    --quiet       :      : decrease output\n      \
--verbose     :      : increase output\n      --tr\
ace       :      : show SOAP messages being interc\
hanged \n   \nSynchronous job:\n\n  The results/er\
rors are returned as soon as the job is finished.\\
n  Usage: $scriptName --email <your\\@email> [opti\
ons...] seqFile\n  Returns: results as an attachme\
nt\n\nAsynchronous job:\n\n  Use this if you want \
to retrieve the results at a later time. The resul\
ts \n  are stored for up to 24 hours. 	\n  Usage: \
$scriptName --async --email <your\\@email> [option\
s...] seqFile\n  Returns: jobid\n\n  Use the jobid\
 to query for the status of the job. If the job is\
 finished, \n  it also returns the results/errors.\
\n  Usage: $scriptName --polljob --jobid <jobId> [\
--outfile string]\n  Returns: string indicating th\
e status of the job and if applicable, results \n \
 as an attachment.\n\nFurther information:\n\n  ht\
tp://www.ebi.ac.uk/Tools/webservices/services/sss/\
wu_blast_rest\n  http://www.ebi.ac.uk/Tools/webser\
vices/tutorials/perl\n\nSupport/Feedback:\n\n  htt\
p://www.ebi.ac.uk/support/\nEOF\n}\n\n=head1 FEEDB\
ACK/SUPPORT\n\nPlease contact us at L<http://www.e\
bi.ac.uk/support/> if you have any \nfeedback, sug\
gestions or issues with the service or this client\
.\n\n=cut\n","\n\n\nmy $PROBTRESH = 0.3;# base pai\
rs below this prob threshold will be ignored\nmy $\
WEIGHT = 100.0; # float!!\nmy $NUCALPH = \"ACGTUNR\
YMKSWHBVD\";\nuse vars qw($NUCALPH $WEIGHT);\n\nmy\
 $myname = basename($0);\n\nuse strict;\nuse warni\
ngs;\n\nuse File::Basename;\nuse Getopt::Long;\nus\
e File::Glob ':glob';\nuse File::Spec;\nuse File::\
Temp qw/ tempfile tempdir /;\n\n\n\n\nsub tcoffeel\
ib_header($;$)\n{\n    my ($nseq, $fd) = @_;\n    \
if (! defined($fd)) {\n        $fd = *STDOUT;\n   \
 }\n    printf $fd \"! TC_LIB_FORMAT_01\\n\";\n   \
 printf $fd \"%d\\n\", $nseq;\n}\n\n\nsub tcoffeel\
ib_header_addseq($$;$)\n{\n    my ($id, $seq, $fd)\
 = @_;\n    if (! defined($fd)) {\n        $fd = *\
STDOUT;\n    }\n    printf $fd \"%s %d %s\\n\", $i\
d, length($seq), $seq;\n}\n\n\nsub tcoffeelib_comm\
ent($;$)\n{\n    my ($comment, $fd) = @_;\n    if \
(! defined($fd)) {\n        $fd = *STDOUT;\n    }\\
n    printf $fd \"!\" . $comment . \"\\n\";\n}\n\n\
\nsub tcoffeelib_struct($$$;$)\n{\n    my ($nseq, \
$len, $bpm, $fd) = @_;\n\n    if (! defined($fd)) \
{\n        $fd = *STDOUT;\n    }\n\n    # output b\
asepair indices with fixed weight\n    printf $fd \
\"#%d %d\\n\", $nseq, $nseq;\n    # output basepai\
rs (only once) and with unit-offset\n    for (my $\
i=0; $i<$len; $i++) {\n        for (my $j=$i+1; $j\
<$len; $j++) {\n            if (! defined($bpm->[$\
i][$j])) {\n                print STDERR \"ERROR: \
\\$bpm->[$i][$j] undefined\\n\";\n            }\n \
           if ($bpm->[$i][$j]>0) {\n              \
  print $fd $i+1;\n                print $fd \" \"\
;\n                print $fd $j+1;\n              \
  print $fd \" \" . $bpm->[$i][$j] . \"\\n\";\n   \
         }\n        }\n    }\n}\n\n\nsub tcoffeeli\
b_footer(;$)\n{\n    my ($fd) = @_;\n    if (! def\
ined($fd)) {\n        $fd = *STDOUT;\n    }\n    p\
rint $fd \"! SEQ_1_TO_N\\n\";\n}\n\n\n    \nsub pl\
fold($$$)\n{    \n    my ($id, $seq, $probtresh) =\
 @_;\n    my (@struct);# return\n    my ($templ, $\
fhtmp, $fnametmp, $cmd, $ctr, $window_size);\n    \
our $ntemp++;\n    \n    $templ = $myname . \".pid\
-\" . $$ .$ntemp .\".XXXXXX\";\n    ($fhtmp, $fnam\
etmp) = tempfile($templ, UNLINK => 1); \n    print\
 $fhtmp \">$id\\n$seq\\n\";\n\n    # --- init base\
pair array\n    #\n    for (my $i=0; $i<length($se\
q); $i++) {\n        for (my $j=$i+1; $j<length($s\
eq); $j++) {\n            $struct[$i][$j]=0;\n    \
    }\n    }\n\n\n    # --- call rnaplfold and dro\
p a readme\n    #\n    $window_size=(length($seq)<\
70)?length($seq):70;\n    $cmd = \"RNAplfold -W $w\
indow_size < $fnametmp >/dev/null\";\n    system($\
cmd);\n    \n    if ($? != 0) {\n        printf ST\
DERR \"ERROR: RNAplfold ($cmd) exited with error s\
tatus %d\\n\", $? >> 8;\n        return;\n    }\n \
   #unlink($fnametmp);\n    my $fps = sprintf(\"%s\
_dp.ps\", $id); # check long name\n    \n    if (!\
 -s $fps) {\n      {\n\n	$fps = sprintf(\"%s_dp.ps\
\", substr($id,0,12)); # check short name\n 	if (!\
 -s $fps)\n	  {\n	    die(\"couldn't find expected\
 file $fps\\n\");\n	    return;\n	  }\n      }\n  \
  }\n\n    \n    # --- read base pairs from create\
d postscript\n    #\n    open(FH, $fps);\n    whil\
e (my $line = <FH>) {\n        my ($nti, $ntj, $pr\
ob);\n        chomp($line);        \n        # lin\
e: bp bp sqrt-prob ubox\n        my @match = ($lin\
e =~ m/^([0-9]+) +([0-9]+) +([0-9\\.]+) +ubox$/);\\
n        if (scalar(@match)) {\n            $nti=$\
1;\n            $ntj=$2;\n            $prob=$3*$3;\
# prob stored as square root\n\n            if ($p\
rob>$probtresh) {\n                #printf STDERR \
\"\\$struct[$nti][$ntj] sqrtprob=$3 prob=$prob > $\
probtresh\\n\";\n                $struct[$nti-1][$\
ntj-1] = $WEIGHT\n            }\n            # sto\
re with zero-offset\n        }\n    }\n    close(F\
H);\n\n    # remove or gzi postscript\n    #\n    \
unlink($fps);\n    #\n    # or gzip\n    #$cmd = \\
"gzip -qf $fps\";\n    #system($cmd);\n    #if ($?\
 != 0) {\n    #    printf STDERR \"ERROR: gzip ($c\
md) exited with error status %d\\n\", $? >> 8;\n  \
  #}\n\n    return \\@struct;\n}\n\n\n\n\n\nsub rn\
aseqfmt($)\n{\n    my ($seq) = @_;\n    # remove g\
aps\n    $seq =~ s/-//g;\n    # uppercase RNA\n   \
 $seq = uc($seq);\n    # T -> U\n    $seq =~ s/T/U\
/g;\n    # check for invalid charaters\n    $_ = $\
seq;\n    s/[^$NUCALPH]//g;\n    return $_;\n}\n\n\
\n\n\nsub usage(;$)\n{    \n    my ($errmsg) = @_;\
\n    if ($errmsg) {\n        print STDERR \"ERROR\
: $errmsg\\n\";\n    }\n    print STDERR << \"EOF\\
";\n$myname:\n Creates a T-Coffee RNA structure li\
brary from RNAplfold prediction.\n See FIXME:citat\
ion\nUsage:\n $myname -in seq_file -out tcoffee_li\
b\nEOF\n    exit(1);\n}\n\nsub read_fasta_seq \n  \
{\n    my $f=$_[0];\n    my %hseq;\n    my (@seq, \
@com, @name);\n    my ($a, $s,$nseq);\n\n    open \
(F, $f);\n    while (<F>)\n      {\n	$s.=$_;\n    \
  }\n    close (F);\n\n    \n    @name=($s=~/>(\\S\
*).*\\n[^>]*/g);\n    \n    @seq =($s=~/>.*.*\\n([\
^>]*)/g);\n    @com =($s=~/>(\\S*)(.*)\\n([^>]*)/g\
);\n\n\n    $nseq=$#name+1;\n  \n    for ($a=0; $a\
<$nseq; $a++)\n      {\n	my $n=$name[$a];\n	my $s;\
\n	$hseq{$n}{name}=$n;\n	$s=$seq[$a];$s=~s/\\s//g;\
\n	\n	$hseq{$n}{seq}=$s;\n	$hseq{$n}{com}=$com[$a]\
;\n      }\n    return %hseq;\n  }\n\n\n\n\n\n\n\n\
my $fmsq = \"\";\nmy $flib = \"\";\nmy %OPTS;\nmy \
%seq;\nmy ($id, $nseq, $i);\nmy @nl;\n\nGetOptions\
(\"in=s\" => \\$fmsq, \"out=s\" => \\$flib);\n\nif\
 (! -s $fmsq) {\n    usage(\"empty or non-existant\
 file \\\"$fmsq\\\"\")\n}\nif (length($flib)==0) {\
\n    usage(\"empty out-filename\")\n}\n\n\n\n\n\n\
\n%seq=read_fasta_seq($fmsq);\n\n\n@nl=keys(%seq);\
\n\n$nseq=$#nl+1;\nopen FD_LIB, \">$flib\" or die \
\"can't open $flib!\";\ntcoffeelib_header($nseq, *\
FD_LIB);\nforeach $id (keys (%seq))\n  {\n    my (\
$seq, $fmtseq);\n    \n    $seq = $seq{$id}{seq};\\
n    \n    $fmtseq = rnaseqfmt($seq);# check here,\
 formatting for folding important later\n    if (l\
ength($seq)!=length($fmtseq)) {\n        print STD\
ERR \"ERROR: invalid sequence $id is not an RNA se\
quence. read seq is: $seq\\n\";\n        exit\n   \
   }\n   \n    tcoffeelib_header_addseq($id, uc($s\
eq), *FD_LIB);\n  }\ntcoffeelib_comment(\"generate\
d by $myname on \" . localtime(), *FD_LIB);\n\n\n\\
n$i=0;\nforeach $id (keys (%seq))\n  {\n    my ($c\
leanid, $seq, $bpm);\n    $seq=$seq{$id}{seq};\n  \
  $cleanid = $id;\n    $cleanid =~ s,[/ ],_,g;# ne\
eded for rnaplfold\n    $seq = rnaseqfmt($seq);\n \
   \n    $bpm = plfold($cleanid, rnaseqfmt($seq), \
$PROBTRESH);       \n    \n    tcoffeelib_struct($\
i+1, length($seq), $bpm, *FD_LIB);\n    $i++;\n}\n\
\n\ntcoffeelib_footer(*FD_LIB);\nclose FD_LIB;\nex\
it (0);\n\n","\n\n\n\n\n$cmd=join ' ', @ARGV;\nif \
($cmd=~/-infile=(\\S+)/){ $seqfile=$1;}\nif ($cmd=\
~/-outfile=(\\S+)/){ $libfile=$1;}\n\n\n\n%s=read_\
fasta_seq ($seqfile);\n\nopen (F, \">$libfile\");\\
nforeach $name (keys (%s))\n  {\n    my $tclib=\"$\
name.RNAplfold_tclib\";\n    print (F \">$name _F_\
 $tclib\\n\");\n    seq2RNAplfold2tclib ($name, $s\
{$name}{seq}, $tclib);\n  }\nclose (F);\nexit (EXI\
T_SUCCESS);\n\nsub seq2RNAplfold2tclib\n  {\n    m\
y ($name, $seq, $tclib)=@_;\n    my ($tmp);\n    $\
n++;\n    $tmp=\"tmp4seq2RNAplfold_tclib.$$.$n.pep\
\";\n    open (RF, \">$tmp\");\n    print (RF \">$\
name\\n$seq\\n\");\n    close (RF);\n    \n    sys\
tem \"t_coffee -other_pg RNAplfold2tclib.pl -in=$t\
mp -out=$tclib\";\n    \n    unlink ($tmp);\n    r\
eturn $tclib;\n  }\n    \n    \nsub read_fasta_seq\
 \n  {\n    my $f=@_[0];\n    my %hseq;\n    my (@\
seq, @com, @name);\n    my ($a, $s,$nseq);\n\n    \
open (F, $f);\n    while (<F>)\n      {\n	$s.=$_;\\
n      }\n    close (F);\n\n    \n    @name=($s=~/\
>(\\S*).*\\n[^>]*/g);\n    \n    @seq =($s=~/>.*.*\
\\n([^>]*)/g);\n    @com =($s=~/>\\S*(.*)\\n([^>]*\
)/g);\n\n    \n    $nseq=$#name+1;\n    \n    for \
($a=0; $a<$nseq; $a++)\n      {\n	my $n=$name[$a];\
\n	$hseq{$n}{name}=$n;\n	$hseq{$n}{seq}=$seq[$a];\\
n	$hseq{$n}{com}=$com[$a];\n      }\n    return %h\
seq;\n  }\n","use Getopt::Long;\nuse File::Path;\n\
use Env;\nuse FileHandle;\nuse Cwd;\nuse Sys::Host\
name;\nour $PIDCHILD;\nour $ERROR_DONE;\nour @TMPF\
ILE_LIST;\nour $EXIT_FAILURE=1;\nour $EXIT_SUCCESS\
=0;\n\nour $REFDIR=getcwd;\nour $EXIT_SUCCESS=0;\n\
our $EXIT_FAILURE=1;\n\nour $PROGRAM=\"tc_generic_\
method.pl\";\nour $CL=$PROGRAM;\n\nour $CLEAN_EXIT\
_STARTED;\nour $debug_lock=$ENV{\"DEBUG_LOCK\"};\n\
our $LOCKDIR=$ENV{\"LOCKDIR_4_TCOFFEE\"};\nif (!$L\
OCKDIR){$LOCKDIR=getcwd();}\nour $ERRORDIR=$ENV{\"\
ERRORDIR_4_TCOFFEE\"};\nour $ERRORFILE=$ENV{\"ERRO\
RFILE_4_TCOFFEE\"};\n&set_lock ($$);\nif (isshellp\
id(getppid())){lock4tc(getppid(), \"LLOCK\", \"LSE\
T\", \"$$\\n\");}\n      \nour $print;\nmy ($fmsq1\
, $fmsq2, $output, $outfile, $arch, $psv, $hmmtop_\
home, $trim, $cov, $sample, $mode, $gor_home, $gor\
_seq, $gor_obs);\n\nGetOptions(\"-in=s\" => \\$fms\
q1,\"-output=s\" =>\\$output ,\"-out=s\" => \\$out\
file, \"-arch=s\" => \\$arch,\"-psv=s\" => \\$psv,\
 \"-hmmtop_home=s\", \\$hmmtop_home,\"-trim=s\" =>\
\\$trim ,\"-print=s\" =>\\$print,\"-cov=s\" =>\\$c\
ov , \"-sample=s\" =>\\$sample, \"-mode=s\" =>\\$m\
ode, \"-gor_home=s\"=>\\$gor_home, \"-gor_seq=s\"=\
>\\$gor_seq,\"-gor_obs=s\"=>\\$gor_obs);\n\n\nif (\
!$mode){$mode = \"hmmtop\"}\nelsif ($mode eq \"hmm\
top\"){;}\nelsif ($mode eq \"gor\"){;}\nelse {myex\
it(flush_error (\"-mode=$mode is unknown\"));}\n\n\
\nour $HOME=$ENV{\"HOME\"};\nour $MCOFFEE=($ENV{\"\
MCOFFEE_4_TCOFFEE\"})?$ENV{\"MCOFFEE_4_TCOFFEE\"}:\
\"$HOME/.t_coffee/mcoffee\";\n\nif ($mode eq \"hmm\
top\")\n  {\n    check_configuration (\"hmmtop\");\
\n    if (-e $arch){$ENV{'HMMTOP_ARCH'}=$arch;}\n \
   elsif (-e $ENV{HMMTOP_ARCH}){$arch=$ENV{HMMTOP_\
ARCH};}\n    elsif (-e \"$MCOFFEE/hmmtop.arch\"){$\
arch=$ENV{'HMMTOP_ARCH'}=\"$MCOFFEE/hmmtop.arch\";\
}\n    elsif (-e \"$hmmtop_home/hmmtop.arc\"){$arc\
h=$ENV{'HMMTOP_ARCH'}=\"$hmmtop_home/hmmtop.arc\";\
}\n    else {myexit(flush_error ( \"Could not find\
 ARCH file for hmmtop\"));}\n    \n    \n    if (-\
e $psv){$ENV{'HMMTOP_PSV'}=$psv;}\n    elsif (-e $\
ENV{HMMTOP_PSV}){$psv=$ENV{HMMTOP_PSV};}\n    elsi\
f (-e \"$MCOFFEE/hmmtop.psv\"){$psv=$ENV{'HMMTOP_P\
SV'}=\"$MCOFFEE/hmmtop.psv\";}\n    elsif (-e \"$h\
mmtop_home/hmmtop.psv\"){$psv=$ENV{'HMMTOP_PSV'}=\\
"$hmmtop_home/hmmtop.psv\";}\n    else {myexit(flu\
sh_error ( \"Could not find PSV file for hmmtop\")\
);}\n  }\nelsif ($mode eq \"gor\")\n  {\n    our $\
GOR_SEQ;\n    our $GOR_OBS;\n    \n    check_confi\
guration (\"gorIV\");\n    if (-e $gor_seq){$GOR_S\
EQ=$gor_seq;}\n    elsif (-e $ENV{GOR_SEQ}){$GOR_S\
EQ=$ENV{GOR_SEQ};}\n    elsif (-e \"$MCOFFEE/New_K\
S.267.seq\"){$GOR_SEQ=\"$MCOFFEE/New_KS.267.seq\";\
}\n    elsif (-e \"$gor_home/New_KS.267.seq\"){$GO\
R_SEQ=\"$gor_home/New_KS.267.seq\";}\n    else {my\
exit(flush_error ( \"Could not find SEQ file for g\
or\"));}\n\n    if (-e $gor_obs){$GOR_OBS=$gor_obs\
;}\n    elsif (-e $ENV{GOR_OBS}){$GOR_OBS=$ENV{GOR\
_OBS};}\n    elsif (-e \"$MCOFFEE/New_KS.267.obs\"\
){$GOR_OBS=\"$MCOFFEE/New_KS.267.obs\";}\n    elsi\
f (-e \"$gor_home/New_KS.267.obs\"){$GOR_OBS=\"$go\
r_home/New_KS.267.obs\";}\n    else {myexit(flush_\
error ( \"Could not find OBS file for gor\"));}\n \
 }\n\n\nif ( ! -e $fmsq1){myexit(flush_error (\"Co\
uld Not Read Input file $fmsq1\"));}\n\n\nmy $fmsq\
2=vtmpnam();\nmy $fmsq3=vtmpnam();\nmy $tmpfile=vt\
mpnam();\nmy $predfile=vtmpnam();\n\nif ($trim){$t\
rim_action=\" +trim _aln_%%$trim\\_K1 \";}\nif ($c\
ov) {$cov_action= \" +sim_filter _aln_c$cov \";}\n\
&safe_system(\"t_coffee -other_pg seq_reformat -in\
 $fmsq1 -action +convert 'BOUJXZ-' $cov_action $tr\
im_action -output fasta_aln -out $fmsq2\");\nmy (%\
pred, %seq, %predA);\n\n\n%seq=read_fasta_seq($fms\
q2);\n%seq=fasta2sample(\\%seq, $sample);\n\nif (1\
==2 && $mode eq \"hmmtop\" && $output eq \"cons\")\
\n  {\n    fasta2hmmtop_cons($outfile,\\%seq);\n  \
}\nelse\n  {\n    %pred=fasta2pred(\\%seq, $mode);\
\n    %predA=pred2aln (\\%pred, \\%seq);\n    \n  \
  \n    if (!$output || $output eq \"prediction\")\
{output_fasta_seq (\\%predA, $outfile);}\n    elsi\
f ($output eq \"color_html\"){pred2color (\\%pred,\
\\%seq, $outfile);}\n    elsif ($output eq \"cons\\
"){pred2cons($outfile,\\%predA);}\n    else {flush\
_error (\"$output is an unknown output mode\");}\n\
  }\n\nsub fasta2sample\n  {\n    my $SR=shift;\n \
   my $it=shift;\n    my %S=%$SR;\n    \n    my $s\
eq=index2seq_name (\\%S, 1);\n    my $l=length($S{\
$seq}{seq});\n    my @sl=keys(%S);\n    my $nseq=$\
#sl+1;\n    my $index=$nseq;\n  \n    if (!$sample\
) {return %S;}\n    for (my $a=0; $a<$it; $a++)\n \
     {\n	my $newseq=\"\";\n	my $nname=\"$seq\\_sam\
pled_$index\";\n	for (my $p=0; $p<$l; $p++)\n	  {\\
n	    my $i=int(rand($nseq));\n	    \n	    my $nam\
e = $sl[$i];\n	    my $seq=$S{$name}{seq};\n	    m\
y $r=substr ($seq, $p, 1);\n	    $newseq.=$r;\n	  \
}\n	$S{$nname}{name}=$nname;\n	$S{$nname}{seq}=$ne\
wseq;\n	$S{$nname}{com}=\"sampled\";\n	$S{$nname}{\
index}=++$index;\n      }\n    return %S;\n  }\n	 \
     \nsub fasta2pred\n  {\n    my $s=shift;\n    \
my $mode=shift;\n\n    if ( $mode eq \"hmmtop\"){r\
eturn fasta2hmmtop_pred($s);}\n    elsif ($mode eq\
 \"gor\"){return fasta2gor_pred ($s);}\n  }\nsub f\
asta2hmmtop_cons\n  {\n    my $outfile=shift;\n   \
 my $SR=shift;\n    \n    my $o = new FileHandle;\\
n    my $i = new FileHandle;\n    my $tmp_in =vtmp\
nam();\n    my $tmp_out=vtmpnam();\n    my %seq=%$\
SR;\n    my %pred;\n    my $N=keys(%seq);\n    \n \
   output_fasta_seq (\\%seq,$tmp_in, \"seq\");\n  \
  `hmmtop -pi=mpred -if=$tmp_in -sf=FAS -pl 2>/dev\
/null >$tmp_out`;\n    open ($o, \">$outfile\");\n\
    open ($i, \"$tmp_out\");\n    while (<$i>)\n  \
    {\n	my $l=$_;\n	if (($l=~/>HP\\:\\s+(\\d+)\\s+\
(.*)/)){my $line=\">$2 NSEQ: $N\\n\";print $o \"$l\
ine\";}\n	elsif ( ($l=~/.*pred(.*)/))  {my $line=\\
"$1\\n\";print $o \"$line\";}\n      }\n    close \
($o);\n    close ($i);\n    return read_fasta_seq(\
$tmp);\n  }\nsub fasta2hmmtop_pred\n  {\n    my $S\
R=shift;\n    my $o = new FileHandle;\n    my $i =\
 new FileHandle;\n    my $tmp    =vtmpnam();\n    \
my $tmp_in =vtmpnam();\n    my $tmp_out=vtmpnam();\
\n    my %seq=%$SR;\n    my %pred;\n    \n\n    ou\
tput_fasta_seq (\\%seq,$tmp_in, \"seq\");\n    `hm\
mtop -if=$tmp_in -sf=FAS -pl 2>/dev/null >$tmp_out\
`;\n    open ($o, \">$tmp\");\n    open ($i, \"$tm\
p_out\");\n    while (<$i>)\n      {\n	my $l=$_;\n\
	if (($l=~/>HP\\:\\s+(\\d+)\\s+(.*)/)){my $line=\"\
>$2\\n\";print $o \"$line\";}\n	elsif ( ($l=~/.*pr\
ed(.*)/))  {my $line=\"$1\\n\";print $o \"$line\";\
}\n      }\n    close ($o);\n    close ($i);\n    \
return read_fasta_seq($tmp);\n  }\n    \n	\n	\n	  \
  \n	\n	\n\n	\nsub fasta2gor_pred\n  {\n    my $SR\
=shift;\n    my $o = new FileHandle;\n    my $i = \
new FileHandle;\n    my $tmp    =vtmpnam();\n    m\
y $tmp_in =vtmpnam();\n    my $tmp_out=vtmpnam();\\
n    my %seq=%$SR;\n    my %pred;\n    \n\n    out\
put_fasta_seq (\\%seq,$tmp_in, \"seq\");\n    `gor\
IV -prd $tmp_in -seq $GOR_SEQ -obs $GOR_OBS >$tmp_\
out`;\n    open ($o, \">$tmp\");\n    open ($i, \"\
$tmp_out\");\n    while (<$i>)\n      {\n	my $l=$_\
;\n\n	\n	if ( $l=~/>/){print $o \"$l\";}\n	elsif (\
 $l=~/Predicted Sec. Struct./){$l=~s/Predicted Sec\
. Struct\\.//;print $o \"$l\";}\n      }\n    clos\
e ($o);\n    close ($i);\n    return read_fasta_se\
q($tmp);\n  }\n			\n			     \nsub index2seq_name\n\
  {\n    \n    my $SR=shift;\n    my $index=shift;\
\n    \n    \n    my %S=%$SR;\n    \n    foreach m\
y $s (%S)\n      {\n	if ( $S{$s}{index}==$index){r\
eturn $s;}\n      }\n    return \"\";\n  }\n\nsub \
pred2cons\n  {\n    my $outfile=shift;\n    my $pr\
edR=shift;\n    my $seq=shift;\n    my %P=%$predR;\
\n    my %C;\n    my ($s,@r,$nseq);\n    my $f= ne\
w FileHandle;\n\n    open ($f, \">$outfile\");\n\n\
    if (!$seq){$seq=index2seq_name(\\%P,1);}\n    \
foreach my $s (keys(%P))\n      {\n	$nseq++;\n	$st\
ring= $P{$s}{seq};\n	$string = uc $string;\n	my @r\
=split (//,$string);\n	for (my $a=0; $a<=$#r; $a++\
)\n	  {\n	    if (($r[$a]=~/[OHICE]/)){$C{$a}{$r[$\
a]}++;}\n	  }\n      }\n    @l=keys(%C);\n    \n  \
  \n    $s=$P{$seq}{seq};\n    print $f \">$seq pr\
ed based on $nseq\\n\";\n    @r=split (//,$s);\n  \
  \n    for (my $x=0; $x<=$#r; $x++)\n      {\n	if\
 ($r[$x] ne \"-\")\n	  {\n	    my $h=$C{$x}{H};\n	\
    my $i=$C{$x}{I};\n	    my $o=$C{$x}{O};\n	    \
my $c=$C{$x}{C};\n	    my $e=$C{$x}{E};\n	    my $\
l=$i+$o;\n	    \n	    if ($h>=$i && $h>=$o && $h>=\
$c && $h>=$e){$r[$x]='H';}\n	    elsif ($i>=$o && \
$i>=$c && $i>=$e){$r[$x]='I';}\n	    elsif ($o>=$c\
 && $o>=$e){$r[$x]='O';}\n	    elsif ($c>=$e){$r[$\
x]='C';}\n	    else {$r[$x]='E';}\n	  }\n      }\n\
    $j=join ('', @r);\n    print $f \"$j\\n\";\n  \
  close ($f);\n    return $j;\n  }\n\nsub pred2aln\
\n  {\n    my $PR=shift;\n    my $AR=shift;\n    \\
n    my $f=new FileHandle;\n    my %P=%$PR;\n    m\
y %A=%$AR;\n    my %PA;\n    my $tmp=vtmpnam();\n \
   my $f= new FileHandle;\n    \n    open ($f, \">\
$tmp\");\n    foreach my $s (sort{$A{$a}{index}<=>\
$A{$b}{index}}(keys (%A)))\n      {\n	my (@list, $\
seq, @plist, @pseq, $L, $PL, $c, $w);\n	my $seq;\n\
	my $seq=$A{$s}{seq};\n	my $pred=$P{$s}{seq};\n	$s\
eq=pred2alnS($P{$s}{seq},$A{$s}{seq});\n	print $f \
\">$s\\n$seq\\n\";\n      }\n    close ($f);\n    \
return read_fasta_seq ($tmp);\n  }\nsub pred2alnS\\
n  {\n    my $pred=shift;\n    my $aln= shift;\n  \
  my ($j,$a,$b);\n    my @P=split (//, $pred);\n  \
  my @A=split (//, $aln);\n    for ($a=$b=0;$a<=$#\
A; $a++)\n      {\n	if ($A[$a] ne \"-\"){$A[$a]=$P\
[$b++];}\n      }\n    if ($b!= ($#P+1)){add_warni\
ng (\"Could not thread sequence: $b $#P\");}\n    \
\n    $j= join ('', @A);\n    return $j;\n  }\nsub\
 pred2color\n  {\n    my $predP=shift;\n    my $al\
nP=shift;\n    my $out=shift;\n    my $F=new FileH\
andle;\n    my $struc=vtmpnam();\n    my $aln=vtmp\
nam();\n    \n\n    output_fasta_seq ($alnP, $aln)\
;\n    my %p=%$predP;\n    \n    open ($F, \">$str\
uc\");\n    \n    \n    foreach my $s (keys(%p))\n\
      {\n	\n	print $F \">$s\\n\";\n	my $s=uc($p{$s\
}{seq});\n	\n	$s=~s/[Oo]/0/g;\n	$s=~s/[Ee]/0/g;\n	\
\n	$s=~s/[Ii]/5/g;\n	$s=~s/[Cc]/5/g;\n	\n	$s=~s/[H\
h]/9/g;\n	\n	print $F \"$s\\n\";\n      }\n    clo\
se ($F);\n    \n    \n    \n    safe_system ( \"t_\
coffee -other_pg seq_reformat -in $aln -struc_in $\
struc -struc_in_f number_fasta -output color_html \
-out $out\");\n    return;\n  }\n	  \n    \nsub di\
splay_fasta_seq\n  {\n    my $SR=shift;\n    my %S\
=%$SR;\n    \n    foreach my $s (sort{$S{$a}{index\
}<=>$S{$b}{index}}(keys (%S)))\n      {\n	print ST\
DERR \">$s\\n$S{$s}{seq}\\n\";\n      }\n    close\
 ($f);\n  }\nsub output_fasta_seq\n  {\n    my $SR\
=shift;\n    my $outfile=shift;\n    my $mode =shi\
ft;\n    my $f= new FileHandle;\n    my %S=%$SR;\n\
    \n    \n    open ($f, \">$outfile\");\n    for\
each my $s (sort{$S{$a}{index}<=>$S{$b}{index}}(ke\
ys (%S)))\n      {\n	my $seq=$S{$s}{seq};\n	if ( $\
mode eq \"seq\"){$seq=~s/\\-//g;}\n	print $f \">$s\
\\n$seq\\n\";\n      }\n    close ($f);\n  }\n    \
  \nsub read_fasta_seq \n  {\n    my $f=$_[0];\n  \
  my %hseq;\n    my (@seq, @com, @name);\n    my (\
$a, $s,$nseq);\n    my $index;\n    open (F, $f);\\
n    while (<F>)\n      {\n	$s.=$_;\n      }\n    \
close (F);\n\n    \n    @name=($s=~/>(\\S*).*\\n[^\
>]*/g);\n    \n    @seq =($s=~/>.*.*\\n([^>]*)/g);\
\n    @com =($s=~/>.*(.*)\\n([^>]*)/g);\n\n\n    $\
nseq=$#name+1;\n    \n  \n    for ($a=0; $a<$nseq;\
 $a++)\n      {\n	my $n=$name[$a];\n	my $s;\n	$hse\
q{$n}{name}=$n;\n	$s=$seq[$a];$s=~s/\\s//g;\n	$hse\
q{$n}{index}=++$index;\n	$hseq{$n}{seq}=$s;\n	$hse\
q{$n}{com}=$com[$a];\n      }\n    return %hseq;\n\
  }\n\n\nsub file2head\n      {\n	my $file = shift\
;\n	my $size = shift;\n	my $f= new FileHandle;\n	m\
y $line;\n	open ($f,$file);\n	read ($f,$line, $siz\
e);\n	close ($f);\n	return $line;\n      }\nsub fi\
le2tail\n      {\n	my $file = shift;\n	my $size = \
shift;\n	my $f= new FileHandle;\n	my $line;\n	\n	o\
pen ($f,$file);\n	seek ($f,$size*-1, 2);\n	read ($\
f,$line, $size);\n	close ($f);\n	return $line;\n  \
    }\n\n\nsub vtmpnam\n      {\n	my $r=rand(10000\
0);\n	my $f=\"file.$r.$$\";\n	while (-e $f)\n	  {\\
n	    $f=vtmpnam();\n	  }\n	push (@TMPFILE_LIST, $\
f);\n	return $f;\n      }\n\nsub myexit\n  {\n    \
my $code=@_[0];\n    if ($CLEAN_EXIT_STARTED==1){r\
eturn;}\n    else {$CLEAN_EXIT_STARTED=1;}\n    ##\
# ONLY BARE EXIT\n    exit ($code);\n  }\nsub set_\
error_lock\n    {\n      my $name = shift;\n      \
my $pid=$$;\n\n      \n      &lock4tc ($$,\"LERROR\
\", \"LSET\", \"$$ -- ERROR: $name $PROGRAM\\n\");\
\n      return;\n    }\nsub set_lock\n  {\n    my \
$pid=shift;\n    my $msg= shift;\n    my $p=getppi\
d();\n    &lock4tc ($pid,\"LLOCK\",\"LRESET\",\"$p\
$msg\\n\");\n  }\nsub unset_lock\n   {\n     \n   \
 my $pid=shift;\n    &lock4tc ($pid,\"LLOCK\",\"LR\
ELEASE\",\"\");\n  }\nsub shift_lock\n  {\n    my \
$from=shift;\n    my $to=shift;\n    my $from_type\
=shift;\n    my $to_type=shift;\n    my $action=sh\
ift;\n    my $msg;\n    \n    if (!&lock4tc($from,\
 $from_type, \"LCHECK\", \"\")){return 0;}\n    $m\
sg=&lock4tc ($from, $from_type, \"LREAD\", \"\");\\
n    &lock4tc ($from, $from_type,\"LRELEASE\", $ms\
g);\n    &lock4tc ($to, $to_type, $action, $msg);\\
n    return;\n  }\nsub isshellpid\n  {\n    my $p=\
shift;\n    if (!lock4tc ($p, \"LLOCK\", \"LCHECK\\
")){return 0;}\n    else\n      {\n	my $c=lock4tc(\
$p, \"LLOCK\", \"LREAD\");\n	if ( $c=~/-SHELL-/){r\
eturn 1;}\n      }\n    return 0;\n  }\nsub isroot\
pid\n  {\n    if(lock4tc (getppid(), \"LLOCK\", \"\
LCHECK\")){return 0;}\n    else {return 1;}\n  }\n\
sub lock4tc\n	{\n	  my ($pid,$type,$action,$value)\
=@_;\n	  my $fname;\n	  my $host=hostname;\n	  \n	\
  if ($type eq \"LLOCK\"){$fname=\"$LOCKDIR/.$pid.\
$host.lock4tcoffee\";}\n	  elsif ( $type eq \"LERR\
OR\"){ $fname=\"$LOCKDIR/.$pid.$host.error4tcoffee\
\";}\n	  elsif ( $type eq \"LWARNING\"){ $fname=\"\
$LOCKDIR/.$pid.$host.warning4tcoffee\";}\n	  \n	  \
if ($debug_lock)\n	    {\n	      print STDERR \"\\\
n\\t---lock4tc(tcg): $action => $fname =>$value (R\
D: $LOCKDIR)\\n\";\n	    }\n\n	  if    ($action eq\
 \"LCHECK\") {return -e $fname;}\n	  elsif ($actio\
n eq \"LREAD\"){return file2string($fname);}\n	  e\
lsif ($action eq \"LSET\") {return string2file ($v\
alue, $fname, \">>\");}\n	  elsif ($action eq \"LR\
ESET\") {return string2file ($value, $fname, \">\"\
);}\n	  elsif ($action eq \"LRELEASE\") \n	    {\n\
	      if ( $debug_lock)\n		{\n		  my $g=new FileH\
andle;\n		  open ($g, \">>$fname\");\n		  print $g\
 \"\\nDestroyed by $$\\n\";\n		  close ($g);\n		  \
safe_system (\"mv $fname $fname.old\");\n		}\n	   \
   else\n		{\n		  unlink ($fname);\n		}\n	    }\n	\
  return \"\";\n	}\n	\nsub file2string\n	{\n	  my \
$file=@_[0];\n	  my $f=new FileHandle;\n	  my $r;\\
n	  open ($f, \"$file\");\n	  while (<$f>){$r.=$_;\
}\n	  close ($f);\n	  return $r;\n	}\nsub string2f\
ile \n    {\n    my ($s,$file,$mode)=@_;\n    my $\
f=new FileHandle;\n    \n    open ($f, \"$mode$fil\
e\");\n    print $f  \"$s\";\n    close ($f);\n  }\
\n\nBEGIN\n    {\n      srand;\n    \n      $SIG{'\
SIGUP'}='signal_cleanup';\n      $SIG{'SIGINT'}='s\
ignal_cleanup';\n      $SIG{'SIGQUIT'}='signal_cle\
anup';\n      $SIG{'SIGILL'}='signal_cleanup';\n  \
    $SIG{'SIGTRAP'}='signal_cleanup';\n      $SIG{\
'SIGABRT'}='signal_cleanup';\n      $SIG{'SIGEMT'}\
='signal_cleanup';\n      $SIG{'SIGFPE'}='signal_c\
leanup';\n      \n      $SIG{'SIGKILL'}='signal_cl\
eanup';\n      $SIG{'SIGPIPE'}='signal_cleanup';\n\
      $SIG{'SIGSTOP'}='signal_cleanup';\n      $SI\
G{'SIGTTIN'}='signal_cleanup';\n      $SIG{'SIGXFS\
Z'}='signal_cleanup';\n      $SIG{'SIGINFO'}='sign\
al_cleanup';\n      \n      $SIG{'SIGBUS'}='signal\
_cleanup';\n      $SIG{'SIGALRM'}='signal_cleanup'\
;\n      $SIG{'SIGTSTP'}='signal_cleanup';\n      \
$SIG{'SIGTTOU'}='signal_cleanup';\n      $SIG{'SIG\
VTALRM'}='signal_cleanup';\n      $SIG{'SIGUSR1'}=\
'signal_cleanup';\n\n\n      $SIG{'SIGSEGV'}='sign\
al_cleanup';\n      $SIG{'SIGTERM'}='signal_cleanu\
p';\n      $SIG{'SIGCONT'}='signal_cleanup';\n    \
  $SIG{'SIGIO'}='signal_cleanup';\n      $SIG{'SIG\
PROF'}='signal_cleanup';\n      $SIG{'SIGUSR2'}='s\
ignal_cleanup';\n\n      $SIG{'SIGSYS'}='signal_cl\
eanup';\n      $SIG{'SIGURG'}='signal_cleanup';\n \
     $SIG{'SIGCHLD'}='signal_cleanup';\n      $SIG\
{'SIGXCPU'}='signal_cleanup';\n      $SIG{'SIGWINC\
H'}='signal_cleanup';\n      \n      $SIG{'INT'}='\
signal_cleanup';\n      $SIG{'TERM'}='signal_clean\
up';\n      $SIG{'KILL'}='signal_cleanup';\n      \
$SIG{'QUIT'}='signal_cleanup';\n      \n      our \
$debug_lock=$ENV{\"DEBUG_LOCK\"};\n      \n      \\
n      \n      \n      foreach my $a (@ARGV){$CL.=\
\" $a\";}\n      if ( $debug_lock ){print STDERR \\
"\\n\\n\\n********** START PG: $PROGRAM **********\
***\\n\";}\n      if ( $debug_lock ){print STDERR \
\"\\n\\n\\n**********(tcg) LOCKDIR: $LOCKDIR $$ **\
***********\\n\";}\n      if ( $debug_lock ){print\
 STDERR \"\\n --- $$ -- $CL\\n\";}\n      \n	     \
\n      \n      \n    }\nsub flush_error\n  {\n   \
 my $msg=shift;\n    return add_error ($EXIT_FAILU\
RE,$$, $$,getppid(), $msg, $CL);\n  }\nsub add_err\
or \n  {\n    my $code=shift;\n    my $rpid=shift;\
\n    my $pid=shift;\n    my $ppid=shift;\n    my \
$type=shift;\n    my $com=shift;\n    \n    $ERROR\
_DONE=1;\n    lock4tc ($rpid, \"LERROR\",\"LSET\",\
\"$pid -- ERROR: $type\\n\");\n    lock4tc ($$, \"\
LERROR\",\"LSET\", \"$pid -- COM: $com\\n\");\n   \
 lock4tc ($$, \"LERROR\",\"LSET\", \"$pid -- STACK\
: $ppid -> $pid\\n\");\n   \n    return $code;\n  \
}\nsub add_warning \n  {\n    my $rpid=shift;\n   \
 my $pid =shift;\n    my $command=shift;\n    my $\
msg=\"$$ -- WARNING: $command\\n\";\n    print STD\
ERR \"$msg\";\n    lock4tc ($$, \"LWARNING\", \"LS\
ET\", $msg);\n  }\n\nsub signal_cleanup\n  {\n    \
print dtderr \"\\n**** $$ (tcg) was killed\\n\";\n\
    &cleanup;\n    exit ($EXIT_FAILURE);\n  }\nsub\
 clean_dir\n  {\n    my $dir=@_[0];\n    if ( !-d \
$dir){return ;}\n    elsif (!($dir=~/tmp/)){return\
 ;}#safety check 1\n    elsif (($dir=~/\\*/)){retu\
rn ;}#safety check 2\n    else\n      {\n	`rm -rf \
$dir`;\n      }\n    return;\n  }\nsub cleanup\n  \
{\n    #print stderr \"\\n----tc: $$ Kills $PIDCHI\
LD\\n\";\n    #kill (SIGTERM,$PIDCHILD);\n    my $\
p=getppid();\n    $CLEAN_EXIT_STARTED=1;\n    \n  \
  \n    \n    if (&lock4tc($$,\"LERROR\", \"LCHECK\
\", \"\"))\n      {\n	my $ppid=getppid();\n	if (!$\
ERROR_DONE) \n	  {\n	    &lock4tc($$,\"LERROR\", \\
"LSET\", \"$$ -- STACK: $p -> $$\\n\");\n	    &loc\
k4tc($$,\"LERROR\", \"LSET\", \"$$ -- COM: $CL\\n\\
");\n	  }\n      }\n    my $warning=&lock4tc($$, \\
"LWARNING\", \"LREAD\", \"\");\n    my $error=&loc\
k4tc($$,  \"LERROR\", \"LREAD\", \"\");\n    #rele\
ase error and warning lock if root\n    \n    if (\
isrootpid() && ($warning || $error) )\n      {\n	\\
n	print STDERR \"**************** Summary ********\
*****\\n$error\\n$warning\\n\";\n\n	&lock4tc($$,\"\
LERROR\",\"RELEASE\",\"\");\n	&lock4tc($$,\"LWARNI\
NG\",\"RELEASE\",\"\");\n      } \n    \n    \n   \
 foreach my $f (@TMPFILE_LIST)\n      {\n	if (-e $\
f){unlink ($f);} \n      }\n    foreach my $d (@TM\
PDIR_LIST)\n      {\n	clean_dir ($d);\n      }\n  \
  #No More Lock Release\n    #&lock4tc($$,\"LLOCK\\
",\"LRELEASE\",\"\"); #release lock \n\n    if ( $\
debug_lock ){print STDERR \"\\n\\n\\n********** EN\
D PG: $PROGRAM ($$) *************\\n\";}\n    if (\
 $debug_lock ){print STDERR \"\\n\\n\\n**********(\
tcg) LOCKDIR: $LOCKDIR $$ *************\\n\";}\n  \
}\nEND \n  {\n    \n    &cleanup();\n  }\n   \n\ns\
ub safe_system \n{\n  my $com=shift;\n  my $ntry=s\
hift;\n  my $ctry=shift;\n  my $pid;\n  my $status\
;\n  my $ppid=getppid();\n  if ($com eq \"\"){retu\
rn 1;}\n  \n  \n\n  if (($pid = fork ()) < 0){retu\
rn (-1);}\n  if ($pid == 0)\n    {\n      set_lock\
($$, \" -SHELL- $com (tcg)\");\n      exec ($com);\
\n    }\n  else\n    {\n      lock4tc ($$, \"LLOCK\
\", \"LSET\", \"$pid\\n\");#update parent\n      $\
PIDCHILD=$pid;\n    }\n  if ($debug_lock){printf S\
TDERR \"\\n\\t .... safe_system (fasta_seq2hmm)  p\
: $$ c: $pid COM: $com\\n\";}\n\n  waitpid ($pid,W\
TERMSIG);\n\n  shift_lock ($pid,$$, \"LWARNING\",\\
"LWARNING\", \"LSET\");\n\n  if ($? == $EXIT_FAILU\
RE || lock4tc($pid, \"LERROR\", \"LCHECK\", \"\"))\
\n    {\n      if ($ntry && $ctry <$ntry)\n	{\n	  \
add_warning ($$,$$,\"$com failed [retry: $ctry]\")\
;\n	  lock4tc ($pid, \"LRELEASE\", \"LERROR\", \"\\
");\n	  return safe_system ($com, $ntry, ++$ctry);\
\n	}\n      elsif ($ntry == -1)\n	{\n	  if (!shift\
_lock ($pid, $$, \"LERROR\", \"LWARNING\", \"LSET\\
"))\n	    {\n	      add_warning ($$,$$,\"$com fail\
ed\");\n	    }\n	  else\n	    {\n	      lock4tc ($\
pid, \"LRELEASE\", \"LERROR\", \"\");\n	    }\n	  \
return $?;}\n      else\n	{\n	  if (!shift_lock ($\
pid,$$, \"LERROR\",\"LERROR\", \"LSET\"))\n	    {\\
n	      myexit(add_error ($EXIT_FAILURE,$$,$pid,ge\
tppid(), \"UNSPECIFIED system\", $com));\n	    }\n\
	}\n    }\n  return $?;\n}\n\nsub check_configurat\
ion \n    {\n      my @l=@_;\n      my $v;\n      \
foreach my $p (@l)\n	{\n	  \n	  if   ( $p eq \"EMA\
IL\")\n	    { \n	      if ( !($EMAIL=~/@/))\n		{\n\
		add_warning($$,$$,\"Could Not Use EMAIL\");\n		m\
yexit(add_error ($EXIT_FAILURE,$$,$$,getppid(),\"E\
MAIL\",\"$CL\"));\n	      }\n	    }\n	  elsif( $p \
eq \"INTERNET\")\n	    {\n	      if ( !&check_inte\
rnet_connection())\n		{\n		  myexit(add_error ($EX\
IT_FAILURE,$$,$$,getppid(),\"INTERNET\",\"$CL\"));\
\n		}\n	    }\n	  elsif( $p eq \"wget\")\n	    {\n\
	      if (!&pg_is_installed (\"wget\") && !&pg_is\
_installed (\"curl\"))\n		{\n		  myexit(add_error \
($EXIT_FAILURE,$$,$$,getppid(),\"PG_NOT_INSTALLED:\
wget\",\"$CL\"));\n		}\n	    }\n	  elsif( !(&pg_is\
_installed ($p)))\n	    {\n	      myexit(add_error\
 ($EXIT_FAILURE,$$,$$,getppid(),\"PG_NOT_INSTALLED\
:$p\",\"$CL\"));\n	    }\n	}\n      return 1;\n   \
 }\nsub pg_is_installed\n  {\n    my @ml=@_;\n    \
my $r, $p, $m;\n    my $supported=0;\n    \n    my\
 $p=shift (@ml);\n    if ($p=~/::/)\n      {\n	if \
(safe_system (\"perl -M$p -e 1\")==$EXIT_SUCCESS){\
return 1;}\n	else {return 0;}\n      }\n    else\n\
      {\n	$r=`which $p 2>/dev/null`;\n	if ($r eq \\
"\"){return 0;}\n	else {return 1;}\n      }\n  }\n\
\n\n\nsub check_internet_connection\n  {\n    my $\
internet;\n    my $tmp;\n    &check_configuration \
( \"wget\"); \n    \n    $tmp=&vtmpnam ();\n    \n\
    if     (&pg_is_installed    (\"wget\")){`wget \
www.google.com -O$tmp >/dev/null 2>/dev/null`;}\n \
   elsif  (&pg_is_installed    (\"curl\")){`curl w\
ww.google.com -o$tmp >/dev/null 2>/dev/null`;}\n  \
  \n    if ( !-e $tmp || -s $tmp < 10){$internet=0\
;}\n    else {$internet=1;}\n    if (-e $tmp){unli\
nk $tmp;}\n\n    return $internet;\n  }\nsub check\
_pg_is_installed\n  {\n    my @ml=@_;\n    my $r=&\
pg_is_installed (@ml);\n    if (!$r && $p=~/::/)\n\
      {\n	print STDERR \"\\nYou Must Install the p\
erl package $p on your system.\\nRUN:\\n\\tsudo pe\
rl -MCPAN -e 'install $pg'\\n\";\n      }\n    els\
if (!$r)\n      {\n	myexit(flush_error(\"\\nProgra\
m $p Supported but Not Installed on your system\")\
);\n      }\n    else\n      {\n	return 1;\n      \
}\n  }\n\n\n\n","\n\n\n\n\nmy $FMODEL =\"\"; \nmy \
$TMPDIR = \"/tmp\";\n\n\n\n\nmy $NUCALPH = \"ACGTU\
NRYMKSWHBVD\";\nmy $PRIMNUCALPH = \"ACGTUN\";\nuse\
 vars qw($NUCALPH $PRIMNUCALPH $TMPDIR);\n\n\nmy $\
errmsg;\nuse vars qw($errmsg);\n\n\n\nuse Getopt::\
Long;\nuse Cwd;\nuse File::Basename;\nuse File::Te\
mp qw/ tempfile tempdir /;\nuse File::Copy;\nuse F\
ile::Path;\n\n\n\nsub usage(;$)\n{\n    my ($errms\
g) = @_;\n    my $myname = basename($0);\n\n    if\
 ($errmsg) {\n        print STDERR \"ERROR: $errms\
g\\n\";\n    }\n\n    print STDERR << \"EOF\";\n  \
  \n$myname: align two sequences by means of consa\
n\\'s sfold\nUsage:\n $myname -i file -o file -d p\
ath\nOptions:\n -i|--in : pairwise input sequence \
file\n -o|--out: output alignment\n -d|--directory\
 containing data\n\nEOF\n}\n\nsub read_stk_aln \n \
 {\n    my $f=$_[0];\n    my ($seq, $id);\n    \n \
   my %hseq;\n\n    open (STK, \"$f\");\n    while\
 (<STK>)\n      {\n	if ( /^#/ || /^\\/\\// || /^\\\
s*$/){;}\n	else\n	  {\n	    ($id,$seq)=/(\\S+)\\s+\
(\\S+)/;\n	    $hseq{$id}{'seq'}.=$seq;\n	  }\n   \
   }\n    close (STK);\n    return %hseq;\n  }\nsu\
b read_fasta_seq \n  {\n    my $f=$_[0];\n    my %\
hseq;\n    my (@seq, @com, @name);\n    my ($a, $s\
,$nseq);\n\n    open (F, $f);\n    while (<F>)\n  \
    {\n	$s.=$_;\n      }\n    close (F);\n\n    \n\
    @name=($s=~/>(.*).*\\n[^>]*/g);\n    \n    @se\
q =($s=~/>.*.*\\n([^>]*)/g);\n    @com =($s=~/>.*(\
.*)\\n([^>]*)/g);\n\n    \n    $nseq=$#name+1;\n  \
  \n    for ($a=0; $a<$nseq; $a++)\n      {\n	my $\
n=$name[$a];\n	$hseq{$n}{name}=$n;\n	$hseq{$n}{seq\
}=$seq[$a];\n	$hseq{$n}{com}=$com[$a];\n      }\n \
   return %hseq;\n  }\n\n\n\nsub sfold_parseoutput\
($$)\n{\n    my ($frawout, $foutfa) = @_;\n    my \
%haln;\n    my ($fstk, $cmd, $id);\n    open FOUTF\
A, \">$foutfa\";\n    \n    $fstk = $frawout . \".\
stk\";\n    \n    # first line of raw out contains\
 info\n    # remaining stuff is stockholm formatte\
d\n    $cmd = \"sed -e '1d' $frawout\";\n    syste\
m(\"$cmd > $fstk\");\n    if ($? != 0) {\n        \
$errmsg = \"command failed with exit status $?.\";\
\n        $errmsg .=  \"Command was \\\"$cmd\\\"\"\
;\n        return -1;\n    }\n\n    # this gives a\
n error message. just ignore it...\n    %haln=read\
_stk_aln ( $fstk);\n    foreach $i (keys (%haln))\\
n      {\n	my $s;\n	$s=$haln{$i}{'seq'};\n	$s =~ s\
/\\./-/g;\n	print FOUTFA \">$i\\n$s\\n\";\n      }\
\n    close FOUTFA;\n    return 0;\n}\n\n\n\n\nsub\
 sfold_wrapper($$$$)\n{\n    \n    my ($fs1, $fs2,\
 $fmodel, $foutfa) = @_;\n    \n\n    my ($cmd, $f\
rawout, $ferrlog, $freadme, $ftimelog, $fstk);\n\n\
    # add  basename($fmsqin) (unknown here!)\n    \
$frawout = \"sfold.log\";\n    $ferrlog = \"sfold.\
err\";\n    $ftimelog = \"sfold.time\";\n    $frea\
dme =  \"sfold.README\";\n    $fstk = \"sfold.stk\\
";\n    \n    # prepare execution...\n    #\n    #\
 ./tmp is essential for dswpalign\n    # otherwise\
 you'll get a segfault\n    mkdir \"./tmp\";\n    \
\n    $cmd = \"sfold -m $fmodel $fs1 $fs2\";\n    \
open(FREADME,\">$freadme\");\n    print FREADME \"\
$cmd\\n\"; \n    close(FREADME);\n\n    # and go\n\
    #\n    system(\"/usr/bin/time -p -o $ftimelog \
$cmd >$frawout 2>$ferrlog\");\n    if ($? != 0) {\\
n        $errmsg = \"command failed with exit stat\
us $?\";\n        $errmsg .= \"command was \\\"$cm\
d\\\". See \" . getcwd . \"\\n\";\n        return \
-1;\n    }\n\n    return sfold_parseoutput($frawou\
t, $foutfa);\n}\n\n\n\n\n\n\n\nmy ($help, $fmsqin,\
 $fmsaout);\nGetOptions(\"help\"  => \\$help,\n   \
        \"in=s\" => \\$fmsqin,\n           \"out=s\
\" => \\$fmsaout,\n	   \"data=s\" => \\$ref_dir);\\
n\n\n\nif ($help) {\n    usage();\n    exit(0);\n}\
\nif (! defined($fmsqin)) {\n    usage('missing in\
put filename');\n    exit(1);\n}\nif (! defined($f\
msaout)) {\n    usage('missing output filename');\\
n    exit(1);\n\n}\nif (scalar(@ARGV)) {\n    usag\
e('Unknown remaining args');\n    exit(1);\n}\n\n$\
FMODEL = \"$ref_dir/mix80.mod\";\nif (! -e \"$FMOD\
EL\") {\n    die(\"couldn't find sfold grammar mod\
el file. Expected $FMODEL\\n\");\n}\n\n\nmy %hseq=\
read_fasta_seq ($fmsqin);\nmy $id;\n\nforeach $id \
(keys(%hseq))\n  {\n    push(@seq_array, $hseq{$id\
});\n  }\n\nif ( scalar(@seq_array) != 2 ) {\n    \
die(\"Need *exactly* two sequences as input (pairw\
ise alignment!).\")\n}\n\n\n\nmy ($sec, $min, $hou\
r, $mday, $mon, $year, $wday, $yday, $isdst) = loc\
altime(time);\nmy $datei = sprintf(\"%4d-%02d-%02d\
\", $year+1900, $mon+1, $mday);\nmy $templ = basen\
ame($0) . \".\" . $datei . \".pid-\" . $$ . \".XXX\
XXX\";\nmy $wd = tempdir ( $templ, DIR => $TMPDIR)\
;\n\ncopy($fmsqin, \"$wd/\" . basename($fmsqin) . \
\".org\"); # for reproduction\ncopy($FMODEL, \"$wd\
\");\nmy $fmodel = basename($FMODEL);\nmy $orgwd =\
 getcwd;\nchdir $wd;\n\n\n\nmy @sepseqfiles;\nfore\
ach $id (keys(%hseq)) {\n    my ($seq, $orgseq, $f\
name, $sout);\n    $seq=$hseq{$id}{'seq'};\n    \n\
    $fname = basename($fmsqin) . \"_$id.fa\";\n   \
 # replace funnies in file/id name (e.g. \"/\" \" \
\" etc)\n    $fname =~ s,[/ ],_,g;\n    open (PF, \
\">$fname\");\n    print (PF \">$id\\n$seq\\n\");\\
n    close (PF);\n\n    push(@sepseqfiles, $fname)\
;\n}\n\nmy ($f1, $f2, $fout);\n$f1 = $sepseqfiles[\
0];\n$f2 = $sepseqfiles[1];\n$fout = $wd . basenam\
e($fmsqin) . \".out.fa\";\nif (sfold_wrapper($f1, \
$f2, $fmodel, \"$fout\") != 0) {\n    printf STDER\
R \"ERROR: See logs in $wd\\n\";\n    exit(1);\n} \
else {\n    chdir $orgwd;\n    copy($fout, $fmsaou\
t);\n    rmtree($wd);\n   exit(0);\n}\n","\nuse En\
v qw(HOST);\nuse Env qw(HOME);\nuse Env qw(USER);\\
n\n\n$tmp=clean_cr ($ARGV[0]);\nopen (F, $tmp);\n\\
nwhile ( <F>)\n  {\n    my $l=$_;\n    if ( $l=~/^\
# STOCKHOLM/){$stockholm=1;}\n    elsif ( $stockho\
lm && $l=~/^#/)\n      {\n	$l=~/^#(\\S+)\\s+(\\S+)\
\\s+(\\S*)/g;\n	$l=\"_stockholmhasch_$1\\_stockhol\
mspace_$2 $3\\n\";\n      }\n    $file.=$l;\n  }\n\
close (F);\nunlink($tmp);\n$file1=$file;\n\n$file=\
~s/\\#/_hash_symbol_/g;\n$file=~s/\\@/_arobase_sym\
bol_/g;\n\n\n$file=~s/\\n[\\.:*\\s]+\\n/\\n\\n/g;\\
n\n$file=~s/\\n[ \\t\\r\\f]+(\\b)/\\n\\1/g;\n\n\n$\
file=~s/(\\n\\S+)(\\s+)(\\S)/\\1_blank_\\3/g;\n\n$\
file=~s/[ ]//g;\n$file=~s/_blank_/ /g;\n\n\n\n$fil\
e =~s/\\n\\s*\\n/#/g;\n\n$file.=\"#\";\n$file =~s/\
\\n/@/g;\n\n\n\n\n@blocks=split /\\#/, $file;\nshi\
ft (@blocks);\n@s=split /\\@/, $blocks[0];\n$nseq=\
$#s+1;\n\n\n\n$file=join '@', @blocks;\n@lines=spl\
it /\\@/,$file;\n\n$c=0;\n\nforeach $l (@lines)\n \
 {\n    if (!($l=~/\\S/)){next;}\n    elsif ($stoc\
kholm && ($l=~/^\\/\\// || $l=~/STOCKHOLM/)){next;\
}#get read of STOCHOLM Terminator\n   \n    $l=~/(\
\\S+)\\s+(\\S*)/g;\n    $n=$1; $s=$2;\n    \n    $\
seq[$c].=$s;\n    $name[$c]=$n;\n    $c++;\n    \n\
    if ( $c==$nseq){$c=0;}\n    \n  } \n\nif ( $c!\
=0)\n      {\n	print STDERR \"ERROR: $ARGV[0] is N\
OT an MSA in Clustalw format: make sure there is n\
o blank line within a block [ERROR]\\n\";\n	exit (\
EXIT_FAILURE);\n      }\n\nfor ($a=0; $a< $nseq; $\
a++)\n  {\n    $name[$a]=cleanstring ($name[$a]);\\
n    $seq[$a]=cleanstring ($seq[$a]);\n    $seq[$a\
]=breakstring($seq[$a], 60);\n    \n    $line=\">$\
name[$a]\\n$seq[$a]\\n\";\n    \n    print \"$line\
\";\n  }\nexit (EXIT_SUCCESS);\n\nsub cleanstring\\
n  {\n    my $s=@_[0];\n    $s=~s/_hash_symbol_/\\\
#/g;\n    $s=~s/_arobase_symbol_/\\@/g;\n    $s=~s\
/[ \\t]//g;\n    return $s;\n  }\nsub breakstring\\
n  {\n    my $s=@_[0];\n    my $size=@_[1];\n    m\
y @list;\n    my $n,$ns, $symbol;\n    \n    @list\
=split //,$s;\n    $n=0;$ns=\"\";\n    foreach $sy\
mbol (@list)\n      {\n	if ( $n==$size)\n	  {\n	  \
  $ns.=\"\\n\";\n	    $n=0;\n	  }\n	$ns.=$symbol;\\
n	$n++;\n      }\n    return $ns;\n    }\n\nsub cl\
ean_cr\n  {\n    my $f=@_[0];\n    my $file;\n    \
\n    $tmp=\"f$.$$\";\n    \n    \n    open (IN, $\
f);\n    open (OUT, \">$tmp\");\n    \n    while (\
 <IN>)\n      {\n	$file=$_;\n	$file=~s/\\r\\n/\\n/\
g;\n	$file=~s/\\n\\r/\\n/g;\n	$file=~s/\\r\\r/\\n/\
g;\n	$file=~s/\\r/\\n/g;\n	print OUT \"$file\";\n \
     }\n    \n    close (IN);\n    close (OUT);\n \
   return $tmp;\n  }\n","use Env qw(HOST);\nuse En\
v qw(HOME);\nuse Env qw(USER);\n\n\n$query_start=-\
1;\n$query_end=-1;\n\nwhile (<>)\n  {\n    if ( /\\
\/\\//){$in_aln=1;}\n    elsif ( $in_aln && /(\\S+\
)\\s+(.*)/)\n      {\n\n\n	$name=$1;\n	\n\n	$seq=$\
2;\n	$seq=~s/\\s//g;\n        $seq=~s/\\~/\\-/g;\n\
	$seq=~s/\\./\\-/g;\n	if ( $list{$n}{'name'} && $l\
ist{$n}{'name'} ne $name)\n	  {\n	    print \"$lis\
t{$n}{'name'} Vs $name\";\n	    \n	    exit (EXIT_\
FAILURE);\n	  }\n	else\n	  {\n	    $list{$n}{'name\
'}= $name;\n	  }\n\n	$list{$n}{'seq'}=$list{$n}{'s\
eq'}.$seq;\n	\n	$nseq=++$n;\n	\n      }\n    else\\
n      {$n=0;}\n  }\n\n\nfor ($a=0; $a<$nseq; $a++\
)\n  {\n    print \">$list{$a}{'name'}\\n$list{$a}\
{'seq'}\\n\";\n  }\n      \n","\nuse Env qw(HOST);\
\nuse Env qw(HOME);\nuse Env qw(USER);\n\n        \
                                                \n\
use strict;                                       \
      \nuse warnings;\nuse diagnostics;\n\nmy $in_\
hit_list, my $in_aln=0, my(%name_list)=(),my (%lis\
t)=(),my $n_seq=0; my $test=0;\nmy($j)=0, my $n=0,\
 my $nom, my $lg_query, my %vu=();\n\nopen (F, \">\
tmp\");\n\n$/=\"\\n\";\nwhile (<>)\n{\n    print F\
 $_;\n    if($_ =~ /Query=\\s*(.+?)\\s/i) { $nom=$\
1;}\n\n    if ( /Sequences producing significant a\
lignments/){$in_hit_list=1;}\n    \n    if ($_=~ /\
^pdb\\|/i) { $_=~ s/pdb\\|//g; }\n    if ($_=~ /^(\
1_\\d+)\\s+\\d+/) { $_=~ s/$1/QUERY/;}\n      \n  \
  if ( /^(\\S+).+?\\s+[\\d.]+\\s+([\\de.-]+)\\s+$/\
 && $in_hit_list)	\n    {\n	my($id)=$1; # \n	$id=~\
 s/\\|/_/g; #\n	if ($id =~ /.+_$/) { chop($id) }; \
#\n	$name_list{$n_seq++}=$id;\n	$name_list{$n_seq-\
1}=~ s/.*\\|//g;     \n    }\n  \n    if (/query/i\
) {$in_aln=1;}\n    if ( /^(\\S+)\\s+(\\d+)\\s+([a\
-zA-Z-]+)\\s+(\\d+)/ || /^(\\S+)(\\s+)(\\-+)(\\s+)\
/ && ($in_aln == 1))\n    {\n	my $name=$1;\n	my $s\
tart=$2;\n	my $seq=$3;\n	my $end=$4;\n		\n	if ($na\
me =~ /QUERY/i) { $lg_query=length($seq); }\n\n	un\
less ($test > $n) #m\n	{\n	    my(@seqq)= split(''\
,$seq);\n	    my($gap_missing)= scalar(@seqq);\n	 \
   \n	    while ($gap_missing != $lg_query)  { uns\
hift (@seqq,\"-\"); $gap_missing= scalar(@seqq); }\
\n	    $seq=join('',@seqq);  #m\n	}\n	\n	if ($name\
 =~ /QUERY/i)\n	{\n	    $n=0; %vu=(); $j=0;\n	    \
$list{$n}{'real_name'}=\"$nom\";\n	}	\n	else\n	{\n\
	    unless (exists $vu{$name}) { ++$j;}	\n	    $l\
ist{$n}{'real_name'}=$name_list{$j-1};\n	}\n		\n	$\
list{$n}{'name'}=$name;\n\n	$seq=~tr/a-z/A-Z/;\n	$\
list{$n}{'seq'}=$list{$n}{'seq'};\n	$list{$n}{'seq\
'}.=$seq;\n\n	$n++;\n	$vu{$name}++;\n	$test++;\n  \
 } \n    \n}\n\nmy @numero=();\n\nfor (my $a=0; $a\
<$n; $a++) #m\n{\n    my $long=length($list{0}{'se\
q'});  \n    my $long1= length($list{$a}{'seq'});\\
n  \n    while ($long1 ne $long)\n    {\n	$list{$a\
}{'seq'}.=\"-\";\n	$long1= length ($list{$a}{'seq'\
});\n    } \n \n    push (@numero,\"$list{$a}{'nam\
e'} $list{$a}{'real_name'}\\n\");\n}\n\nmy %dejavu\
=();\n\n\nfor (my $i=0; $i<=$#numero; $i++)\n{\n  \
  my $s=\">$list{$i}{'real_name'}\\n$list{$i}{'seq\
'}\\n\";\n    my $k=0;\n    \n    if (exists $deja\
vu{$numero[$i]}) {next;}\n    else\n    {	\n	for (\
$j=0; $j<$n ; $j++)\n	{\n	    if (\"$numero[$i]\" \
eq \"$numero[$j]\" && $j != $i )\n	    {\n		++$k;\\
n		$s .=\">$list{$j}{'real_name'}\\n$list{$j}{'seq\
'}\\n\";\n	    }\n	}	\n    }\n    \n    if ($k>0) \
\n    {\n	my $cons;\n	open (SOR,\">tempo_aln2cons\\
"); print SOR $s;  close SOR ;\n	open (COM,\"t_cof\
fee -other_pg seq_reformat -in tempo_aln2cons -act\
ion +aln2cons +upper |\") ; \n     	while (<COM>)\\
n	{	\n	    if (/^>/) { $cons =\">$list{$i}{'real_n\
ame'}\\n\"; next;}\n	    $_=~ s/\\n//g;\n	    $con\
s .=$_;\n	}\n	close COM; unlink (\"tempo_aln2cons\\
");\n	print $cons,\"\\n\"; print F $cons,\"\\n\";\\
n    }	\n    else  { print $s;  print F $s; }\n   \
 \n    $dejavu{$numero[$i]}++;\n} #m\n\nexit;\n\n\\
n\n\n\n\n\n\n\n\n\n","use Env;\n\n\n$tmp_dir=\"\";\
\n$init_dir=\"\";\n$program=\"tc_generic_method.pl\
\";\n\n$blast=@ARGV[0];\n\n$name=\"query\";$seq=\"\
\";\n%p=blast_xml2profile($name,$seq,100, 0, 0, $b\
last);\n&output_profile (%p);\n\n\nsub output_prof\
ile\n  {\n    my (%profile)=(@_);\n    my ($a);\n \
   for ($a=0; $a<$profile{n}; $a++)\n      {\n	\n	\
print \">$profile{$a}{name} $profile{$a}{comment}\\
\n$profile{$a}{seq}\\n\";\n      }\n    return;\n \
 }\nsub file_contains \n  {\n    my ($file, $tag, \
$max)=(@_);\n    my ($n);\n    $n=0;\n    \n    if\
 ( !-e $file && ($file =~/$tag/)) {return 1;}\n   \
 elsif ( !-e $file){return 0;}\n    else \n      {\
\n	open (FC, \"$file\");\n	while ( <FC>)\n	  {\n	 \
   if ( ($_=~/$tag/))\n	      {\n		close (FC);\n		\
return 1;\n	      }\n	    elsif ($max && $n>$max)\\
n	      {\n		close (FC);\n		return 0;\n	      }\n	\
    $n++;\n	  }\n      }\n    close (FC);\n    ret\
urn 0;\n  }\n	    \n	  \nsub file2string\n  {\n   \
 my $f=@_[0];\n    my $string, $l;\n    open (F,\"\
$f\");\n    while (<F>)\n      {\n\n	$l=$_;\n	#cho\
mp ($l);\n	$string.=$l;\n      }\n    close (F);\n\
    $string=~s/\\r\\n//g;\n    $string=~s/\\n//g;\\
n    return $string;\n  }\n\n\n\nsub tag2value \n \
 {\n    \n    my $tag=(@_[0]);\n    my $word=(@_[1\
]);\n    my $return;\n    \n    $tag=~/$word=\"([^\
\"]+)\"/;\n    $return=$1;\n    return $return;\n \
 }\n      \nsub hit_tag2pdbid\n  {\n    my $tag=(@\
_[0]);\n    my $pdbid;\n       \n    $tag=~/id=\"(\
\\S+)\"/;\n    $pdbid=$1;\n    $pdbid=~s/_//;\n   \
 return $pdbid;\n  }\nsub id2pdbid \n  {\n    my $\
id=@_[0];\n  \n    if ($id =~/pdb/)\n      {\n	$id\
=~/pdb(.*)/;\n	$id=$1;\n      }\n    $id=~s/[|�_]/\
/g;\n    return $id;\n  }\nsub set_blast_type \n  \
{\n    my $file =@_[0];\n    if (&file_contains ($\
file,\"EBIApplicationResult\",100)){$BLAST_TYPE=\"\
EBI\";}\n    elsif (&file_contains ($file,\"NCBI_B\
lastOutput\",100)) {$BLAST_TYPE=\"NCBI\";}\n    el\
se\n      {\n	$BLAST_TYPE=\"\";\n      }\n    retu\
rn $BLAST_TYPE;\n  }\nsub blast_xml2profile \n  {\\
n    my ($name,$seq,$maxid, $minid, $mincov, $file\
)=(@_);\n    my (%p, $a, $string, $n);\n    \n\n\n\
    if ($BLAST_TYPE eq \"EBI\" || &file_contains (\
$file,\"EBIApplicationResult\",100)){%p=ebi_blast_\
xml2profile(@_);}\n    elsif ($BLAST_TYPE eq \"NCB\
I\" || &file_contains ($file,\"NCBI_BlastOutput\",\
100)){%p=ncbi_blast_xml2profile(@_);}\n    else \n\
      {\n	print \"************ ERROR: Blast Return\
ed an unknown XML Format **********************\";\
\n	die;\n      }\n    for ($a=0; $a<$p{n}; $a++)\n\
      {\n	my $name=$p{$a}{name};\n	$p{$name}{seq}=\
$p{$a}{seq};\n      }\n    return %p;\n  }\nsub nc\
bi_blast_xml2profile \n  {\n    my ($name,$seq,$ma\
xid, $minid, $mincov, $string)=(@_);\n    my ($L,$\
l, $a,$b,$c,$d,$nhits,@identifyerL);\n    \n    \n\
    $seq=~s/[^a-zA-Z]//g;\n    $L=length ($seq);\n\
    \n    %hit=&xml2tag_list ($string, \"Hit\");\n\
    \n    \n    for ($nhits=0,$a=0; $a<$hit{n}; $a\
++)\n      {\n	my ($ldb,$id, $identity, $expectati\
on, $start, $end, $coverage, $r);\n	my (%ID,%DE,%H\
SP);\n	\n	$ldb=\"\";\n\n	%ID=&xml2tag_list ($hit{$\
a}{body}, \"Hit_id\");\n	$identifyer=$ID{0}{body};\
\n	\n	%DE=&xml2tag_list ($hit{$a}{body}, \"Hit_def\
\");\n	$definition=$DE{0}{body};\n	\n	%HSP=&xml2ta\
g_list ($hit{$a}{body}, \"Hsp\");\n	for ($b=0; $b<\
$HSP{n}; $b++)\n	  {\n	    my (%START,%END,%E,%I,%\
Q,%M);\n\n	 \n	    %START=&xml2tag_list ($HSP{$b}{\
body}, \"Hsp_query-from\");\n	    %HSTART=&xml2tag\
_list ($HSP{$b}{body}, \"Hsp_hit-from\");\n	    \n\
	    %LEN=  &xml2tag_list ($HSP{$b}{body}, \"Hsp_a\
lign-len\");\n	    %END=  &xml2tag_list ($HSP{$b}{\
body}, \"Hsp_query-to\");\n	    %HEND=  &xml2tag_l\
ist ($HSP{$b}{body}, \"Hsp_hit-to\");\n	    %E=&xm\
l2tag_list     ($HSP{$b}{body}, \"Hsp_evalue\");\n\
	    %I=&xml2tag_list     ($HSP{$b}{body}, \"Hsp_i\
dentity\");\n	    %Q=&xml2tag_list     ($HSP{$b}{b\
ody}, \"Hsp_qseq\");\n	    %M=&xml2tag_list     ($\
HSP{$b}{body}, \"Hsp_hseq\");\n	    \n	    for ($e\
=0; $e<$Q{n}; $e++)\n\n	      {\n		$qs=$Q{$e}{body\
};\n		$ms=$M{$e}{body};\n		if ($seq eq\"\"){$seq=$\
qs;$L=length($seq);}\n		\n		$expectation=$E{$e}{bo\
dy};\n		$identity=($LEN{$e}{body}==0)?0:$I{$e}{bod\
y}/$LEN{$e}{body}*100;\n		$start=$START{$e}{body};\
\n		$end=$END{$e}{body};\n		$Hstart=$HSTART{$e}{bo\
dy};\n		$Hend=$HEND{$e}{body};\n	\n		$coverage=(($\
end-$start)*100)/$L;\n\n	\n		if ($identity>$maxid \
|| $identity<$minid || $coverage<$mincov){next;}\n\
		@lr1=(split (//,$qs));\n		@lr2=(split (//,$ms));\
\n		$l=$#lr1+1;\n		for ($c=0;$c<$L;$c++){$p[$nhits\
][$c]=\"-\";}\n		for ($d=0,$c=0; $c<$l; $c++)\n		 \
 {\n		    $r=$lr1[$c];\n		    if ( $r=~/[A-Za-z]/)\
\n		      {\n			\n			$p[$nhits][$d + $start-1]=$lr\
2[$c];\n			$d++;\n		      }\n		  }\n		$Qseq[$nhits\
]=$qs;\n		$Hseq[$nhits]=$ms;\n		$QstartL[$nhits]=$\
start;\n		$HstartL[$nhits]=$Hstart;\n		$identityL[\
$nhits]=$identity;\n		$endL[$nhits]=$end;\n		$defi\
nitionL[$nhits]=$definition;\n		$identifyerL[$nhit\
s]=$identifyer;\n		$comment[$nhits]=\"$ldb|$identi\
fyer [Eval=$expectation][id=$identity%][start=$Hst\
art end=$Hend]\";\n		$nhits++;\n	      }\n	  }\n  \
    }\n    \n    $profile{n}=0;\n    $profile{$pro\
file{n}}{name}=$name;\n    $profile{$profile{n}}{s\
eq}=$seq;\n    $profile {n}++;\n    \n    for ($a=\
0; $a<$nhits; $a++)\n      {\n	$n=$a+1;\n	\n	$prof\
ile{$n}{name}=\"$name\\_$a\";\n	$profile{$n}{seq}=\
\"\";\n	$profile{$n}{Qseq}=$Qseq[$a];\n	$profile{$\
n}{Hseq}=$Hseq[$a];\n	$profile{$n}{Qstart}=$Qstart\
L[$a];\n	$profile{$n}{Hstart}=$HstartL[$a];\n	$pro\
file{$n}{identity}=$identityL[$a];\n	$profile{$n}{\
definition}=$definitionL[$a];\n	$profile{$n}{ident\
ifyer}=$identifyerL[$a];\n	$profile{$n}{comment}=$\
comment[$a];\n	for ($b=0; $b<$L; $b++)\n	  {\n	   \
 if ($p[$a][$b])\n	      {\n		$profile{$n}{seq}.=$\
p[$a][$b];\n	      }\n	    else\n	      {\n		$prof\
ile{$n}{seq}.=\"-\";\n	      }\n	  }\n      }\n   \
 \n    $profile{n}=$nhits+1;\n    return %profile;\
\n  }\nsub ebi_blast_xml2profile \n  {\n    my ($n\
ame,$seq,$maxid, $minid, $mincov, $string)=(@_);\n\
    my ($L,$l, $a,$b,$c,$d,$nhits,@identifyerL,$id\
entifyer);\n    \n\n    \n    $seq=~s/[^a-zA-Z]//g\
;\n    $L=length ($seq);\n    %hit=&xml2tag_list (\
$string, \"hit\");\n    \n    for ($nhits=0,$a=0; \
$a<$hit{n}; $a++)\n      {\n	my ($ldb,$id, $identi\
ty, $expectation, $start, $end, $coverage, $r);\n	\
my (%Q,%M,%E,%I);\n	\n	$ldb=&tag2value ($hit{$a}{o\
pen}, \"database\");\n	$identifyer=&tag2value ($hi\
t{$a}{open}, \"id\");\n\n	$description=&tag2value \
($hit{$a}{open}, \"description\");\n	\n	%Q=&xml2ta\
g_list ($hit{$a}{body}, \"querySeq\");\n	%M=&xml2t\
ag_list ($hit{$a}{body}, \"matchSeq\");\n	%E=&xml2\
tag_list ($hit{$a}{body}, \"expectation\");\n	%I=&\
xml2tag_list ($hit{$a}{body}, \"identity\");\n	\n\\
n	for ($b=0; $b<$Q{n}; $b++)\n	  {\n	    \n	    \n\
	    $qs=$Q{$b}{body};\n	    $ms=$M{$b}{body};\n	 \
   if ($seq eq\"\"){$seq=$qs;$L=length($seq);}\n\n\
	    $expectation=$E{$b}{body};\n	    $identity=$I\
{$b}{body};\n	    \n	    	    \n	    $start=&tag2v\
alue ($Q{$b}{open}, \"start\");\n	    $end=&tag2va\
lue ($Q{$b}{open}, \"end\");\n	    $startM=&tag2va\
lue ($M{$b}{open}, \"start\");\n	    $endM=&tag2va\
lue ($M{$b}{open}, \"end\");\n	    $coverage=(($en\
d-$start)*100)/$L;\n	    \n	   # print \"$id: ID: \
$identity COV: $coverage [$start $end]\\n\";\n	   \
 \n	    \n	    if ($identity>$maxid || $identity<$\
minid || $coverage<$mincov){next;}\n	    # print \\
"KEEP\\n\";\n\n	    \n	    @lr1=(split (//,$qs));\\
n	    @lr2=(split (//,$ms));\n	    $l=$#lr1+1;\n	 \
   for ($c=0;$c<$L;$c++){$p[$nhits][$c]=\"-\";}\n	\
    for ($d=0,$c=0; $c<$l; $c++)\n	      {\n		$r=$\
lr1[$c];\n		if ( $r=~/[A-Za-z]/)\n		  {\n		    \n	\
	    $p[$nhits][$d + $start-1]=$lr2[$c];\n		    $d\
++;\n		  }\n	      }\n	  \n	    \n	    $identifyer\
L[$nhits]=$identifyer;\n	    $comment[$nhits]=\"$l\
db|$identifyer [Eval=$expectation][id=$identity%][\
start=$startM end=$endM]\";\n	    $nhits++;\n	  }\\
n      }\n    \n    $profile{n}=0;\n    $profile{$\
profile{n}}{name}=$name;\n    $profile{$profile{n}\
}{seq}=$seq;\n    $profile {n}++;\n    \n    for (\
$a=0; $a<$nhits; $a++)\n      {\n	$n=$a+1;\n	$prof\
ile{$n}{name}=\"$name\\_$a\";\n	$profile{$n}{seq}=\
\"\";\n	$profile{$n}{identifyer}=$identifyerL[$a];\
\n	\n	$profile{$n}{comment}=$comment[$a];\n	for ($\
b=0; $b<$L; $b++)\n	  {\n	    if ($p[$a][$b])\n	  \
    {\n		$profile{$n}{seq}.=$p[$a][$b];\n	      }\\
n	    else\n	      {\n		$profile{$n}{seq}.=\"-\";\\
n	      }\n	  }\n      }\n    $profile{n}=$nhits+1\
;\n    \n    return %profile;\n  }\n\nsub blast_xm\
l2hit_list\n  {\n    my $string=(@_[0]);\n    retu\
rn &xml2tag_list ($string, \"hit\");\n  }\nsub xml\
2tag_list  \n  {\n    my ($string_in,$tag)=@_;\n  \
  my $tag_in, $tag_out;\n    my %tag;\n    \n    i\
f (-e $string_in)\n      {\n	$string=&file2string \
($string_in);\n      }\n    else\n      {\n	$strin\
g=$string_in;\n      }\n    $tag_in1=\"<$tag \";\n\
    $tag_in2=\"<$tag>\";\n    $tag_out=\"/$tag>\";\
\n    $string=~s/>/>##1/g;\n    $string=~s/</##2</\
g;\n    $string=~s/##1/<#/g;\n    $string=~s/##2/#\
>/g;\n    @l=($string=~/(\\<[^>]+\\>)/g);\n    $ta\
g{n}=0;\n    $in=0;$n=-1;\n  \n \n\n    foreach $t\
 (@l)\n      {\n\n	$t=~s/<#//;\n	$t=~s/#>//;\n	\n	\
if ( $t=~/$tag_in1/ || $t=~/$tag_in2/)\n	  {\n	 \n\
	    $in=1;\n	    $tag{$tag{n}}{open}=$t;\n	    $n\
++;\n	    \n	  }\n	elsif ($t=~/$tag_out/)\n	  {\n	\
    \n\n	    $tag{$tag{n}}{close}=$t;\n	    $tag{n\
}++;\n	    $in=0;\n	  }\n	elsif ($in)\n	  {\n	   \\
n	    $tag{$tag{n}}{body}.=$t;\n	  }\n      }\n  \\
n    return %tag;\n  }\n\n\n\n\n","use Env qw(HOST\
);\nuse Env qw(HOME);\nuse Env qw(USER);\nwhile (<\
>)\n  {\n    if ( /^>(\\S+)/)\n      {\n	if ($list\
{$1})\n	  {\n	    print \">$1_$list{$1}\\n\";\n	  \
  $list{$1}++;\n	  }\n	else\n	  {\n	    print $_;\\
n	    $list{$1}=1;\n	  }\n      }\n    else\n     \
 {\n	print $_;\n      }\n  }\n      \n","\n\n\nuse\
 Env qw(HOST);\nuse Env qw(HOME);\nuse Env qw(USER\
);\n\n\nopen (F,$ARGV[0]);\nwhile ( <>)\n  {\n    \
@x=/([^:,;\\)\\(\\s]+):[^:,;\\)\\(]*/g;\n    @list\
=(@list,@x);\n  }\n$n=$#list+1;\nforeach $n(@list)\
{print \">$n\\nsequence\\n\";}\n\n\nclose (F);\n",\
"\nopen (F, $ARGV[0]);\n\nwhile ( <F>)\n  {\n    @\
l=($_=~/(\\S+)/g);\n    \n    $name=shift @l;\n   \
 \n    print STDOUT \"\\n>$name\\n\";\n    foreach\
 $e (@l){$e=($e eq \"0\")?\"O\":\"I\";print \"$e\"\
;}\n  }\nclose (F);\n\n		       \n    \n","use Env\
 qw(HOST);\nuse Env qw(HOME);\nuse Env qw(USER);\n\
\n$tmp=\"$ARGV[0].$$\";\nopen (IN, $ARGV[0]);\nope\
n (OUT, \">$tmp\");\n\nwhile ( <IN>)\n  {\n    $fi\
le=$_;\n    $file=~s/\\r\\n/\\n/g;\n    $file=~s/\\
\n\\r/\\n/g;\n    $file=~s/\\r\\r/\\n/g;\n    $fil\
e=~s/\\r/\\n/g;\n    print OUT \"$file\";\n  }\ncl\
ose (IN);\nclose (OUT);\n\nopen (OUT, \">$ARGV[0]\\
");\nopen (IN, \"$tmp\");\n\nwhile ( <IN>)\n{\n  p\
rint OUT \"$_\";\n}\nclose (IN);\nclose (OUT);\nun\
link ($tmp);\n\n"};
/******************************COPYRIGHT NOTICE*******************************/
/*� Centro de Regulacio Genomica */
/*and */
/*Cedric Notredame */
/*Fri Feb 18 08:27:45 CET 2011 - Revision 596. */
/*All rights reserved.*/
/*This file is part of T-COFFEE.*/
/**/
/*    T-COFFEE is free software; you can redistribute it and/or modify*/
/*    it under the terms of the GNU General Public License as published by*/
/*    the Free Software Foundation; either version 2 of the License, or*/
/*    (at your option) any later version.*/
/**/
/*    T-COFFEE is distributed in the hope that it will be useful,*/
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of*/
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the*/
/*    GNU General Public License for more details.*/
/**/
/*    You should have received a copy of the GNU General Public License*/
/*    along with Foobar; if not, write to the Free Software*/
/*    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA*/
/*...............................................                                                                                      |*/
/*  If you need some more information*/
/*  cedric.notredame@europe.com*/
/*...............................................                                                                                                                                     |*/
/**/
/**/
/*	*/
/******************************COPYRIGHT NOTICE*******************************/

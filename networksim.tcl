set ns [new Simulator]

$ns color 1 Blue
$ns color 2 Red

set nf [open sl.nam w]

$ns namtrace-all $nf

set nfl [open sl.tr w]

$ns trace-all $nfl

proc finish {} {
	global ns nfl nf
	$ns flush-trace
	close $nf
	close $nfl
	exec nam sl.nam &
	exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]

$ns at 0.1 "$n1 label \"CBR\""
$ns at 1.0 "$n0 label \"FTP\""

$ns duplex-link $n0 $n2 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail
$ns duplex-link $n2 $n3 0.3Mb 10ms DropTail
$ns duplex-link $n3 $n4 0.5Mb 10ms DropTail
$ns duplex-link $n3 $n5 0.5Mb 10ms DropTail

$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n2 $n3 orient right
$ns duplex-link-op $n3 $n4 orient right-up
$ns duplex-link-op $n3 $n5 orient right-down

$ns queue-limit $n2 $n3 40

set tcp [new Agent/TCP]
$ns attach-agent $n0 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n4 $sink
$ns connect $tcp $sink
$tcp set fid_ 1
$tcp set window_ 8000
$tcp set packetSize_ 552

set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set packetSize_ 552

set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

set udp0 [new Agent/UDP]
$ns attach-agent $n1 $udp0
set null [new Agent/Null]
$ns attach-agent $n5 $null
$ns connect $udp0 $null
$udp0 set fid_ 2

set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0
$cbr0 set type_ CBR
$cbr0 set packetSize_ 1000
$cbr0 set rate_ 0.01mb
$cbr0 set random_ false

$ns at 0.1 "$cbr0 start"
$ns at 1.0 "$ftp start"
$ns at 624.0 "$ftp stop"
$ns at 624.5 "$cbr0 stop"

set file [open cwnd_rtt.tr w]
$tcp attach $file
$tcp trace cwnd_
$tcp trace rtt_

$ns at 625.0 "finish"
$ns run

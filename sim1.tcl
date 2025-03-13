# Set up the simulation
set ns [new Simulator]

# Create two nodes (n0 and n1)
set n0 [$ns node]
set n1 [$ns node]

# Create a duplex link between the nodes (1Mb bandwidth, 10ms delay)
$ns duplex-link $n0 $n1 1Mb 10ms DropTail

# Create a TCP agent attached to n0 (sender)
set tcp [new Agent/TCP]

# Attach the TCP agent to node n0
$ns attach-agent $n0 $tcp

# Create a TCP Sink agent attached to n1 (receiver)
set sink [new Agent/TCPSink]

# Attach the TCP Sink agent to node n1
$ns attach-agent $n1 $sink

# Connect the TCP agent (sender) to the TCP Sink agent (receiver)
$ns connect $tcp $sink

# Set up an FTP application to generate traffic over the TCP connection
set ftp [new Application/FTP]

# Attach the FTP application to the TCP agent (sender)
$ftp attach $tcp

# Start the FTP application at time 0.5 seconds
$ns at 0.5 "$ftp start"

# Set up the simulation to run for 10 seconds
$ns at 10.0 "finish"

# Define the finish procedure to end the simulation
proc finish {} {
    global ns
    $ns flush
    exit 0
}

# Run the simulation
$ns run


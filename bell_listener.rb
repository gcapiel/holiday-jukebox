#!/usr/bin/env ruby

#simplest ruby program to read from arduino serial, 
#using the SerialPort gem
#(http://rubygems.org/gems/serialport)

require "serialport"
require "net/http"

#params for serial port
port_str = "/dev/rfcomm0"  #may be different for you
baud_rate = 9600
data_bits = 8
stop_bits = 1
parity = SerialPort::NONE

sp = SerialPort.new(port_str, baud_rate, data_bits, stop_bits, parity)

#just read forever
while true do
   while (i = sp.gets.chomp) do
   
      puts i
      if i[0,3] != "msg" then
      	puts 'play stereo'
		puts Net::HTTP.get(URI.parse("http://192.168.1.149/receiver_on.php"))
		sleep(4)
		puts Net::HTTP.get(URI.parse("http://192.168.1.149/sonosplay.php?file="+i))
		#sleep(7)
		#puts Net::HTTP.get(URI.parse("http://192.168.1.149/clear_queue.php"))
		#puts Net::HTTP.get(URI.parse("http://192.168.1.149/receiver_off.php"))

		#system('say "holy guacamole someones at the door"')
      end
    end
end
sp.close

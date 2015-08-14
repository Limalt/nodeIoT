--Limalt.io
--Sends data to thingspeak by serial port
--by Euler Alves Aug 2015
--Device ESP8266 (nodeMCU Firmware)
--Init Wi-Fi Station mode
--version: 1.0.1 
wifi.setmode(wifi.STATION)
--your wireless id
wifi.sta.config("SSID","PASS")
 wifi.sta.connect()
   tmr.alarm(1, 2500, 1, function() 
     if wifi.sta.getip()== nil 
      then 
    -- print(" Waiting IP...") 
      else 
       tmr.stop(1)
     -- print("IP = "..wifi.sta.getip())
     --  print("MAC = "..wifi.sta.getmac())
  end
end)

-- Start Uart
uart.on("data", 0, 
  function(data)
-- txd = data * local voltage
      local txd= data * 119.0
              
--- Send data and connection to thingspeak.com     
conn=net.createConnection(net.TCP, 0) 
 conn:on("receive", function(conn, payload) 
   print(payload) end)

----------------------------------------------------    
-- connection api.thingspeak.com 184.106.153.149
-- key: Get your key in thingspeak
conn:connect(80,'184.106.153.149') 
 conn:send("POST /update?key=your-key&field1="..txd.."&field4="..txd.." HTTP/1.1\r\n") 
  conn:send("Host: api.thingspeak.com\r\n") 
   conn:send("Accept: */*\r\n") 
    conn:send("\r\n")
 
--Close and disconnection
 conn:on("sent",function(conn)
   conn:close()
  end)
     conn:on("disconnection", function(conn)
  --   print("Sent", txd)                                
  end)

end, 1)


#https://python-forum.io/Thread-Writing-commands-to-serial
import serial, time



ser = serial.Serial('COM7', 19200, timeout=1)
print(ser)
# Delay zodat de vreemde tekens weg zijn
time.sleep(5)
while(1):
    response = ser.read(ser.inWaiting()).decode('ascii')
    print(response)
    time.sleep(5)
    if  (response[:3] == "201"):
        ser.write('kersthaan'.encode() + bytes([13]))
        time.sleep(1)
    # Bij de handshake moet het ook het geheime woord teruggeven
    
    if (response[10:3] == "200"):
        ser.write('1'.encode() + bytes([13]))
        time.sleep(1)



    if response[:3] == ("200"):
        print("hoi")
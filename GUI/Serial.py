#https://python-forum.io/Thread-Writing-commands-to-serial
import serial, time
HANDSHAKE = "kersthaan"
version = "1"

ser = serial.Serial('COM7', 19200, timeout=1)
print(ser)
# Delay zodat de vreemde tekens weg zijn
time.sleep(5)
while(1):
    response = ser.read(ser.inWaiting()).decode('ascii')
    print(response)
    time.sleep(1)

    if  (response[:3] == "201"):
        ser.write(HANDSHAKE.encode() + bytes([13]))
        time.sleep(1)

    if ('504' in response):
        # Exit de while loop en geef aan dat de ID niet matched
        print("ID doesn't match")


    # Bij de handshake moet het ook het geheime woord teruggeven
    elif ('201' and 'groeneotter' in response):
        print("Handshake bevestigd")



    # voer command uit
    # ser.write(opdracht.encode() + bytes([13]))
    # if setopdracht
    # elif getopdracht
    # elif rolopdracht
    # testen
    if ('200' in response):
        ser.write('GET_LIGHT'.encode() + bytes([13]))
        response = ser.read(ser.inWaiting()).decode('ascii')
        if response[:3] == '202':
            lichtintensiteit = response[12:9]
            print("lichtintensiteit:", lichtintensiteit)
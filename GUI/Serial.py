#https://python-forum.io/Thread-Writing-commands-to-serial
import serial, time
HANDSHAKE = "kersthaan"
version = "1"

def readSerial():
    return ser.read(ser.inWaiting()).decode('ascii')




ser = serial.Serial('COM7', 19200, timeout=1)
print(ser)
# Delay zodat de vreemde tekens weg zijn
time.sleep(5)
while(1):
    response = readSerial()
    print(response)
    time.sleep(1)


    if  (response[:3] == "201"):
        ser.write(HANDSHAKE.encode() + bytes([13]))
        time.sleep(1)
        response = readSerial()
        if ('504' in response):
            # Exit de while loop en geef aan dat de ID niet matched
            print("ID doesn't match")
        # Bij de handshake moet het ook het geheime woord teruggeven
        elif ('201' and 'groeneotter' in response):
            print("Handshake bevestigd")
            if ("200" in response):
                ser.write('GET_NAME'.encode() + bytes([13]))
                time.sleep(1)
                response = readSerial()
                name = response[14:] #TODO het moet de enter detecten en alles na de enter afsnijden
                print("naam", name)
                #print(response)
                if (len(name) is 0):
                    print("nieuw besturingseenheid")
                    #TODO geef het bordje een temporary name zodat het terug te vinden is
                    #TODO ergens een melding dat een nieuw bordje is aangesloten
                else:
                    print("bekend bordje")
                    ser.write('GET_VERSION'.encode() + bytes([13]))
                    time.sleep(1)
                    response = readSerial()
                    if(version in response):
                        print("yay")
                    else:
                        print("Outdated version")


    #TODO
    # voer command uit
    # ser.write(opdracht.encode() + bytes([13]))
    # if setopdracht
    # elif getopdracht
    # elif rolopdracht
    # testen
    if ('204' in response):
        ser.write('GET_LIGHT'.encode() + bytes([13]))
        response = readSerial()
        if response[:3] == '202':
            lichtintensiteit = response[12:9]
            print("lichtintensiteit:", lichtintensiteit)
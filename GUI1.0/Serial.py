#https://python-forum.io/Thread-Writing-commands-to-serial
import serial, time
HANDSHAKE = "kersthaan"
version = "1"

ser = serial.Serial('COM7', 19200, timeout=1)
print(ser)
# Delay zodat de vreemde tekens weg zijn
time.sleep(5)

def readSerial():
    return ser.read(ser.inWaiting()).decode('ascii')


#TODO ervoor zorgen dat wanneer je eenmaal gehandshaked hebt, dit niet weer te hoeven doen
def initialHandshake():
    response = readSerial()
    print(response)
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
                if (len(name) is 0): #TODO ipv dit if name is not in lijst
                    print("onbekend besturingseenheid")
                    #TODO geef het bordje een temporary name en locatie zodat het terug te vinden is
                    #TODO ADD a label in instellingen zodat de user de instellingen kan wijzigen
                else:
                    print("bekend bordje")
                    ser.write('GET_VERSION'.encode() + bytes([13]))
                    time.sleep(1)
                    response = readSerial()
                    if(version in response):
                        print("Same version, you may continue")
                    else:
                        print("Outdated version")
                        ser.write('Exit'.encode() + bytes([13]))
                    print("Response:", response)
                    # TODO voer command uit ....
                    # ser.write(opdracht.encode() + bytes([13]))
                    # if setopdracht
                    # elif getopdracht
                    # elif rolopdracht
                    # testen
                    #while(1):
                    # TODO in plaats van GET_LIGHT, voer opdracht uit

def doTask(task):
    response = readSerial()
    print(response)
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
            if ('204' in response):
                ser.write(task.encode() + bytes([13]))
                time.sleep(1)
                response = readSerial()
                print(response[:3])
                if response[:3] == '202':
                    taskvariable = response
                    print("yay")
                    print("lichtintensiteit:", taskvariable)
                    return taskvariable


task = "GET_LIGHT"
variable = doTask(task)






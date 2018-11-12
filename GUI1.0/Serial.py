import serial, time, glob, sys

HANDSHAKE = "kersthaan"
version = "1"
known_ports = []

#https://stackoverflow.com/questions/12090503/listing-available-com-ports-with-python
def serial_ports():
    """ Lists serial port names

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
    """
    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result

def readSerial():
    # https://python-forum.io/Thread-Writing-commands-to-serial
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



for port in serial_ports():
    if port not in known_ports:
        ser = serial.Serial(port, 19200, timeout=1)
        time.sleep(2)
        initialHandshake()
        known_ports.append(port)

print(known_ports)


# Delay zodat de vreemde tekens weg zijn


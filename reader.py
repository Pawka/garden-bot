import serial, time, datetime

port = '/dev/ttyUSB0'
bound = 9600

ser = serial.Serial(port, bound, timeout=1)
now = datetime.datetime.now()
filename = "results/" + now.strftime("%Y%m%d%H%M") + ".csv"
results = open(filename, 'w')

while True:
    now = datetime.datetime.now()
    try:
        output = ser.readline().strip()
        if len(output):

            # If stats data line is returned
            if "DAT;" == output[:4]:
                timestamp = now.strftime("%Y-%m-%d %H:%M")
                line = timestamp + "," + output[4:]
                results.write(line + "\n")
                results.flush()
                print line
            else:
                print output

        
    except serial.serialutil.SerialException, e:
        pass

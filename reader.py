import serial, time, datetime

port = '/dev/ttyUSB0'
bound = 9600
timeout = 2 #60

ser = serial.Serial(port, bound, timeout=1)
now = datetime.datetime.now()
filename = "results/" + now.strftime("%Y%m%d%H%M") + ".csv"
results = open(filename, 'w')

while True:
    now = datetime.datetime.now()
    try:
        output = ser.readline().strip()
        if len(output):
            timestamp = now.strftime("%Y-%m-%d %H:%M")
            line = timestamp + "," + output
            results.write(line + "\n")
            results.flush()
            print line
        
    except serial.serialutil.SerialException, e:
        pass
    time.sleep(timeout)

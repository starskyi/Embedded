# simple inquiry example
import bluetooth
import time
# nearby_devices = bluetooth.discover_devices(lookup_names=True)
# print("Found {} devices.".format(len(nearby_devices)))

# for addr, name in nearby_devices:
#     print("  {} - {}".format(addr, name))

sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
try:
    # sock.connect(("A7:66:47:DE:33:81", 1))
    sock.connect(("A8:6A:86:12:83:C1", 1))
    #sock.connect("21:08:30:17:2F:4C", "U-King", 1)
    # print("Connected successfully. {} ({})".format(name, addr))
    sock.sendall(b"Hello, Bluetooth!")
    msg = sock.recv(1024)
    
    time.sleep(100)
    print(msg)
except Exception as e:
    print(e)
import bluetooth

def list_services(device_address):
    services = bluetooth.find_service(address=device_address)
    if services:
        print(f"Services on {device_address}:")
        for svc in services:
            print(f"  Name: {svc['name']}, Port: {svc['port']}, Protocol: {svc['protocol']}")
    else:
        print(f"No services found on {device_address}.")

# 使用前面找到的设备地址
device_address = "A8:6A:86:12:83:C1"
list_services(device_address)

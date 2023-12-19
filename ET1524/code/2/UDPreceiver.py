# Max Dahlgren, Linus Jansson

import socket
from datetime import datetime


serverPort = 12000
ip = "0.0.0.0"

sock = socket.socket(socket.AF_INET,
                     socket.SOCK_DGRAM)
sock.bind((ip, serverPort))

nextId = 10000

numPackets = 0
now = None

while True:
    data, addr = sock.recvfrom(1500)
    if numPackets == 0:
        now = datetime.now()
    numPackets += 1
    msgId = int(data[0:5])
    msg = data[5:-4]
    if msgId != nextId:
        print(f"ERROR EXPECTED MSG {nextId} BUT RECVIED {msgId}")
        break
    nextId += 1
    if numPackets % 100 == 0:
        print(f"{numPackets} packets received in {datetime.now() - now}")
    print(f"received message id: {msgId}: {msg[0:50]}...")

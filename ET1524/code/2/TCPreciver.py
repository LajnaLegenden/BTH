import socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
well_known_port = 12000
sock.bind(('127.0.0.1', well_known_port))
sock.listen(100000)
nextId = 10000

numPackets = 0
now = None
try:
    while 1:
        newSocket, address = sock.accept()
        # loop serving the new client
        while 1:
            try:
                data = newSocket.recv(1500)
                if not data:
                    break
                msgId = int(data[0:5])
                msg = data[5:-4]
                if msgId != nextId:
                    print(f"ERROR EXPECTED MSG {nextId} BUT RECVIED {msgId}")
                    break
                nextId += 1
                numPackets += 1
                if numPackets % 100 == 0:
                    print(f"{numPackets} packets received")
                print(f"received message id: {msgId}: {msg[0:50]}...")       
                newSocket.close()
            except OSError:
                break
finally:
    sock.close()

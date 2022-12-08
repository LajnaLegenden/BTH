
# Max Dahlgren, Linus Jansson

from random import randrange
import socket
from time import sleep

serverPort = 12000
receiverIp = "127.0.0.1"


def getData(length):
    string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
    out = ""
    for i in range(length):
        out += string[randrange(0, len(string)-1, 1)]
    return out


msgToSend = getData(1431)
nrOfMsg = 1000
msgSpeed = 50

print("UDP target IP: %s" % receiverIp)
print("UDP target Port: %s" % serverPort)
print("UDP target Message: %s" % msgToSend)

#asd
for i in range(nrOfMsg):
    data = None
    msg = f"{10000+i}{msgToSend}####"
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((receiverIp, serverPort))
        s.sendall(msg.encode())
        


    sleep(1/msgSpeed)

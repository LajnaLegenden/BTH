# UDP Sender
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

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

#asd
for i in range(nrOfMsg):

    msg = f"{10000+i}{msgToSend}####"
    sock.sendto(msg.encode(), (receiverIp, serverPort))
    sleep(1/msgSpeed)

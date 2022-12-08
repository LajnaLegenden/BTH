from socket import *
# serverName = 'hostname'
serverName = 'www.ingonline.nu'
serverPort = 443

# create TCP socket on client to use for connecting to remote server
clientSocket = socket(AF_INET, SOCK_STREAM)

# open the TCP connection
clientSocket.connect((serverName, serverPort))

# Input sentence from keyboard
sentence = """
GET /index.php HTTP/1.1
User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)
Host: www.ingonline.nu
Connection: Keep-Alive
"""

# send text over the TCP connection
# there's no need to specify server name & port
# sentence converted to bytes
clientSocket.send(sentence.encode())

# get modified sentence back from server
modifiedSentence = clientSocket.recv(1024)
print ('From Server:', modifiedSentence.decode())

# close the TCP connection
clientSocket.close()

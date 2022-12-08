import socket

server = "www.ingonline.nu"
port = 80
path = "/tictactoe/index.php"
data = "board=oxoxoxeee"

url = path + "?" + data
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((server, 80))
sock.send(
    "GET {path} HTTP/1.1\nHost:{server}\nConnection: close\n\n".format(server=server, path=url).encode())
response = sock.recv(1024)
sock.close()
print(response.decode())

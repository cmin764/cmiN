"""
Acest script porneste un server pe sockets. 
Scrieti un client care comunica cu acest server si reuseste sa
    il faca sa ii trimita mesajul "Well done!".

Atentie: nu modificati acest script!

Usage: 
    this_script.py ipv4_addr port

Example: 
    this_script.py 127.0.0.1 80
"""

import sys
import socket
import random

IS_PY3 = sys.version_info >= (3,)

# Hint: clientul isi poate stabili singur de pe port face conexiunea cu serverul (bind) sau
#       poate accesa adresa asignata automat de sistemul operare prin getsockname()

def read_message_from_client(client_socket):
    message = client_socket.recv(1024)
    if IS_PY3:
        message = message.decode()
    return message

def send_message_to_client(client_socket, message):
    if isinstance(message, str) and IS_PY3:
        message = message.encode()
    client_socket.send(message)


def start_server(host, port):
    server_socket = socket.socket()

    if not isinstance(port, int):
        port = int(port)

    server_socket.bind((host, port))
    server_socket.listen(5)

    while True:
        client_socket, (client_host, client_port) = server_socket.accept()
        print("[!] Accepted client {0}:{1}".format(client_host, client_port))

        divisors = [(random.randint(50, 100) * 2 + 1) for _ in range(3)]
        number = 1
        for d in divisors:
            number *= d

        send_message_to_client(client_socket, str(number))

        final_response = read_message_from_client(client_socket)
        try:
            final_response = int(final_response)
        except ValueError:
            print("[x] Invalid message from client")
            continue

        print("[!] Got final response: {}".format(final_response))
        if number % final_response == 0 and \
                final_response != 1 and \
                final_response != number:
            print("Well done!")
            send_message_to_client(client_socket, "Well done!")
            client_socket.close()
            server_socket.close()
            exit(0)


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print(__doc__)
        exit(-1)

    # ignore this if
    if sys.argv[1] == "md5":
        import hashlib
        with open(__file__, "r") as f:
            content = f.read()
        if IS_PY3:
            content = content.encode()
        print(hashlib.md5(content).hexdigest())
        exit()

    start_server(sys.argv[1], sys.argv[2])

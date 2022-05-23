#!/usr/bin/env python
# nlantau, 2022-04-09

import socket
import uuid


def rfcomm_server():
    host = 'E8:84:A5:B0:82:AD'
    phone = 'D8:55:75:36:4F:2E'

    port = 0x1101
    s = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
    s.bind((host, port))
    s.listen(1)

    try:
        client, addr = s.accept()
        while 1:
            data = client.recv(1024)
            if data:
                print(data)
                client.send(data)
    except:
        print("Closing socket")
    finally:
        client.close()
        s.close()


    print("All done")

rfcomm_server()

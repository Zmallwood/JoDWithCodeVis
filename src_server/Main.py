import socket

print("Running JoD Server")

HOST = "127.0.0.1"  # Standard loopback interface address (localhost)
PORT = 65432  # Port to listen on (non-privileged ports are > 1023)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    print("Binding")
    s.bind((HOST, PORT))
    print("Listening")
    s.listen()
    print("Accepting")
    while True:
        conn, addr = s.accept()
        print("Accepted")
        with conn:
            print(f"Connected by {addr}")
            while True:
                try:
                    print("Recieving")
                    data = conn.recv(1024)
                    print("Recieved data: ", data)
                    if not data:
                        break
                    msgs = data.split(b"<END>")
                    for msg in msgs:
                        print("Msg: ", msg)
                        if msg[0:6] == b"Login\n":
                            print("Do login")
                            login_parts = msg.split(b"\n")
                            user_name = login_parts[1].decode("utf-8")
                            password_hash = int(login_parts[2])
                            print("Try and login with username=" + user_name + " and password_hash=" + str(password_hash))
                            if user_name == "adde":
                                conn.send(b"LoginSuccessful<END>")
                            else:
                                conn.send(b"LoginFailed<END>")
                    conn.send(b"Tessst from scoket")
                except ConnectionResetError:
                    print("Connection reset by peer.")
                    break


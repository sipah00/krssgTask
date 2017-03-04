from socket import *
from thread import *
 
host = '127.0.0.1'
port = 8082 

sock = socket()


sock.bind((host, port))

sock.listen(2) 
 
def clientthread(conn):
     while True:
          list=[]
          data=conn.recv(1024)
          if not data:
             break
          print "connected from user :"+str(addr)
          list=data.split()
          list.sort(key=int)
          ans=' '.join(list)
          print("sending sorted list")
          conn.send(ans) 
while True:
    conn, addr = sock.accept()

    start_new_thread(clientthread,(conn,)) 
 
conn.close()
sock.close()

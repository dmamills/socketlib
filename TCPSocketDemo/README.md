# TCP File Transfer Server

This demo creates a server that allows Clients to connect requesting a file located on the servers machine.
If the file exists, it is opened as a stream, and transferred to the client in chunks.

The server contains a const integer MAX_FILES_SENT that represents how many files the server will send before, it
shuts down.

The Client/Server operations exist using this protocol:

* CLIENT -> connects to server
* CLIENT -> sends "OK"
* SERVER -> replys "OK"
* CLIENT -> sends FILENAME
* SERVER -> sends either FILESIZE or NOTFOUND
* CLIENT -> if FILESIZE recieved, sends "OK", else closes connection
* LOOP
  * SERVER -> sends SIZE OF CHUNK
  * SERVER -> sends CHUNK

# TCP File Transfer Client

This demo creates a client that connects to a server to request a file. It takes two parameters to run,
the name of the file to request, and the name to save the file as locally.

Usage examples:

```
 TCPSocketDemoClient.exe <request file> <local file>
 TCPSocketDemoClient.exe C:\\test.md out.md
 TCPSocketDemoClient.exe somecoolsong.mp3 local.mp3
```

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

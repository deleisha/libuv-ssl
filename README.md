# libuv-tls
Add SSL/TLS functionality on top of libuv using OpenSSL.

This small library adds SSL/TLS functionality using BIO pair on libuv. It tries to provide
API similar to libuv with bare minimum change. Also it tries to use facilities provided by
OpenSSL. Currently it scratches BIO pair only as a result. This might go away as we learn
more and more both on OpenSSL and libuv. Writing our own custom BIO will lend lot more
flexibility. 

We intend to provide the library as subpart of libuv, if we can finish soon.

### TODO:
- Add session resumption feature - may be later version
- Renegotiation not yet handled - may be later version
- Work on supporting DTLS support - later versions
- Handle multiple, simultaneous client connection - must have for next release
- Work on building and packaging



### TEST:
To test the echo server, generate the test cert and key using

```openssl req -x509 -newkey rsa:2048 -nodes -keyout server-key.pem -out server-cert.pem```

```make && ./echo```

Now the echo server is compiled and started and we can start sending some data using

```openssl s_client -connect address:8000 -nbio -state -msg -debug```


where address is your ip address.

### CONTRIBUTING
Clone/fork the library and play around and provide feedback/patches or anything for improvement.

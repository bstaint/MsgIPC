import zmq
import msgpack

context = zmq.Context()
sub = context.socket( zmq.SUB )
sub.connect( "tcp://127.0.0.1:5555" )
sub.setsockopt(zmq.LINGER, 0)
sub.setsockopt_string(zmq.SUBSCRIBE, "")

while True:
    bytes_ = sub.recv()
    print(msgpack.unpackb(bytes_, raw=False))

sub.close()
context.term()   
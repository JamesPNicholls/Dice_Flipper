import struct
x = 500


xx = x.to_bytes(2,'big')
print(xx[:1])
print(xx[1:2])
print(xx[2:3])
print(len(xx))
s = struct.unpack('H',xx)
print(s)
m = memoryview(xx).cast('H')
print(m[0])
d = int.from_bytes(xx[1:2], 'big')
print(d)
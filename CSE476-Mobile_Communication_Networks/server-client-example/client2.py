from urllib import request

fhand = request.urlopen("http://data.pr4e.org/romeo.txt")

for line in fhand:
    print(line.decode().strip())
